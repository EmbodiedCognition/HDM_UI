/****************************************************************************
 *                                                                          *
 * HDM_UI/HDM--Physics-base inverse kinematics and inverse dynamics               *
 * Copyright (c) 2013 Joseph Cooper                                         *
 *                                                                          *
 * This software is provided 'as-is', without any express or implied        *
 * warranty. In no event will the authors be held liable for any damages    *
 * arising from the use of this software.                                   *
 *                                                                          *
 * Permission is granted to anyone to use this software for any purpose,    *
 * including commercial applications, and to alter it and redistribute it   *
 * freely, subject to the following restrictions:                           *
 *                                                                          *
 *  1. The origin of this software must not be misrepresented; you must not *
 *  claim that you wrote the original software. If you use this software    *
 *  in a product, an acknowledgment in the product documentation would be   *
 *  appreciated but is not required.                                        *
 *                                                                          *
 *  2. Altered source versions must be plainly marked as such, and must not *
 *  be misrepresented as being the original software.                       *
 *                                                                          *
 *  3. This notice may not be removed or altered from any source            *
 *  distribution.                                                           *
 ****************************************************************************/
#include "simworld.h"
#include "CapBody.h"

#include "sequence.h"

SimWorld::SimWorld(QObject *parent) :
    QObject(parent)
{
  dInitODE();
  world = dWorldCreate();
  space = dHashSpaceCreate(0);
  contact_group = dJointGroupCreate(0);

  // Setup gravity
  dWorldSetGravity (world,0,0,-9.8);

  // Setup constraint satisfaction parameters.
  dWorldSetERP (world, 0.5);     //up, torque down
  dWorldSetCFM(world, 0.0001);   // up torque down
  dWorldSetContactSurfaceLayer(world,.005); // How deeply an object can penetrate (in meters)
  dWorldSetMaxAngularSpeed(world,15); // A hard limit on how fast anything can spin
  //dWorldSetLinearDamping(world,.02);  // Linear Friction
  //dWorldSetAngularDamping(world,.02); // Angular friction

  // Create the ground plane
  ground_plane = dCreatePlane (space,0,0,1,0.0);
  ground_squish = .001;    //   (SOFT|Friction = 0.1)
  ground_friction = 0.01;


  stepsize=1/60.0;
  //load marker file and body files
  body = new CapBody(this);
  body->createBody(world,space);
  marker_space = dSimpleSpaceCreate(0);
  target_space = dSimpleSpaceCreate(0);
  std::cout << "[Simworld] Loading marker_data..." << std::endl;
  marker_data = new MarkerData(world,marker_space,this);
  marker_data->body_pointer=body;
  body->changeMarkLinks(marker_data->marker_count);
  std::cout << "[SimWorld] loading body model data..." <<  std::endl;
  body->loadBody(defaultMarkerMapFile, defaultMarkerRelPosFile,defaultBodyDimFile, defaultJointAnchorFile);
  body->updateBodyMarkMapCMU(marker_data->labels);
  body->updatePosMapCMU(marker_data->labels);
  std::cout << "[SimWorld] SimWorld Created." <<  std::endl;
  paused=true;
  single_step=false;

  angle_sequence = new Sequence(this);
  angle_sequence2 = new Sequence(this);
  torque_sequence = new Sequence(this);
  torque_sequence2 = new Sequence(this);
  position_sequence = new Sequence(this);

  self_collide=false;
  follow_sequence_source_state=0;

 // one set:
  total_torques = 0.0;
  main_file = fopen("/Users/lijialiu/Documents/HDM_UI/HDM/data/results/totals.txt","w");
}


SimWorld::~SimWorld()
{
  fclose(main_file);
}


#define MAX_CONTACTS 4
void SimWorld::collideGeoms(void* data,dGeomID object_1_ID,dGeomID object_2_ID)
{
  dContact contact[MAX_CONTACTS];
  SimWorld* world_object = static_cast<SimWorld*>(data);
  dBodyID body_1 = dGeomGetBody(object_1_ID);
  dBodyID body_2 = dGeomGetBody(object_2_ID);

  if (body_1 == NULL) {
    body_1 = body_2;
    body_2 = NULL;
    dGeomID object_3_ID = object_1_ID;
    object_1_ID = object_2_ID;
    object_2_ID = object_3_ID;
  }

  // Don't use body-body collisions for now.
  if (!world_object->self_collide && (body_2!=NULL)) return;

  // exit without doing anything if the two bodies are connected by a joint
  if (body_1 && body_2 && dAreConnectedExcluding (body_1,body_2,dJointTypeContact)) return;


  // If all bodies are kinematic, we don't need to do anything here since
  // adding constraints has no effect.
  if ( ((body_1==NULL)||dBodyIsKinematic(body_1)) && ((body_2==NULL)||dBodyIsKinematic(body_2))) return;

  // Exclude collisions between the upper arm and torso.
  if (((object_1_ID==world_object->body->geometries[CapBody::UP_TORSO_BODY])||
       (object_2_ID==world_object->body->geometries[CapBody::UP_TORSO_BODY])) &&
      ((object_1_ID==world_object->body->geometries[CapBody::RUP_ARM_BODY])||
       (object_2_ID==world_object->body->geometries[CapBody::RUP_ARM_BODY])||
       (object_1_ID==world_object->body->geometries[CapBody::LUP_ARM_BODY])||
       (object_2_ID==world_object->body->geometries[CapBody::LUP_ARM_BODY]))) return;

  contact[0].surface.mode = dContactSoftCFM | ((body_1&&body_2)?0:dContactApprox1); //Surfaces are just a little squishy
  contact[0].surface.soft_cfm = (body_1&&body_2)?0.001:world_object->ground_squish; //
  contact[0].surface.bounce_vel = 0.01;
  contact[0].surface.bounce = 0.25;
  contact[0].surface.mu = (body_1&&body_2)?1:world_object->ground_friction; // Strong friction with ground

  for (int ii=1;ii<MAX_CONTACTS;++ii) {
    contact[ii].surface.mode = contact[0].surface.mode;
    contact[ii].surface.soft_cfm = contact[0].surface.soft_cfm;
    contact[ii].surface.bounce_vel = contact[0].surface.bounce_vel;
    contact[ii].surface.bounce = contact[0].surface.bounce;
    contact[ii].surface.mu = contact[0].surface.mu;
  }

  int numC = dCollide (object_1_ID,object_2_ID,MAX_CONTACTS,&contact[0].geom,sizeof(dContact) );


 // std::cout << "numC begin:" << numC << std::endl;
  for (int ii=0;ii<numC;++ii) {
    dJointID cc = dJointCreateContact (world_object->world,world_object->contact_group,&contact[ii]);
    dJointAttach(cc,body_1,body_2);
    if ((body_2==NULL)&&(world_object->number_active_ground_contacts<MAX_GROUND_FEEDBACK)) {
      dJointSetFeedback(cc,&(world_object->ground_feedback[world_object->number_active_ground_contacts]));
      dOPE(world_object->contact_point[world_object->number_active_ground_contacts],=,contact[ii].geom.pos);

      if ((body_1==world_object->body->body_segments[CapBody::L_HEEL_BODY])
          ||(body_1==world_object->body->body_segments[CapBody::L_TARSAL_BODY]))
          //||(body_1==world_object->body->bodies[CapBody::L_TOE_BODY]))
      {
        world_object->left_foot_feedback.push_back(world_object->number_active_ground_contacts);

//        std::cout << "left_foot"<< std::endl;
//        std::cout << world_object->number_active_ground_contacts << std::endl;

      } else if ((body_1==world_object->body->body_segments[CapBody::R_HEEL_BODY])
                 ||(body_1==world_object->body->body_segments[CapBody::R_TARSAL_BODY]))
        //||(body_1==world_object->body->bodies[CapBody::R_TOE_BODY]))
      {
        world_object->right_foot_feedback.push_back(world_object->number_active_ground_contacts);
       // std::cout << "right foot on the ground." << std::endl;
//        std::cout << world_object->number_active_ground_contacts << std::endl;

      }
      world_object->number_active_ground_contacts+=1;
    }
  }
 // std::cout << "numC end" << std::endl;
}//end SimWorld::collideGeoms

void SimWorld::updateSeqFrame()
{
  if (follow_sequence_source_state==1 || follow_sequence_source_state==2) {
    body->setTargetFrame(angle_sequence->getFrame(sequence_frame));
    sequence_frame+=1;
  }
  if (follow_sequence_source_state==3) {
    DataFrame* frame = torque_sequence->getFrame(sequence_frame);
    if (frame) {
      applyTorquesToBody(frame);
      sequence_frame+=1;
    }
  }
}

void SimWorld::applyTorquesToBody(DataFrame* joint_frame)
{
//  body->zeroAccumulators();
  body->applyForceFrame(joint_frame);

  for (int joint_index=0; joint_index<body->JOINT_COUNT; ++joint_index) {
    for (int axis_index=0; axis_index<3; axis_index++) {
      fprintf(main_file,"%lf ",joint_frame->getData(joint_index,axis_index));
      fprintf(main_file,"\n");
    }
  }
}


void SimWorld::setStepSize(double ss)
{
  if (stepsize!=ss) {
    stepsize=ss;
    //Optional emit
    body->setStepSize(ss);
  }
}

//Simulation types

void SimWorld::follow(int type)
{
  follow_sequence_source_state = type;
  switch (type) {
  case 0:
    // Follow markers
    emit useMarkers(true);
    break;
  case 1:
    // Follow angles
    emit useMarkers(false);
    sequence_frame = 0;
    break;
  case 2:
    // Instead of blindly following torques generated as a sequence
    // We find and then apply the torques.
    emit useMarkers(false);
    sequence_frame = 0;
    break;
  case 3:
    // Follow torques
    emit useMarkers(false);
    sequence_frame = 0;
    break;
  default:
    // Uh oh.
    break;
  }
}


/*
  Before each step, we need to capture the
  orientation of all the body parts.

  Afterward, when we get the joint feedback,
  we need to record it in the local frame
  of reference
  */

void SimWorld::step()
{

   marker_data->setStepTime(stepsize);
   marker_data->step();

  if (single_step || !paused) {



    dSpaceCollide (space,this,&collideGeoms);

    //********
    // We need to save/set the state _before_ we apply the
    // control signal.  Setting the body state
    // changes things ever so slightly by re-normalizing
    // the quaternions.

    // Record the current position and orientation of the bodies
    body->saveTempState();
    //This sets the body state to what it currently is
    // but it also ensures that the bodies are all in the
    // same order every time we go through.
    body->restoreTempState();

    // Set the target joint angles/stiffness
    // or apply forward dynamics torques
    updateSeqFrame();
    body->updateControl();


    // Get ready to capture ground forces on the feet.
  number_active_ground_contacts=0;
  left_foot_feedback.clear();
  right_foot_feedback.clear();


    dWorldStep (world,stepsize);
    body->findMassProperties();
    single_step=false;
    JointFrame* joint_frame;
    if (follow_sequence_source_state==0) {
      //Follow Markers
      //Save computed angles
      joint_frame = new JointFrame;
      body->fillJointFrame(joint_frame);
      angle_sequence->appendFrame(joint_frame);
    }
    if (follow_sequence_source_state==1) {

      //  std::cout << "1" << std::endl;
      //Follow Angles
      //save computed torques
      joint_frame = new JointFrame;
      body->fillForceFrame(joint_frame);
      torque_sequence->appendFrame(joint_frame);
    }
    if (follow_sequence_source_state==2) {


    //    std::cout << "2" << std::endl;

      //Follow Alt Angles
      // Grab the torques
      joint_frame = new JointFrame;
      body->fillForceFrame(joint_frame);
      torque_sequence->appendFrame(joint_frame);

      //Get to the real state after applying torques
      // Rewind
      body->restoreTempState();
      // Zero-control
      body->zeroControl();
      // Apply torques
      applyTorquesToBody(joint_frame);
      // Step again (don't need to collide again...)
      // We keep the old collision joints
      dWorldStep (world,stepsize);
      body->findMassProperties();
      body->restoreControl();

      //Grab angles
      joint_frame = new JointFrame;
      body->fillJointFrame(joint_frame);
      angle_sequence2->appendFrame(joint_frame);
    }
    if (follow_sequence_source_state==3) {
      //Follow Torques
      //save computed torques
      joint_frame = new JointFrame;
      body->fillForceFrame(joint_frame);
      torque_sequence2->appendFrame(joint_frame);
    }

    dJointGroupEmpty (contact_group);
    line_list.clear();
    GLine line;

    // Raw ground feedback lines
    line.col[0]=1;
    line.col[1]=1;
    line.col[2]=0;
    for (int ii=0;ii<number_active_ground_contacts;++ii) {
      dOPE(line.p1,=,contact_point[ii]);
      line.p2[0] = contact_point[ii][0]+ground_feedback[ii].f1[0]*.001;
      line.p2[1] = contact_point[ii][1]+ground_feedback[ii].f1[1]*.001;
      line.p2[2] = contact_point[ii][2]+ground_feedback[ii].f1[2]*.001;
      //line_list.push_back(line);
    }

    // Composite foot feedback lines
    double total_magnitude;
    int number_of_ground_force_feedback_lines;
    dReal* pt;
    dReal  mg;
    line.col[0]=0;
    line.col[1]=1;
    line.col[2]=0;
    dOPEC(line.p1,=,0);
    dOPEC(line.p2,=,0);
    total_magnitude=0;
    number_of_ground_force_feedback_lines=left_foot_feedback.size();
    for (int ii=0;ii<number_of_ground_force_feedback_lines;++ii) {
      pt = contact_point[left_foot_feedback[ii]];
      mg = ground_feedback[left_foot_feedback[ii]].f1[2];
      line.p1[0]+=pt[0]*mg;
      line.p1[1]+=pt[1]*mg;
      line.p1[2]+=pt[2]*mg;
      total_magnitude+=mg;
    }
    if (number_of_ground_force_feedback_lines>0) {
      dOPEC(line.p1,/=,total_magnitude);
      dOPE(line.p2,=,line.p1);
      // 80kg (~800N) should be a 1.6m line
      line.p2[2]+=total_magnitude*.002;
      line_list.push_back(line);
    }



    dOPEC(line.p1,=,0);
    dOPEC(line.p2,=,0);
    total_magnitude=0;
    number_of_ground_force_feedback_lines=right_foot_feedback.size();
    for (int ii=0;ii<number_of_ground_force_feedback_lines;++ii) {
      pt = contact_point[right_foot_feedback[ii]];
      mg = ground_feedback[right_foot_feedback[ii]].f1[2];
      line.p1[0]+=pt[0]*mg;
      line.p1[1]+=pt[1]*mg;
      line.p1[2]+=pt[2]*mg;
      total_magnitude+=mg;
    }
    if (number_of_ground_force_feedback_lines>0) {
      dOPEC(line.p1,/=,total_magnitude);
      dOPE(line.p2,=,line.p1);
      line.p2[2]+=total_magnitude*.002;
      line_list.push_back(line);
    }


    // Torques
    line.col[0]=.5;
    line.col[1]=0;
    line.col[2]=1;
    CapBody* body = this->body;

    const dReal* body_waist_position = dBodyGetPosition(body->body_segments[CapBody::WAIST_BODY]);
    const dReal* body_root_torque = body->feedback[CapBody::ROOT_ANGMOTOR_JOINT].t1;
    dOPE(line.p1,=,body_waist_position);
    line.p2[0]=body_waist_position[0]+body_root_torque[0]*.001;
    line.p2[1]=body_waist_position[1]+body_root_torque[1]*.001;
    line.p2[2]=body_waist_position[2]+body_root_torque[2]*.001;
    //lineList.push_back(line);

    // Center of mass projection
    body_waist_position = body->center_of_mass;
    line.col[0]=0;
    line.col[1]=0;
    line.col[2]=0;
    dOPE(line.p1,=,body_waist_position);
    dOPE(line.p2,=,body_waist_position);
    line.p2[2]=0;
    //lineList.push_back(line);

    // Linear velocity
    line.col[0]=1;
    line.col[1]=0;
    line.col[2]=0;
    line.p2[0]=body_waist_position[0]+body->senter_lin_vel[0]*.1;
    line.p2[1]=body_waist_position[1]+body->senter_lin_vel[1]*.1;
    line.p2[2]=body_waist_position[2]+body->senter_lin_vel[2]*.1;
    //lineList.push_back(line);

    // Angular velocity
    line.col[0]=0;
    line.col[1]=0;
    line.col[2]=1;
    line.p2[0]=body_waist_position[0]+body->center_ang_vel[0]*.1;
    line.p2[1]=body_waist_position[1]+body->center_ang_vel[1]*.1;
    line.p2[2]=body_waist_position[2]+body->center_ang_vel[2]*.1;
    //lineList.push_back(line);

    //if (!follow_mark) {
    //  joint_frame->writeData(main_file);
    //}
  }
}

void SimWorld::pauseSim(bool pp)
{
  paused=pp;
}

void SimWorld::setSingleStep()
{
  single_step=true;
  paused=true;

}



void SimWorld::setGroundFriction(double friction)
{
  ground_friction = friction;
}

void SimWorld::setTerrainSoftness(double terrain)
{
  ground_squish = terrain;
}

void SimWorld::setGroundCFM(double cfm)
{
  ground_CFM = cfm;
}

void SimWorld::setGroundERP(double erp)
{
  ground_ERP = erp;
}

void SimWorld::setGroundSurfaceLayer(double sfl)
{
  ground_surfaceLayer = sfl;
}


void SimWorld::setTerrainZ(double z_value)
{
  dGeomPlaneSetParams(ground_plane,0,0,1,z_value);
}


void SimWorld::setSelfCollide(bool hit_self)
{
  self_collide=hit_self;
}


////Reset motions/////
void SimWorld::setMotion(const char* newfile){
    dJointGroupEmpty (contact_group);
    contact_group = dJointGroupCreate(0);
    std::cout << "[SimWorld] reload marker data..." << std::endl;
    marker_data->reloadMarkerfile(newfile);
    body->changeMarkLinks(marker_data->marker_count);
    body->loadBody(defaultMarkerMapFile, defaultMarkerRelPosFile,defaultBodyDimFile, defaultJointAnchorFile);
    body->updateBodyMarkMapCMU(marker_data->labels);
    body->updatePosMapCMU(marker_data->labels);
    body->copyToSim();
}

void SimWorld::setCMotion(const char* markerfile, const char* markerMap, const char* markerRelPos,const char* bodyDim, const char* jointAnchor){
      std::cout << "[SimWorld] Custom setting..." << std::endl;
      marker_data->reloadCMarkerfile(markerfile);
      body->changeMarkLinks(marker_data->marker_count);
      body->loadCBody(markerMap, markerRelPos,bodyDim, jointAnchor);
      usingDefaultSettings = false;
}


void SimWorld::setDMotion(){
      std::cout << "[SimWorld] Default setting..." << std::endl;
      marker_data->reloadCMarkerfile(defaultMarkerFile);
      body->changeMarkLinks(marker_data->marker_count);
      body->loadBody(defaultMarkerMapFile, defaultMarkerRelPosFile, defaultBodyDimFile, defaultJointAnchorFile);
      usingDefaultSettings = true;
}



/////Write angles/torques to files//////
void SimWorld::anglesToFile(QString filename)
{
  angle_sequence->toFile(filename);
}

void SimWorld::writeBodyPositionFrame(int cc,int tri,FILE* file)
{
  int markCnt = (int)body->marker_to_body.size();
  for (int ii=0;ii<markCnt;++ii) {
     dVector4 pt;
     if (body->marker_to_body[ii].id>=0) {
          // Find the global coordinate of the relative position to which the marker is mapped
          dBodyGetRelPointPos(body->body_segments[body->marker_to_body[ii].id],
                              body->marker_to_body[ii].position[0],
                              body->marker_to_body[ii].position[1],
                              body->marker_to_body[ii].position[2],
                              pt);
          pt[3]=1;
        } else {
          pt[0]=pt[1]=pt[2]=0;
          pt[3]=-1;
        }

        for (int kk=0;kk<4;++kk) {
          fprintf(file,"%lf ",pt[kk]);
          fprintf(file,"\n");
        }
      }
}


void SimWorld::writeAngleFrame(int cc,int tri,FILE* file)
{
  for (int jj=0;jj<body->JOINT_COUNT;++jj) {
    for (int kk=0;kk<3;++kk) {
      fprintf(file,"%lf ",body->jointValue(jj,kk));
      fprintf(file,"\n");
    }
  }  
}

void SimWorld::writeJointFrame(int cc,int tri,FILE* file){

      for (int jj=0;jj<body->JOINT_COUNT;++jj) {
        for (int kk=0;kk<3;++kk) {
          fprintf(file,"%lf ",body->forceValue(jj,kk));
          fprintf(file,"\n");
          if (jj == 20 || jj == 21){
            total_torques += abs(body->forceValue(jj,kk));
          }
        }
      }
}



void SimWorld::makePlotEmit(){
    emit makePlot();
}

void SimWorld::writeFrameToFile(DataFrame *joint_frame, FILE* file) {

    for (int joint_index=0; joint_index< body->JOINT_COUNT; ++joint_index) {
      for (int axis_index=0; axis_index<3; axis_index++) {
        fprintf(file,"%lf ",joint_frame->getData(joint_index,axis_index));
        fprintf(file,"\n");
      }
    }
}



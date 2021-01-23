/****************************************************************************
 *                                                                          *
 * QtVR--Physics-base inverse kinematics and inverse dynamics               *
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
#ifndef __CAPBODY_H
#define __CAPBODY_H

#include <QObject>
#include <ode/ode.h>
#include <QList>
#include <vector>
#include <map>

class JointFrame;
class DataFrame;
class DSBoxWithParams;
using namespace std;

/**
  A marker or another body connects to a body
  segment.  Joint anchors are specified
  relative to the body.
  */
struct BodyLink
{
  int id; ///< Which body part does the marker link to?
  dVector3 position; ///< Where (in body-relative coords) does the marker connect.

  BodyLink() {id = -1; position[0]=0;position[1]=0;position[2]=0; }
};

/**
  The dynamic state of a body segment.
  */
struct BodyState
{
  dVector3 position;  ///< Position
  dQuaternion orientation_quaternion; ///< Orientation
  dVector3 linear_velocity; ///< Linear velocity
  dVector3 angular_velocity; ///< Angular velocity
};

/**
  Data, loaded from file, about a particular body part.
  */
struct PartInfo
{
  int classtype; ///< Sphere, caps, or box
  dVector3 dimensions;  ///< radius, length, or x,y,z
  DSBoxWithParams* spin_box[3]; ///< Widgets for setting body dimensions
  dQuaternion qq; ///< Orientation in default pose
  QList<BodyLink> links; ///< Links that need anchoring

  PartInfo() {classtype=-1;
              dimensions[0]=0;dimensions[1]=0;dimensions[2]=0;
              spin_box[0]=0;spin_box[1]=0;spin_box[2]=0;
              qq[0]=1;qq[1]=0;qq[2]=0;qq[3]=0; }
};

/**
  Joint info loaded from file includes the anchor
  points for the two linked bodies and the type of
  joint doing the connecting.

  We should also load joint limits and axes.
  */
struct JointInfo
{
  int classtype;
  BodyLink link[2];
};

/**
  An ODE humanoid character model.
  Collision geometry, dynamic bodies, and joints.
  The topology of the model is currently hardcoded.
  The dimensions and joint anchors are loaded from file.
  I was working at storing and loading topology from
  a database, but didn't finish.
  */
class CapBody : public QObject
{
    Q_OBJECT

public:
  enum BodyType {
    HEAD_BODY,    
    NECK_BODY,    
    UP_TORSO_BODY,
    R_COLLAR_BODY,
    RUP_ARM_BODY,
    RLO_ARM_BODY,
    R_HAND_BODY,
    L_COLLAR_BODY,
    LUP_ARM_BODY,
    LLO_ARM_BODY,
    L_HAND_BODY,
    LO_TORSO_BODY,
    WAIST_BODY,
    RUP_LEG_BODY,
    RLO_LEG_BODY,
    R_HEEL_BODY,
    R_TARSAL_BODY,
 //   R_TOE_BODY,
    LUP_LEG_BODY,
    LLO_LEG_BODY,
    L_HEEL_BODY,
    L_TARSAL_BODY,
 //   L_TOE_BODY,
 //     HOG_BODY,
    BODY_COUNT
  };

  enum GeomType {
    HEAD_GEOM,
    NECK_GEOM,
    UP_TORSO_GEOM,
    R_COLLAR_GEOM,
    RUP_ARM_GEOM,
    RLO_ARM_GEOM,
    R_HAND_GEOM,
    L_COLLAR_GEOM,
    LUP_ARM_GEOM,
    LLO_ARM_GEOM,
    L_HAND_GEOM,
    LO_TORSO_GEOM,
    WAIST_GEOM,
    RUP_LEG_GEOM,
    RLO_LEG_GEOM,
    R_HEEL_GEOM,
    R_TARSAL_GEOM,
 //   R_TOE_GEOM,
    LUP_LEG_GEOM,
    LLO_LEG_GEOM,
    L_HEEL_GEOM,
    L_TARSAL_GEOM,
//    L_TOE_GEOM,
 //     HOG_GEOM,
    GEOM_COUNT
  };




  enum JointType {
    CHIN_JOINT,
    THROAT_JOINT,
    R_COLLAR_JOINT,
    R_SHOULDER_JOINT,
    R_ELBOW_JOINT,
    R_WRIST_JOINT,
    L_COLLAR_JOINT,
    L_SHOULDER_JOINT,
    L_ELBOW_JOINT,
    L_WRIST_JOINT,
    SPINE_JOINT,
    WAIST_JOINT,
    R_HIP_JOINT,
    R_KNEE_JOINT,
    R_ANKLE_JOINT,
    R_FOOT_JOINT,
 //   R_TOE_JOINT,
    L_HIP_JOINT,
    L_KNEE_JOINT,
    L_ANKLE_JOINT,
    L_FOOT_JOINT,
//    L_TOE_JOINT,
    ROOT_LINMOTOR_JOINT,
    ROOT_ANGMOTOR_JOINT,
  //  HOG_JOINT,
    JOINT_COUNT
  };


  map <int, QString> jointNames = {{0,"CHIN"},
                                  {1,"THROAT"},
                                  {2,"R_COLLAR"},
                                  {3,"R_SHOULDER"},
                                  {4,"R_ELBOW"},
                                  {5,"R_WRIST"},
                                  {6,"L_COLLAR"},
                                  {7,"L_SHOULDER"},
                                  {8,"L_ELBOW"},
                                  {9,"L_WRIST"},
                                  {10,"SPINE"},
                                  {11,"WAIST"},
                                  {12,"R_HIP"},
                                  {13,"R_KNEE"},
                                  {14,"L_ANKLE"},
                                  {15,"L_FOOT"},
                                  {16,"L_HIP"},
                                  {17,"L_KNEE"},
                                  {18,"L_ANKLE"},
                                  {19,"L_FOOT"},
                                  {20,"ROOT_LINMOTOR"},
                                  {21,"ROOT_ANGMOTOR"},
                                 };

  // Each marker is assigned to a corresponding body segment.
  // The body segment ids are corresponding to enum BodyType

  map<string, int> bodyMarkMap = {{ "LBWT" ,12},
                                { "RBWT" ,12},
                                { "LFWT" ,12},
                                { "RFWT" ,12},
                                { "LFRM" ,10},
                                { "RWRA" ,6},
                                { "RFRM" ,5},
                                { "LWRB" ,10},
                                { "RELB" ,5},
                                { "LWRA" ,10},
                                { "RTHI" ,13},
                                { "LELB" ,9},
                                { "T10" ,11},
                                { "STRN" ,11},
                                { "LFIN" ,10},
                                { "RFIN" ,6},
                                { "RWRB" ,6},
                                { "LUPA" ,8},
                                { "LTHI" ,17},
                                { "RUPA" ,4},
                                { "RBAC" ,2},
                                { "RKNE" ,13},
                                { "LSHO" ,8},
                                { "C7" ,1},
                                { "LKNE" ,18},
                                { "RSHN" ,14},
                                { "RBHD" ,0},
                                { "LBHD" ,0},
                                { "LFHD" ,0},
                                { "LSHN" ,18},
                                { "RFHD" ,0},
                                { "RANK" ,15},
                                { "RMT5" ,16},
                                { "RTOE" ,16},
                                { "RSHO" ,4},
                                { "LANK" ,19},
                                { "LHEE" ,19},
                                { "CLAV" ,2},
                                { "RHEE" ,15},
                                { "LTOE" ,20},
                                { "LMT5" ,20}};


    map<string, vector<float>> posMap = {{ "LBWT" ,{0.022,-0.0833,0.056}},
                               { "RBWT" ,{0.0213,-0.0894,-0.0393}},
                               { "LFWT" ,{-0.014,0.0982,0.1248}},
                               { "RFWT" ,{-0.027,0.0736,-0.1431}},
                               { "LFRM" ,{-0.0123,-0.0168,0.1744}},
                               { "RWRA" ,{-0.0029,0.0332,0.0326}},
                               { "RFRM" ,{0.0046,-0.0717,0.006}},
                               { "LWRB" ,{-0.0033,-0.0645,0.0421}},
                               { "RELB" ,{0.0237,-0.0446,0.0924}},
                               { "LWRA" ,{0.013,0.0843,0.0361}},
                               { "RTHI" ,{0.083,0.0518,-0.0678}},
                               { "LELB" ,{-0.0403,0.0338,0.1016}},
                               { "T10" ,{0.011,0.015,0.1101}},
                               { "STRN" ,{0.0264,0.2078,0.0213}},
                               { "LFIN" ,{-0.0018,-0.0055,-0.0218}},
                               { "RFIN" ,{-0.0007,-0.0315,-0.0411}},
                               { "RWRB" ,{0.0042,-0.1186,0.0404}},
                               { "LUPA" ,{-0.0261,0.0525,-0.0576}},
                               { "LTHI" ,{-0.0536,0.0804,-0.1386}},
                               { "RUPA" ,{0.0429,-0.0003,-0.0378}},
                               { "RBAC" ,{0.008,-0.0237,-0.1095}},
                               { "RKNE" ,{0.0338,0.0971,-0.2792}},
                               { "LSHO" ,{0.0361,0.0855,0.1752}},
                               { "C7" ,{0.0354,0.0032,-0.0426}},
                               { "LKNE" ,{-0.0378,0.1008,0.1503}},
                               { "RSHN" ,{0.0351,0.057,0.054}},
                               { "RBHD" ,{0.0604,-0.0598,-0.0456}},
                               { "LBHD" ,{-0.0439,-0.0594,-0.0512}},
                               { "LFHD" ,{-0.0876,0.0461,0.0157}},
                               { "LSHN" ,{-0.0435,0.0425,-0.0916}},
                               { "RFHD" ,{0.0745,0.0729,0.0566}},
                               { "RANK" ,{0.0226,0.0069,0.0067}},
                               { "RMT5" ,{-0.0206,-0.0106,-0.0413}},
                               { "RTOE" ,{-0.0205,0.0504,0.0305}},
                               { "RSHO" ,{0.0269,0.0388,0.0813}},
                               { "LANK" ,{-0.0188,0.0069,0.0156}},
                               { "LHEE" ,{0.0309,-0.0298,-0.0039}},
                               { "CLAV" ,{0.0794,0.1447,-0.0236}},
                               { "RHEE" ,{-0.0275,-0.0495,-0.0219}},
                               { "LTOE" ,{0.001,0.0547,0.0122}},
                               { "LMT5" ,{0.0188,-0.0144,-0.0382}}};


  /// 'Long-term' storage of model state
  BodyState saved[BODY_COUNT];
  /// 'Short-term' (per frame) storage of model state
  BodyState temp_state[BODY_COUNT];

  dBodyID body_segments[BODY_COUNT];   ///< Body parts
  dGeomID geometries[GEOM_COUNT];    ///< Collision geometry
  dJointID joints[JOINT_COUNT]; ///< Joints
  dJointID limits[JOINT_COUNT]; ///< Joint limits for 3dof joints
  dJointID motors[JOINT_COUNT]; ///< Joint motors for all joints
  /// Feedback from the motors for getting the inverse dynamics
  dJointFeedback feedback[JOINT_COUNT];

  dWorldID world; ///< The ODE world, passed in from SimWorld
  dSpaceID space; ///< The collision space passed in from SimWorld



  /*
    We assume constant density (approximately that of water)
    for all body parts.  We could do much better by using
    real anthropometric data for each limb.
    */
 static dReal density; ///< Density of body parts
 static dReal joint_cfm;
 static dReal density_HOG;


  double joint_target[JOINT_COUNT][3]; ///< Target angle for each joint
  double joint_offset[JOINT_COUNT][3]; ///< Offset applied to the target (from the GUI)
  double control_limit[JOINT_COUNT][3]; ///< Max force a joint motor can apply to pursue the target

  std::vector<BodyLink> marker_to_body; ///< Relationship between markers and bodies.
  PartInfo part_info[BODY_COUNT];
  JointInfo joint_info[JOINT_COUNT];
  double stepsize; ///< Delta time for each step of dynamics (passed in from SimWorld)

  bool global_forces; ///< Should we compute/apply forces in body local or global coordinates

  /*
    These data are computed only for display purposes at
    the moment.  However, they could be used as part of
    a control strategy eventually.
    */
  dVector3 center_of_mass;  ///< Model's center of mass
  dVector3 senter_lin_vel; ///< Model's aggregate linear velocity
  dVector3 center_ang_vel; ///< Model's aggregate angular velocity

  /// When body dimensions are changed, what should be do with the anchors?
  bool keep_rel_anchors;

public:

    explicit CapBody(QObject *parent = 0);
    ~CapBody(void);

  void fillJointFrame(JointFrame* jf);
  void fillForceFrame(JointFrame* jf);
  void fillPositionFrame(DataFrame* bp);  // fill body position
  void setTargetFrame(DataFrame* jf);
  void setTargetFrame2(DataFrame* jf, DataFrame* bp);
  void applyForceFrame(DataFrame* jf);
  void applyForceFrame2(DataFrame* jf, DataFrame* bp);

  void setStepSize(double ss) { stepsize = ss; }
  void createBody(dWorldID world,dSpaceID space);

  void createSphere(BodyType id,GeomType g,dReal radius);
  void createCaps(BodyType id,GeomType g,dReal radius,dReal zLen, dReal density);
  void createBox(BodyType id,GeomType g,dReal xLen,dReal yLen,dReal zLen);
  //void createBox_HOG(BodyType id,GeomType g,dReal xLen,dReal yLen,dReal zLen);

  void createBall(JointType jj,BodyType id1,BodyType id2,
                  dReal px1,dReal py1,dReal pz1,
                  dReal px2,dReal py2,dReal pz2,
                  dReal ax1,dReal ay1,dReal az1,
                  dReal ax3,dReal ay3,dReal az3,
                  dReal lo1,dReal hi1,
                  dReal lo2,dReal hi2,
                  dReal lo3,dReal hi3);

  void createUni(JointType jj,BodyType id1,BodyType id2,
                  dReal px1,dReal py1,dReal pz1,
                  dReal px2,dReal py2,dReal pz2,
                  dReal rx1,dReal ry1,dReal rz1,
                  dReal rx2,dReal ry2,dReal rz2,
                  dReal lo1,dReal hi1,
                  dReal lo2,dReal hi2);
  void createHinge(JointType jj,BodyType id1,BodyType id2,
                   dReal px1,dReal py1,dReal pz1,
                   dReal px2,dReal py2,dReal pz2,
                   dReal hx1,dReal hy1,dReal hz1,
                   dReal lo1,dReal hi1);
  void bodyDims(BodyType id,dVector3 dims);


  void loadMarkToBodyMap(QString filename);
  void loadMarkRelPosMap(QString filename);
  void loadBodyProperties(QString filename);
  void loadJointAnchors(QString filename);

  void saveMarkToBodyMap(QString filename);
  void saveMarkRelPosMap(QString filename,bool bodyID=false);
  void saveBodyProperties(QString filename);
  void saveFullBodyProperties(QString filename);
  void saveJointProperties(QString filename);
  void saveJointAnchors(QString filename);

  double jointValue(int jj,int ax);
  double forceValue(int jj,int ax);
  double forceValue2(int jj,int ax);
  double jointMax(int jj,int ax);
  double jointMin(int jj,int ax);

  void setLink(int bb,int jj,dVector3 pos);
  void setBodySpin(int bb,int ax,DSBoxWithParams* spin);
  void setBody(int ii);
  void getBody(int ii);

  void findMassProperties();
  void saveTempState();
  void restoreTempState();

  void zeroAccumulators();
  void zeroControl();
  void restoreControl();

  void updateBodyMarkMapCMU(vector<string> labels);
  void updatePosMapCMU(vector<string> labels);

signals:
  void markMap(int mark,int bodyID);
  void markPoint(int mark,double px,double py,double pz);
  void targetChange(int jj,int ax,double val);

public slots:
  void loadBody(const char* markerMap, const char* markerRelPos,const char* bodyDim, const char* jointAnchor);
  void loadCBody(const char* markerMap, const char* markerRelPos,const char* bodyDim, const char* jointAnchor);
  void reloadBodySetting();
  void saveBody();

  void saveState();
  void restoreState();

  void saveModelProperties();

  void copyToSim();
  void copyFromSim();

  void updateControl();

  void changeMarkLinks(int numMarkers);

  void setJointTarget(int jj,int ax, double val);
  void setJointOffset(int jj,int ax, double val);
  void setJointForce(int jj,int ax,double val);
  void applyJointForce(int jj,int ax,double val);

  void setBodyDim(int bb,int ax,double val);
  void bigHand(bool big);

  void writeModel();
  void writeMarkers();



protected:



};

#endif

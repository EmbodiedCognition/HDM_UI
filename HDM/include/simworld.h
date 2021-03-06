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
#ifndef SIMWORLD_H
#define SIMWORLD_H

/// The maximum number of ground contacts we'll
/// track ground forces from.
/// Generally, we only expect three per foot.
#define MAX_GROUND_FEEDBACK 40

#include <QObject>
#include <ode/ode.h>


//#include "swingdata.h"
//#include "livemarkerdata.h"
#if defined( BOARD_DATA )
#include "boardmarkerdata.h"
#elif defined( POKE_DATA )
#include "pokemarkerdata.h"
#else
#include "markerdata.h"
#endif

class Sequence;
class CapBody;
class JointFrame;
class DataFrame;

/**
  A simple object holding a line segment and a color.
  GLine is used for providing graphical feedback about
  ground forces and torques.
  */
struct GLine {
  dVector3 p1;
  dVector3 p2;
  dVector3 col;
};

/**
  A wrapper around the physics engine and associated
  objects including marker, angle, and torque data.
  */
class SimWorld : public QObject
{
    Q_OBJECT
public:
    explicit SimWorld(QObject *parent = 0);
    virtual ~SimWorld();

  //SwingData* getMarkerData() {return marker_data;}
  //LiveMarkerData* getMarkerData() {return marker_data;}
#if defined( BOARD_DATA )
  BoardMarkerData* getMarkerData() {return marker_data;}
#elif defined( POKE_DATA )
  PokeMarkerData* getMarkerData() {return marker_data;}
#else
  MarkerData* getMarkerData() {return marker_data;}
#endif
  dSpaceID getSpace() { return space; }
  dSpaceID getMarkSpace() { return marker_space; }
  dSpaceID getTargetSpace() {return target_space;}
  CapBody* getBody() { return body; }

  static void collideGeoms(void* data,dGeomID object_1_ID,dGeomID object_2_ID);

  void updateSeqFrame();
  void applyTorquesToBody(DataFrame *joint_frame);
  void writeFrameToFile(DataFrame *joint_angle_frame, FILE* file);

#if defined( BOARD_DATA )
  void updateBoards();
#endif

  void setMotion(const char* file);
  void setCMotion(const char* markerfile, const char* markerMap, const char* markerRelPos,const char* bodyDim, const char* jointAnchor);
  void setDMotion();
  void writeBodyPositionFrame(int cc,int tri,FILE* file);
  void writeAngleFrame(int cc,int tri,FILE* file);
  void writeJointFrame(int cc,int tri,FILE* file);


  bool isPaused() { return paused;}

signals:

  /// The GUI keys off this signal to connect or
  /// disconnect the joints between the markers
  /// and the character model.  We should make
  /// this less convoluted.
  void useMarkers(bool);
  void makePlot();
  //void usingMarkers(bool);

public slots:

  void setStepSize(double ss);
  void step();  ///< Advance the physical simulation forward in time
  void pauseSim(bool);
  void setSingleStep();

  void setGroundFriction(double friction);    // ground_friction
  void setTerrainSoftness(double terrain);    // ground_squish
  void setGroundERP(double erp);  // ground_ERP
  void setGroundCFM(double cfm);  // ground_CFM
  void setGroundSurfaceLayer(double sfl);   // ground_surfaceLayer

  void setTerrainZ(double z_value); ///< Set the ground plane height

  /// Set the play-back state:
  /// Following InverseKinematics, InverseDynamics, or ForwardDynamics
  void follow(int type);

  void setSelfCollide(bool hit_self);

  /// Open the specified file and write out recorded kinematics
  void anglesToFile(QString filename);

public:
  MarkerData* marker_data;   ///< MoCap Marker data (from Phasespace C3D file)
  int follow_sequence_source_state;   ///< Are we following markers, joint angles, or torques?
  double total_torques;

  const char* fileDialogPath = "/Users/lijialiu/Documents/HDM_UI/HDM/data/motions";

  const char* defaultMarkerFile = "/Users/lijialiu/Documents/HDM_UI/HDM/data/motions/dmotions/walk.c3d";
  const char* defaultMarkerMapFile = "/Users/lijialiu/Documents/HDM_UI/HDM/data/motions/dmotions/bodysettings/default_markMap.txt";
  const char* defaultMarkerRelPosFile = "/Users/lijialiu/Documents/HDM_UI/HDM/data/motions/dmotions/bodysettings/default_posMap.txt";
  const char* defaultBodyDimFile = "/Users/lijialiu/Documents/HDM_UI/HDM/data/motions/dmotions/bodysettings/default_dimMap.txt";
  const char* defaultJointAnchorFile = "/Users/lijialiu/Documents/HDM_UI/HDM/data/motions/dmotions/bodysettings/default_anchorMap.txt";

  const char* markerFile = "";
  const char* markerMapFile = "";
  const char* markerRelPosFile = "";
  const char* bodyDimFile = "";
  const char* jointAnchorFile = "";
  string drawObjects = "";
  int objectFrames = 0;
  bool usingDefaultSettings;

  double ground_squish = .00001; ///< How 'soft' (CFM) are ground contacts
  double ground_friction = 1; ///< A strong (Fmax) is ground friction
  double ground_ERP = 0.5;
  double ground_CFM = 0.0001;
  double ground_surfaceLayer = .005;




protected:

  dWorldID world; ///< Container for ODE dynamics
  dSpaceID space; ///< Container for ODE collision geometry

  dGeomID ground_plane; ///< Ground plane
  dGeomID mouse_ray;    ///< For ray-picking
#if defined( BOARD_DATA )
  dGeomID board0;
  dGeomID board1;
#endif
  dJointGroupID contact_group; ///< Holds contact joints

  bool paused;      ///< Is the simulation paused
  bool single_step;  ///< Should the simulation advance by a single step

  double stepsize;  ///< How much time for a single step

  CapBody* body;  ///< The character model


  /*
    In a fit of laziness, I took a quick and dirty route
    and simply copied MarkerData, rather than creating
    a proper parent class and subclassing it.
    Different incarnations of "MarkerData" expect different
    file formats and may contain other data such as ground
    forces or EMG data.
    */
  //SwingData* markData;
  //LiveMarkerData* markData;
#if defined( BOARD_DATA )
  BoardMarkerData* marker_data;
#elif defined( POKE_DATA )
  PokeMarkerData* marker_data;
#else

#endif


  dSpaceID target_space;  ///< When analysis includes target geometry, they go here.
  dSpaceID marker_space;    ///< Spheres representing the markers go here

  bool self_collide;  ///< Should the body collide with itself
  int sequence_frame;      ///< What frame are we on as we move through an angle or torque sequence
  FILE* main_file;    ///< Kludge file handle for writing out whatever data is interesting at the moment
  FILE* angle_file;   ///< joint angles at second path
  const char * motiondata;

public:

  Sequence* angle_sequence;  ///< The stored sequence of joint angles (kinematics)
  Sequence* angle_sequence2; ///< The sequence of joint angles at second path
  Sequence* torque_sequence; ///< The stored sequence of torques/forces (dynamics)
  Sequence* torque_sequence2;
  Sequence* position_sequence; /// < The position of new HOG

  int number_active_ground_contacts; ///< How many contacts were made with the ground
  dJointFeedback ground_feedback[MAX_GROUND_FEEDBACK]; ///< Feedback structures for extracting ground forces
  dVector3 contact_point[MAX_GROUND_FEEDBACK]; ///< Contact points between body and ground

  /// Lines showing whatever information happened to be needed:
  /// Ground forces, residual torques, center of mass, aggregate momentum, etc.
  QList<GLine> line_list;
  QList<int> left_foot_feedback;  ///< Lines specifically showing ground forces from left foot
  QList<int> right_foot_feedback; ///< Ground forces from right foot.


  void makePlotEmit();
};


#endif // SIMWORLD_H

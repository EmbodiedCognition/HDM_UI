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
#include "testscript.h"

#include "simworld.h"
#include "CapBody.h"
#include "mainwindow.h"
#include <QFile>
#include <QTextStream>

TestScript::TestScript(MainWindow* win,QObject *parent) :
  ScriptBase(win,parent)
{
  testState = 0;
  runScript = false;

  test_angle_round1 = fopen("/Users/lijialiu/Documents/QtVR/data/results/test_angle_round1.txt","w");
  test_angle_round2 = fopen("/Users/lijialiu/Documents/QtVR/data/results/test_angle_round2.txt","w");
  test_angle_round3 = fopen("/Users/lijialiu/Documents/QtVR/data/results/test_angle_round3.txt","w");
  test_torque_round1 = fopen("/Users/lijialiu/Documents/QtVR/data/results/test_torque_round1.txt","w");
  test_torque_round2 = fopen("/Users/lijialiu/Documents/QtVR/data/results/test_torque_round2.txt","w");
  test_torque_round3 = fopen("/Users/lijialiu/Documents/QtVR/data/results/test_torque_round3.txt","w");
  test_position_round1 = fopen("/Users/lijialiu/Documents/QtVR/data/results/test_position_round1.txt","w");
  test_position_round2 = fopen("/Users/lijialiu/Documents/QtVR/data/results/test_position_round2.txt","w");
  test_position_round3 = fopen("/Users/lijialiu/Documents/QtVR/data/results/test_position_round3.txt","w");
}


//virtual
void TestScript::startScript()
{
    test_angle_round1 = fopen("/Users/lijialiu/Documents/QtVR/data/results/test_angle_round1.txt","w");
    test_angle_round2 = fopen("/Users/lijialiu/Documents/QtVR/data/results/test_angle_round2.txt","w");
    test_angle_round3 = fopen("/Users/lijialiu/Documents/QtVR/data/results/test_angle_round3.txt","w");
    test_torque_round1 = fopen("/Users/lijialiu/Documents/QtVR/data/results/test_torque_round1.txt","w");
    test_torque_round2 = fopen("/Users/lijialiu/Documents/QtVR/data/results/test_torque_round2.txt","w");
    test_torque_round3 = fopen("/Users/lijialiu/Documents/QtVR/data/results/test_torque_round3.txt","w");
    test_position_round1 = fopen("/Users/lijialiu/Documents/QtVR/data/results/test_position_round1.txt","w");
    test_position_round2 = fopen("/Users/lijialiu/Documents/QtVR/data/results/test_position_round2.txt","w");
    test_position_round3 = fopen("/Users/lijialiu/Documents/QtVR/data/results/test_position_round3.txt","w");


      std::cout << "[testscript] start test script..." << std::endl;
      SimWorld* sw = mainWin->getWorld();
      CapBody* cb = sw->getBody();
      MarkerData* md = sw->getMarkerData();
      md->setFrame(0);

      // Set the marker file to a target frame.
      mainWin->setDataFrame(20000);
      mainWin->playPauseAll(false);
      mainWin->playPauseSim(true);
      mainWin->lightForces();
      mainWin->clearData();
      mainWin->useMarkers(true);
      mainWin->useGlobalForces(false);

      testState = 1;
      eFrame = 0;
      runScript = true;
      wait_frame = md->data.data.frames /md->frames_per_step + 100;
}

//virtual
void TestScript::updateScript()
{

  eFrame+=1;

  switch (testState) {
    case 1:
    if (eFrame>=100) {
      std::cout << "[testscript] Round 1: inverse kinematics" << std::endl;
      testState = 2;
      eFrame=0;
      mainWin->setDataFrame(20000);
      mainWin->lightForces();
      mainWin->clearData();
      mainWin->useMarkers(true);
      mainWin->playPauseData(true);
      mainWin->playPauseSim(true);
      mainWin->saveModel();
      mainWin->restoreModel();
    }
    break;
  case 2:

      mainWin->writeAngleFrame(-1, 0, test_angle_round1);
      mainWin->writeJointFrame(-1, 0, test_torque_round1);
      mainWin->writePositionFrame(-1, 0, test_position_round1);


    if (eFrame>=wait_frame) {
      std::cout << "[testscript] Round 2: inverse dynamics" << std::endl;
      testState = 3;
      eFrame=0;
      mainWin->setDataFrame(20000);
      mainWin->strongForces();
      mainWin->useAltAngles(true);
      mainWin->playPauseData(false);
      mainWin->playPauseSim(true);
      mainWin->restoreModel();
    }
    break;
  case 3:
    mainWin->writeAngleFrame(-1, 0, test_angle_round2);
    mainWin->writeJointFrame(-1, 0, test_torque_round2);
    mainWin->writePositionFrame(-1, 0, test_position_round2);

    if (eFrame>=wait_frame) {
      std::cout << "[testscript] Round 3: forward dynamics" << std::endl;
      testState = 4;
      eFrame = 0;
      mainWin->setDataFrame(20000);
      //mainWin->zeroForces();
      mainWin->useTorques(true);
      mainWin->playPauseData(false);
      mainWin->playPauseSim(true);
      mainWin->restoreModel();
    }
    break;
  case 4:
    mainWin->writeAngleFrame(-1, 0, test_angle_round3);
    mainWin->writeJointFrame(-1, 0, test_torque_round3);
    mainWin->writePositionFrame(-1, 0, test_position_round3);
    if (eFrame>=wait_frame) {
      testState = 0;
      eFrame = 0;
      mainWin->playPauseData(false);
      mainWin->playPauseSim(false);
      }
    break;
  default:
      eFrame=0;
      endScript();
    break;
  }
}

//virtual
void TestScript::endScript()
{
    fclose(test_angle_round1);
    fclose(test_angle_round2);
    fclose(test_angle_round3);
    fclose(test_torque_round1);
    fclose(test_torque_round2);
    fclose(test_torque_round3);
    fclose(test_position_round1);
    fclose(test_position_round2);
    fclose(test_position_round3);

    mainWin->getWorld()->makePlotEmit();
    runScript = false;
    std::cout << "[testscript] Test script done." << std::endl;
}

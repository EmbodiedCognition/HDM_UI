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
#ifndef TESTSCRIPT_H
#define TESTSCRIPT_H

#include "scriptbase.h"

class MainWindow;

class TestScript : public ScriptBase
{
  Q_OBJECT
public:

  explicit TestScript(MainWindow* win,QObject *parent = 0);
  int testState;
  int eFrame;
  int wait_frame;

  
signals:

  
public slots:   

  virtual void startScript();

  virtual void updateScript();

  virtual void endScript();
protected:


  FILE* test_angle_round1;
  FILE* test_angle_round2;
  FILE* test_angle_round3;
  FILE* test_torque_round1;
  FILE* test_torque_round2;
  FILE* test_torque_round3;
  FILE* test_position_round1;
  FILE* test_position_round2;
  FILE* test_position_round3;
};

#endif // TESTSCRIPT_H

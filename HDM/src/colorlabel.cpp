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
#include "colorlabel.h"
#include <QMouseEvent>

ColorLabel::ColorLabel(QWidget *parent) :
    QLabel(parent)
{
  eState = WaitState;
}


void 	ColorLabel::enterEvent ( QEvent * event )
{
  eState = EnterState;
  event->accept();
}

void 	ColorLabel::leaveEvent ( QEvent * event )
{
  eState = WaitState;
  event->accept();
}

void 	ColorLabel::mousePressEvent ( QMouseEvent * event )
{
  eState = ClickState;
  event->accept();
}

void 	ColorLabel::mouseReleaseEvent ( QMouseEvent * event )
{
  if (eState==ClickState) {
    eState = EnterState;
    emit clicked();
  }
  event->accept();
}


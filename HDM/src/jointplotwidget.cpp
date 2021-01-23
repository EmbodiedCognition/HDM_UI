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
#include "jointplotwidget.h"
#include "ui_jointplotwidget.h"



JointPlotWidget::JointPlotWidget(QString label,int jj, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::JointPlotWidget),
    jVal(jj)
{
    ui->setupUi(this);
    ui->checkBox->setText(label);
    //ui->label->setText("Plot");
    connect(ui->checkBox,SIGNAL(toggled(bool)),this,SLOT(changeStatus(bool)));

}

JointPlotWidget::~JointPlotWidget()
{
    delete ui;
}

void JointPlotWidget::changeStatus(bool toggle){
    ui->checkBox->setChecked(toggle);
    emit checkStatusChanged(toggle, jVal);
}

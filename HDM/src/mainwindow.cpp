
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


#include <string>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "simworld.h"
#include "CapBody.h"
#include "dsboxwithparams.h"
#include "testscript.h"
#include "experimentScript.h"

/**
 * @brief MainWindow::MainWindow Initialize the main window and everything else
 * @param parent
 */
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
   Q_INIT_RESOURCE(resources);
  // Initialize the interface
  ui->setupUi(this);
  ui->glWidget->addAction(ui->actionFullscreen);
  ui->glWidget->addAction(ui->actionExit);

  connect(ui->actionExit,SIGNAL(triggered()),this,SLOT(close()));
  connect(ui->actionFullscreen,SIGNAL(triggered()),this,SLOT(toggleFullscreenSlot()));

  // The test script runs a simple experiment
  experimentScript = new TestScript(this,this);

  //experimentScript = new ExperimentScript(this, this);

  // Add a cosmetic line to the splitter handle
  // so that it's easier to grab with the mouse
  QSplitterHandle *handle = ui->splitter->handle(1);
  QVBoxLayout *layout = new QVBoxLayout(handle);
  layout->setSpacing(0);
  layout->setMargin(0);
  QFrame *line = new QFrame(handle);
  line->setFrameShape(QFrame::VLine);
  line->setFrameShadow(QFrame::Sunken);
  layout->addWidget(line);

  // In a future revision, we'll move the SimWorld
  // to a more intelligent place.  It doesn't
  // belong as a child to the graphics widget.
  SimWorld* world = ui->glWidget->getWorld();
  world->usingDefaultSettings = true;
  CapBody* capBody = world->getBody();
  MarkerData* md = world->getMarkerData();
  int markCnt = md->marker_count;
  ui->markerCountLineEdit->setText(QString::number(markCnt));
  ui->frameCountLineEdit->setText(QString::number(md->size()));
  ui->markerFileLineEdit->setText("/Users/lijialiu/Documents/HDM_UI/HDM/data/walk.c3d");
  ui->markerFrameStartBox->setValue(0);
  setDataRange(md->size());

  // Setting Tabs
  ui->controlTabWidget->setTabText(0, "Basic");
  //Graphs Tab
  QScrollArea* sa = new QScrollArea;
  QWidget* wid = new QWidget;
  layout = new QVBoxLayout;
  layout->setContentsMargins(0,0,0,0);
  QHBoxLayout* innerLayout = new QHBoxLayout;
  QPushButton* saveImage = new QPushButton("Save image");
  connect(saveImage,SIGNAL(clicked(bool)),this,SLOT(saveImage()));
  innerLayout->addWidget(saveImage);
  layout->addLayout(innerLayout);

  QGroupBox *groupBox = new QGroupBox("");
  QRadioButton* jointAngle = new QRadioButton("Joint anlge");
  QRadioButton* jointTorque = new QRadioButton("Joint torques");
  jointAngle->setChecked(true);
  QHBoxLayout *vbox = new QHBoxLayout;
  vbox->addWidget(jointAngle);
  vbox->addWidget(jointTorque);
  //vbox->addStretch(1);
  groupBox->setLayout(vbox);
  innerLayout = new QHBoxLayout;
  innerLayout->addWidget(groupBox);
  connect(jointAngle,SIGNAL(toggled(bool)),this,SLOT(plotJointAngle(bool)));
  connect(jointTorque,SIGNAL(toggled(bool)),this,SLOT(plotJointTorque(bool)));
  layout->addLayout(innerLayout);


  groupBox = new QGroupBox("");
  QRadioButton* xAxis = new QRadioButton("x axis");
  QRadioButton* yAxis = new QRadioButton("y axis");
  QRadioButton* zAxis = new QRadioButton("z axis");
  xAxis->setChecked(true);
  vbox = new QHBoxLayout;
  vbox->addWidget(xAxis);
  vbox->addWidget(yAxis);
  vbox->addWidget(zAxis);
  //vbox->addStretch(1);
  groupBox->setLayout(vbox);
  innerLayout = new QHBoxLayout;
  innerLayout->addWidget(groupBox);
  connect(xAxis,SIGNAL(toggled(bool)),this,SLOT(plotXAxis(bool)));
  connect(yAxis,SIGNAL(toggled(bool)),this,SLOT(plotYAxis(bool)));
  connect(zAxis,SIGNAL(toggled(bool)),this,SLOT(plotZAxis(bool)));
  layout->addLayout(innerLayout);

  populateJointPlotTab(capBody,layout);
  wid->setLayout(layout);
  sa->setWidget(wid);
  ui->controlTabWidget->addTab(sa,"Graphs");

  //Markers Tab
  sa = new QScrollArea;
  wid = new QWidget;
  layout = new QVBoxLayout;
  innerLayout = new QHBoxLayout;
  QPushButton* connectButton = new QPushButton("Connect");
  QPushButton* releaseButton = new QPushButton("Release");
  QPushButton* updateButton = new QPushButton("Update Anchors");
  innerLayout->addWidget(connectButton);
  innerLayout->addWidget(releaseButton);
  innerLayout->addWidget(updateButton);
  connect(connectButton,SIGNAL(clicked()),this,SLOT(connectMarkers()));
  connect(releaseButton,SIGNAL(clicked()),this,SLOT(releaseMarkers()));
  connect(updateButton,SIGNAL(clicked()),this,SLOT(updateMarkerAnchors()));
  layout->addLayout(innerLayout);
  markerWidgetArray.resize(markCnt);
  for (int ii=0;ii<markCnt;++ii) {
    markerWidgetArray[ii] = new MarkerWidget(ii,0);
    layout->addWidget(markerWidgetArray[ii]);
  }
  wid->setLayout(layout);
  sa->setWidget(wid);
  ui->controlTabWidget->addTab(sa,"Markers");


  // Joints tab
  sa = new QScrollArea;
  wid = new QWidget;
  layout = new QVBoxLayout;
  layout->setContentsMargins(0,0,0,0);

  // A couple buttons at the top of the joint tab make it possible
  // to rapidly change all the force limits
  innerLayout = new QHBoxLayout;
  QPushButton* zeroButton = new QPushButton("Zero");
  QPushButton* lightButton = new QPushButton("Light");
  QPushButton* resetButton = new QPushButton("Strong");
  innerLayout->addWidget(zeroButton);
  innerLayout->addWidget(lightButton);
  innerLayout->addWidget(resetButton);
  layout->addLayout(innerLayout);
  connect(zeroButton,SIGNAL(clicked()),this,SLOT(zeroForces()));
  connect(lightButton,SIGNAL(clicked()),this,SLOT(lightForces()));
  connect(resetButton,SIGNAL(clicked()),this,SLOT(strongForces()));

  // Fill the tab with hard-coded data about the model...
  populateJointTab(capBody,layout);
  wid->setLayout(layout);
  sa->setWidget(wid);
  ui->controlTabWidget->addTab(sa,"Joints");


  // Body Dimensions Tab
  sa = new QScrollArea;
  wid = new QWidget;
  layout = new QVBoxLayout;
  layout->setContentsMargins(0,0,0,0);
  QCheckBox* keepBodyRel = new QCheckBox("Body Rel");
  layout->addWidget(keepBodyRel);

  // Fill the tab with model-specific widgets
  populateBodyTab(capBody,layout);
  wid->setLayout(layout);
  sa->setWidget(wid);
  ui->controlTabWidget->addTab(sa,"Model dimensions");



  QIcon *ico = new QIcon();
  ico->addPixmap(QPixmap(":/icons/data/icons/media-playback-pause-3.png"),QIcon::Normal,QIcon::On);
  ico->addPixmap(QPixmap(":/icons/data/icons/media-playback-start-3.png"),QIcon::Normal,QIcon::Off);
  ui->playPauseSimButton->setIcon(*ico);
  ui->playPauseDataButton->setIcon(*ico);
  ui->playAllButton->setIcon(*ico);
  ui->playPauseSimButton->setCheckable(true);
  ui->playPauseDataButton->setCheckable(true);
  ui->playAllButton->setCheckable(true);


  ui->torqueRadio->setVisible(false);

  // Hook up the interface elements to their respecitve functionality
  connect(ui->saveButton,SIGNAL(clicked()),capBody,SLOT(saveBody()));
  connect(ui->plotGraphsButton,SIGNAL(clicked()),this,SLOT(makingPlot()));
  connect(ui->runTestPushButton,SIGNAL(clicked()),this,SLOT(experimentSlot()));
  connect(ui->stopTestPushButton,SIGNAL(clicked()),this,SLOT(experimentStopSlot()));

  // When a the CapBody loads the marker map, tell the interface
  // how and where the markers are connected.
  connect(capBody,SIGNAL(markMap(int,int)),this,SLOT(setMarkMap(int,int)));
  connect(capBody,SIGNAL(markPoint(int,double,double,double)),
          this,SLOT(setMarkPoint(int,double,double,double)));

  // *****
  // (Each MarkerWidget informs the capBody when the interface changes).
  for (int ii=0;ii<markCnt;++ii) {
    connect(markerWidgetArray[ii],SIGNAL(markBodySet(int,int)),md,SLOT(changeBodyConnect(int,int)));
    connect(markerWidgetArray[ii],SIGNAL(markConnect(int,bool)),md,SLOT(changeBodyLink(int,bool)));
    connect(markerWidgetArray[ii],SIGNAL(markPosSet(int,double,double,double)),
            md,SLOT(changeLinkPos(int,double,double,double)));
    connect(markerWidgetArray[ii],SIGNAL(markGrab(int)),this, SLOT(grabMarkPos(int)));
  }
  connect(ui->clearPlotButton,SIGNAL(clicked()),this,SLOT(clearData()));
  connect(ui->glWidget->getWorld(),SIGNAL(useMarkers(bool)),this,SLOT(usingMarkers(bool)));
  connect(ui->glWidget->getWorld(),SIGNAL(makePlot()),this,SLOT(makingPlot()));
  connect(ui->frictionSpinBox,SIGNAL(valueChanged(double)),world,SLOT(setGroundFriction(double)));
  connect(ui->terrainSpinBox,SIGNAL(valueChanged(double)),world,SLOT(setTerrainSoftness(double)));
  connect(ui->zBox,SIGNAL(valueChanged(double)),ui->glWidget->getWorld(),SLOT(setTerrainZ(double)));
  connect(ui->forceLinesCheckBox,SIGNAL(clicked(bool)),ui->glWidget,SLOT(setDrawLines(bool)));
  connect(ui->camFollowCheckBox,SIGNAL(clicked(bool)),ui->glWidget,SLOT(setFollowCamera(bool)));
  connect(ui->timeSlider,SIGNAL(valueChanged(int)),world->getMarkerData(),SLOT(setFrame(int)));
  connect(ui->glWidget->getWorld()->getMarkerData(),SIGNAL(frameChanged(int)),ui->timeSlider,SLOT(setValue(int)));
  connect(ui->bodyAlpha,SIGNAL(valueChanged(double)),ui->glWidget,SLOT(setBodyAlpha(double)));
  connect(ui->showMarkBox,SIGNAL(toggled(bool)),ui->glWidget,SLOT(setShowMarkers(bool)));
  connect(ui->selfCollideBox,SIGNAL(toggled(bool)),world,SLOT(setSelfCollide(bool)));
  connect(ui->saveStateButton,SIGNAL(clicked()),this,SLOT(saveModel()));
  connect(ui->restoreButton,SIGNAL(clicked()),this,SLOT(restoreModel()));
  connect(ui->markerRadio,SIGNAL(toggled(bool)),this,SLOT(useMarkers(bool)));
  connect(ui->angleRadio,SIGNAL(toggled(bool)),this,SLOT(useAngles(bool)));
  connect(ui->altRadio,SIGNAL(toggled(bool)),this,SLOT(useAltAngles(bool)));
  connect(ui->playAllButton,SIGNAL(clicked(bool)),this,SLOT(playPauseAll(bool)));
  connect(ui->playPauseDataButton,SIGNAL(clicked(bool)),this,SLOT(playPauseData(bool)));
  connect(ui->playPauseSimButton,SIGNAL(clicked(bool)),this,SLOT(playPauseSim(bool)));
  connect(ui->stepAllButton,SIGNAL(clicked()),this,SLOT(stepAll()));
  connect(ui->stepDataButton,SIGNAL(clicked()),this,SLOT(stepData()));
  connect(ui->stepSimButton,SIGNAL(clicked()),this,SLOT(stepSim()));
  connect(ui->selectFileToolButton,SIGNAL(clicked()),this,SLOT(markerFileDialog()));
  connect(ui->dataStepBox,SIGNAL(valueChanged(int)),this,SLOT(setDataStep(int)));
  connect(ui->dataFrameBox,SIGNAL(valueChanged(int)),this,SLOT(setDataFrame(int)));
  connect(ui->timeSlider,SIGNAL(valueChanged(int)),ui->dataFrameBox,SLOT(setValue(int)));
  connect(ui->cselectFileToolButton,SIGNAL(clicked()),this,SLOT(cmarkerFileDialog()));
  connect(ui->cselectMarkerMapToolButton,SIGNAL(clicked()),this,SLOT(cmarkerMarkerMapDialog()));
  connect(ui->cselectRelPosToolButton,SIGNAL(clicked()),this,SLOT(cmarkerRelPosDialog()));
  connect(ui->cselectModelDimToolButton,SIGNAL(clicked()),this,SLOT(cModelDimsDialog()));
  connect(ui->cselectjointAnchorButton,SIGNAL(clicked()),this,SLOT(cjointAnchorDialog()));
  connect(ui->cselectDrawObjectsButton,SIGNAL(clicked()),this,SLOT(cdrawObjectsDialog()));
  connect(ui->customPushButton,SIGNAL(clicked()),this,SLOT(customSetting()));
  connect(ui->defaultPushButton,SIGNAL(clicked()),this,SLOT(defaultSetting()));
  // *****
  // Need to dynamically change this
  ui->timeSlider->setRange(0,world->getMarkerData()->size()-1);
  connect(ui->globalBox,SIGNAL(toggled(bool)),this,SLOT(useGlobalForces(bool)));


  // Start the timer for updating the data, sim, and graphics
  updateTimer.setSingleShot(false);
  connect(&updateTimer,SIGNAL(timeout()),this,SLOT(updateLoop()));

  connect(ui->frameTimeBox,SIGNAL(valueChanged(double)),this,SLOT(setFrameTime(double)));
  ui->frameTimeBox->setValue(1/60.0);
  ui->dataStepBox->setValue(2);
  ui->tabWidget->setCurrentIndex(0);

  capBody->copyToSim();
  useMarkers(true);
  saveModel();
  updateButtonStatus = false;

  //Setting plots
   ui->customPlot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectAxes |
                                    QCP::iSelectLegend | QCP::iSelectPlottables);
    ui->customPlot->axisRect()->setupFullAxesBox();
    ui->customPlot->plotLayout()->insertRow(0);
    QCPTextElement *title = new QCPTextElement(ui->customPlot, "Joints Angles/Torques", QFont("sans", 17, QFont::Bold));
    ui->customPlot->plotLayout()->addElement(0, 0, title);
    connect(title, SIGNAL(doubleClicked(QMouseEvent*)), this, SLOT(titleDoubleClick(QMouseEvent*)));

    // connect slot that ties some axis selections together (especially opposite axes):
     connect(ui->customPlot, SIGNAL(selectionChangedByUser()), this, SLOT(selectionChanged()));
     // connect slots that takes care that when an axis is selected, only that direction can be dragged and zoomed:
     connect(ui->customPlot, SIGNAL(mousePress(QMouseEvent*)), this, SLOT(mousePress()));
     connect(ui->customPlot, SIGNAL(mouseWheel(QWheelEvent*)), this, SLOT(mouseWheel()));

     // make bottom and left axes transfer their ranges to top and right axes:
     connect(ui->customPlot->xAxis, SIGNAL(rangeChanged(QCPRange)), ui->customPlot->xAxis2, SLOT(setRange(QCPRange)));
     connect(ui->customPlot->yAxis, SIGNAL(rangeChanged(QCPRange)), ui->customPlot->yAxis2, SLOT(setRange(QCPRange)));

     // connect some interaction slots:
     connect(ui->customPlot, SIGNAL(axisDoubleClick(QCPAxis*,QCPAxis::SelectablePart,QMouseEvent*)), this, SLOT(axisLabelDoubleClick(QCPAxis*,QCPAxis::SelectablePart)));
     connect(ui->customPlot, SIGNAL(legendDoubleClick(QCPLegend*,QCPAbstractLegendItem*,QMouseEvent*)), this, SLOT(legendDoubleClick(QCPLegend*,QCPAbstractLegendItem*)));

     // connect slot that shows a message in the status bar when a graph is clicked:
     connect(ui->customPlot, SIGNAL(plottableClick(QCPAbstractPlottable*,int,QMouseEvent*)), this, SLOT(graphClicked(QCPAbstractPlottable*,int)));

     // setup policy and connect slot for context menu popup:
     ui->customPlot->setContextMenuPolicy(Qt::CustomContextMenu);
     connect(ui->customPlot, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(contextMenuRequest(QPoint)));

  initialPlotJoints();
}

MainWindow::~MainWindow()
{
  delete ui;
}



void MainWindow::makeJointWidget(QString label,int joint,
                                 int axis,CapBody* cb,
                                 QVBoxLayout* lay)
{
  JointWidget* jw = new JointWidget(label,joint,axis,0);
  connect(jw,SIGNAL(valueChanged(int,int,double)),
          cb,SLOT(setJointOffset(int,int,double)));
  connect(jw,SIGNAL(forceChanged(int,int,double)),
          cb,SLOT(setJointForce(int,int,double)));
  connect(cb,SIGNAL(targetChange(int,int,double)),
          jw,SLOT(setValue(int,int,double)));

  lay->addWidget(jw);
  jointWidgets.push_back(jw);
}


/**
 * @brief MainWindow::populateJointTab Fill the "Joints" tab with controls
 * @param cb Pointer to the model
 * @param lay Layout for the Tab widget
 *
 *  This function creates all of the JointWidgets that allow
 * the user to control the independent degrees of freedom
 * of the character model.
 *
 *  In the future, the DoF labels and associated degrees of freedom
 * should be loaded from a file or database so that you don't have
 * to remember to change this function everytime you make a change
 * to the model.
 */
void MainWindow::populateJointTab(CapBody* capBody,
                                  QVBoxLayout* layout)
{
  makeJointWidget("RootX",CapBody::ROOT_LINMOTOR_JOINT,0,capBody,layout);
  makeJointWidget("RootY",CapBody::ROOT_LINMOTOR_JOINT,1,capBody,layout);
  //makeJointWidget("RootZ",CapBody::ROOT_LINMOTOR_JOINT,2,capBody,layout);

 makeJointWidget("Pitch",CapBody::ROOT_ANGMOTOR_JOINT,0,capBody,layout);
 makeJointWidget("Roll",CapBody::ROOT_ANGMOTOR_JOINT,1,capBody,layout);
 makeJointWidget("Yaw",CapBody::ROOT_ANGMOTOR_JOINT,2,capBody,layout);

  makeJointWidget("ChinX",CapBody::CHIN_JOINT,0,capBody,layout);
  makeJointWidget("ChinY",CapBody::CHIN_JOINT,2,capBody,layout);
  makeJointWidget("ChinZ",CapBody::CHIN_JOINT,1,capBody,layout);

  makeJointWidget("NeckX",CapBody::THROAT_JOINT,0,capBody,layout);
  makeJointWidget("NeckY",CapBody::THROAT_JOINT,2,capBody,layout);
  makeJointWidget("NeckZ",CapBody::THROAT_JOINT,1,capBody,layout);

  makeJointWidget("R.CollarX",CapBody::R_COLLAR_JOINT,0,capBody,layout);
  makeJointWidget("R.CollarY",CapBody::R_COLLAR_JOINT,2,capBody,layout);
  makeJointWidget("R.CollarZ",CapBody::R_COLLAR_JOINT,1,capBody,layout);

  makeJointWidget("R.ShoulderX",CapBody::R_SHOULDER_JOINT,0,capBody,layout);
  makeJointWidget("R.ShoulderY",CapBody::R_SHOULDER_JOINT,2,capBody,layout);
  makeJointWidget("R.ShoulderZ",CapBody::R_SHOULDER_JOINT,1,capBody,layout);

  makeJointWidget("R.ElbowX",CapBody::R_ELBOW_JOINT,0,capBody,layout);
  makeJointWidget("R.ElbowZ",CapBody::R_ELBOW_JOINT,1,capBody,layout);

  makeJointWidget("R.WristX",CapBody::R_WRIST_JOINT,0,capBody,layout);
  makeJointWidget("R.WristY",CapBody::R_WRIST_JOINT,1,capBody,layout);

  makeJointWidget("L.CollarX",CapBody::L_COLLAR_JOINT,0,capBody,layout);
  makeJointWidget("L.CollarY",CapBody::L_COLLAR_JOINT,2,capBody,layout);
  makeJointWidget("L.CollarZ",CapBody::L_COLLAR_JOINT,1,capBody,layout);

  makeJointWidget("L.ShoulderX",CapBody::L_SHOULDER_JOINT,0,capBody,layout);
  makeJointWidget("L.ShoulderY",CapBody::L_SHOULDER_JOINT,2,capBody,layout);
  makeJointWidget("L.ShoulderZ",CapBody::L_SHOULDER_JOINT,1,capBody,layout);

  makeJointWidget("L.ElbowX",CapBody::L_ELBOW_JOINT,0,capBody,layout);
  makeJointWidget("L.ElbowZ",CapBody::L_ELBOW_JOINT,1,capBody,layout);

  makeJointWidget("L.WristX",CapBody::L_WRIST_JOINT,0,capBody,layout);
  makeJointWidget("L.WristY",CapBody::L_WRIST_JOINT,1,capBody,layout);

  makeJointWidget("SpineX",CapBody::SPINE_JOINT,0,capBody,layout);
  makeJointWidget("SpineY",CapBody::SPINE_JOINT,2,capBody,layout);
  makeJointWidget("SpineZ",CapBody::SPINE_JOINT,1,capBody,layout);

  makeJointWidget("WaistX",CapBody::WAIST_JOINT,0,capBody,layout);
  makeJointWidget("WaistY",CapBody::WAIST_JOINT,2,capBody,layout);
  makeJointWidget("WaistZ",CapBody::WAIST_JOINT,1,capBody,layout);

  makeJointWidget("R.HipX",CapBody::R_HIP_JOINT,0,capBody,layout);
  makeJointWidget("R.HipY",CapBody::R_HIP_JOINT,2,capBody,layout);
  makeJointWidget("R.HipZ",CapBody::R_HIP_JOINT,1,capBody,layout);

  makeJointWidget("R.KneeX",CapBody::R_KNEE_JOINT,0,capBody,layout);
  makeJointWidget("R.KneeZ",CapBody::R_KNEE_JOINT,1,capBody,layout);

  makeJointWidget("R.AnkleX",CapBody::R_ANKLE_JOINT,0,capBody,layout);
  makeJointWidget("R.AnkleY",CapBody::R_ANKLE_JOINT,1,capBody,layout);

  makeJointWidget("R.Foot",CapBody::R_FOOT_JOINT,0,capBody,layout);

  makeJointWidget("L.HipX",CapBody::L_HIP_JOINT,0,capBody,layout);
  makeJointWidget("L.HipY",CapBody::L_HIP_JOINT,2,capBody,layout);
  makeJointWidget("L.HipZ",CapBody::L_HIP_JOINT,1,capBody,layout);

  makeJointWidget("L.KneeX",CapBody::L_KNEE_JOINT,0,capBody,layout);
  makeJointWidget("L.KneeZ",CapBody::L_KNEE_JOINT,1,capBody,layout);

  makeJointWidget("L.AnkleX",CapBody::L_ANKLE_JOINT,0,capBody,layout);
  makeJointWidget("L.AnkleY",CapBody::L_ANKLE_JOINT,1,capBody,layout);

  makeJointWidget("L.Foot",CapBody::L_FOOT_JOINT,0,capBody,layout);
}



void MainWindow::populateJointPlotTab(CapBody* capBody,
                                  QVBoxLayout* layout)
{

    for (int i = 0; i < capBody->JOINT_COUNT; i++){

        QString jointName = capBody->jointNames[i];
        JointPlotWidget* jw = new JointPlotWidget(jointName, i);

        connect(jw,SIGNAL(checkStatusChanged(bool, int)),
                this,SLOT(jointPlotChecked(bool, int)));

        layout->addWidget(jw);
        jointPlotWidgets.push_back(jw);
    }
}

void MainWindow::makeBodyWidget(QString label,int body,
                                int axis,CapBody* cb,
                                QVBoxLayout* lay)
{
  QHBoxLayout* hl = new QHBoxLayout;
  QLabel* lab = new QLabel(label);
  hl->addWidget(lab);
  DSBoxWithParams* spin=new DSBoxWithParams(body,axis);
  spin->setMinimum(0.01);
  spin->setMaximum(2);
  spin->setDecimals(3);     // Millimeter resolution
  spin->setSingleStep(.01); // Centimeter steps
  hl->addWidget(spin);

  // We need a way to connect this thing to the
  // appropriate setter in the body object.
  cb->setBodySpin(body,axis,spin);
  lay->addLayout(hl);
}

/**
 * @brief MainWindow::populateBodyTab Allow control of body-part dimensions
 * @param capBody Pointer to the character model
 * @param layout Layout of the BodyDim
 *
 *  This function creates widgets for manipulating the dimensions
 * of the individual body parts of the character model.
 *  As with the populateJointsTab above, this should be loaded
 * from a model file rather than hard-coded here.
 */
void MainWindow::populateBodyTab(CapBody* capBody,
                                 QVBoxLayout* layout)
{
  makeBodyWidget("Head Rad",CapBody::HEAD_BODY,0,capBody,layout);
  makeBodyWidget("Neck X",CapBody::NECK_BODY,0,capBody,layout);
  makeBodyWidget("Neck Y",CapBody::NECK_BODY,1,capBody,layout);
  makeBodyWidget("Neck Z",CapBody::NECK_BODY,2,capBody,layout);
  makeBodyWidget("UpTorso Rad",CapBody::UP_TORSO_BODY,0,capBody,layout);
  makeBodyWidget("UpTorso Len",CapBody::UP_TORSO_BODY,2,capBody,layout);
  makeBodyWidget("R.Collar Rad",CapBody::R_COLLAR_BODY,0,capBody,layout);
  makeBodyWidget("R.Collar Len",CapBody::R_COLLAR_BODY,2,capBody,layout);
  makeBodyWidget("R.UpArm Rad",CapBody::RUP_ARM_BODY,0,capBody,layout);
  makeBodyWidget("R.UpArm Len",CapBody::RUP_ARM_BODY,2,capBody,layout);
  makeBodyWidget("R.LoArm Rad",CapBody::RLO_ARM_BODY,0,capBody,layout);
  makeBodyWidget("R.LoArm Len",CapBody::RLO_ARM_BODY,2,capBody,layout);
  makeBodyWidget("R.Hand Rad",CapBody::R_HAND_BODY,0,capBody,layout);
  makeBodyWidget("L.Collar Rad",CapBody::L_COLLAR_BODY,0,capBody,layout);
  makeBodyWidget("L.Collar Len",CapBody::L_COLLAR_BODY,2,capBody,layout);
  makeBodyWidget("L.UpArm Rad",CapBody::LUP_ARM_BODY,0,capBody,layout);
  makeBodyWidget("L.UpArm Len",CapBody::LUP_ARM_BODY,2,capBody,layout);
  makeBodyWidget("L.LoArm Rad",CapBody::LLO_ARM_BODY,0,capBody,layout);
  makeBodyWidget("L.LoArm Len",CapBody::LLO_ARM_BODY,2,capBody,layout);
  makeBodyWidget("L.Hand Rad",CapBody::L_HAND_BODY,0,capBody,layout);
  makeBodyWidget("LoTorso X",CapBody::LO_TORSO_BODY,0,capBody,layout);
  makeBodyWidget("LoTorso Y",CapBody::LO_TORSO_BODY,1,capBody,layout);
  makeBodyWidget("LoTorso Z",CapBody::LO_TORSO_BODY,2,capBody,layout);
  makeBodyWidget("Waist Rad",CapBody::WAIST_BODY,0,capBody,layout);
  makeBodyWidget("Waist Len",CapBody::WAIST_BODY,2,capBody,layout);
  makeBodyWidget("R.UpLeg Rad",CapBody::RUP_LEG_BODY,0,capBody,layout);
  makeBodyWidget("R.UpLeg Len",CapBody::RUP_LEG_BODY,2,capBody,layout);
  makeBodyWidget("R.LoLeg Rad",CapBody::RLO_LEG_BODY,0,capBody,layout);
  makeBodyWidget("R.LoLeg Len",CapBody::RLO_LEG_BODY,2,capBody,layout);
  makeBodyWidget("R.Heel Rad",CapBody::R_HEEL_BODY,0,capBody,layout);
  makeBodyWidget("R.Tarsal Rad",CapBody::R_TARSAL_BODY,0,capBody,layout);
  makeBodyWidget("R.Tarsal Len",CapBody::R_TARSAL_BODY,2,capBody,layout);
  makeBodyWidget("L.UpLeg Rad",CapBody::LUP_LEG_BODY,0,capBody,layout);
  makeBodyWidget("L.UpLeg Len",CapBody::LUP_LEG_BODY,2,capBody,layout);
  makeBodyWidget("L.LoLeg Rad",CapBody::LLO_LEG_BODY,0,capBody,layout);
  makeBodyWidget("L.LoLeg Len",CapBody::LLO_LEG_BODY,2,capBody,layout);
  makeBodyWidget("L.Heel Rad",CapBody::L_HEEL_BODY,0,capBody,layout);
  makeBodyWidget("L.Tarsal Rad",CapBody::L_TARSAL_BODY,0,capBody,layout);
  makeBodyWidget("L.Tarsal Len",CapBody::L_TARSAL_BODY,2,capBody,layout);
}

SimWorld* MainWindow::getWorld()
{
  return ui->glWidget->getWorld();
}

void MainWindow::toggleFullscreenSlot()
{
  ui->glWidget->setWindowFlags(
        ui->glWidget->windowFlags()^Qt::Window);
  // This does nothing if we're not a window.
  ui->glWidget->showFullScreen();
}



/**
 * @brief MainWindow::playPauseAll Start or stop both simulation and data
 * @param play
 */
void MainWindow::playPauseAll(bool play)
{
  playPauseData(play);
  playPauseSim(play);
  updatePlayButtons();
  updateButtonStatus = true;

}

void MainWindow::playPauseSim(bool play)
{
  SimWorld* world = ui->glWidget->getWorld();
  if (world->isPaused() != play) return;
  world->pauseSim(!play);
  updatePlayButtons();
  updateButtonStatus = true;
}

void MainWindow::playPauseData(bool play)
{
  MarkerData* markerData = ui->glWidget->getWorld()->getMarkerData();
  if (markerData->isPaused() != play) return;
  markerData->setPaused(!play);
  updatePlayButtons();
  updateButtonStatus = true;
}

void MainWindow::updatePlayButtons()
{
  SimWorld* world = ui->glWidget->getWorld();
  MarkerData* markerData = world->getMarkerData();

  if (world->isPaused()) {
      ui->playPauseSimButton->setChecked(false);
    } else {
      ui->playPauseSimButton->setChecked(true);
  }
  if (markerData->isPaused()) {
    ui->playPauseDataButton->setChecked(false);
  } else {
    ui->playPauseDataButton->setChecked(true);  }

  if (!(world->isPaused()||markerData->isPaused())) {
    ui->playAllButton->setChecked(true);
  } else {
    ui->playAllButton->setChecked(false);
  }
}

void MainWindow::setMarkMap(int id,int bod)
{
  markerWidgetArray[id]->setMarkBody(bod+1);
  markerWidgetArray[id]->setConnect(bod>=0);
}

void MainWindow::setMarkPoint(int id,double xx,double yy,double zz)
{
  markerWidgetArray[id]->setMarkPos(xx,yy,zz);
}

void MainWindow::stepSim()
{
  playPauseSim(false);
  ui->glWidget->getWorld()->setSingleStep();

}

void MainWindow::stepData()
{
  playPauseData(false);
  ui->glWidget->getWorld()->getMarkerData()->setSingleStep();
}

void MainWindow::stepAll()
{
  stepSim();
  stepData();
}

/**
 * @brief MainWindow::setDataFrame Set the active data frame
 * @param frame
 */
void MainWindow::setDataFrame(int frame)
{

  MarkerData* md = ui->glWidget->getWorld()->getMarkerData();
  md->setFrame(frame);
}

/**
 * @brief MainWindow::setDataStep  Set how many frames pass with each time step
 * @param stepSize Number of frames to advance with each step
 */
void MainWindow::setDataStep(int stepSize)
{

  MarkerData* md = ui->glWidget->getWorld()->getMarkerData();
  md->setStepSize(stepSize);
}

/**
 * @brief MainWindow::setFrameTime How long is each time step
 * @param step Time in milliseconds
 *
 * This also has the side-effect of setting the animation
 * speed.  Maybe it shouldn't.
 */
void MainWindow::setFrameTime(double step)
{
  getWorld()->setStepSize(step);
  updateTimer.start(int(1000*step));
}

/**
 * @brief MainWindow::grabMarkPos Anchor a marker at its current position
 * @param mark The marker to anchor
 *
 *  Compute the location of the marker in body-relative
 * coordinates.  Set the joint anchor at that point.
 */
void MainWindow::grabMarkPos(int mark)
{
  CapBody* body = ui->glWidget->getWorld()->getBody();
  MarkerData* md = ui->glWidget->getWorld()->getMarkerData();
  const dReal* markPos = dBodyGetPosition(md->body[mark]);
  dVector3 pos;
  dBodyGetPosRelPoint(body->body_segments[body->marker_to_body[mark].id],
                      markPos[0],markPos[1],markPos[2],pos);
  markerWidgetArray[mark]->setMarkPos(pos[0],pos[1],pos[2]);
}

/**
 * @brief MainWindow::updateLoop Main animation loop
 *
 * Advance the script.  Then advance the simulation and
 * data if appropriate.  Then render.
 */
void MainWindow::updateLoop()
{

    if (updateButtonStatus) {
        this->update();
        updateButtonStatus = false;
    }

  if (experimentScript->runScript) {
        experimentScript->updateScript();
  }
  ui->glWidget->animate();
}

void MainWindow::usingMarkers(bool used)
{
    if (ui->glWidget->getWorld()->usingDefaultSettings) {

        int markCnt = (int) markerWidgetArray.size();
            for (int ii=0;ii<markCnt;++ii) {
                markerWidgetArray[ii]->setConnect(used);
            }
    }else{
        usingCMarkers(used);
    }
}

void MainWindow::connectMarkers()
{
  usingMarkers(true);
  std::cout << "[mainwindow] Connect all markers" << std::endl;
}

void MainWindow::releaseMarkers()
{
  usingMarkers(false);
  std::cout << "[mainwindow] Release all markers." << std::endl;

}

void MainWindow::updateMarkerAnchors()
{
  int markCnt = (int) markerWidgetArray.size();
  for (int ii=0;ii<markCnt;++ii) {
    markerWidgetArray[ii]->grab();
  }
}

void MainWindow::useMarkers(bool toggle)   // markers
{
  if (toggle) {
    ui->glWidget->getWorld()->follow(0);
    lightForces();
  }
}

void MainWindow::useAngles(bool toggle)    //angle
{
  if (toggle) {
    ui->glWidget->getWorld()->follow(1);
    strongForces();
    playPauseData(false);
  }
}

void MainWindow::useAltAngles(bool toggle)  // altangle
{
  if (toggle) {
    ui->glWidget->getWorld()->follow(2);
    strongForces();
    playPauseData(false);
  }
}

void MainWindow::useTorques(bool toggle) // last button
{
  if (toggle) {
    ui->glWidget->getWorld()->follow(3);
    zeroForces();
  }
}


void MainWindow::setDataRange(int maxSize)
{
  ui->timeSlider->setRange(0,maxSize);
  ui->dataFrameBox->setRange(0,maxSize);
  ui->markerFrameStartBox->setRange(0,maxSize);
  ui->markerFrameStopBox->setRange(0,maxSize);
  ui->markerFrameStartBox->setValue(0);
  ui->markerFrameStopBox->setValue(maxSize);
  ui->timeSlider->setValue(0);
  ui->dataFrameBox->setValue(0);
}

/**
 * @brief MainWindow::loadMarkerFile Open and load some marker data
 * @param filename
 *
 * Pending...
 *  We determine an appropriate sub-class of
 * MarkerData from the extension.  We create it and then
 * we hook up all the appropriate pieces.
 */

void MainWindow::markerFileDialog()
{
  std::cout << "[mainwindow] marker file load..." << std::endl;

  ui->playAllButton->clicked(false);
  experimentScript->endScript();
  ui->glWidget->getWorld()->usingDefaultSettings = true;

  QString filename = QFileDialog::getOpenFileName(this,"Select marker data file",ui->glWidget->getWorld()->fileDialogPath,tr("motion capture data (*.c3d)"));
  if (filename.isNull() || filename.isEmpty()){
      return;
  }
  loadMarkerFile(filename, ui->markerFileLineEdit->text());
}

void MainWindow::loadMarkerFile(QString filename, QString previousFileName)
{

    //load new marker files
    QByteArray ba = filename.toLocal8Bit();
    const char *c_filename = ba.data();

    //check if the new file can be loaded successfully
    C3dFile data;
    if (data.loadFile(c_filename) == false) {
             std::cout << "[mainwindow] Load marker file error!" << std::endl;
             QMessageBox::warning(this,"Undone", "Load marker file error!");
             return;
    }

    //check if the new marker file fits the current body settings
    SimWorld* sw = ui->glWidget->getWorld();
    string fulllabel;
    vector<string> newLables;
    for (int i = 0; i < sw->getBody()->bodyMarkMap.size(); i++) {
        fulllabel = data.parameters.groups["POINT"]->params["LABELS"].getString(i);
        newLables.push_back(fulllabel.substr(fulllabel.find(":")+1));
    }

  vector<string> previousLabels = sw->getMarkerData()->labels;
  std::sort(previousLabels.begin(), previousLabels.end());
  std::sort(newLables.begin(), newLables.end());

  if (previousLabels != newLables) {
      QMessageBox::warning(this,"Undone",
                             "The selected marker file\n"
                             "does not fit the current body setting.\n"
                             "Please change the CapBody setting in \n"
                             "CapBody.h file.\n"
                             );
  }else{
      ui->glWidget->getWorld()->setMotion(c_filename);
      setDataRange(sw->getMarkerData()->size());
      resetMarkerTab();
      sw->getBody()->copyToSim();
      ui->markerRadio->setChecked(true);
     // usingMarkers(true);

      ui->glWidget->defaultView();
      //clear previous angle/torque sequence data
      clearData();
      //clear graphs
      makingPlot();
  }
}

void MainWindow::updateParameters(double p1, double p2, double p3, double p4, double p5){

    SimWorld* sw = ui->glWidget->getWorld();
    sw->ground_ERP = p1;
    sw->ground_CFM = p2;
    sw->ground_squish = p3;
    sw->ground_friction = p4;
    //sw->ground_surfaceLayer = p5;
}

void MainWindow::experimentSlot()
{
    experimentScript->startScript();
}

void MainWindow::experimentStopSlot()
{
    experimentScript->endScript();
    ui->playAllButton->clicked(false);
}

void MainWindow::experimentEndSlot()
{

    experimentScript->endScript();
}

void MainWindow::saveModel()
{
  getWorld()->getBody()->saveState();
}

void MainWindow::restoreModel()
{
  getWorld()->getBody()->restoreState();
}

void MainWindow::clearData()
{
  SimWorld* w = getWorld();
  w->angle_sequence->clear();
  w->angle_sequence2->clear();
  w->torque_sequence->clear();
}

void MainWindow::strongForces()
{
  int count = jointWidgets.size();
  for (int ii=0;ii<6;++ii) {
    jointWidgets[ii]->setForceLimit(9999);
  }

  for (int ii=6;ii<count;++ii) {
    jointWidgets[ii]->setForceLimit(9999);
  }
}

void MainWindow::lightForces()
{
  int count = jointWidgets.size();
  for (int ii=0;ii<6;++ii) {
    jointWidgets[ii]->setForceLimit(0);
  }

  for (int ii=6;ii<count;++ii) {
    jointWidgets[ii]->setForceLimit(50);
  }
}

void MainWindow::zeroForces()
{
  int count = jointWidgets.size();
  for (int ii=0;ii<6;++ii) {
    jointWidgets[ii]->setForceLimit(0);
  }

  for (int ii=6;ii<count;++ii) {
    jointWidgets[ii]->setForceLimit(0);
  }
}


void MainWindow::saveBodyAngles(QString filename)
{
  getWorld()->anglesToFile(filename);
}


void MainWindow::writePositionFrame(int cc,int tri,FILE* file)
{
  getWorld()->writeBodyPositionFrame(cc,tri,file);
}

void MainWindow::writeAngleFrame(int cc,int tri,FILE* file)
{
  getWorld()->writeAngleFrame(cc,tri,file);
}

void MainWindow::writeJointFrame(int cc,int tri,FILE* file)
{
  getWorld()->writeJointFrame(cc,tri,file);
}


void MainWindow::useGlobalForces(bool use)
{
  getWorld()->getBody()->global_forces = use;
}



////////////////plotting//////////////////
void MainWindow::initialPlotJoints(){

    xyzAxis.push_back(1);
    xyzAxis.push_back(0);
    xyzAxis.push_back(0);

    plotAngleTorque.push_back(1);
    plotAngleTorque.push_back(0);

    for (int i = 0; i < 22; i++){
        plotJoints.push_back(0);
    }

    for(int i = 0; i < 22; i++){
        if (i == 12 || i == 4 || i == 8 || i == 13 || i == 16 || i == 17){
            jointPlotWidgets[i]->changeStatus(true);
        }
    }
}


void MainWindow::jointPlotChecked(bool checked, int joint_index){

    if (checked == true){
        plotJoints[joint_index] = 1;
    }else{
        plotJoints[joint_index] = 0;
    }
    makingPlot();
}

void MainWindow::makingPlot(){

    ui->customPlot->clearGraphs();
    map <int, QColor> colors = {{0, Qt::red},
                             {1, Qt::black},
                             {2, Qt::green},
                             {3, Qt::darkRed},
                             {4, Qt::darkGreen},
                             {5, Qt::blue},
                             {6, Qt::darkBlue},
                             {7, Qt::cyan},
                             {8, Qt::darkCyan},
                             {9, Qt::magenta},
                             {10, Qt::darkMagenta},
                             {11, Qt::yellow},
                             {12, Qt::darkYellow},
                             {13, Qt::gray},
                             {14, Qt::darkGray},
                             {15, Qt::lightGray},
                             {16, Qt::green},
                             {17, Qt::red},
                             {18, Qt::darkGreen},
                             {19, Qt::yellow},
                             {20, Qt::darkCyan},
                             {21, Qt::black},
                            };


    SimWorld* world = ui->glWidget->getWorld();
    CapBody* cb = world->getBody();

    //plot angles or torques

    Sequence* sequence1;
    Sequence* sequence2;
    const char * strTitle;

    if (plotAngleTorque[0] == 1) {
        sequence1 = world->angle_sequence;
        sequence2 = world->angle_sequence2;

        QCPItemText *textLabel = new QCPItemText(ui->customPlot);
        textLabel->position->setType(QCPItemPosition::ptAxisRectRatio);
        textLabel->setPositionAlignment(Qt::AlignHCenter);
        textLabel->position->setCoords(0.3, 0); // place position at center/top of axis rect
        textLabel->setText("Solid lines indicate ground true\nDashed lines indicate recovered angles");
        textLabel->setTextAlignment(Qt::AlignLeft);
        textLabel->setFont(QFont(font().family(), 15)); // make font a bit larger
        textLabel->setPadding(QMargins(8, 0, 0, 0));// show black border around tex

    }else{
        sequence1 = world->torque_sequence;
        sequence2 = new Sequence();
    }

    int frames = sequence1->size();
    int frames2 = sequence2->size();
    QVector<double> x(frames), y(frames);
    QVector<double> x2(frames2), y2(frames2);


    int axis = 0;
    for (int i = 0; i < 3; i++){
        if( xyzAxis[i] == 1) {
            axis = i;
            break;
        }
    }

   double ymin = 0;
   double ymax = 0;
   int graphCount = -1;
   for (int index = 0; index < cb->JOINT_COUNT; index++){

        if (plotJoints[index] == 0) continue;

        for(int i = 0; i < frames; i++) {
                x[i] = i;
                y[i] = sequence1->getFrame(i)->getData(index, axis);
        }

        for(int i = 0; i < frames2; i++) {
                x2[i] = i;
                y2[i] = sequence2->getFrame(i)->getData(index, axis);
        }
        ymin = min(ymin, *min_element(y.begin(), y.end()));
        ymax = max(ymax, *max_element(y.begin(), y.end()));

        QPen pen;
        pen.setColor(colors[index]);
        ui->customPlot->addGraph();
        graphCount+=1;
        ui->customPlot->graph(graphCount)->setData(x, y);
        ui->customPlot->graph(graphCount)->setPen(pen);
        ui->customPlot->graph(graphCount)->setName(cb->jointNames[index]);

        if (frames2 == NULL) continue;

        pen.setStyle(Qt::DashLine);
        pen.setWidth(1.0);
        //pen.setColor(colors[graphCount]);
        ui->customPlot->addGraph();
        graphCount+=1;
        ui->customPlot->graph(graphCount)->setPen(pen);
        ui->customPlot->graph(graphCount)->setData(x2, y2);
        ui->customPlot->graph(graphCount)->setName(cb->jointNames[index]);
    }

    // Give the axes some labels:
    ui->customPlot->xAxis->setLabel("Frames");
    ui->customPlot->yAxis->setLabel("Joint Angles (rad)");

    // Rescale axes
    ui->customPlot->xAxis->setRange(0, frames);
    ui->customPlot->yAxis->setRange(ymin*1.8, ymax*1.8);
   // ui->customPlot->rescaleAxes();

    //legend
    QFont legendFont = font();
    legendFont.setPointSize(10);
    ui->customPlot->legend->setFont(legendFont);
    ui->customPlot->legend->setSelectedFont(legendFont);
    ui->customPlot->legend->setSelectableParts(QCPLegend::spItems); // legend box shall not be selectable, only legend items
    ui->customPlot->legend->setVisible(true);
    ui->customPlot->replot();

}


void MainWindow::plotJointAngle(bool toggle){

    if (toggle){
        plotAngleTorque[0] = 1;
    }else{
        plotAngleTorque[0] = 0;
    }
    makingPlot();
}

void MainWindow::plotJointTorque(bool toggle){

    if (toggle){
        plotAngleTorque[1] = 1;
    }else{
        plotAngleTorque[1] = 0;
    }
    makingPlot();
}


void MainWindow::plotXAxis(bool toggle){

    if (toggle){
        xyzAxis[0] = 1;
    }else{
        xyzAxis[0] = 0;
    }
    makingPlot();
}

void MainWindow::plotYAxis(bool toggle){

    if (toggle){
        xyzAxis[1] = 1;
    }else{
        xyzAxis[1] = 0;
    }
      makingPlot();
}

void MainWindow::plotZAxis(bool toggle){

    if (toggle){
        xyzAxis[2] = 1;
    }else{
        xyzAxis[2] = 0;
    }
      makingPlot();
}


void MainWindow::saveImage(){
    QString filters("PNG (*.png);;JPG (*.jpg);;TIFF (*.tiff);;XPM (*.xpm)");
    QString defaultFilter("PNG (*.png)");
    QString filename = QFileDialog::getSaveFileName(this,tr("Save Image"),"image", filters, &defaultFilter);
    ui->customPlot->saveJpg(filename,  0, 0, 1.0, -1  );
}


void MainWindow::titleDoubleClick(QMouseEvent* event)
{
  Q_UNUSED(event)
  if (QCPTextElement *title = qobject_cast<QCPTextElement*>(sender()))
  {
    // Set the plot title by double clicking on it
    bool ok;
    QString newTitle = QInputDialog::getText(this, "QCustomPlot example", "New plot title:", QLineEdit::Normal, title->text(), &ok);
    if (ok)
    {
      title->setText(newTitle);
      ui->customPlot->replot();
    }
  }
}

void MainWindow::axisLabelDoubleClick(QCPAxis *axis, QCPAxis::SelectablePart part)
{
  // Set an axis label by double clicking on it
  if (part == QCPAxis::spAxisLabel) // only react when the actual axis label is clicked, not tick label or axis backbone
  {
    bool ok;
    QString newLabel = QInputDialog::getText(this, "QCustomPlot example", "New axis label:", QLineEdit::Normal, axis->label(), &ok);
    if (ok)
    {
      axis->setLabel(newLabel);
      ui->customPlot->replot();
    }
  }
}

void MainWindow::legendDoubleClick(QCPLegend *legend, QCPAbstractLegendItem *item)
{
  // Rename a graph by double clicking on its legend item
  Q_UNUSED(legend)
  if (item) // only react if item was clicked (user could have clicked on border padding of legend where there is no item, then item is 0)
  {
    QCPPlottableLegendItem *plItem = qobject_cast<QCPPlottableLegendItem*>(item);
    bool ok;
    QString newName = QInputDialog::getText(this, "QCustomPlot example", "New graph name:", QLineEdit::Normal, plItem->plottable()->name(), &ok);
    if (ok)
    {
      plItem->plottable()->setName(newName);
      ui->customPlot->replot();
    }
  }
}

void MainWindow::selectionChanged()
{
  /*
   normally, axis base line, axis tick labels and axis labels are selectable separately, but we want
   the user only to be able to select the axis as a whole, so we tie the selected states of the tick labels
   and the axis base line together. However, the axis label shall be selectable individually.

   The selection state of the left and right axes shall be synchronized as well as the state of the
   bottom and top axes.

   Further, we want to synchronize the selection of the graphs with the selection state of the respective
   legend item belonging to that graph. So the user can select a graph by either clicking on the graph itself
   or on its legend item.
  */

  // make top and bottom axes be selected synchronously, and handle axis and tick labels as one selectable object:
  if (ui->customPlot->xAxis->selectedParts().testFlag(QCPAxis::spAxis) || ui->customPlot->xAxis->selectedParts().testFlag(QCPAxis::spTickLabels) ||
      ui->customPlot->xAxis2->selectedParts().testFlag(QCPAxis::spAxis) || ui->customPlot->xAxis2->selectedParts().testFlag(QCPAxis::spTickLabels))
  {
    ui->customPlot->xAxis2->setSelectedParts(QCPAxis::spAxis|QCPAxis::spTickLabels);
    ui->customPlot->xAxis->setSelectedParts(QCPAxis::spAxis|QCPAxis::spTickLabels);
  }
  // make left and right axes be selected synchronously, and handle axis and tick labels as one selectable object:
  if (ui->customPlot->yAxis->selectedParts().testFlag(QCPAxis::spAxis) || ui->customPlot->yAxis->selectedParts().testFlag(QCPAxis::spTickLabels) ||
      ui->customPlot->yAxis2->selectedParts().testFlag(QCPAxis::spAxis) || ui->customPlot->yAxis2->selectedParts().testFlag(QCPAxis::spTickLabels))
  {
    ui->customPlot->yAxis2->setSelectedParts(QCPAxis::spAxis|QCPAxis::spTickLabels);
    ui->customPlot->yAxis->setSelectedParts(QCPAxis::spAxis|QCPAxis::spTickLabels);
  }

  // synchronize selection of graphs with selection of corresponding legend items:
  for (int i=0; i<ui->customPlot->graphCount(); ++i)
  {
    QCPGraph *graph = ui->customPlot->graph(i);
    QCPPlottableLegendItem *item = ui->customPlot->legend->itemWithPlottable(graph);
    if (item->selected() || graph->selected())
    {
      item->setSelected(true);
      graph->setSelection(QCPDataSelection(graph->data()->dataRange()));
    }
  }
}

void MainWindow::mousePress()
{
  // if an axis is selected, only allow the direction of that axis to be dragged
  // if no axis is selected, both directions may be dragged

  if (ui->customPlot->xAxis->selectedParts().testFlag(QCPAxis::spAxis))
    ui->customPlot->axisRect()->setRangeDrag(ui->customPlot->xAxis->orientation());
  else if (ui->customPlot->yAxis->selectedParts().testFlag(QCPAxis::spAxis))
    ui->customPlot->axisRect()->setRangeDrag(ui->customPlot->yAxis->orientation());
  else
    ui->customPlot->axisRect()->setRangeDrag(Qt::Horizontal|Qt::Vertical);
}

void MainWindow::mouseWheel()
{
  // if an axis is selected, only allow the direction of that axis to be zoomed
  // if no axis is selected, both directions may be zoomed

  if (ui->customPlot->xAxis->selectedParts().testFlag(QCPAxis::spAxis))
    ui->customPlot->axisRect()->setRangeZoom(ui->customPlot->xAxis->orientation());
  else if (ui->customPlot->yAxis->selectedParts().testFlag(QCPAxis::spAxis))
    ui->customPlot->axisRect()->setRangeZoom(ui->customPlot->yAxis->orientation());
  else
    ui->customPlot->axisRect()->setRangeZoom(Qt::Horizontal|Qt::Vertical);
}

void MainWindow::removeSelectedGraph()
{
  if (ui->customPlot->selectedGraphs().size() > 0)
  {
    ui->customPlot->removeGraph(ui->customPlot->selectedGraphs().first());
    ui->customPlot->replot();
  }
}

void MainWindow::removeAllGraphs()
{
  ui->customPlot->clearGraphs();
  ui->customPlot->replot();
}

void MainWindow::contextMenuRequest(QPoint pos)
{
  QMenu *menu = new QMenu(this);
  menu->setAttribute(Qt::WA_DeleteOnClose);

  if (ui->customPlot->legend->selectTest(pos, false) >= 0) // context menu on legend requested
  {
    menu->addAction("Move to top left", this, SLOT(moveLegend()))->setData((int)(Qt::AlignTop|Qt::AlignLeft));
    menu->addAction("Move to top center", this, SLOT(moveLegend()))->setData((int)(Qt::AlignTop|Qt::AlignHCenter));
    menu->addAction("Move to top right", this, SLOT(moveLegend()))->setData((int)(Qt::AlignTop|Qt::AlignRight));
    menu->addAction("Move to bottom right", this, SLOT(moveLegend()))->setData((int)(Qt::AlignBottom|Qt::AlignRight));
    menu->addAction("Move to bottom left", this, SLOT(moveLegend()))->setData((int)(Qt::AlignBottom|Qt::AlignLeft));
  } else  // general context menu on graphs requested
  {
    menu->addAction("Replot", this, SLOT(makingPlot()));
    if (ui->customPlot->selectedGraphs().size() > 0)
      menu->addAction("Remove selected graph", this, SLOT(removeSelectedGraph()));
    if (ui->customPlot->graphCount() > 0)
      menu->addAction("Remove all graphs", this, SLOT(removeAllGraphs()));
  }

  menu->popup(ui->customPlot->mapToGlobal(pos));
}

void MainWindow::moveLegend()
{
  if (QAction* contextAction = qobject_cast<QAction*>(sender())) // make sure this slot is really called by a context menu action, so it carries the data we need
  {
    bool ok;
    int dataInt = contextAction->data().toInt(&ok);
    if (ok)
    {
      ui->customPlot->axisRect()->insetLayout()->setInsetAlignment(0, (Qt::Alignment)dataInt);
      ui->customPlot->replot();
    }
  }
}

void MainWindow::graphClicked(QCPAbstractPlottable *plottable, int dataIndex)
{
  // since we know we only have QCPGraphs in the plot, we can immediately access interface1D()
  // usually it's better to first check whether interface1D() returns non-zero, and only then use it.
  double dataValue = plottable->interface1D()->dataMainValue(dataIndex);
  QString message = QString("Clicked on graph '%1' at data point #%2 with value %3.").arg(plottable->name()).arg(dataIndex).arg(dataValue);
  ui->statusBar->showMessage(message, 2500);
}


///////////Set default motion//////////////
void MainWindow::defaultSetting(){
    std::cout << "[mainwindow] custom settings load..." << std::endl;
    SimWorld* sw = ui->glWidget->getWorld();
    sw->usingDefaultSettings = true;
    sw->setDMotion();
    setDataRange(sw->getMarkerData()->size());
    resetMarkerTab();
    sw->getBody()->copyToSim();
    usingMarkers(true);
    ui->glWidget->defaultView();
    //clear previous angle/torque sequence data
    clearData();
    //clear graphs
    makingPlot();
}


//////////////////////////////////////////////////////////////////
//////////////////////Set Custom Motions/////////////////////////////////

void MainWindow::cmarkerFileDialog()
{
  std::cout << "[mainwindow] custom  marker file load..." << std::endl;
  QString filename = QFileDialog::getOpenFileName(this,"Select marker data file",ui->glWidget->getWorld()->fileDialogPath,tr("motion capture data (*.c3d *.csv *.tvd)"));
  if (filename.isNull() || filename.isEmpty()){
      return;
  }

  QByteArray ba = filename.toLocal8Bit();
  const char *c_filename = ba.data();

  C3dFile data;
  if (data.loadFile(c_filename)){
      ui->cmarkerFileLineEdit->setText(filename);
      SimWorld* sw = ui->glWidget->getWorld();

  }else{
      ui->cmarkerFileLineEdit->setText("");
      QMessageBox::warning(this,"Undone", "Load marker file error! The current loadfile method does not support this motion file.\nPlease add a custom loadfile method in c3ddata.cpp file.");
  }
}

void MainWindow::cmarkerMarkerMapDialog()
{
    std::cout << "[mainwindow] custom  marker-body map file load..." << std::endl;
    QString filename = QFileDialog::getOpenFileName(this,"Select marker data file",QString(),tr("marker map (*.txt)"));
    if (filename.isNull() || filename.isEmpty()){
        return;
    }
    ui->cmarkerMapLineEdit->setText(filename);

}

void MainWindow::cmarkerRelPosDialog()
{
    std::cout << "[mainwindow] custom  marker-body relative positions file load..." << std::endl;
    QString filename = QFileDialog::getOpenFileName(this,"Select marker data file",QString(),tr("marker relpos (*.txt)"));
    if (filename.isNull() || filename.isEmpty()){
        return;
    }
    ui->cmarkerRelPosLineEdit->setText(filename);

}

void MainWindow::cModelDimsDialog()
{
    std::cout << "[mainwindow] custom human model dimension file load..." << std::endl;
    QString filename = QFileDialog::getOpenFileName(this,"Select marker data file",QString(),tr("body dimension (*.txt)"));
    if (filename.isNull() || filename.isEmpty()){
        return;
    }
    ui->cmodelDimLineEdit->setText(filename);

}

void MainWindow::cjointAnchorDialog()
{
    std::cout << "[mainwindow] custom joint anchor file load..." << std::endl;
    QString filename = QFileDialog::getOpenFileName(this,"Select marker data file",QString(),tr("joint anchor (*.txt)"));
    if (filename.isNull() || filename.isEmpty()){
        return;
    }
    ui->cjointAnchorLineEdit->setText(filename);
}

void MainWindow::cdrawObjectsDialog()
{
    std::cout << "[mainwindow] custom drawing objects file load..." << std::endl;
    QString filename = QFileDialog::getOpenFileName(this,"Select marker data file",QString(),tr("joint anchor (*.csv)"));
    if (filename.isNull() || filename.isEmpty()){
        return;
    }
    ui->cDrawObjectsLineEdit->setText(filename);
}


void MainWindow::customSetting(){

    ui->playAllButton->clicked(false);
    experimentScript->endScript();
    ui->markerRadio->setChecked(true);

    std::cout << "[mainwindow] custom settings load..." << std::endl;
    SimWorld* sw = ui->glWidget->getWorld();
    sw->usingDefaultSettings = false;


    string markerFile = ui->cmarkerFileLineEdit->text().toStdString();
    string markerMapFile = ui->cmarkerMapLineEdit->text().toStdString();
    string markerRelPosFile = ui->cmarkerRelPosLineEdit->text().toStdString();
    string bodyDimFile = ui->cmodelDimLineEdit->text().toStdString();
    string jointAnchorFile = ui->cjointAnchorLineEdit->text().toStdString();


    if (markerFile == "") {
       QMessageBox::warning(this, "File Missing", "Custom marker file missing.\n The system will use default marker file.");
       markerFile = sw->defaultMarkerFile;
    }

    if (markerMapFile == "") {
       QMessageBox::warning(this, "File Missing", "Custom marker-body map missing.\n The system will use default marker-body map file.");
       markerMapFile = sw->defaultMarkerMapFile;
    }

    if (markerRelPosFile == "") {
       QMessageBox::warning(this, "File Missing", "Custom marker-body relative positions file missing.\n The system will use default marker-body relative positions file.");
        markerRelPosFile = sw->defaultMarkerRelPosFile;
    }

    if (bodyDimFile == "") {
       QMessageBox::warning(this, "File Missing", "Custom body dimension file missing.\n The system will use default body dimension file.");
       bodyDimFile = sw->defaultBodyDimFile;
    }

    if (jointAnchorFile == "") {
       QMessageBox::warning(this, "File Missing", "Custom joint anchor file missing.\n The system will use default joint anchor file.");
       jointAnchorFile = sw->defaultJointAnchorFile;
    }

    sw->markerFile = markerFile.c_str();
    sw->markerMapFile = markerMapFile.c_str();
    sw->markerRelPosFile = markerRelPosFile.c_str();
    sw->bodyDimFile = bodyDimFile.c_str();
    sw->jointAnchorFile = jointAnchorFile.c_str();
    sw->setCMotion(sw->markerFile, sw->markerMapFile, sw->markerRelPosFile, sw->bodyDimFile, sw->jointAnchorFile);
    setDataRange(sw->getMarkerData()->size());
    resetMarkerTab();
    sw->getBody()->copyToSim();
    usingMarkers(true);


    string drawObjects = ui->cDrawObjectsLineEdit->text().toStdString();
    if (drawObjects != ""){
        std::ifstream ip(drawObjects.c_str());
        if(!ip.is_open()) {
            std::cout << "[mainwindow] ERROR: Object File Open!" << '\n';
        }else{
            string line;
            int frames = 0;
            while (getline(ip, line)){
                frames += 1;
            }
            sw->drawObjects = drawObjects;
            sw->objectFrames = frames;
            ui->glWidget->customCamera();
        }
    }

    //clear previous angle/torque sequence data
    clearData();
    //clear graphs
    makingPlot();
   std::cout << "[mainwindow] custom setting completed" << std::endl;
}


void MainWindow::resetMarkerTab(){

    std::cout << "[mainwindow] reset marker tab..." << std::endl;

    SimWorld* sw = ui->glWidget->getWorld();

    ui->controlTabWidget->removeTab(2);

    QScrollArea* sa = new QScrollArea;
    QWidget* wid = new QWidget;
    QVBoxLayout* layout = new QVBoxLayout;
    layout->setContentsMargins(0,0,0,0);

    QHBoxLayout* innerLayout = new QHBoxLayout;
    QPushButton* connectButton = new QPushButton("Connect");
    QPushButton* releaseButton = new QPushButton("Release");
    QPushButton* updateButton = new QPushButton("Update Anchors");
    innerLayout->addWidget(connectButton);
    innerLayout->addWidget(releaseButton);
    innerLayout->addWidget(updateButton);
    connect(connectButton,SIGNAL(clicked()),this,SLOT(connectMarkers()));
    connect(releaseButton,SIGNAL(clicked()),this,SLOT(releaseMarkers()));
    connect(updateButton,SIGNAL(clicked()),this,SLOT(updateMarkerAnchors()));
    layout->addLayout(innerLayout);

    int markCnt = sw->marker_data->marker_count;

    markerWidgetArray.clear();
    markerWidgetArray.resize(markCnt);
    for (int ii=0;ii<markCnt;++ii) {
      markerWidgetArray[ii] = new MarkerWidget(ii,0);
      layout->addWidget(markerWidgetArray[ii]);
    }

    for (int ii=0;ii<markCnt;++ii) {
      connect(markerWidgetArray[ii],SIGNAL(markBodySet(int,int)),sw->marker_data,SLOT(changeBodyConnect(int,int)));
      connect(markerWidgetArray[ii],SIGNAL(markConnect(int,bool)),sw->marker_data,SLOT(changeBodyLink(int,bool)));
      connect(markerWidgetArray[ii],SIGNAL(markPosSet(int,double,double,double)),
              sw->marker_data,SLOT(changeLinkPos(int,double,double,double)));
      connect(markerWidgetArray[ii],SIGNAL(markGrab(int)),this, SLOT(grabMarkPos(int)));
    }

    wid->setLayout(layout);
    sa->setWidget(wid);
    ui->controlTabWidget->insertTab(2, sa,"Markers");
}


void MainWindow::usingCMarkers(bool used){

    int markCnt = (int) markerWidgetArray.size();
    for (int ii=0;ii<markCnt;++ii) {
        if ((ii == 0) || (ii == 5)|| (ii == 6)|| (ii == 32)||(ii == 32)|| (ii == 33)||(ii == 30)||(ii == 38)||(ii == 16)|| (ii == 20)||(ii == 21)|| (ii == 40)|| (ii == 41)||  (ii == 45)||(ii == 46)||(ii == 47)||(ii == 44)) {
            markerWidgetArray[ii]->setConnect(used);
        }else{
             markerWidgetArray[ii]->setConnect(false);
           }
     }
}

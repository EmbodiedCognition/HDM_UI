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
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <vector>
#include <QColorDialog>
#include <QColor>
#include <QDockWidget>
#include <QFileDialog>
#include <QMessageBox>
#include <QScrollArea>
#include <QGLWidget>
#include <openGL/glu.h>
#include <QTimer>
#include <markerwidget.h>
#include <jointwidget.h>
#include <jointplotwidget.h>
#include <ode/ode.h>
#include <QMainWindow>
#include <QInputDialog>
#include "qcustomplot.h"


class MarkerWidget;
class JointWidget;
class JointPlotWidget;
class CapBody;
class QVBoxLayout;
class BoardData;
class QPushButton;
class SimWorld;
class ScriptBase;

using namespace std;

namespace Ui {
    class MainWindow;
}

/**
  The main GUI window.  In windowed mode, this
  provides a docking place for the openGL window
  as well as GUI elements for setting various
  modes and controlling the flow of information.
  */
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();


 vector<int> plotJoints;
 vector<int> xyzAxis;
 vector<int> plotAngleTorque;


  void makeJointWidget(QString label,int joint,
                       int axis,CapBody* cb,
                       QVBoxLayout* lay);

  void makeJointPlotWidget(QString label,int joint,
                       int axis,CapBody* cb,
                       QVBoxLayout* lay);

  void populateJointTab(CapBody* capBody,
                        QVBoxLayout* layout);
  void populateJointPlotTab(CapBody *capBody, QVBoxLayout *layout);
  void makeBodyWidget(QString label,int joint,
                      int axis,CapBody* cb,
                      QVBoxLayout* lay);
  void populateBodyTab(CapBody* capBody,
                       QVBoxLayout* layout);
  SimWorld* getWorld();

  void writePositionFrame(int cc,int tri,FILE* file);
  void writeAngleFrame(int cc,int tri,FILE* file);
  void writeJointFrame(int cc,int tri,FILE* file);


  bool updateButtonStatus;

public slots:
  void toggleFullscreenSlot();

  void playPauseAll(bool);
  void playPauseSim(bool);
  void playPauseData(bool);
  void updatePlayButtons();

  void setMarkMap(int id,int bod);
  void setMarkPoint(int id,double xx,double yy,double zz);

  void stepSim();
  void stepData();
  void stepAll();

  void setDataFrame(int);
  void setDataStep(int);
  void setFrameTime(double);

  void grabMarkPos(int);

  void updateLoop();

  void usingMarkers(bool used);
  void connectMarkers();
  void releaseMarkers();
  void updateMarkerAnchors();

  void useAngles(bool toggle);
  void useMarkers(bool toggle);
  void useTorques(bool toggle);
  void useAltAngles(bool toggle);
  void makingPlot();

  void setDataRange(int maxSize);
  void loadMarkerFile(QString filename, QString previousFilename);


  void updateParameters(double p1, double p2, double p3, double p4, double p5);
  void experimentSlot();
  void experimentStopSlot();
  void experimentEndSlot();
  void saveModel();
  void restoreModel();
  void clearData();

  void strongForces();
  void lightForces();
  void zeroForces();

  void saveBodyAngles(QString filename);

  void useGlobalForces(bool use);

  void markerFileDialog();

  void cmarkerFileDialog();
  void cmarkerMarkerMapDialog();
  void cmarkerRelPosDialog();
  void cModelDimsDialog();
  void cjointAnchorDialog();
  void cdrawObjectsDialog();
  void customSetting();
  void usingCMarkers(bool used);
  void defaultSetting();
  void resetMarkerTab();


  void jointPlotChecked(bool, int);

  void plotXAxis(bool);
  void plotYAxis(bool);
  void plotZAxis(bool);
  void saveImage();
  void plotJointAngle(bool);
  void plotJointTorque(bool);

  void titleDoubleClick(QMouseEvent*);
  void selectionChanged();
  void mousePress();
  void mouseWheel();
  void axisLabelDoubleClick(QCPAxis*,QCPAxis::SelectablePart);
  void legendDoubleClick(QCPLegend*,QCPAbstractLegendItem*);
  void graphClicked(QCPAbstractPlottable*,int);
  void contextMenuRequest(QPoint);
  void removeSelectedGraph();
  void removeAllGraphs();
  void moveLegend();


public:
    Ui::MainWindow *ui;  ///< Holds the widgets created in the designer
    /// An array of widgets for controlling marker attachments
    std::vector<MarkerWidget*> markerWidgetArray;


#if defined( BOARD_DATA )
    BoardData* bd;
#endif

    /// Driver code for running a specific process to get kinematic or dynamic data
    ScriptBase* experimentScript;

    /// Timer object controls the main update loop
    QTimer updateTimer;

    /// An array of widgets controlling individual joint degrees of freedom
    QList<JointWidget*> jointWidgets;
    QList<JointPlotWidget*> jointPlotWidgets;
    void initialPlotJoints();
};

#endif // MAINWINDOW_H

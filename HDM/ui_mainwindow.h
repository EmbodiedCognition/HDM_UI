/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "myglwidget.h"
#include "qcustomplot.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionExit;
    QAction *actionFullscreen;
    QWidget *centralWidget;
    QHBoxLayout *horizontalLayout_20;
    QSplitter *splitter;
    QFrame *frame_2;
    QVBoxLayout *verticalLayout_6;
    QTabWidget *tabWidget;
    QWidget *tab;
    QVBoxLayout *verticalLayout_3;
    MyGLWidget *glWidget;
    QWidget *tab_2;
    QVBoxLayout *verticalLayout_4;
    QCustomPlot *customPlot;
    QSlider *timeSlider;
    QFrame *frame;
    QHBoxLayout *horizontalLayout_19;
    QGroupBox *groupBox_3;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_16;
    QLabel *baLabel;
    QDoubleSpinBox *bodyAlpha;
    QCheckBox *camFollowCheckBox;
    QCheckBox *forceLinesCheckBox;
    QCheckBox *showMarkBox;
    QGroupBox *simulationGroupBox;
    QVBoxLayout *verticalLayout_5;
    QHBoxLayout *horizontalLayout_17;
    QCheckBox *selfCollideBox;
    QCheckBox *globalBox;
    QHBoxLayout *horizontalLayout_12;
    QSpacerItem *horizontalSpacer_12;
    QLabel *label_11;
    QDoubleSpinBox *frameTimeBox;
    QHBoxLayout *horizontalLayout_13;
    QSpacerItem *horizontalSpacer_11;
    QLabel *label_3;
    QDoubleSpinBox *terrainSpinBox;
    QHBoxLayout *horizontalLayout_14;
    QSpacerItem *horizontalSpacer_9;
    QLabel *label_2;
    QDoubleSpinBox *zBox;
    QHBoxLayout *horizontalLayout_15;
    QSpacerItem *horizontalSpacer_10;
    QLabel *label;
    QDoubleSpinBox *frictionSpinBox;
    QHBoxLayout *horizontalLayout_18;
    QSpacerItem *horizontalSpacer_3;
    QToolButton *playPauseSimButton;
    QToolButton *stepSimButton;
    QSpacerItem *horizontalSpacer_4;
    QGroupBox *markerGroupBox;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_4;
    QLineEdit *markerFileLineEdit;
    QToolButton *selectFileToolButton;
    QHBoxLayout *horizontalLayout_4;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_5;
    QLineEdit *frameCountLineEdit;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_6;
    QLineEdit *markerCountLineEdit;
    QHBoxLayout *horizontalLayout_9;
    QHBoxLayout *horizontalLayout_7;
    QSpacerItem *horizontalSpacer_5;
    QLabel *label_7;
    QSpinBox *markerFrameStartBox;
    QHBoxLayout *horizontalLayout_10;
    QSpacerItem *horizontalSpacer_6;
    QLabel *label_8;
    QSpinBox *dataStepBox;
    QHBoxLayout *horizontalLayout_6;
    QSpacerItem *horizontalSpacer_7;
    QLabel *label_9;
    QSpinBox *markerFrameStopBox;
    QHBoxLayout *horizontalLayout_8;
    QHBoxLayout *horizontalLayout_11;
    QLabel *label_10;
    QSpinBox *dataFrameBox;
    QSpacerItem *horizontalSpacer_8;
    QCheckBox *markerLoopCheckBox;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer_13;
    QToolButton *playPauseDataButton;
    QToolButton *stepDataButton;
    QSpacerItem *horizontalSpacer_14;
    QToolButton *playAllButton;
    QToolButton *stepAllButton;
    QTabWidget *controlTabWidget;
    QWidget *buttonTab;
    QVBoxLayout *verticalLayout_8;
    QPushButton *plotGraphsButton;
    QPushButton *saveButton;
    QPushButton *clearPlotButton;
    QPushButton *saveStateButton;
    QPushButton *restoreButton;
    QGroupBox *followBox;
    QVBoxLayout *verticalLayout_9;
    QRadioButton *markerRadio;
    QRadioButton *angleRadio;
    QRadioButton *altRadio;
    QRadioButton *torqueRadio;
    QSpacerItem *verticalSpacer_2;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout_7;
    QHBoxLayout *horizontalLayout_24;
    QLabel *label_13;
    QSpacerItem *horizontalSpacer;
    QHBoxLayout *horizontalLayout_22;
    QLineEdit *cmarkerFileLineEdit;
    QToolButton *cselectFileToolButton;
    QHBoxLayout *horizontalLayout_26;
    QLabel *label_14;
    QHBoxLayout *horizontalLayout_25;
    QLineEdit *cmarkerMapLineEdit;
    QToolButton *cselectMarkerMapToolButton;
    QHBoxLayout *horizontalLayout_27;
    QLabel *label_15;
    QHBoxLayout *horizontalLayout_28;
    QLineEdit *cmarkerRelPosLineEdit;
    QToolButton *cselectRelPosToolButton;
    QHBoxLayout *horizontalLayout_29;
    QLabel *label_16;
    QHBoxLayout *horizontalLayout_30;
    QLineEdit *cmodelDimLineEdit;
    QToolButton *cselectModelDimToolButton;
    QHBoxLayout *horizontalLayout_31;
    QLabel *label_17;
    QHBoxLayout *horizontalLayout_32;
    QLineEdit *cjointAnchorLineEdit;
    QToolButton *cselectjointAnchorButton;
    QHBoxLayout *horizontalLayout_36;
    QLabel *label_18;
    QHBoxLayout *horizontalLayout_35;
    QLineEdit *cDrawObjectsLineEdit;
    QToolButton *cselectDrawObjectsButton;
    QSpacerItem *verticalSpacer;
    QHBoxLayout *horizontalLayout_33;
    QPushButton *customPushButton;
    QPushButton *defaultPushButton;
    QHBoxLayout *horizontalLayout_21;
    QPushButton *runTestPushButton;
    QPushButton *stopTestPushButton;
    QMenuBar *menuBar;
    QMenu *menu_File;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1194, 932);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/icons/data/sx111.gif"), QSize(), QIcon::Normal, QIcon::Off);
        MainWindow->setWindowIcon(icon);
        MainWindow->setDockOptions(QMainWindow::AllowTabbedDocks|QMainWindow::AnimatedDocks|QMainWindow::VerticalTabs);
        actionExit = new QAction(MainWindow);
        actionExit->setObjectName(QString::fromUtf8("actionExit"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/icons/data/icons/system-exit.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionExit->setIcon(icon1);
        actionFullscreen = new QAction(MainWindow);
        actionFullscreen->setObjectName(QString::fromUtf8("actionFullscreen"));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/icons/data/icons/view-fullscreen.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionFullscreen->setIcon(icon2);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        horizontalLayout_20 = new QHBoxLayout(centralWidget);
        horizontalLayout_20->setSpacing(6);
        horizontalLayout_20->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_20->setObjectName(QString::fromUtf8("horizontalLayout_20"));
        splitter = new QSplitter(centralWidget);
        splitter->setObjectName(QString::fromUtf8("splitter"));
        splitter->setFrameShape(QFrame::NoFrame);
        splitter->setFrameShadow(QFrame::Plain);
        splitter->setLineWidth(2);
        splitter->setMidLineWidth(5);
        splitter->setOrientation(Qt::Horizontal);
        splitter->setHandleWidth(5);
        frame_2 = new QFrame(splitter);
        frame_2->setObjectName(QString::fromUtf8("frame_2"));
        frame_2->setFrameShape(QFrame::StyledPanel);
        frame_2->setFrameShadow(QFrame::Raised);
        verticalLayout_6 = new QVBoxLayout(frame_2);
        verticalLayout_6->setSpacing(0);
        verticalLayout_6->setContentsMargins(11, 11, 11, 11);
        verticalLayout_6->setObjectName(QString::fromUtf8("verticalLayout_6"));
        verticalLayout_6->setContentsMargins(2, 2, 2, 2);
        tabWidget = new QTabWidget(frame_2);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tab = new QWidget();
        tab->setObjectName(QString::fromUtf8("tab"));
        verticalLayout_3 = new QVBoxLayout(tab);
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setContentsMargins(11, 11, 11, 11);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        glWidget = new MyGLWidget(tab);
        glWidget->setObjectName(QString::fromUtf8("glWidget"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(1);
        sizePolicy.setVerticalStretch(1);
        sizePolicy.setHeightForWidth(glWidget->sizePolicy().hasHeightForWidth());
        glWidget->setSizePolicy(sizePolicy);

        verticalLayout_3->addWidget(glWidget);

        tabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QString::fromUtf8("tab_2"));
        verticalLayout_4 = new QVBoxLayout(tab_2);
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setContentsMargins(11, 11, 11, 11);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        customPlot = new QCustomPlot(tab_2);
        customPlot->setObjectName(QString::fromUtf8("customPlot"));

        verticalLayout_4->addWidget(customPlot);

        tabWidget->addTab(tab_2, QString());

        verticalLayout_6->addWidget(tabWidget);

        timeSlider = new QSlider(frame_2);
        timeSlider->setObjectName(QString::fromUtf8("timeSlider"));
        timeSlider->setOrientation(Qt::Horizontal);

        verticalLayout_6->addWidget(timeSlider);

        frame = new QFrame(frame_2);
        frame->setObjectName(QString::fromUtf8("frame"));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        horizontalLayout_19 = new QHBoxLayout(frame);
        horizontalLayout_19->setSpacing(6);
        horizontalLayout_19->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_19->setObjectName(QString::fromUtf8("horizontalLayout_19"));
        groupBox_3 = new QGroupBox(frame);
        groupBox_3->setObjectName(QString::fromUtf8("groupBox_3"));
        verticalLayout_2 = new QVBoxLayout(groupBox_3);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        horizontalLayout_16 = new QHBoxLayout();
        horizontalLayout_16->setSpacing(6);
        horizontalLayout_16->setObjectName(QString::fromUtf8("horizontalLayout_16"));
        baLabel = new QLabel(groupBox_3);
        baLabel->setObjectName(QString::fromUtf8("baLabel"));

        horizontalLayout_16->addWidget(baLabel);

        bodyAlpha = new QDoubleSpinBox(groupBox_3);
        bodyAlpha->setObjectName(QString::fromUtf8("bodyAlpha"));
        bodyAlpha->setMaximum(1.000000000000000);
        bodyAlpha->setSingleStep(0.100000000000000);
        bodyAlpha->setValue(0.500000000000000);

        horizontalLayout_16->addWidget(bodyAlpha);


        verticalLayout_2->addLayout(horizontalLayout_16);

        camFollowCheckBox = new QCheckBox(groupBox_3);
        camFollowCheckBox->setObjectName(QString::fromUtf8("camFollowCheckBox"));

        verticalLayout_2->addWidget(camFollowCheckBox);

        forceLinesCheckBox = new QCheckBox(groupBox_3);
        forceLinesCheckBox->setObjectName(QString::fromUtf8("forceLinesCheckBox"));

        verticalLayout_2->addWidget(forceLinesCheckBox);

        showMarkBox = new QCheckBox(groupBox_3);
        showMarkBox->setObjectName(QString::fromUtf8("showMarkBox"));
        showMarkBox->setChecked(true);

        verticalLayout_2->addWidget(showMarkBox);


        horizontalLayout_19->addWidget(groupBox_3);

        simulationGroupBox = new QGroupBox(frame);
        simulationGroupBox->setObjectName(QString::fromUtf8("simulationGroupBox"));
        verticalLayout_5 = new QVBoxLayout(simulationGroupBox);
        verticalLayout_5->setSpacing(2);
        verticalLayout_5->setContentsMargins(11, 11, 11, 11);
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        verticalLayout_5->setContentsMargins(2, 2, 2, 2);
        horizontalLayout_17 = new QHBoxLayout();
        horizontalLayout_17->setSpacing(6);
        horizontalLayout_17->setObjectName(QString::fromUtf8("horizontalLayout_17"));
        selfCollideBox = new QCheckBox(simulationGroupBox);
        selfCollideBox->setObjectName(QString::fromUtf8("selfCollideBox"));

        horizontalLayout_17->addWidget(selfCollideBox);

        globalBox = new QCheckBox(simulationGroupBox);
        globalBox->setObjectName(QString::fromUtf8("globalBox"));
        globalBox->setChecked(false);

        horizontalLayout_17->addWidget(globalBox);


        verticalLayout_5->addLayout(horizontalLayout_17);

        horizontalLayout_12 = new QHBoxLayout();
        horizontalLayout_12->setSpacing(6);
        horizontalLayout_12->setObjectName(QString::fromUtf8("horizontalLayout_12"));
        horizontalSpacer_12 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_12->addItem(horizontalSpacer_12);

        label_11 = new QLabel(simulationGroupBox);
        label_11->setObjectName(QString::fromUtf8("label_11"));

        horizontalLayout_12->addWidget(label_11);

        frameTimeBox = new QDoubleSpinBox(simulationGroupBox);
        frameTimeBox->setObjectName(QString::fromUtf8("frameTimeBox"));
        frameTimeBox->setDecimals(3);
        frameTimeBox->setMinimum(0.001000000000000);
        frameTimeBox->setMaximum(1.000000000000000);
        frameTimeBox->setSingleStep(0.010000000000000);
        frameTimeBox->setValue(0.015000000000000);

        horizontalLayout_12->addWidget(frameTimeBox);


        verticalLayout_5->addLayout(horizontalLayout_12);

        horizontalLayout_13 = new QHBoxLayout();
        horizontalLayout_13->setSpacing(6);
        horizontalLayout_13->setObjectName(QString::fromUtf8("horizontalLayout_13"));
        horizontalSpacer_11 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_13->addItem(horizontalSpacer_11);

        label_3 = new QLabel(simulationGroupBox);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        horizontalLayout_13->addWidget(label_3);

        terrainSpinBox = new QDoubleSpinBox(simulationGroupBox);
        terrainSpinBox->setObjectName(QString::fromUtf8("terrainSpinBox"));
        terrainSpinBox->setDecimals(6);
        terrainSpinBox->setMaximum(1.000000000000000);
        terrainSpinBox->setValue(0.000010000000000);

        horizontalLayout_13->addWidget(terrainSpinBox);


        verticalLayout_5->addLayout(horizontalLayout_13);

        horizontalLayout_14 = new QHBoxLayout();
        horizontalLayout_14->setSpacing(6);
        horizontalLayout_14->setObjectName(QString::fromUtf8("horizontalLayout_14"));
        horizontalSpacer_9 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_14->addItem(horizontalSpacer_9);

        label_2 = new QLabel(simulationGroupBox);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        horizontalLayout_14->addWidget(label_2);

        zBox = new QDoubleSpinBox(simulationGroupBox);
        zBox->setObjectName(QString::fromUtf8("zBox"));
        zBox->setDecimals(3);
        zBox->setMinimum(-99.000000000000000);
        zBox->setSingleStep(0.100000000000000);

        horizontalLayout_14->addWidget(zBox);


        verticalLayout_5->addLayout(horizontalLayout_14);

        horizontalLayout_15 = new QHBoxLayout();
        horizontalLayout_15->setSpacing(6);
        horizontalLayout_15->setObjectName(QString::fromUtf8("horizontalLayout_15"));
        horizontalSpacer_10 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_15->addItem(horizontalSpacer_10);

        label = new QLabel(simulationGroupBox);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout_15->addWidget(label);

        frictionSpinBox = new QDoubleSpinBox(simulationGroupBox);
        frictionSpinBox->setObjectName(QString::fromUtf8("frictionSpinBox"));
        frictionSpinBox->setDecimals(1);
        frictionSpinBox->setMaximum(9999.000000000000000);
        frictionSpinBox->setValue(1.000000000000000);

        horizontalLayout_15->addWidget(frictionSpinBox);


        verticalLayout_5->addLayout(horizontalLayout_15);

        horizontalLayout_18 = new QHBoxLayout();
        horizontalLayout_18->setSpacing(6);
        horizontalLayout_18->setObjectName(QString::fromUtf8("horizontalLayout_18"));
        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_18->addItem(horizontalSpacer_3);

        playPauseSimButton = new QToolButton(simulationGroupBox);
        playPauseSimButton->setObjectName(QString::fromUtf8("playPauseSimButton"));
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/icons/data/icons/media-playback-start-3.png"), QSize(), QIcon::Normal, QIcon::Off);
        playPauseSimButton->setIcon(icon3);
        playPauseSimButton->setCheckable(true);

        horizontalLayout_18->addWidget(playPauseSimButton);

        stepSimButton = new QToolButton(simulationGroupBox);
        stepSimButton->setObjectName(QString::fromUtf8("stepSimButton"));
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/icons/data/icons/media-step-right-3.png"), QSize(), QIcon::Normal, QIcon::Off);
        stepSimButton->setIcon(icon4);

        horizontalLayout_18->addWidget(stepSimButton);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_18->addItem(horizontalSpacer_4);


        verticalLayout_5->addLayout(horizontalLayout_18);


        horizontalLayout_19->addWidget(simulationGroupBox);

        markerGroupBox = new QGroupBox(frame);
        markerGroupBox->setObjectName(QString::fromUtf8("markerGroupBox"));
        verticalLayout = new QVBoxLayout(markerGroupBox);
        verticalLayout->setSpacing(2);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(2, 2, 2, 2);
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        label_4 = new QLabel(markerGroupBox);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        QSizePolicy sizePolicy1(QSizePolicy::Minimum, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(label_4->sizePolicy().hasHeightForWidth());
        label_4->setSizePolicy(sizePolicy1);
        label_4->setMinimumSize(QSize(55, 0));

        horizontalLayout_2->addWidget(label_4);

        markerFileLineEdit = new QLineEdit(markerGroupBox);
        markerFileLineEdit->setObjectName(QString::fromUtf8("markerFileLineEdit"));
        markerFileLineEdit->setEnabled(false);

        horizontalLayout_2->addWidget(markerFileLineEdit);

        selectFileToolButton = new QToolButton(markerGroupBox);
        selectFileToolButton->setObjectName(QString::fromUtf8("selectFileToolButton"));

        horizontalLayout_2->addWidget(selectFileToolButton);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        label_5 = new QLabel(markerGroupBox);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        sizePolicy1.setHeightForWidth(label_5->sizePolicy().hasHeightForWidth());
        label_5->setSizePolicy(sizePolicy1);
        label_5->setMinimumSize(QSize(65, 0));

        horizontalLayout_3->addWidget(label_5);

        frameCountLineEdit = new QLineEdit(markerGroupBox);
        frameCountLineEdit->setObjectName(QString::fromUtf8("frameCountLineEdit"));
        frameCountLineEdit->setEnabled(false);
        QSizePolicy sizePolicy2(QSizePolicy::MinimumExpanding, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(frameCountLineEdit->sizePolicy().hasHeightForWidth());
        frameCountLineEdit->setSizePolicy(sizePolicy2);
        frameCountLineEdit->setMinimumSize(QSize(30, 0));

        horizontalLayout_3->addWidget(frameCountLineEdit);


        horizontalLayout_4->addLayout(horizontalLayout_3);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        label_6 = new QLabel(markerGroupBox);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        sizePolicy1.setHeightForWidth(label_6->sizePolicy().hasHeightForWidth());
        label_6->setSizePolicy(sizePolicy1);
        label_6->setMinimumSize(QSize(65, 0));

        horizontalLayout_5->addWidget(label_6);

        markerCountLineEdit = new QLineEdit(markerGroupBox);
        markerCountLineEdit->setObjectName(QString::fromUtf8("markerCountLineEdit"));
        markerCountLineEdit->setEnabled(false);
        sizePolicy2.setHeightForWidth(markerCountLineEdit->sizePolicy().hasHeightForWidth());
        markerCountLineEdit->setSizePolicy(sizePolicy2);
        markerCountLineEdit->setMinimumSize(QSize(30, 0));

        horizontalLayout_5->addWidget(markerCountLineEdit);


        horizontalLayout_4->addLayout(horizontalLayout_5);


        verticalLayout->addLayout(horizontalLayout_4);

        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setSpacing(6);
        horizontalLayout_9->setObjectName(QString::fromUtf8("horizontalLayout_9"));
        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setSpacing(6);
        horizontalLayout_7->setObjectName(QString::fromUtf8("horizontalLayout_7"));
        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_7->addItem(horizontalSpacer_5);

        label_7 = new QLabel(markerGroupBox);
        label_7->setObjectName(QString::fromUtf8("label_7"));

        horizontalLayout_7->addWidget(label_7);

        markerFrameStartBox = new QSpinBox(markerGroupBox);
        markerFrameStartBox->setObjectName(QString::fromUtf8("markerFrameStartBox"));

        horizontalLayout_7->addWidget(markerFrameStartBox);


        horizontalLayout_9->addLayout(horizontalLayout_7);

        horizontalLayout_10 = new QHBoxLayout();
        horizontalLayout_10->setSpacing(6);
        horizontalLayout_10->setObjectName(QString::fromUtf8("horizontalLayout_10"));
        horizontalSpacer_6 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_10->addItem(horizontalSpacer_6);

        label_8 = new QLabel(markerGroupBox);
        label_8->setObjectName(QString::fromUtf8("label_8"));

        horizontalLayout_10->addWidget(label_8);

        dataStepBox = new QSpinBox(markerGroupBox);
        dataStepBox->setObjectName(QString::fromUtf8("dataStepBox"));
        dataStepBox->setMinimum(-16);
        dataStepBox->setMaximum(16);

        horizontalLayout_10->addWidget(dataStepBox);


        horizontalLayout_9->addLayout(horizontalLayout_10);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setSpacing(6);
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        horizontalSpacer_7 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_6->addItem(horizontalSpacer_7);

        label_9 = new QLabel(markerGroupBox);
        label_9->setObjectName(QString::fromUtf8("label_9"));

        horizontalLayout_6->addWidget(label_9);

        markerFrameStopBox = new QSpinBox(markerGroupBox);
        markerFrameStopBox->setObjectName(QString::fromUtf8("markerFrameStopBox"));

        horizontalLayout_6->addWidget(markerFrameStopBox);


        horizontalLayout_9->addLayout(horizontalLayout_6);


        verticalLayout->addLayout(horizontalLayout_9);

        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setSpacing(6);
        horizontalLayout_8->setObjectName(QString::fromUtf8("horizontalLayout_8"));
        horizontalLayout_11 = new QHBoxLayout();
        horizontalLayout_11->setSpacing(6);
        horizontalLayout_11->setObjectName(QString::fromUtf8("horizontalLayout_11"));
        label_10 = new QLabel(markerGroupBox);
        label_10->setObjectName(QString::fromUtf8("label_10"));

        horizontalLayout_11->addWidget(label_10);

        dataFrameBox = new QSpinBox(markerGroupBox);
        dataFrameBox->setObjectName(QString::fromUtf8("dataFrameBox"));

        horizontalLayout_11->addWidget(dataFrameBox);


        horizontalLayout_8->addLayout(horizontalLayout_11);

        horizontalSpacer_8 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_8->addItem(horizontalSpacer_8);

        markerLoopCheckBox = new QCheckBox(markerGroupBox);
        markerLoopCheckBox->setObjectName(QString::fromUtf8("markerLoopCheckBox"));

        horizontalLayout_8->addWidget(markerLoopCheckBox);


        verticalLayout->addLayout(horizontalLayout_8);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalSpacer_13 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_13);

        playPauseDataButton = new QToolButton(markerGroupBox);
        playPauseDataButton->setObjectName(QString::fromUtf8("playPauseDataButton"));
        playPauseDataButton->setIcon(icon3);
        playPauseDataButton->setCheckable(true);

        horizontalLayout->addWidget(playPauseDataButton);

        stepDataButton = new QToolButton(markerGroupBox);
        stepDataButton->setObjectName(QString::fromUtf8("stepDataButton"));
        stepDataButton->setIcon(icon4);

        horizontalLayout->addWidget(stepDataButton);

        horizontalSpacer_14 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_14);


        verticalLayout->addLayout(horizontalLayout);


        horizontalLayout_19->addWidget(markerGroupBox);

        playAllButton = new QToolButton(frame);
        playAllButton->setObjectName(QString::fromUtf8("playAllButton"));
        QIcon icon5;
        icon5.addFile(QString::fromUtf8(":/icons/data/icons/media-playback-large.png"), QSize(), QIcon::Normal, QIcon::Off);
        playAllButton->setIcon(icon5);
        playAllButton->setIconSize(QSize(32, 32));
        playAllButton->setCheckable(true);

        horizontalLayout_19->addWidget(playAllButton);

        stepAllButton = new QToolButton(frame);
        stepAllButton->setObjectName(QString::fromUtf8("stepAllButton"));
        stepAllButton->setIcon(icon4);
        stepAllButton->setIconSize(QSize(32, 32));
        stepAllButton->setToolButtonStyle(Qt::ToolButtonIconOnly);
        stepAllButton->setAutoRaise(false);

        horizontalLayout_19->addWidget(stepAllButton);

        stepAllButton->raise();
        groupBox_3->raise();
        playAllButton->raise();
        simulationGroupBox->raise();
        markerGroupBox->raise();

        verticalLayout_6->addWidget(frame);

        verticalLayout_6->setStretch(0, 1);
        splitter->addWidget(frame_2);
        timeSlider->raise();
        frame->raise();
        tabWidget->raise();
        controlTabWidget = new QTabWidget(splitter);
        controlTabWidget->setObjectName(QString::fromUtf8("controlTabWidget"));
        controlTabWidget->setTabPosition(QTabWidget::East);
        buttonTab = new QWidget();
        buttonTab->setObjectName(QString::fromUtf8("buttonTab"));
        verticalLayout_8 = new QVBoxLayout(buttonTab);
        verticalLayout_8->setSpacing(6);
        verticalLayout_8->setContentsMargins(11, 11, 11, 11);
        verticalLayout_8->setObjectName(QString::fromUtf8("verticalLayout_8"));
        plotGraphsButton = new QPushButton(buttonTab);
        plotGraphsButton->setObjectName(QString::fromUtf8("plotGraphsButton"));

        verticalLayout_8->addWidget(plotGraphsButton);

        saveButton = new QPushButton(buttonTab);
        saveButton->setObjectName(QString::fromUtf8("saveButton"));

        verticalLayout_8->addWidget(saveButton);

        clearPlotButton = new QPushButton(buttonTab);
        clearPlotButton->setObjectName(QString::fromUtf8("clearPlotButton"));

        verticalLayout_8->addWidget(clearPlotButton);

        saveStateButton = new QPushButton(buttonTab);
        saveStateButton->setObjectName(QString::fromUtf8("saveStateButton"));

        verticalLayout_8->addWidget(saveStateButton);

        restoreButton = new QPushButton(buttonTab);
        restoreButton->setObjectName(QString::fromUtf8("restoreButton"));

        verticalLayout_8->addWidget(restoreButton);

        followBox = new QGroupBox(buttonTab);
        followBox->setObjectName(QString::fromUtf8("followBox"));
        verticalLayout_9 = new QVBoxLayout(followBox);
        verticalLayout_9->setSpacing(6);
        verticalLayout_9->setContentsMargins(11, 11, 11, 11);
        verticalLayout_9->setObjectName(QString::fromUtf8("verticalLayout_9"));
        markerRadio = new QRadioButton(followBox);
        markerRadio->setObjectName(QString::fromUtf8("markerRadio"));
        markerRadio->setChecked(true);

        verticalLayout_9->addWidget(markerRadio);

        angleRadio = new QRadioButton(followBox);
        angleRadio->setObjectName(QString::fromUtf8("angleRadio"));

        verticalLayout_9->addWidget(angleRadio);

        altRadio = new QRadioButton(followBox);
        altRadio->setObjectName(QString::fromUtf8("altRadio"));

        verticalLayout_9->addWidget(altRadio);

        torqueRadio = new QRadioButton(followBox);
        torqueRadio->setObjectName(QString::fromUtf8("torqueRadio"));

        verticalLayout_9->addWidget(torqueRadio);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_9->addItem(verticalSpacer_2);


        verticalLayout_8->addWidget(followBox);

        groupBox = new QGroupBox(buttonTab);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        verticalLayout_7 = new QVBoxLayout(groupBox);
        verticalLayout_7->setSpacing(6);
        verticalLayout_7->setContentsMargins(11, 11, 11, 11);
        verticalLayout_7->setObjectName(QString::fromUtf8("verticalLayout_7"));
        horizontalLayout_24 = new QHBoxLayout();
        horizontalLayout_24->setSpacing(6);
        horizontalLayout_24->setObjectName(QString::fromUtf8("horizontalLayout_24"));
        label_13 = new QLabel(groupBox);
        label_13->setObjectName(QString::fromUtf8("label_13"));
        sizePolicy1.setHeightForWidth(label_13->sizePolicy().hasHeightForWidth());
        label_13->setSizePolicy(sizePolicy1);
        label_13->setMinimumSize(QSize(55, 0));

        horizontalLayout_24->addWidget(label_13);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_24->addItem(horizontalSpacer);


        verticalLayout_7->addLayout(horizontalLayout_24);

        horizontalLayout_22 = new QHBoxLayout();
        horizontalLayout_22->setSpacing(6);
        horizontalLayout_22->setObjectName(QString::fromUtf8("horizontalLayout_22"));
        cmarkerFileLineEdit = new QLineEdit(groupBox);
        cmarkerFileLineEdit->setObjectName(QString::fromUtf8("cmarkerFileLineEdit"));
        cmarkerFileLineEdit->setEnabled(false);

        horizontalLayout_22->addWidget(cmarkerFileLineEdit);

        cselectFileToolButton = new QToolButton(groupBox);
        cselectFileToolButton->setObjectName(QString::fromUtf8("cselectFileToolButton"));

        horizontalLayout_22->addWidget(cselectFileToolButton);


        verticalLayout_7->addLayout(horizontalLayout_22);

        horizontalLayout_26 = new QHBoxLayout();
        horizontalLayout_26->setSpacing(6);
        horizontalLayout_26->setObjectName(QString::fromUtf8("horizontalLayout_26"));
        label_14 = new QLabel(groupBox);
        label_14->setObjectName(QString::fromUtf8("label_14"));
        sizePolicy1.setHeightForWidth(label_14->sizePolicy().hasHeightForWidth());
        label_14->setSizePolicy(sizePolicy1);
        label_14->setMinimumSize(QSize(55, 0));

        horizontalLayout_26->addWidget(label_14);


        verticalLayout_7->addLayout(horizontalLayout_26);

        horizontalLayout_25 = new QHBoxLayout();
        horizontalLayout_25->setSpacing(6);
        horizontalLayout_25->setObjectName(QString::fromUtf8("horizontalLayout_25"));
        cmarkerMapLineEdit = new QLineEdit(groupBox);
        cmarkerMapLineEdit->setObjectName(QString::fromUtf8("cmarkerMapLineEdit"));
        cmarkerMapLineEdit->setEnabled(false);

        horizontalLayout_25->addWidget(cmarkerMapLineEdit);

        cselectMarkerMapToolButton = new QToolButton(groupBox);
        cselectMarkerMapToolButton->setObjectName(QString::fromUtf8("cselectMarkerMapToolButton"));

        horizontalLayout_25->addWidget(cselectMarkerMapToolButton);


        verticalLayout_7->addLayout(horizontalLayout_25);

        horizontalLayout_27 = new QHBoxLayout();
        horizontalLayout_27->setSpacing(6);
        horizontalLayout_27->setObjectName(QString::fromUtf8("horizontalLayout_27"));
        label_15 = new QLabel(groupBox);
        label_15->setObjectName(QString::fromUtf8("label_15"));
        sizePolicy1.setHeightForWidth(label_15->sizePolicy().hasHeightForWidth());
        label_15->setSizePolicy(sizePolicy1);
        label_15->setMinimumSize(QSize(55, 0));

        horizontalLayout_27->addWidget(label_15);


        verticalLayout_7->addLayout(horizontalLayout_27);

        horizontalLayout_28 = new QHBoxLayout();
        horizontalLayout_28->setSpacing(6);
        horizontalLayout_28->setObjectName(QString::fromUtf8("horizontalLayout_28"));
        cmarkerRelPosLineEdit = new QLineEdit(groupBox);
        cmarkerRelPosLineEdit->setObjectName(QString::fromUtf8("cmarkerRelPosLineEdit"));
        cmarkerRelPosLineEdit->setEnabled(false);

        horizontalLayout_28->addWidget(cmarkerRelPosLineEdit);

        cselectRelPosToolButton = new QToolButton(groupBox);
        cselectRelPosToolButton->setObjectName(QString::fromUtf8("cselectRelPosToolButton"));

        horizontalLayout_28->addWidget(cselectRelPosToolButton);


        verticalLayout_7->addLayout(horizontalLayout_28);

        horizontalLayout_29 = new QHBoxLayout();
        horizontalLayout_29->setSpacing(6);
        horizontalLayout_29->setObjectName(QString::fromUtf8("horizontalLayout_29"));
        label_16 = new QLabel(groupBox);
        label_16->setObjectName(QString::fromUtf8("label_16"));
        sizePolicy1.setHeightForWidth(label_16->sizePolicy().hasHeightForWidth());
        label_16->setSizePolicy(sizePolicy1);
        label_16->setMinimumSize(QSize(55, 0));

        horizontalLayout_29->addWidget(label_16);


        verticalLayout_7->addLayout(horizontalLayout_29);

        horizontalLayout_30 = new QHBoxLayout();
        horizontalLayout_30->setSpacing(6);
        horizontalLayout_30->setObjectName(QString::fromUtf8("horizontalLayout_30"));
        cmodelDimLineEdit = new QLineEdit(groupBox);
        cmodelDimLineEdit->setObjectName(QString::fromUtf8("cmodelDimLineEdit"));
        cmodelDimLineEdit->setEnabled(false);

        horizontalLayout_30->addWidget(cmodelDimLineEdit);

        cselectModelDimToolButton = new QToolButton(groupBox);
        cselectModelDimToolButton->setObjectName(QString::fromUtf8("cselectModelDimToolButton"));

        horizontalLayout_30->addWidget(cselectModelDimToolButton);


        verticalLayout_7->addLayout(horizontalLayout_30);

        horizontalLayout_31 = new QHBoxLayout();
        horizontalLayout_31->setSpacing(6);
        horizontalLayout_31->setObjectName(QString::fromUtf8("horizontalLayout_31"));
        label_17 = new QLabel(groupBox);
        label_17->setObjectName(QString::fromUtf8("label_17"));
        sizePolicy1.setHeightForWidth(label_17->sizePolicy().hasHeightForWidth());
        label_17->setSizePolicy(sizePolicy1);
        label_17->setMinimumSize(QSize(55, 0));

        horizontalLayout_31->addWidget(label_17);


        verticalLayout_7->addLayout(horizontalLayout_31);

        horizontalLayout_32 = new QHBoxLayout();
        horizontalLayout_32->setSpacing(6);
        horizontalLayout_32->setObjectName(QString::fromUtf8("horizontalLayout_32"));
        cjointAnchorLineEdit = new QLineEdit(groupBox);
        cjointAnchorLineEdit->setObjectName(QString::fromUtf8("cjointAnchorLineEdit"));
        cjointAnchorLineEdit->setEnabled(false);

        horizontalLayout_32->addWidget(cjointAnchorLineEdit);

        cselectjointAnchorButton = new QToolButton(groupBox);
        cselectjointAnchorButton->setObjectName(QString::fromUtf8("cselectjointAnchorButton"));

        horizontalLayout_32->addWidget(cselectjointAnchorButton);


        verticalLayout_7->addLayout(horizontalLayout_32);

        horizontalLayout_36 = new QHBoxLayout();
        horizontalLayout_36->setSpacing(6);
        horizontalLayout_36->setObjectName(QString::fromUtf8("horizontalLayout_36"));
        label_18 = new QLabel(groupBox);
        label_18->setObjectName(QString::fromUtf8("label_18"));
        sizePolicy1.setHeightForWidth(label_18->sizePolicy().hasHeightForWidth());
        label_18->setSizePolicy(sizePolicy1);
        label_18->setMinimumSize(QSize(55, 0));

        horizontalLayout_36->addWidget(label_18);


        verticalLayout_7->addLayout(horizontalLayout_36);

        horizontalLayout_35 = new QHBoxLayout();
        horizontalLayout_35->setSpacing(6);
        horizontalLayout_35->setObjectName(QString::fromUtf8("horizontalLayout_35"));
        cDrawObjectsLineEdit = new QLineEdit(groupBox);
        cDrawObjectsLineEdit->setObjectName(QString::fromUtf8("cDrawObjectsLineEdit"));
        cDrawObjectsLineEdit->setEnabled(false);

        horizontalLayout_35->addWidget(cDrawObjectsLineEdit);

        cselectDrawObjectsButton = new QToolButton(groupBox);
        cselectDrawObjectsButton->setObjectName(QString::fromUtf8("cselectDrawObjectsButton"));

        horizontalLayout_35->addWidget(cselectDrawObjectsButton);


        verticalLayout_7->addLayout(horizontalLayout_35);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_7->addItem(verticalSpacer);

        horizontalLayout_33 = new QHBoxLayout();
        horizontalLayout_33->setSpacing(6);
        horizontalLayout_33->setObjectName(QString::fromUtf8("horizontalLayout_33"));
        customPushButton = new QPushButton(groupBox);
        customPushButton->setObjectName(QString::fromUtf8("customPushButton"));

        horizontalLayout_33->addWidget(customPushButton);

        defaultPushButton = new QPushButton(groupBox);
        defaultPushButton->setObjectName(QString::fromUtf8("defaultPushButton"));

        horizontalLayout_33->addWidget(defaultPushButton);


        verticalLayout_7->addLayout(horizontalLayout_33);


        verticalLayout_8->addWidget(groupBox);

        horizontalLayout_21 = new QHBoxLayout();
        horizontalLayout_21->setSpacing(6);
        horizontalLayout_21->setObjectName(QString::fromUtf8("horizontalLayout_21"));
        runTestPushButton = new QPushButton(buttonTab);
        runTestPushButton->setObjectName(QString::fromUtf8("runTestPushButton"));

        horizontalLayout_21->addWidget(runTestPushButton);

        stopTestPushButton = new QPushButton(buttonTab);
        stopTestPushButton->setObjectName(QString::fromUtf8("stopTestPushButton"));

        horizontalLayout_21->addWidget(stopTestPushButton);


        verticalLayout_8->addLayout(horizontalLayout_21);

        controlTabWidget->addTab(buttonTab, QString());
        splitter->addWidget(controlTabWidget);

        horizontalLayout_20->addWidget(splitter);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1194, 22));
        menu_File = new QMenu(menuBar);
        menu_File->setObjectName(QString::fromUtf8("menu_File"));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        statusBar->setSizeGripEnabled(true);
        MainWindow->setStatusBar(statusBar);

        menuBar->addAction(menu_File->menuAction());
        menu_File->addAction(actionExit);
        mainToolBar->addAction(actionExit);
        mainToolBar->addAction(actionFullscreen);

        retranslateUi(MainWindow);

        tabWidget->setCurrentIndex(0);
        controlTabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "Qt VR App", nullptr));
        actionExit->setText(QApplication::translate("MainWindow", "E&xit", nullptr));
#ifndef QT_NO_SHORTCUT
        actionExit->setShortcut(QApplication::translate("MainWindow", "Ctrl+X", nullptr));
#endif // QT_NO_SHORTCUT
        actionFullscreen->setText(QApplication::translate("MainWindow", "Fullscreen", nullptr));
#ifndef QT_NO_TOOLTIP
        actionFullscreen->setToolTip(QApplication::translate("MainWindow", "Toggle fullscreen mode", nullptr));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_SHORTCUT
        actionFullscreen->setShortcut(QApplication::translate("MainWindow", "Ctrl+F", nullptr));
#endif // QT_NO_SHORTCUT
        tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("MainWindow", "3d View", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QApplication::translate("MainWindow", "Graphs", nullptr));
#ifndef QT_NO_TOOLTIP
        timeSlider->setToolTip(QApplication::translate("MainWindow", "Shows progression through the recorded marker data", nullptr));
#endif // QT_NO_TOOLTIP
        groupBox_3->setTitle(QApplication::translate("MainWindow", "Display", nullptr));
        baLabel->setText(QApplication::translate("MainWindow", "Model Alpha", nullptr));
#ifndef QT_NO_TOOLTIP
        bodyAlpha->setToolTip(QApplication::translate("MainWindow", "Transparency used when rendering the body: allows you to see the markers through the body.", nullptr));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_TOOLTIP
        camFollowCheckBox->setToolTip(QApplication::translate("MainWindow", "When checked, the camera follows the character's head.", nullptr));
#endif // QT_NO_TOOLTIP
        camFollowCheckBox->setText(QApplication::translate("MainWindow", "Camera Follows Model", nullptr));
#ifndef QT_NO_TOOLTIP
        forceLinesCheckBox->setToolTip(QApplication::translate("MainWindow", "When checked, lines are rendered showing the magnitude of certain forces", nullptr));
#endif // QT_NO_TOOLTIP
        forceLinesCheckBox->setText(QApplication::translate("MainWindow", "Force Lines", nullptr));
#ifndef QT_NO_TOOLTIP
        showMarkBox->setToolTip(QApplication::translate("MainWindow", "Show the locations of the markers", nullptr));
#endif // QT_NO_TOOLTIP
        showMarkBox->setText(QApplication::translate("MainWindow", "Show Markers", nullptr));
        simulationGroupBox->setTitle(QApplication::translate("MainWindow", "Simulation", nullptr));
#ifndef QT_NO_TOOLTIP
        selfCollideBox->setToolTip(QApplication::translate("MainWindow", "When checked, the simulated body collides with itself as well as with the ground", nullptr));
#endif // QT_NO_TOOLTIP
        selfCollideBox->setText(QApplication::translate("MainWindow", "Self-collide Model", nullptr));
#ifndef QT_NO_TOOLTIP
        globalBox->setToolTip(QApplication::translate("MainWindow", "Use global forces for inverse dynamics and forward dynamics (as opposed to internal generalized coordinate forces)", nullptr));
#endif // QT_NO_TOOLTIP
        globalBox->setText(QApplication::translate("MainWindow", "Global force", nullptr));
        label_11->setText(QApplication::translate("MainWindow", "Timestep", nullptr));
#ifndef QT_NO_TOOLTIP
        frameTimeBox->setToolTip(QApplication::translate("MainWindow", "Sim Time per Step", nullptr));
#endif // QT_NO_TOOLTIP
        frameTimeBox->setSuffix(QApplication::translate("MainWindow", "ms", nullptr));
        label_3->setText(QApplication::translate("MainWindow", "Ground Soft", nullptr));
#ifndef QT_NO_TOOLTIP
        terrainSpinBox->setToolTip(QApplication::translate("MainWindow", "Larger numbers make the ground \"softer\"", nullptr));
#endif // QT_NO_TOOLTIP
        label_2->setText(QApplication::translate("MainWindow", "Ground CFM", nullptr));
#ifndef QT_NO_TOOLTIP
        zBox->setToolTip(QApplication::translate("MainWindow", "Height adjustment of the ground level (used to raise the terrain when capture data come from treadmill walking)", nullptr));
#endif // QT_NO_TOOLTIP
        label->setText(QApplication::translate("MainWindow", "Ground Friction", nullptr));
#ifndef QT_NO_TOOLTIP
        frictionSpinBox->setToolTip(QApplication::translate("MainWindow", "Friction force applied to ground contacts (proportional to normal force)", nullptr));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_TOOLTIP
        playPauseSimButton->setToolTip(QApplication::translate("MainWindow", "Play/Pause Sim", nullptr));
#endif // QT_NO_TOOLTIP
        playPauseSimButton->setText(QApplication::translate("MainWindow", "Play/Pause Sim", nullptr));
#ifndef QT_NO_TOOLTIP
        stepSimButton->setToolTip(QApplication::translate("MainWindow", "Step Sim", nullptr));
#endif // QT_NO_TOOLTIP
        stepSimButton->setText(QApplication::translate("MainWindow", "Step Sim", nullptr));
        markerGroupBox->setTitle(QApplication::translate("MainWindow", "Marker Data", nullptr));
        label_4->setText(QApplication::translate("MainWindow", "Marker File", nullptr));
#ifndef QT_NO_TOOLTIP
        selectFileToolButton->setToolTip(QApplication::translate("MainWindow", "Load a new file of marker data", nullptr));
#endif // QT_NO_TOOLTIP
        selectFileToolButton->setText(QApplication::translate("MainWindow", "...", nullptr));
        label_5->setText(QApplication::translate("MainWindow", "Frame Count", nullptr));
        frameCountLineEdit->setText(QString());
        label_6->setText(QApplication::translate("MainWindow", "Marker Count", nullptr));
        label_7->setText(QApplication::translate("MainWindow", "Start", nullptr));
        label_8->setText(QApplication::translate("MainWindow", "Step", nullptr));
#ifndef QT_NO_TOOLTIP
        dataStepBox->setToolTip(QApplication::translate("MainWindow", "Frames per step", nullptr));
#endif // QT_NO_TOOLTIP
        label_9->setText(QApplication::translate("MainWindow", "Stop", nullptr));
        label_10->setText(QApplication::translate("MainWindow", "Current Frame", nullptr));
#ifndef QT_NO_TOOLTIP
        dataFrameBox->setToolTip(QApplication::translate("MainWindow", "Current frame in the marker data", nullptr));
#endif // QT_NO_TOOLTIP
        markerLoopCheckBox->setText(QApplication::translate("MainWindow", "Loop", nullptr));
        playPauseDataButton->setText(QApplication::translate("MainWindow", "Play/Pause Data", nullptr));
#ifndef QT_NO_TOOLTIP
        stepDataButton->setToolTip(QApplication::translate("MainWindow", "Step Sim", nullptr));
#endif // QT_NO_TOOLTIP
        stepDataButton->setText(QApplication::translate("MainWindow", "Step Sim", nullptr));
#ifndef QT_NO_TOOLTIP
        playAllButton->setToolTip(QApplication::translate("MainWindow", "Play/Pause All", nullptr));
#endif // QT_NO_TOOLTIP
        playAllButton->setText(QApplication::translate("MainWindow", "...", nullptr));
#ifndef QT_NO_TOOLTIP
        stepAllButton->setToolTip(QApplication::translate("MainWindow", "Step All", nullptr));
#endif // QT_NO_TOOLTIP
        stepAllButton->setText(QApplication::translate("MainWindow", "Step Sim", nullptr));
        plotGraphsButton->setText(QApplication::translate("MainWindow", "Plot Graphs", nullptr));
        saveButton->setText(QApplication::translate("MainWindow", "Save Model Data", nullptr));
        clearPlotButton->setText(QApplication::translate("MainWindow", "Clear Saved Angles", nullptr));
        saveStateButton->setText(QApplication::translate("MainWindow", "Save Model State", nullptr));
        restoreButton->setText(QApplication::translate("MainWindow", "Restore Model State", nullptr));
        followBox->setTitle(QString());
        markerRadio->setText(QApplication::translate("MainWindow", "Markers (IK)", nullptr));
        angleRadio->setText(QApplication::translate("MainWindow", "Angle (FK)", nullptr));
        altRadio->setText(QApplication::translate("MainWindow", "Alt Angle (ID)", nullptr));
        torqueRadio->setText(QApplication::translate("MainWindow", "Torques (FD)", nullptr));
        groupBox->setTitle(QApplication::translate("MainWindow", "Custom Settings", nullptr));
        label_13->setText(QApplication::translate("MainWindow", "Marker file", nullptr));
#ifndef QT_NO_TOOLTIP
        cselectFileToolButton->setToolTip(QApplication::translate("MainWindow", "Load a new file of marker data", nullptr));
#endif // QT_NO_TOOLTIP
        cselectFileToolButton->setText(QApplication::translate("MainWindow", "...", nullptr));
        label_14->setText(QApplication::translate("MainWindow", "Marker Map", nullptr));
#ifndef QT_NO_TOOLTIP
        cselectMarkerMapToolButton->setToolTip(QApplication::translate("MainWindow", "Load a new file of marker data", nullptr));
#endif // QT_NO_TOOLTIP
        cselectMarkerMapToolButton->setText(QApplication::translate("MainWindow", "...", nullptr));
        label_15->setText(QApplication::translate("MainWindow", "Marker RelPositon", nullptr));
#ifndef QT_NO_TOOLTIP
        cselectRelPosToolButton->setToolTip(QApplication::translate("MainWindow", "Load a new file of marker data", nullptr));
#endif // QT_NO_TOOLTIP
        cselectRelPosToolButton->setText(QApplication::translate("MainWindow", "...", nullptr));
        label_16->setText(QApplication::translate("MainWindow", "Model Dimemsion", nullptr));
#ifndef QT_NO_TOOLTIP
        cselectModelDimToolButton->setToolTip(QApplication::translate("MainWindow", "Load a new file of marker data", nullptr));
#endif // QT_NO_TOOLTIP
        cselectModelDimToolButton->setText(QApplication::translate("MainWindow", "...", nullptr));
        label_17->setText(QApplication::translate("MainWindow", "Joint Anchor", nullptr));
#ifndef QT_NO_TOOLTIP
        cselectjointAnchorButton->setToolTip(QApplication::translate("MainWindow", "Load a new file of marker data", nullptr));
#endif // QT_NO_TOOLTIP
        cselectjointAnchorButton->setText(QApplication::translate("MainWindow", "...", nullptr));
        label_18->setText(QApplication::translate("MainWindow", "Draw Objects", nullptr));
#ifndef QT_NO_TOOLTIP
        cselectDrawObjectsButton->setToolTip(QApplication::translate("MainWindow", "Load a new file of marker data", nullptr));
#endif // QT_NO_TOOLTIP
        cselectDrawObjectsButton->setText(QApplication::translate("MainWindow", "...", nullptr));
        customPushButton->setText(QApplication::translate("MainWindow", "Custom", nullptr));
        defaultPushButton->setText(QApplication::translate("MainWindow", "Default", nullptr));
        runTestPushButton->setText(QApplication::translate("MainWindow", "Run Test", nullptr));
        stopTestPushButton->setText(QApplication::translate("MainWindow", "Stop Test", nullptr));
        controlTabWidget->setTabText(controlTabWidget->indexOf(buttonTab), QApplication::translate("MainWindow", "Buttons", nullptr));
        menu_File->setTitle(QApplication::translate("MainWindow", "&File", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H

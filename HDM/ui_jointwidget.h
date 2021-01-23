/********************************************************************************
** Form generated from reading UI file 'jointwidget.ui'
**
** Created by: Qt User Interface Compiler version 5.12.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_JOINTWIDGET_H
#define UI_JOINTWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSlider>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_JointWidget
{
public:
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QDoubleSpinBox *angleSpinBox;
    QSlider *angleSlider;
    QDoubleSpinBox *fmaxSpinBox;

    void setupUi(QWidget *JointWidget)
    {
        if (JointWidget->objectName().isEmpty())
            JointWidget->setObjectName(QString::fromUtf8("JointWidget"));
        JointWidget->resize(250, 22);
        horizontalLayout = new QHBoxLayout(JointWidget);
        horizontalLayout->setSpacing(2);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(2, 0, 2, 0);
        label = new QLabel(JointWidget);
        label->setObjectName(QString::fromUtf8("label"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy);
        label->setMinimumSize(QSize(80, 0));

        horizontalLayout->addWidget(label);

        angleSpinBox = new QDoubleSpinBox(JointWidget);
        angleSpinBox->setObjectName(QString::fromUtf8("angleSpinBox"));
        angleSpinBox->setMinimum(-3.140000000000000);
        angleSpinBox->setMaximum(3.140000000000000);
        angleSpinBox->setSingleStep(0.010000000000000);

        horizontalLayout->addWidget(angleSpinBox);

        angleSlider = new QSlider(JointWidget);
        angleSlider->setObjectName(QString::fromUtf8("angleSlider"));
        angleSlider->setMinimum(-10000);
        angleSlider->setMaximum(10000);
        angleSlider->setOrientation(Qt::Horizontal);

        horizontalLayout->addWidget(angleSlider);

        fmaxSpinBox = new QDoubleSpinBox(JointWidget);
        fmaxSpinBox->setObjectName(QString::fromUtf8("fmaxSpinBox"));
        fmaxSpinBox->setMaximum(9999.000000000000000);
        fmaxSpinBox->setValue(250.000000000000000);

        horizontalLayout->addWidget(fmaxSpinBox);


        retranslateUi(JointWidget);
        QObject::connect(angleSlider, SIGNAL(valueChanged(int)), JointWidget, SLOT(intToAngleSpinBox(int)));
        QObject::connect(angleSpinBox, SIGNAL(valueChanged(double)), JointWidget, SLOT(doubleToAngleSlider(double)));

        QMetaObject::connectSlotsByName(JointWidget);
    } // setupUi

    void retranslateUi(QWidget *JointWidget)
    {
        JointWidget->setWindowTitle(QApplication::translate("JointWidget", "Form", nullptr));
        label->setText(QApplication::translate("JointWidget", "TextLabel", nullptr));
#ifndef QT_NO_TOOLTIP
        angleSpinBox->setToolTip(QApplication::translate("JointWidget", "The desired angle.", nullptr));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_TOOLTIP
        angleSlider->setToolTip(QApplication::translate("JointWidget", "Analog control of the angle.", nullptr));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_TOOLTIP
        fmaxSpinBox->setToolTip(QApplication::translate("JointWidget", "Maximum force used to achieve the desired angle.", nullptr));
#endif // QT_NO_TOOLTIP
    } // retranslateUi

};

namespace Ui {
    class JointWidget: public Ui_JointWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_JOINTWIDGET_H

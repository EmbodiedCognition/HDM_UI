/********************************************************************************
** Form generated from reading UI file 'markerwidget.ui'
**
** Created by: Qt User Interface Compiler version 5.12.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MARKERWIDGET_H
#define UI_MARKERWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MarkerWidget
{
public:
    QHBoxLayout *horizontalLayout;
    QPushButton *idButton;
    QComboBox *bodyComboBox;
    QDoubleSpinBox *xSpinBox;
    QDoubleSpinBox *ySpinBox;
    QDoubleSpinBox *zSpinBox;
    QToolButton *grabButton;

    void setupUi(QWidget *MarkerWidget)
    {
        if (MarkerWidget->objectName().isEmpty())
            MarkerWidget->setObjectName(QString::fromUtf8("MarkerWidget"));
        MarkerWidget->resize(333, 24);
        horizontalLayout = new QHBoxLayout(MarkerWidget);
        horizontalLayout->setSpacing(2);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(2, 0, 2, 0);
        idButton = new QPushButton(MarkerWidget);
        idButton->setObjectName(QString::fromUtf8("idButton"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(idButton->sizePolicy().hasHeightForWidth());
        idButton->setSizePolicy(sizePolicy);
        idButton->setMaximumSize(QSize(30, 16777215));
        idButton->setCheckable(true);

        horizontalLayout->addWidget(idButton);

        bodyComboBox = new QComboBox(MarkerWidget);
        bodyComboBox->addItem(QString());
        bodyComboBox->addItem(QString());
        bodyComboBox->addItem(QString());
        bodyComboBox->addItem(QString());
        bodyComboBox->addItem(QString());
        bodyComboBox->addItem(QString());
        bodyComboBox->addItem(QString());
        bodyComboBox->addItem(QString());
        bodyComboBox->addItem(QString());
        bodyComboBox->addItem(QString());
        bodyComboBox->addItem(QString());
        bodyComboBox->addItem(QString());
        bodyComboBox->addItem(QString());
        bodyComboBox->addItem(QString());
        bodyComboBox->addItem(QString());
        bodyComboBox->addItem(QString());
        bodyComboBox->addItem(QString());
        bodyComboBox->addItem(QString());
        bodyComboBox->addItem(QString());
        bodyComboBox->addItem(QString());
        bodyComboBox->addItem(QString());
        bodyComboBox->addItem(QString());
        bodyComboBox->setObjectName(QString::fromUtf8("bodyComboBox"));

        horizontalLayout->addWidget(bodyComboBox);

        xSpinBox = new QDoubleSpinBox(MarkerWidget);
        xSpinBox->setObjectName(QString::fromUtf8("xSpinBox"));
        QSizePolicy sizePolicy1(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(1);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(xSpinBox->sizePolicy().hasHeightForWidth());
        xSpinBox->setSizePolicy(sizePolicy1);
        xSpinBox->setDecimals(4);
        xSpinBox->setMinimum(-1.000000000000000);
        xSpinBox->setMaximum(1.000000000000000);
        xSpinBox->setSingleStep(0.010000000000000);

        horizontalLayout->addWidget(xSpinBox);

        ySpinBox = new QDoubleSpinBox(MarkerWidget);
        ySpinBox->setObjectName(QString::fromUtf8("ySpinBox"));
        sizePolicy1.setHeightForWidth(ySpinBox->sizePolicy().hasHeightForWidth());
        ySpinBox->setSizePolicy(sizePolicy1);
        ySpinBox->setDecimals(4);
        ySpinBox->setMinimum(-1.000000000000000);
        ySpinBox->setMaximum(1.000000000000000);
        ySpinBox->setSingleStep(0.010000000000000);

        horizontalLayout->addWidget(ySpinBox);

        zSpinBox = new QDoubleSpinBox(MarkerWidget);
        zSpinBox->setObjectName(QString::fromUtf8("zSpinBox"));
        sizePolicy1.setHeightForWidth(zSpinBox->sizePolicy().hasHeightForWidth());
        zSpinBox->setSizePolicy(sizePolicy1);
        zSpinBox->setDecimals(4);
        zSpinBox->setMinimum(-1.000000000000000);
        zSpinBox->setMaximum(1.000000000000000);
        zSpinBox->setSingleStep(0.010000000000000);

        horizontalLayout->addWidget(zSpinBox);

        grabButton = new QToolButton(MarkerWidget);
        grabButton->setObjectName(QString::fromUtf8("grabButton"));

        horizontalLayout->addWidget(grabButton);


        retranslateUi(MarkerWidget);

        bodyComboBox->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MarkerWidget);
    } // setupUi

    void retranslateUi(QWidget *MarkerWidget)
    {
        MarkerWidget->setWindowTitle(QApplication::translate("MarkerWidget", "Form", nullptr));
        idButton->setText(QApplication::translate("MarkerWidget", "#", nullptr));
        bodyComboBox->setItemText(0, QApplication::translate("MarkerWidget", "None", nullptr));
        bodyComboBox->setItemText(1, QApplication::translate("MarkerWidget", "Head", nullptr));
        bodyComboBox->setItemText(2, QApplication::translate("MarkerWidget", "Neck", nullptr));
        bodyComboBox->setItemText(3, QApplication::translate("MarkerWidget", "Up Torso", nullptr));
        bodyComboBox->setItemText(4, QApplication::translate("MarkerWidget", "R. Collar", nullptr));
        bodyComboBox->setItemText(5, QApplication::translate("MarkerWidget", "R. Up Arm", nullptr));
        bodyComboBox->setItemText(6, QApplication::translate("MarkerWidget", "R. Lo Arm", nullptr));
        bodyComboBox->setItemText(7, QApplication::translate("MarkerWidget", "R. Hand", nullptr));
        bodyComboBox->setItemText(8, QApplication::translate("MarkerWidget", "L. Collar", nullptr));
        bodyComboBox->setItemText(9, QApplication::translate("MarkerWidget", "L. Up Arm", nullptr));
        bodyComboBox->setItemText(10, QApplication::translate("MarkerWidget", "L. Lo Arm", nullptr));
        bodyComboBox->setItemText(11, QApplication::translate("MarkerWidget", "L. Hand", nullptr));
        bodyComboBox->setItemText(12, QApplication::translate("MarkerWidget", "Lo Torso", nullptr));
        bodyComboBox->setItemText(13, QApplication::translate("MarkerWidget", "Waist", nullptr));
        bodyComboBox->setItemText(14, QApplication::translate("MarkerWidget", "R. Up Leg", nullptr));
        bodyComboBox->setItemText(15, QApplication::translate("MarkerWidget", "R. Lo Leg", nullptr));
        bodyComboBox->setItemText(16, QApplication::translate("MarkerWidget", "R. Heel", nullptr));
        bodyComboBox->setItemText(17, QApplication::translate("MarkerWidget", "R. Toe", nullptr));
        bodyComboBox->setItemText(18, QApplication::translate("MarkerWidget", "L. Up Leg", nullptr));
        bodyComboBox->setItemText(19, QApplication::translate("MarkerWidget", "L. Lo Leg", nullptr));
        bodyComboBox->setItemText(20, QApplication::translate("MarkerWidget", "L. Heel", nullptr));
        bodyComboBox->setItemText(21, QApplication::translate("MarkerWidget", "L. Toe", nullptr));

#ifndef QT_NO_TOOLTIP
        grabButton->setToolTip(QApplication::translate("MarkerWidget", "Grabs the current relative location from the simulation.", nullptr));
#endif // QT_NO_TOOLTIP
        grabButton->setText(QApplication::translate("MarkerWidget", "...", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MarkerWidget: public Ui_MarkerWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MARKERWIDGET_H

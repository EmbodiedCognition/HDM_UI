/********************************************************************************
** Form generated from reading UI file 'jointplotwidget.ui'
**
** Created by: Qt User Interface Compiler version 5.12.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_JOINTPLOTWIDGET_H
#define UI_JOINTPLOTWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_JointPlotWidget
{
public:
    QHBoxLayout *horizontalLayout;
    QCheckBox *checkBox;

    void setupUi(QWidget *JointPlotWidget)
    {
        if (JointPlotWidget->objectName().isEmpty())
            JointPlotWidget->setObjectName(QString::fromUtf8("JointPlotWidget"));
        JointPlotWidget->resize(250, 23);
        horizontalLayout = new QHBoxLayout(JointPlotWidget);
        horizontalLayout->setSpacing(2);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(2, 0, 2, 0);
        checkBox = new QCheckBox(JointPlotWidget);
        checkBox->setObjectName(QString::fromUtf8("checkBox"));

        horizontalLayout->addWidget(checkBox);


        retranslateUi(JointPlotWidget);

        QMetaObject::connectSlotsByName(JointPlotWidget);
    } // setupUi

    void retranslateUi(QWidget *JointPlotWidget)
    {
        JointPlotWidget->setWindowTitle(QApplication::translate("JointPlotWidget", "Form", nullptr));
        checkBox->setText(QApplication::translate("JointPlotWidget", "CheckBox", nullptr));
    } // retranslateUi

};

namespace Ui {
    class JointPlotWidget: public Ui_JointPlotWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_JOINTPLOTWIDGET_H

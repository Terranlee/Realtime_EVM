/********************************************************************************
** Form generated from reading UI file 'paramcontroler.ui'
**
** Created by: Qt User Interface Compiler version 5.1.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PARAMCONTROLER_H
#define UI_PARAMCONTROLER_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ParamControler
{
public:
    QGroupBox *groupBox;
    QRadioButton *Motion;
    QRadioButton *Color;
    QGroupBox *groupBox_2;
    QRadioButton *IIR;
    QRadioButton *Ideal;
    QRadioButton *Butterworth;
    QPushButton *OK;
    QLabel *Alpha;
    QLineEdit *Alpha_input;
    QLabel *LambdaC;
    QLineEdit *LambdaC_input;
    QLabel *Freq_low;
    QLineEdit *Freq_low_input;
    QLineEdit *Freq_high_input;
    QLabel *Freq_high;
    QLabel *Attenuation;
    QLineEdit *Attenuation_input;
    QLabel *Notice;

    void setupUi(QWidget *ParamControler)
    {
        if (ParamControler->objectName().isEmpty())
            ParamControler->setObjectName(QStringLiteral("ParamControler"));
        ParamControler->resize(400, 300);
        groupBox = new QGroupBox(ParamControler);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setGeometry(QRect(30, 20, 181, 61));
        Motion = new QRadioButton(groupBox);
        Motion->setObjectName(QStringLiteral("Motion"));
        Motion->setGeometry(QRect(10, 30, 100, 21));
        Color = new QRadioButton(groupBox);
        Color->setObjectName(QStringLiteral("Color"));
        Color->setGeometry(QRect(110, 30, 71, 21));
        groupBox_2 = new QGroupBox(ParamControler);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        groupBox_2->setGeometry(QRect(30, 100, 311, 61));
        IIR = new QRadioButton(groupBox_2);
        IIR->setObjectName(QStringLiteral("IIR"));
        IIR->setGeometry(QRect(10, 30, 100, 21));
        Ideal = new QRadioButton(groupBox_2);
        Ideal->setObjectName(QStringLiteral("Ideal"));
        Ideal->setGeometry(QRect(110, 30, 100, 21));
        Butterworth = new QRadioButton(groupBox_2);
        Butterworth->setObjectName(QStringLiteral("Butterworth"));
        Butterworth->setGeometry(QRect(200, 30, 100, 21));
        OK = new QPushButton(ParamControler);
        OK->setObjectName(QStringLiteral("OK"));
        OK->setGeometry(QRect(270, 90, 80, 23));
        Alpha = new QLabel(ParamControler);
        Alpha->setObjectName(QStringLiteral("Alpha"));
        Alpha->setGeometry(QRect(30, 170, 51, 31));
        Alpha_input = new QLineEdit(ParamControler);
        Alpha_input->setObjectName(QStringLiteral("Alpha_input"));
        Alpha_input->setGeometry(QRect(80, 170, 91, 31));
        LambdaC = new QLabel(ParamControler);
        LambdaC->setObjectName(QStringLiteral("LambdaC"));
        LambdaC->setGeometry(QRect(190, 170, 71, 31));
        LambdaC_input = new QLineEdit(ParamControler);
        LambdaC_input->setObjectName(QStringLiteral("LambdaC_input"));
        LambdaC_input->setGeometry(QRect(260, 170, 91, 31));
        Freq_low = new QLabel(ParamControler);
        Freq_low->setObjectName(QStringLiteral("Freq_low"));
        Freq_low->setGeometry(QRect(20, 210, 61, 31));
        Freq_low_input = new QLineEdit(ParamControler);
        Freq_low_input->setObjectName(QStringLiteral("Freq_low_input"));
        Freq_low_input->setGeometry(QRect(80, 210, 91, 31));
        Freq_high_input = new QLineEdit(ParamControler);
        Freq_high_input->setObjectName(QStringLiteral("Freq_high_input"));
        Freq_high_input->setGeometry(QRect(260, 210, 91, 31));
        Freq_high = new QLabel(ParamControler);
        Freq_high->setObjectName(QStringLiteral("Freq_high"));
        Freq_high->setGeometry(QRect(190, 210, 61, 31));
        Attenuation = new QLabel(ParamControler);
        Attenuation->setObjectName(QStringLiteral("Attenuation"));
        Attenuation->setGeometry(QRect(10, 250, 71, 31));
        Attenuation_input = new QLineEdit(ParamControler);
        Attenuation_input->setObjectName(QStringLiteral("Attenuation_input"));
        Attenuation_input->setGeometry(QRect(80, 250, 91, 31));
        Notice = new QLabel(ParamControler);
        Notice->setObjectName(QStringLiteral("Notice"));
        Notice->setGeometry(QRect(230, 10, 161, 71));

        retranslateUi(ParamControler);

        QMetaObject::connectSlotsByName(ParamControler);
    } // setupUi

    void retranslateUi(QWidget *ParamControler)
    {
        ParamControler->setWindowTitle(QApplication::translate("ParamControler", "Form", 0));
        groupBox->setTitle(QApplication::translate("ParamControler", "Function", 0));
        Motion->setText(QApplication::translate("ParamControler", "Motion", 0));
        Color->setText(QApplication::translate("ParamControler", "Color", 0));
        groupBox_2->setTitle(QApplication::translate("ParamControler", "Temporal Filter", 0));
        IIR->setText(QApplication::translate("ParamControler", "IIR", 0));
        Ideal->setText(QApplication::translate("ParamControler", "Ideal", 0));
        Butterworth->setText(QApplication::translate("ParamControler", "Butterworth", 0));
        OK->setText(QApplication::translate("ParamControler", "OK", 0));
        Alpha->setText(QApplication::translate("ParamControler", "Alpha", 0));
        LambdaC->setText(QApplication::translate("ParamControler", "LambdaC", 0));
        Freq_low->setText(QApplication::translate("ParamControler", "Freq_low", 0));
        Freq_high->setText(QApplication::translate("ParamControler", "Freq_high", 0));
        Attenuation->setText(QApplication::translate("ParamControler", "Attenuation", 0));
        Notice->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class ParamControler: public Ui_ParamControler {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PARAMCONTROLER_H

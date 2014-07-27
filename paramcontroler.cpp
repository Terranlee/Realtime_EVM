#include "paramcontroler.h"
#include "ui_paramcontroler.h"

ParamControler::ParamControler(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ParamControler)
{
    ui->setupUi(this);

    //connect the signals and slots
    QObject::connect(ui->OK , SIGNAL(clicked()) , this , SLOT(check_param()));
    QObject::connect(this , SIGNAL(new_notice(QString)) , this , SLOT(notice_change(QString)));

    QObject::connect(ui->Color , SIGNAL(clicked()) , this , SLOT(locked()));
    QObject::connect(ui->Motion , SIGNAL(clicked()) , this , SLOT(unlock()));

    //set default parameters
    parameters[0] = manipulate::alphaConst;
    parameters[1] = manipulate::lambdaCConst;
    parameters[2] = manipulate::heart_low;
    parameters[3] = manipulate::heart_high;
    parameters[4] = manipulate::attenuationConst;

    //set default UI
    ui->Alpha_input->setText(QString("%1").arg(parameters[0]));
    ui->LambdaC_input->setText(QString("%1").arg(parameters[1]));
    ui->Freq_low_input->setText(QString("%1").arg(parameters[2]));
    ui->Freq_high_input->setText(QString("%1").arg(parameters[3]));
    ui->Attenuation_input->setText(QString("%1").arg(parameters[4]));
    ui->Motion->setChecked(true);
    ui->IIR->setChecked(true);
    ui->Notice->setText(QString("parameters okay"));
}

ParamControler::~ParamControler()
{
    delete ui;
}

void ParamControler::notice_change(QString message)
{
    ui->Notice->setText(message);
}

void ParamControler::unlock()
{
    ui->Attenuation_input->setReadOnly(false);
    ui->Attenuation_input->setText(QString("%1").arg(parameters[4]));

    ui->LambdaC_input->setReadOnly(false);
    ui->LambdaC_input->setText(QString("%1").arg(parameters[1]));
}

void ParamControler::locked()
{
    ui->Attenuation_input->clear();
    parameters[4] = manipulate::attenuationConst;
    ui->Attenuation_input->setReadOnly(true);

    ui->LambdaC_input->clear();
    parameters[1] = manipulate::lambdaCConst;
    ui->LambdaC_input->setReadOnly(true);
}

void ParamControler::check_param()
{
    //use exception to check the parameters
    //coding like this to learn how to use exceptions , actually it is not really necessary
    try{
        for(int i=0; i<argNum; i++)
            if(parameters[i] < 0)
                throw error::NegativeError(argName[i] , parameters[i]);

        if(parameters[0] < 1) throw error::TooSmallError(argName[0] , parameters[0]);
        else if(parameters[0] > 200) throw error::TooLargeError(argName[0] , parameters[0]);

        if(parameters[1] < 20) throw error::TooSmallError(argName[1] , parameters[1]);
        else if(parameters[1] > 150) throw error::TooLargeError(argName[1] , parameters[1]);

        if(parameters[2] > parameters[3]) throw error::MessageError(QString("freqLow must be smaller than freqHigh"));
    }
    catch(error::NumberError& e)
    {
        emit(e.print_message());
    }
    catch(error::MessageError e)
    {
        emit (e.print());
    }
}

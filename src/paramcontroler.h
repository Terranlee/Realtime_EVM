#ifndef PARAMCONTROLER_H
#define PARAMCONTROLER_H

#include <QWidget>
#include <QString>
#include "process.h"
#include "error.h"

namespace Ui {
class ParamControler;
}

const int argNum = 5;
const QString argName[argNum] = {"alpha" , "lambdaC" , "freqLow" , "freqHigh" , "attenuation"};

enum Kind{ MOTION , COLOR };
enum Spacial{ LAPLACIAN , GAUSSIAN };
enum Temporal{ IIR , IDEAL , BUTTER };

class ParamControler : public QWidget
{
    Q_OBJECT
    
public:
    explicit ParamControler(QWidget *parent = 0);
    ~ParamControler();
    
signals:
    void new_notice(QString);
    void all_set(float[] , Kind , Temporal);

private slots:
    void check_param();
    void notice_change(QString);
    void locked();
    void unlock();

private:
    Ui::ParamControler *ui;

    //parameters used for the video magnify
    //alpha , lambdaC , freqLow , freqHigh , attenuation
    float parameters[argNum];
    Kind ampKind;
    Temporal ampTemporal;

    void set_parameters();
};

#endif // PARAMCONTROLER_H

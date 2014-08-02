#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "videothread.h"
#include "paramcontroler.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    material::VideoThread* source;
    ParamControler* controler;

private slots:
    void print();
    void begin_main();
    void stop_main();
    void set_parameter(float[],Kind,Temporal);
};

#endif // MAINWINDOW_H

#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    source = new material::VideoThread(33);
    controler = new ParamControler;
    ui->if_face->setWordWrap(true);

    //paint update of the image
    QObject::connect(source , SIGNAL(frame_change()), this , SLOT(print()));

    //control the begin and stop of the video magnify
    QObject::connect(ui->Begin , SIGNAL(clicked()) , this , SLOT(begin_main()));
    QObject::connect(ui->Stop , SIGNAL(clicked()) , this , SLOT(stop_main()));

    //set the details of videothread
    QObject::connect(ui->Set , SIGNAL(clicked()) , controler , SLOT(show()));
    QObject::connect(controler , SIGNAL(all_set(float[],Kind,Temporal)) , this , SLOT(set_parameter(float[],Kind,Temporal)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::begin_main()
{
    source->start();
}

void MainWindow::stop_main()
{
    source->exit();
}

void MainWindow::set_parameter(float param[] , Kind ampKind , Temporal ampTemporal)
{

}

void MainWindow::print()
{
    IplImage* temp = source->acquire_access();
    QImage image = QImage((const uchar*) temp->imageData , temp->width , temp->height , QImage::Format_RGB888).rgbSwapped();
    ui->show_area->setPixmap(QPixmap::fromImage(image));

    IplImage* temp1 = source->acquire_init();
    QImage image1 = QImage((const uchar*) temp1->imageData , temp1->width , temp1->height , QImage::Format_RGB888).rgbSwapped();
    ui->show_area_4->setPixmap(QPixmap::fromImage(image1));

}


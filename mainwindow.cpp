#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    source = new material::VideoThread(33);
    QObject::connect(source , SIGNAL(frame_change()), this , SLOT(print()));
    QObject::connect(ui->Begin , SIGNAL(clicked()) , this , SLOT(begin_main()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::begin_main()
{
    source->start();
}

void MainWindow::print()
{
    IplImage* temp = source->acquire_access();
    QImage image = QImage((const uchar*) temp->imageData , temp->width , temp->height , QImage::Format_RGB888).rgbSwapped();
    ui->show_area->setPixmap(QPixmap::fromImage(image));
}

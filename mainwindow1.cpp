#include "mainwindow1.h"
#include "ui_mainwindow1.h"
#include"bgmusic.h"
#include<QSound>
#include<QPainter>

MainWindow1::MainWindow1(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow1)
  ,neverend_music(_neverend_music)


{
    ui->setupUi(this);
    neverend_music.setLoops(1);
    neverend_music.play();

}

MainWindow1::~MainWindow1()
{
    delete ui;
}
void MainWindow1::paintEvent(QPaintEvent *)
{
    QPixmap cachePix(":/image/Start.png");
    QPainter painter(this);
    painter.drawPixmap(0, 0, cachePix);

}
void MainWindow1::on_pushButton_2_clicked()
{
    this->hide();
    // neverend_music.stop();
    mainwindow11=new MainWindow11(nullptr , 1);
    mainwindow11->show();
    mainwindow11->gameStart();
}

void MainWindow1::on_pushButton_clicked()
{
    this->hide();
   // neverend_music.stop();
    mainwindow11=new MainWindow11(nullptr , 2);
    mainwindow11->show();
    mainwindow11->gameStart();
}

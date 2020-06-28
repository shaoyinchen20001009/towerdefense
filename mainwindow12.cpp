#include "mainwindow12.h"
#include "ui_mainwindow12.h"

MainWindow12::MainWindow12(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow12)
{
    ui->setupUi(this);
}

MainWindow12::~MainWindow12()
{
    delete ui;
}

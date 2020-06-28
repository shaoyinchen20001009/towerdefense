#ifndef MAINWINDOW1_H
#define MAINWINDOW1_H

#include <QMainWindow>

#include"mainwindow11.h"
#include"mainwindow12.h"
#include"bgmusic.h"
#include<QSound>
namespace Ui {
class MainWindow1;
}

class MainWindow1 : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow1(QWidget *parent = nullptr);
    ~MainWindow1();
    void paintEvent(QPaintEvent *);


public slots:
    void on_pushButton_2_clicked();
    void on_pushButton_clicked();

private:
    Ui::MainWindow1 *ui;
    MainWindow11 *mainwindow11;//=new MainWindow11;
    MainWindow12 *mainwindow12;//=new MainWindow12;
    BgMusic neverend_music;//出场音乐

};

#endif // MAINWINDOW1_H

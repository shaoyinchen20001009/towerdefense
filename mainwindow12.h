#ifndef MAINWINDOW12_H
#define MAINWINDOW12_H

#include <QMainWindow>

namespace Ui {
class MainWindow12;
}

class MainWindow12 : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow12(QWidget *parent = nullptr);
    ~MainWindow12();

private:
    Ui::MainWindow12 *ui;
};

#endif // MAINWINDOW12_H

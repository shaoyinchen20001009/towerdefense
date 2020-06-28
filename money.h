#ifndef MONEY_H
#define MONEY_H

#include <QWidget>
#include <QMovie>
#include <QMouseEvent>
#include <QLabel>
#include <QPushButton>
#include <QTimer>
#include <QDebug>
#include <QKeyEvent>

class MainWindow11;

class money : public QLabel
{
public:
    money(QWidget* parent = 0);
    virtual void act() = 0;
    bool alive = true;
    int strength = 1;
    virtual void setgame(MainWindow11* game);
    MainWindow11 *m_game;

};

class zSun : virtual public money
{
public:
    zSun(QWidget* parent = 0);
    ~zSun();
    void act();
    int frame;
    float level, speed, accelerate, x_speed = 0;
    void setgame(MainWindow11* game);
    MainWindow11 *m_game;


protected:
    void mousePressEvent(QMouseEvent *event);
private:
    QMovie* anim = new QMovie(":/image/othermoney.png");
};

class zSunFall : virtual public money
{
public:
    zSunFall(QWidget* parent = 0);
    ~zSunFall();
    void act();
    int frame;
    float level, speed;
    void setgame(MainWindow11* game);
    MainWindow11 *m_game;

protected:
    void mousePressEvent(QMouseEvent *event);
private:
    QMovie* anim = new QMovie(":/image/othermoney.png");
};

#endif // MONEY_H

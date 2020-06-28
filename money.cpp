#include "money.h"
#include "mainwindow11.h"
#include"bgmusic.h"
#include<QSound>
#include<QString>
money::money(QWidget* parent)  : QLabel(parent)
{
    this->setMouseTracking(true);
}

void money::act()
{

}
void money::setgame(MainWindow11 * game)
{
    m_game = game;
}
zSun::zSun(QWidget* parent) : money(parent)
{
    this->setGeometry(260, 80, 80, 80);
    this->setMovie(anim);
    anim->start();
    this->show();
    this->speed = -(qrand() % 5 + 7);
    this->accelerate = 2;
    //this->level = 200;
    this->x_speed = qrand() % 5 - 2;
    this->frame = 120;
}

zSun::~zSun()
{
    delete (this->anim);
}

void zSun::act()
{
    this->raise();
    this->frame --;
    if (this->frame <= 0)
    {
        this->alive = false;
    }
    if (this->y() <= this->level)
    {
        this->speed += this->accelerate;
        this->move(this->x() + this->x_speed, this->y() + this->speed);
    }
}
void zSun::setgame(MainWindow11 * game) {
    m_game = game;
}
void zSun::mousePressEvent(QMouseEvent* event)
{
    this->alive = false;
    m_game->awardGold(50);

}

zSunFall::zSunFall(QWidget* parent) : money(parent)
{
    this->setGeometry(qrand() % 1340 , 0, 80, 80);
    this->setMovie(anim);
    anim->start();
    this->show();
    this->speed = qrand() % 5;
    this->level = qrand() % 400 + 150;
    this->frame = 120;
}

zSunFall::~zSunFall()
{
    delete (this->anim);
}

void zSunFall::act()
{
    this->raise();
    this->frame --;
    if (this->frame <= 0)
    {
        this->alive = false;
    }
    if (this->y() <= this->level)
    {
        this->move(this->x(), this->y() + this->speed);
    }
}
void zSunFall::setgame(MainWindow11 * game) {
    m_game = game;
   //if(_game->gameEnd || _game->gameWin) delete (this->anim);
}
void zSunFall::mousePressEvent(QMouseEvent* event)
{
    this->alive = false;
    m_game->awardGold(25);
   // collectpotion_music.setLoops(1);
    //collectpotion_music.play();//m_game->awardGold(200);
}


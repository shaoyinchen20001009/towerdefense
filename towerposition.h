#ifndef TOWERPOSITION_H
#define TOWERPOSITION_H

#include <QPoint>
#include <QSize>
#include <QPixmap>
#include "tower.h"
#include "cannon.h"
#include "icetower.h"

class QPainter;

class TowerPosition
{
public:
    TowerPosition(QPoint pos, const QPixmap &sprite = QPixmap(":/image/bullet.png"));

    void setHasTower(int hasTower = 0);
    int hasTower() const;
    const QPoint centerPos() const;
    bool containPoint(const QPoint &pos) const;

    void draw(QPainter *painter) const;

    Tower* tower;
    Cannon* cannon;
    IceTower* iceTower;
    QPoint		m_pos;

private:
    int         m_hasTower;
    QPixmap		m_sprite;

    static const QSize ms_fixedSize;

};

#endif // TOWERPOSITION_H

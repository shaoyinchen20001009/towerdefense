#ifndef CANNONBULLET_H
#define CANNONBULLET_H

#include <QPoint>
#include <QSize>
#include <QPixmap>
#include <QObject>

class QPainter;
class Enemy;
class MainWindow11;

class CannonBullet : QObject
{
    Q_OBJECT
    Q_PROPERTY(QPoint m_currentPos READ currentPos WRITE setCurrentPos)

public:
    CannonBullet(QPoint startPos, QPoint targetPoint, int damage, Enemy *target,
           MainWindow11 *game, const QPixmap &sprite = QPixmap(":/image/cannon_bullet0.png"));

    void draw(QPainter *painter) const;
    void move();
    void setCurrentPos(QPoint pos);
    QPoint currentPos() const;

private slots:
    void hitTarget();

private:
    const QPoint	m_startPos;
    const QPoint	m_targetPos;
    const QPixmap	m_sprite;
    QPoint			m_currentPos;
    Enemy *			m_target;
    MainWindow11 *	m_game;
    int				m_damage;
    static const QSize ms_fixedSize;
};


#endif // CANNONBULLET_H

#ifndef ENEMY_H
#define ENEMY_H

#include <QObject>
#include <QPoint>
#include <QSize>
#include <QPixmap>

class WayPoint;
class QPainter;
class MainWindow11;
class Tower;
class Cannon;
class IceTower;

class Enemy : public QObject
{
    Q_OBJECT
public:
    Enemy(WayPoint *startWayPoint, MainWindow11 *game, bool attackTower, const QPixmap &sprite = QPixmap(":/image/princess.png"));
    ~Enemy();

    void draw(QPainter *painter) const;
    void move();
    void getDamage(int damage);
    void getSpeedDown(double speeddown);

    void getRemoved();
    void getAttacked(Tower *attacker);
    void gotLostSight(Tower *attacker);
    void getAttacked(Cannon *attacker);
    void gotLostSight(Cannon *attacker);
    void getAttacked(IceTower *attacker);
    void gotLostSight(IceTower *attacker);
    QPoint pos() const;

public slots:
    void doActivate();

private:
    bool			m_active;

    bool			m_attackTower;

    int				m_maxHp;
    int				m_currentHp;

    double			m_walkingSpeed;

    qreal			m_rotationSprite;

    QPoint			m_pos;
    WayPoint *		m_destinationWayPoint;
    MainWindow11 *	m_game;
    QList<Tower *>	m_attackedTowersList;
    QList<Cannon *> m_attackedCannonList;
    QList<IceTower *> m_attackedIceTowerList;
    const QPixmap	m_sprite,m_sprite1;
    static const QSize ms_fixedSize;
    static const QSize ms_fixedSize1;
};
#endif // ENEMY_H

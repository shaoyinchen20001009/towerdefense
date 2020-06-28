#ifndef ICETOWER_H
#define ICETOWER_H


#include <QPoint>
#include <QSize>
#include <QPixmap>
#include <QObject>

class QPainter;
class Enemy;
class MainWindow11;
class QTimer;

class IceTower : QObject
{
    Q_OBJECT
public:
    IceTower(QPoint pos, MainWindow11 *game, const QPixmap &sprite = QPixmap(":/image/cannon.png"));
    ~IceTower();

    void draw(QPainter *painter) const;
    void checkEnemyInRange();
    void targetKilled();
    void attackEnemy();
    void chooseEnemyForAttack(Enemy *enemy);
    void removeBullet();
    void damageEnemy();
    void lostSightOfEnemy();
    void setDamage(int num);
    void setRange(int num);
    QPoint getPos();
    void deleteSelf();

private slots:
    void shootWeapon();

private:
    bool			m_attacking;
    int				m_attackRange;	// 代表塔可以攻击到敌人的距离
    int				m_damage;		// 代表攻击敌人时造成的伤害
    double          m_speeddown;
    int				m_fireRate;		// 代表再次攻击敌人的时间间隔

    Enemy *			m_chooseEnemy;
    MainWindow11 *	m_game;
    QTimer *		m_fireRateTimer;

    const QPoint	m_pos;
    const QPixmap	m_sprite;

    static const QSize ms_fixedSize;
};

#endif // ICETOWER_H

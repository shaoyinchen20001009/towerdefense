#include "icetower.h"
#include "enemy.h"
#include "bullet.h"
#include "mainwindow11.h"
#include "judge.h"
#include <QPainter>
#include <QColor>
#include <QTimer>
#include <QVector2D>
#include <QtMath>

const QSize IceTower::ms_fixedSize(42, 42);

IceTower::IceTower(QPoint pos, MainWindow11 *game, const QPixmap &sprite/* = QPixmap(":/image/tower.png"*/)
    : m_attacking(false)
    , m_attackRange(250)
    , m_damage(50)
    , m_speeddown(0.1)
    , m_fireRate(800)
    , m_chooseEnemy(NULL) //减速
    , m_game(game)
    , m_pos(pos)
    , m_sprite(sprite)
{
    m_fireRateTimer = new QTimer(this);
    connect(m_fireRateTimer, SIGNAL(timeout()), this, SLOT(shootWeapon()));
}

IceTower::~IceTower()
{
    delete m_fireRateTimer;
    m_fireRateTimer = NULL;
}

void IceTower::checkEnemyInRange()
{
    if (m_chooseEnemy)
    {
        // 如果敌人脱离攻击范围
        if (!collisionWithCircle(m_pos, m_attackRange, m_chooseEnemy->pos(), 1))
            lostSightOfEnemy();
    }
    else
    {
        // 遍历敌人,看是否有敌人在攻击范围内
        QList<Enemy *> enemyList = m_game->enemyList();
        foreach (Enemy *enemy, enemyList)
        {
            if (collisionWithCircle(m_pos, m_attackRange, enemy->pos(), 1))
            {
                chooseEnemyForAttack(enemy);
                break;
            }
        }
        QList<Enemy *> enemyList1 = m_game->enemyList1();
        foreach (Enemy *enemy1, enemyList1)
        {
            if (collisionWithCircle(m_pos, m_attackRange, enemy1->pos(), 1))
            {
                chooseEnemyForAttack(enemy1);
                break;
            }
        }
    }
}

void IceTower::draw(QPainter *painter) const
{
    painter->save();
    painter->setPen(Qt::red);
    // 绘制攻击范围
    //painter->drawEllipse(m_pos, m_attackRange, m_attackRange);

    // 绘制偏转坐标,由中心+偏移=左上
    static const QPoint offsetPoint(-ms_fixedSize.width() / 2 - 1, -ms_fixedSize.height() / 2 + 8);
    // 绘制炮塔并选择炮塔
    painter->translate(m_pos);
    painter->drawPixmap(offsetPoint, m_sprite);
    painter->restore();
}

void IceTower::attackEnemy()
{
    m_fireRateTimer->start(m_fireRate);
}

void IceTower::chooseEnemyForAttack(Enemy *enemy)
{
    m_chooseEnemy = enemy;
    attackEnemy();
    m_chooseEnemy->getAttacked(this);
}

void IceTower::shootWeapon()
{
    IceBullet *icebullet = new IceBullet(m_pos, m_chooseEnemy->pos(), m_damage, m_speeddown, m_chooseEnemy, m_game);
    icebullet->move();
    m_game->addIceBullet(icebullet);
}

void IceTower::targetKilled()
{
    if (m_chooseEnemy)
        m_chooseEnemy = NULL;

    m_fireRateTimer->stop();
}

void IceTower::lostSightOfEnemy()
{
    if (m_chooseEnemy)
    {
        m_chooseEnemy->gotLostSight(this);
        if (m_chooseEnemy)
            m_chooseEnemy = NULL;

        m_fireRateTimer->stop();
    }
}

void IceTower::setDamage(int num){
    m_damage = m_damage*num;
}

void IceTower::setRange(int num){
    m_attackRange = m_attackRange*num;
}

QPoint IceTower::getPos(){
    return m_pos;
}

void IceTower::deleteSelf(){
    delete this;
}

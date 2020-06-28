#include "enemy.h"
#include "waypoint.h"
#include "tower.h"
#include "cannon.h"
#include "judge.h"
#include "mainwindow11.h"
#include "audioplayer.h"
#include <QPainter>
#include <QColor>
#include <QDebug>
#include <QMatrix>
#include <QVector2D>
#include <QtMath>

static const int Health_Bar_Width = 30;
const QSize Enemy::ms_fixedSize(52, 52);

static const int Health_Bar_Width1 = 30;
const QSize Enemy::ms_fixedSize1(52, 52);

Enemy::Enemy(WayPoint *startWayPoint, MainWindow11 *game, bool attackTower, const QPixmap &sprite/* = QPixmap(":/image/enemy.png")*/)
    : QObject(0)
    , m_active(false)
    , m_attackTower(attackTower)
    , m_maxHp(1500)
    , m_currentHp(1500)
    , m_walkingSpeed(1.0)
    , m_rotationSprite(0.0)
    , m_pos(startWayPoint->pos())
    , m_destinationWayPoint(startWayPoint->nextWayPoint())
    , m_game(game)
    , m_sprite(sprite)
    , m_sprite1(sprite)
{
    if (m_attackTower == true){
        m_walkingSpeed = m_walkingSpeed * 2;
        m_maxHp = 500;
        m_currentHp = 500;
    }
}

Enemy::~Enemy()
{
    m_attackedTowersList.clear();
    m_attackedCannonList.clear();
    m_attackedIceTowerList.clear();
    m_destinationWayPoint = NULL;
    m_game = NULL;
}

void Enemy::doActivate()
{
    m_active = true;
}

void Enemy::move()
{
    if (!m_active)
        return;

    if(m_attackTower == true){
        bool result = m_game->attactTower(m_pos);
        if(result == true){
            m_game->removedEnemy(this);
            return;
        }
    }

    if (collisionWithCircle(m_pos, 1, m_destinationWayPoint->pos(), 1))
    {
        // 敌人抵达了一个航点
        if (m_destinationWayPoint->nextWayPoint())
        {
            // 还有下一个航点
            m_pos = m_destinationWayPoint->pos();
            m_destinationWayPoint = m_destinationWayPoint->nextWayPoint();
        }
        else
        {
            // 表示进入基地
            m_game->getHpDamage();
            m_game->removedEnemy(this);
            return;
        }
    }

    // 还在前往航点的路上
    // 目标航点的坐标
    QPoint targetPoint = m_destinationWayPoint->pos();
    // 未来修改这个可以添加移动状态,加快,减慢,m_walkingSpeed是基准值

    // 向量标准化
    qreal movementSpeed = m_walkingSpeed;
    QVector2D normalized(targetPoint - m_pos);
    normalized.normalize();
    m_pos = m_pos + normalized.toPoint() * movementSpeed;
}

void Enemy::draw(QPainter *painter) const
{
    if (!m_active)
        return;

    painter->save();

    QPoint healthBarPoint = m_pos + QPoint(-Health_Bar_Width / 2 - 5, -ms_fixedSize.height() / 2);
    // 绘制血条
    painter->setPen(Qt::NoPen);
    painter->setBrush(Qt::red);
    QRect healthBarBackRect(healthBarPoint, QSize(Health_Bar_Width, 2));
    painter->drawRect(healthBarBackRect);

    painter->setBrush(Qt::yellow);
    QRect healthBarRect(healthBarPoint, QSize((double)m_currentHp / m_maxHp * Health_Bar_Width, 2));
    painter->drawRect(healthBarRect);

    // 绘制偏转坐标,由中心+偏移=左上
    static const QPoint offsetPoint(-ms_fixedSize.width() / 2, -ms_fixedSize.height() / 2);
    painter->translate(m_pos);
    painter->rotate(m_rotationSprite);
    // 绘制敌人
    painter->drawPixmap(offsetPoint, m_sprite);
    painter->restore();
}

void Enemy::getRemoved()
{
    if (m_attackedTowersList.empty() && m_attackedCannonList.empty() && m_attackedIceTowerList.empty())
        return;

    foreach (Tower *attacker, m_attackedTowersList)
        attacker->targetKilled();

    foreach (Cannon *attacker, m_attackedCannonList)
        attacker->targetKilled1();

    foreach (IceTower *attacker, m_attackedIceTowerList)
        attacker->targetKilled();

    // 通知game,此敌人已经阵亡
    m_game->removedEnemy(this);
}


void Enemy::getDamage(int damage)
{
    m_currentHp -= damage;
    // 阵亡,需要移除
    if (m_currentHp <= 0)
    {
        m_game->awardGold(150);
        getRemoved();
    }
}

void Enemy::getSpeedDown(double speeddown)
{
    m_walkingSpeed -= speeddown;
    if (m_walkingSpeed <= 0)
    {
        m_walkingSpeed = -1.0;
    }
}

void Enemy::getAttacked(Tower *attacker)
{
    m_attackedTowersList.push_back(attacker);
}

void Enemy::getAttacked(Cannon *attacker)
{
    m_attackedCannonList.push_back(attacker);
}

void Enemy::getAttacked(IceTower *attacker)
{
    m_attackedIceTowerList.push_back(attacker);
}

// 表明敌人已经逃离了攻击范围
void Enemy::gotLostSight(Tower *attacker)
{
//    foreach (Tower *tower, m_attackedTowersList){
//        printf("=========\n");
//        if(attacker == tower){
//            printf("相等\n");
//        }
//        else{
//            printf("不相等\n");
//        }
//    }
    m_attackedTowersList.removeOne(attacker);
}

void Enemy::gotLostSight(Cannon *attacker)
{
    m_attackedCannonList.removeOne(attacker);
}

void Enemy::gotLostSight(IceTower *attacker)
{
    m_attackedIceTowerList.removeOne(attacker);
}
QPoint Enemy::pos() const
{
    return m_pos;
}

#include "cannon.h"
#include "enemy.h"
#include "cannonbullet.h"
#include "mainwindow11.h"
#include "judge.h"
#include <QPainter>
#include <QColor>
#include <QTimer>
#include <QVector2D>
#include <QtMath>

const QSize Cannon::ms_fixedSize(42, 42);

Cannon::Cannon(QPoint pos, MainWindow11 *game, const QPixmap &sprite/* = QPixmap(":/image/tower.png"*/)
    : m_attacking(false)
    , m_attackRange(150)
    , m_damage(300)
    , m_fireRate(1000)
    , m_rotationSprite(0.0)
    , m_chooseEnemy2(NULL)
    , m_game(game)
    , m_pos(pos)
    , m_sprite(sprite)
{
    m_fireRateTimer = new QTimer(this);
    connect(m_fireRateTimer, SIGNAL(timeout()), this, SLOT(shootWeapon()));
}

Cannon::~Cannon()
{
    delete m_fireRateTimer;
    m_fireRateTimer = NULL;
}

void Cannon::checkEnemyInRange()
{
    if (m_chooseEnemy2)
    {
        // 这种情况下,需要旋转炮台对准敌人
        // 向量标准化
        QVector2D normalized(m_chooseEnemy2->pos() - m_pos);
        normalized.normalize();
        m_rotationSprite = qRadiansToDegrees(qAtan2(normalized.y(), normalized.x())) - 90;

        // 如果敌人脱离攻击范围
        if (!collisionWithCircle(m_pos, m_attackRange, m_chooseEnemy2->pos(), 1))
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

void Cannon::draw(QPainter *painter) const
{
    painter->save();
    painter->setPen(Qt::blue);
    // 绘制攻击范围
    //painter->drawEllipse(m_pos, m_attackRange, m_attackRange);

    // 绘制偏转坐标,由中心+偏移=左上
    static const QPoint offsetPoint(-ms_fixedSize.width() / 2, -ms_fixedSize.height() / 2);
    // 绘制炮塔并选择炮塔
    painter->translate(m_pos);
    painter->rotate(m_rotationSprite);
    painter->drawPixmap(offsetPoint, m_sprite);
    painter->restore();
}

void Cannon::attackEnemy()
{
    m_fireRateTimer->start(m_fireRate);
}

void Cannon::chooseEnemyForAttack(Enemy *enemy)
{
    m_chooseEnemy2 = enemy;
    attackEnemy();
    m_chooseEnemy2->getAttacked(this);
}

void Cannon::shootWeapon()
{
    CannonBullet *cannonbullet = new CannonBullet(m_pos, m_chooseEnemy2->pos(), m_damage, m_chooseEnemy2, m_game);
    cannonbullet->move();
    m_game->addCannonBullet(cannonbullet);
}

void Cannon::targetKilled1()
{
    if (m_chooseEnemy2)
        m_chooseEnemy2 = NULL;

    m_fireRateTimer->stop();
    m_rotationSprite = 0.0;
}

void Cannon::lostSightOfEnemy()
{
    m_chooseEnemy2->gotLostSight(this);
    if (m_chooseEnemy2)
        m_chooseEnemy2 = NULL;

    m_fireRateTimer->stop();
    m_rotationSprite = 0.0;
}

void Cannon::setDamage(int num){
    m_damage = m_damage*num;
    printf("m_damage=%d", m_damage);
}

void Cannon::setRange(int num){
    m_attackRange = m_attackRange*num;
}

QPoint Cannon::getPos(){
    return m_pos;
}

void Cannon::deleteSelf(){
    delete this;
}

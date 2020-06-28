#include "mainwindow11.h"
#include "ui_mainwindow11.h"


#include "waypoint.h"
#include "enemy.h"
#include "bullet.h"
#include "cannonbullet.h"
#include "icebullet.h"
#include "audioplayer.h"
#include "plistreader.h"
#include "money.h"
#include <QPainter>
#include <QMouseEvent>
#include <QtGlobal>
#include <QMessageBox>
#include <QTimer>
#include <QXmlStreamReader>
#include <QtDebug>
#include <QColor>
//#include"bgmusic.h"




static const int TowerCost= 400;
static int flag = 0;

MainWindow11::MainWindow11(QWidget *parent,int _roundflag) :
    QMainWindow(parent),
    roundflag(_roundflag),
    ui(new Ui::MainWindow11)

  , m_waves(0)
  , m_playerHp(5)
  , m_playrGold(1000)
  , m_gameEnded(false)
  , m_gameWin(false)
  ,attackedcastle_music(_attackedcastle_music)
  ,collectpotion_music(_collectpotion_music)
  ,enemydie_music(_enemydie_music)
  ,neverend_music(_neverend_music)
  ,settower_music(_settower_music)
  ,win_music(_win_music)
  ,towerPosition(QPoint(0,0))


{
     menuShow = false;

    ui->setupUi(this);

    preLoadWavesInfo();
    loadTowerPositions();
    addWayPoints();


    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(updateMap()));
    timer->start(30);

    // 设置300ms后游戏启动
    //QTimer::singleShot(300, this, SLOT(gameStart()));


}

MainWindow11::~MainWindow11()
{
    delete ui;
}
void MainWindow11::loadTowerPositions()
{
    if(roundflag==1)
    {


        QFile file(":/config/TowersPosition.plist");
        if (!file.open(QFile::ReadOnly | QFile::Text))
        {
            QMessageBox::warning(this, "TowerDefense", "Cannot Open TowersPosition.plist");
            return;
        }

        PListReader reader;
        reader.read(&file);

        QList<QVariant> array = reader.data();
        foreach (QVariant dict, array)
        {
            QMap<QString, QVariant> point = dict.toMap();
            int x = point.value("x").toInt();
            int y = point.value("y").toInt();
            m_towerPositionsList.push_back(QPoint(x, y));
        }

        file.close();
    }
    if(roundflag==2)
    {
        QFile file(":/config/TowersPosition2.plist");
        if (!file.open(QFile::ReadOnly | QFile::Text))
        {
            QMessageBox::warning(this, "TowerDefense", "Cannot Open TowersPosition.plist");
            return;
        }

        PListReader reader;
        reader.read(&file);

        QList<QVariant> array = reader.data();
        foreach (QVariant dict, array)
        {
            QMap<QString, QVariant> point = dict.toMap();
            int x = point.value("x").toInt();
            int y = point.value("y").toInt();
            m_towerPositionsList.push_back(QPoint(x, y));
        }

        file.close();
    }
}
//手机修复城堡的药水
void MainWindow11::act()
{
    money* mymoney;
    foreach(mymoney, moneylist)
    {
        mymoney->act();
    }

}
void MainWindow11::paintEvent(QPaintEvent *)
{
    if (m_gameEnded || m_gameWin)
    {

        if(m_gameEnded==true)
        {
            //lost
            attackedcastle_music.stop();
            collectpotion_music.stop();
            enemydie_music.stop();
            settower_music.stop();

            win_music.setLoops(3);
            win_music.play();
            QPixmap cachePix(":/image/snowworld.jpg");
            QPainter cachePainter(&cachePix);
            QPainter painter(this);
            painter.drawPixmap(0, 0, cachePix);

        }
        if(m_gameEnded==false)
        {
            //win
            attackedcastle_music.stop();
            collectpotion_music.stop();
            enemydie_music.stop();
            neverend_music.stop();
            settower_music.stop();

            win_music.setLoops(3);
            win_music.play();
            QPixmap cachePix(":/image/hotworld.jpg");
            QPainter cachePainter(&cachePix);
            QPainter painter(this);
            painter.drawPixmap(0, 0, cachePix);

        }
        while (!moneylist.empty())
        {
            delete moneylist[0];
            moneylist.removeAt(0);
        }
        return;
    }
    if(roundflag==1)
    {
        QPixmap cachePix(":/image/Bg4.png");
        QPainter cachePainter(&cachePix);
        castle.draw(&cachePainter);

        foreach (const TowerPosition &towerPos, m_towerPositionsList)
            towerPos.draw(&cachePainter);

        foreach (const Tower *tower, m_towersList)
            tower->draw(&cachePainter);

        //重复绘制
//        foreach (const TowerPosition &cannonPos, m_towerPositionsList)
//            cannonPos.draw(&cachePainter);

        foreach (const Cannon *cannon, m_cannonList)
            cannon->draw(&cachePainter);

//        foreach (const TowerPosition &icetowerPos, m_towerPositionsList)
//            icetowerPos.draw(&cachePainter);

        foreach (const IceTower *icetower, m_icetowerList)
            icetower->draw(&cachePainter);

        foreach (const Enemy *enemy, m_enemyList)
            enemy->draw(&cachePainter);

        foreach (const Enemy *enemy1, m_enemyList1)
            enemy1->draw(&cachePainter);


        foreach (const Bullet *bullet, m_bulletList)
            bullet->draw(&cachePainter);

        foreach (const CannonBullet *cannonbullet, m_cannonbulletList)
            cannonbullet->draw(&cachePainter);

        foreach (const IceBullet *icebullet, m_icebulletList)
            icebullet->draw(&cachePainter);

        drawWave(&cachePainter);
        drawHP(&cachePainter);
        drawPlayerGold(&cachePainter);
        drawXT(&cachePainter);

        QPainter painter(this);
        painter.drawPixmap(0, 0, cachePix);//QPixmap cachePix(":/image/Bg4.png");
    }
    if(roundflag==2)
    {
        QPixmap cachePix(":/image/round2map.png");
        QPainter cachePainter(&cachePix);
        castle2.draw(&cachePainter);

        foreach (const TowerPosition &towerPos, m_towerPositionsList)
            towerPos.draw(&cachePainter);

        foreach (const Tower *tower, m_towersList)
            tower->draw(&cachePainter);

        foreach (const TowerPosition &cannonPos, m_towerPositionsList)
            cannonPos.draw(&cachePainter);

        foreach (const Cannon *cannon, m_cannonList)
            cannon->draw(&cachePainter);

        foreach (const TowerPosition &icetowerPos, m_towerPositionsList)
            icetowerPos.draw(&cachePainter);

        foreach (const IceTower *icetower, m_icetowerList)
            icetower->draw(&cachePainter);

        foreach (const Enemy *enemy, m_enemyList)
            enemy->draw(&cachePainter);

        foreach (const Enemy *enemy1, m_enemyList1)
            enemy1->draw(&cachePainter);


        foreach (const Bullet *bullet, m_bulletList)
            bullet->draw(&cachePainter);

        foreach (const CannonBullet *cannonbullet, m_cannonbulletList)
            cannonbullet->draw(&cachePainter);

        foreach (const IceBullet *icebullet, m_icebulletList)
            icebullet->draw(&cachePainter);


        drawWave(&cachePainter);
        drawHP(&cachePainter);
        drawPlayerGold(&cachePainter);
        drawXT(&cachePainter);

        QPainter painter(this);
        painter.drawPixmap(0, 0, cachePix);//QPixmap cachePix(":/image/Bg4.png");
      }
}

bool MainWindow11::attactTower(QPoint point){

    if(point.x() != 863){
        return false;
    }
    QList<TowerPosition>::iterator tPosition = m_towerPositionsList.begin();

    for ( ; tPosition != m_towerPositionsList.end(); tPosition++)  {
        int towerX = tPosition->centerPos().x();
        int towerY = tPosition->centerPos().y();

        if(tPosition->hasTower()>0 && (towerX == 770 || towerX == 910) && qAbs(towerY-point.y()) <= 10){
            printf("attack tower \n ");
            if(tPosition->hasTower() == 1){
                tPosition->tower->setRange(0);
                tPosition->tower->checkEnemyInRange();      //@@有异常
                m_towersList.removeOne(tPosition->tower);
//                tPosition->tower->setPos(QPoint(-1000,-1000));
//                tPosition->tower->checkEnemyInRange();
//                tPosition->tower->targetKilled();
//                tPosition->tower->lostSightOfEnemy();
//                tPosition->tower->deleteSelf();
//                m_towerPositionsList.removeOne(tPosition);
            }
            else if(tPosition->hasTower() == 2){
                tPosition->cannon->setRange(0);
                tPosition->cannon->checkEnemyInRange();     //@@有异常
                m_cannonList.removeOne(tPosition->cannon);
//                tPosition->cannon->deleteSelf();
            }
            else if(tPosition->hasTower() == 3){
                tPosition->iceTower->setRange(0);
                tPosition->iceTower->checkEnemyInRange();   //@@有异常
                m_icetowerList.removeOne(tPosition->iceTower);
//                tPosition->iceTower->deleteSelf();
            }

            tPosition->setHasTower(0);
            update();
            return true;
        }
    }
    return false;
}

void MainWindow11::flagChange(int towerId)
{
    if (canBuyTower())
    {
        printf("build towerId=%d \n", towerId);

        int x = towerPosition.centerPos().x();
        int y = towerPosition.centerPos().y();

        QList<TowerPosition>::iterator point = m_towerPositionsList.begin();
        for ( ; point != m_towerPositionsList.end(); point++)  {
            int towerX = point->centerPos().x();
            int towerY = point->centerPos().y();

            if(qAbs(towerX-x) <= 20 && qAbs(towerY-y) <= 20){
                settower_music.setLoops(1);
                settower_music.play();
                m_playrGold -= TowerCost;

                point->setHasTower(towerId);
                if(towerId == 1){
                    Tower *tower = new Tower(point->centerPos(), this);
                    m_towersList.push_back(tower);
                    point->tower = tower;
                }
                else if(towerId == 2){
                    Cannon *cannon = new Cannon(point->centerPos(), this);
                    m_cannonList.push_back(cannon);
                    point->cannon = cannon;
                }
                else if(towerId == 3){
                    IceTower *icetower = new IceTower(point->centerPos(), this);
                    m_icetowerList.push_back(icetower);
                    point->iceTower = icetower;
                }
                update();
            }
         }
    }
}

void MainWindow11::upgrade(int type){

    printf("type=%d\n", type);

    int x = towerPosition.centerPos().x();
    int y = towerPosition.centerPos().y();

    QList<TowerPosition>::iterator position = m_towerPositionsList.begin();
    for ( ; position != m_towerPositionsList.end(); position++)  {

        if(x == position->m_pos.x() && y == position->m_pos.y()){
            if(type == 3){
                printf("拆塔\n");
                if(position->hasTower() == 1){
                    printf("拆塔  1号\n");
                    position->tower->setRange(0);
                    position->tower->checkEnemyInRange();
                    m_towersList.removeOne(position->tower);
//                    position->tower->lostSightOfEnemy();
//                    position->tower->deleteSelf();
                }
                else if(position->hasTower() == 2){
                    position->cannon->setRange(0);
                    position->cannon->checkEnemyInRange();
                    m_cannonList.removeOne(position->cannon);
//                    position->cannon->deleteSelf();
//                    position->cannon->lostSightOfEnemy();
                }
                else if(position->hasTower() == 3){
                    position->iceTower->setRange(0);
                    position->iceTower->checkEnemyInRange();
                    m_icetowerList.removeOne(position->iceTower);
//                    position->iceTower->deleteSelf();
//                    position->iceTower->lostSightOfEnemy();

                }

                position->setHasTower(0);

                update();
                break;
            }

            if (canBuyTower()){
                m_playrGold -= TowerCost;
                if(type == 1){
                    if(position->hasTower() == 1){
                        position->tower->setDamage(2);
                    }
                    else if(position->hasTower() == 2){
                        position->cannon->setDamage(2);
                    }
                    else if(position->hasTower() == 3){
                        position->iceTower->setDamage(2);
                    }
                }
                else{
                    if(position->hasTower() == 1){
                        position->tower->setRange(2);
                    }
                    else if(position->hasTower() == 2){
                        position->cannon->setRange(2);
                    }
                    else if(position->hasTower() == 3){
                        position->iceTower->setRange(2);
                    }
                }
            }
        }
    }
    update();
}

void MainWindow11::mousePressEvent(QMouseEvent *event)
{
    if(event->button()==Qt::LeftButton){
        int mouseX = event->x();
        int mouseY = event->y();
        foreach(TowerPosition point, m_towerPositionsList){
            int towerX = point.centerPos().x();
            int towerY = point.centerPos().y();
            if(qAbs(towerX-mouseX) <= 20 && qAbs(towerY-mouseY) <= 20){
                towerPosition = point;
                if(towerPosition.hasTower() > 0){
                    QMenu *menu = new QMenu(this);

                    menu->setStyleSheet("QMenu::item{ padding:15px;font-size:20px;}");
                    QAction *pNew1 = new QAction("攻击*2", this);
                    QAction *pNew2 = new QAction("范围*2", this);
                    QAction *pNew3 = new QAction("拆除塔", this);

                    menu->addAction(pNew1);
                    menu->addAction(pNew2);
                    menu->addAction(pNew3);

                    QSignalMapper *signalMapper = new QSignalMapper(this);

                    connect(pNew1, SIGNAL(triggered()), signalMapper, SLOT(map()));
                    connect(pNew2, SIGNAL(triggered()), signalMapper, SLOT(map()));
                    connect(pNew3, SIGNAL(triggered()), signalMapper, SLOT(map()));

                    signalMapper->setMapping(pNew1, 1);
                    signalMapper->setMapping(pNew2, 2);
                    signalMapper->setMapping(pNew3, 3);

                    connect(signalMapper, SIGNAL(mapped(int)), this, SLOT(upgrade(int)));

                    menu->move(cursor().pos());
                    menu->show();
                }
                else{
                    QMenu *menu = new QMenu(this);

                    menu->setStyleSheet("QMenu::item{ padding:25px;font-size:20px;}");
                    QAction *pNew1 = new QAction("建造地狱之塔1", this);
                    pNew1->setIcon(QIcon(":/image/helltower.png"));
                    QAction *pNew2 = new QAction("建造加农炮2", this);
                    pNew2->setIcon(QIcon(":/image/tower.png"));
                    QAction *pNew3 = new QAction("建造冰冻塔3", this);
                    pNew3->setIcon(QIcon(":/image/cannon.png"));

                    menu->addAction(pNew1);
                    menu->addAction(pNew2);
                    menu->addAction(pNew3);

                    QSignalMapper *signalMapper = new QSignalMapper(this);

                    connect(pNew1, SIGNAL(triggered()), signalMapper, SLOT(map()));
                    connect(pNew2, SIGNAL(triggered()), signalMapper, SLOT(map()));
                    connect(pNew3, SIGNAL(triggered()), signalMapper, SLOT(map()));

                    signalMapper->setMapping(pNew1, 1);
                    signalMapper->setMapping(pNew2, 2);
                    signalMapper->setMapping(pNew3, 3);

                    connect(signalMapper, SIGNAL(mapped(int)), this, SLOT(flagChange(int)));

                    menu->move(cursor().pos());
                    menu->show();
                }

            }
        }
    }
}

bool MainWindow11::canBuyTower() const
{
    if (m_playrGold >= TowerCost)
        return true;
    return false;
}

void MainWindow11::drawWave(QPainter *painter)
{
    painter->setPen(QPen(Qt::red));
    painter->drawText(QRect(800, 5, 100, 25), QString("WAVE : %1").arg(m_waves + 1));
}

void MainWindow11::drawHP(QPainter *painter)
{
    painter->setPen(QPen(Qt::red));
    painter->drawText(QRect(30, 5, 100, 25), QString("HP : %1").arg(m_playerHp));
}

void MainWindow11::drawXT(QPainter *painter)
{
    if(roundflag==1)
    {

        painter->save();

        QPoint healthBarPoint = QPoint(560,135) + QPoint(0, -5);
        // 绘制血条
        painter->setPen(Qt::NoPen);
        painter->setBrush(QColor(169,169,169));
        QRect healthBarBackRect(healthBarPoint, QSize(50, 6));
        painter->drawRect(healthBarBackRect);

        painter->setBrush(Qt::green);
        QRect healthBarRect(healthBarPoint, QSize((double)m_playerHp / 5 * 50, 6));
        //attackedcastle_music.setLoops(1);
        //attackedcastle_music.play();
        painter->drawRect(healthBarRect);

        painter->restore();
    }
    if(roundflag==2)
    {
        painter->save();

        QPoint healthBarPoint = QPoint(900,330) + QPoint(0, -5);
        // 绘制血条
        painter->setPen(Qt::NoPen);
        painter->setBrush(QColor(169,169,169));
        QRect healthBarBackRect(healthBarPoint, QSize(50, 6));
        painter->drawRect(healthBarBackRect);

        painter->setBrush(Qt::green);
        QRect healthBarRect(healthBarPoint, QSize((double)m_playerHp / 5 * 50, 6));
        //attackedcastle_music.setLoops(1);
        //attackedcastle_music.play();
        painter->drawRect(healthBarRect);

        painter->restore();
    }

}


void MainWindow11::drawPlayerGold(QPainter *painter)
{
    painter->setPen(QPen(Qt::yellow));
    painter->drawText(QRect(400, 5, 200, 25), QString("GOLD : %1").arg(m_playrGold));
}

void MainWindow11::doGameOver()
{
    if (!m_gameEnded)
    {
        m_gameEnded = true;

    }
}

void MainWindow11::awardGold(int gold)
{
    m_playrGold += gold;
    //收集到金币攻击敌人的声音
   //collectpotion_music.setLoops(1);
  // collectpotion_music.play();
    update();
}

AudioPlayer *MainWindow11::audioPlayer() const
{
    return m_audioPlayer;
}

void MainWindow11::addWayPoints()
{

    if(roundflag==1)
    {
        WayPoint *wayPoint1 = new WayPoint(QPoint(600,160));
        m_wayPointsList.push_back(wayPoint1);

        WayPoint *wayPoint2 = new WayPoint(QPoint(417,160));
        m_wayPointsList.push_back(wayPoint2);
        wayPoint2->setNextWayPoint(wayPoint1);

        WayPoint *wayPoint3 = new WayPoint(QPoint(417,545));
        m_wayPointsList.push_back(wayPoint3);
        wayPoint3->setNextWayPoint(wayPoint2);

        WayPoint *wayPoint4 = new WayPoint(QPoint(160,545));
        m_wayPointsList.push_back(wayPoint4);
        wayPoint4->setNextWayPoint(wayPoint3);

        WayPoint *wayPoint5 = new WayPoint(QPoint(160,231));
        m_wayPointsList.push_back(wayPoint5);
        wayPoint5->setNextWayPoint(wayPoint4);

        WayPoint *wayPoint6 = new WayPoint(QPoint(35,231));
        m_wayPointsList.push_back(wayPoint6);
        wayPoint6->setNextWayPoint(wayPoint5);

        //同窗口的第二波怪物
        WayPoint *wayPoint11 = new WayPoint(QPoint(600,160));
        m_wayPointsList1.push_back(wayPoint11);

        WayPoint *wayPoint12 = new WayPoint(QPoint(863, 160));
        m_wayPointsList1.push_back(wayPoint12);
        wayPoint12->setNextWayPoint(wayPoint11);

        WayPoint *wayPoint13 = new WayPoint(QPoint(863, 675));
        m_wayPointsList1.push_back(wayPoint13);
        wayPoint13->setNextWayPoint(wayPoint12);

        WayPoint *wayPoint14 = new WayPoint(QPoint(900, 675));
        m_wayPointsList1.push_back(wayPoint14);
        wayPoint14->setNextWayPoint(wayPoint13);
     }
     if(roundflag==2)
     {

         WayPoint *wayPoint1 = new WayPoint(QPoint(1024,296));
         m_wayPointsList.push_back(wayPoint1);

         WayPoint *wayPoint2 = new WayPoint(QPoint(675,296));
         m_wayPointsList.push_back(wayPoint2);
         wayPoint2->setNextWayPoint(wayPoint1);

         WayPoint *wayPoint3 = new WayPoint(QPoint(675,231));
         m_wayPointsList.push_back(wayPoint3);
         wayPoint3->setNextWayPoint(wayPoint2);



         WayPoint *wayPoint4= new WayPoint(QPoint(35,231));//对
         m_wayPointsList.push_back(wayPoint4);
         wayPoint4->setNextWayPoint(wayPoint3);

         //同窗口的第二波怪物
        WayPoint *wayPoint11 = new WayPoint(QPoint(1024,485));
         m_wayPointsList1.push_back(wayPoint11);

         WayPoint *wayPoint12 = new WayPoint(QPoint(675, 485));
         m_wayPointsList1.push_back(wayPoint12);
         wayPoint12->setNextWayPoint(wayPoint11);

         WayPoint *wayPoint13 = new WayPoint(QPoint(675,550));
         m_wayPointsList1.push_back(wayPoint13);
         wayPoint13->setNextWayPoint(wayPoint12);

         WayPoint *wayPoint14 = new WayPoint(QPoint(35, 550));
         m_wayPointsList1.push_back(wayPoint14);
         wayPoint14->setNextWayPoint(wayPoint13);
     }

}

void MainWindow11::getHpDamage(int damage/* = 1*/)
{
    attackedcastle_music.setLoops(1);
    attackedcastle_music.play();
    m_playerHp -= damage;
    if (m_playerHp <= 0)
        doGameOver();
}

void MainWindow11::removedEnemy(Enemy *enemy)
{
    Q_ASSERT(enemy);

    m_enemyList.removeOne(enemy);
    m_enemyList1.removeOne(enemy);
    delete enemy;

    if (m_enemyList.empty()&&m_enemyList1.empty())
    {
        ++m_waves;
        if (!loadWave())
        {
            m_gameWin = true;
            //win_music.setLoops(1);
            //win_music.play();
            // 游戏胜利转到游戏胜利场景
            // 这里暂时以打印处理
        }
    }
}

void MainWindow11::removeDeath()
{
    int p = 0;
    while (p < moneylist.count())
    {
        if (!(moneylist[p]->alive))
        {
            enemydie_music.setLoops(1);
            enemydie_music.play();
            delete (moneylist[p]);
            moneylist.removeAt(p);
        }
        else
        {
            p++;
        }
    }
}
void MainWindow11::removedBullet(Bullet *bullet)
{
    Q_ASSERT(bullet);

    m_bulletList.removeOne(bullet);
    delete bullet;
}

void MainWindow11::addBullet(Bullet *bullet)
{
    Q_ASSERT(bullet);

    m_bulletList.push_back(bullet);
}

void MainWindow11::removedCannonBullet(CannonBullet *cannonbullet)
{
    Q_ASSERT(cannonbullet);

    m_cannonbulletList.removeOne(cannonbullet);
    delete cannonbullet;
}

void MainWindow11::addCannonBullet(CannonBullet *cannonbullet)
{
    Q_ASSERT(cannonbullet);

    m_cannonbulletList.push_back(cannonbullet);
}

void MainWindow11::removedIceBullet(IceBullet *icebullet)
{
    Q_ASSERT(icebullet);

    m_icebulletList.removeOne(icebullet);
    delete icebullet;
}

void MainWindow11::addIceBullet(IceBullet *icebullet)
{
    Q_ASSERT(icebullet);

    m_icebulletList.push_back(icebullet);
}




void MainWindow11::updateMap()
{
    foreach (Enemy *enemy, m_enemyList)
        enemy->move();
    foreach (Enemy *enemy1, m_enemyList1)
        enemy1->move();
    foreach (Tower *tower, m_towersList)
        tower->checkEnemyInRange();
    foreach (Cannon *cannon, m_cannonList)
        cannon->checkEnemyInRange();
    foreach (IceTower *icetower, m_icetowerList)
        icetower->checkEnemyInRange();

    this->removeDeath();
    this->act();
    if (qrand() % 200 < 1)
    {
        money* sun = new zSunFall(this);
        collectpotion_music.setLoops(1);
        collectpotion_music.play();
        sun->setgame(this);
        moneylist.append(sun);
    }
   // this->exit->raise();
    update();
}

void MainWindow11::preLoadWavesInfo()
{
    if(roundflag==1)
    {
    QFile file(":/config/Waves.plist");
    if (!file.open(QFile::ReadOnly | QFile::Text))
    {
        QMessageBox::warning(this, "TowerDefense", "Cannot Open TowersPosition.plist");
        return;
    }

    PListReader reader;
    reader.read(&file);

    // 获取波数信息
    m_wavesInfo = reader.data();

    file.close();
    }
    if(roundflag==2)
    {
        QFile file(":/config/Waves2.plist");
        if (!file.open(QFile::ReadOnly | QFile::Text))
        {
            QMessageBox::warning(this, "TowerDefense", "Cannot Open TowersPosition.plist");
            return;
        }

        PListReader reader;
        reader.read(&file);

        // 获取波数信息
        m_wavesInfo = reader.data();

        file.close();
    }
}

bool MainWindow11::loadWave()
{
    if(roundflag==1)
    {

        if (m_waves >= m_wavesInfo.size())
            return false;

        WayPoint *startWayPoint = m_wayPointsList.back();
        WayPoint *startWayPoint1 = m_wayPointsList1.back();
        QList<QVariant> curWavesInfo = m_wavesInfo[m_waves].toList();

        for (int i = 0; i < curWavesInfo.size(); ++i)
        {
            QMap<QString, QVariant> dict = curWavesInfo[i].toMap();
            int spawnTime = dict.value("spawnTime").toInt();

            Enemy *enemy = new Enemy(startWayPoint, this, false);
            Enemy *enemy1 = new Enemy(startWayPoint1, this, true, QPixmap(":/image/enemy2.jpg"));
            m_enemyList.push_back(enemy);
            m_enemyList1.push_back(enemy1);
            QTimer::singleShot(spawnTime, enemy, SLOT(doActivate()));
            QTimer::singleShot(spawnTime, enemy1, SLOT(doActivate()));
        }
    }
    if(roundflag==2)
    {
        if (m_waves >= m_wavesInfo.size())
            return false;

        WayPoint *startWayPoint = m_wayPointsList.back();
        WayPoint *startWayPoint1 = m_wayPointsList1.back();
        QList<QVariant> curWavesInfo = m_wavesInfo[m_waves].toList();

        for (int i = 0; i < curWavesInfo.size(); ++i)
        {
            QMap<QString, QVariant> dict = curWavesInfo[i].toMap();
            int spawnTime = dict.value("spawnTime").toInt();

            Enemy *enemy = new Enemy(startWayPoint, this, false);
            Enemy *enemy1 = new Enemy(startWayPoint1, this, false, QPixmap(":/image/enemy2.jpg"));
            m_enemyList.push_back(enemy);
            m_enemyList1.push_back(enemy1);
            QTimer::singleShot(spawnTime, enemy, SLOT(doActivate()));
            QTimer::singleShot(spawnTime, enemy1, SLOT(doActivate()));
        }
    }

    return true;
}

QList<Enemy *> MainWindow11::enemyList() const
{
    return m_enemyList;

}
QList<Enemy *> MainWindow11::enemyList1() const
{

    return m_enemyList1;
}

void MainWindow11::gameStart()
{
    loadWave();
}

#ifndef MAINWINDOW11_H
#define MAINWINDOW11_H

#include <QMainWindow>
#include "towerposition.h"
#include "tower.h"
#include "cannon.h"
#include "icetower.h"
#include "supercastle.h"
#include "castle.h"
#include "money.h"
#include "icebullet.h"
#include <QList>
#include <bgmusic.h>
#include <QSound>
#include <QString>
#include <QSignalMapper>

namespace Ui {
class MainWindow11;
}
class WayPoint;
class Enemy;
class Bullet;
class CannonBullet;
class IceBullet;
class AudioPlayer;

class MainWindow11 : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow11(QWidget *parent = nullptr,int roundflag=0);
    ~MainWindow11();

    void getHpDamage(int damage = 1);
    void removedEnemy(Enemy *enemy);
    void removedBullet(Bullet *bullet);
    void addBullet(Bullet *bullet);
    void removedCannonBullet(CannonBullet *cannonbullet);
    void addCannonBullet(CannonBullet *cannonbullet);
    void removedIceBullet(IceBullet *icebullet);
    void addIceBullet(IceBullet *icebullet);
    void awardGold(int gold);
//    void contextMenuEvent(QContextMenuEvent *event);

    AudioPlayer* audioPlayer() const;
    QList<Enemy *> enemyList() const;
    QList<Enemy *> enemyList1() const;

    bool attackStatus = false;

public slots:
    void updateMap();
    void gameStart();

    void flagChange(int towerId);
    void upgrade(int type);

    bool attactTower(QPoint point);

protected:
    void paintEvent(QPaintEvent *);
    void mousePressEvent(QMouseEvent *);

private:
    Ui::MainWindow11 *ui;

    void loadTowerPositions();
    void addWayPoints();
    bool loadWave();
    bool canBuyTower() const;
    void drawWave(QPainter *painter);
    void drawHP(QPainter *painter);
    void drawXT(QPainter *painter);
    void drawPlayerGold(QPainter *painter);
    void doGameOver();
    void preLoadWavesInfo();
    void act();
    void removeDeath();
    QList<money*> moneylist;



    //数据成员
    bool                    menuShow;
    int						m_waves;
    int						m_playerHp;
    int						m_playrGold;
     int roundflag;
    bool					m_gameEnded;
    bool					m_gameWin;
    Castle                  castle;
    supercastle             castle2;
    AudioPlayer *			m_audioPlayer;
    QList<QVariant>			m_wavesInfo;
    QList<TowerPosition>	m_towerPositionsList;
    QList<Tower *>			m_towersList;
    QList<Cannon *>         m_cannonList;
    QList<IceTower * >      m_icetowerList;
    QList<WayPoint *>		m_wayPointsList;
    QList<WayPoint *>		m_wayPointsList1;

    QList<Enemy *>			m_enemyList;
    QList<Enemy *>			m_enemyList1;
    QList<Bullet *>			m_bulletList;
    QList<CannonBullet *>   m_cannonbulletList;
    QList<IceBullet *>      m_icebulletList;

    BgMusic attackedcastle_music;
    BgMusic collectpotion_music ;
    BgMusic enemydie_music ;
    BgMusic neverend_music;
    BgMusic settower_music ;
    BgMusic win_music;
    TowerPosition         towerPosition;


};

#endif // MAINWINDOW11_H

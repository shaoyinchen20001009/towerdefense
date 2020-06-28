#ifndef BGMUSIC_H
#define BGMUSIC_H
#include <QSound>
#include<QString>

const QString _attackedcastle_music = ":/music/attackedcastle_music.wav";
const QString _collectpotion_music = ":/music/collectpotion_music.wav";
const QString _enemydie_music = ":/music/enemydie_music.wav";
const QString _neverend_music= ":/music/neverend_music.wav";
const QString _settower_music = ":/music/settower_music.wav";
const QString _win_music= ":/music/win_music.wav";


class BgMusic : public QSound
{
public:
    BgMusic(const QString& filename):QSound(filename)
    {
        setLoops(QSound::Infinite);
    }
};

#endif // BGMUSIC_H

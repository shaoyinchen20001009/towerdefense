#ifndef CASTLE_H
#define CASTLE_H

#include <QPoint>
#include <QSize>
#include <QPixmap>

class QPainter;

class Castle
{
public:
    Castle(const QPixmap &sprite = QPixmap(":/image/大本营.png"));


    void draw(QPainter *painter) const;

private:

    QPixmap		m_sprite;

    static const QSize ms_fixedSize;
};

#endif // CASTLE_H

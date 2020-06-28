#ifndef SUPERCASTLE_H
#define SUPERCASTLE_H


#include <QPoint>
#include <QSize>
#include <QPixmap>
#include<castle.h>

class QPainter;

class supercastle:public Castle
{
public:
    supercastle(const QPixmap &sprite = QPixmap(":/image/supercastle.png"));


    void draw(QPainter *painter) const;

private:

    QPixmap		m_sprite;

    static const QSize ms_fixedSize;
};



#endif // SUPERCASTLE_H

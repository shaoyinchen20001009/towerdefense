#include "castle.h"


#include "QPainter"

const QSize Castle::ms_fixedSize(50, 50);

Castle::Castle(const QPixmap &sprite)
    : m_sprite(sprite)
{
}


void Castle::draw(QPainter *painter) const
{
    painter->drawPixmap(500, 120, m_sprite);
}

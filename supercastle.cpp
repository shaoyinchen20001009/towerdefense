#include "supercastle.h"


#include "QPainter"

const QSize supercastle::ms_fixedSize(50, 50);

supercastle::supercastle(const QPixmap &sprite)
    : m_sprite(sprite)
{
}


void supercastle::draw(QPainter *painter) const
{
    painter->drawPixmap(865, 270, m_sprite);
}

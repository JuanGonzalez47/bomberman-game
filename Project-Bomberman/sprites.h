#ifndef SPRITES_H
#define SPRITES_H

#include <QGraphicsPixmapItem>
#include <QObject>
#include <QString>

using namespace std;

#define dimension_block 16
#define map_scale 3

class sprites : public QObject, public QGraphicsPixmapItem
{
private:
    QPixmap sprites_bomberman,fondo,copy,image;
    int animation_counter;

public:
    sprites();
    QPixmap set_block(unsigned int type);
    QPixmap set_sprite_for_animation(unsigned int pos_x, unsigned int pos_y);

};

#endif // SPRITES_H

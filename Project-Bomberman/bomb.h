#ifndef BOMB_H
#define BOMB_H

#include "bomberman_character.h"
#include <Qtimer>

class bomb : public QObject, public QGraphicsPixmapItem
{
private:
    QGraphicsPixmapItem *bomb_image, *burst_image, *block_destruction_image;
    QPixmap *bomb_, *burst_, burst_animation_, copy_, *block_Destruction_;
    int animation_counter_ = -1, animation_counter = -1;

public:
    bomb();
    QGraphicsPixmapItem *set_bomb();
    QGraphicsPixmapItem *set_burst();
    QGraphicsPixmapItem *set_destruction_block();
    QPixmap burst_animation_image(QString name_image);
    void burst_animation(QGraphicsPixmapItem *burst_image_);
    void bomb_animation(QGraphicsPixmapItem *bomba_image);
    void destruction_animation(QGraphicsPixmapItem *destruction_image, int counter);
    bool ask_up(map<pair<unsigned int, unsigned int>,unsigned int> coordinates, unsigned int pos_x, unsigned int pos_y);
    bool ask_down(map<pair<unsigned int, unsigned int>,unsigned int> coordinates, unsigned int pos_x, unsigned int pos_y);
    bool ask_left(map<pair<unsigned int, unsigned int>,unsigned int> coordinates, unsigned int pos_x, unsigned int pos_y);
    bool ask_rigth(map<pair<unsigned int, unsigned int>,unsigned int> coordinates, unsigned int pos_x, unsigned int pos_y);

};

#endif // BOMB_H

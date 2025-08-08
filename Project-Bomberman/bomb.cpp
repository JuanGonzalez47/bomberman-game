#include "bomb.h"

bomb::bomb()
{

}


QGraphicsPixmapItem* bomb::set_bomb()
{
    sprites sprite_aux_;

    unsigned int cont = 0;
    bomb_ = new QPixmap[3];
    unsigned int y = 3;
    for(unsigned int x = 0; x < 3; x++){
        bomb_[cont] = sprite_aux_.set_sprite_for_animation(x,y);
        cont++;
    }
    bomb_image = new QGraphicsPixmapItem(bomb_[0]);

    return bomb_image;

}

QGraphicsPixmapItem *bomb::set_burst()
{
    burst_ = new QPixmap[4];
    burst_[0] = burst_animation_image(":/image_bust/Images/explosion1.png");
    burst_[1] = burst_animation_image(":/image_bust/Images/explosion2.png");
    burst_[2] = burst_animation_image(":/image_bust/Images/explosion3.png");
    burst_[3] = burst_animation_image(":/image_bust/Images/explosion4.png");


    burst_image = new QGraphicsPixmapItem(burst_[0]);

    return burst_image;
}


QGraphicsPixmapItem *bomb::set_destruction_block()
{
    unsigned int cont = 0;
    sprites sprite_aux_;

    block_Destruction_ = new QPixmap[8];

    unsigned int y = 3;

    for(unsigned int x = 4; x < 11; x++){
        block_Destruction_[cont] = sprite_aux_.set_sprite_for_animation(x,y);
        cont++;
    }

    block_Destruction_[7] = sprite_aux_.set_block(0);

    block_destruction_image = new QGraphicsPixmapItem(block_Destruction_[0]);

    return block_destruction_image;
}


QPixmap bomb::burst_animation_image(QString name_image)
{
    burst_animation_.load(name_image);
    setPixmap(burst_animation_);
    copy_ = burst_animation_.copy(0,0,burst_animation_.width(),burst_animation_.height()).scaled(burst_animation_.width()*map_scale,(burst_animation_.height()*map_scale));
    setPixmap(copy_);

    return copy_;
}

void bomb::burst_animation(QGraphicsPixmapItem *burst_image_)
{
    if (animation_counter_ == 4) {
        animation_counter_ --;
        burst_image_->setPixmap(burst_[animation_counter_ -=1]);
        if (animation_counter_== 1) animation_counter_ = 5;
    }
    else if (animation_counter_ <= 3) {
        animation_counter_++;
        burst_image_->setPixmap(burst_[animation_counter_]);
        if(animation_counter_ == 3) animation_counter_ = 4;
    }
}

void bomb::bomb_animation(QGraphicsPixmapItem *bomba_image)
{
    animation_counter++;
    if (animation_counter == 3) animation_counter = 0;
    bomba_image->setPixmap(bomb_[animation_counter]);

}

void bomb::destruction_animation(QGraphicsPixmapItem *destruction_image, int counter)
{
   destruction_image->setPixmap(block_Destruction_[counter]);
}

bool bomb::ask_up(map<pair<unsigned int, unsigned int>, unsigned int> coordinates, unsigned int pos_x, unsigned int pos_y)
{
    if (coordinates[pair<unsigned int,unsigned int>(pos_x/(dimension_block*map_scale),(pos_y/(dimension_block*map_scale))-1)] == 2) return true;
    else return false;
}

bool bomb::ask_down(map<pair<unsigned int, unsigned int>, unsigned int> coordinates, unsigned int pos_x, unsigned int pos_y)
{
    if (coordinates[pair<unsigned int,unsigned int>(pos_x/(dimension_block*map_scale),(pos_y/(dimension_block*map_scale))+1)] == 2) return true;
    else return false;
}

bool bomb::ask_left(map<pair<unsigned int, unsigned int>, unsigned int> coordinates, unsigned int pos_x, unsigned int pos_y)
{
    if (coordinates[pair<unsigned int,unsigned int>((pos_x/(dimension_block*map_scale))-1,pos_y/(dimension_block*map_scale))] == 2) return true;
    else return false;
}

bool bomb::ask_rigth(map<pair<unsigned int, unsigned int>, unsigned int> coordinates, unsigned int pos_x, unsigned int pos_y)
{
    if (coordinates[pair<unsigned int,unsigned int>((pos_x/(dimension_block*map_scale))+1,pos_y/(dimension_block*map_scale))] == 2) return true;
    else return false;
}






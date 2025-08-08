#include "bomberman_character.h"

void bomberman_character::up_movement(QPixmap *bomber, QGraphicsPixmapItem *bomberman_image,map<pair<unsigned int, unsigned int>,unsigned int> coordinates)
{
    if (animation_counter_W == 11) animation_counter_W = 9;
    else animation_counter_W ++;

    switch (animation_counter_W){
    case 9:
        bomberman_image->setPixmap(bomber[animation_counter_W]);
        if (verify_up_movement(bomberman_image,coordinates)) bomberman_image->setY(bomberman_image->y()-speed);
        break;
    case 10:
        bomberman_image->setPixmap(bomber[animation_counter_W]);
        if (verify_up_movement(bomberman_image,coordinates)) bomberman_image->setY(bomberman_image->y()-speed);
        break;
    case 11:
        bomberman_image->setPixmap(bomber[animation_counter_W]);
        if (verify_up_movement(bomberman_image,coordinates)) bomberman_image->setY(bomberman_image->y()-speed);
        break;
    }
}

void bomberman_character::left_movement(QPixmap *bomber, QGraphicsPixmapItem *bomberman_image, map<pair<unsigned int, unsigned int>,unsigned int> coordinates)
{
    if (animation_counter_A == 2) animation_counter_A = 0;
    else animation_counter_A ++;
    switch (animation_counter_A){
    case 0:
        bomberman_image->setPixmap(bomber[animation_counter_A]);
        if (verify_left_movement(bomberman_image,coordinates)) bomberman_image->setX(bomberman_image->x()-speed);
        break;
    case 1:
        bomberman_image->setPixmap(bomber[animation_counter_A]);
        if (verify_left_movement(bomberman_image,coordinates)) bomberman_image->setX(bomberman_image->x()-speed);
        break;
    case 2:
        bomberman_image->setPixmap(bomber[animation_counter_A]);
        if (verify_left_movement(bomberman_image,coordinates)) bomberman_image->setX(bomberman_image->x()-speed);
        break;
    }
}

void bomberman_character::rigth_movement(QPixmap *bomber, QGraphicsPixmapItem *bomberman_image,map<pair<unsigned int, unsigned int>,unsigned int> coordinates)
{
    if (animation_counter_D == 8) animation_counter_D = 6;
    else animation_counter_D ++;

    switch (animation_counter_D){
    case 6:
        bomberman_image->setPixmap(bomber[animation_counter_D]);
        if (verify_right_movement(bomberman_image,coordinates)) bomberman_image->setX(bomberman_image->x()+speed);
        break;
    case 7:
        bomberman_image->setPixmap(bomber[animation_counter_D]);
        if (verify_right_movement(bomberman_image,coordinates)) bomberman_image->setX(bomberman_image->x()+speed);
        break;
    case 8:
        bomberman_image->setPixmap(bomber[animation_counter_D]);
        if (verify_right_movement(bomberman_image,coordinates)) bomberman_image->setX(bomberman_image->x()+speed);
        break;
    }
}

void bomberman_character::down_movement(QPixmap *bomber, QGraphicsPixmapItem *bomberman_image, map<pair<unsigned int, unsigned int>,unsigned int> coordinates)
{
    if (animation_counter_S == 5) animation_counter_S = 3;
    else animation_counter_S ++;
    switch (animation_counter_S){
    case 3:
        bomberman_image->setPixmap(bomber[animation_counter_S]);
        if(verify_down_movement(bomberman_image, coordinates)) bomberman_image->setY(bomberman_image->y()+speed);
        break;
    case 4:
        bomberman_image->setPixmap(bomber[animation_counter_S]);
        if(verify_down_movement(bomberman_image, coordinates)) bomberman_image->setY(bomberman_image->y()+speed);
        break;
    case 5:
        bomberman_image->setPixmap(bomber[animation_counter_S]);
        if(verify_down_movement(bomberman_image, coordinates)) bomberman_image->setY(bomberman_image->y()+speed);
        break;
    }
}

void bomberman_character::dead_animation(QPixmap *bomber, QGraphicsPixmapItem *bomberman_image, int counter)
{
    bomberman_image->setPixmap(bomber[counter]);
}

bool bomberman_character::verify_up_movement(QGraphicsPixmapItem *bomberman, map<pair<unsigned int, unsigned int>,unsigned int> coordinates)
{
    int xf1,xf2,yf1, width;
    bool valid_1, valid_2;

    width = bomberman->pixmap().width();

    xf1 = bomberman->x();
    yf1 = bomberman->y() - speed;
    xf2 = bomberman->x() + width -1;

    valid_1 = coordinates[pair<unsigned int,unsigned int>(xf1/(dimension_block*map_scale),yf1/(dimension_block*map_scale))] == 0;
    valid_2 = coordinates[pair<unsigned int,unsigned int>(xf2/(dimension_block*map_scale),yf1/(dimension_block*map_scale))] == 0;

    return valid_1 && valid_2;


}

bool bomberman_character::verify_right_movement(QGraphicsPixmapItem *bomberman, map<pair<unsigned int, unsigned int>, unsigned int> coordinates)
{
    int xf1,yf1,yf2, width, height;
    bool valid_1, valid_2;

    width = bomberman->pixmap().width();
    height = bomberman->pixmap().height();

    xf1 = bomberman->x() + width -1 + speed;
    yf1 = bomberman->y();
    yf2 = bomberman->y() + height -1;

    valid_1 = coordinates[pair<unsigned int,unsigned int>(xf1/(dimension_block*map_scale),yf1/(dimension_block*map_scale))] == 0;
    valid_2 = coordinates[pair<unsigned int,unsigned int>(xf1/(dimension_block*map_scale),yf2/(dimension_block*map_scale))] == 0;

    return valid_1 && valid_2;


}

bool bomberman_character::verify_left_movement(QGraphicsPixmapItem *bomberman, map<pair<unsigned int, unsigned int>, unsigned int> coordinates)
{
    int xf1,yf1,yf2, height;
    bool valid_1, valid_2;

    height = bomberman->pixmap().height();

    xf1 = bomberman->x() - speed;
    yf1 = bomberman->y();
    yf2 = bomberman->y() + height -1;

    valid_1 = coordinates[pair<unsigned int,unsigned int>(xf1/(dimension_block*map_scale),yf1/(dimension_block*map_scale))] == 0;
    valid_2 = coordinates[pair<unsigned int,unsigned int>(xf1/(dimension_block*map_scale),yf2/(dimension_block*map_scale))] == 0;


    return valid_1 && valid_2;
}

bool bomberman_character::verify_down_movement(QGraphicsPixmapItem *bomberman, map<pair<unsigned int, unsigned int>, unsigned int> coordinates)
{
    int xf1,xf2,yf1, width;
    bool valid_1, valid_2;

    width = bomberman->pixmap().width();

    xf1 = bomberman->x();
    yf1 = bomberman->y() + bomberman->pixmap().width() - 1 + speed;
    xf2 = bomberman->x() + width - 1;

    valid_1 = coordinates[pair<unsigned int,unsigned int>(xf1/(dimension_block*map_scale),yf1/(dimension_block*map_scale))] == 0;
    valid_2 = coordinates[pair<unsigned int,unsigned int>(xf2/(dimension_block*map_scale),yf1/(dimension_block*map_scale))] == 0;


    return valid_1 && valid_2;
}

bool bomberman_character::ask_bomberman_up(unsigned int pos_y_burst, unsigned int pos_y_bomberman, unsigned int pos_x_burst, unsigned int pos_x_bomberman)
{
    unsigned int value;
    if (pos_x_burst > pos_x_bomberman) value = pos_x_burst - pos_x_bomberman;
    else value = pos_x_bomberman - pos_x_burst;
    if (pos_y_burst - (pos_y_bomberman+(dimension_block*map_scale)) < dimension_block*map_scale - 16 && value < dimension_block*map_scale - 16) return true;
    else return false;

}

bool bomberman_character::ask_bomberman_down(unsigned int pos_y_burst, unsigned int pos_y_bomberman, unsigned int pos_x_burst, unsigned int pos_x_bomberman)
{
    unsigned int value, value1;
    if (pos_x_burst > pos_x_bomberman) value = pos_x_burst - pos_x_bomberman;
    else value = pos_x_bomberman - pos_x_burst;
    if (pos_y_bomberman + (dimension_block*map_scale) < pos_y_burst) value1 = pos_y_bomberman;
    else value1 = pos_y_bomberman + (dimension_block*map_scale);
    if (pos_y_bomberman - (pos_y_burst + (dimension_block*map_scale)) < dimension_block*map_scale - 16 && value < dimension_block*map_scale - 16) return true;
    else return false;
}

bool bomberman_character::ask_bomberman_right(unsigned int pos_x_burst, unsigned int pos_x_bomberman, unsigned int pos_y_burst, unsigned int pos_y_bomberman)
{
    unsigned int value;
    if (pos_y_burst > pos_y_bomberman) value = pos_y_burst - pos_y_bomberman;
    else value = pos_y_bomberman - pos_y_burst;
    if (pos_x_bomberman - (pos_x_burst + (dimension_block*map_scale)) < dimension_block*map_scale - 16 && value < dimension_block*map_scale -16) return true;
    else return false;
}

bool bomberman_character::ask_bomberman_left(unsigned int pos_x_burst, unsigned int pos_x_bomberman, unsigned int pos_y_burst, unsigned int pos_y_bomberman)
{
    unsigned int value, value1;
    if (pos_y_burst > pos_y_bomberman) value = pos_y_burst - pos_y_bomberman;
    else value = pos_y_bomberman - pos_y_burst;
    if (pos_x_bomberman + (dimension_block*map_scale) > pos_x_burst) value1 = pos_x_bomberman;
    else value1 = pos_x_bomberman + (dimension_block*map_scale);
    if (pos_x_burst - value1  < (dimension_block*map_scale) - 16 && value < dimension_block*map_scale -16) return true;
    else return false;
}

bool bomberman_character::ask_bomberman_on_fire(unsigned int pos_x_burst, unsigned int pos_x_bomberman, unsigned int pos_y_bomberman, unsigned int pos_y_burst)
{
    if ((pos_x_burst/(dimension_block*map_scale)) == (pos_x_bomberman/(dimension_block*map_scale)) && (pos_y_burst/(dimension_block*map_scale)) == (pos_y_bomberman/(dimension_block*map_scale))) return true;
    else return false;
}




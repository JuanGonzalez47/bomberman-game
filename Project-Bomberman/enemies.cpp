#include "enemies.h"
#include <QTimer>


enemies::enemies()
{
    unsigned int cont = 0;
    sprites sprite_aux_;

    enemy_image_ = new QPixmap[11];

    unsigned int y = 15;

    for(unsigned int x = 0; x < 11; x++){
        enemy_image_[cont] = sprite_aux_.set_sprite_for_animation(x,y);
        cont++;
    }
}

QGraphicsPixmapItem * enemies::set_enemy()
{
    unsigned int cont = 0;
    sprites sprite_aux_;

    enemy_image_ = new QPixmap[11];

    unsigned int y = 15;

    for(unsigned int x = 0; x < 11; x++){
        enemy_image_[cont] = sprite_aux_.set_sprite_for_animation(x,y);
        cont++;
    }

    enemy_image = new QGraphicsPixmapItem(enemy_image_[0]);

    return enemy_image;

}

void enemies::up_movement(QGraphicsPixmapItem *enemy_image, map<pair<unsigned int, unsigned int>, unsigned int> coordinates)
{
    if (animation_counter_W == 2) animation_counter_W = 0;
    else animation_counter_W ++;

    switch (animation_counter_W){
    case 0:
        enemy_image->setPixmap(enemy_image_[animation_counter_W]);
        if (verify_up_movement(enemy_image,coordinates))enemy_image->setY(enemy_image->y()-speed_enemies);
        else confirm_change_direction_y_down = true;
        break;
    case 1:
        enemy_image->setPixmap(enemy_image_[animation_counter_W]);
        if (verify_up_movement(enemy_image,coordinates))enemy_image->setY(enemy_image->y()-speed_enemies);
        else confirm_change_direction_y_down = true;
        break;
    case 2:
        enemy_image->setPixmap(enemy_image_[animation_counter_W]);
        if (verify_up_movement(enemy_image,coordinates))enemy_image->setY(enemy_image->y()-speed_enemies);
        else confirm_change_direction_y_down = true;
        break;
    }
}

void enemies::down_movement(QGraphicsPixmapItem *enemy_image, map<pair<unsigned int, unsigned int>, unsigned int> coordinates)
{
    if (animation_counter_S == 5) animation_counter_S = 3;
    else animation_counter_S ++;

    switch (animation_counter_S){
    case 3:
        enemy_image->setPixmap(enemy_image_[animation_counter_S]);
        if (verify_down_movement(enemy_image,coordinates))enemy_image->setY(enemy_image->y()+speed_enemies);
        else confirm_change_direction_y_up = true;
        break;
    case 4:
        enemy_image->setPixmap(enemy_image_[animation_counter_S]);
        if (verify_down_movement(enemy_image,coordinates))enemy_image->setY(enemy_image->y()+speed_enemies);
        else confirm_change_direction_y_up = true;
        break;
    case 5:
        enemy_image->setPixmap(enemy_image_[animation_counter_S]);
        if (verify_down_movement(enemy_image,coordinates))enemy_image->setY(enemy_image->y()+speed_enemies);
        else confirm_change_direction_y_up = true;
        break;
    }
}

void enemies::left_movement(QGraphicsPixmapItem *enemy_image, map<pair<unsigned int, unsigned int>, unsigned int> coordinates)
{
    if (animation_counter_S == 5) animation_counter_S = 3;
    else animation_counter_S ++;

    switch (animation_counter_S){
    case 3:
        enemy_image->setPixmap(enemy_image_[animation_counter_S]);
        if (verify_left_movement(enemy_image,coordinates))enemy_image->setX(enemy_image->x()-speed_enemies);
        else confirm_change_direction_x_right = true;
        break;
    case 4:
        enemy_image->setPixmap(enemy_image_[animation_counter_S]);
        if (verify_left_movement(enemy_image,coordinates))enemy_image->setX(enemy_image->x()-speed_enemies);
        else confirm_change_direction_x_right = true;
        break;
    case 5:
        enemy_image->setPixmap(enemy_image_[animation_counter_S]);
        if (verify_left_movement(enemy_image,coordinates))enemy_image->setX(enemy_image->x()-speed_enemies);
        else confirm_change_direction_x_right = true;
        break;
    }
}

void enemies::right_movement(QGraphicsPixmapItem *enemy_image, map<pair<unsigned int, unsigned int>, unsigned int> coordinates)
{
    if (animation_counter_W == 2) animation_counter_W = 0;
    else animation_counter_W ++;

    switch (animation_counter_W){
    case 0:
        enemy_image->setPixmap(enemy_image_[animation_counter_W]);
        if (verify_right_movement(enemy_image,coordinates))enemy_image->setX(enemy_image->x()+speed_enemies);
        else confirm_change_direction_x_left = true;
        break;
    case 1:
        enemy_image->setPixmap(enemy_image_[animation_counter_W]);
        if (verify_right_movement(enemy_image,coordinates))enemy_image->setX(enemy_image->x()+speed_enemies);
        else confirm_change_direction_x_left = true;
        break;
    case 2:
        enemy_image->setPixmap(enemy_image_[animation_counter_W]);
        if (verify_right_movement(enemy_image,coordinates))enemy_image->setX(enemy_image->x()+speed_enemies);
        else confirm_change_direction_x_left = true;
        break;
    }
}

void enemies::dead_animation(QGraphicsPixmapItem *enemies_image, int counter)
{
    enemies_image->setPixmap(enemy_image_[counter]);
}

bool enemies::kill_bomberman(unsigned int x_bomb, unsigned int y_bomb, unsigned int x_enemy, unsigned int y_enemy)
{
    //caso en el que este arriba del enemigo
    if (x_bomb == x_enemy && (y_enemy - y_bomb) < (dimension_block*map_scale) - 16) return true;
    //izquierda
    else if (y_bomb == y_enemy && x_bomb - x_enemy < (dimension_block*map_scale) - 16) return true;
    //derecha
    else if (y_bomb == y_enemy && x_enemy - x_bomb  < (dimension_block*map_scale) - 16) return true;
    //abajo
    else if (x_bomb == x_enemy && y_bomb - y_enemy < (dimension_block*map_scale) - 16) return true;
    else return false;
}

bool enemies::get_confirm_change_direction_y_up()
{
    return confirm_change_direction_y_up;
}

bool enemies::get_confirm_change_direction_y_down()
{
    return confirm_change_direction_y_down;
}

bool enemies::get_confirm_bool_change_direction_x_right()
{
    return confirm_change_direction_x_right;
}

bool enemies::get_confirm_bool_change_direction_x_left()
{
    return confirm_change_direction_x_left;
}

void enemies::set_confirm_change_direction_x_right(bool value)
{
    confirm_change_direction_x_right = value;
}

void enemies::set_confirm_change_direction_x_left(bool value)
{
    confirm_change_direction_x_left = value;
}

void enemies::set_confirm_change_direction_y_up(bool value)
{
    confirm_change_direction_y_up = value;
}

void enemies::set_confirm_change_direction_y_down(bool value)
{
    confirm_change_direction_y_down = value;
}

void enemies::set_verify_move(bool value)
{
    verify_move = value;
}

void enemies::set_move_in_y(bool value)
{
    move_in_y = value;
}

bool enemies::get_move_in_y()
{
    return move_in_y;
}

bool enemies::get_verify_move()
{
    return verify_move;
}





#ifndef ENEMIES_H
#define ENEMIES_H

#include "bomberman_character.h"
#define amount_enemies 10
#define speed_enemies 6

class enemies : public bomberman_character
{
private:
    unsigned int animation_counter_A = 3;
    unsigned int animation_counter_W = 0;
    unsigned int animation_counter_S = 3;
    unsigned int animation_counter_D = 0;
    QPixmap *enemy_image_;
    QGraphicsPixmapItem *enemy_image;
    bool confirm_change_direction_y_up = false;
    bool confirm_change_direction_y_down = false;
    bool confirm_change_direction_x_right = false;
    bool confirm_change_direction_x_left = false;
    bool move_in_y = false;
    bool verify_move = true;
public:
    enemies();
    QGraphicsPixmapItem *set_enemy();
    void up_movement(QGraphicsPixmapItem *enemy_image,map<pair<unsigned int, unsigned int>,unsigned int> coordinates);
    void down_movement(QGraphicsPixmapItem *enemy_image,map<pair<unsigned int, unsigned int>,unsigned int> coordinates);
    void left_movement(QGraphicsPixmapItem *enemy_image,map<pair<unsigned int, unsigned int>,unsigned int> coordinates);
    void right_movement(QGraphicsPixmapItem *enemy_image,map<pair<unsigned int, unsigned int>,unsigned int> coordinates);
    //confirmar cambio de direccion
    bool get_confirm_change_direction_y_up();
    bool get_confirm_change_direction_y_down();
    bool get_confirm_bool_change_direction_x_right();
    bool get_confirm_bool_change_direction_x_left();
    //setear las confirmaciones
    void set_confirm_change_direction_x_right(bool value);
    void set_confirm_change_direction_x_left(bool value);
    void set_confirm_change_direction_y_up(bool value);
    void set_confirm_change_direction_y_down(bool value);
    void set_verify_move(bool value);
    //definir en donde se movera
    void set_move_in_y(bool value);
    bool get_move_in_y();
    bool get_verify_move();
    //animacion de muerte
    void dead_animation(QGraphicsPixmapItem *enemies_image,int counter);
    //matar bomberman
    bool kill_bomberman(unsigned int x_bomb, unsigned int y_bomb, unsigned int x_enemy, unsigned int y_enemy);



};

#endif // ENEMIES_H

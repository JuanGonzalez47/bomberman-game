#ifndef BOMBERMAN_CHARACTER_H
#define BOMBERMAN_CHARACTER_H

#include <QGraphicsScene>
#include "sprites.h"
#define speed 6

using namespace std;



class bomberman_character
{
private:
    //contadores para cada una de las animaciones
    unsigned int animation_counter_A = 0;
    unsigned int animation_counter_W = 9;
    unsigned int animation_counter_S = 3;
    unsigned int animation_counter_D = 6;

public:
    //animacione sdel movimiento y muerte
    void up_movement(QPixmap *bomber, QGraphicsPixmapItem *bomberman_image,map<pair<unsigned int, unsigned int>,unsigned int> coordinates);
    void left_movement(QPixmap *bomber, QGraphicsPixmapItem *bomberman_image, map<pair<unsigned int, unsigned int>,unsigned int> coordinates);
    void rigth_movement(QPixmap *bomber, QGraphicsPixmapItem *bomberman_image,map<pair<unsigned int, unsigned int>,unsigned int> coordinates);
    void down_movement(QPixmap *bomber, QGraphicsPixmapItem *bomberman_image, map<pair<unsigned int, unsigned int>,unsigned int> coordinates);
    void dead_animation(QPixmap *bomber, QGraphicsPixmapItem *bomberman_image,int counter);
    bool verify_up_movement(QGraphicsPixmapItem *bomberman, map<pair<unsigned int, unsigned int>,unsigned int> coordinates);
    bool verify_right_movement(QGraphicsPixmapItem *bomberman, map<pair<unsigned int, unsigned int>,unsigned int> coordinates);
    bool verify_left_movement(QGraphicsPixmapItem *bomberman, map<pair<unsigned int, unsigned int>,unsigned int> coordinates);
    bool verify_down_movement(QGraphicsPixmapItem *bomberman, map<pair<unsigned int, unsigned int>,unsigned int> coordinates);
    bool ask_bomberman_up(unsigned int pos_y_burst, unsigned int pos_y_bomberman,unsigned int pos_x_burst, unsigned int pos_x_bomberman);
    bool ask_bomberman_down(unsigned int pos_y_burst, unsigned int pos_y_bomberman,unsigned int pos_x_burst, unsigned int pos_x_bomberman);
    bool ask_bomberman_right(unsigned int pos_x_burst, unsigned int pos_x_bomberman,unsigned int pos_y_burst, unsigned int pos_y_bomberman);
    bool ask_bomberman_left(unsigned int pos_x_burst, unsigned int pos_x_bomberman,unsigned int pos_y_burst, unsigned int pos_y_bomberman);
    bool ask_bomberman_on_fire(unsigned int pos_x_burst, unsigned int pos_x_bomberman, unsigned int pos_y_bomberman, unsigned int pos_y_burst);

};

#endif // BOMBERMAN_CHARACTER_H

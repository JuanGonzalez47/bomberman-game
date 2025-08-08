#include "sprites.h"

sprites::sprites()
{
    sprites_bomberman.load(":/Images/bomberma_sprites.png");
    setPixmap(sprites_bomberman);
    fondo.load(":/Images/fondo.png");
    setPixmap(fondo);
}



QPixmap sprites::set_block(unsigned int type)
{
    //tomar el bloque solido
    if(type == 1){
        copy = sprites_bomberman.copy(dimension_block*3,dimension_block*3,dimension_block, dimension_block).scaled(dimension_block*map_scale,dimension_block*map_scale);
        setPixmap(copy);
    }
    //tomar bloque de ladrillo
    else if (type == 2){
        copy = sprites_bomberman.copy(dimension_block*4,dimension_block*3,dimension_block, dimension_block).scaled(dimension_block*map_scale,dimension_block*map_scale);
        setPixmap(copy);
    }
    //tomar fondo
    else{
        copy = fondo.copy(0,0,dimension_block,dimension_block).scaled(dimension_block*map_scale,dimension_block*map_scale);
        setPixmap(copy);
    }
    return copy;
}


QPixmap sprites::set_sprite_for_animation(unsigned int pos_x,unsigned int pos_y)
{
    //se encargara de rotar las imagenes de un conjunto de sprites en especifico
    copy = sprites_bomberman.copy(dimension_block*pos_x,dimension_block*pos_y,dimension_block, dimension_block).scaled(dimension_block*map_scale,dimension_block*map_scale);
    setPixmap(copy);
    return copy;
}




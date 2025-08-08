#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <cstdlib>
#include <ctime>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    srand(time(nullptr));
    ui->setupUi(this);
    game = new QGraphicsScene;
    ui->graphicsView->setFixedSize(size_x*dimension_block*map_scale, size_y*dimension_block*map_scale);
    game->setSceneRect(0, 0, (size_x*dimension_block*map_scale) - 5, (size_y*dimension_block*map_scale) - 5);
    ui->graphicsView->setScene(game);
    set_map();
    set_bomberman_position();
    put_enemies_on_escene();
}

MainWindow::~MainWindow()
{
    delete ui;
    delete game;
}


void MainWindow::set_map()
{
    blocks = new unsigned int*[size_x];
    for(unsigned int i = 0;i< size_x; i++) blocks[i] = new unsigned int [size_y];

    for(unsigned int x = 0; x < size_x; x++){
        for(unsigned int y = 0; y < size_y; y++){
            //definir cuando voy a poner fondo
            if((y == 1 && x == 1) || (y == 1 && x == 2) || (y == 2 && x == 1) ) blocks[x][y] = 0;
            //definir cuando poner un bloque solido
            else if(x == 0 || y == 0 || x == size_x - 1 || y == size_y - 1 || (x % 2 == 0 && y % 2 == 0)) blocks[x][y] = 1;
            //reproducir evento aleatorio para poner un ladrillo
            else if(aleatory(difficult))  blocks[x][y] = 2;
            else blocks [x][y] = 0;
        }
    }
    show_map();
}

void MainWindow::show_map()
{

    for(unsigned int x = 0; x < size_x ; x++){
        for(unsigned int y = 0; y < size_y ; y++){
            if((y == 1 && x == 1) || (y == 1 && x == 2) || (y == 2 && x == 1)){
                choose_block[x][y] = new sprites();
                choose_block[x][y]->set_block(0);
                coordinates[pair<unsigned int,unsigned int>(x,y)] = 0;
                paint(map_scale*dimension_block*x,map_scale*dimension_block*y,0,choose_block[x][y]);
            }
            else if(blocks[x][y] == 0){
                choose_block[x][y] = new sprites();
                choose_block[x][y]->set_block(0);
                coordinates[pair<unsigned int,unsigned int>(x,y)] = 0;
                paint(map_scale*dimension_block*x,map_scale*dimension_block*y,0,choose_block[x][y]);
            }
            else if(blocks[x][y] == 2){
                choose_block[x][y] = new sprites();
                choose_block[x][y]->set_block(2);
                coordinates[pair<unsigned int,unsigned int>(x,y)] = 2;
                paint(map_scale*dimension_block*x,map_scale*dimension_block*y,0,choose_block[x][y]);

            }
            else if(blocks[x][y] == 1){
                choose_block[x][y] = new sprites();
                choose_block[x][y]->set_block(1);
                coordinates[pair<unsigned int,unsigned int>(x,y)] = 1;
                paint(map_scale*dimension_block*x,map_scale*dimension_block*y,5,choose_block[x][y]);

            }
        }
    }
}

bool MainWindow::aleatory(float probability)
{
    return (rand()/float(RAND_MAX)) < probability;
}

void MainWindow::paint(unsigned int pos_x_to_paint, unsigned int pos_y_to_paint, unsigned int value_z, QGraphicsPixmapItem *painter)
{
    painter->setPos(pos_x_to_paint,pos_y_to_paint);
    painter->setZValue(value_z);
    game->addItem(painter);
    ui->graphicsView->setScene(game);
}

void MainWindow::set_bomberman_position()
{
    unsigned int cont = 0;
    bomber = new QPixmap[19];
    //obtener animaciones de movimiento
    for(unsigned int y = 0; y < 2; y++){
        for(unsigned int x = 0; x < 6; x++){
            bomber[cont] = sprite_aux.set_sprite_for_animation(x,y);
            cont++;
        }
    }
    //obtener animaciones de muerte
    unsigned int y = 2;
    for (unsigned int x = 0; x < 7; x++){
        bomber[cont] = sprite_aux.set_sprite_for_animation(x,y);
        cont++;
    }

    bomberman_image = new QGraphicsPixmapItem(bomber[4]);

    paint(map_scale*dimension_block,map_scale*dimension_block,5,bomberman_image);
    enemies_cont = amount_enemies;
}

void MainWindow::put_bomb_on_escene()
{
    valid_put_bomb = true;

    bomba_image = new QGraphicsPixmapItem();

    bomba_image = bomba.set_bomb();

    unsigned int pos_x, pos_y;

    pos_x = valid_x_bomb_position(bomberman_image->x());
    pos_y = valid_y_bomb_position(bomberman_image->y());

    coordinates[pair<unsigned int,unsigned int>(pos_x /(dimension_block*map_scale),pos_y/(dimension_block*map_scale))] = 1;

    paint(pos_x,pos_y,3,bomba_image);

    valid_put_bomb = false;

    aux_cont = 0;

    put_bomb();

}

void MainWindow::put_burst_on_escene(unsigned int pos_x, unsigned int pos_y)
{
    burst_image_ = new QGraphicsPixmapItem();

    burst_image_ = bomba.set_burst();

    paint(pos_x - (dimension_block*map_scale), pos_y-(dimension_block*map_scale),4,burst_image_);

    aux_cont_ = 0;
    counter_1 = -1;

    pos_x_burst_to_evaluate = burst_image_->x() + (dimension_block*map_scale);
    pos_y_burst_to_evaluate = burst_image_->y() + (dimension_block*map_scale);
    pos_x_burst_to_evaluate_enemy = pos_x_burst_to_evaluate;
    pos_y_burst_to_evaluate_enemy = pos_y_burst_to_evaluate;
    valid_evaluate_dead = true;

    put_burst();
}

void MainWindow::put_destruction_on_escene(unsigned int pos_x, unsigned int pos_y,int direction_block)
{
    if (direction_block == 1){
        destruction_block_image_up = new QGraphicsPixmapItem();

        destruction_block_image_up = bomba.set_destruction_block();

        paint(pos_x, pos_y,1,destruction_block_image_up);
    }
    else if (direction_block == 2){
        destruction_block_image_down = new QGraphicsPixmapItem();

        destruction_block_image_down = bomba.set_destruction_block();

        paint(pos_x, pos_y,1,destruction_block_image_down);
    }
    else if (direction_block == 3){
        destruction_block_image_right = new QGraphicsPixmapItem();

        destruction_block_image_right = bomba.set_destruction_block();

        paint(pos_x, pos_y,1,destruction_block_image_right);
    }
    else{
        destruction_block_image_left = new QGraphicsPixmapItem();

        destruction_block_image_left = bomba.set_destruction_block();

        paint(pos_x, pos_y,1,destruction_block_image_left);

    }
}

void MainWindow::put_enemies_on_escene()
{
    unsigned int pos_x_enemy, pos_y_enemy;

    array_enemies = new enemies[amount_enemies];

    //creacion de amount_enemies enemigos
    for (unsigned int i = 0; i < amount_enemies; i++){
        enemies *enemy_n = new enemies;
        array_enemies[i] = *enemy_n;
        enemies_image.push_back(enemy.set_enemy());

        while(true){
            pos_x_enemy = rand() % (size_x - 1);
            pos_y_enemy = rand() % (size_y - 1);
            if (coordinates[pair<unsigned int,unsigned int>(pos_x_enemy,pos_y_enemy)] == 0 && !((pos_y_enemy == 1 && pos_x_enemy == 1) || (pos_y_enemy == 1 && pos_x_enemy == 2) || (pos_y_enemy == 2 && pos_x_enemy == 1))) break;
        }
        paint(pos_x_enemy*dimension_block*map_scale,pos_y_enemy*dimension_block*map_scale,2,enemies_image[i]);
    }
    put_move_enemies();
}

void MainWindow::put_move_enemies()
{
    if (valid_timer_move){
        if (timer_put_move->isActive()) timer_put_move->stop();
    }
    else{
        timer_put_move = new QTimer();
        connect(timer_put_move, SIGNAL(timeout()), this, SLOT(move_enemies()));
        valid_timer_move = true;
    }
    timer_put_move->start(50);
}


void MainWindow::put_bomb()
{

    if (valid_timer_bomb){
        if (timer_put->isActive()) timer_put->stop();
    }
    else{
        timer_put = new QTimer();
        connect(timer_put, SIGNAL(timeout()), this, SLOT(burst()));
        valid_timer_bomb = true;
    }
    timer_put->start(300);


}

void MainWindow::put_burst()
{
    if (valid_timer_burst){
        if (timer_put_burst->isActive()) timer_put_burst->stop();
    }
    else{
        timer_put_burst = new QTimer();
        connect(timer_put_burst, SIGNAL(timeout()), this, SLOT(burst_flame()));
        valid_timer_burst = true;
    }
    timer_put_burst->start(50);
}

void MainWindow::put_destruction()
{
    if (valid_timer_destruction){
        if (timer_put_destruction->isActive()) timer_put_destruction->stop();
    }
    else{
        timer_put_destruction = new QTimer();
        connect(timer_put_destruction, SIGNAL(timeout()), this, SLOT(destruction_block()));
        valid_timer_destruction = true;
    }
    timer_put_destruction->start(50);
}

void MainWindow::put_dead()
{
    if (valid_timer_dead){
        if (timer_put_dead->isActive()) timer_put_dead->stop();
    }
    else{
        timer_put_dead = new QTimer();
        connect(timer_put_dead, SIGNAL(timeout()), this, SLOT(dead_bomberman()));
        valid_timer_dead = true;
    }
    timer_put_dead->start(100);
}


void MainWindow::put_dead_enemy()
{
    if (valid_timer_dead_enemy){
        if (timer_put_dead_enemy->isActive()) timer_put_dead_enemy->stop();
    }
    else{
        timer_put_dead_enemy = new QTimer();
        connect(timer_put_dead_enemy, SIGNAL(timeout()), this, SLOT(dead_enemy()));
        valid_timer_dead_enemy = true;
    }
    timer_put_dead_enemy->start(150);
}

void MainWindow::burst()
{
    unsigned int x_pos_bomb, y_pos_bomb;

    aux_cont++;
    bomba.bomb_animation(bomba_image);
    if (aux_cont == 7){
        x_pos_bomb = bomba_image->x();
        y_pos_bomb = bomba_image->y();
        game->removeItem(bomba_image);
        delete bomba_image;
        timer_put->stop();
        valid_timer_bomb = false;
        put_burst_on_escene(x_pos_bomb,y_pos_bomb);
    }
}



void MainWindow::burst_flame()
{

    aux_cont_++;

    bomba.burst_animation(burst_image_);

    if (valid_evaluate_dead){
        if (bomberman.ask_bomberman_down(pos_y_burst_to_evaluate,bomberman_image->y(),pos_x_burst_to_evaluate,bomberman_image->x()) || bomberman.ask_bomberman_left(pos_x_burst_to_evaluate,bomberman_image->x(),pos_y_burst_to_evaluate,bomberman_image->y()) || bomberman.ask_bomberman_right(pos_x_burst_to_evaluate,bomberman_image->x(),pos_y_burst_to_evaluate,bomberman_image->y()) || bomberman.ask_bomberman_up(pos_y_burst_to_evaluate,bomberman_image->y(),pos_x_burst_to_evaluate,bomberman_image->x()) || bomberman.ask_bomberman_on_fire(pos_x_burst_to_evaluate,bomberman_image->x(), bomberman_image->y(),pos_y_burst_to_evaluate)){
            put_dead();
        }
        else if (bomberman_image->x() == pos_door_x && bomberman_image->y() == pos_door_y) exit(EXIT_SUCCESS);

        else valid_evaluate_dead = false;
        pos_x_burst_to_evaluate_enemy = -1;
        pos_y_burst_to_evaluate_enemy = -1;
    }

    if (aux_cont_ == 8){
        coordinates[pair<unsigned int,unsigned int>((burst_image_->x() + (dimension_block*map_scale))/(dimension_block*map_scale),(burst_image_->y() + (dimension_block*map_scale))/(dimension_block*map_scale))] = 0;
        pos_x_burst = burst_image_->x() + (dimension_block*map_scale);
        pos_y_burst = burst_image_->y() + (dimension_block*map_scale);
        game->removeItem(burst_image_);
        delete burst_image_;
        timer_put_burst->stop();
        valid_timer_burst = false;
        counter_1 = -1;
        counter_2 = -1;
        counter_3 = -1;
        counter_4 = -1;
        valid_evaluate_dead = false;
        put_destruction();
    }
}


void MainWindow::destruction_block()
{
    if(bomba.ask_up(coordinates, pos_x_burst, pos_y_burst) && counter_1 <= 8){
        counter_1++;
        if (counter_1 == 0) put_destruction_on_escene(pos_x_burst,pos_y_burst - (dimension_block*map_scale),1);

        if (counter_1 == 8){
            if (aleatory(probability_finish_game) && amount_door == 0){
                QPixmap door;
                door = sprite_aux.set_sprite_for_animation(11,3);
                QGraphicsPixmapItem *door_ = new QGraphicsPixmapItem(door);
                paint(pos_x_burst,pos_y_burst - (dimension_block*map_scale),4,door_);
                pos_door_x = pos_x_burst;
                pos_door_y = pos_y_burst - (dimension_block*map_scale);
                amount_door++;
            }
            game->removeItem(choose_block[pos_x_burst/(dimension_block*map_scale)][(pos_y_burst - (dimension_block*map_scale))/(dimension_block*map_scale)]);
            delete choose_block[pos_x_burst/(dimension_block*map_scale)][(pos_y_burst - (dimension_block*map_scale))/(dimension_block*map_scale)];
            coordinates[pair<unsigned int,unsigned int>(pos_x_burst/(dimension_block*map_scale),(pos_y_burst - (dimension_block*map_scale))/(dimension_block*map_scale))] = 0;
        }
        else bomba.destruction_animation(destruction_block_image_up,counter_1);
    }
    if(bomba.ask_down(coordinates, pos_x_burst, pos_y_burst) && counter_2 <= 8){
        counter_2++;
        if (counter_2 == 0) put_destruction_on_escene(pos_x_burst,pos_y_burst + (dimension_block*map_scale),2);
        if (counter_2 == 8){
            if (aleatory(probability_finish_game) && amount_door == 0){
                QPixmap door;
                door = sprite_aux.set_sprite_for_animation(11,3);
                QGraphicsPixmapItem *door_ = new QGraphicsPixmapItem(door);
                paint(pos_x_burst,pos_y_burst + (dimension_block*map_scale),4,door_);
                pos_door_x = pos_x_burst;
                pos_door_y = pos_y_burst + (dimension_block*map_scale);
                amount_door++;
            }
            game->removeItem(choose_block[pos_x_burst/(dimension_block*map_scale)][(pos_y_burst + (dimension_block*map_scale))/(dimension_block*map_scale)]);
            delete choose_block[pos_x_burst/(dimension_block*map_scale)][(pos_y_burst + (dimension_block*map_scale))/(dimension_block*map_scale)];
            coordinates[pair<unsigned int,unsigned int>(pos_x_burst/(dimension_block*map_scale),(pos_y_burst + (dimension_block*map_scale))/(dimension_block*map_scale))] = 0;
        }
        else bomba.destruction_animation(destruction_block_image_down,counter_2);
    }
    if(bomba.ask_rigth(coordinates, pos_x_burst, pos_y_burst) && counter_3 <= 8){
        counter_3++;
        if (counter_3 == 0) put_destruction_on_escene(pos_x_burst + (dimension_block*map_scale),pos_y_burst,3);
        if (counter_3 == 8){
            if (aleatory(probability_finish_game) && amount_door == 0){
                QPixmap door;
                door = sprite_aux.set_sprite_for_animation(11,3);
                QGraphicsPixmapItem *door_ = new QGraphicsPixmapItem(door);
                paint(pos_x_burst + (dimension_block*map_scale),pos_y_burst,4,door_);
                pos_door_x = pos_x_burst + (dimension_block*map_scale);
                pos_door_y = pos_y_burst;
                amount_door++;
            }
            game->removeItem(choose_block[(pos_x_burst + (dimension_block*map_scale))/(dimension_block*map_scale)][pos_y_burst/(dimension_block*map_scale)]);
            delete choose_block[(pos_x_burst + (dimension_block*map_scale))/(dimension_block*map_scale)][pos_y_burst/(dimension_block*map_scale)];
            coordinates[pair<unsigned int,unsigned int>((pos_x_burst + (dimension_block*map_scale))/(dimension_block*map_scale),pos_y_burst/(dimension_block*map_scale))] = 0;
        }
        else bomba.destruction_animation(destruction_block_image_right,counter_3);
    }
    if(bomba.ask_left(coordinates, pos_x_burst, pos_y_burst) && counter_4 <= 8){
        counter_4++;
        if (counter_4 == 0) put_destruction_on_escene(pos_x_burst - (dimension_block*map_scale),pos_y_burst,4);
        if (counter_4 == 8){
            if (aleatory(probability_finish_game) && amount_door == 0){
                QPixmap door;
                door = sprite_aux.set_sprite_for_animation(11,3);
                QGraphicsPixmapItem *door_ = new QGraphicsPixmapItem(door);
                paint(pos_x_burst - (dimension_block*map_scale),pos_y_burst,4,door_);
                pos_door_x = pos_x_burst - (dimension_block*map_scale);
                pos_door_y = pos_y_burst;
                amount_door++;
            }
            game->removeItem(choose_block[(pos_x_burst - (dimension_block*map_scale))/(dimension_block*map_scale)][pos_y_burst/(dimension_block*map_scale)]);
            delete choose_block[(pos_x_burst - (dimension_block*map_scale))/(dimension_block*map_scale)][pos_y_burst/(dimension_block*map_scale)];
            coordinates[pair<unsigned int,unsigned int>((pos_x_burst - (dimension_block*map_scale))/(dimension_block*map_scale),pos_y_burst/(dimension_block*map_scale))] = 0;
        }
        else bomba.destruction_animation(destruction_block_image_left,counter_4);
    }
    if(counter_2 == 8 || counter_1 == 8 ||counter_3 == 8 || counter_4 == 8){
        valid_timer_destruction = false;
        timer_put_destruction->stop();
        valid_put_bomb = true;
    }
    else{
        valid_put_bomb = true;

    }


}

void MainWindow::move_enemies()
{
    //si da true el enemigo se mueve aleatorio
    for (unsigned int i = 0; i < amount_enemies; i++){
        //preguntar si la posicion del bomberman concuerda con la posicion del enemigo[i]
        for (unsigned int i = 0; i < amount_enemies; i++){
            if (array_enemies[i].kill_bomberman(bomberman_image->x(),bomberman_image->y(),enemies_image[i]->x(),enemies_image[i]->y())) put_dead();
        }
        //preguntar si alguno de los enemigos toca el fuego para morir
        if (bomberman.ask_bomberman_down(pos_y_burst_to_evaluate_enemy,enemies_image[i]->y(),pos_x_burst_to_evaluate_enemy,enemies_image[i]->x()) || bomberman.ask_bomberman_left(pos_x_burst_to_evaluate_enemy,enemies_image[i]->x(),pos_y_burst_to_evaluate_enemy,enemies_image[i]->y()) || bomberman.ask_bomberman_right(pos_x_burst_to_evaluate_enemy,enemies_image[i]->x(),pos_y_burst_to_evaluate_enemy,enemies_image[i]->y()) || bomberman.ask_bomberman_up(pos_y_burst_to_evaluate_enemy,enemies_image[i]->y(),pos_x_burst_to_evaluate_enemy,enemies_image[i]->x()) || bomberman.ask_bomberman_on_fire(pos_x_burst_to_evaluate_enemy,enemies_image[i]->x(), enemies_image[i]->y(),pos_y_burst_to_evaluate_enemy)){
            k = i;
            array_enemies[i].set_verify_move(false);
            put_dead_enemy();
        }
        //definir aleatoriamente si se mueve en y o en x
        if (confirm_aleatory){
            if (aleatory(movement_enemie)) array_enemies[i].set_move_in_y(true);
            else array_enemies[i].set_move_in_y(false);
        }
        if (array_enemies[i].get_move_in_y() && array_enemies[i].get_verify_move()){
            if (array_enemies[i].get_confirm_change_direction_y_down()) {
                array_enemies[i].down_movement(enemies_image[i],coordinates);
                if (array_enemies[i].get_confirm_change_direction_y_up())array_enemies[i].set_confirm_change_direction_y_down(false);
            }
            else if (array_enemies[i].get_confirm_change_direction_y_up()) {
                array_enemies[i].up_movement(enemies_image[i],coordinates);
                if (array_enemies[i].get_confirm_change_direction_y_down()) array_enemies[i].set_confirm_change_direction_y_up(false);
            }
            else array_enemies[i].up_movement(enemies_image[i],coordinates);
        }
        else if(array_enemies[i].get_verify_move()){

            if (array_enemies[i].get_confirm_bool_change_direction_x_right()) {
                array_enemies[i].right_movement(enemies_image[i],coordinates);
                if (array_enemies[i].get_confirm_bool_change_direction_x_left())array_enemies[i].set_confirm_change_direction_x_right(false);
            }
            else if (array_enemies[i].get_confirm_bool_change_direction_x_left()) {
                array_enemies[i].left_movement(enemies_image[i],coordinates);
                if (array_enemies[i].get_confirm_bool_change_direction_x_right()) array_enemies[i].set_confirm_change_direction_x_left(false);
            }
            else array_enemies[i].left_movement(enemies_image[i],coordinates);
        }
    }
    confirm_aleatory = false;
}


void MainWindow::dead_bomberman()
{
    counter_5++;
    valid_key = false;
    if (counter_5 == 19){
        valid_timer_dead = false;
        timer_put_dead->stop();
        exit(EXIT_SUCCESS);
    }
    else{
        bomberman.dead_animation(bomber,bomberman_image,counter_5);
    }

}


void MainWindow::dead_enemy()
{
    counter_6++;
    if (counter_6 == 11){
        QPixmap aux = sprite_aux.set_block(0);
        QGraphicsPixmapItem *aux_ = new QGraphicsPixmapItem(aux);
        paint(enemies_image[k]->x(), enemies_image[k]->y(),1,aux_);
        valid_timer_dead_enemy = false;
        timer_put_dead_enemy->stop();
        enemies_image[k]->setPos(0,0);
        counter_6 = 5;
        enemies_cont--;
        if (enemies_cont == 0) probability_finish_game = 0.8;

    }
    else{
        array_enemies[k].dead_animation(enemies_image[k],counter_6);
    }

}

unsigned int MainWindow::valid_x_bomb_position(unsigned int bomberman_pos_x)
{
    unsigned int residuo_x,range_half;

    residuo_x = bomberman_pos_x % (dimension_block*map_scale);
    if (residuo_x != 0) {
        range_half = (dimension_block*map_scale)/ 2;
        if (residuo_x > range_half) {
            return bomberman_pos_x - residuo_x + (dimension_block*map_scale);
        } else {
            return bomberman_pos_x - residuo_x;
        }
    }
    return bomberman_pos_x;
}

unsigned int MainWindow::valid_y_bomb_position(unsigned int bomberman_pos_y)
{
    unsigned int residuo_y,range_half;

    residuo_y = bomberman_pos_y % (dimension_block*map_scale);
    if (residuo_y != 0) {
        range_half = (dimension_block*map_scale)/ 2;
        if (residuo_y > range_half) {
            return bomberman_pos_y - residuo_y + (dimension_block*map_scale);
        } else {
            return bomberman_pos_y - residuo_y;
        }
    }
    return bomberman_pos_y;
}

void MainWindow::keyPressEvent(QKeyEvent *key)
{

    if (key->key() == Qt::Key_W && valid_key) {
        bomberman.up_movement(bomber,bomberman_image,coordinates);
        if (bomberman_image->x() == pos_door_x && bomberman_image->y() == pos_door_y) exit(EXIT_SUCCESS);
    }
    else if (key->key() == Qt::Key_A && valid_key) {
        bomberman.left_movement(bomber,bomberman_image, coordinates);
        if (bomberman_image->x() == pos_door_x && bomberman_image->y() == pos_door_y) exit(EXIT_SUCCESS);
    }
    else if (key->key() == Qt::Key_S && valid_key) {
        bomberman.down_movement(bomber,bomberman_image, coordinates);
        if (bomberman_image->x() == pos_door_x && bomberman_image->y() == pos_door_y) exit(EXIT_SUCCESS);
    }
    else if (key->key() == Qt::Key_D && valid_key) {
        bomberman.rigth_movement(bomber,bomberman_image,coordinates);
        if (bomberman_image->x() == pos_door_x && bomberman_image->y() == pos_door_y) exit(EXIT_SUCCESS);
    }
    if (key->key() == Qt::Key_Space && valid_put_bomb) put_bomb_on_escene();


}


void MainWindow::handle_dead_enemy()
{
    // Dejar vacío por ahora
}




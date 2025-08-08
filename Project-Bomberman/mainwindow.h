#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QKeyEvent>
#include <vector>
#include "bomb.h"
#include "enemies.h"

#define size_x 1550/(dimension_block*map_scale)
#define size_y 810/(dimension_block*map_scale)

using namespace std;

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

private:
    Ui::MainWindow *ui;
    QGraphicsScene *game;
    //puntero que me contendra los bloques a agregar y contadores para las animaciones
    int aux_cont = 7,aux_cont_,counter_1 = -1, counter_2 = -1,counter_3 = -1, counter_4 = -1, counter_5 = 12, counter_6 = 5;
    unsigned int **blocks, pos_x_burst, pos_y_burst, pos_x_burst_to_evaluate = -1, pos_y_burst_to_evaluate = -1, k = 0, pos_x_burst_to_evaluate_enemy = -1 , pos_y_burst_to_evaluate_enemy = -1, pos_door_x = -1, pos_door_y = -1, amount_door = 0, enemies_cont = 0;
    //puntero el cual almacenara el bloque a poner
    sprites *choose_block[size_x][size_y], sprite_aux;
    //punteros para poner las imagenes en el tablero
    QGraphicsPixmapItem *bomberman_image, *burst_image_, *bomba_image, *destruction_block_image_up, *destruction_block_image_down, *destruction_block_image_left, *destruction_block_image_right;
    //obtener las imagenes del bomberman
    QPixmap *bomber;
    //objeto bomberman, bomba y enemigo
    bomberman_character bomberman;
    bomb bomba;
    enemies enemy_n;
    enemies enemy;
    //dificultad en cuanto a cantidad de ladrillos, cantidad de enemigos
    float difficult = 0.2, movement_enemie = 0.5, probability_finish_game = 0.1;
    //mapa con las coordenadas de mi mapa y que tipo de bloque hay en ella
    map<pair<unsigned int, unsigned int>,unsigned int> coordinates;
    //qtiemers para eventos periodicos
    QTimer *timer_put, *timer_put_burst,*timer_put_destruction, *timer_put_dead, *timer_put_enemies, *timer_put_move, *timer_put_dead_enemy;

    //validaciones para los qtiemers
    bool valid_timer_bomb = false, valid_timer_burst = false, valid_timer_dead_enemy = false, valid_put_bomb = true,  valid_timer_destruction = false, valid_timer_dead = false, valid_evaluate_dead = false, valid_key = true, valid_timer_move = false, valid_set = true, confirm_change_direction = false, confirm_aleatory = true;
    vector<QGraphicsPixmapItem*> enemies_image;
    enemies *array_enemies;


public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    //setear el mapa
    void set_map();
    bool aleatory(float difficult);
    //pintar en el tablero las imagenes
    void show_map();
    void set_bomberman_position();
    void put_bomb_on_escene();
    void put_burst_on_escene(unsigned int pos_x, unsigned int pos_y);
    void put_destruction_on_escene(unsigned int pos_x, unsigned int pos_y, int direction_block);
    //validacion de las coordenadas de la bomba
    unsigned int valid_x_bomb_position(unsigned int bomberman_pos_x);
    unsigned int valid_y_bomb_position(unsigned int bomberman_pos_y);
    //timers
    void put_bomb();
    void put_burst();
    void put_destruction();
    void put_dead();
    //pintar en el tablero
    void paint(unsigned int pos_x_to_paint,unsigned int pos_y_to_paint, unsigned int z_value, QGraphicsPixmapItem *painter);
    //evento de teclas
    void keyPressEvent(QKeyEvent *key);
    //definicion de si se muere o no el bomberman

public slots:
    //eventos periodicos
    void burst();
    void burst_flame();
    void destruction_block();
    void dead_bomberman();
    void put_enemies_on_escene();
    void put_move_enemies();
    void move_enemies();
    void put_dead_enemy();
    void dead_enemy();
    void handle_dead_enemy();


};
#endif // MAINWINDOW_H

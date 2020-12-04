#ifndef P3_INTERSTELLAR_FIGURE_H
#define P3_INTERSTELLAR_FIGURE_H

#include <ctime>
#include <GL/glut.h>
#include <cmath>
#include <iostream>
#include <fstream>
#include <conio.h>
#include "vec.h"

typedef struct routine_node{
    vec coordinate;
    routine_node *next;
}routine_node;

typedef class Figure {
public:
    explicit Figure(vec insert_center);
    virtual ~Figure()= default;
    virtual void draw()=0;
    vec get_center();
    void set_center(vec insert_center);
    virtual void action()=0;
protected:
    vec center;
    const GLfloat pi=3.1415926536f;
}Figure;

typedef class color_figure: public Figure {
public:
    explicit color_figure(vec insert_center,double color1,double color2,double color3);
    virtual void zoom(double scale)=0;
    virtual void move(vec last_one,vec mid_one,vec next_one,vec new_center)=0;
    virtual void rotate(double angle)=0;
    void action() override;
protected:
    GLfloat color_1;
    GLfloat color_2;
    GLfloat color_3;
}color_figure;

typedef class group:public Figure{
public:
    explicit group(vec insert_center,int insert_index);
    ~group() override;
    void set_if_start();
    bool get_if_start();
    void set_if_end();
    bool get_if_end();
    void find_path();
    void run_routine_node();
    virtual void move()=0;
    void track();
    int get_index();
    virtual void set_figures_center(vec insert_center)=0;
protected:
    bool if_start;
    bool if_end;
    routine_node *node_now;
    routine_node *node_last;
    int index;
    routine_node* head;
    vec** links;
    routine_node *delete_node;
}group;

typedef class trapezoid: public color_figure{
public:
    trapezoid(vec insert_small_one,vec insert_big_one,vec insert_center,double color1,double color2,double color3);
    ~trapezoid() override= default;
    void draw() override;
    void zoom(double scale) override;
    void move(vec last_one,vec mid_one,vec next_one,vec new_center) override;
    void rotate(double angle) override;
private:
    vec small_one;
    vec big_one;
}trapezoid;

typedef class semicircle: public color_figure{
public:
    semicircle(vec insert_clock_order_one,vec insert_center,double color1,double color2,double color3);
    ~semicircle() override= default;
    void draw() override;
    void zoom(double scale) override;
    void move(vec last_one,vec mid_one,vec next_one,vec new_center) override;
    void rotate(double angle) override;
private:
    vec clock_order_one;
    const GLfloat pi=3.1415926536f;
}semicircle;

typedef class parallelogram: public color_figure{
public:
    parallelogram(vec insert_first_one,vec insert_second_one,vec insert_center,double color1,double color2,double color3);
    ~parallelogram() override= default;
    void draw() override;
    void zoom(double scale) override;
    void move(vec last_one,vec mid_one,vec next_one,vec new_center) override;
    void rotate(double angle) override;
private:
    vec first_one;
    vec second_one;
}parallelogram;

typedef class triangle: public color_figure{
public:
    triangle(vec insert_first_one,vec insert_second_one,vec insert_center,double color1,double color2,double color3);
    ~triangle() override = default;
    void draw() override;
    void zoom(double scale) override;
    void move(vec last_one,vec mid_one,vec next_one,vec new_center) override;
    void rotate(double angle) override;
private:
    vec first_one;
    vec second_one;
}triangle;

typedef class Rocket:public group{
public:
    explicit Rocket(vec insert_center,int insert_index);
    ~Rocket() override;
    void draw() override;
    void action() override;
    void move() override;
    void set_figures_center(vec insert_center) override;
private:
    color_figure *figure[5];
}Rocket;

typedef class Radar:public group{
public:
    explicit Radar(vec insert_center,int insert_index);
    ~Radar() override;
    void draw() override;
    void action() override;
    void move() override;
    void set_figures_center(vec insert_center) override;
private:
    color_figure *figure[5];
}Radar;

typedef class Car:public group{
public:
    explicit Car(vec insert_center,int insert_index);
    ~Car() override;
    void draw() override;
    void move() override;
    void action() override;
    void set_figures_center(vec insert_center) override;
    void set_free_move(int key);
private:
    color_figure *figure[6];
}Car;

typedef class parking_lot {
public:
    parking_lot();
    ~parking_lot();
    static void draw();
    static void draw_basic_lines();
    static void total_draw();
    static void draw_roadblock();
    static void draw_barrier();
    static void draw_gateway();
    static void move_free_car(int key, int x, int y);
private:
    static int number_of_barrier;
    static int number_of_figure;
    static group **vehicle;
    static Figure **barrier;
    static bool open_the_door;
    static int counter_door;
    static color_figure **gateway;
    static int index_of_gateway;
    static int index_of_get_in_gateway;
    static Car* free_move_car;
}parking_lot;

void TimeStep(int n);

#endif
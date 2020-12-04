#include "Figure.h"
#include <iostream>
void TimeStep(int n) {
    glutTimerFunc(25, TimeStep,2000);
    glutPostRedisplay();
};

void exit_function(unsigned char key, int x, int y)
{
    if (key == 27)
        exit(0);
};
void parking_lot::move_free_car(int key, int x, int y) {
    vec vec1(0.05,0),vec2(0,0.05),center=free_move_car->get_center();
    switch (key) {
        case GLUT_KEY_UP:
            free_move_car->set_free_move(GLUT_KEY_UP);
            break;
        case GLUT_KEY_LEFT:
            free_move_car->set_free_move(GLUT_KEY_LEFT);
            break;
        case GLUT_KEY_RIGHT:
            free_move_car->set_free_move(GLUT_KEY_RIGHT);
            break;
        case GLUT_KEY_DOWN:
            free_move_car->set_free_move(GLUT_KEY_DOWN);
            break;
        default:
            std::cout<<"wrong"<<std::endl;
            break;
    };
}


vec find_center(int index){
    if (index>8){
        vec return_one(-0.63462+0.1923077*(16-index),0.600);
        return return_one;
    }else{
        vec return_one(-0.63462+0.1923077*(index-1),-0.5224);
        return return_one;
    };
}

parking_lot::parking_lot() {
    srand((unsigned)time(nullptr));
    number_of_barrier=rand()%3+4;
    number_of_figure=rand()%2+3;
    barrier=new Figure*[number_of_barrier];
    vehicle=new group*[number_of_figure];
    int array_barrier[number_of_barrier],array_vehicle[number_of_figure],array_left[16-number_of_barrier-number_of_figure],temp,array_total[16],array_left_barrier[16-number_of_barrier];
    for(int i=0;i<16;i++){
        array_total[i]=i+1;
    }
    for (int i=0;i<number_of_barrier;i++){
        temp=rand()%16+1;
        while(array_total[temp-1]==0){
            temp=rand()%16+1;
        };
        array_barrier[i]=temp;
        array_total[temp-1]=0;

    };
    int left_barrier_counter=0;
    for (int i : array_total) {
        if(i !=0){
            array_left_barrier[left_barrier_counter]= i;
            left_barrier_counter++;
        };
    };
    for (int i=0;i<number_of_figure;i++){
        temp=rand()%16+1;
        while(array_total[temp-1]==0){
            temp=rand()%16+1;
        };
        array_vehicle[i]=temp;
        array_total[temp-1]=0;
        std::cout<<array_vehicle[i]<<std::endl;
    };
    int left_counter=0;
    for (int i : array_total) {
        if(i !=0){
            array_left[left_counter]= i;
            left_counter++;
        }
    };
    vec start_point(-0.855387,-0.6667);
    for (int i=0;i<number_of_figure;i++){
         temp=rand()%3+1;
         switch (temp) {
             case 1:
                 vehicle[i] = new Car(start_point,array_vehicle[i]);
                 break;
             case 2:
                 vehicle[i] = new Rocket(start_point,array_vehicle[i]);
                 break;
             case 3:
                 vehicle[i] = new Radar(start_point,array_vehicle[i]);
                 break;
             default:
                 std::cout << "wrong!!" << std::endl;
         };
    };
    vehicle[0]->set_if_start();
    vec first_one(0.07,0.10),second_one(-0.07,0.10);
    for (int i=0;i<number_of_barrier;i++){
        temp=rand()%4+1;
        switch (temp) {
            case 1:
                barrier[i] = new Car(find_center(array_barrier[i]),array_barrier[i]);
                break;
            case 2:
                barrier[i] = new Rocket(find_center(array_barrier[i]),array_barrier[i]);
                break;
            case 3:
                barrier[i] = new Radar(find_center(array_barrier[i]),array_barrier[i]);
                break;
            default:
                barrier[i]= new parallelogram(first_one,second_one,find_center(array_barrier[i]),0.0, 1.0, 1.0);
                break;
        };
    };
    vec vec1(-0.033334,0.05774),vec2(-0.066667f,0),vec3(0.033334,0.05774),vec4(0.066667f,0),vec5(-0.033334,-0.05774),vec6(0.033334,-0.05774);
    index_of_gateway=rand()%(16-number_of_barrier);
    gateway=new color_figure*[4];
    gateway[0]=new parallelogram(first_one,second_one,find_center(array_left_barrier[index_of_gateway]),0,0,0);
    gateway[1]=new triangle(vec1,vec2,find_center(array_left_barrier[index_of_gateway]),1.0, 1.0, 0.0);
    gateway[2]=new triangle(vec3,vec4,find_center(array_left_barrier[index_of_gateway]),1.0, 1.0, 0.0);
    gateway[3]=new triangle(vec5,vec6,find_center(array_left_barrier[index_of_gateway]),1.0, 1.0, 0.0);
    index_of_gateway=array_left_barrier[index_of_gateway];
    index_of_get_in_gateway=array_left[rand()%(16-number_of_barrier-number_of_figure)];
    free_move_car=new Car(find_center(17),17);
};

int parking_lot::number_of_barrier=0;

int parking_lot::number_of_figure=0;

group** parking_lot::vehicle=nullptr;

Figure** parking_lot::barrier=nullptr;

color_figure** parking_lot::gateway= nullptr;

bool parking_lot::open_the_door=false;

int parking_lot::counter_door=0;

int parking_lot::index_of_gateway=1;

int parking_lot::index_of_get_in_gateway=2;

Car* parking_lot::free_move_car= nullptr;

parking_lot::~parking_lot() {
    delete[] *vehicle;
    delete(vehicle);
    delete[] *barrier;
    delete(barrier);
    delete[] gateway;
};

void parking_lot::draw_basic_lines() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glColor3f(0.5, 0.5, 0.5);
    glLineWidth(4);
    glBegin(GL_LINE_STRIP);
    glVertex2f(-0.73f, -0.6666f);
    glVertex2f(1.0f, -0.6666f);
    glVertex2f(1.0f, 0.75f);
    glVertex2f(-0.98f, 0.75f);
    glVertex2f(-0.98f, -0.6666f);
    glEnd();
    glColor3f(0.5,0.8,0.3);
    glBegin(GL_QUADS);
    glVertex2f(-0.73f, -0.03f);
    glVertex2f(0.808f, -0.03f);
    glVertex2f(0.808f, 0.1f);
    glVertex2f(-0.73f, 0.1f);
    glEnd();
    for (int i = 0; i <= 8; i++) {
        glColor3f(0.5, 0.5, 0.5);
        glLineWidth(4);
        glBegin(GL_LINES);
        glVertex2f(float(-0.73 + i * 0.1923), -0.6666f);
        glVertex2f(float(-0.73 + i * 0.1923), -0.3782f);
        glEnd();
        glBegin(GL_LINES);
        glVertex2f(float(-0.73 + i * 0.1923), 0.461538f);
        glVertex2f(float(-0.73 + i * 0.1923), 0.75f);
        glEnd();
    };
};

void parking_lot::draw_gateway(){
    for (int i=1;i<4;i++){
        gateway[i]->rotate(3.1415926536f/180);
    }
    for (int i=0;i<4;i++){
        gateway[i]->draw();
    };
}

void parking_lot::draw_roadblock() {
    if(!open_the_door){
        static vec length(-0.25,0.0);
        vec start_vec(-0.25,0.0);
        static double angle=0.0;
        vec lift_points(-0.73,-0.5166f);
        lift_points.vector_plus(length);
        vec right_points(-0.73,-0.5166f);
        glColor3f(0.2, 0.5, 0.1);
        glBegin(GL_LINES);
        glVertex2f(static_cast<GLfloat>(lift_points.get_x()), static_cast<GLfloat>(lift_points.get_y()));
        glVertex2f(static_cast<GLfloat>(right_points.get_x()), static_cast<GLfloat>(right_points.get_y()));
        glEnd();
        length.vector_right_angle(3.1415926536f/180);
        angle+=3.1415926536f/180;
        if(angle>=3.1415926536f/2){
            length=start_vec;
            open_the_door=true;
            angle=0;
        };
    }else{
        static double angle=0.0;
        static vec length(0.0, 0.25);
        vec temp(0.0,0.25);
        if(counter_door==0){
            angle=0;
            length=temp;
        }
        if(counter_door>200){
            if(angle<=3.1415926536f/2) {
                vec lift_points(-0.73, -0.5166f);
                lift_points.vector_plus(length);
                vec right_points(-0.73, -0.5166f);
                glColor3f(0.2, 0.5, 0.1);
                glBegin(GL_LINES);
                glVertex2f(static_cast<GLfloat>(lift_points.get_x()), static_cast<GLfloat>(lift_points.get_y()));
                glVertex2f(static_cast<GLfloat>(right_points.get_x()), static_cast<GLfloat>(right_points.get_y()));
                glEnd();
                length.vector_light_angle(3.1415926536f / 180);
                angle += 3.1415926536f / 180;
            }else{
                vec start_vec(-0.25,0.0);
                vec lift_points(-0.73,-0.5166f);
                lift_points.vector_plus(start_vec);
                vec right_points(-0.73,-0.5166f);
                glColor3f(0.2, 0.5, 0.1);
                glBegin(GL_LINES);
                glVertex2f(static_cast<GLfloat>(lift_points.get_x()), static_cast<GLfloat>(lift_points.get_y()));
                glVertex2f(static_cast<GLfloat>(right_points.get_x()), static_cast<GLfloat>(right_points.get_y()));
                glEnd();
            };
        }else{
            vec start_vec(0.0,0.25);
            vec lift_points(-0.73,-0.5166f);
            lift_points.vector_plus(start_vec);
            vec right_points(-0.73,-0.5166f);
            glColor3f(0.2, 0.5, 0.1);
            glBegin(GL_LINES);
            glVertex2f(static_cast<GLfloat>(lift_points.get_x()), static_cast<GLfloat>(lift_points.get_y()));
            glVertex2f(static_cast<GLfloat>(right_points.get_x()), static_cast<GLfloat>(right_points.get_y()));
            glEnd();
        };
        counter_door++;
    }
};

void parking_lot::draw_barrier(){
    for (int i=0;i<number_of_barrier;i++){
        barrier[i]->draw();
    };
};

void parking_lot::total_draw() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    draw_basic_lines();
    draw_barrier();
    draw_gateway();
    for(int i=0;i<number_of_figure;i++){
        if (vehicle[i]->get_if_start() && !vehicle[i]->get_if_end()){
            draw_roadblock();
        }
        if(vehicle[i]->get_if_start()){
            if(!vehicle[i]->get_if_end()&& open_the_door){
                vehicle[i]->action();
            };
            vehicle[i]->draw();
            if (open_the_door){
                vehicle[i]->move();
            };
        };
        if( vehicle[i]->get_if_end()){
            if (i+2<=number_of_figure){
                if(!vehicle[i+1]->get_if_start()){
                    vehicle[i+1]->set_if_start();
                    open_the_door=false;
                    counter_door=0;
                };
            };
        };
        if(vehicle[i]->get_if_end()){
            if(vehicle[i]->get_index()==index_of_gateway){
                vehicle[i]->set_figures_center(find_center(index_of_get_in_gateway));
            };
        };
    };
    free_move_car->draw();
    glutSwapBuffers();
    glFlush();
};

void parking_lot::draw() {
    glutInitDisplayMode(GLUT_DEPTH|GLUT_RGB|GLUT_DOUBLE);
    glutInitWindowSize(1000,1000);
    glutCreateWindow("parking lot");
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT);
    glutDisplayFunc(total_draw);
    glutKeyboardFunc(exit_function);
    glutSpecialFunc(move_free_car);
    glutTimerFunc(25,TimeStep,25);
    glutMainLoop();
};




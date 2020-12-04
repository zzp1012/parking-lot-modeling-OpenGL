#include "Figure.h"
#include "vec.h"
Figure::Figure(vec insert_center) {
    center=insert_center;
}

vec Figure::get_center() {
    return center;
}

void Figure::set_center(vec insert_center) {
    center=insert_center;
};

color_figure::color_figure(vec insert_center, double color1, double color2, double color3):Figure(insert_center) {
    color_1=(GLfloat)color1;
    color_2=(GLfloat)color2;
    color_3=(GLfloat)color3;
}

void color_figure::action() {
};

group::group(vec insert_center,int insert_index):Figure(insert_center) {
    if_end= false;
    if_start=false;
    index=insert_index;
    find_path();
    node_last=head;
    node_now=head->next;
    delete_node=head;
}

void group::set_if_start() {
    if_start=true;
}

bool group::get_if_start() {
    return if_start;
}

void group::set_if_end() {
    if_end=true;
}

bool group::get_if_end() {
    return if_end;
};

void group::run_routine_node() {
    if(!get_if_end()){
        if(node_now->next->next==nullptr){
            set_if_end();
        }else{
            node_now=node_now->next;
            node_last=node_last->next;
        };
    };
}

void group::track() {
    glColor3f(0.0, 1.0, 0.7);
    glBegin(GL_LINES);
    routine_node* temp_now=node_now;
    routine_node* temp_last=node_last;
    while(temp_now->next!=nullptr){
        glVertex2f((GLfloat)temp_now->coordinate.get_x(),(GLfloat)temp_now->coordinate.get_y());
        glVertex2f((GLfloat)temp_last->coordinate.get_x(),(GLfloat)temp_last->coordinate.get_y());
        temp_last=temp_last->next;
        temp_now=temp_now->next;
    };
    glEnd();
}

int group::get_index() {
    return index;
}

group::~group() {
    routine_node *temp_head=delete_node;
    while (temp_head->next->next!=nullptr){
        routine_node *temp=temp_head->next;
        delete (temp_head);
        temp_head=temp_head->next;
    };
    delete(temp_head);
}

trapezoid::trapezoid(vec insert_small_one, vec insert_big_one, vec insert_center, double color1, double color2,
                     double color3) :color_figure(insert_center,color1,color2,color3){
    small_one=insert_small_one;
    big_one=insert_big_one;
}

void trapezoid::zoom(double scale) {
    small_one.vector_constant(scale);
    big_one.vector_constant(scale);
}

void trapezoid::draw() {
    glColor3f(color_1,color_2,color_3);
    glBegin(GL_QUADS);
    vec point1=center,point2=center,point3=center,point4=center;
    point1.vector_plus(small_one);
    point2.vector_plus(big_one);
    point3.vector_plus(small_one.reverse_vector(big_one.vector_absolute()/small_one.vector_absolute()));
    point4.vector_plus(big_one.reverse_vector(small_one.vector_absolute()/big_one.vector_absolute()));
    glVertex2f((GLfloat)point1.get_x(),(GLfloat)point1.get_y());
    glVertex2f((GLfloat)point2.get_x(),(GLfloat)point2.get_y());
    glVertex2f((GLfloat)point3.get_x(),(GLfloat)point3.get_y());
    glVertex2f((GLfloat)point4.get_x(),(GLfloat)point4.get_y());
    glEnd();
}

void trapezoid::move(vec last_one,vec mid_one,vec next_one,vec new_center) {
    vec this_one=mid_one;
    vec one_next=next_one;
    one_next.vector_minus(mid_one);
    this_one.vector_minus(last_one);
    double angle=one_next.the_angle_between_two_vector(this_one);
    if (angle>pi/2){
        angle-=pi;
    }
    if (this_one.outside_product(one_next)<=0){
        small_one.vector_right_angle(angle);
        big_one.vector_right_angle(angle);
    }else {
        small_one.vector_light_angle(angle);
        big_one.vector_light_angle(angle);
    };
    center=new_center;
}

void trapezoid::rotate(double angle) {
    small_one.vector_right_angle(angle);
    big_one.vector_right_angle(angle);
}

semicircle::semicircle(vec insert_clock_order_one, vec insert_center, double color1, double color2,
        double color3):color_figure(insert_center,color1,color2,color3) {
    clock_order_one=insert_clock_order_one;
}

void semicircle::draw() {
    vec store_vector=clock_order_one;
    glColor3f(color_1,color_2,color_3);
    glBegin(GL_POLYGON);
    for (int i=0;i<401;i++) {
        glVertex2f((GLfloat)(center.get_x()+clock_order_one.get_x()),(GLfloat)(center.get_y()+clock_order_one.get_y()));
        clock_order_one.vector_right_angle(pi/400);
    };
    clock_order_one=store_vector;
    glVertex2f((GLfloat)center.get_x(),(GLfloat)center.get_y());
    glEnd();
}

void semicircle::zoom(double scale) {
    clock_order_one.vector_constant(scale);
}

void semicircle::move(vec last_one,vec mid_one,vec next_one,vec new_center) {
    vec this_one=mid_one;
    vec one_next=next_one;
    one_next.vector_minus(mid_one);
    this_one.vector_minus(last_one);
    double angle=one_next.the_angle_between_two_vector(this_one);
    if (angle>pi/2){
        angle-=pi;
    }
    if (this_one.outside_product(one_next)<=0){
        clock_order_one.vector_right_angle(angle);
        center.vector_right_angle(angle);
    }else {
        clock_order_one.vector_light_angle(angle);
        center.vector_light_angle(angle);
    };
    center=new_center;
}

void semicircle::rotate(double angle) {
    clock_order_one.vector_right_angle(angle);
}


parallelogram::parallelogram(vec insert_first_one, vec insert_second_one, vec insert_center, double color1, double color2,
                             double color3):color_figure(insert_center,color1,color2,color3){
    first_one=insert_first_one;
    second_one=insert_second_one;
}

void parallelogram::draw() {
    glColor3f(color_1,color_2,color_3);
    glBegin(GL_QUADS);
    vec point1=center,point2=center,point3=center,point4=center;
    point1.vector_plus(first_one);
    point2.vector_plus(second_one);
    point3.vector_plus(first_one.reverse_vector(1));
    point4.vector_plus(second_one.reverse_vector(1));
    glVertex2f((GLfloat)point1.get_x(),(GLfloat)point1.get_y());
    glVertex2f((GLfloat)point2.get_x(),(GLfloat)point2.get_y());
    glVertex2f((GLfloat)point3.get_x(),(GLfloat)point3.get_y());
    glVertex2f((GLfloat)point4.get_x(),(GLfloat)point4.get_y());
    glEnd();
}

void parallelogram::zoom(double scale) {
    first_one.vector_constant(scale);
    second_one.vector_constant(scale);
}

void parallelogram::move(vec last_one,vec mid_one,vec next_one,vec new_center) {
    vec this_one=mid_one;
    vec one_next=next_one;
    one_next.vector_minus(mid_one);
    this_one.vector_minus(last_one);
    double angle=one_next.the_angle_between_two_vector(this_one);
    if (angle>pi/2){
        angle-=pi;
    }
    if (this_one.outside_product(one_next)<=0){
        first_one.vector_right_angle(angle);
        second_one.vector_right_angle(angle);
    }else {
        first_one.vector_light_angle(angle);
        second_one.vector_light_angle(angle);
    };
    center=new_center;
}

void parallelogram::rotate(double angle) {
    first_one.vector_right_angle(angle);
    second_one.vector_right_angle(angle);
}

triangle::triangle(vec insert_first_one, vec insert_second_one, vec insert_center, double color1, double color2,
                   double color3) :color_figure(insert_center,color1,color2,color3){
    first_one=insert_first_one;
    second_one=insert_second_one;
}

void triangle::draw() {
    vec point1=center,point2=center;
    point1.vector_plus(first_one);
    point2.vector_plus(second_one);
    glColor3f(color_1,color_2,color_3);
    glBegin(GL_TRIANGLES);
    glVertex2f((GLfloat)point1.get_x(),(GLfloat)point1.get_y());
    glVertex2f((GLfloat)point2.get_x(),(GLfloat)point2.get_y());
    glVertex2f((GLfloat)center.get_x(),(GLfloat)center.get_y());
    glEnd();
}

void triangle::zoom(double scale) {
    first_one.vector_constant(scale);
    second_one.vector_constant(scale);
}

void triangle::move(vec last_one,vec mid_one,vec next_one,vec new_center) {
    vec this_one=mid_one;
    vec one_next=next_one;
    one_next.vector_minus(mid_one);
    this_one.vector_minus(last_one);
    double angle=one_next.the_angle_between_two_vector(this_one);
    if (angle>pi/2){
        angle-=pi;
    }
    if (this_one.outside_product(one_next)<=0){
        first_one.vector_right_angle(angle);
        second_one.vector_right_angle(angle);
        center.vector_right_angle(angle);
    }else {
        first_one.vector_light_angle(angle);
        second_one.vector_light_angle(angle);
        center.vector_light_angle(angle);
    };
    center=new_center;
}

void triangle::rotate(double angle) {
    first_one.vector_right_angle(angle);
    second_one.vector_right_angle(angle);
}
Rocket::Rocket(vec insert_center,int insert_index):group(insert_center,insert_index) {
    links=new vec*[5];
    vec vec1(-0.08,0.0),vec2(-0.04,0.0693),vec3(0.04,0.06);
    links[0]=new vec(0.04,0.06);
    vec3.vector_plus(center);
    figure[0]=new triangle(vec1,vec2,vec3,0.7,0.1,0.2);
    vec vec4(0.04,-0.06),vec5(0.04,0.06),vec15(0,0);
    links[1]=new vec(0.001,0.001);
    vec15.vector_plus(center);
    figure[1]=new parallelogram(vec4,vec5,vec15,1.0, 0.0, 1.0);
    vec vec6(-0.025,0.0),vec7(0.0,0.06),vec8(-0.04,-0.06);
    links[2]=new vec(-0.0370,-0.06);
    vec8.vector_plus(center);
    figure[2]=new triangle(vec6,vec7,vec8,0.0, 1.0, 1.0);
    vec vec9(-0.025,0.0),vec10(-0.025,0.06),vec11(0.0655,-0.06);
    links[3]=new vec(0.0655,-0.06);
    vec11.vector_plus(center);
    figure[3]=new triangle(vec9,vec10,vec11,0.0, 1.0, 1.0);
    vec vec12(0.04,-0.0231), vec13(0.02,0.01155),vec14(0.0,-0.0695);
    links[4]=new vec(0.0,-0.0695);
    vec14.vector_plus(center);
    figure[4]=new trapezoid(vec12,vec13,vec14,0.4, 0.0, 0.0);
};

Rocket::~Rocket() {
    for (auto &i : figure) {
        delete(i);
    }
};

void Rocket::draw() {
    for (auto i: figure){
        i->draw();
    };
    if(!if_end){
        if(if_start){
            track();
        };
    };
};

void Rocket::action() {
    static double times=1;
    static int judge=0;
    if(judge==0){
        if(times>1.1){
            judge=1;
        }
        figure[4]->zoom(9.0/8);
        times=times*9/8;
    }else{
        if(times<1){
            judge=0;
        };
        figure[4]->zoom(8.0/9);
        times=times*8/9;
    };

};

void Rocket::move() {
    if(!if_end){
        vec next_one=node_now->next->coordinate;
        vec this_one=node_now->coordinate;
        vec last_one=node_last->coordinate;
        next_one.vector_minus(this_one);
        this_one.vector_minus(last_one);
        double angle=next_one.the_angle_between_two_vector(this_one);
        if (angle>pi/2){
            angle-=pi;
        }
        for(int i=0;i<5;i++){
            if (this_one.outside_product(next_one)<=0){
                links[i]->vector_right_angle(angle);
            }else {
                links[i]->vector_light_angle(angle);
            };
            vec temp_center=node_now->coordinate;
            temp_center.vector_plus(*links[i]);
            figure[i]->move(node_last->coordinate,node_now->coordinate,node_now->next->coordinate,temp_center);
        }
        run_routine_node();
    };

}

void Rocket::set_figures_center(vec insert_center) {
    for (int i=0;i<5;i++){
        vec temp=insert_center;
        temp.vector_plus(*links[i]);
        figure[i]->set_center(temp);
    };
    this->set_center(insert_center);
};

Radar::Radar(vec insert_center,int insert_index): group(insert_center,insert_index){
    links=new vec*[5];
    vec vec1(-0.00550,0.0108),vec2(0.0100,-0.0108),vec3(-0.03125,0.0541);
    vec1.vector_constant(1.5);vec2.vector_constant(1.5);vec2.vector_constant(1.5);
    links[0]=new vec(-0.03125,0.0541);links[0]->vector_constant(1.5);
    vec3.vector_plus(center);
    figure[0]=new parallelogram(vec1,vec2,vec3,0.0, 1.0, 1.0);
    vec vec4(0.0100,0.0108),vec5(-0.00550,-0.0108),vec6(0.03125,0.0541);
    vec4.vector_constant(1.5);vec5.vector_constant(1.5);vec6.vector_constant(1.5);
    links[1]=new vec(0.03125,0.0541);links[1]->vector_constant(1.5);
    vec6.vector_plus(center);
    figure[1]=new parallelogram(vec4,vec5,vec6,0.0, 1.0, 1.0);
    vec vec7(-0.050),vec8(0.0,0.0);
    vec7.vector_constant(1.5);vec8.vector_constant(1.5);
    links[2]=new vec(0.001,0.001);links[2]->vector_constant(1.5);
    vec8.vector_plus(center);
    figure[2]=new semicircle(vec7,vec8,1.0, 1.0, 0.0);
    vec vec9(0.02215,-0.0128), vec10(0.0125,0.0072),vec11(-0.025,-0.0042);
    vec9.vector_constant(1.5);vec10.vector_constant(1.5);vec11.vector_constant(1.5);
    links[3]=new vec(-0.025,-0.0042);links[3]->vector_constant(1.5);
    vec11.vector_plus(center);
    figure[3]=new trapezoid(vec9,vec10,vec11,0.4,0.1,0.1);
    vec vec12(0.02215,-0.0128),vec13(0.0125,0.0072),vec14(0.025,-0.0042);
    vec12.vector_constant(1.5);vec13.vector_constant(1.5);vec14.vector_constant(1.5);
    links[4]=new vec(0.025,-0.0042);links[4]->vector_constant(1.5);
    vec14.vector_plus(center);
    figure[4]=new trapezoid(vec12,vec13,vec14,0.4,0.1,0.1);
};

Radar::~Radar() {
    for (auto &i : figure) {
        delete(i);
    };
    delete[] *links;
    delete(links);
};

void Radar::draw() {
    for (auto i:figure){
        i->draw();
    };
    if(!if_end){
        if(if_start){
            track();
        }
    };
};

void Radar::action() {
    for (auto i:figure){
        i->rotate(pi/180);
    };
    for (int i=0;i<5;i++){
        links[i]->vector_right_angle(pi/180);
    }
};

void Radar::move() {
    if(!if_end){
        vec next_one=node_now->next->coordinate;
        vec this_one=node_now->coordinate;
        vec last_one=node_last->coordinate;
        next_one.vector_minus(this_one);
        this_one.vector_minus(last_one);
        double angle=next_one.the_angle_between_two_vector(this_one);
        if (angle>pi/2){
            angle-=pi;
        }
        for(int i=0;i<5;i++){
            if (this_one.outside_product(next_one)<=0){
                links[i]->vector_right_angle(angle);
            }else {
                links[i]->vector_light_angle(angle);
            };
            vec temp_center=node_now->coordinate;
            temp_center.vector_plus(*links[i]);
            figure[i]->move(node_last->coordinate,node_now->coordinate,node_now->next->coordinate,temp_center);
        }
        run_routine_node();
    };
}

void Radar::set_figures_center(vec insert_center) {
    for (int i=0;i<5;i++){
        vec temp=insert_center;
        temp.vector_plus(*links[i]);
        figure[i]->set_center(temp);
    };
    this->set_center(insert_center);
};

Car::Car(vec insert_center,int insert_index): group(insert_center,insert_index) {
    links=new vec*[6];
    vec vec1(-0.02404,0.1202),vec2(0.02404,0.1202),vec3(0.02404,0);
    links[0]=new vec(0.02404,0);
    vec3.vector_plus(center);
    figure[0]=new parallelogram(vec1,vec2,vec3,255,0.0,0.0);
    vec vec4(-0.012019,0.0601),vec5(0.018029,0.072115),vec6(-0.015000,0.0);
    links[1]=new vec(-0.015000,0.0);
    vec6.vector_plus(center);
    figure[1]=new trapezoid(vec4,vec5,vec6,0,0,205);
    vec vec7(0.0,0.024048),vec8(0.048077,-0.060096);
    links[2]=new vec(0.048077,-0.060096);
    vec8.vector_plus(center);
    figure[2]=new semicircle(vec7,vec8,0.0,0.0,0.0);
    vec vec9(0.0,0.024048),vec10(0.048077,0.060096);
    links[3]=new vec(0.048077,0.060096);
    vec10.vector_plus(center);
    figure[3]=new semicircle(vec9,vec10,0.0,0.0,0.0);
    vec vec11(-0.035,0.0039243f),vec12(0.035,0.0039243f),vec13(-0.034,0.08);
    links[4]=new vec(-0.034,0.08);
    vec13.vector_plus(center);
    figure[4]=new parallelogram(vec11,vec12,vec13,0.0,0.0,0.0);
    vec vec14(0.01,0.02),vec15(-0.01,0.02),vec16(-0.060,0.1);
    links[5]=new vec(-0.060,0.1);
    vec16.vector_plus(center);
    figure[5]=new parallelogram(vec14,vec15,vec16,1.0, 0.0, 0.0);
}

Car::~Car() {
    for (auto &i : figure) {
        delete(i);
    };
    delete[] *links;
    delete(links);
}

void Car::draw() {
    for (auto i:figure){
        i->draw();
    };
    if(!if_end){
        if(if_start){
            track();
        }
    };
};

void Car::move() {
    if(!if_end){
        vec next_one=node_now->next->coordinate;
        vec this_one=node_now->coordinate;
        vec last_one=node_last->coordinate;
        next_one.vector_minus(this_one);
        this_one.vector_minus(last_one);
        double angle=next_one.the_angle_between_two_vector(this_one);
        if (angle>pi/2){
            angle-=pi;
        };
        for(int i=0;i<6;i++){
            if (this_one.outside_product(next_one)<=0){
                links[i]->vector_right_angle(angle);
            }else {
                links[i]->vector_light_angle(angle);
            };
            vec temp_center=node_now->coordinate;
            temp_center.vector_plus(*links[i]);
            figure[i]->move(node_last->coordinate,node_now->coordinate,node_now->next->coordinate,temp_center);
        }
        run_routine_node();
    };
}

void Car::action() {
    static double times=1;
    static int judge=0;
    static vec vec_move(0.002,0);
    vec next_one=node_now->next->coordinate;
    vec this_one=node_now->coordinate;
    vec last_one=node_last->coordinate;
    next_one.vector_minus(this_one);
    this_one.vector_minus(last_one);
    double angle=next_one.the_angle_between_two_vector(this_one);
    if (angle>pi/2){
        angle-=pi;
    };
    if (this_one.outside_product(next_one)<=0){
        vec_move.vector_right_angle(angle);
    }else {
        vec_move.vector_light_angle(angle);
    };
    if(judge==0){
        if(times>2048){
            judge=1;
        }
        figure[5]->get_center().vector_plus(vec_move);
        links[5]->vector_plus(vec_move);
        times=times*2;
    }else{
        if(times<1){
            judge=0;
        };
        figure[5]->get_center().vector_minus(vec_move);
        links[5]->vector_minus(vec_move);
        times=times/2;
    };
}

void Car::set_figures_center(vec insert_center) {
    for (int i=0;i<6;i++){
        vec temp=insert_center;
        temp.vector_plus(*links[i]);
        figure[i]->set_center(temp);
    };
    this->set_center(insert_center);
}

void Car::set_free_move(int key) {
    vec vec1(0.02,0),vec2(0,0.02),center[6];
    vec total_center=this->get_center();
    vec vec3(0.0,0.0),vec4(1,0),vec5(2,0.1),vec6(1,0.1),vec7(1,-0.1);
    for (int i=0;i<6;i++){
        center[i]=figure[i]->get_center();
    }
    if(key==GLUT_KEY_UP){
        for (int i=0;i<6;i++){
            center[i].vector_plus(vec2);
            figure[i]->set_center(center[i]);
            total_center.vector_plus(vec2);
        };
    }else if (key==GLUT_KEY_DOWN){
        for (int i=0;i<6;i++){
            center[i].vector_minus(vec2);
            figure[i]->set_center(center[i]);
            total_center.vector_minus(vec2);
        };
    }else if(key==GLUT_KEY_LEFT){
        for (int i=0;i<6;i++){
            center[i].vector_minus(vec1);
            figure[i]->set_center(center[i]);
            total_center.vector_minus(vec1);
        };
    }else if(key==GLUT_KEY_RIGHT){
        for (int i=0;i<6;i++){
            center[i].vector_plus(vec1);
            figure[i]->set_center(center[i]);
            total_center.vector_plus(vec1);
        };
    };
    this->set_center(total_center);
 }


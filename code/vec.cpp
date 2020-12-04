#include "Figure.h"
#include "vec.h"
vec::vec(double insert_x, double insert_y) {
    x=insert_x;
    y=insert_y;
}

double vec::get_x() {
    return x;
}

double vec::get_y() {
    return y;
}

void vec::vector_constant(double constant) {
    x*=constant;
    y*=constant;
}

void vec::vector_plus(vec another_one) {
    x+=another_one.get_x();
    y+=another_one.get_y();
}

void vec::vector_minus(vec another_one) {
    x-=another_one.get_x();
    y-=another_one.get_y();
}

double vec::vector_times(vec another_one) {
    return another_one.get_x()*x+another_one.get_y()*y;
}

double vec::vector_absolute() {
    return sqrt(pow(y,2)+pow(x,2));
}

void vec::vector_right_angle(double angle) {
    const float pi=3.1415926536f;
    if(y>=0){
        x=this->vector_absolute()*cos(acos(x/this->vector_absolute())-angle);
        y=this->vector_absolute()*sin(acos(x/this->vector_absolute())-angle);
    }else if (x>=0 && y<0){
        x=this->vector_absolute()*cos(asin(y/this->vector_absolute())-angle);
        y=this->vector_absolute()*sin(asin(y/this->vector_absolute())-angle);
    }else {
        x=this->vector_absolute()*cos(pi-asin(y/this->vector_absolute())-angle);
        y=this->vector_absolute()*sin(pi-asin(y/this->vector_absolute())-angle);
    }
}

void vec::vector_light_angle(double angle) {
    const float pi=3.1415926536f;
    if(y>=0){
        x=this->vector_absolute()*cos(acos(x/this->vector_absolute())+angle);
        y=this->vector_absolute()*sin(acos(x/this->vector_absolute())+angle);
    }else if (x>=0 && y<0){
        x=this->vector_absolute()*cos(asin(y/this->vector_absolute())+angle);
        y=this->vector_absolute()*sin(asin(y/this->vector_absolute())+angle);
    }else {
        x=this->vector_absolute()*cos(pi-asin(y/this->vector_absolute())+angle);
        y=this->vector_absolute()*sin(pi-asin(y/this->vector_absolute())+angle);
    }
}

double vec::the_angle_between_two_vector(vec another_one) {
    return acos(this->vector_times(another_one)/(this->vector_absolute()*another_one.vector_absolute()));
}

vec vec::reverse_vector(double scale) {
    vec reverse_one(-this->get_x()*scale,-this->get_y()*scale);
    return reverse_one;
}

double vec::outside_product(vec another_one) {
    return x*another_one.get_y()-y*another_one.get_x();
}

void vec::set_x(double insert_one) {
    x=insert_one;
}

void vec::set_y(double insert_one) {
    y=insert_one;
};

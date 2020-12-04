#ifndef P3_INTERSTELLAR_VEC_H
#define P3_INTERSTELLAR_VEC_H

typedef class vec {
public:
    explicit vec(double insert_x=0,double insert_y=0);
    ~vec()= default;
    double get_x();
    double get_y();
    void vector_constant(double constant);
    void vector_plus(vec another_one);
    void vector_minus(vec another_one);
    double vector_times(vec another_one);
    double vector_absolute();
    void vector_right_angle(double angle);
    void vector_light_angle(double angle);
    double the_angle_between_two_vector(vec another_one);
    vec reverse_vector(double scale);
    double outside_product(vec another_one);
    void set_x(double insert_one);
    void set_y(double insert_one);
private:
    double x;
    double y;
}vec;


#endif

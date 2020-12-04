#include "vec.h"
#include <cmath>
#include "Figure.h"
void group::find_path(){
    const float pi=3.1415926536f;
    vec *Vec= new vec[2000];
    for(int i=0;i<2000;i++){
        (Vec+i)->set_x(0.0);
        (Vec+i)->set_y(0.0);
    }
    int counter=0;
    while (counter<=57){//going straight into the parking lot
        (Vec+counter)->set_x(0.0);
        (Vec+counter)->set_y(0.005);
        counter++;
    }
    while (counter>57&&counter<=147){//90 vector is used in turning, the radius will be 0.231177
        (Vec+counter)->set_x(0.004*sin((counter-57)*pi/180));
        (Vec+counter)->set_y(0.004*cos((counter-57)*pi/180));
        counter++;
    }
    if (index<8){//proceed straight 45+(index-1)*38 more steps
        while(counter<=147+45+(index-1)*38){
            (Vec+counter)->set_x(0.005);
            (Vec+counter)->set_y(0.0);
            counter++;
        }
        for(int i=1;i<=90;i++) {//drive into the slot
            (Vec+counter)->set_x(-0.004 * cos(i * pi / 180));
            (Vec+counter)->set_y( -0.004 * sin(i * pi / 180));
            counter++;
        }
        for(int i=1;i<=29;i++){
            (Vec+counter)->set_x(0.0);
            (Vec+counter)->set_y(-0.005);
            counter++;
        }
    }
    else if(index==8){//index>8
        while(counter<=147+45+(index-1)*38-10){
            (Vec+counter)->set_x(0.005);
            (Vec+counter)->set_y(0.0);
            counter++;
        }
        for(int i=1;i<=90;i++) {//drive into the slot
            (Vec+counter)->set_x(-0.003 * cos(i * pi / 180));
            (Vec+counter)->set_y(-0.003 * sin(i * pi / 180));
            counter++;
        }
        for(int i=1;i<=39;i++){
            (Vec+counter)->set_x(0.0);
            (Vec+counter)->set_y(-0.005);
            counter++;
        }
    }
    else if(index>8){
        while(counter<=147+275){
            (Vec+counter)->set_x(0.005);
            (Vec+counter)->set_y(0.0);
            counter++;
        }
        for(int i=1;i<=90;i++) {
            (Vec+counter)->set_x(0.003 * cos(i * pi / 180));
            (Vec+counter)->set_y(0.003 * sin(i * pi / 180));
            counter++;
        }
        for(int i=1;i<=6;i++){
            (Vec+counter)->set_x(0.0);
            (Vec+counter)->set_y(0.005);
            counter++;
        }
        for(int i=1;i<=90;i++) {
            (Vec+counter)->set_x(-0.003 * sin(i * pi / 180));
            (Vec+counter)->set_y(0.003 * cos(i * pi / 180));
            counter++;
        }
        for(int i=1;i<=53+(index-9)*38;i++){//now it's on the 9-16 slots
            (Vec+counter)->set_x(-0.005);
            (Vec+counter)->set_y(0.0);
            counter++;
        }
        for(int i=1;i<=90;i++){
            (Vec+counter)->set_x(0.004 * cos(i * pi / 180));
            (Vec+counter)->set_y(0.004 * sin(i * pi / 180));
            counter++;
        }
        for(int i=1;i<=29;i++){
            (Vec+counter)->set_x(0.0);
            (Vec+counter)->set_y(0.005);
            counter++;
        };
    };
    vec temp_vec(-0.855387,-0.671685);
    head=new routine_node;
    head->coordinate=temp_vec;
    head->next= nullptr;
    routine_node *temp=head;
    for (int i=0;i<counter;i++){
        temp_vec.vector_plus(Vec[i]);
        auto * body_node=new routine_node;
        body_node->coordinate=temp_vec;
        body_node->next=nullptr;
        temp->next=body_node;
        temp=temp->next;
    };
}
#include "main.h"

#ifndef Boat_H
#define Boat_H


class Boat {
public:
    Boat() {}
    Boat(float x, float y, color_t color);
    glm::vec3 position;
    float rotation;
    
    void draw(glm::mat4 VP);
    void set_position(float x, float y,float z);
    void tick();
    void tick1();
    float length,width;
    double speed =1;
    double speedy ;
    double speedw=0.03 ;
    bool jumping ;
    double jumpTime =0;
    double ground =0;
    double flagz=0;
    bounding_box_t bounding_box();
    void Jump(float);
    bool destroyed = false;
    void drawFlag();
private:
    VAO *object;
    VAO *object1;
    VAO *object2;
    VAO *object3;
    VAO *object4;
};

#endif // Boat_H

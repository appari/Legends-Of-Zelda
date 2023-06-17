#include "main.h"

#ifndef Cannon_H
#define Cannon_H


class Cannon {
public:
    Cannon() {}
    Cannon(float x, float y,float z ,color_t color);
    glm::vec3 position;
    float rotation;
    float rotation1;
    float side = 2;
    void draw(glm::mat4 VP);
    void set_position(float x, float y,float z);
    void tick();
    bounding_box_t bounding_box();
    
    double speed;
private:
    VAO *object;
};

#endif // Cannon_H

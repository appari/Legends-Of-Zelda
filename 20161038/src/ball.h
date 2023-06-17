#include "main.h"

#ifndef BALL_H
#define BALL_H


class Ball {
public:
    Ball() {}
    Ball(float x, float y, float z,float speedx,float speedy,float speedz,float size);
    glm::vec3 position;
    float rotation;
    float rotation1;
    float rotation2;
    float speedx,speedy,speedz;
    bool fire=false;
    void draw(glm::mat4 VP);
    void set_position(float x, float y,float z);
    void tick();
    float gravity = 0.02;
    void tick1();
    bool destroyed = false;
    float size;
     bounding_box_t bounding_box();
    double speed=0.1;
private:
    VAO *object;
};

#endif // BALL_H
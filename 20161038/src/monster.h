#include "main.h"

#ifndef Monster_H
#define Monster_H


class Monster {
public:
    Monster() {}
    Monster(float x, float y, float z,color_t color);
    glm::vec3 position;
    float rotation;
    float rotation1;
    float rotation2;
    bool active = true;
    bool fire=false;
    void draw(glm::mat4 VP);
    void set_position(float x, float y,float z);
    void tick();
    void tick1(float x,float z);
    float side = 1.6;
    double speed=0.1;
    double speedy=0.2;
     bounding_box_t bounding_box();
     float health = 5;
     float rad = 0.5;
     float height = 4;
private:
    VAO *object;
    VAO *object1;
    VAO *object2;
    VAO *object3;
    VAO *object4;
};

#endif // Monster_H
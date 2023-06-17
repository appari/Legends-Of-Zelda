#include "main.h"

#ifndef Gift_H
#define Gift_H


class Gift {
public:
    Gift() {}
    Gift(float x, float y,float z ,color_t color);
    glm::vec3 position;
    float rotation;
    float side = 0.2;
    void draw(glm::mat4 VP);
    void set_position(float x, float y,float z);
    void tick();
    bool Point;
    bounding_box_t bounding_box();
    double ground;
    double speedw = 0.02;
    void tick1();
    double speed;
private:
    VAO *object;
    VAO *object1;
    VAO *object2;
};

#endif // Gift_H

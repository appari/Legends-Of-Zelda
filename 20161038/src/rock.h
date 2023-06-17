#include "main.h"

#ifndef rock_H
#define rock_H


class Rock {
public:
    Rock() {}
    Rock(float x, float y,float z ,color_t color);
    glm::vec3 position;
    float rotation;
    float side = 2;
    void draw(glm::mat4 VP);
    void set_position(float x, float y,float z);
    void tick();
    int noColls=0;
    bool collapsed = false;
    bounding_box_t bounding_box();

    double speed;
private:
    VAO *object;
};

#endif // rock_H

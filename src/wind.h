#include "main.h"

#ifndef Wind_H
#define Wind_H


class Wind {
public:
    Wind() {}
    Wind(float x, float y,float z ,color_t color);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y,float z);
    void tick();
    float windTimer =0;
    float side = 0.5;
    
    double speed;
private:
    VAO *object;
};

#endif // Wind_H

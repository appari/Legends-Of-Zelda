#include "main.h"

#ifndef SEA_H
#define SEA_H


class Sea {
public:
    Sea() {}
    Sea(float x, float y, color_t color,int area);
    glm::vec3 position;
    float rotation;
    
    void draw(glm::mat4 VP);
    void set_position(float x, float y,float z);
    void tick();
    int triCnt;
    int triCnt1;
    double speed;
    int area=250;
    int c=0;
    void drawSea();

  private:
    VAO *object;
    VAO *object1;
};

#endif // sea_H

#include "booster.h"
#include "main.h"

Booster::Booster(float x, float y,float z ,color_t color) {
    this->position = glm::vec3(x, y, z);
    this->rotation = 0;
    speed = 1;
    
    float a = this->side;
    static const GLfloat vertex_buffer_data[] =  { 
        -a,-a,-a, // triangle 1 : begin
        -a,-a, a,
        -a, a, a, // triangle 1 : end
        a, a,-a, // triangle 2 : begin
        -a,-a,-a,
        -a, a,-a, // triangle 2 : end
        a,-a, a,
        -a,-a,-a,
        a,-a,-a,
        a, a,-a,
        a,-a,-a,
        -a,-a,-a,
        -a,-a,-a,
        -a, a, a,
        -a, a,-a,
        a,-a, a,
        -a,-a, a,
        -a,-a,-a,
        -a, a, a,
        -a,-a, a,
        a,-a, a,
        a, a, a,
        a,-a,-a,
        a, a,-a,
        a,-a,-a,
        a, a, a,
        a,-a, a,
        a, a, a,
        a, a,-a,
        -a, a,-a,
        a, a, a,
        -a, a,-a,
        -a, a, a,
        a, a, a,
        -a, a, a,
        a,-a, a
        
        
    };
    
    this->object = create3DObject(GL_TRIANGLES, 12*3, vertex_buffer_data, COLOR_BOOSTER , GL_FILL);

}

void Booster::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(1, 1, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    
    draw3DObject(this->object);
}

void Booster::set_position(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
}
bounding_box_t Booster::bounding_box() {
    float x = this->position.x,z = this->position.z;
    bounding_box_t bbox = { x,this->position.y, z, this->side,this->side,this->side};
    return bbox;
}

void Booster::tick() {
    this->rotation += 10;
    //this->position.z += speed;
    // this->position.x -= speed;
    // this->position.y -= speed;
}

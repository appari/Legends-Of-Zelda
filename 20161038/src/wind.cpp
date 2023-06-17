#include "wind.h"
#include "main.h"

Wind::Wind(float x, float y,float z ,color_t color) {
    this->position = glm::vec3(x, y, z);
    this->rotation = 0;
    speed = 1;
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    float a = this->side;

    static const GLfloat vertex_buffer_data[] =  { 
        -a+5,0,0,
        5,0,a,
        5,0,-a,

        5,0,a/2,
        5,0,-a/2,
        a*3/2+5,0,-a/2,

        a*3/2+5,0,-a/2,
        a*3/2+5,0,a/2,
        5,0,a/2

        

        
        
        
    };
   
    this->object = create3DObject(GL_TRIANGLES, 3*3, vertex_buffer_data, color , GL_FILL);

}

void Wind::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 1, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    
    draw3DObject(this->object);
}

void Wind::set_position(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
}

void Wind::tick() {
    //this->position.z += speed;
    // this->position.x -= speed;
    // this->position.y -= speed;
}

#include "cannon.h"
#include "main.h"

Cannon::Cannon(float x, float y,float z ,color_t color) {
    this->position = glm::vec3(x, y, z);
    this->rotation = 0;
    speed = 1;
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    float a = this->side;

    GLfloat g_vertex_buffer_data[4000];
    float PI = 3.14159265;
    float r = 0.3,height = 0.2;
    int top = 0;
    // float z = 0;
    float degree = 0;
    while(degree <= 360.0f)
    {
        g_vertex_buffer_data[top++] = -5;
        g_vertex_buffer_data[top++] = r*sin(degree*PI/180.0);
        g_vertex_buffer_data[top++] = -r*cos(degree*PI/180.0);

        g_vertex_buffer_data[top++] = 0;
        g_vertex_buffer_data[top++] = r*sin(degree*PI/180.0);
        g_vertex_buffer_data[top++] = -r*cos(degree*PI/180.0);

        degree += 1;

    }


    this->object = create3DObject(GL_LINES, top/3, g_vertex_buffer_data, color, GL_FILL);
   
    

}

void Cannon::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 1, 0));
    glm::mat4 rotate1    = glm::rotate((float) (this->rotation1 * M_PI / 180.0f), glm::vec3(0, 0, 1));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate*rotate1);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    
    draw3DObject(this->object);
}

void Cannon::set_position(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
}
bounding_box_t Cannon::bounding_box() {
    float x = this->position.x, z = this->position.z;
    bounding_box_t bbox = { x, z, this->side,this->side,this->side};
    return bbox;
}

void Cannon::tick() {
    
}

#include "land.h"
#include "main.h"

Land::Land(float x, float y, float z, color_t color) {
    this->position = glm::vec3(x, y, z);
    this->rotation = 0;
    float w =10,l=10,h=10;
       static const GLfloat vertex_buffer_data[] = {
        -w/2,-l/2,-h/2, // triangle 1 : begin
        -w/2,-l/2, h/2,
        -w/2, l/2, h/2, // triangle 1 : end

        w/2, l/2,-h/2, // triangle 2 : begin
        -w/2,-l/2,-h/2,
        -w/2,l/2,-h/2, // triangle 2 : end

        w/2,-l/2, h/2,
        -w/2,-l/2,-h/2,
        w/2,-l/2,-h/2,

        w/2, l/2,-h/2,
        w/2,-l/2,-h/2,
        -w/2,-l/2,-h/2,

        -w/2,-l/2,-h/2,
        -w/2, l/2, h/2,
        -w/2, l/2,-h/2,

        w/2,-l/2, h/2,
        -w/2,-l/2, h/2,
        -w/2,-l/2,-h/2,

        -w/2, l/2, h/2,
        -w/2,-l/2, h/2,
        w/2,-l/2, h/2,

        w/2, l/2, h/2,
        w/2,-l/2,-h/2,
        w/2, l/2,-h/2,

        w/2,-l/2,-h/2,
        w/2, l/2, h/2,
        w/2,-l/2, h/2,

        w/2, l/2, h/2,
        w/2, l/2,-h/2,
        -w/2, l/2,-h/2,

        w/2, l/2, h/2,
        -w/2, l/2,-h/2,
        -w/2, l/2, h/2,

        w/2, l/2, h/2,
        -w/2, l/2, h/2,
        w/2,-l/2, h/2
    };

    this->object[0] = create3DObject(GL_TRIANGLES, 12*3, vertex_buffer_data, color, GL_FILL);

    static const GLfloat vertex_buffer_data1[] = {
        -40.0f,-1.0f,-40.0f, // triangle 1 : begin
        -40.0f,-1.0f, 40.0f,
        0, 20.0f, 0, // triangle 1 : end

        
        40.0f,-1.0f, 40.0f,
        -40.0f,-1.0f,-40.0f,
        40.0f,-1.0f,-40.0f,

        0, 20.0f, 0 ,
        40.0f,-1.0f,-40.0f,
        -40.0f,-1.0f,-40.0f,

        
        40.0f,-1.0f, 40.0f,
        -40.0f,-1.0f, 40.0f,
        -40.0f,-1.0f,-40.0f,

          0,20.0f, 0 ,
        -40.0f,-1.0f, 40.0f,
        40.0f,-1.0f, 40.0f,


        40.0f,-1.0f,-40.0f,
          0, 20.0f, 0 ,
        40.0f,-1.0f, 40.0f,

        
        
    };
    static const GLfloat color_buffer_data[] = {
        0, 10, 0,              // triangle 1 : end
        0, 10, 0,              // triangle 1 : end
        -40.0f, -1.0f, -40.0f, // triangle 1 : begin

        0, 10, 0,              // triangle 1 : end
        0, 10, 0,              // triangle 1 : end
        -40.0f, -1.0f, -40.0f, // triangle 1 : begin

        0, 10, 0,              // triangle 1 : end
        0, 10, 0,              // triangle 1 : end
        -40.0f, -1.0f, -40.0f, // triangle 1 : begin

        0, 10, 0,              // triangle 1 : end
        0, 10, 0,              // triangle 1 : end
        -40.0f, -1.0f, -40.0f, // triangle 1 : begin

        0, 10, 0,              // triangle 1 : end
        0, 10, 0,              // triangle 1 : end
        -40.0f, -1.0f, -40.0f, // triangle 1 : begin

        0, 10, 0,              // triangle 1 : end
        0, 10, 0,              // triangle 1 : end
        -40.0f, -1.0f, -40.0f, // triangle 1 : begin

    };
    this->object[1] = create3DObject(GL_TRIANGLES, 12*3, vertex_buffer_data1,color_buffer_data, GL_FILL);

}


void Land::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(1, 0, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object[0]);
    draw3DObject(this->object[1]);

}

void Land::set_position(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
}

void Land::tick() {
    this->rotation += speed;
    // this->position.x -= speed;
    // this->position.y -= speed;
}

// bounding_box_t Land::bounding_box() {
//     float x = this->position.x, y = this->position.z,z = this->position.y;
//    bounding_box_t bbox ;
//     bbox.position = this->position;
//     return bbox;
// }
#include "gift.h"
#include "main.h"

Gift::Gift(float x, float y,float z ,color_t color) {
    this->position = glm::vec3(x, y, z);
    this->rotation = 0;
    speed = 1;
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has  6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    float a;
    this->ground = y;
    a= this->side;
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

    static const GLfloat vertex_buffer_data2[] =  { 
        -3.5*a,-3.5*a,-3.5*a, // triangle 1 : begin
        -3.5*a,-3.5*a, 3.5*a,
        -3.5*a, 3.5*a, 3.5*a, // triangle 1 : end
        3.5*a, 3.5*a,-3.5*a, // triangle 2 : begin
        -3.5*a,-3.5*a,-3.5*a,
        -3.5*a, 3.5*a,-3.5*a, // triangle 2 : end
        3.5*a,-3.5*a, 3.5*a,
        -3.5*a,-3.5*a,-3.5*a,
        3.5*a,-3.5*a,-3.5*a,
        3.5*a, 3.5*a,-3.5*a,
        3.5*a,-3.5*a,-3.5*a,
        -3.5*a,-3.5*a,-3.5*a,
        -3.5*a,-3.5*a,-3.5*a,
        -3.5*a, 3.5*a, 3.5*a,
        -3.5*a, 3.5*a,-3.5*a,
        3.5*a,-3.5*a, 3.5*a,
        -3.5*a,-3.5*a, 3.5*a,
        -3.5*a,-3.5*a,-3.5*a,
        -3.5*a, 3.5*a, 3.5*a,
        -3.5*a,-3.5*a, 3.5*a,
        3.5*a,-3.5*a, 3.5*a,
        3.5*a, 3.5*a, 3.5*a,
        3.5*a,-3.5*a,-3.5*a,
        3.5*a, 3.5*a,-3.5*a,
        3.5*a,-3.5*a,-3.5*a,
        3.5*a, 3.5*a, 3.5*a,
        3.5*a,-3.5*a, 3.5*a,
        3.5*a, 3.5*a, 3.5*a,
        3.5*a, 3.5*a,-3.5*a,
        -3.5*a, 3.5*a,-3.5*a,
        3.5*a, 3.5*a, 3.5*a,
        -3.5*a, 3.5*a,-3.5*a,
        -3.5*a, 3.5*a, 3.5*a,
        3.5*a, 3.5*a, 3.5*a,
        -3.5*a, 3.5*a, 3.5*a,
        3.5*a,-3.5*a, 3.5*a
    };

    static const GLfloat vertex_buffer_data1[] =  { 
        -4*a,-5.0f,-4*a, // triangle 1 : begin
        -4*a,-5.0f, 4*a,
        -4*a, -1.7f, 4*a, // triangle 1 : end

        4*a, -1.7f,-4*a, // triangle 2 : begin
        -4*a,-5.0f,-4*a,
        -4*a, -1.7f,-4*a, // triangle 2 : end

        4*a,-5.0f, 4*a,
        -4*a,-5.0f,-4*a,
        4*a,-5.0f,-4*a,

        4*a, -1.7f,-4*a,
        4*a,-5.0f,-4*a,
        -4*a,-5.0f,-4*a,

        -4*a,-5.0f,-4*a,
        -4*a, -1.7f, 4*a,
        -4*a, -1.7f,-4*a,

        4*a,-5.0f, 4*a,
        -4*a,-5.0f, 4*a,
        -4*a,-5.0f,-4*a,

        -4*a, -1.7f, 4*a,
        -4*a,-5.0f, 4*a,
        4*a,-5.0f, 4*a,

        4*a, -1.7f, 4*a,
        4*a,-5.0f,-4*a,
        4*a, -1.7f,-4*a,

        4*a,-5.0f,-4*a,
        4*a, -1.7f, 4*a,
        4*a,-5.0f, 4*a,

        4*a, -1.7f, 4*a,
        4*a, -1.7f,-4*a,
        -4*a, -1.7f,-4*a,

        4*a, -1.7f, 4*a,
        -4*a, -1.7f,-4*a,
        -4*a, -1.7f, 4*a,

        4*a, -1.7f, 4*a,
        -4*a, -1.7f, 4*a,
        4*a,-5.0f, 4*a

    };   
    this->object = create3DObject(GL_TRIANGLES, 12*3, vertex_buffer_data, COLOR_GREEN, GL_FILL);
    this->object1 = create3DObject(GL_TRIANGLES, 12*3, vertex_buffer_data1, COLOR_BARRAEL, GL_FILL);
    this->object2 = create3DObject(GL_TRIANGLES, 12*3, vertex_buffer_data2, COLOR_POINTS, GL_FILL);

}

void Gift::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 1, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    
    if(!this->Point)
    {
       draw3DObject(this->object);
       
        draw3DObject(this->object1);
    }
    else
    {
        draw3DObject(this->object2);
    }
}

void Gift::set_position(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
}
bounding_box_t Gift::bounding_box() {
    float x = this->position.x, z = this->position.z;
    bounding_box_t bbox = { x, this->position.y,z, this->side,this->side,this->side};
    return bbox;
}

void Gift::tick1(){
   
    {
        if((this->position.y-this->ground)>1||(this->position.y-this->ground)<0)
            this->speedw = -this->speedw;

        this->position.y += this->speedw;
    }
}

void Gift::tick() {
    this->rotation += 1;
    //this->position.z += speed;
    // this->position.x -= speed;
    // this->position.y -= speed;
}

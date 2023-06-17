#include "boat.h"
#include "main.h"

Boat::Boat(float x, float y, color_t color) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    this->speed = 0.5;
    this->ground = y;
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    /*static const GLfloat vertex_buffer_data[] = {
        -1.0f,-1.0f,-1.0f, // triangle 1 : begin
        -1.0f,-1.0f, 1.0f,
        -1.0f, 1.0f, 1.0f, // triangle 1 : end
        1.0f, 1.0f,-1.0f, // triangle 2 : begin
        -1.0f,-1.0f,-1.0f,
        -1.0f, 1.0f,-1.0f, // triangle 2 : end
        1.0f,-1.0f, 1.0f,
        -1.0f,-1.0f,-1.0f,
        1.0f,-1.0f,-1.0f,
        1.0f, 1.0f,-1.0f,
        1.0f,-1.0f,-1.0f,
        -1.0f,-1.0f,-1.0f,
        -1.0f,-1.0f,-1.0f,
        -1.0f, 1.0f, 1.0f,
        -1.0f, 1.0f,-1.0f,
        1.0f,-1.0f, 1.0f,
        -1.0f,-1.0f, 1.0f,
        -1.0f,-1.0f,-1.0f,
        -1.0f, 1.0f, 1.0f,
        -1.0f,-1.0f, 1.0f,
        1.0f,-1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,
        1.0f,-1.0f,-1.0f,
        1.0f, 1.0f,-1.0f,
        1.0f,-1.0f,-1.0f,
        1.0f, 1.0f, 1.0f,
        1.0f,-1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,
        1.0f, 1.0f,-1.0f,
        -1.0f, 1.0f,-1.0f,
        1.0f, 1.0f, 1.0f,
        -1.0f, 1.0f,-1.0f,
        -1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,
        -1.0f, 1.0f, 1.0f,
        1.0f,-1.0f, 1.0f
    };*/
    this->width = 1;
    this->length = 3.5;
    static const GLfloat vertex_buffer_data1[] = 
        { -2.8,1.4,0.8,
        -2.8,1.4,-0.8,
        -0.8,0.85,-0.8,
        -0.8,0.85,-0.8,
        -0.8,0.85,0.8,
        -2.8,1.4,0.8,
        //top 2
        -0.8,0.85,0.8,
        -0.8,0.85,-0.8,
        0.8,0.85,-0.8,
        0.8,0.85,-0.8,
        0.8,0.85,0.8,
        -0.8,0.85,0.8,
        //top3
        2.8,1.4,0.8,
        2.8,1.4,-0.8,
        0.8,0.85,-0.8,
        0.8,0.85,-0.8,
        0.8,0.85,0.8,
        2.8,1.4,0.8
        };
    static const GLfloat vertex_buffer_data[] = {
        //base
        -3,0,1,
        -3,0,-1, 
        3,0,-1,
        3,0,-1,
        3,0,1,
        -3,0,1,
        
        //side close
        //side1

        -4.5,2,0,
        -3,1.4,1,
        -3,0,1,
        -4.5,2,0,
        -3,1.4,-1,
        -3,0,-1,
        -4.5,2,0,
        -3,0,1,
        -3,0,-1,
        //back pyramid

        4.5,2,0,
        3,1.4,1,
        3,0,1,
        4.5,2,0,
        3,1.4,-1,
        3,0,-1,
        4.5,2,0,
        3,0,1,
        3,0,-1,
        
        //back close
        3,1.4,1,
        3,1.4,-1,
        3,0,-1,
        3,0,-1,
        3,0,1,
        3,1.4,1,
        //side 
        -3,1.4,1,
        -1,0.85,1,
        -3,0,1,
        -3,0,1,
        -1,0,1,
        -1,0.85,1,

        -1,0,1,
        -1,0.85,1,
        1,0.85,1,
        1,0.85,1,
        1,0,1,
        -1,0,1,

        3,1.4,1,
        1,0.85,1,
        3,0,1,
        3,0,1,
        1,0,1,
        1,0.85,1,

        //side2
        -3,1.4,-1,
        -1,0.85,-1,
        -3,0,-1,
        -3,0,-1,
        -1,0,-1,
        -1,0.85,-1,

        -1,0,-1,
        -1,0.85,-1,
        1,0.85,-1,
        1,0.85,-1,
        1,0,-1,
        -1,0,-1,

        3,1.4,-1,
        1,0.85,-1,
        3,0,-1,
        3,0,-1,
        1,0,-1,
        1,0.85,-1,

        -3,0,1,
        -3,0,-1,
        3,0,-1,
        3,0,-1,
        3,0,1,
        -3,0,1
    };
    static const GLfloat vertex_buffer_data2[] = {
        // -3,1.4,0.9,
        // -3,1.4,0.1,
        // -2,1.6,0.1,
        // -2,1.6,0.1,
        // -2,1.6,0.9,
        // -3,1.4,0.9,

        // -3,1.4,-0.9,
        // -3,1.4,-0.1,
        // -2,1.6,-0.1,
        // -2,1.6,-0.1,
        // -2,1.6,-0.9,
        // -3,1.4,-0.9

        -3.0f-0.07f,-0.07f,-0.07f, // triangle 1 : begin
        -3.0f-0.07f,-0.07f, 0.07f,
        -3.0f-0.07f, 5.0f, 0.07f, // triangle 1 : end

        -3.0f+0.07f, 5.0f,-0.07f, // triangle 2 : begin
        -3.0f-0.07f,-0.07f,-0.07f,
        -3.0f-0.07f, 5.0f,-0.07f, // triangle 2 : end

        -3.0f+0.07f,-0.07f, 0.07f,
        -3.0f-0.07f,-0.07f,-0.07f,
        -3.0f+0.07f,-0.07f,-0.07f,

        -3.0f+0.07f, 5.0f,-0.07f,
        -3.0f+0.07f,-0.07f,-0.07f,
        -3.0f-0.07f,-0.07f,-0.07f,

        -3.0f-0.07f,-0.07f,-0.07f,
        -3.0f-0.07f, 5.0f, 0.07f,
        -3.0f-0.07f, 5.0f,-0.07f,

        -3.0f+0.07f,-0.07f, 0.07f,
        -3.0f-0.07f,-0.07f, 0.07f,
        -3.0f-0.07f,-0.07f,-0.07f,

        -3.0f-0.07f, 5.0f, 0.07f,
        -3.0f-0.07f,-0.07f, 0.07f,
        -3.0f+0.07f,-0.07f, 0.07f,

        -3.0f+0.07f, 5.0f, 0.07f,
        -3.0f+0.07f,-0.07f,-0.07f,
        -3.0f+0.07f, 5.0f,-0.07f,

        -3.0f+0.07f,-0.07f,-0.07f,
        -3.0f+0.07f, 5.0f, 0.07f,
        -3.0f+0.07f,-0.07f, 0.07f,

        -3.0f+0.07f, 5.0f, 0.07f,
        -3.0f+0.07f, 5.0f,-0.07f,
        -3.0f-0.07f, 0.07f,-0.07f,

        -3.0f+0.07f, 5.0f, 0.07f,
        -3.0f-0.07f, 5.0f,-0.07f,
        -3.0f-0.07f, 5.0f, 0.07f,

        -3.0f+0.07f, 5.0f, 0.07f,
        -3.0f-0.07f, 5.0f, 0.07f,
        -3.0f+0.07f,-0.07f, 0.07f
    };
    

    static const GLfloat vertex_buffer_data4[] = {


        -4.5,2,0,
        -3,1.4,1,
        -3,1.4,-1,

        4.5,2,0,
        3,1.4,1,
        3,1.4,-1

    }    ;
    this->drawFlag();
    this->object = create3DObject(GL_TRIANGLES, 23*3, vertex_buffer_data, COLOR_BOAT1, GL_FILL);
    this->object1 = create3DObject(GL_TRIANGLES, 7*3, vertex_buffer_data1, COLOR_BROWN, GL_FILL);
    this->object2 = create3DObject(GL_TRIANGLES, 12*3, vertex_buffer_data2, COLOR_GREEN, GL_FILL);
    this->object4 = create3DObject(GL_TRIANGLES, 2*3, vertex_buffer_data4, COLOR_BLACK, GL_FILL);

}

void Boat::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 1, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.85, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
     draw3DObject(this->object1);
     draw3DObject(this->object2);
     draw3DObject(this->object3);
     draw3DObject(this->object4);
}

void Boat::set_position(float x, float y,float z) {
    this->position = glm::vec3(x, y, z);
}
bounding_box_t Boat::bounding_box() {
    float x = this->position.x, z = this->position.z;
    float y = this->position.y;
    bounding_box_t bbox = { x,y, z, this->width,this->length,1000000};
    return bbox;
}
void Boat::drawFlag()
{
    GLfloat vertex_buffer_data3[] = {
        

        -2.5,1.4,0,
        -2.5,5.0,0,
        3,2,this->flagz

    };
    //std::cout<<this->flagz<<"\n";
    this->object3 = create3DObject(GL_TRIANGLES, 3, vertex_buffer_data3, COLOR_WHITE, GL_FILL);
}

void Boat::Jump(float t){
    float gravity = -0.4f;
    this->speedy += gravity*t;
    this->position.y += this->speedy*t;
}
void Boat::tick1(){
    if(!this->jumping)
    {
        if(this->position.y>1||this->position.y<0)
            this->speedw = -this->speedw;

        this->position.y += this->speedw;
    }
}

void Boat::tick() {

    this->position.y -= 0.1;
}

#include "ball.h"
#include "main.h"

Ball::Ball(float x, float y, float z,float speedx,float speedy,float speedz,float size) {
    this->position = glm::vec3(x, y, z);
    this->rotation = 0;
    this->rotation1 = 0;
    this->speedx = speedx;
    this->speedy = speedy;
    this->speedz = speedz;
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    
    
    float a = size;
    //std::cout << a<<std::endl;
    static const GLfloat vertex_buffer_data1[] = {
        -0.3f, -0.3f, -0.3f, // tri0.3fngle 1 : begin
        -0.3f, -0.3f, 0.3f,
        -0.3f, 0.3f, 0.3f, // tri0.3fngle 1 : end
        0.3f, 0.3f, -0.3f, // tri0.3fngle 2 : begin
        -0.3f, -0.3f, -0.3f,
        -0.3f, 0.3f, -0.3f, // tri0.3fngle 2 : end
        0.3f, -0.3f, 0.3f,
        -0.3f, -0.3f, -0.3f,
        0.3f, -0.3f, -0.3f,
        0.3f, 0.3f, -0.3f,
        0.3f, -0.3f, -0.3f,
        -0.3f, -0.3f, -0.3f,
        -0.3f, -0.3f, -0.3f,
        -0.3f, 0.3f, 0.3f,
        -0.3f, 0.3f, -0.3f,
        0.3f, -0.3f, 0.3f,
        -0.3f, -0.3f, 0.3f,
        -0.3f, -0.3f, -0.3f,
        -0.3f, 0.3f, 0.3f,
        -0.3f, -0.3f, 0.3f,
        0.3f, -0.3f, 0.3f,
        0.3f, 0.3f, 0.3f,
        0.3f, -0.3f, -0.3f,
        0.3f, 0.3f, -0.3f,
        0.3f, -0.3f, -0.3f,
        0.3f, 0.3f, 0.3f,
        0.3f, -0.3f, 0.3f,
        0.3f, 0.3f, 0.3f,
        0.3f, 0.3f, -0.3f,
        -0.3f, 0.3f, -0.3f,
        0.3f, 0.3f, 0.3f,
        -0.3f, 0.3f, -0.3f,
        -0.3f, 0.3f, 0.3f,
        0.3f, 0.3f, 0.3f,
        -0.3f, 0.3f, 0.3f,
        0.3f, -0.3f, 0.3f};
    static const GLfloat vertex_buffer_data2[] = {
        -0.05f, -0.05f, -0.05f, // tri0.05fngle 1 : begin
        -0.05f, -0.05f, 0.05f,
        -0.05f, 0.05f, 0.05f, // tri0.05fngle 1 : end
        0.05f, 0.05f, -0.05f, // tri0.05fngle 2 : begin
        -0.05f, -0.05f, -0.05f,
        -0.05f, 0.05f, -0.05f, // tri0.05fngle 2 : end
        0.05f, -0.05f, 0.05f,
        -0.05f, -0.05f, -0.05f,
        0.05f, -0.05f, -0.05f,
        0.05f, 0.05f, -0.05f,
        0.05f, -0.05f, -0.05f,
        -0.05f, -0.05f, -0.05f,
        -0.05f, -0.05f, -0.05f,
        -0.05f, 0.05f, 0.05f,
        -0.05f, 0.05f, -0.05f,
        0.05f, -0.05f, 0.05f,
        -0.05f, -0.05f, 0.05f,
        -0.05f, -0.05f, -0.05f,
        -0.05f, 0.05f, 0.05f,
        -0.05f, -0.05f, 0.05f,
        0.05f, -0.05f, 0.05f,
        0.05f, 0.05f, 0.05f,
        0.05f, -0.05f, -0.05f,
        0.05f, 0.05f, -0.05f,
        0.05f, -0.05f, -0.05f,
        0.05f, 0.05f, 0.05f,
        0.05f, -0.05f, 0.05f,
        0.05f, 0.05f, 0.05f,
        0.05f, 0.05f, -0.05f,
        -0.05f, 0.05f, -0.05f,
        0.05f, 0.05f, 0.05f,
        -0.05f, 0.05f, -0.05f,
        -0.05f, 0.05f, 0.05f,
        0.05f, 0.05f, 0.05f,
        -0.05f, 0.05f, 0.05f,
        0.05f, -0.05f, 0.05f};
    static const GLfloat vertex_buffer_data3[] = {
        -0.15f, -0.15f, -0.15f, // tri0.15fngle 1 : begin
        -0.15f, -0.15f, 0.15f,
        -0.15f, 0.15f, 0.15f, // tri0.15fngle 1 : end
        0.15f, 0.15f, -0.15f, // tri0.15fngle 2 : begin
        -0.15f, -0.15f, -0.15f,
        -0.15f, 0.15f, -0.15f, // tri0.15fngle 2 : end
        0.15f, -0.15f, 0.15f,
        -0.15f, -0.15f, -0.15f,
        0.15f, -0.15f, -0.15f,
        0.15f, 0.15f, -0.15f,
        0.15f, -0.15f, -0.15f,
        -0.15f, -0.15f, -0.15f,
        -0.15f, -0.15f, -0.15f,
        -0.15f, 0.15f, 0.15f,
        -0.15f, 0.15f, -0.15f,
        0.15f, -0.15f, 0.15f,
        -0.15f, -0.15f, 0.15f,
        -0.15f, -0.15f, -0.15f,
        -0.15f, 0.15f, 0.15f,
        -0.15f, -0.15f, 0.15f,
        0.15f, -0.15f, 0.15f,
        0.15f, 0.15f, 0.15f,
        0.15f, -0.15f, -0.15f,
        0.15f, 0.15f, -0.15f,
        0.15f, -0.15f, -0.15f,
        0.15f, 0.15f, 0.15f,
        0.15f, -0.15f, 0.15f,
        0.15f, 0.15f, 0.15f,
        0.15f, 0.15f, -0.15f,
        -0.15f, 0.15f, -0.15f,
        0.15f, 0.15f, 0.15f,
        -0.15f, 0.15f, -0.15f,
        -0.15f, 0.15f, 0.15f,
        0.15f, 0.15f, 0.15f,
        -0.15f, 0.15f, 0.15f,
        0.15f, -0.15f, 0.15f};

    if (size > 0.3 && size<0.4)
        this->object = create3DObject(GL_TRIANGLES, 12 * 3, vertex_buffer_data1, COLOR_BROWN, GL_FILL);
    else if (size <0.1)

        this->object = create3DObject(GL_TRIANGLES, 12 * 3, vertex_buffer_data2, COLOR_BLUE, GL_FILL);
    else if (size >0.1 && size<=0.3)
        this->object = create3DObject(GL_TRIANGLES, 12 * 3, vertex_buffer_data3, COLOR_BLACK, GL_FILL);
}

void Ball::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 1, 0));
    glm::mat4 rotate1    = glm::rotate((float) (this->rotation2 * M_PI / 180.0f), glm::vec3(1, 1, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate*rotate1);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Ball::set_position(float x, float y,float z) {
    this->position = glm::vec3(x, y, z);
}
bounding_box_t Ball::bounding_box() {
    float x = this->position.x,z = this->position.z;
    bounding_box_t bbox = { x,this->position.y, z, this->size,this->size,this->size};
    return bbox;
}

void Ball::tick() {
    float gravity=this->gravity;
    this->rotation2 += 20;

    this->position.x -= this->speedx;
    this->position.z += this->speedz;
    this->position.y += this->speedy; 

    this->speedy -= gravity;
}
void Ball::tick1()
{
    float gravity = 0.45;
    this->rotation2 += 20;

    this->position.x -= this->speedx;
    this->position.z += this->speedz;
    this->position.y += this->speedy;

    this->speedy -= gravity;
}

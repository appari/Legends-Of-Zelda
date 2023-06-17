#include "monster.h"
#include "main.h"

Monster::Monster(float x, float y, float z,color_t color) {
    this->position = glm::vec3(x, y, z);
    this->rotation = 0;
    this->rotation1 = 0;
    
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    float a= this->side;
    
    static const GLfloat vertex_buffer_data[] = {
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

    GLfloat g_vertex_buffer_data1[4000];
    float PI = 3.14159265;
    float r = this->rad;
    int top = 0;
    float height = this->height;
    // float z = 0;
    float degree = 0;
    while(degree <= 360.0f)
    {
        g_vertex_buffer_data1[top++] = -0.5+r*cos(degree*PI/180.0);
        g_vertex_buffer_data1[top++] = 0;
        g_vertex_buffer_data1[top++] = r*sin(degree*PI/180.0);

        g_vertex_buffer_data1[top++] = -0.5+r*cos(degree*PI/180.0);
        g_vertex_buffer_data1[top++] = -height;
        g_vertex_buffer_data1[top++] = r*sin(degree*PI/180.0);
        degree += 1;

        degree += 1;

    }



    GLfloat g_vertex_buffer_data2[4000];
    
    top = 0;
    degree = 0;
    while(degree <= 360.0f)
    {
        g_vertex_buffer_data2[top++] = 0.8+r*cos(degree*PI/180.0);
        g_vertex_buffer_data2[top++] = 0;
        g_vertex_buffer_data2[top++] = 0.8+r*sin(degree*PI/180.0);

        g_vertex_buffer_data2[top++] = 0.8+r*cos(degree*PI/180.0);
        g_vertex_buffer_data2[top++] = -height;
        g_vertex_buffer_data2[top++] = 0.8+r*sin(degree*PI/180.0);
        degree += 1;

    }
    GLfloat g_vertex_buffer_data3[4000];
    top = 0;
    degree = 0;
    while(degree <= 360.0f)
    {
        g_vertex_buffer_data3[top++] = 0.8+r*cos(degree*PI/180.0);
        g_vertex_buffer_data3[top++] = 0;
        g_vertex_buffer_data3[top++] = -0.8+r*sin(degree*PI/180.0);

        g_vertex_buffer_data3[top++] = 0.8+r*cos(degree*PI/180.0);
        g_vertex_buffer_data3[top++] = -height;
        g_vertex_buffer_data3[top++] = -0.8+r*sin(degree*PI/180.0);
        degree += 1;

    }

    GLfloat g_vertex_buffer_data4[4000];
    top = 0;
    degree = 0;
    while(degree <= 180.0f)
    {
        g_vertex_buffer_data4[top++] = a;
        g_vertex_buffer_data4[top++] = r*sin(degree*PI/180.0);
        g_vertex_buffer_data4[top++] = a/2+r*cos(degree*PI/180.0);

        g_vertex_buffer_data4[top++] = a;
        g_vertex_buffer_data4[top++] = -r*sin(degree*PI/180.0);
        g_vertex_buffer_data4[top++] = -a/2+r*cos(degree*PI/180.0);


       
      
        degree += 1;

    }
    color_t color1[4] = {COLOR_ENEMY1, COLOR_FIRE,COLOR_BLACK};
    
    color_t c1 = color1[rand()%3];
    this->object = create3DObject(GL_TRIANGLES, 12*3, vertex_buffer_data, color1[rand()%3], GL_FILL);
    this->object1= create3DObject(GL_LINES, top/3, g_vertex_buffer_data1, c1, GL_FILL);
    this->object2= create3DObject(GL_LINES, top/3, g_vertex_buffer_data2, c1, GL_FILL);
    this->object3 = create3DObject(GL_LINES, top/3, g_vertex_buffer_data3, c1, GL_FILL);
    this->object4 = create3DObject(GL_LINES, top/3, g_vertex_buffer_data4, color1[rand()%3], GL_FILL);
    //this->object4 = create3DObject(GL_LINES, top/3, g_vertex_buffer_data4, COLOR_WHITE, GL_FILL);
}

void Monster::draw(glm::mat4 VP) {
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
    draw3DObject(this->object1);
    draw3DObject(this->object2);
    draw3DObject(this->object3);
    draw3DObject(this->object4);


}

void Monster::set_position(float x, float y,float z) {
    this->position = glm::vec3(x, y, z);
}

bounding_box_t Monster::bounding_box() {
    float x = this->position.x,z = this->position.z;
    bounding_box_t bbox = { x,this->position.y, z, this->side,this->side,this->side+this->height};
    return bbox;
}
void Monster::tick1(float x,float z) {
    if(this->position.x>x)
        this->position.x -= this->speed;
    else
        this->position.x += this->speed;
    if(this->position.z>z)
        this->position.z -= this->speed;
    else
        this->position.z += this->speed;
    

}

void Monster::tick() {
    this->position.x -= this->speed*cos(this->rotation*M_PI/180.0f);
    this->position.z += this->speed*sin(this->rotation*M_PI/180.0f);
    if(this->position.y>10 || this->position.y<0)
        this->speedy = -this->speedy;
        this->position.y += this->speedy;
}

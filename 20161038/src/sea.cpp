#include "sea.h"
#include "main.h"

Sea::Sea(float x, float y, color_t color,int area) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    speed = 1;
    // static const GLfloat vertex_buffer_data[] =  { 
    //     -1000.0f,5.9f,-1000.0f, // triangle 1 : begin
    //     -1000.0f,5.9f, 1000.0f,
    //     -1000.0f, 6.0f, 1000.0f, // triangle 1 : end

    //     1000.0f, 6.0f,-1000.0f, // triangle 2 : begin
    //     -1000.0f,5.0f,-1000.0f,
    //     -1000.0f, 6.0f,-1000.0f, // triangle 2 : end

    //     1000.0f,5.9f, 1000.0f,
    //     -1000.0f,5.9f,-1000.0f,
    //     1000.0f,5.9f,-1000.0f,

    //     1000.0f, 6.0f,-1000.0f,
    //     1000.0f,5.9f,-1000.0f,
    //     -1000.0f,5.9f,-1000.0f,

    //     -1000.0f,5.9f,-1000.0f,
    //     -1000.0f, 6.0f, 1000.0f,
    //     -1000.0f, 6.0f,-1000.0f,

    //     1000.0f,5.9f, 1000.0f,
    //     -1000.0f,5.9f, 1000.0f,
    //     -1000.0f,5.9f,-1000.0f,

    //     -1000.0f, 6.0f, 1000.0f,
    //     -1000.0f,5.9f, 1000.0f,
    //     1000.0f,5.9f, 1000.0f,

    //     1000.0f, 6.0f, 1000.0f,
    //     1000.0f,5.9f,-1000.0f,
    //     1000.0f, 6.0f,-1000.0f,

    //     1000.0f,5.9f,-1000.0f,
    //     1000.0f, 6.0f, 1000.0f,
    //     1000.0f,5.9f, 1000.0f,

    //     1000.0f, 6.0f, 1000.0f,
    //     1000.0f, 6.0f,-1000.0f,
    //     -1000.0f, 6.0f,-1000.0f,

    //     1000.0f, 6.0f, 1000.0f,
    //     -1000.0f, 6.0f,-1000.0f,
    //     -1000.0f, 6.0f, 1000.0f,

    //     1000.0f, 6.0f, 1000.0f,
    //     -1000.0f, 6.0f, 1000.0f,
    //     1000.0f,5.9f, 1000.0f
    // };

    int N=area;
    int count1 =0 ;
    int count =0 ;
    this->triCnt=0;
    this->triCnt=0;
    GLfloat vertex_buffer_data[100000];
    GLfloat vertex_buffer_data1[100000];
    for (int i=-N;i<N;i+=20)
    
        for (int j=-N;j<N;j+=20)
        {
            //1
            vertex_buffer_data[count] = i; 
            vertex_buffer_data[count+1] = 0;
            vertex_buffer_data[count+2] = j; 
            
            vertex_buffer_data[count+3] = i+20; 
            vertex_buffer_data[count+4] = 0;
            vertex_buffer_data[count+5] = j ;

            vertex_buffer_data[count+6] = i+20; 
            vertex_buffer_data[count+7] = 0;
            vertex_buffer_data[count+8] = j+20;
            
            this->triCnt +=1;
            count += 9;
            //2
            vertex_buffer_data1[count1] = i+20;
            vertex_buffer_data1[count1+1] = 0;
            vertex_buffer_data1[count1+2] = j+20; 

            vertex_buffer_data1[count1+3] = i ;
            vertex_buffer_data1[count1+4] = 0;
            vertex_buffer_data1[count1+5] = j+20; 

            vertex_buffer_data1[count1+6] = i ;
            vertex_buffer_data1[count1+7] = 0;
            vertex_buffer_data1[count1+8] = j ;
            count1 += 9;
            this->triCnt1 +=1;
        }
    this->object = create3DObject(GL_TRIANGLES, this->triCnt*3, vertex_buffer_data, COLOR_WATER, GL_FILL);
    this->object1 = create3DObject(GL_TRIANGLES, this->triCnt1*3, vertex_buffer_data1, COLOR_WATER1, GL_FILL);

}

void Sea::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(1, 1, 0));
    
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
    draw3DObject(this->object1);
}

void Sea::set_position(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
}

void Sea::tick() {
    this->rotation += 0.1;
    //this->position.z += speed;
    // this->position.x -= speed;
    // this->position.y -= speed;
}

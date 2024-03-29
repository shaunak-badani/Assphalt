#include "obstacles.h"
#include "main.h"
#include "functions.h"
#include <bits/stdc++.h>
;
using namespace std;

Obstacles::Obstacles(float x, float y, float z, float radius) {
    this->position = glm::vec3(x, y, z);
    this->rotation = 0;
    speed = 0;

    // vector<GLfloat> obstacle = makePrism(0, 0, 0, 4.0f, 3.0f, 5.0f);
    vector<GLfloat> obstacle = makeObstacle(radius, 5.0f);
    GLfloat *vertex_buffer_data = vecToArray(obstacle);
    
    // vector<GLfloat> colorPrism = color_prism();
    vector<GLfloat> colorPrism = giveColor();
    GLfloat *color_buffer_data = vecToArray(colorPrism);

    this->object = create3DObject(GL_TRIANGLES, obstacle.size() / 3, vertex_buffer_data, COLOR_GREEN, GL_FILL);
}

void Obstacles::draw(glm::mat4 VP) {
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

void Obstacles::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Obstacles::tick() {
    // this->rotation += speed;
    // this->position.x -= speed;
    // this->position.y -= speed;
}


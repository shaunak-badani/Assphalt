#include "plane.h"
#include "main.h"
#include "functions.h"
#include "config.h"

#include <bits/stdc++.h>

using namespace std;

Plane::Plane(float x, float y, color_t color) {
    this->position = glm::vec3(x, y, 0);
    this->rotationX = 0;
    this->rotationY = 0;
    this->rotationZ = 0;
    this->local_axis = glm::mat4(1.0f);
    this->speedZ = 0;
    vector<GLfloat> v = planeConstruct();
    GLfloat *vertex_buffer_data = vecToArray(v);
    GLfloat *color_buffer_data = color_array();

    this->object = create3DObject(GL_TRIANGLES, v.size() / 3, vertex_buffer_data, color_buffer_data, GL_FILL);
}  

void Plane::pitch(float rot){ 
    this->local_axis *= glm::rotate((float) (rot * M_PI / 180 ), glm::vec3(1, 0, 0));
}

void Plane::roll(float rot){ 
    this->local_axis *= glm::rotate((float) (rot * M_PI / 180 ), glm::vec3(0, 1, 0));
}

void Plane::yaw(float rot){ 
    this->rotationZ += rot;
    this->local_axis *= glm::rotate((float) (rot * M_PI / 180 ), glm::vec3(0, 0, 1));
}

void Plane::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= ( translate * local_axis );
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

float Plane::getCenterX() {
    return this->position.x;
}


float Plane::getCenterY() {
    return this->position.y;
}

float Plane::getCenterZ() {
    return this->position.z  + 1.23f;
}

void Plane::speedUp(float increment) {
    this->speedZ += increment;
}

void Plane::rotateY(bool right) {
    right ? this->rotation -= 0.1 : this->rotation += 0.1;
}

void Plane::tick() {
    this->position.x += this->speedZ * (local_axis[2].x);
    this->position.y += this->speedZ * (local_axis[2].y);
    this->position.z += this->speedZ * (local_axis[2].z);
    if(view == GLFW_KEY_F) {
        followCam();
    }
    if(view == GLFW_KEY_P) {
        planeView();
    }
}

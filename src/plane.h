#include "main.h"
#include "ball.h"
#include <string.h>
#include "functions.h"

#ifndef PLANE_H
#define PLANE_H
;
class Plane : public Ball {
    public : 
    float rotationX, rotationY, rotationZ;
    //rotationX defines rotation about X axis.
    
    //constructors
    Plane() {}
    Plane(float x, float y, color_t color);
    
    float speedZ;
    glm::mat4 local_axis;

    //functions
    void speedUp(float increment);
    void tick(); 
    // yaw -> about z axis
    // roll -> about y-axis
    // pitch -> about x-axis
    void yaw(float rotation); 
    void pitch(float rotation); 
    void roll(float rotation);
    float getCenterX();
    float getCenterY();
    float getCenterZ();
    void draw(glm::mat4 VP);
    
    void translateZ();
    void rotateY(bool right);
};

#endif
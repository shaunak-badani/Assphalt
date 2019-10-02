#include "main.h"

#ifndef OBSTACLES_H
#define OBSTACLES_H
;

class Obstacles {
public:
    Obstacles() {}
    Obstacles(float x, float y, float z, float radius);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
    double speed;
    VAO *object;
};

#endif // BALL_H

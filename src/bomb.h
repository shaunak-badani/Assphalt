#include "main.h"

#ifndef BOMB_H
#define BOMB_H
;

class Bomb{
public:
    Bomb() {};
    Bomb(float x, float y, float z);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
    double speedX, speedY, speedZ;
    VAO *object;
};

class Missile {
    public:
    Missile() {};
    Missile(float x, float y, float z, glm::mat4 local_axis);
    glm::vec3 position;
    float rotation;
    glm::mat4 local_axis;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
    double speedX, speedY, speedZ;
    VAO *object;
};

class Score {
    public:
    Score() {};
    Score(float x, float y, float z, float breadth, float height, color_t color);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick(float y_h);
    VAO *object;
};

//Seven segment display

class SevenSegment {
    public:
    SevenSegment(){};
    SevenSegment(float x, float y, float z, int number1, color_t color);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick(float y_h);
    VAO *object;
};

//Fuel bar

class Fuel {
    public:
    Fuel(){};
    Fuel(float x, float y, float z, float width, color_t color);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick(float y_h);
    VAO *object;
};

class Volcano {
    public:
    Volcano(){};
    Volcano(float x, float y, float z);
    glm::vec3 position;
    float rotation; 
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick(float y_h);
    VAO *object;
};

// Cannon

class Cannon {
    public:
    Cannon(){};
    Cannon(float x, float y, float z, float s_x, float s_y, float s_z);
    glm::vec3 position;
    float rotation; 
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
    float speedX, speedY, speedZ;
    VAO *object;
};

// Cannons

class Cannons {
    public:
    Cannons(){};
    Cannons(float x, float y, float z);
    std::vector<Cannon> can;
    bool st;
    glm::vec3 position;
    glm::mat4 l_axis;
    float rotation; 
    void shoot();
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
    VAO *object;
};

//Radar

class Radar {
public:
    Radar() {}
    Radar(float x, float y);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
    double speed;
    VAO *object;
};

//Health

class Health {
public:
    Health() {}
    Health(float x, float y);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
    double speed;
    VAO *object;
};

//Radar

class BombShow {
public:
    BombShow() {}
    BombShow(float x, float y);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
    double speed;
    VAO *object;
};

//Smoke rings

class Rings {
public:
    Rings() {}
    Rings(float x, float y, float z);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
    double speed;
    VAO *object;
};

// Parachute

class Parachoot {
public:
    Parachoot() {}
    Parachoot(float x, float y, float z);
    glm::vec3 position;
    float rotation, speedY;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
    double speed;
    VAO *object;
};


class Arrow {
public:
    Arrow() {}
    Arrow(float x, float y, float z);
    glm::vec3 position;
    float rotation, speedY;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
    double speed;
    VAO *object;
};





#endif // BOMB_H

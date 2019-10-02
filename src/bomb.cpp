#include "bomb.h"
#include "functions.h"
#include "main.h"
#include "config.h"
;


Bomb::Bomb(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
    this->rotation = 0;
    speedX = 0.0f;
    speedY = -0.7f;
    speedZ = 0.0f;
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    std::vector<GLfloat> b1 = makeSphere(2.0f);
    GLfloat *vertex_buffer_data = vecToArray(b1);

    std::vector<GLfloat> col = addColor(b1.size() / 2, COLOR_BROWN1);
    std::vector<GLfloat> col2 = addColor(b1.size() / 2, COLOR_BROWN2);
    col.insert(col.end(), col2.begin(), col2.end());
    GLfloat *color_buffer_data = vecToArray(col);

    this->object = create3DObject(GL_TRIANGLES, b1.size() / 3, vertex_buffer_data, color_buffer_data, GL_FILL);
}

void Bomb::draw(glm::mat4 VP) {
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

void Bomb::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Bomb::tick() {
    this->position.x += this->speedX;
    this->position.y += this->speedY;
    this->position.z += this->speedZ;
    // this->rotation += speed;
    // this->position.x -= speed;
    // this->position.y -= speed;
}


// Missile constructor

Missile::Missile(float x, float y, float z, glm::mat4 local_axis) {
    this->position = glm::vec3(x, y, z);
    this->rotation = 0;
    speedX = -0.3 * glm::normalize(local_axis[2]).x;
    speedY = 0.3 * glm::normalize(local_axis[2]).y;
    speedZ = -0.3 * glm::normalize(local_axis[2]).z;
    this->local_axis = local_axis;   
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    std::vector<GLfloat> b =  makeFrustrum(0.0f, 2.0f, 0.5f, 0.5f);
    std::vector<GLfloat> b2 = makeFrustrum(0, -1.0f, 0.5f, 0.0f);
    b.insert(b.end(), b2.begin(), b2.end());
    GLfloat *vertex_buffer_data = vecToArray(b);

    this->object = create3DObject(GL_TRIANGLES, b.size() / 3, vertex_buffer_data, COLOR_RED, GL_FILL);
}

void Missile::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 1, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * local_axis);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Missile::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Missile::tick() {
    this->position.x += this->speedX;
    this->position.y += this->speedY;
    this->position.z += this->speedZ;
    // this->rotation += speed;
    // this->position.x -= speed;
    // this->position.y -= speed;
}

// Score Display 

Score::Score(float x, float y, float z, float breadth, float height, color_t color) {
    this->position = glm::vec3(x, y, z);
    this->rotation = 0;
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    GLfloat vertex_buffer_data[] = {
        height/2, breadth / 2, 0.0f,
        -height/2, breadth / 2, 0.0f,
        -height/2, -breadth / 2, 0.0f,
        -height/2, -breadth / 2, 0.0f,
        height/2, -breadth / 2, 0.0f,
        height/2, breadth / 2, 0.0f
    };
    this->object = create3DObject(GL_TRIANGLES, 6, vertex_buffer_data, color, GL_FILL);
}

void Score::draw(glm::mat4 VP) {
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

void Score::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Score::tick(float y_h) {
    this->position.y = y_h;
    // this->rotation += speed;
    // this->position.x -= speed;
    // this->position.y -= speed;
}

// Seven Segment Display 

SevenSegment::SevenSegment(float x, float y, float z, int num1, color_t color) {
    this->position = glm::vec3(x, y, z);
    this->rotation = 0;
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    float height = 1, breadth = 1;
    std::vector<GLfloat> b = makeNumber(num1);
    GLfloat *vertex_buffer_data = vecToArray(b);
    this->object = create3DObject(GL_LINES, b.size() / 3, vertex_buffer_data, color, GL_FILL);
}

void SevenSegment::draw(glm::mat4 VP) {
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

void SevenSegment::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void SevenSegment::tick(float y_h) {
    this->position.y = y_h;
    // this->rotation += speed;
    // this->position.x -= speed;
    // this->position.y -= speed;
}

// Fuel bar 

Fuel::Fuel(float x, float y, float z, float width, color_t color) {
    this->position = glm::vec3(x, y, z);
    this->rotation = 0;
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    float length = width, breadth = 0.5f;
    GLfloat vertex_buffer_data[] = {
        length , breadth, 0.0f,
        0, breadth , 0.0f,
        0, 0, 0.0f,
        0, 0, 0.0f, 
        length, 0, 0.0f, 
        length , breadth, 0.0f
    };

    this->object = create3DObject(GL_TRIANGLES, 6, vertex_buffer_data, color, GL_FILL);
}

void Fuel::draw(glm::mat4 VP) {
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

void Fuel::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Fuel::tick(float y_h) {
    this->position.y = y_h;
    // this->rotation += speed;
    // this->position.x -= speed;
    // this->position.y -= speed;
}

// Volcano 

Volcano::Volcano(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
    this->rotation = 0;
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    std::vector<GLfloat> b = makeFrustrumXZ(10.0f, 0, 3.5f, 13.5f);
    GLfloat *vertex_buffer_data = vecToArray(b);
    
    std::vector<GLfloat> col = colorVol();
    GLfloat *color_buffer_data = vecToArray(col);
    this->object = create3DObject(GL_TRIANGLES, b.size() / 3, vertex_buffer_data, color_buffer_data, GL_FILL);
}

void Volcano::draw(glm::mat4 VP) {
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

void Volcano::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Volcano::tick(float y_h) {
    this->position.y = y_h;
    // this->rotation += speed;
    // this->position.x -= speed;
    // this->position.y -= speed;
}

// Cannons 

Cannons::Cannons(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
    this->rotation = 0;
    this->l_axis = glm::mat4(1.0f);
    this->st = false;
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    std::vector<GLfloat> b = makeFrustrum(0.0f, 10.0f, 0.6f, 0.6f);
    std::vector<GLfloat> c = makeFrustrum(10.0f, 12.0f, 0.6f, 0.0f);
    b.insert(b.end(), c.begin(), c.end());
    GLfloat *vertex_buffer_data = vecToArray(b);
    
    std::vector<GLfloat> col = addColor(b.size() / 2, COLOR_GROUND);
    std::vector<GLfloat> col2 = addColor(c.size(), COLOR_WALL2);
    col.insert(col.end(), col2.begin(), col2.end());
    GLfloat *color_buffer_data = vecToArray(col);
    
    this->object = create3DObject(GL_TRIANGLES, b.size() / 3, vertex_buffer_data, color_buffer_data, GL_FILL);
}

void Cannons::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 1, 0));
    glm::vec3 ax = glm::vec3(plane.position.x - this->position.x,
        plane.position.y - this->position.y,
        plane.position.z - this->position.z
    );
    ax = glm::normalize(ax);
    this->l_axis[2].x = ax.x;
    this->l_axis[2].y = ax.y;
    this->l_axis[2].z = ax.z;
    glm::vec3 cr = glm::normalize(glm::cross(glm::vec3(this->l_axis[2].x, this->l_axis[2].y, this->l_axis[2].z), glm::vec3(0, 1, 0))); 
    this->l_axis[1].x = cr.x;
    this->l_axis[1].y = cr.y;
    this->l_axis[1].z = cr.z;

    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * this->l_axis);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
    for(auto i = (this->can).begin() ; i != (this->can).end() ; ++i) {
        (*i).draw(VP);
    }
} 

void Cannons::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Cannons::tick() {
    if(gameTick.processTick() && st) {
        this->shoot();
    }
    for(auto i = this->can.begin() ; i != this->can.end() ; i++) {
        (*i).tick();
    }
    // this->rotation += speed;
    // this->position.x -= speed;
    // this->position.y -= speed;
}

void Cannons::shoot() {
    Cannon c1 = Cannon(this->position.x, this->position.y, this->position.z, (float)0.3 * this->l_axis[2].x, (float)0.3 * this->l_axis[2].y, (float)0.3f * this->l_axis[2].z);
    can.push_back(c1);
}

// Spheres 

Cannon::Cannon(float x, float y, float z, float s_x, float s_y, float s_z) {
    this->position = glm::vec3(x, y, z);
    this->rotation = 0;
    this->speedX = s_x;
    this->speedY = s_y;
    this->speedZ = s_z;
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    std::vector<GLfloat> b = makeSphere(0.5f);
    GLfloat *vertex_buffer_data = vecToArray(b);
    
    std::vector<GLfloat> col = addColor(b.size() / 2, COLOR_RED);
    std::vector<GLfloat> col2 = addColor(b.size() / 2, COLOR_BLUE);
    col.insert(col.end(), col2.begin(), col2.end());
    GLfloat *color_buffer_data = vecToArray(col);
    
    this->object = create3DObject(GL_TRIANGLES, b.size() / 3, vertex_buffer_data, color_buffer_data, GL_FILL);
}

void Cannon::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 1, 0));
    glm::mat4 l_axis = glm::mat4(1.0f);
    glm::vec3 ax = glm::vec3(plane.position.x - this->position.x,
        plane.position.y - this->position.y,
        plane.position.z - this->position.z
    );
    ax = glm::normalize(ax);
    l_axis[2].x = ax.x;
    l_axis[2].y = ax.y;
    l_axis[2].z = ax.z;
    glm::vec3 cr = glm::normalize(glm::cross(glm::vec3(l_axis[2].x, l_axis[2].y, l_axis[2].z), glm::vec3(0, 1, 0))); 
    l_axis[1].x = cr.x;
    l_axis[1].y = cr.y;
    l_axis[1].z = cr.z;

    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * l_axis);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Cannon::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Cannon::tick() {
    this->position.x += this->speedX;
    this->position.y += this->speedY;
    this->position.z += this->speedZ;
    // this->rotation += speed;
    // this->position.x -= speed;
    // this->position.y -= speed;
}

// Radar

Radar::Radar(float x, float y) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    speed = 0;
    float width = 0.3f, height = 1.0f;
    std::vector<GLfloat> needle = {
        -width / 2, 0.0f, 0.0f,
        width / 2, 0.0f, 0.0f,
        0.0f, height, 0.0f,
        -width / 2, 0.0f, 0.0f,
        width / 2, 0.0f, 0.0f,
        0.0f, -height, 0.0f,
    };

    // std::vector<GLfloat> col1 = addColor(circ.size(), COLOR_BROWN1);
    std::vector<GLfloat> col2 = addColor(needle.size() / 2, COLOR_WHITE); 
    std::vector<GLfloat> col3 = addColor(needle.size() / 2, COLOR_RED); 

    col2.insert(col2.begin(), col3.begin(), col3.end());
    // col1.insert(col1.begin(), col2.begin(), col2.end());

    // circ.insert(circ.end(), needle.begin(), needle.end());

    GLfloat *vertex_buffer_data = vecToArray(needle);
    GLfloat *color_buffer_data = vecToArray(col2);
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    this->object = create3DObject(GL_TRIANGLES, needle.size() / 3, vertex_buffer_data, color_buffer_data, GL_FILL);
}

void Radar::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 ax = glm::mat4(1.0f);
    glm::vec3 po = glm::normalize(glm::vec3(-plane.local_axis[2].x, 0, plane.local_axis[2].z));
    ax[1].x = po.x;
    ax[1].z = po.z;
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * ax);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Radar::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Radar::tick() {
    // this->rotation += speed;
    // this->position.x -= speed;
    // this->position.y -= speed;
}

// Health

Health::Health(float x, float y) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    speed = 0;
    float width = 0.2f, length = 0.5f;
    std::vector<GLfloat> needle1 = {
        length / 2, width / 2, 0.0f,
        -length / 2, width / 2, 0.0f,
        -length / 2, -width / 2, 0.0f,
        -length / 2, -width / 2, 0.0f,
        length / 2, -width / 2, 0.0f,
        length / 2, width / 2, 0.0f,
    };

    float temp = width;
    width = length;
    length = temp;

    std::vector<GLfloat> needle2 = {
        length / 2, width / 2, 0.0f,
        -length / 2, width / 2, 0.0f,
        -length / 2, -width / 2, 0.0f,
        -length / 2, -width / 2, 0.0f,
        length / 2, -width / 2, 0.0f,
        length / 2, width / 2, 0.0f,
    };

    needle1.insert(needle1.end(), needle2.begin(), needle2.end());

    GLfloat *vertex_buffer_data = vecToArray(needle1);
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    this->object = create3DObject(GL_TRIANGLES, needle1.size() / 3, vertex_buffer_data, COLOR_RED, GL_FILL);
}

void Health::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 1, 0));
    // ax[1].y = plane.local_axis[2].y;
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Health::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Health::tick() {
    // this->rotation += speed;
    // this->position.x -= speed;
    // this->position.y -= speed;
}

// BombShow

BombShow::BombShow(float x, float y) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    speed = 0;
    std::vector<GLfloat> b = makeCircle(0.12f, 0.0f, 0.0f, 0.0f);

    GLfloat *vertex_buffer_data = vecToArray(b);
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    this->object = create3DObject(GL_TRIANGLES, b.size() / 3, vertex_buffer_data, COLOR_BROWN2, GL_FILL);
}

void BombShow::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 1, 0));
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void BombShow::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void BombShow::tick() {
    // this->rotation += speed;
    // this->position.x -= speed;
    // this->position.y -= speed;
}

// Smoke rings

Rings::Rings(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
    this->rotation = 0;
    speed = 0;

    std::vector<GLfloat> b = makeHollowFrustrum(+0.2f, -0.2f, 2.0f, 1.8f);
    GLfloat *vertex_buffer_data = vecToArray(b);
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    this->object = create3DObject(GL_TRIANGLES, b.size() / 3, vertex_buffer_data, COLOR_BROWN2, GL_FILL);
}

void Rings::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 1, 0));
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Rings::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Rings::tick() {
    // this->rotation += speed;
    // this->position.x -= speed;
    // this->position.y -= speed;
}

// Parachute

Parachoot::Parachoot(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
    this->rotation = 0;
    speedY = -0.03f;

    std::vector<GLfloat> b = makeFrustrumXZ(0.0f, 2.0f, 0.0f, 2.0f);
    GLfloat *vertex_buffer_data = vecToArray(b);
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    this->object = create3DObject(GL_TRIANGLES, b.size() / 3, vertex_buffer_data, COLOR_BROWN2, GL_FILL);
}

void Parachoot::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 1, 0));
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Parachoot::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Parachoot::tick() {
    // this->rotation += speed;
    // this->position.x -= speed;
    this->position.y += speedY;
}

// Arrow

Arrow::Arrow(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
    this->rotation = 0;
    speedY = -0.03f;
    float height1 = 50.0f, height2 = 100.0f, width1 = 15.0f, width2 = 10.0f;
    std::vector<GLfloat> b = {
        0.0f, 0.0f, 0.0f,
        -width1 / 2, height1 / 2, 0.0f,
        width1 / 2, height1 / 2, 0.0f,
        -width1 / 2, height1 / 2, 0.0f,
        -width2 / 2, height1 / 2, 0.0f,
        width2 / 2, height1 / 2, 0.0f,
        width2 / 2, height2 / 2, 0.0f,
        width2 / 2, height2 / 2, 0.0f,
        -width2 / 2, height2 /2, 0.0f,
        -width2 / 2, height1 / 2, 0.0f
    };

    GLfloat *vertex_buffer_data = vecToArray(b);
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    this->object = create3DObject(GL_TRIANGLES, b.size() / 3, vertex_buffer_data, COLOR_COINS, GL_FILL);
}

void Arrow::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 1, 0));
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Arrow::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Arrow::tick() {
    // this->rotation += speed;
    // this->position.x -= speed;
    this->position.y += speedY;
}

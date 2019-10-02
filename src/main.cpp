#include "main.h"
#include "timer.h"
#include "ball.h"
#include "plane.h"
#include "functions.h"
#include "config.h"
#include "ground.h"
#include "obstacles.h"
#include "bomb.h"
#include <string.h>

using namespace std;

GLMatrices Matrices;
GLuint     programID;
GLFWwindow *window;
float fuel = 100;
int health = 100;
int score = 0;

int checkpoint = 1;

Timer gameTick = Timer(1.0f);

int no_of_seconds = 180;
int no_of_islands = 14;
int no_of_volcanoes = 5;
int no_of_cannons = 5;
int no_of_bombs = 5;
int no_of_parachoots = 10;
int no_of_rings = 10;

float parachoots_x[10] = {
    -10.0f, 19.0f, 30.0f, 50.0f, -40.0f, 25.0f, 70.0f, -55.0f, 70.0f, -90.0f,
};

float parachoots_z[10] = {
    10.0f, -20.0f, -60.0f, 70.0f, -15.0f, -10.0f, 25.0f, 20.0f, -70.0f, 50.0f
};

float islands_x[14] = {
    -3.0f, -10.0f, -40.0f, -35.0f, 20.0f, -25.0f, 70.0f, -65.0f, 45.0f, -40.0f, 25.0f, 30.0f, -30.0f, 60.0f,
};

float islands_z[14] = {
    -4.0f, 5.0f, 92.0f, 70.0f, 30.0f, -20.0f, -36.0f, -45.0f, -60.0f, -71.0f, 30.0f, 50.0f, 0.0f, 60.0f,
};

float radii[14] = {
    16.0f, 10.0f, 8.0f, 14.0f, 19.0f, 8.0f, 11.0f, 14.0f, 9.0f, 11.0f, 25.0f, 20.0f, 19.0f, 20.0f,
};

float volcanoes_x[5] = {
    -30.0f, -40.0f, 30.0f, -40.0f, 65.0f
};

float volcanoes_z[5] = {
    3.0f, -65.0f, 55.0f, 75.0f, -35.0f
};

float cans_x[5] = {
    3.0f, 65.0f, 40.0f, -35.0f, -69.0f 
};

float cans_z[5] = {
    -4.0f, -50.0f, 30.0f, -20.0f, 60.0f
};

float ring_x[10] = {
    5.0f, -1.0f, 1.0f, 40.0f, -30.0f, 50.0f, -20.0f, -50.0f, 90.0f, -90.0f
};

float ring_z[10] = {
    -50.0f, 50.0f, 40.0f, -40.0f, 30.0f, 25.0f, -25.0f, 30.0f, 5.0f, 5.0f
};


/**************************
* Customizable functions *
**************************/

float camX = 0, camZ = radius;
float camera_rotation_angle = 90.0f;


//All objects associated
Plane plane;
Ground ground;
vector<Obstacles> obs;
vector<Bomb> bom;
vector<Missile> mis;
vector<Volcano> vol;
int view = GLFW_KEY_F;
Score sc1, sc2;
Health cros;
SevenSegment s1, s2, h1, h2, h3;
Fuel fbar;
vector<BombShow> bs;
Radar r1;
vector<Cannons> can;
vector<Rings> ring;
Arrow arrow;
vector<Parachoot> p1;


cam_coords eye_cam = {
    x: 0.0f,
    y: 7.0f,
    z: -2.0f
};

cam_coords target_cam = {
    x: 0.0f,
    y: 0.0f,
    z: -4.0f
};

cam_coords up_cam = {
    x: 0,
    y: 1,
    z: 0
};

void reset_bombs() {
    for( int i = 0 ; i < no_of_bombs ; i++) {
        BombShow b = BombShow(2.0f + i * (0.3f),-3.5f);
        bs.push_back(b);
    }
}

void initializeCheckpoint() {
    switch(checkpoint) {
        case 1:
            (*can.begin()).st = true;
            break;
        case 2: 
            reset_bombs();
            (*can.begin()).st = true;
            (*next(can.begin(),1)).st = true;
            arrow       = Arrow(70.0f, y_offset + 0.1f, -80.0f);
            break;
    }
}

void debugFunction(char *message) {
    cout.write(message, 100);
}

void  initializeObjects() {
    plane       = Plane(0, 0, COLOR_RED);
    ground      = Ground(0, 0, SEA_BLUE);
    sc1         = Score(-3.5f, 0.0f, 0.0f, 6.0f, 0.2f, COLOR_RED);
    sc2         = Score(-3.5f, 0.0f, 0.0f, 0.2f, 0.3f, COLOR_PLAYER);
    s1          = SevenSegment(-4.0f, 4.0f, 0, score / 10, COLOR_BLACK);
    s2          = SevenSegment(-4.0f, 2.0f, 0, score % 10, COLOR_BLACK);
    fbar        = Fuel(-3.5, -3.75, 0, 1, COLOR_COINS);
    r1          = Radar(3.5f, 3.0f);
    h1          = SevenSegment(-0.25f, 3.75f, 0.0f, health / 100 , COLOR_RED);
    h2          = SevenSegment(0.0f, 3.75f, 0.0f, (health / 10) % 10, COLOR_RED);
    h3          = SevenSegment(0.25f, 3.75f, 0.0f, health % 10 , COLOR_RED);
    cros        = Health(-0.75f, 3.5f);
    arrow       = Arrow(-70.0f, y_offset + 0.1f, -80.0f);
    for(int i = 0 ; i < no_of_volcanoes ; i++ ){
        Volcano v         = Volcano(volcanoes_x[i], y_offset + 1, volcanoes_z[i]);
        vol.push_back(v);
    }

    // Initializing islands
    for( int i = 0 ; i < no_of_islands ; i++ ){
        Obstacles ob1         = Obstacles(islands_x[i],  y_offset + 0.1, islands_z[i], radii[i]);
        obs.push_back(ob1);
    }

    for( int i = 0 ; i < no_of_cannons ; i++ ){
        Cannons c1             = Cannons(cans_x[i], y_offset + 0.1f, cans_z[i]);
        can.push_back(c1);
    } 

    for( int i = 0 ; i < no_of_bombs ; i++) {
        BombShow b = BombShow(2.0f + i * (0.3f),-3.5f);
        bs.push_back(b);
    }

    for(int i = 0 ; i < no_of_rings ; i++ ) {
        Rings ri = Rings(ring_x[i], 10.0f, ring_z[i]);
        ring.push_back(ri);
    } 

    for(int i = 0 ; i < no_of_parachoots ; i++) {
        Parachoot p_choot = Parachoot(parachoots_x[i], y_offset + 40.0f, parachoots_z[i]);
        p1.push_back(p_choot);
    }
}


void dropBomb() {
    if(bs.empty()) return;
    Bomb b1 = Bomb(plane.position.x, plane.position.y, plane.position.z);
    bom.push_back(b1);
    bs.erase(bs.begin());
}

void shootMissile() {
    Missile m1 = Missile(plane.position.x , plane.position.y , plane.position.z - 6.0f * glm::normalize(plane.local_axis[2]).z, plane.local_axis);
    mis.push_back(m1);
}

void tick_elements() {
    plane.tick();
    for(auto i = bom.begin() ; i != bom.end() ;) {
        (*i).tick();
        if( (*i).position.y <= y_offset ) {
            bom.erase(i);
        }
        else {
            i++;
        }
    }
    s1          = SevenSegment(-3.75, 3.875, 0, score / 10, COLOR_BLACK);
    s2          = SevenSegment(-3.5, 3.875,0, score % 10, COLOR_BLACK);
    h1          = SevenSegment(-0.25f, 3.75f, 0.0f, health / 100 , COLOR_RED);
    h2          = SevenSegment(0.0f, 3.75f, 0.0f, (health / 10)%10, COLOR_RED);
    h3          = SevenSegment(0.25f, 3.75f, 0.0f, health % 10 , COLOR_RED);
    fbar        = Fuel(-3.5, -3.75, 0, (float)fuel / 25, COLOR_COINS);

    fuel -= 100.0f / (no_of_seconds * 60);
    //Missile loop
    for(auto i = mis.begin() ; i != mis.end() ;) {
        (*i).tick();
        if( (*i).position.y <= y_offset ) {
            mis.erase(i);
        }
        else {
            i++;
        }
    }
    for( auto i = can.begin() ; i != can.end() ; i++ ) {
        (*i).tick();
    }
    rotateCam();
    sc2.tick(plane.position.y / 10);

    bounding_box_t temp1, temp2;
    temp1 = {
        x : plane.position.x,
        y : plane.position.y,
        z : plane.position.z,
        width : 3.0f,
        height : 3.0f,
        breadth : 12.0f
    };
    // enemy missile and plane
    for(auto i = can.begin() ; i != can.end() ; i++ ) {
        if(!(*i).st) continue;
        for(auto j = (*i).can.begin() ; j != (*i).can.end() ; ) {
            temp2.x = (*j).position.x;
            temp2.y = (*j).position.y;
            temp2.z = (*j).position.z;
            temp2.width = 1.0f;
            temp2.breadth = 1.0f;
            temp2.height = 1.0f;
            if(detect_collision(temp1, temp2)) {
                (*i).can.erase(j);
                health -= 5;
                if(health <= 70) {
                    (*i).st = false;
                }
            }
            else {
                j++;
            }
        }
    }
    //plane and checkpoint
    temp2.x = arrow.position.x;
    temp2.y = arrow.position.y;
    temp2.z = arrow.position.z;
    temp2.height = 100.0f;
    temp2.width = 15.0f;
    temp2.breadth = 0.01f;
    if(plane.position.y - 4.0f <= y_offset) quit(window);
    if(detect_collision(temp1, temp2)) {
        checkpoint++;
        if(checkpoint > 2) {
            cout << "Congrats! : Your final score is " << score << endl;
            quit(window);
        }
        else {
            initializeCheckpoint();
        }
    }
    // plane and ring 
    for(auto i = ring.begin() ; i != ring.end() ; ) {
        temp2.x = (*i).position.x;
        temp2.y = (*i).position.y;
        temp2.z = (*i).position.z;
        temp2.height = 4.0f;
        temp2.width = 4.0f;
        temp2.breadth = 0.4f;
        if(detect_collision(temp1, temp2)) {
            score += 6;
            ring.erase(i);
        }
        else {
            i++;
        }
    }
    //bomb and cannon
    bounding_box_t  temp3;
    for(auto i = bom.begin(); i != bom.end() ; i++) {
        temp2.x = (*i).position.x;
        temp2.y = (*i).position.y;
        temp2.z = (*i).position.z;
        temp2.width = 4.0f;
        temp2.height = 4.0f;
        temp2.breadth = 4.0f;
        for(auto j = can.begin() ; j != can.end();) {
            temp3.x = (*j).position.x;
            temp3.y = (*j).position.y;
            temp3.z = (*j).position.z;
            temp3.width = 2.0f;
            temp3.height = 4.0f;
            temp3.breadth = 4.0f;
            if(detect_collision(temp2,temp3) && (*j).st) {
                score += 15;
                can.erase(j);
            }
            else {
                j++;
            }
        }
    }

    // camera_rotation_angle += 1;
}

void draw_all(glm::mat4 VP) {
    ground.draw(VP);
    for(auto i = obs.begin() ; i != obs.end() ; i++) {
        (*i).draw(VP);
    }
    plane.draw(VP);
    for(auto i = bom.begin() ; i != bom.end() ; i++) {
        (*i).draw(VP);
    }

    //Draw missiles 
    for(auto i = mis.begin() ; i != mis.end() ; i++) {
        (*i).draw(VP);
    }
    for(auto i = vol.begin() ; i != vol.end() ; i++) {
        (*i).draw(VP);
    }
    for(auto i = can.begin() ; i != can.end() ; i++) {
        (*i).draw(VP);
    }
    for(auto i = ring.begin() ; i != ring.end() ; i++ ) {
        (*i).draw(VP);
    }
    for(auto i = p1.begin() ; i != p1.end() ; i++) {
        (*i).draw(VP);
    }
    arrow.draw(VP);
}

void draw_scoreboard(glm::mat4 VP) {
    sc1.draw(VP);
    sc2.draw(VP);
    s1.draw(VP);
    s2.draw(VP);
    fbar.draw(VP);
    r1.draw(VP);
    h1.draw(VP);
    h2.draw(VP);
    h3.draw(VP);
    cros.draw(VP);
    for(auto i = bs.begin() ; i != bs.end() ; i++) {
        (*i).draw(VP);
    }
}

float screen_zoom = 1, screen_center_x = 0, screen_center_y = 0;
float x = 0, y = 0, z = 5;

// Camera views 


Timer t60(1.0 / 60);

/* Render the scene with openGL */
/* Edit this function according to your assignment */
void draw() {
    // clear the color and depth in the frame buffer
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // use the loaded shader program
    // Don't change unless you know what you are doing
    glUseProgram (programID);

    // Eye - Location of camera. Don't change unless you are sure!!
    glm::vec3 eye ( eye_cam.x, eye_cam.y, eye_cam.z);
    // Target - Where is the camera looking at.  Don't change unless you are sure!!
    glm::vec3 target ( target_cam.x, target_cam.y, target_cam.z); 
    // Up - Up vector defines tilt of camera.  Don't change unless you are sure!!
    glm::vec3 up ( up_cam.x, up_cam.y, up_cam.z);

    // Compute Camera matrix (view)
    Matrices.view = glm::lookAt( eye, target, up ); 

    glm::vec3 eye_db ( 5*cos(camera_rotation_angle*M_PI/180.0f), 0, 5*sin(camera_rotation_angle*M_PI/180.0f) );

    glm::vec3 target_db ( 0, 0, 0 );

    glm::vec3 up_db ( 0, 1, 0 );

    Matrices.view_db = glm::lookAt( eye_db, target_db, up_db );
    // Don't change unless you are sure!!
    // Matrices.view = glm::lookAt(glm::vec3(0, 0, 3), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0)); // Fixed camera for 2D (ortho) in XY plane

    // Compute ViewProject matrix as view/camera might not be changed for this frame (basic scenario)
    // Don't change unless you are sure!!
    glm::mat4 VP = Matrices.projection * Matrices.view;

    glm::mat4 VP_Dashboard = Matrices.projection_db * Matrices.view_db; 

    // Send our transformation to the currently bound shader, in the "MVP" uniform
    // For each model you render, since the MVP will be different (at least the M part)
    // Don't change unless you are sure!!
    glm::mat4 MVP;  // MVP = Projection * View * Model

    // Scene render
    draw_all(VP);
    draw_scoreboard(VP_Dashboard);
}

void tick_input(GLFWwindow *window) {
    int left  = glfwGetKey(window, GLFW_KEY_LEFT);
    int right = glfwGetKey(window, GLFW_KEY_RIGHT);

    // Keys to handle input
    if(glfwGetKey(window, GLFW_KEY_Q)) plane.yaw(0.3f);
    if(glfwGetKey(window, GLFW_KEY_E)) plane.yaw(-0.3f);
    if(glfwGetKey(window, GLFW_KEY_A)) plane.roll(0.3f);
    if(glfwGetKey(window, GLFW_KEY_D)) plane.roll(-0.3f);
    if(glfwGetKey(window, GLFW_KEY_L)) plane.pitch(0.3f);
    if(glfwGetKey(window, GLFW_KEY_B)) plane.pitch(-0.3f);

    if(glfwGetKey(window, GLFW_KEY_SPACE))plane.position.y += 0.3f;
    if(glfwGetKey(window, GLFW_KEY_DOWN)) plane.position.y -= 0.3f;    
}



/* Initialize the OpenGL rendering properties */
/* Add all the models to be created here */
void initGL(GLFWwindow *window, int width, int height) {
    /* Objects should be created before any other gl function and shaders */
    // Create the models


    // Create and compile our GLSL program from the shaders
    programID = LoadShaders("Sample_GL.vert", "Sample_GL.frag");
    // Get a handle for our "MVP" uniform
    Matrices.MatrixID = glGetUniformLocation(programID, "MVP");


    reshapeWindow (window, width, height);

    // Background color of the scene
    glClearColor (COLOR_BACKGROUND.r / 256.0, COLOR_BACKGROUND.g / 256.0, COLOR_BACKGROUND.b / 256.0, 0.0f); // R, G, B, A
    glClearDepth (1.0f);

    glEnable (GL_DEPTH_TEST);
    glDepthFunc (GL_LEQUAL);

    cout << "VENDOR: " << glGetString(GL_VENDOR) << endl;
    cout << "RENDERER: " << glGetString(GL_RENDERER) << endl;
    cout << "VERSION: " << glGetString(GL_VERSION) << endl;
    cout << "GLSL: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << endl;
}


int main(int argc, char **argv) {
    srand(time(0));
    int width  = 1600;
    int height = 800;

    window = initGLFW(width, height);
    initializeObjects();
    initGL (window, width, height);
    initializeCheckpoint();

    /* Draw in loop */
    while (!glfwWindowShouldClose(window)) {
        // Process timers

        if (t60.processTick()) {
            // 60 fps
            // OpenGL Draw commands
            draw();
            // Swap Frame Buffer in double buffering
            glfwSwapBuffers(window);

            tick_elements();
            tick_input(window);
        }

        // Poll for Keyboard and mouse events
        glfwPollEvents();
    }

    quit(window);
}

bool detect_collision(bounding_box_t a, bounding_box_t b) {
    return (abs(a.x - b.x) * 2 < (a.width + b.width)) &&
           (abs(a.y - b.y) * 2 < (a.height + b.height)) &&
           (abs(a.z - b.z) * 2 < (a.breadth + b.breadth));
}

void reset_screen() {
    float top    = screen_center_y + 4 / screen_zoom;
    float bottom = screen_center_y - 4 / screen_zoom;
    float left   = screen_center_x - 4 / screen_zoom;
    float right  = screen_center_x + 4 / screen_zoom;
    Matrices.projection = glm::perspective(90.0f, 1.0f , 3.0f, 500.f);
    Matrices.projection_db = glm::ortho(left, right, bottom, top, 0.1f, 500.0f);
}

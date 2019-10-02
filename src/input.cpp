#include <iostream>
#include <cmath>
#include <fstream>
#include <vector>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#define GLM_FORCE_RADIANS
#define GLM_ENABLE_EXPERIMENTAL

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "main.h"
#include "functions.h"
#include "config.h"

bool   cannon_keyboard_input = true;
bool   drag_pan = false, old_cki;
double drag_oldx = -1, drag_oldy = -1;

double cursor_x = 50, cursor_y = 50;

bool pressed = false;

using namespace std;

/* Executed when a regular key is pressed/released/held-down */
/* Prefered for Keyboard events */
void keyboard(GLFWwindow *window, int key, int scancode, int action, int mods) {
    // Function is called first on GLFW_PRESS.

    if (action == GLFW_RELEASE) {
        handleInputRelease(key);    
        // switch (key) {
        // case GLFW_KEY_C:
        // rectangle_rot_status = !rectangle_rot_status;
        // break;
        // case GLFW_KEY_P:
        // triangle_rot_status = !triangle_rot_status;
        // break;
        // case GLFW_KEY_X:
        //// do something ..
        // break;
        // default:
        // break;
        // }
    } else if (action == GLFW_PRESS) {
        handleInputPress(key);
        switch (key) {
        case GLFW_KEY_ESCAPE:
            quit(window);
            break; 
        default:
            break;
        }
    }
}

/* Executed for character input (like in text boxes) */
void keyboardChar(GLFWwindow *window, unsigned int key) {
    switch (key) {
    default:
        break;
    }
}

/* Executed when a mouse button is pressed/released */
void mouseButton(GLFWwindow *window, int button, int action, int mods) {
    switch (button) {
    case GLFW_MOUSE_BUTTON_LEFT:
        if (action == GLFW_PRESS) {
            dropBomb();
            pressed = true;
            return;
        } else if (action == GLFW_RELEASE) {
            // Do something
            pressed = false;
        }
        break;
    case GLFW_MOUSE_BUTTON_RIGHT:
    if (action == GLFW_PRESS) {
        // rectangle_rot_dir *= -1;
        shootMissile();
    }
    break;
    default:
        break;
    }
}

void scroll_callback(GLFWwindow *window, double xoffset, double yoffset) {
    // Do something
    if(view == GLFW_KEY_H) {
        if(yoffset == -1) radius += 0.5;
        if(yoffset == 1) radius -= 0.5;
    }
}

// Executed when mouse moves in any direction
void cursor_position_callback(GLFWwindow* window, double xpos, double ypos) {
    if(view == GLFW_KEY_H) {
        cursor_x = xpos;
        cursor_y = ypos;
    }
}


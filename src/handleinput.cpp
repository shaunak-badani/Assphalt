#include "main.h"
#include "config.h"
#include "functions.h"
#include <bits/stdc++.h>

using namespace std;

void handleInputPress(int key) {
    switch(key) {
        //keys to handle views

        case GLFW_KEY_P: cout << "Plane View" << endl;
        planeView();
        view = key;
        break;

        case GLFW_KEY_U: topView();
        view = key;
        break;

        case GLFW_KEY_T: towerView();
        view = key;
        break;

        case GLFW_KEY_F: cout << "Follow View" << endl;
        followCam();
        view = key;
        break;

        case GLFW_KEY_H: cout << "Helicam view" << endl;
        heliCam();
        view = key;
        break;
        
        //keys to handle moving forward
        case GLFW_KEY_W:
            plane.speedUp(-0.5);
        break;

        //backward
        case GLFW_KEY_S:
            plane.speedUp(0.5);
        break;
    }
}

void handleInputRelease(int key) {
    switch(key) {
        case GLFW_KEY_W : 
            plane.speedUp(0.5);
            break;
        case GLFW_KEY_S:
            plane.speedUp(-0.5);
        break;
    }
}
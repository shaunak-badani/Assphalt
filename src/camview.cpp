#include "main.h"
#include "functions.h"
#include "config.h"
#include <bits/stdc++.h>

using namespace std;

float radius = 15, theta = 3.14 / 3, phi = 0;

void planeView() {

    eye_cam.x = plane.getCenterX();
    eye_cam.y = plane.getCenterY();
    eye_cam.z = plane.getCenterZ() - 7.0f;

    target_cam.x = plane.getCenterX() - plane.local_axis[2].x; 
    target_cam.y = plane.getCenterY() + plane.local_axis[2].y;

    target_cam.z = eye_cam.z - 1.0f;


    up_cam.x = plane.local_axis[1].x;
    up_cam.y = plane.local_axis[1].y;
    up_cam.z = plane.local_axis[1].z;
}

void towerView(){
    cout << "Tower view" << endl;
    eye_cam.x = plane.getCenterX() + 10.0f;
    eye_cam.y = plane.getCenterY() + 9.0f;
    eye_cam.z = plane.getCenterZ();


    target_cam.x = plane.getCenterX();                   
    target_cam.y = plane.getCenterY();                   
    target_cam.z = plane.getCenterZ();                   

    up_cam.x = 0.0f;
    up_cam.y = 1.0f;
    up_cam.z = 0.0f;
}

void followCam(){
    eye_cam.x = plane.getCenterX();
    eye_cam.y = plane.getCenterY() +  15.0f;
    eye_cam.z = plane.position.z + 10.0f;


    // cout << "Eye cam : " << plane.local_axis[1].x << " : " << plane.local_axis[1].y << " : " << plane.local_axis[1].z << endl;

    target_cam.x = plane.getCenterX();
    target_cam.y = plane.getCenterY();
    target_cam.z = plane.position.z - 10.0f;

    up_cam.x = 0.0f;
    up_cam.y = 1.0f;
    up_cam.z = 0.0f;
}

void topView(){
    cout << "Top View" << endl;
    eye_cam.x = plane.getCenterX();
    eye_cam.y = plane.getCenterY() + 9.0f;
    eye_cam.z = target_cam.z = plane.position.z;

    up_cam.x = 0.0f;
    up_cam.y = 0.0f;
    up_cam.z = -1.0f;
}

void heliCam() {
    eye_cam.x = plane.getCenterX() + radius * sin(theta) * cos(phi);
    eye_cam.y = plane.getCenterY() + radius * cos(theta) ;
    eye_cam.z = plane.getCenterZ() + radius * sin(theta) * sin(phi);

    target_cam.z = plane.getCenterZ();

    up_cam.x = 0.0f;
    up_cam.y = 1.0f;
    up_cam.z = 0.0f;
}

// Rotates cam if in helicam mode
void rotateCam() {
    if(view != GLFW_KEY_H) return;

    if(cursor_x > 1500) {
        phi -= 0.01;
    }
    if(cursor_x < 50) {
        phi += 0.01;
    }
    if(cursor_y > 700) {
        theta += 0.01;
    }
    if(cursor_y < 50) {
        theta -= 0.01;
    }
    heliCam();
}
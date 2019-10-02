#include "main.h"
#include "plane.h"
#include "timer.h"

#ifndef CONFIG_H
#define CONFIG_H

//Variables

extern cam_coords eye_cam;
extern cam_coords target_cam;
extern cam_coords up_cam;
extern float radius, theta, phi;
extern double cursor_x, cursor_y;
extern float y_offset;
extern Timer gameTick;

extern Plane plane;
extern int view;
extern bool pressed;

#endif
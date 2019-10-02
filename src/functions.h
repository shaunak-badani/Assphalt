#include "main.h"
#include <bits/stdc++.h>

#ifndef PLANE_FUNCTIONS_H
#define PLANE_FUNCTIONS_H


//Functions

void debugFunction(char *str);

// Helper functions that return a float vector to construct objects

std::vector<GLfloat> makeCircle(float r, float x, float y, float z);

std::vector<GLfloat> makeCircleXZ(float r, float x, float y, float z);

std::vector<GLfloat> makePolygon(float centerX, float centerY, float sideLength, int n);

std::vector<GLfloat> groundPolygon(float centerX, float centerY, float z,float sideLength, int n);

std::vector<GLfloat> makeFrustrum(float c_front, float c_back, float r_front, float r_back);

std::vector<GLfloat> makeHollowFrustrum(float c_front, float c_back, float r_front, float r_back);

std::vector<GLfloat> makeFrustrumXZ(float c_front, float c_back, float r1, float r2);

// Functions related to construction of the plane

std::vector<GLfloat> planeConstruct();

GLfloat* color_array();

std::vector<GLfloat> colorVol();

std::vector<GLfloat> addColor(int size, color_t color);


void colorPlane(int n, color_t color);

//Helps in converting vectors to arrays

GLfloat* vecToArray(std::vector<GLfloat> arr);

//Change the camera view

void planeView();

void towerView();

void followCam();

void topView();

void heliCam();

void rotateCam();

// Function to handle input

void handleInputPress(int key);

void handleInputRelease(int key);

// Functions to make obstacles

std::vector<GLfloat> makePrism(float z, float centerX, float centerY, float width, float breadth, float height);

std::vector<GLfloat> color_prism();

std::vector<GLfloat> makeObstacle(int radius, float height);

std::vector<GLfloat> giveColor();

// To make bombs

std::vector<GLfloat> makeSphere(float radius);

// main.cpp

extern void dropBomb();

extern void shootMissile();

// seven segment display

std::vector<GLfloat> makeNumber(int number);

#endif

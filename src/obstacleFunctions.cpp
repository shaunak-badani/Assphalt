#include "main.h"
#include "functions.h"
#include <bits/stdc++.h>
;
using namespace std;
vector <GLfloat> finalColor;

//width => along x-axis
vector<GLfloat> makePrism(float z, float centerX, float centerY, float width, float breadth, float height){

    vector <GLfloat> prism = {
        // base
        centerX + width / 2, centerY, z + breadth / 2,
        centerX + width / 2, centerY, z - breadth / 2,
        centerX - width / 2, centerY, z - breadth / 2,
        centerX - width / 2, centerY, z - breadth / 2,
        centerX - width / 2, centerY, z + breadth / 2,
        centerX + width / 2, centerY, z + breadth / 2,
        // 4 triangles around it
        centerX + width / 2, centerY, z + breadth / 2,
        centerX + width / 2, centerY, z - breadth / 2,
        centerX, centerY + height, z,

        centerX + width / 2, centerY, z - breadth / 2, 
        centerX - width / 2, centerY, z - breadth / 2,
        centerX, centerY + height, z,

        centerX - width / 2, centerY, z - breadth / 2,
        centerX - width / 2, centerY, z + breadth / 2,
        centerX, centerY + height, z,

        centerX - width / 2, centerY, z + breadth / 2,
        centerX + width / 2, centerY, z + breadth / 2,
        centerX, centerY + height, z
    };

    return prism;
}

vector<GLfloat> color_prism() {
    vector<GLfloat> color = {
        //coloring the base white
        1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,

        0.382f, 0.714f, 0.039f,
        0.382f, 0.714f, 0.039f,
        0.382f, 0.714f, 0.039f,

        0.265f, 0.351f, 0.0234f,
        0.265f, 0.351f, 0.0234f,
        0.265f, 0.351f, 0.0234f,

        0.382f, 0.714f, 0.039f,
        0.382f, 0.714f, 0.039f,
        0.382f, 0.714f, 0.039f,

        0.265f, 0.351f, 0.0234f,
        0.265f, 0.351f, 0.0234f,
        0.265f, 0.351f, 0.0234f
    };
    return color;
}

vector<GLfloat> makeObstacle(int radius, float height) {    

    vector<float> b = makeCircleXZ(radius, 0, 0, 0);
    return b;
}

vector<GLfloat> makeSphere(float radius) {
    int n = 100;
    float theta = M_PI / n;
    float dr = 2 * radius / n;
    float centerZ = -radius;

    vector<GLfloat> sphere, temp;

    for(int i = -n/2 ; i < n / 2 ; i++) {
        temp = makeFrustrum(centerZ + dr*i, centerZ + dr * (i+1), radius * cos(i*theta), radius * cos((i+1)*theta));
        sphere.insert(sphere.end(), temp.begin(), temp.end());
    }   
    return sphere;
}

vector<GLfloat> giveColor() {
    return finalColor;
}


vector<GLfloat> makeNumber(int number) {
    vector<GLfloat> b;
    float width = 0.15f, height = 0.3f; 
    switch(number) {
        case 1:
            b = {
                width, 0.0f, 0.0f,
                width, -height, 0.0f, //2
                width, -height, 0.0f,
                width, -height * 2, 0.0f, //5
            };
            break;
        case 2:
            b = {
                0.0f, 0.0f, 0.0f,
                width, 0.0f, 0.0f,// 1
                width, 0.0f, 0.0f,
                width, -height, 0.0f, //2
                width, -height, 0.0f, 
                0, -height, 0.0f, //3
                width, -height * 2, 0.0f,
                0.0f, -height * 2, 0.0f, //6
                0.0f, -height * 2, 0.0f, 
                0.0f, -height , 0.0f,//7
            };
            break;
        case 3:
            b = {
                0.0f, 0.0f, 0.0f,
                width, 0.0f, 0.0f,// 1
                width, 0.0f, 0.0f,
                width, -height, 0.0f, //2
                width, -height, 0.0f, 
                0, -height, 0.0f, //3
                width, -height, 0.0f,
                width, -height * 2, 0.0f, //5
                width, -height * 2, 0.0f,
                0.0f, -height * 2, 0.0f, //6
            };
            break;
        case 4:
            b = {
                width, 0.0f, 0.0f,
                width, -height, 0.0f, //2
                width, -height, 0.0f, 
                0, -height, 0.0f, //3
                0, -height, 0.0f,
                0.0f, 0.0f, 0.0f,//4
                width, -height, 0.0f,
                width, -height * 2, 0.0f, //5
            };
            break;
        case 5:
            b = {
                0.0f, 0.0f, 0.0f,
                width, 0.0f, 0.0f,// 1
                width, -height, 0.0f, 
                0, -height, 0.0f, //3
                0, -height, 0.0f,
                0.0f, 0.0f, 0.0f,//4
                width, -height, 0.0f,
                width, -height * 2, 0.0f, //5
                width, -height * 2, 0.0f,
                0.0f, -height * 2, 0.0f, //6
            };
            break;
        case 6:
            b = {
                0.0f, 0.0f, 0.0f,
                width, 0.0f, 0.0f,// 1
                width, -height, 0.0f, 
                0, -height, 0.0f, //3
                0, -height, 0.0f,
                0.0f, 0.0f, 0.0f,//4
                width, -height, 0.0f,
                width, -height * 2, 0.0f, //5
                width, -height * 2, 0.0f,
                0.0f, -height * 2, 0.0f, //6
                0.0f, -height * 2, 0.0f, 
                0.0f, -height , 0.0f,//7
            };
            break;
        case 7:
            b = {
                0.0f, 0.0f, 0.0f,
                width, 0.0f, 0.0f,// 1
                width, 0.0f, 0.0f,
                width, -height, 0.0f, //2
                width, -height, 0.0f, 
                width, -height * 2, 0.0f, //5
            };
            break;
        case 8:
            b = {
                0.0f, 0.0f, 0.0f,
                width, 0.0f, 0.0f,// 1
                width, 0.0f, 0.0f,
                width, -height, 0.0f, //2
                width, -height, 0.0f, 
                0, -height, 0.0f, //3
                0, -height, 0.0f,
                0.0f, 0.0f, 0.0f,//4
                width, -height, 0.0f,
                width, -height * 2, 0.0f, //5
                width, -height * 2, 0.0f,
                0.0f, -height * 2, 0.0f, //6
                0.0f, -height * 2, 0.0f, 
                0.0f, -height , 0.0f,//7
            };
            break;
        case 9:
            b = {
                0.0f, 0.0f, 0.0f,
                width, 0.0f, 0.0f,// 1
                width, 0.0f, 0.0f,
                width, -height, 0.0f, //2
                width, -height, 0.0f, 
                0, -height, 0.0f, //3
                0, -height, 0.0f,
                0.0f, 0.0f, 0.0f,//4
                width, -height, 0.0f,
                width, -height * 2, 0.0f, //5
                width, -height * 2, 0.0f,
                0.0f, -height * 2, 0.0f, //6
            };
            break;
        case 0:
            b = {
                0.0f, 0.0f, 0.0f,
                width, 0.0f, 0.0f,// 1
                width, 0.0f, 0.0f,
                width, -height, 0.0f, //2
                0, -height, 0.0f,
                0.0f, 0.0f, 0.0f,//4
                width, -height, 0.0f,
                width, -height * 2, 0.0f, //5
                width, -height * 2, 0.0f,
                0.0f, -height * 2, 0.0f, //6
                0.0f, -height * 2, 0.0f, 
                0.0f, -height , 0.0f,//7
            };
            break;
        default:
            b = {
                1.0f, 1.0f, 0.0f,
                0.0f, 0.0f, 0.0f
            };
       }
    return b;
}
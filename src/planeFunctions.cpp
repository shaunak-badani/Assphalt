;
#include "functions.h"
;
#include "main.h"
#include <math.h>
#include <bits/stdc++.h>

using namespace std;

color_t color_front = {167, 166, 161};
color_t color_mid = {134, 84, 84};
color_t color_back = {187, 162, 62};
color_t color_wing_left = {127, 127, 127};
color_t color_wing_right = {127, 127, 127};

vector<GLfloat> color_plane, color_volcano;

void colorPlane(int n, color_t color)
{

	vector<GLfloat> localColor = {(float)color.r / 256, (float)color.g / 256, (float)color.b / 256};
	for (int i = 0; i < n; i += 3)
	{
		color_plane.insert(color_plane.end(), localColor.begin(), localColor.end());
	}
}

void colorVolcano(int n, color_t color) {
	vector<GLfloat> localColor = {(float)color.r / 256, (float)color.g / 256, (float)color.b / 256};
	for (int i = 0; i < n; i += 3)
	{
		color_volcano.insert(color_volcano.end(), localColor.begin(), localColor.end());
	}
}

vector<GLfloat> addColor(int n, color_t color) {
	vector<GLfloat> localColor = {(float)color.r / 256, (float)color.g / 256, (float)color.b / 256};
	vector<GLfloat> col;
	for (int i = 0; i < n; i += 3)
	{
		col.insert(col.end(), localColor.begin(), localColor.end());
	}
	return col;
}

vector<GLfloat> makePolygon(float centerX, float centerY, float z, float sideLength, int n)
{
	vector<GLfloat> g_vertex_buffer_data(9 * n);

	float angle = 2 * M_PI / n;
	float start_coordX = sideLength / 2;
	float start_coordY = -start_coordX / tan(angle / 2);
	float tempX, tempY;
	for (int i = 0; i < 3 * n; i += 3)
	{
		// Initializing all 3rd co-ordinates to 0
		g_vertex_buffer_data[3 * i] = centerX;
		g_vertex_buffer_data[3 * i + 1] = centerY;
		g_vertex_buffer_data[3 * i + 2] = z;

		g_vertex_buffer_data[3 * (i + 1)] = centerX + start_coordX;
		g_vertex_buffer_data[3 * (i + 1) + 1] = centerY + start_coordY;
		g_vertex_buffer_data[3 * (i + 1) + 2] = z;

		g_vertex_buffer_data[3 * (i + 2)] = centerX + start_coordX * cos(angle) - start_coordY * sin(angle);
		g_vertex_buffer_data[3 * (i + 2) + 1] = centerY + start_coordX * sin(angle) + start_coordY * cos(angle);
		g_vertex_buffer_data[3 * (i + 2) + 2] = z;

		tempX = start_coordX;
		tempY = start_coordY;

		start_coordX = tempX * cos(angle) - tempY * sin(angle);
		start_coordY = tempX * sin(angle) + tempY * cos(angle);
	}
	return g_vertex_buffer_data;
}

vector<GLfloat> groundPolygon(float centerX, float centerY, float z, float sideLength, int n)
{
	vector<GLfloat> g_vertex_buffer_data(9 * n);

	float angle = 2 * M_PI / n;
	float start_coordX = sideLength / 2;
	float start_coordY = -start_coordX / tan(angle / 2);
	float tempX, tempY;
	for (int i = 0; i < 3 * n; i += 3)
	{
		// Initializing all 3rd co-ordinates to 0
		g_vertex_buffer_data[3 * i] = centerX;
		g_vertex_buffer_data[3 * i + 1] = centerY;
		g_vertex_buffer_data[3 * i + 2] = z;

		g_vertex_buffer_data[3 * (i + 1)] = centerX + start_coordX;
		g_vertex_buffer_data[3 * (i + 1) + 1] = centerY;
		g_vertex_buffer_data[3 * (i + 1) + 2] = z + start_coordY;

		g_vertex_buffer_data[3 * (i + 2)] = centerX + start_coordX * cos(angle) - start_coordY * sin(angle);
		g_vertex_buffer_data[3 * (i + 2) + 1] = centerY;
		g_vertex_buffer_data[3 * (i + 2) + 2] = z + start_coordX * sin(angle) + start_coordY * cos(angle);

		tempX = start_coordX;
		tempY = start_coordY;

		start_coordX = tempX * cos(angle) - tempY * sin(angle);
		start_coordY = tempX * sin(angle) + tempY * cos(angle);
	}
	return g_vertex_buffer_data;
}

// Makes a circle in the xy plane
vector<GLfloat> makeCircle(float r, float x, float y, float z)
{
	int n = 30;
	// Make a polygon using 30 triangles
	return makePolygon(x, y, z, 2 * r * sin(M_PI / n), n);
}

vector<GLfloat> makeCircleXZ(float r, float x, float y, float z)
{
	int n = 30;
	return groundPolygon(x, y, z, 2 * r * sin(M_PI / n), n);
}

GLfloat *vecToArray(vector<GLfloat> v)
{
	GLfloat *vertex_buffer_data = new GLfloat[v.size()];
	int j = 0;
	for (vector<GLfloat>::iterator i = v.begin(); i != v.end(); ++i)
	{
		vertex_buffer_data[j] = *i;
		j++;
	}
	return vertex_buffer_data;
}

GLfloat *color_array()
{
	GLfloat *vertex_buffer_data = new GLfloat[color_plane.size()];
	int j = 0;
	for (vector<GLfloat>::iterator i = color_plane.begin(); i != color_plane.end(); ++i)
	{
		vertex_buffer_data[j] = *i;
		j++;
	}
	return vertex_buffer_data;
}

vector<GLfloat> makeFrustrumXZ(float c_front, float c_back, float r1, float r2)
{
	vector<GLfloat> circle1, circle2;
	circle1 = makeCircleXZ(r1, 0, c_front, 0);
	circle2 = makeCircleXZ(r2, 0, c_back, 0);
	vector<GLfloat> midRect(circle1.size() * 2);
	int j = 0;
	auto c2 = circle2.begin();
	for (auto c1 = circle1.begin(); c1 != circle1.end(); c1 = next(c1, 9))
	{
		midRect[j] = *next(c1, 3);
		midRect[j + 1] = *(next(c1, 4));
		midRect[j + 2] = *(next(c1, 5));

		midRect[j + 3] = *(next(c1, 6));
		midRect[j + 4] = *(next(c1, 7));
		midRect[j + 5] = *(next(c1, 8));

		midRect[j + 6] = *(next(c2, 3));
		midRect[j + 7] = *(next(c2, 4));
		midRect[j + 8] = *(next(c2, 5));

		midRect[j + 9] = *(next(c2, 3));
		midRect[j + 10] = *(next(c2, 4));
		midRect[j + 11] = *(next(c2, 5));

		midRect[j + 12] = *(next(c2, 6));
		midRect[j + 13] = *(next(c2, 7));
		midRect[j + 14] = *(next(c2, 8));

		midRect[j + 15] = *(next(c1, 6));
		midRect[j + 16] = *(next(c1, 7));
		midRect[j + 17] = *(next(c1, 8));

		c2 = next(c2, 9);
		j += 18;
	}

	colorVolcano(circle1.size(), COLOR_ORANGE);
	circle1.insert(circle1.end(), midRect.begin(), midRect.end());
	colorVolcano(midRect.size(), COLOR_GREY);
	circle1.insert(circle1.end(), circle2.begin(), circle2.end());
	colorVolcano(circle2.size(), COLOR_ORANGE);

	return circle1;
}

vector<GLfloat> colorVol() {
	return color_volcano;
}

// Constructs a frustrum with coordinates at the center,and radius
vector<GLfloat> makeFrustrum(float c_front, float c_back, float r1, float r2)
{
	vector<GLfloat> circle1, circle2;
	circle1 = makeCircle(r1, 0, 0, c_front);
	circle2 = makeCircle(r2, 0, 0, c_back);
	vector<GLfloat> midRect(circle1.size() * 2);
	int j = 0;
	auto c2 = circle2.begin();
	for (auto c1 = circle1.begin(); c1 != circle1.end(); c1 = next(c1, 9))
	{
		midRect[j] = *next(c1, 3);
		midRect[j + 1] = *(next(c1, 4));
		midRect[j + 2] = *(next(c1, 5));

		midRect[j + 3] = *(next(c1, 6));
		midRect[j + 4] = *(next(c1, 7));
		midRect[j + 5] = *(next(c1, 8));

		midRect[j + 6] = *(next(c2, 3));
		midRect[j + 7] = *(next(c2, 4));
		midRect[j + 8] = *(next(c2, 5));

		midRect[j + 9] = *(next(c2, 3));
		midRect[j + 10] = *(next(c2, 4));
		midRect[j + 11] = *(next(c2, 5));

		midRect[j + 12] = *(next(c2, 6));
		midRect[j + 13] = *(next(c2, 7));
		midRect[j + 14] = *(next(c2, 8));

		midRect[j + 15] = *(next(c1, 6));
		midRect[j + 16] = *(next(c1, 7));
		midRect[j + 17] = *(next(c1, 8));

		c2 = next(c2, 9);
		j += 18;
	}

	circle1.insert(circle1.end(), midRect.begin(), midRect.end());
	circle1.insert(circle1.end(), circle2.begin(), circle2.end());

	return circle1;
}

vector<GLfloat> makeHollowFrustrum(float c_front, float c_back, float r1, float r2) {
	vector<GLfloat> circle1, circle2;
	circle1 = makeCircle(r1, 0, 0, c_front);
	circle2 = makeCircle(r2, 0, 0, c_back);
	vector<GLfloat> midRect(circle1.size() * 2);
	int j = 0;
	auto c2 = circle2.begin();
	for (auto c1 = circle1.begin(); c1 != circle1.end(); c1 = next(c1, 9))
	{
		midRect[j] = *next(c1, 3);
		midRect[j + 1] = *(next(c1, 4));
		midRect[j + 2] = *(next(c1, 5));

		midRect[j + 3] = *(next(c1, 6));
		midRect[j + 4] = *(next(c1, 7));
		midRect[j + 5] = *(next(c1, 8));

		midRect[j + 6] = *(next(c2, 3));
		midRect[j + 7] = *(next(c2, 4));
		midRect[j + 8] = *(next(c2, 5));

		midRect[j + 9] = *(next(c2, 3));
		midRect[j + 10] = *(next(c2, 4));
		midRect[j + 11] = *(next(c2, 5));

		midRect[j + 12] = *(next(c2, 6));
		midRect[j + 13] = *(next(c2, 7));
		midRect[j + 14] = *(next(c2, 8));

		midRect[j + 15] = *(next(c1, 6));
		midRect[j + 16] = *(next(c1, 7));
		midRect[j + 17] = *(next(c1, 8));

		c2 = next(c2, 9);
		j += 18;
	}

	return midRect;
}

vector<GLfloat> bodyConstruct()
{
	vector<GLfloat> front = makeFrustrum(-2, -6, 1.5, 0);
	colorPlane(front.size(), color_front);

	vector<GLfloat> middle = makeFrustrum(6, -2, 1.5, 1.5);
	colorPlane(middle.size(), color_mid);

	vector<GLfloat> endPart = makeFrustrum(7, 6, 0.5, 1);
	colorPlane(endPart.size(), color_back);

	middle.insert(middle.end(), endPart.begin(), endPart.end());
	front.insert(front.end(), middle.begin(), middle.end());

	return front;
}

// Args -> start with x and z and construct wings using these coordinates
vector<GLfloat> wingsConstruct(float x, float z, float size, bool left)
{
	vector<GLfloat> wing_left = {
		x, 0.0f, z - size / 2,
		x - size, 0.0f, z + size / 2,
		x, 0.0f, z + size / 2};

	vector<GLfloat> wing_right = {
		x, 0.0f, z - size / 2,
		x + size, 0.0f, z + size / 2,
		x, 0.0f, z + size / 2};

	return left ? wing_left : wing_right;
}

vector<GLfloat> planeConstruct()
{
	vector<GLfloat> body = bodyConstruct();
	vector<GLfloat> wing_left = wingsConstruct(-1.5, 0.5, 3, true);
	colorPlane(wing_left.size(), color_wing_left);

	vector<GLfloat> wing_right = wingsConstruct(1.5, 0.5, 3, false);
	colorPlane(wing_right.size(), color_wing_right);

	wing_left.insert(wing_left.end(), wing_right.begin(), wing_right.end());

	body.insert(body.end(), wing_left.begin(), wing_left.end());
	return body;
}
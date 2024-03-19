#pragma once
#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include "GL/freeglut.h"
#include "GLUTCallbacks.h"
#include "GLUTUtils.h"

#include <utility>



using namespace std;


class GL2D
{
public:
	/// <summary
	/// >Draws a triangle based off three desired points, will be drawn in red.
	/// <para>Look at SeeTriangeColor to change the desired color</para>
	/// </summary>
	void DrawTriangle(pair<GLfloat, GLfloat> p1, pair<GLfloat, GLfloat> p2, pair<GLfloat, GLfloat> p3);
	/// <summary
	/// >Draws a triangle based off three desired points, will be drawn in the desired color.
	/// </summary>
	void DrawTriangleColor(pair<GLfloat, GLfloat> p1, pair<GLfloat, GLfloat> p2, pair<GLfloat, GLfloat> p3, GlutColor color);

	/// <summary
	/// >Draws a Polygon based off four desired points, will be drawn in red.
	/// <para>Look at DrawPolygonColor to change the desired color</para>
	/// </summary>
	void DrawPolygon(pair<GLfloat, GLfloat> p1, pair<GLfloat, GLfloat> p2, pair<GLfloat, GLfloat> p3, pair<GLfloat, GLfloat> p4);
	/// <summary
	/// >Draws a Polygon based off four desired points, will be drawn in the desired color.
	/// </summary>
	void DrawPolygonColor(pair<GLfloat, GLfloat> p1, pair<GLfloat, GLfloat> p2, pair<GLfloat, GLfloat> p3, pair<GLfloat, GLfloat> p4, GlutColor color);





};


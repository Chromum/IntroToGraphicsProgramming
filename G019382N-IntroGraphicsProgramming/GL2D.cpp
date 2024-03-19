#include "GL2D.h"

void GL2D::DrawTriangle(pair<GLfloat, GLfloat> p1, pair<GLfloat, GLfloat> p2, pair<GLfloat, GLfloat> p3)
{
	glBegin(GL_POLYGON);
	{
		glColor4f(1.0f, 0.0f, 0.0f, 0.0f);
		glVertex2f(p1.first, p1.second);
		glColor4f(1.0f, 0.0f, 0.0f, 0.0f);
		glVertex2f(p2.first, p2.second);
		glColor4f(1.0f, 0.0f, 0.0f, 0.0f);
		glVertex2f(p3.first, p3.second);
		glEnd();
	}
}

void GL2D::DrawTriangleColor(pair<GLfloat, GLfloat> p1, pair<GLfloat, GLfloat> p2, pair<GLfloat, GLfloat> p3, GlutColor color)
{
	glBegin(GL_POLYGON);
	{
		glColor4f(color.r,color.g,color.b,color.a);
		glVertex2f(p1.first, p1.second);
		glColor4f(color.r, color.g, color.b, color.a);
		glVertex2f(p2.first, p2.second);
		glColor4f(color.r, color.g, color.b, color.a);
		glVertex2f(p3.first, p3.second);
		glEnd();
	}
}

void GL2D::DrawPolygon(pair<GLfloat, GLfloat> p1, pair<GLfloat, GLfloat> p2, pair<GLfloat, GLfloat> p3, pair<GLfloat, GLfloat> p4)
{
	glBegin(GL_POLYGON);
	{
		glColor4f(1.0f, 0.0f, 0.0f, 0.0f);
		glVertex2f(p1.first , p1.second);
		glVertex2f(p2.first, p2.second);
		glVertex2f(p3.first, p3.second);
		glVertex2f(p4.first, p4.second);
		glEnd();
	}
}

void GL2D::DrawPolygonColor(pair<GLfloat, GLfloat> p1, pair<GLfloat, GLfloat> p2, pair<GLfloat, GLfloat> p3, pair<GLfloat, GLfloat> p4, GlutColor color)
{
	glBegin(GL_POLYGON);
	{
		glColor4f(color.r,color.g,color.b,color.a);
		glVertex2f(p1.first, p1.second);
		glVertex2f(p2.first, p2.second);
		glVertex2f(p3.first, p3.second);
		glVertex2f(p4.first, p4.second);
		glEnd();
	}
}

void GL2D::DrawTriangleRotate(pair<GLfloat, GLfloat> p1, pair<GLfloat, GLfloat> p2, pair<GLfloat, GLfloat> p3, float rotation)
{
	glPushMatrix();
	glRotatef(rotation, 0.0f, 0.0f, -1.0f);

	glBegin(GL_POLYGON);
	{

		glColor4f(1.0f, 0.0f, 0.0f, 0.0f);
		glVertex2f(p1.first, p1.second);
		glColor4f(1.0f, 0.0f, 0.0f, 0.0f);
		glVertex2f(p2.first, p2.second);
		glColor4f(1.0f, 0.0f, 0.0f, 0.0f);
		glVertex2f(p3.first, p3.second);
		glEnd();
	}

	glPopMatrix();
}

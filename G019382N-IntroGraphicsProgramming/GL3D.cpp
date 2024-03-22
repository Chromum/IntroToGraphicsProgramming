#include "GL3D.h"

void GL3D::DrawCube()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glBegin(GL_QUADS);
	{
		glColor3f(1, 0, 0);
		glVertex3f(.5f, .5f, -.5f);
		glVertex3f(-.5f, .5f, -.5f);
		glVertex3f(-.5f, .5f, .5f);
		glVertex3f(.5f, .5f, .5f);

		glColor3f(1, 0, 1);
		glVertex3f(.5f, -.5f, .5f);
		glVertex3f(-.5f, -.5f, .5f);
		glVertex3f(-.5f, -.5f, -.5f);
		glVertex3f(.5f, -.5f, -.5f);

		glColor3f(1, .05f, 1);
		glVertex3f(.5f, .5f, .5f);
		glVertex3f(-.5f, .5f, .5f);
		glVertex3f(-.5f, -.5f, .5f);
		glVertex3f(.5f, -.5f, .5f);

		glColor3f(0.5f, .05f, 1);
		glVertex3f(.5f, -.5f, -.5f);
		glVertex3f(-.5f, -.5f, -.5f);
		glVertex3f(-.5f, .5f, -.5f);
		glVertex3f(.5f, .5f, -.5f);

		glColor3f(0.5f, .05f, .05f);
		glVertex3f(-.5f, .5f, .5f);
		glVertex3f(-.5f, .5f, -.5f);
		glVertex3f(-.5f, -.5f, -.5f);
		glVertex3f(-.5f, -.5f, .5f);

		glVertex3f(.5f, .5f, -.5f);
		glVertex3f(.5f, .5f, .5f);
		glVertex3f(.5f, -.5f, .5f);
		glVertex3f(.5f, -.5f, -.5f);
		glEnd();
	}
	glFlush();

}

void GL3D::DrawCubeRotate(float rotationX, float rotationY, float rotationZ)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(DMPAPER_FANFOLD_LGL_GERMAN);
	glLoadIdentity();

	glPushMatrix();
	//glRotatef(.5f, rotationX, rotationY, 0);
	glRotatef(rotationY, 1.0f, 0, 0);
	glRotatef(rotationX,0, 1.0f, 0);
	glRotatef(rotationZ, 0, 0, 1.0f);
	
	glBegin(GL_QUADS);
	{
		glColor3f(1, 0, 0);
		glVertex3f(.5f, .5f, -.5f);
		glVertex3f(-.5f, .5f, -.5f);
		glVertex3f(-.5f, .5f, .5f);
		glVertex3f(.5f, .5f, .5f);

		glColor3f(1, 0, 1);
		glVertex3f(.5f, -.5f, .5f);
		glVertex3f(-.5f, -.5f, .5f);
		glVertex3f(-.5f, -.5f, -.5f);
		glVertex3f(.5f, -.5f, -.5f);

		glColor3f(1, .05f, 1);
		glVertex3f(.5f, .5f, .5f);
		glVertex3f(-.5f, .5f, .5f);
		glVertex3f(-.5f, -.5f, .5f);
		glVertex3f(.5f, -.5f, .5f);

		glColor3f(0.5f, .05f, 1);
		glVertex3f(.5f, -.5f, -.5f);
		glVertex3f(-.5f, -.5f, -.5f);
		glVertex3f(-.5f, .5f, -.5f);
		glVertex3f(.5f, .5f, -.5f);

		glColor3f(0.5f, .05f, .05f);
		glVertex3f(-.5f, .5f, .5f);
		glVertex3f(-.5f, .5f, -.5f);
		glVertex3f(-.5f, -.5f, -.5f);
		glVertex3f(-.5f, -.5f, .5f);

		glVertex3f(.5f, .5f, -.5f);
		glVertex3f(.5f, .5f, .5f);
		glVertex3f(.5f, -.5f, .5f);
		glVertex3f(.5f, -.5f, -.5f);
		glEnd();
	}

	glFlush();
	glPopMatrix();
}

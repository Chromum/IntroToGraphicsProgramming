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

void GL3D::DrawCubeRotate(float rotation)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glPushMatrix();
	glRotatef(rotation, rotation, rotation, -1.0f);

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

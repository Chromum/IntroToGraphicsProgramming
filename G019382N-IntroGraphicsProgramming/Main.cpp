#include "Main.h"

int main(int argc, char* argv[])
{
	Main* game = new Main(argc, argv);





	delete game;

	return 0;
}

//Construct
Main::Main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitWindowSize(800, 800);
	GLUTCallbacks::Init(this);
	glutCreateWindow("Simple OpenGL Program");
	glutDisplayFunc(GLUTCallbacks::Display);
	glutMainLoop();
}

//Deconstruct
Main::~Main(void)
{
}

void Main::Display()
{
	glClear(GL_COLOR_BUFFER_BIT);
	pair<GLfloat,GLfloat> p1;
	pair<GLfloat, GLfloat> p2;
	pair<GLfloat, GLfloat> p3;
	//p1
	p1.first = 1.0;
	p1.second = 1.0;
	//p2
	p2.first = 1.0f;
	p2.second = -1.0f;
	//p3
	p3.first = -1.0f;
	p3.second = -1.0f;

	DrawTriangle(p1,p2,p3);

	p2.first = -1.0f;
	p2.second = 1.0f;
	//DrawTriangle(p1, p2, p3);


	//p1.first = 0.24;
	//p1.second = 1.0;
	//p2.first = 0.75;
	//p2.second = 0.45;
	//p3.first = -0.93;
	//p3.second = -0.1f;

	//DrawTriangle(p1, p2, p3);


	//DrawPolygon();


	glFlush();

}

void Main::DrawPolygon()
{
	glBegin(GL_POLYGON);
	{
		glColor4f(1.0f, 0.0f, 0.0f, 0.0f);
		glVertex2f(-0.75, 0.5);
		glVertex2f(0.75, 0.5);
		glVertex2f(0.75, -0.5);
		glVertex2f(-0.75, -0.5);
		glEnd();
	}
}

void Main::DrawTriangle(pair<GLfloat, GLfloat> p1, pair<GLfloat, GLfloat> p2, pair<GLfloat, GLfloat> p3)
{
	glBegin(GL_POLYGON);
	{
		glColor4f(1.0f, 0.0f, 0.0f, 0.0f);
		glVertex2f(p1.first, p1.second);
		glColor4f(0.0f, 1.0f, 0.0f, 0.0f);
		glVertex2f(p2.first, p2.second);
		glColor4f(0.0f, 0.0f, 1.0f, 0.0f);
		glVertex2f(p3.first, p3.second);
		glEnd();
	}

}

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

	GL2D* gl2d = new GL2D;
	GlutColor color = GlutColor();

	color.r = 255;
	color.g = 255;



	gl2d->DrawTriangleColor(p1,p2,p3,color);

	glFlush();

}




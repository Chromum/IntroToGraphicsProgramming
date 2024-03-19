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
	rotationX = 0.0f;
	rotationY = 0.0f;
	rotationZ = 0.0f;
	std::fill_n(buffer, 256, false);

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE);
	glutInitWindowSize(800, 800);
	GLUTCallbacks::Init(this);
	glutCreateWindow("Simple OpenGL Program");
	glutDisplayFunc(GLUTCallbacks::Display);
	glutTimerFunc(REFRESHRATE, GLUTCallbacks::Timer, REFRESHRATE);
	glEnable(GL_DEPTH_TEST);
	glutKeyboardFunc(GLUTCallbacks::KeyboardKeyDown);
	glutKeyboardUpFunc(GLUTCallbacks::KeyboardKeyUp);
	glutMainLoop();
}

//Deconstruct
Main::~Main(void)
{
}

void Main::Update()
{
	glutPostRedisplay();
	HandleInput();

	//rotation += 0.5f;

	if (rotationX >= 360.0f)
		rotationX = 0.0f;

	if (rotationY >= 360.0f)
		rotationY = 0.0f;

	if (rotationZ >= 360.0f)
		rotationZ = 0.0f;

	//std::cout << "Z: " << rotationZ << endl;
}

void Main::Display()
{
	glClear(GL_COLOR_BUFFER_BIT);
	//pair<GLfloat,GLfloat> p1;
	//pair<GLfloat, GLfloat> p2;
	//pair<GLfloat, GLfloat> p3;
	////p1
	//p1.first = 1.0;
	//p1.second = 1.0;
	////p2
	//p2.first = 1.0f;
	//p2.second = -1.0f;
	////p3
	//p3.first = -1.0f;
	//p3.second = -1.0f;

	//GL2D* gl2d = new GL2D;
	//GlutColor color = GlutColor();

	//color.r = 255;
	//color.g = 255;

	//gl2d->DrawTriangleRotate(p1,p2,p3,rotation);

	////p1
	//p1.first = -0.30;
	//p1.second = -1.0;
	////p2
	//p2.first = -1.0f;
	//p2.second = 1.0f;
	////p3
	//p3.first = 1.0f;
	//p3.second = 1.0f;

	//gl2d->DrawTriangleRotate(p1, p2, p3, rotation);

	GL3D* gl3d = new GL3D;
	gl3d->DrawCubeRotate(rotationX,rotationY,rotationZ);

	glFlush();
	glutSwapBuffers();

}

void Main::KeyboardDown(unsigned char key, int x, int y)
{
	buffer[key] = true;
}

void Main::KeyboardUp(unsigned char key, int x, int y)
{
	buffer[key] = false;
}

void Main::HandleInput()
{
	for (size_t i = 0; i < sizeof(buffer); i++)
	{
		if (buffer[(int)'w'] == true)
			rotationY += .01f;
		if (buffer[(int)'s'] == true)
			rotationY += -.01f;

		if (buffer[(int)'d'] == true)
			rotationX += .01f;
		if (buffer[(int)'a'] == true)
			rotationX += -.01f;

		if (buffer[(int)'e'] == true)
			rotationZ += .01f;
		if (buffer[(int)'q'] == true)
			rotationZ += -.01f;

	}
}





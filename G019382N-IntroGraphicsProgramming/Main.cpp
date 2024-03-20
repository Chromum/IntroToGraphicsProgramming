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
	displayEvent = new EventHandler("Display");

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

	

	Render3DComponent* renderer = new Render3DComponent(displayEvent);
	Mesh mesh = Mesh();
	mesh.AddVert(.5f, .5f, -.5f);
	mesh.AddVert(-.5f, .5f, -.5f);
	mesh.AddVert(-.5f, .5f, .5f);
	mesh.AddVert(.5f, .5f, .5f);

	mesh.AddVert(.5f, -.5f, .5f);
	mesh.AddVert(-.5f, -.5f, .5f);
	mesh.AddVert(-.5f, -.5f, -.5f);
	mesh.AddVert(.5f, -.5f, -.5f);

	mesh.AddVert(.5f, .5f, .5f);
	mesh.AddVert(-.5f, .5f, .5f);
	mesh.AddVert(-.5f, -.5f, .5f);
	mesh.AddVert(.5f, -.5f, .5f);

	mesh.AddVert(.5f, -.5f, -.5f);
	mesh.AddVert(-.5f, -.5f, -.5f);
	mesh.AddVert(-.5f, .5f, -.5f);
	mesh.AddVert(.5f, .5f, -.5f);

	mesh.AddVert(-.5f, .5f, .5f);
	mesh.AddVert(-.5f, .5f, -.5f);
	mesh.AddVert(-.5f, -.5f, -.5f);
	mesh.AddVert(-.5f, -.5f, .5f);

	mesh.AddVert(.5f, .5f, -.5f);
	mesh.AddVert(.5f, .5f, .5f);
	mesh.AddVert(.5f, -.5f, .5f);
	mesh.AddVert(.5f, -.5f, -.5f);

	renderer->objectMesh = mesh;
	GLComponent* comp = renderer;
	comp->objectParent = object;
	object->AddComponent(comp);

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

	object->Transform.Rotation.x = rotationX;
	object->Transform.Rotation.y = rotationY;
	object->Transform.Rotation.z = rotationZ;


	//std::cout << "Z: " << rotationZ << endl;
}

void Main::Display()
{
	glClear(GL_COLOR_BUFFER_BIT);

	//GL3D* gl3d = new GL3D;
	//gl3d->DrawCubeRotate(rotationX,rotationY,rotationZ);

	displayEvent->FireEvent();

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

		if (buffer[(int)'0'] == true)
			object->Transform.Position.x += 0.0001f;
		if (buffer[(int)'1'] == true)
			object->Transform.Position.x -= 0.0001f;

		if (buffer[(int)'2'] == true)
			object->Transform.Position.y += 0.0001f;
		if (buffer[(int)'9'] == true)
			object->Transform.Position.y -= 0.0001f;

		if (buffer[(int)'3'] == true)
			object->Transform.Position.z += 0.0001f;
		if (buffer[(int)'8'] == true)
			object->Transform.Position.z -= 0.0001f;

	}
}





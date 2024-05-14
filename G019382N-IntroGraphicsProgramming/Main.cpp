#include "Main.h"
#include "Constants.h"
#include "GLUTUtils.h"
#include "ModelLoader.h"
#include "ImageReader.h"
#include "Image.h"
#include "Sphere.h"

Vector3 atVector = Vector3(0, 0, 0);
Vector3 lookDirection = Vector3(0, 0, 0);
Vector3 forwardDirection = Vector3(0, 0, 0);

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
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	screenWidth = glutGet(GLUT_SCREEN_WIDTH);
	screenHeight = glutGet(GLUT_SCREEN_HEIGHT);

	glutInitWindowSize(screenWidth, screenHeight);
	glutInitContextVersion(3, 1);
	GLUTCallbacks::Init(this);
	glutCreateWindow("Simple OpenGL Program");
	glutDisplayFunc(GLUTCallbacks::Display);
	glutTimerFunc(REFRESHRATE, GLUTCallbacks::Timer, REFRESHRATE);
	glEnable(GL_DEPTH_TEST);
	glutKeyboardFunc(GLUTCallbacks::KeyboardKeyDown);
	glutKeyboardUpFunc(GLUTCallbacks::KeyboardKeyUp);
	glutMouseFunc(GLUTCallbacks::MouseClick);
	glutPassiveMotionFunc(GLUTCallbacks::MouseMove);
	glutReshapeFunc(GLUTCallbacks::OnWindowResize);
	//glutSetCursor(GLUT_CURSOR_NONE);
	//glutFullScreen();
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	//ReBuildProjectionMatrix();
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glViewport(0, 0, screenWidth, screenHeight);
	gluPerspective(110, ((float)screenWidth / (float)screenHeight), 0.01, 1000);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	ModelLoader ml = ModelLoader();
	ImageReader image = ImageReader();

	std::vector<Mesh*> meshes = ml.LoadMeshAtPath("Models/untitled.obj");

	GLObject* obj1 = new GLObject(Vector3(0,-10,0), Vector3(1, 1, 1), image.ReadImage("Models/untitled.png"), meshes,displayEvent);
	GLObject* obj2 = new GLObject(Vector3(-10, -10, 0), Vector3(1, 1, 1), image.ReadImage("Models/untitled.png"), meshes, displayEvent);
	GLObject* obj3 = new GLObject(Vector3(10, -10, 0), Vector3(1, 1, 1), image.ReadImage("Models/untitled.png"), meshes, displayEvent);
	sphere = new Sphere();
	sphere->Transform.Scale = Vector3(1, 1, 1);

	objects.push_back(obj1);
	objects.push_back(obj2);
	objects.push_back(obj3);


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
}

void Main::Display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	ReBuildProjectionMatrix();




	drawLine(startPoint, endPoint);
	sphere->Draw();
	displayEvent->FireEvent();

	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	gluOrtho2D(0, screenWidth, 0, screenHeight);
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
	// Set circle properties
	glColor3f(1.0f, 1.0f, 1.0f); // White color

	// Draw a circle at the center of the screen
	glBegin(GL_LINE_LOOP);
	for (int i = 0; i < 360; ++i) {
		float angle = i * 3.14159f / 180.0f;
		float x = screenWidth / 2 + 2 * cos(angle);
		float y = screenHeight / 2 + 2 * sin(angle);
		glVertex2f(x, y);
	}
	glEnd();

	glRasterPos2f(100, 120);
	glutBitmapString(GLUT_BITMAP_8_BY_13, (const unsigned char*)"text.c_str()");

	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
	glFlush();
	glutSwapBuffers();

}

void Main::KeyboardDown(unsigned char key, int x, int y)
{

	buffer[key] = true;
	std::cout << key << endl;
}

void Main::KeyboardUp(unsigned char key, int x, int y)
{
	buffer[key] = false;
}

void Main::HandleInput()
{


	if (buffer[(int)'0'] == true)
		objects[0]->Transform.Position.x += 0.05f;
	if (buffer[(int)'1'] == true)
		objects[0]->Transform.Position.x -= 0.05f;

	if (buffer[(int)'l'] == true)
		objects[0]->Transform.Position.y += 0.05f;
	if (buffer[(int)'k'] == true)
		objects[0]->Transform.Position.y -= 0.05f;

	if (buffer[(int)'3'] == true)
		objects[0]->Transform.Position.z += 0.05f;
	if (buffer[(int)'8'] == true)
		objects[0]->Transform.Position.z -= 0.05f;

	if (buffer[(int)'w'])
	{
		cameraTransform.Position = cameraTransform.Position + cameraFront * 1;
	}
	if (buffer[(int)'s'])
	{
		cameraTransform.Position = cameraTransform.Position - cameraFront * 1;
	}

	if (buffer[(int)'a'])
	{
		Vector3 rVec = Vector3(0, 1, 0).Cross(cameraFront).Normilized();
		cameraTransform.Position = cameraTransform.Position + rVec * 1;
	}
	if (buffer[(int)'d'])
	{
		Vector3 rVec = Vector3(0, 1, 0).Cross(cameraFront).Normilized();
		cameraTransform.Position = cameraTransform.Position - rVec * 1;
	}

	static bool wireFrame = false;
	if (buffer[(int)'o'] == true) 
	{
		if (wireFrame)
		{
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
			wireFrame = false;
		}
		else 
		{
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
			wireFrame = true;
		}
	}

	
	return;
}

void Main::drawLine(Vector3 startPoint, Vector3 endPoint) {
	glBegin(GL_LINES);
	glVertex3f(startPoint.x, startPoint.y, startPoint.z);
	glVertex3f(endPoint.x, endPoint.y, endPoint.z);
	glEnd();
}

void Main::ReBuildProjectionMatrix() 
{
	Vector3 cameraUp = Vector3(0.0f, 1.0f, 0.0f);
	Vector3 lookat_point = cameraFront + cameraTransform.Position;


	glMatrixMode(GL_MODELVIEW);
	{
		glLoadIdentity();
		gluLookAt(
			cameraTransform.Position.x,
			cameraTransform.Position.y,
			cameraTransform.Position.z,

			lookat_point.x,
			lookat_point.y,
			lookat_point.z,

			cameraUp.x,
			cameraUp.y,
			cameraUp.z);
	}

	glutPostRedisplay();
}





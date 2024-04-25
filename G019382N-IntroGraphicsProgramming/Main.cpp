#include "Main.h"
#include "Constants.h"
#include "GLUTUtils.h"
#include "ModelLoader.h"
#include "ImageReader.h"
#include "Image.h"

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
	glutSetCursor(GLUT_CURSOR_NONE);
	//glutFullScreen();
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	//ReBuildProjectionMatrix();
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glViewport(0, 0, screenWidth, screenHeight);
	gluPerspective(120, 1, 0.01, 1000);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	//cameraTransform.Position.x = 5;
	//cameraTransform.Position.y = -10;
	//cameraTransform.Position.z = 10;
	//gluLookAt(cameraTransform.Position.x, cameraTransform.Position.y, cameraTransform.Position.z, 0, 0, 0, 0, 1, 0);

	

	ModelLoader ml = ModelLoader();
	ImageReader image = ImageReader();

	std::vector<Mesh*> meshes = ml.LoadMeshAtPath("Models/untitled.obj");
	GLuint image2 = image.ReadImage("Models/untitled.png");

	GLObject* obj1 = new GLObject();
	obj1->Transform.Scale.x = 1;
	obj1->Transform.Scale.y = 1;
	obj1->Transform.Scale.z = 1;
	objects.push_back(obj1);
	Renderer3D* renderer1 = new Renderer3D(displayEvent, obj1);
	renderer1->SetTexture(image2);
	renderer1->objectMeshes = meshes;
	renderer1->color = GlutColor(0, 128, 128, 1);
	obj1->render3D = renderer1;
	obj1->Transform.Position.x = 0;
	obj1->Transform.Position.z = -10;
	obj1->Transform.Position.y = 0;


	GLObject* obj2 = new GLObject();
	obj2->Transform.Scale.x = 1;
	obj2->Transform.Scale.y = 1;
	obj2->Transform.Scale.z = 1;
	objects.push_back(obj2);
	Renderer3D* renderer2 = new Renderer3D(displayEvent, obj2);
	renderer2->SetTexture(image2);
	renderer2->objectMeshes = meshes;
	renderer2->color = GlutColor(0, 128, 128, 1);
	obj2->render3D = renderer2;
	obj2->Transform.Position.x = 10;
	obj2->Transform.Position.z = -10;
	obj2->Transform.Position.y = 0;

	

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

	rotationX += .5f;
	if (rotationX >= 360.0f)
		rotationX = 0.0f;	
}

void Main::Display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	ReBuildProjectionMatrix();

	for (size_t i = 0; i < 5; i++)
	{
		for (size_t j = 0; j < 5; j++)
		{
			for (size_t k = 0; k < 5; k++)
			{
				glPushMatrix();
				glTranslatef(i * 10, j * 10, k * 10);
				glutSolidCube(1);
				glPopMatrix();
			}
		}
	}

	displayEvent->FireEvent();

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

	//if (key == 'w')
	//{
	//	ReBuildProjectionMatrix();
	//}
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

	if (buffer[(int)'p'])
	{
		//static float angle = 0;
		//angle += 0;
		//cameraTransform.Rotation = Vector3(0, 1, 0) * ToRad(angle);

		Vector3 posZ = Vector3( 0,0,1 );
		posZ.RotateAroundAxis(Vector3(0, 1, 0), ToRad(90));
		std::cout << posZ.RotateAroundAxis(Vector3(0, 1, 0), ToRad(90)).ToString();
	}


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





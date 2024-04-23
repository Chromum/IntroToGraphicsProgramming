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
	//glutInitContextProfile(GLUT_CORE_PROFILE);
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
	gluPerspective(45, 1, 0.01, 1000);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	cameraTransform.Position.x = 5;
	cameraTransform.Position.y = -10;
	cameraTransform.Position.z = 10;
	gluLookAt(cameraTransform.Position.x, cameraTransform.Position.y, cameraTransform.Position.z, 0, 0, 0, 0, 1, 0);

	

	ModelLoader ml = ModelLoader();
	ImageReader image = ImageReader();

	//Mesh* mesh = ml.LoadMeshAtPath("Models/ShittyQuadTest.obj");
	//std::cout << "gfdg";
	std::vector<Mesh*> meshes = ml.LoadMeshAtPath("Models/untitled.obj");
	GLuint image2 = image.ReadImage("Models/untitled.png");

	GLObject* obj1 = new GLObject();
	obj1->Transform.Scale.x = .1f;
	obj1->Transform.Scale.y = .1f;
	obj1->Transform.Scale.z = .1f;
	objects.push_back(obj1);
	Renderer3D* renderer1 = new Renderer3D(displayEvent, obj1);
	renderer1->SetTexture(image2);
	renderer1->objectMeshes = meshes;
	renderer1->color = GlutColor(0, 128, 128, 1);
	obj1->render3D = renderer1;
	obj1->Transform.Position.x = 0;
	obj1->Transform.Position.z = 0;
	obj1->Transform.Position.y = -10;

	GLObject* obj2 = new GLObject();
	obj2->Transform.Scale.x = .1f;
	obj2->Transform.Scale.y = .1f;
	obj2->Transform.Scale.z = .1f;
	objects.push_back(obj2);
	Renderer3D* renderer2 = new Renderer3D(displayEvent, obj2);
	renderer2->SetTexture(image2);
	renderer2->objectMeshes = meshes;
	renderer2->color = GlutColor(0, 128, 128, 1);
	obj2->render3D = renderer2;
	obj2->Transform.Position.x = 10;
	obj2->Transform.Position.z = 0;
	obj2->Transform.Position.y = 0;

	GLObject* obj3 = new GLObject();
	obj3->Transform.Scale.x = 1;
	obj3->Transform.Scale.y = 1;
	obj3->Transform.Scale.z = 1;
	objects.push_back(obj3);
	Renderer3D* renderer3 = new Renderer3D(displayEvent, obj3);
	renderer3->SetTexture(image2);
	renderer3->objectMeshes = meshes;
	renderer3->color = GlutColor(0, 128, 128, 1);
	obj3->render3D = renderer3;
	obj3->Transform.Position.x = -10;
	obj3->Transform.Position.z = 0;
	obj3->Transform.Position.y = 0;

	GLObject* obj4 = new GLObject();
	obj4->Transform.Scale.x = 1;
	obj4->Transform.Scale.y = 1;
	obj4->Transform.Scale.z = 1;
	objects.push_back(obj4);
	Renderer3D* renderer4 = new Renderer3D(displayEvent, obj4);
	renderer4->SetTexture(image2);
	renderer4->objectMeshes = meshes;
	renderer4->color = GlutColor(0, 128, 128, 1);
	obj4->render3D = renderer4;
	obj4->Transform.Position.x = 0;
	obj4->Transform.Position.z = 0;
	obj4->Transform.Position.y = 10;

	

	glutMainLoop();
}

//Deconstruct
Main::~Main(void)
{
}

void Main::Update()
{
	//double lastTime = glutGet(GLUT_ELAPSED_TIME);
	//int nbFrames = 0;

	//do
	//{

	//	// Measure speed
	//	double currentTime = glutGet(GLUT_ELAPSED_TIME);
	//	nbFrames++;
	//	if (currentTime - lastTime >= 1.0) { // If last prinf() was more than 1 sec ago
	//		// printf and reset timer
	//		printf("%f ms/frame\n", 1000.0 / double(nbFrames));
	//		nbFrames = 0;
	//		lastTime += 1.0;
	//	}


	//	glutPostRedisplay();
	//	HandleInput();
	//	ReBuildProjectionMatrix();

	//	rotationX += .5f;
	//	if (rotationX >= 360.0f)
	//		rotationX = 0.0f;

	//	//rotationY += .1f;
	//	//if (rotationY >= 360.0f)
	//	//	rotationY = 0.0f;

	//	//rotationZ += .1f;
	//	//if (rotationZ >= 360.0f)
	//	//	rotationZ = 0.0f;


	//	for (size_t i = 0; i < objects.size(); i++)
	//	{
	//		objects[i]->Transform.Rotation.x = rotationX;
	//		objects[i]->Transform.Rotation.y = rotationY;
	//		objects[i]->Transform.Rotation.z = rotationZ;
	//	}
	//} while (buffer[(int)'p'] == true);
	// Measure speed




	glutPostRedisplay();
	HandleInput();
	//ReBuildProjectionMatrix();

	rotationX += .5f;
	if (rotationX >= 360.0f)
		rotationX = 0.0f;

	//rotationY += .1f;
	//if (rotationY >= 360.0f)
	//	rotationY = 0.0f;

	//rotationZ += .1f;
	//if (rotationZ >= 360.0f)
	//	rotationZ = 0.0f;


	//for (size_t i = 0; i < objects.size(); i++)
	//{
	//	objects[i]->Transform.Rotation.x = rotationX;
	//	objects[i]->Transform.Rotation.y = rotationY;
	//	objects[i]->Transform.Rotation.z = rotationZ;
	//}
	
	
}

void Main::Display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//GL3D* gl3d = new GL3D;
	//gl3d->DrawCubeRotate(rotationX,rotationY,rotationZ);
	glPushMatrix();
	glTranslatef(0, 0, 0);
	glutSolidCube(1);
	glPopMatrix();


	//displayEvent->FireEvent();

	ReBuildProjectionMatrix();



	//glActiveTexture()
	glFlush();


	//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//// Set up modelview and projection matrices (e.g., using gluLookAt and gluPerspective)

	//// Bind the texture
	//glEnable(GL_TEXTURE_2D);
	//glBindTexture(GL_TEXTURE_2D, objects[0]->render3D->texture);

	//// Draw your 3D model (e.g., using glBegin/glEnd or vertex arrays)
	//glBegin(GL_TRIANGLES);
	//glTexCoord2f(0, 0);
	////glColor3f(0, 0, 0);
	//glVertex3f(0,0, 0);


	//glTexCoord2f(1, 1);
	////glColor3f(1, 1, 0);
	//glVertex3f(1, 1, 0);

	//glTexCoord2f(1, 0);
	////glColor3f(1, 0, 0);
	//glVertex3f(1, 0, 0);


	//glTexCoord2f(0, 0);
	////glColor3f(0, 0, 0);
	//glVertex3f(0, 0, 0);

	//glTexCoord2f(0, 1);
	////glColor3f(0, 1, 0);
	//glVertex3f(0, 1, 0);

	//glTexCoord2f(1, 1);
	////glColor3f(1, 1, 0);
	//glVertex3f(1, 1, 0);


	//glDisable(GL_TEXTURE_2D);
	//glEnd();

	 //Swapbuffers (if using double buffering)
	glutSwapBuffers();

}

void Main::KeyboardDown(unsigned char key, int x, int y)
{

	buffer[key] = true;
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
	int forward = buffer['w'] - buffer['s'];
	int horizontal = buffer['a'] - buffer['d'];
	int vertical = buffer['q'] - buffer['e'];

	inputVector = Vector3(horizontal, vertical, forward);
	//if(buffer['s'])
	//	std::cout << inputVector.ToString();
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
	/*glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluPerspective(45, 1, 0.01, 1000);
	*/
	
	
	//if (rightMouse)
	//{
	//	cameraTransform.Rotation.y += mouseDelta.x * .01f;
	//	cameraTransform.Rotation.x += mouseDelta.y * .01f;
	//}
	//cameraTransform.Rotation.y += mouseDelta.y * .1f;
	//cameraTransform.Rotation.x += mouseDelta.x * .1f;

	
	
	//Vector3 relMove = Vector3(
	//	cos(ToRad(yaw)) * -inputVector.z - sin(ToRad(pitch)) * inputVector.x,
	//	inputVector.y,
	//	sin(ToRad(yaw)) * -inputVector.z + cos(ToRad(pitch)) * inputVector.x
	//);

	//relMove = relMove + (cameraFront * inputVector);

	////std::cout << relMove.ToString();

	//cameraTransform.Position.x += relMove.x/2;
	//cameraTransform.Position.y += relMove.y/2;
	//cameraTransform.Position.z += relMove.z/2;

	
	Vector3 cameraUp = Vector3(0.0f, 1.0f, 0.0f);
	
	lookDirection = (atVector - cameraTransform.Position);
	atVector = cameraTransform.Position + lookDirection;
	forwardDirection = lookDirection;// (cameraTransform.Position + atVector);

	cameraTransform.Position = cameraTransform.Position + (forwardDirection.Normilized()* inputVector.z);
	atVector = (atVector + (forwardDirection.Normilized() * inputVector.z));


	glutPostRedisplay();

	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	gluLookAt(
		cameraTransform.Position.x,
		cameraTransform.Position.y,
		cameraTransform.Position.z,

		atVector.x + cameraTransform.Rotation.x,
		atVector.y + cameraTransform.Rotation.y,
		atVector.z + cameraTransform.Rotation.z,

		cameraUp.x,
		cameraUp.y,
		cameraUp.z);


	

	//relMove = Vector3(.0f,.0f,.0f);
}





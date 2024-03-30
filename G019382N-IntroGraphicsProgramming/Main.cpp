#include "Main.h"
#include "Constants.h"
#include "GLUTUtils.h"
#include "ModelLoader.h"
#include "ImageReader.h"
#include "Image.h"

Transform cameraTransform;


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
	//glutFullScreen();
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	ReBuildProjectionMatrix();

	ModelLoader ml = ModelLoader();
	ImageReader image = ImageReader();

	//Mesh* mesh = ml.LoadMeshAtPath("Models/ShittyQuadTest.obj");
	//std::cout << "gfdg";
	GLObject* obj2 = new GLObject();
	obj2->Transform.Scale.x = 0.1f;
	obj2->Transform.Scale.y = 0.1f;
	obj2->Transform.Scale.z = 0.1;
	objects.push_back(obj2);
	Renderer3D* renderer2 = new Renderer3D(displayEvent, obj2);
	GLuint i = image.ReadImage("Models/PINTURA_01.1001.jpg");
	renderer2->SetTexture(i);
	renderer2->objectMeshes = ml.LoadMeshAtPath("Models/PINTURA_01.obj");
	renderer2->color = GlutColor(0, 128, 128,1);
	obj2->render3D = renderer2;
	obj2->Transform.Position.z = -6;
	obj2->Transform.Position.y = -1;
	

	glutMainLoop();
}

//Deconstruct
Main::~Main(void)
{
}

void Main::Update()
{
	double lastTime = glutGet(GLUT_ELAPSED_TIME);
	int nbFrames = 0;

	do
	{

		// Measure speed
		double currentTime = glutGet(GLUT_ELAPSED_TIME);
		nbFrames++;
		if (currentTime - lastTime >= 1.0) { // If last prinf() was more than 1 sec ago
			// printf and reset timer
			printf("%f ms/frame\n", 1000.0 / double(nbFrames));
			nbFrames = 0;
			lastTime += 1.0;
		}


		glutPostRedisplay();
		HandleInput();
		ReBuildProjectionMatrix();

		rotationX += .5f;
		if (rotationX >= 360.0f)
			rotationX = 0.0f;

		//rotationY += .1f;
		//if (rotationY >= 360.0f)
		//	rotationY = 0.0f;

		//rotationZ += .1f;
		//if (rotationZ >= 360.0f)
		//	rotationZ = 0.0f;


		for (size_t i = 0; i < objects.size(); i++)
		{
			objects[i]->Transform.Rotation.x = rotationX;
			objects[i]->Transform.Rotation.y = rotationY;
			objects[i]->Transform.Rotation.z = rotationZ;
		}
	} while (buffer[(int)'p'] == true);
	
	
	
}

void Main::Display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//GL3D* gl3d = new GL3D;
	//gl3d->DrawCubeRotate(rotationX,rotationY,rotationZ);

	displayEvent->FireEvent();
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
}

void Main::HandleInput()
{
	if (buffer[(int)'w'] == true)
		cameraTransform.Position.z += .1f;
	if (buffer[(int)'s'] == true)
		cameraTransform.Position.z -= .1f;

	if (buffer[(int)'d'] == true)
		cameraTransform.Position.x -= .1f;
	if (buffer[(int)'a'] == true)
		cameraTransform.Position.x += .1f;


	if (buffer[(int)'0'] == true)
		objects[0]->Transform.Position.x += 0.1f;
	if (buffer[(int)'1'] == true)
		objects[0]->Transform.Position.x -= 0.1f;

	if (buffer[(int)'2'] == true)
		objects[0]->Transform.Position.y += 0.1f;
	if (buffer[(int)'9'] == true)
		objects[0]->Transform.Position.y -= 0.1f;

	if (buffer[(int)'3'] == true)
		objects[0]->Transform.Position.z += 0.1f;
	if (buffer[(int)'8'] == true)
		objects[0]->Transform.Position.z -= 0.1f;

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
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	float _near = 0.1f;
	float _far = 500.0f;

	float tangent = tanf(45 / 2 * 3.14159 / 180);   // tangent of half fovY
	float height = _near * tangent;           // half height of near plane
	float width = height * screenWidth / screenHeight;       // half width of near plane
	// params: left, right, bottom, top, near, far
	glFrustum(-width, width, -height, height, _near, _far);

	

	if (rightMouse)
	{
		cameraTransform.Rotation.y += mouseDelta.x * .01f;
		cameraTransform.Rotation.x += mouseDelta.y * .01f;
	}
	//cameraTransform.Rotation.y += mouseDelta.y * .1f;
	//cameraTransform.Rotation.x += mouseDelta.x * .1f;

	glTranslatef(cameraTransform.Position.x, cameraTransform.Position.y, cameraTransform.Position.z);
	glRotatef(cameraTransform.Rotation.y, 1.0f, 0, 0);
	glRotatef(cameraTransform.Rotation.x, 0, 1.0f, 0);
	//glRotatef(cameraTransform.Rotation.z, 0, 0, 1.0f);
	glMatrixMode(GL_MODELVIEW);


}





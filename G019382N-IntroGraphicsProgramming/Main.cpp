#include "Main.h"
#include "Constants.h"
#include "GLUTUtils.h"
#include "ModelLoader.h"
#include "ImageReader.h"
#include "Image.h"
#include "Sphere.h"
#include "LightingManager.h"
#include <chrono>
#include "Camera.h"
#include "LinkedList.h"
#include "SceneManager.h"

SceneObject* rootLevelObject;

int main(int argc, char* argv[])
{
	Main* game = new Main(argc, argv);

	delete game;

	return 0;
}

GLObject* obj11;

//Construct
Main::Main(int argc, char* argv[])
{
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
	glutTimerFunc(8, GLUTCallbacks::Timer, 8);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glutKeyboardFunc(GLUTCallbacks::KeyboardKeyDown);
	glutKeyboardUpFunc(GLUTCallbacks::KeyboardKeyUp);
	glutMouseFunc(GLUTCallbacks::MouseClick);
	glutMotionFunc(GLUTCallbacks::MouseMove);
	glutReshapeFunc(GLUTCallbacks::OnWindowResize);
	glutFullScreen();
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glViewport(0, 0, screenWidth, screenHeight);
	gluPerspective(110, ((float)screenWidth / (float)screenHeight), 0.01, 10000);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	
	SceneManager();
	Camera* cam = new Camera("Camera");
	SceneManager::instance->CreateNewObject(cam);
	



	ModelLoader ml = ModelLoader();
	int i = ImageReader().ReadImage("Models/Untitled.png");

	std::vector<Mesh*> meshes = ml.LoadMeshAtPath("Models/Model1.obj");
	std::vector<Mesh*> meshes3 = ml.LoadMeshAtPath("Models/plane.obj");
	std::vector<Mesh*> meshes2 = ml.LoadMeshAtPath("Models/SkyboxCube.obj");

	GLObject* obj1 = new GLObject("Test Model", Vector3(0, 0, 0), Vector3(1, 1, 1), meshes, displayEvent,1);
	GLObject* obj10 = new GLObject("Skybox", Vector3(0, 0, 0), Vector3(2, 2, 2), meshes2, displayEvent,1);
	obj11 = new GLObject("Plane", Vector3(0,0,0), Vector3(1, 1, 1), meshes3, displayEvent,5);
	SceneManager::instance->skyboxId1 = obj10->render3D->objectMeshes[0]->texture;

	SceneManager::instance->CreateNewObject(obj11);
	SceneManager::instance->CreateNewObject(obj10);
	SceneManager::instance->CreateNewObject(obj1,obj10);

	std::string name = SceneManager::instance->FindObject("Test Model")->name;
	std::cout << name;

	LightingManager();
	LightingManager::instance->AddLight(
		Vector4(0,0,0,0),
		Vector4(5.2f,5.2f,5.2f,5.0f),
		Vector4(0.8f, 0.8f,0.8f,1.0f),
		Vector4(0.2f,0.2f,0.2,1.0f)
	);

	glutMainLoop();
}



//Deconstruct
Main::~Main(void)
{
}

// Global variables
int frameCount = 0;
int currentTime = 0;
int previousTime = 0;
int fps;

void Main::Update()
{
	glutPostRedisplay();
	HandleInput();	
}

void Main::Display()
{
	frameCount++;

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	Camera::instance->Update();

	drawLine(startPoint, endPoint);

	//Vector3 rot = SceneManager::instance->FindObject("Plane")->Transform.Rotation;
	//SceneManager::instance->FindObject("Plane")->Transform.Rotation = rot + Vector3(1, 1, 1);

	SceneManager::instance->sceneGraph->graph->UpdateNodes(SceneManager::instance->sceneGraph->graph->head);
	displayEvent->FireEvent();

	DrawHUD();

	LightingManager::instance->RenderAllLights();
	glFlush();
	glutSwapBuffers();
}

void Main::KeyboardDown(unsigned char key, int x, int y)
{

	buffer[key] = true;
	if(key == 'm')
		SceneManager::instance->ToggleSkyboxTexture();
	if (key == 'n')
		SceneManager::instance->ToggleWireFrame();

	if (key == 27)
		SceneManager::instance->ToggleControls();

}

void Main::KeyboardUp(unsigned char key, int x, int y)
{
	buffer[key] = false;
}

void Main::HandleInput()
{
	if (buffer[(int)'w'])
	{
		Camera::instance->Transform.Position = Camera::instance->Transform.Position + Camera::instance->cameraForward * 1;
	}
	if (buffer[(int)'s'])
	{
		Camera::instance->Transform.Position = Camera::instance->Transform.Position - Camera::instance->cameraForward * 1;
	}

	if (buffer[(int)'a'])
	{
		Vector3 rVec = Vector3(0, 1, 0).Cross(Camera::instance->cameraForward).Normilized();
		Camera::instance->Transform.Position = Camera::instance->Transform.Position + rVec * 1;
	}
	if (buffer[(int)'d'])
	{
		Vector3 rVec = Vector3(0, 1, 0).Cross(Camera::instance->cameraForward).Normilized();
		Camera::instance->Transform.Position = Camera::instance->Transform.Position - rVec * 1;
	}

	if (buffer[(int)'u'])
		obj11->Transform.Position.x += 1;

	return;
}

void Main::drawLine(Vector3 startPoint, Vector3 endPoint) {
	glBegin(GL_LINES);
	glVertex3f(startPoint.x, startPoint.y, startPoint.z);
	glVertex3f(endPoint.x, endPoint.y, endPoint.z);
	glEnd();
}

void Main::DrawHUD()
{
	glDisable(GL_LIGHTING);
	glDisable(GL_LIGHT0);
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	gluOrtho2D(0, screenWidth, 0, screenHeight);
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
	
	glColor3f(1.0f, 1.0f, 1.0f);
	// Draw a circle at the center of the screen
	glBegin(GL_LINE_LOOP);
	for (int i = 0; i < 360; ++i) {
		float angle = i * 3.14159f / 180.0f;
		float x = screenWidth / 2 + 2 * cos(angle);
		float y = screenHeight / 2 + 2 * sin(angle);
		glVertex2f(x, y);
	}
	glEnd();

	DrawTextAtPos(("Object Count: " + std::to_string(SceneManager::instance->objectCount)).c_str(), Vector2(100, 125));

	// Calculate elapsed time
	currentTime = glutGet(GLUT_ELAPSED_TIME);
	int elapsedTime = currentTime - previousTime;

	// Update FPS every second
	if (elapsedTime > 1000) {
		fps = static_cast<int>(frameCount) / (elapsedTime / 1000.0f);

		// Reset counters
		frameCount = 0;
		previousTime = currentTime;
	}
	DrawTextAtPos(("FPS: " + std::to_string(fps)).c_str(), Vector2(100, 100));

	if(SceneManager::instance->showControls)
		DrawControlUI();


	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
}

void Main::DrawControlUI()
{
	DrawTextAtPos("M - Change Skybox", Vector2(25, 500));
	DrawTextAtPos("WASD - Move", Vector2(25, 525));
	DrawTextAtPos("Right Click - Unlock Free-Cam", Vector2(25, 550));
	DrawTextAtPos("N - Toggle Wireframe", Vector2(25, 575));
	DrawTextAtPos("Left Click - Select Object", Vector2(25, 600));
	DrawTextAtPos("F - Focus Object", Vector2(25, 625));
	DrawTextAtPos("ESC - Show Controls", Vector2(25, 650));
	DrawTextAtPos("B - Toggle Selection Spheres", Vector2(25, 675));
}

void Main::DrawTextAtPos(const char* text, Vector2 pos) {
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, 0);
	glColor3f(1, .75f, .8f);
	glRasterPos2f(pos.x,pos.y);
	glutBitmapString(GLUT_BITMAP_8_BY_13, (unsigned char*)text);
	glPopMatrix();
}





#include "Main.h"
#include "Constants.h"
#include "GLUTUtils.h"
#include "ModelLoader.h"
#include "ImageReader.h"
#include "Image.h"
#include "Sphere.h"
#include "LightingManager.h"
#include <chrono>
#include "Plane.h"

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
	//glutFullScreen();
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glViewport(0, 0, screenWidth, screenHeight);
	gluPerspective(110, ((float)screenWidth / (float)screenHeight), 0.01, 10000);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	
	SceneManager();
	SceneManager::instance->Renderables = std::vector<GLObject*>();
	Camera* cam = new Camera("Camera");
	SceneManager::instance->CreateNewObject(cam); 
	SceneManager::instance->Renderables = std::vector<GLObject*>();



	ModelLoader ml = ModelLoader();
	int i = ImageReader().ReadImage("Models/Untitled.png");

	std::vector<Mesh*> meshes = ml.LoadMeshAtPath("Models/Model1.obj");
	std::vector<Mesh*> meshes3 = ml.LoadMeshAtPath("Models/plane.obj");
	std::vector<Mesh*> meshes2 = ml.LoadMeshAtPath("Models/SkyboxCube.obj");
	std::vector<Mesh*> meshes4 = ml.LoadMeshAtPath("Models/building.obj");
	std::vector<Mesh*> meshes5 = ml.LoadMeshAtPath("Models/Floor.obj");
	std::vector<Mesh*> meshes6 = ml.LoadMeshAtPath("Models/Man.obj");



	GLObject* obj2 = new GLObject("Building01", Vector3(-38.8824501, -0.0678701401, 56.9566116),Vector3(0,0,0), Vector3(1, 1, 1), meshes4, displayEvent, 1);
	GLObject* obj4 = new GLObject("Building02", Vector3(-38.8835144, -0.0678701401, -3.58601379), Vector3(0, 0, 0), Vector3(1, 1, 1), meshes4, displayEvent, 1);
	GLObject* obj3 = new GLObject("Floor", Vector3(-20, 0, 0), Vector3(0, 0, 0), Vector3(1, 1, 1), meshes5, displayEvent, 1);
	GLObject* obj1 = new GLObject("Test Model", Vector3(23.3199997, -0.0840089321, 62.2700005), Vector3(-240, 0, 0), Vector3(1, 1, 1), meshes, displayEvent,1);
	GLObject* obj10 = new GLObject("Skybox", Vector3(0, 1, 0), Vector3(0, 0, 0), Vector3(2,2,2), meshes2, displayEvent,1);
	Plane* obj11 = new Plane("Plane", Vector3(100.6, 80.0, -102.2), Vector3(0, 0, 0), Vector3(3, 3, 3), meshes3, displayEvent,3);

	GLObject* objRoot = new GLObject("Man", Vector3(0, 1, 0), Vector3(0, 0, 0), Vector3(2,2,2), meshes6, displayEvent, .1f);

	for (size_t i = 0; i < 6; i++)
	{
		for (size_t j = 0; j < 6; j++)
		{
			SceneManager::instance->CreateNewObject(new GLObject("Man" + (i+j), Vector3(i+1, 1, j+1), Vector3(0, 0, 0), Vector3(2,2,2), meshes6, displayEvent, .1f), objRoot);
		}
	}

	GLObject* objMan = new GLObject("Man", Vector3(0, 1, 0), Vector3(0, 0, 0), Vector3(1,1,1), meshes6, displayEvent, 1);
	SceneManager::instance->skyboxId1 = obj10->render3D->objectMeshes[0]->texture;

	SceneManager::instance->CreateNewObject(obj11);
	SceneManager::instance->CreateNewObject(obj10);
	SceneManager::instance->CreateNewObject(obj1);
	SceneManager::instance->CreateNewObject(obj2);
	SceneManager::instance->CreateNewObject(obj3);
	SceneManager::instance->CreateNewObject(obj4);
	SceneManager::instance->CreateNewObject(objMan);
	SceneManager::instance->selectedObject = obj10;

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
	auto timeNow = std::chrono::high_resolution_clock::now();
	glutPostRedisplay();
	HandleInput();	
	auto timeAfter = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(timeAfter - timeNow);

	SceneManager::instance->deltaTime = duration.count() / 1000.0f;
}

void Main::Display()
{
	frameCount++;

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	Camera::instance->Update();

	for (size_t i = 0; i < SceneManager::instance->Renderables.size(); i++)
	{
		SceneManager::instance->Renderables[i]->Update();
	}

	//Draw Lines to all objects
	//for (size_t i = 0; i < SceneManager::instance->debugLines.size(); i++)
	//{
	//	drawLine(SceneManager::instance->debugLines[i].first, SceneManager::instance->debugLines[i].second);

	//}

	drawLine(Camera::instance->Transform.Position + Vector3(0.1f,0.1f,.01f), SceneManager::instance->Renderables[0]->Transform.Position);

	displayEvent->FireEvent();

	DrawHUD();

	LightingManager::instance->RenderAllLights();
	glFlush();
	glutSwapBuffers();
}

void Main::KeyboardDown(unsigned char key, int x, int y)
{
	std::cout << (int)key;

	buffer[key] = true;
	if(key == 'm')
		SceneManager::instance->ToggleSkyboxTexture();
	if (key == 'n')
		SceneManager::instance->ToggleWireFrame();

	if (key == 27)
		SceneManager::instance->ToggleControls();

	if (key == 'f')
	{
		if (Camera::instance->targetObjectToFollow == nullptr)
			Camera::instance->targetObjectToFollow = SceneManager::instance->selectedObject;
		else
			Camera::instance->targetObjectToFollow = nullptr;
	}

	if (key == 'p')
	{
		Plane* p = dynamic_cast<Plane*>(SceneManager::instance->FindObject("Plane"));
		p->moving = !p->moving;
	}

}

void Main::KeyboardUp(unsigned char key, int x, int y)
{
	buffer[key] = false;
}

void Main::HandleInput()
{

	//Camera Movement
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

	//Selected Object Movement

	if (buffer[(int)'i'])
	{
		SceneManager::instance->selectedObject->Transform.Position.x += 1;
	}
	if (buffer[(int)'k'])
	{
		SceneManager::instance->selectedObject->Transform.Position.x -= 1;
	}

	if (buffer[(int)'l'])
	{
		SceneManager::instance->selectedObject->Transform.Position.z += 1;
	}
	if (buffer[(int)'j'])
	{
		SceneManager::instance->selectedObject->Transform.Position.z -= 1;
	}

	if (buffer[(int)'o'])
	{
		SceneManager::instance->selectedObject->Transform.Position.y += 1;
	}
	if (buffer[(int)'u'])
	{
		SceneManager::instance->selectedObject->Transform.Position.y -= 1;
	}

	//Selected Object Rotation

	static int rotAxis = 0; // 0 = x | 1 = y | 2 = z

	if (buffer[8]) //backspace
	{
		if (rotAxis == 0)
			rotAxis = 1;
		else if (rotAxis == 1)
			rotAxis = 2;
		else
			rotAxis = 0;
	}

	if (buffer[(int)'-'])
	{
		switch (rotAxis)
		{
		case 0: SceneManager::instance->selectedObject->Transform.Rotation.x += 1; break;
		case 1: SceneManager::instance->selectedObject->Transform.Rotation.y += 1; break;
		case 2: SceneManager::instance->selectedObject->Transform.Rotation.z += 1; break;
		}
	}

	if (buffer[(int)'='])
	{
		switch (rotAxis)
		{
		case 0: SceneManager::instance->selectedObject->Transform.Rotation.x -= 1; break;
		case 1: SceneManager::instance->selectedObject->Transform.Rotation.y -= 1; break;
		case 2: SceneManager::instance->selectedObject->Transform.Rotation.z -= 1; break;
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

	if (SceneManager::instance->selectedObject->name != "")
		DrawTextAtPos(("Current Object: " + SceneManager::instance->selectedObject->name).c_str(), Vector2(100, 75));
	else
		DrawTextAtPos(("Current Object: NULL"), Vector2(100, 75));



	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
}

void Main::DrawControlUI()
{
	DrawTextAtPos("Camera Controls", Vector2(25, 825));
	DrawTextAtPos("ESC - Show Controls", Vector2(25, 800));
	DrawTextAtPos("WASD - Move", Vector2(25, 775));
	DrawTextAtPos("Right Click - Unlock Free-Cam", Vector2(25, 750));
	DrawTextAtPos("Left Click - Select Object", Vector2(25, 725));
	DrawTextAtPos("F - Focus Object", Vector2(25, 700));
	DrawTextAtPos("Selected Object Controls", Vector2(25, 675));
	DrawTextAtPos("IJKL - Move Selected Object", Vector2(25, 650));
	DrawTextAtPos("Backspace - Change Rotation Axis", Vector2(25, 625));
	DrawTextAtPos("- & = - Rotate Objects", Vector2(25, 600));
	DrawTextAtPos("Misc Controls", Vector2(25, 575));
	DrawTextAtPos("M - Change Skybox", Vector2(25, 550));
	DrawTextAtPos("N - Toggle Wireframe", Vector2(25, 525));
	DrawTextAtPos("B - Toggle Selection Spheres", Vector2(25, 500));
	DrawTextAtPos("P - Start/Stop Planes", Vector2(25, 475));
}

void Main::DrawTextAtPos(const char* text, Vector2 pos) {
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, 0);
	glColor3f(1, .75f, .8f);
	glRasterPos2f(pos.x,pos.y);
	glutBitmapString(GLUT_BITMAP_8_BY_13, (unsigned char*)text);
	glPopMatrix();
}

void Main::SelectObject(float x, float y) {
	std::pair<Vector3,Vector3> e = SceneManager::instance->SelectObject(x,y);

	startPoint = e.first;
	endPoint = e.second;

}





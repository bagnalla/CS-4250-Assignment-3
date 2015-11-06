#include "Angel.h"
#include "Game.h"
#include "Line.h"
#include "FpsTracker.h"
#include "Wheel.h"
#include "Util.h"
#include "World.h"
#include "WorldTile.h"
#include "Track.h"
#include "Cart.h"
#include "Cube.h"
#include "Sphere.h"
#include "Coaster.h"
#include "Person.h"
#include "Sun.h"
#include "Camera.h"
#include "PathFinder.h"
#include "Bush.h"
#include "TrashCan.h"
#include "LightSource.h"
#include <time.h>

using namespace Bagnall;

GLuint vao; // vertex array object pointer
GLuint buffer; // vertex buffer object pointer

Coaster *coaster = NULL;
Sun *sn = NULL;
Camera *camera = NULL;
float trackZFactor = 19.9;
int numofCarts = 10;

void createWorld()
{
	TrashCan::ClearTrashCans();
	Bush::ClearBushes();
	delete Game::GameWorld;
	delete sn;

	Game::GameWorld = new World(17, 17, trackZFactor);

	for (int i = 0; i < 50; i++)
		new Bush(rand() % 2 ? Bagnall::BUSH_TYPE_ROUND : Bagnall::BUSH_TYPE_SWIRLY);

	Game::GameWorld->AssignSegmentNumbers();

	std::map<int, std::vector<WorldTile*> > segments = Game::GameWorld->Segments;
	for (std::map<int, std::vector<WorldTile*> >::iterator it = segments.begin(); it != segments.end(); it++)
	{
		if ((*it).second.size() > 1)
		{
			TrashCan *trashCan = new TrashCan();
			trashCan->SetRandomLocationInSegment((*it).second);
		}
	}

	Game::GameWorld->AssignSegmentNumbers();

	sn = new Sun(vec4(1.0, 0.8, 0.0, 1.0), 0.0005);
}

void createPeople()
{
	Person::ClearPeople();

	for (int i = 0; i < 10; i++)
	{
		Person *person = new Person();
		person->Scale(0.5);
		person->Translate(vec4(0.0, 0.0, -1.0, 0.0));
		person->RandomizePosition();
		person->ChooseNewDestination();
	}
}

void createCoaster()
{
	delete coaster;

	coaster = new Coaster(Game::GameWorld->GetTrack(), 0.0025);

	for (int i = 0; i < numofCarts; i++)
		coaster->AddCart();

	if (camera != NULL)
		camera->SetCoaster(coaster);
}

void createCamera()
{
	if (camera == NULL)
	{
		camera = new Camera();
		camera->SetMode(CAMERA_MODE_COASTER);
	}

	if (coaster != NULL)
		camera->SetCoaster(coaster);
}

void createEverything(bool firstTime)
{
	Game::Vertices.clear();
	Game::Normals.clear();

	// initialize classes
	Line::Init();
	Cube::Init();
	Sphere::Init();
	Wheel::Init();
	WorldTile::Init();
	Bush::Init();
	TrashCan::Init();
	LightSource::Init();

	createWorld();
	createPeople();
	createCoaster();
	createCamera();

	if (!firstTime)
	{
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vec4)*Game::Vertices.size(), &Game::Vertices[0]);
		glBufferSubData(GL_ARRAY_BUFFER, sizeof(vec4)*Game::Vertices.size(), sizeof(vec4)*Game::Normals.size(), &Game::Normals[0]);
	}
}

void init(void)
{
	// random seed
	srand(time(NULL));

	Material::Init();

	//createWorld();
	createEverything(true);

	auto sdfgdg = Game::Vertices;
	//auto dfgdfg = Game::Normals;

	// Create a vertex array object
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	// set up vertex buffer
	glGenBuffers(1, &buffer);
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vec4)*Game::Vertices.size() + sizeof(vec4)*Game::Normals.size(), NULL, GL_STATIC_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vec4)*Game::Vertices.size(), &Game::Vertices[0]);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(vec4)*Game::Vertices.size(), sizeof(vec4)*Game::Normals.size(), &Game::Normals[0]);

	// Load shaders and use the resulting shader program
	GLuint program = InitShader("vshader.glsl", "fshader.glsl");
	glUseProgram(program);

	// set up vertex arrays
	GLuint vPositionLoc = glGetAttribLocation(program, "vPosition");
	glEnableVertexAttribArray(vPositionLoc);
	glVertexAttribPointer(vPositionLoc, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));

	GLuint vNormalLoc = glGetAttribLocation(program, "vNormal");
	glEnableVertexAttribArray(vNormalLoc);
	glVertexAttribPointer(vNormalLoc, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(sizeof(vec4)*Game::Vertices.size()));

	// Initialize attributes from the vertex shader
	Game::WindowSizeLoc = glGetUniformLocation(program, "windowSize");
	if (Game::WindowSizeLoc == -1) {
		std::cerr << "Unable to find windowSizeLoc parameter" << std::endl;
	}
	Game::ColorLoc = glGetUniformLocation(program, "color");
	if (Game::ColorLoc == -1) {
		std::cerr << "Unable to find colorLoc parameter" << std::endl;
	}
	Game::ModelViewLoc = glGetUniformLocation(program, "modelView");
	if (Game::ModelViewLoc == -1) {
		std::cerr << "Unable to find modelViewloc parameter" << std::endl;
	}
	Game::CameraLoc = glGetUniformLocation(program, "camera");
	if (Game::CameraLoc == -1) {
		std::cerr << "Unable to find cameraLoc parameter" << std::endl;
	}
	Game::ProjectionLoc = glGetUniformLocation(program, "projection");
	if (Game::ProjectionLoc == -1) {
		std::cerr << "Unable to find projectionLoc parameter" << std::endl;
	}
	Game::CameraPositionLoc = glGetUniformLocation(program, "cameraPosition");
	if (Game::CameraPositionLoc == -1) {
		std::cerr << "Unable to find cameraPositionLoc parameter" << std::endl;
	}
	Game::LightPositionLoc = glGetUniformLocation(program, "lightPosition");
	if (Game::LightPositionLoc == -1) {
		std::cerr << "Unable to find lightPositionLoc parameter" << std::endl;
	}
	Game::AmbientProductLoc = glGetUniformLocation(program, "ambientProduct");
	if (Game::AmbientProductLoc == -1) {
		std::cerr << "Unable to find ambientProduct parameter" << std::endl;
	}
	Game::DiffuseProductLoc = glGetUniformLocation(program, "diffuseProduct");
	if (Game::DiffuseProductLoc == -1) {
		std::cerr << "Unable to find diffuseProductLoc parameter" << std::endl;
	}
	Game::SpecularProductLoc = glGetUniformLocation(program, "specularProduct");
	if (Game::SpecularProductLoc == -1) {
		std::cerr << "Unable to find specularProductLoc parameter" << std::endl;
	}
	Game::ShininessLoc = glGetUniformLocation(program, "shininess");
	if (Game::ShininessLoc == -1) {
		std::cerr << "Unable to find shininessLoc parameter" << std::endl;
	}
	Game::LightModelViewLoc = glGetUniformLocation(program, "lightModelView");
	if (Game::LightModelViewLoc == -1) {
		std::cerr << "Unable to find lightModelViewLoc parameter" << std::endl;
	}
	Game::EmissiveLoc = glGetUniformLocation(program, "emissive");
	if (Game::EmissiveLoc == -1) {
		std::cerr << "Unable to find emissiveLoc parameter" << std::endl;
	}
	Game::EmissionColorLoc = glGetUniformLocation(program, "emissionColor");
	if (Game::EmissionColorLoc == -1) {
		std::cerr << "Unable to find emissionColor parameter" << std::endl;
	}

	// enable z-buffer
	glEnable(GL_DEPTH_TEST);

	// enable MSAA
	glEnable(GL_MULTISAMPLE);
	glHint(GL_MULTISAMPLE_FILTER_HINT_NV, GL_NICEST);
	//glDisable(GL_MULTISAMPLE);

	// enable color transparency
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);

	// cornflower blue background
	glClearColor(100.0 / 255.0, 149.0 / 255.0, 237.0 / 255.0, 1.0);
	//glClearColor(0.0, 0.0, 0.0, 1.0);

	// set crosshair cursor
	glutSetCursor(GLUT_CURSOR_NONE);

	glLineWidth(2.0);
	//glPointSize(5.0);

	Game::Projection = Util::Perspective(45.0, 1.0, 1.0, Game::ViewDistance);
	glUniformMatrix4fv(Game::ProjectionLoc, 1, GL_TRUE, Game::Projection);

	// send light source position
	glUniform4fv(Game::LightPositionLoc, 1, LightSource::Default.position);

	// initialize emissive to false and set emission color to white
	glUniform1i(Game::EmissiveLoc, 0);

	Game::DebugMode = false;

	//glutFullScreen();
}

void drawEverything(bool select)
{
	Game::GameWorld->Draw();

	if (coaster != NULL)
		coaster->Draw();

	for (std::vector<Person*>::iterator it = Person::People.begin(); it != Person::People.end(); it++)
		(*it)->Draw();

	for (std::vector<Bush*>::iterator it = Bush::Bushes.begin(); it != Bush::Bushes.end(); it++)
		(*it)->Draw();

	for (std::vector<TrashCan*>::iterator it = TrashCan::TrashCans.begin(); it != TrashCan::TrashCans.end(); it++)
		(*it)->Draw();

	sn->Draw();

	/*glUniformMatrix4fv(Game::ModelViewLoc, 1, GL_TRUE, Angel::Translate(vec4(0.5, 0.5, -0.5, 0.0)));
	glDrawArrays(GL_TRIANGLE_STRIP, trackVertexOffset, track.size());*/
	//glDrawArrays(GL_LINES, pathVertexOffset, path.size());
}

extern "C" void display(void)
{
	// clear the window
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// draw all game objects normally
	drawEverything(false);

	// finish drawing
	glutSwapBuffers();
	glFlush();
}

extern "C" void myReshape(int w, int h)
{
	glViewport(0, 0, w, h);
	Game::WindowSize = vec2(w, h);
	glUniform2f(Game::WindowSizeLoc, w, h);       // Pass the window size
	//glLineWidth(h/256.0); // adjust line width

	// update projection to match aspect ratio of window
	Game::Projection = Util::Perspective(45.0, w / static_cast<float>(h), 1.0, Game::ViewDistance);
	glUniformMatrix4fv(Game::ProjectionLoc, 1, GL_TRUE, Game::Projection);

	glutPostRedisplay();
}

extern "C" void idle(void)
{
	FpsTracker::Update();
	Game::StatusMessage = "FPS: " + Util::ToString(FpsTracker::GetFps());
		//+ ". view distance: " + Util::ToString(Game::ViewDistance)
		//+ ". x: " + Util::ToString(player->mazePosition.x) + ", y: " + Util::ToString(player->mazePosition.y)
		//+ ". camera x: " + Util::ToString(camera->GetPosition().x) + ", y: " + Util::ToString(camera->GetPosition().y)
		//+ "person pos: " + Util::ToString(Person::People[0]->GetPosition().x) + ", " + Util::ToString(Person::People[0]->GetPosition().y) + ", " + Util::ToString(Person::People[0]->GetPosition().z);
	glutSetWindowTitle(Game::StatusMessage.c_str());

	camera->Update();

	Game::GameWorld->Update();

	if (coaster != NULL)
		coaster->Update();

	for (std::vector<Person*>::iterator it = Person::People.begin(); it != Person::People.end(); it++)
		(*it)->Update();

	for (std::vector<Bush*>::iterator it = Bush::Bushes.begin(); it != Bush::Bushes.end(); it++)
		(*it)->Update();

	for (std::vector<TrashCan*>::iterator it = TrashCan::TrashCans.begin(); it != TrashCan::TrashCans.end(); it++)
		(*it)->Update();

	sn->Update();

	// redisplay
	glutPostRedisplay();
}

extern "C" void mouseClick(int button, int state, int x, int y)
{
	if (state != GLUT_DOWN)
		return;

	/*if (button == GLUT_LEFT_BUTTON)
	{
		for (int i = 0; i < 1; i++)
		{
			createNewMaze();
		}
	}
	else
	{
	}*/
}

int oldMouseX, oldMouseY;
extern "C" void mouseMotion(int x, int y)
{
	camera->MouseMotion(x, y);

	if (x != Game::WindowSize.x / 2 || y != Game::WindowSize.y / 2)
		glutWarpPointer(Game::WindowSize.x / 2, Game::WindowSize.y / 2);
}

extern "C" void keyPress(unsigned char k, int x, int y)
{
	switch (k)
	{
	/*case '-':
		coaster->SetVelocity(coaster->GetVelocity() - 0.001);
		break;
	case '=':
		coaster->SetVelocity(coaster->GetVelocity() + 0.001);
		break;*/
	// change game speed
	case '-': case '_':
		Game::GameSpeed = std::max(0.0, Game::GameSpeed - 0.1);
		break;
	case '=': case '+':
		Game::GameSpeed = Game::GameSpeed + 0.1;
		break;
	case ',':
		numofCarts = std::max(numofCarts - 1, 0);
		coaster->RemoveCart();
		break;
	case '.':
		numofCarts++;
		coaster->AddCart();
		break;
	/*case 'f':
		Game::FreeMode = !Game::FreeMode;
		break;*/
	case 'r':
		createEverything(false);
		break;
	case '/':
		Game::DebugMode = !Game::DebugMode;
		break;
	// EXIT
	case 033:
		exit(EXIT_SUCCESS);
		break;
	}

 	camera->KeyPress(k, x, y);
}

extern "C" void keyUp(unsigned char k, int x, int y)
{
	camera->KeyUp(k, x, y);
}

extern "C" void specialKeyPress(int k, int x, int y)
{
	camera->SpecialKeyPress(k, x, y);

	switch (k)
	{
	case GLUT_KEY_LEFT:
		trackZFactor = std::max(trackZFactor - 0.1, 0.1);
		Game::GameWorld->RecreateTrack(trackZFactor);
		createCoaster();
		break;
	case GLUT_KEY_RIGHT:
		trackZFactor += 0.1;
		Game::GameWorld->RecreateTrack(trackZFactor);
		createCoaster();
		break;
	}
}

int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH | GLUT_MULTISAMPLE);
	glutInitWindowSize(512, 512);

	glutCreateWindow(Game::StatusMessage.c_str());
	glewInit();

	init();

	glutDisplayFunc(display);
	glutMouseFunc(mouseClick);
	glutMotionFunc(mouseMotion);
	glutPassiveMotionFunc(mouseMotion);
	glutIdleFunc(idle);
	glutReshapeFunc(myReshape);
	glutKeyboardFunc(keyPress);
	glutKeyboardUpFunc(keyUp);
	glutSpecialFunc(specialKeyPress);

	glutMainLoop();
	return 0;
}

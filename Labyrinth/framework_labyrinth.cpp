#include "framework_labyrinth.h"

framework_labyrinth* framework_labyrinth::__framework_labyrinth__ = NULL;

extern void initalizeGlut(int argc, char **argv)
{
    glutInit(&argc, argv);
}

extern void startGlut()
{
	glutMainLoop();
}

framework_labyrinth::framework_labyrinth()
{
	theda = 0.0;
	phi = 0.0;
}

framework_labyrinth* framework_labyrinth::instance()
{
	if(!__framework_labyrinth__)
		__framework_labyrinth__ = new framework_labyrinth();
	return __framework_labyrinth__;
}

bool framework_labyrinth::initialize(std::string windowName, int windowWidth, int windowHeight)
{
	display.initializeDisplay(windowName, windowWidth, windowHeight);

	// Now that the window is created the GL context is fully set up
    // Because of that we can now initialize GLEW to prepare work with shaders
    GLenum status = glewInit();
    if( status != GLEW_OK)
    {
        std::cerr << "[ERROR] GLEW NOT INITIALIZED: ";
        std::cerr << glewGetErrorString(status) << std::endl;
        return false;
    }

	glutIgnoreKeyRepeat(true);
	
	//initialize callbacks
	initializeCallbacks();

	//initialize resources
	if(!display.initializeDisplayResources())
		return false;

	//set objects pointers in collision and physics?

	mvMaze *m = display.getMaze();
	mvSphere *b = display.getSphere();

	b->pos = m->getBegin();
	
	objs.push_back(dynamic_cast<mvObject*>(m));
	objs.push_back(dynamic_cast<mvObject*>(b));

	physics.setObjs(objs);

	collision.setMaze(m);
	collision.setBall(b);

	stopwatch.startTime();
	return true;
}

void framework_labyrinth::initializeCallbacks()
{
	glutDisplayFunc(displayWrapperFunc);
	glutReshapeFunc(reshapeWrapperFunc);
	glutKeyboardFunc(keyboardWrapperFunc);
	glutKeyboardUpFunc(keyboardUpWrapperFunc);
	glutSpecialFunc(specialWrapperFunc);
	glutSpecialUpFunc(specialUpWrapperFunc);
	glutMouseFunc(mouseWrapperFunc);
	glutMotionFunc(motionWrapperFunc);
	glutIdleFunc(idleWrapperFunc);
}

void framework_labyrinth::displayFunc()
{
	display.display();
}

void framework_labyrinth::reshapeFunc(int newWidth, int newHeight)
{
	display.reshape(newWidth, newHeight);
}

void framework_labyrinth::keyboardFunc(unsigned char key, int x, int y)
{
	userInput.handleKeyboardFunc(key,mvKeyboardData(KEY_DOWN));
}

void framework_labyrinth::keyboardUpFunc(unsigned char key, int x, int y)
{
	userInput.handleKeyboardFunc(key,mvKeyboardData(KEY_UP));
}

void framework_labyrinth::specialFunc(int key, int x, int y)
{
	userInput.handleSpecialFunc(key,mvKeyboardData(KEY_DOWN));
}

void framework_labyrinth::specialUpFunc(int key, int x, int y)
{
	userInput.handleSpecialFunc(key,mvKeyboardData(KEY_UP));
}

void framework_labyrinth::mouseFunc(int button, int state, int x, int y)
{
	userInput.handleMouseFunc(button, state, x, y, mvMouseData(theda,phi));
}

void framework_labyrinth::motionFunc(int x, int y)
{
	mvMouseData mouseOutput;
	if(userInput.handleMouseMotionFunc(x, y, mouseOutput))
	{
		setTheda(mouseOutput.theda);
		setPhi(mouseOutput.phi);
	}
}

void framework_labyrinth::idleFunc()
{
	//update object pos from input
	//updateObjFromInput();
	glm::mat4 rotationTheda;
	glm::mat4 rotationPhi;
	glm::mat4 mm;//mazeModel

	glm::vec4 phiAxis(0.0,0.0,1.0,0.0);

	double keyRotationRate = 30.0;
	
	double deltaThedaTime=0.0;
	double deltaPhiTime=0.0;
	
	deltaPhiTime -= userInput.timeKeyDown('a');
	deltaPhiTime += userInput.timeKeyDown('d');
	deltaPhiTime -= userInput.timeSpecialDown(GLUT_KEY_LEFT);
	deltaPhiTime += userInput.timeSpecialDown(GLUT_KEY_RIGHT);

	setPhi(phi + deltaPhiTime * keyRotationRate);
	
	deltaThedaTime -= userInput.timeKeyDown('s');
	deltaThedaTime += userInput.timeKeyDown('w');
	deltaThedaTime -= userInput.timeSpecialDown(GLUT_KEY_DOWN);
	deltaThedaTime += userInput.timeSpecialDown(GLUT_KEY_UP);

	setTheda(theda + deltaThedaTime * keyRotationRate);
	
	rotationTheda = glm::rotate(glm::mat4(1.0f), (float)theda, glm::vec3(1.0,0.0,0.0));

	phiAxis = rotationTheda*phiAxis;

	rotationPhi = glm::rotate(glm::mat4(1.0f), (float)phi, glm::vec3(phiAxis.x, phiAxis.y, phiAxis.z));

	mm = rotationTheda * rotationPhi;

	display.setMazeModelMat(mm);

	//get gravity acceleration

	glm::mat4 worldRotation = glm::inverse(mm);

	glm::vec4 gravity(0.0,-9.8,0.0,0.0);

	gravity = worldRotation*gravity;
	
	physics.setGravity(glm::vec3(gravity.x, 0.0, gravity.z));

	//update physics for object
	physics.update(stopwatch.resetTime());
	
	//get object references from display
	//check collision based on those objects

	collision.resolveCollisions();//need walls/holes/goal and sphere radius

	glm::mat4 translation = glm::translate(glm::mat4(1.0f),objs[1]->pos);

	display.setBallModelMat(mm * translation);

	//physics update

	//collision check

	//update display

	display.display();

    glutPostRedisplay();//call the display callback
}

void framework_labyrinth::setTheda(double t)
{
	if(t<-45.0)
		theda = -45.0;
	else if(t>45.0)
		theda = 45.0;
	else
		theda = t;
}

void framework_labyrinth::setPhi(double p)
{
	if(p<-45.0)
		phi = -45.0;
	else if(p>45.0)
		phi = 45.0;
	else
		phi = p;
}

extern void displayWrapperFunc()
{
	framework_labyrinth::instance()->displayFunc();
}

extern void reshapeWrapperFunc(int newWidth, int newHeight)
{
	framework_labyrinth::instance()->reshapeFunc(newWidth, newHeight);
}

extern void keyboardWrapperFunc(unsigned char key, int x, int y)
{
	framework_labyrinth::instance()->keyboardFunc(key, x, y);
}

extern void keyboardUpWrapperFunc(unsigned char key, int x, int y)
{
	framework_labyrinth::instance()->keyboardUpFunc(key, x, y);
}

extern void specialWrapperFunc(int key, int x, int y)
{
	framework_labyrinth::instance()->specialFunc(key, x, y);
}

extern void specialUpWrapperFunc(int key, int x, int y)
{
	framework_labyrinth::instance()->specialUpFunc(key, x, y);
}

extern void mouseWrapperFunc(int button, int state, int x, int y)
{
	framework_labyrinth::instance()->mouseFunc(button, state, x, y);
}

extern void motionWrapperFunc(int x, int y)
{
	framework_labyrinth::instance()->motionFunc(x, y);
}

extern void idleWrapperFunc()
{
	framework_labyrinth::instance()->idleFunc();
}
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
	
	display.setUserInput(&userInput);

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
	userInput.handleMouseFunc(button, state, x, y, mvMouseData(display.getTheda(), display.getPhi()));
}

void framework_labyrinth::motionFunc(int x, int y)
{
	mvMouseData mouseOutput;
	if(userInput.handleMouseMotionFunc(x, y, mouseOutput))
	{
		display.setTheda(mouseOutput.theda);
		display.setPhi(mouseOutput.phi);
	}
}

void framework_labyrinth::idleFunc()
{
	//update object pos from input

	//physics update

	//collision check

	//update display

	display.updateDisplay();

    glutPostRedisplay();//call the display callback
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
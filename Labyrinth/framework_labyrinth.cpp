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
	width = 640;
	height = 480;
	
	std::vector<mvRect> walls;
	mvRect wall;
	mvRect base;

	wall.loadMesh("wall1.obj");
	wall.setColor(1.0,0.0,0.75);
	walls.push_back(wall);

	wall.loadMesh("wall2.obj");
	wall.setColor(0.5,0.0,1.0);
	walls.push_back(wall);

	wall.loadMesh("wall3.obj");
	wall.setColor(1.0,0.0,0.5);
	walls.push_back(wall);

	wall.loadMesh("wall4.obj");
	wall.setColor(0.75,0.0,1.0);
	walls.push_back(wall);

	base.loadMesh("base.obj");
	base.setColor(0.0,1.0,0.0);

	maze.setMaze(walls, base);
}

framework_labyrinth* framework_labyrinth::instance()
{
	if(!__framework_labyrinth__)
		__framework_labyrinth__ = new framework_labyrinth();
	return __framework_labyrinth__;
}

bool framework_labyrinth::initialize(std::string windowName, int windowWidth, int windowHeight)
{
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowSize(windowWidth, windowHeight);
	width = windowWidth;
	height = windowHeight;

    // Name and create the Window
    glutCreateWindow(windowName.c_str());

	// Now that the window is created the GL context is fully set up
    // Because of that we can now initialize GLEW to prepare work with shaders
    GLenum status = glewInit();
    if( status != GLEW_OK)
    {
        std::cerr << "[ERROR] GLEW NOT INITIALIZED: ";
        std::cerr << glewGetErrorString(status) << std::endl;
        return false;
    }

	//initialize callbacks
	initializeCallbacks();

	//initialize resources
	if(!initializeResources())
		return false;
	
    t1 = std::clock();//std::chrono::high_resolution_clock::now();
	return true;
}

void framework_labyrinth::initializeCallbacks()
{
	glutDisplayFunc(displayWrapperFunc);
	glutReshapeFunc(reshapeWrapperFunc);
	glutKeyboardFunc(keyboardWrapperFunc);
	glutSpecialFunc(specialWrapperFunc);
	glutMouseFunc(mouseWrapperFunc);
	glutMotionFunc(motionWrapperFunc);
	glutIdleFunc(idleWrapperFunc);
}

bool framework_labyrinth::initializeResources()
{
	glBufferInitialize(maze);

	GLuint vertex_shader = glCreateShader(GL_VERTEX_SHADER);
	GLuint fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
	
	mvShader vs("VertexShader.txt");

	if(!vs.isShaderRdy())
    {
        std::cerr << "[ERROR] VERTEXSHADER NOT LOADED: ";
		std::cerr << vs.getError() << std::endl;
        return false;
    }

	mvShader fs("FragShader.txt");

	if(!fs.isShaderRdy())
    {
        std::cerr << "[ERROR] VERTEXSHADER NOT LOADED: ";
		std::cerr << fs.getError() << std::endl;
        return false;
    }
	
	const char *vs_c_str = vs.getShaderString();
	const char *fs_c_str = fs.getShaderString();
	
    //compile the shaders
    GLint shader_status;

    // Vertex shader first
    glShaderSource(vertex_shader, 1, &vs_c_str, NULL);
    glCompileShader(vertex_shader);

    //check the compile status
    glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &shader_status);
    if(!shader_status)
    {
        std::cerr << "[F] FAILED TO COMPILE VERTEX SHADER!" << std::endl;
        return false;
    }

    // Now the Fragment shader
    glShaderSource(fragment_shader, 1, &fs_c_str, NULL);
    glCompileShader(fragment_shader);

    //check the compile status
    glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &shader_status);
    if(!shader_status)
    {
        std::cerr << "[F] FAILED TO COMPILE FRAGMENT SHADER!" << std::endl;
        return false;
    }

    //Now we link the 2 shader objects into a program
    //This program is what is run on the GPU
    program = glCreateProgram();
    glAttachShader(program, vertex_shader);
    glAttachShader(program, fragment_shader);
    glLinkProgram(program);

    //check if everything linked ok
    glGetProgramiv(program, GL_LINK_STATUS, &shader_status);
    if(!shader_status)
    {
        std::cerr << "[F] THE SHADER PROGRAM FAILED TO LINK" << std::endl;
        return false;
    }

    //Now we set the locations of the attributes and uniforms
    //this allows us to access them easily while rendering
    loc_position = glGetAttribLocation(program,
                    const_cast<const char*>("v_position"));
    if(loc_position == -1)
    {
        std::cerr << "[F] POSITION NOT FOUND" << std::endl;
        return false;
    }

    loc_color = glGetAttribLocation(program,
                    const_cast<const char*>("v_color"));
    if(loc_color == -1)
    {
        std::cerr << "[F] V_COLOR NOT FOUND" << std::endl;
        return false;
    }

    loc_mvpmat = glGetUniformLocation(program,
                    const_cast<const char*>("mvpMatrix"));
    if(loc_mvpmat == -1)
    {
        std::cerr << "[F] MVPMATRIX NOT FOUND" << std::endl;
        return false;
    }
    
    //--Init the view and projection matrices
    //  if you will be having a moving camera the view matrix will need to more dynamic
    //  ...Like you should update it before you render more dynamic 
    //  for this project having them static will be fine
    view = glm::lookAt( glm::vec3(0.0, 8.0, -16.0), //Eye Position
                        glm::vec3(0.0, 0.0, 0.0), //Focus point
                        glm::vec3(0.0, 1.0, 0.0)); //Positive Y is up

    projection = glm::perspective( 45.0f, //the FoV typically 90 degrees is good which is what this is set to
                                   float(width)/float(height), //Aspect Ratio, so Circles stay Circular
                                   0.01f, //Distance to the near plane, normally a small value like this
                                   100.0f); //Distance to the far plane, 

    //enable depth testing
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    //and its done
    return true;
}

void framework_labyrinth::glBufferInitialize(mvObject &object)
{
	glGenBuffers(1, &object.vbo_geometry);
	glBindBuffer(GL_ARRAY_BUFFER, object.vbo_geometry);
	glBufferData(GL_ARRAY_BUFFER, object.sizeofgeometry(), object.geometry, GL_STATIC_DRAW);
}

void framework_labyrinth::displayFunc()
{
    //clear the screen
    glClearColor(0.0, 0.0, 0.2, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	displayObject(maze);

    //swap the buffers
    glutSwapBuffers();
}

void framework_labyrinth::reshapeFunc(int newWidth, int newHeight)
{
    width = newWidth;
    height = newHeight;
    //Change the viewport to be correct
    glViewport( 0, 0, width, height);
    //Update the projection matrix as well
    //See the init function for an explaination
    projection = glm::perspective(45.0f, float(width)/float(height), 0.01f, 100.0f);
}

void framework_labyrinth::keyboardFunc(unsigned char key, int x, int y)
{
	double degreeDelta = 2.5;

    // Handle keyboard input
    if(key == 27)//ESC
    {
		//clean up
        exit(0);
    }
	else if(key == 'w')
	{
		maze.theda += degreeDelta;
	}
	else if(key == 's')
	{
		maze.theda -= degreeDelta;
	}
	else if(key == 'a')
	{
		maze.phi -= degreeDelta;
	}
	else if(key == 'd')
	{
		maze.phi += degreeDelta;
	}
	else
	{
		return;
	}

	idleFunc();
}

void framework_labyrinth::specialFunc(int key, int x, int y)
{
	double degreeDelta = 2.5;

	if(key == GLUT_KEY_UP)
	{
		maze.theda += degreeDelta;
	}
	else if(key == GLUT_KEY_DOWN)
	{
		maze.theda -= degreeDelta;
	}
	else if(key == GLUT_KEY_LEFT)
	{
		maze.phi -= degreeDelta;
	}
	else if(key == GLUT_KEY_RIGHT)
	{
		maze.phi += degreeDelta;
	}
	else
	{
		return;
	}

	idleFunc();
}

void framework_labyrinth::mouseFunc(int button, int state, int x, int y)
{
	userInput.handleMouseFunc(button, state, x, y, mvMouseInput(maze.theda, maze.phi));
}

void framework_labyrinth::motionFunc(int x, int y)
{
	mvMouseOutput mouseOutput;
	if(userInput.handleMouseMotionFunc(x, y, mouseOutput))
	{
		maze.theda = mouseOutput.theda;
		maze.phi = mouseOutput.phi;
	}
}

void framework_labyrinth::idleFunc()
{
	//update physics

	updateDisplay();

    glutPostRedisplay();//call the display callback
}

void framework_labyrinth::displayObject(mvObject object)
{
    //premultiply the matrix for this example
    glm::mat4 mvp = projection * view * object.model;

    //enable the shader program
    glUseProgram(program);

    //upload the matrix to the shader
    glUniformMatrix4fv(loc_mvpmat, 1, GL_FALSE, glm::value_ptr(mvp));

    //set up the Vertex Buffer Object so it can be drawn
    glEnableVertexAttribArray(loc_position);
    glEnableVertexAttribArray(loc_color);
    glBindBuffer(GL_ARRAY_BUFFER, object.vbo_geometry);
    //set pointers into the vbo for each of the attributes(position and color)
    glVertexAttribPointer( loc_position,//location of attribute
                           3,//number of elements
                           GL_FLOAT,//type
                           GL_FALSE,//normalized?
                           sizeof(mvVertex),//stride
                           0);//offset

    glVertexAttribPointer( loc_color,
                           3,
                           GL_FLOAT,
                           GL_FALSE,
                           sizeof(mvVertex),
                           (void*)offsetof(mvVertex,color));

	glDrawArrays(GL_TRIANGLES, 0, object.vertexCount);//mode, starting index, count

    //clean up
    glDisableVertexAttribArray(loc_position);
    glDisableVertexAttribArray(loc_color);
}

//returns the time delta
float framework_labyrinth::getDT()
{
    float ret;
    t2 = std::clock();//std::chrono::high_resolution_clock::now();
    ret = float(t2-t1)/CLOCKS_PER_SEC;//std::chrono::duration_cast< std::chrono::duration<float> >(t2-t1).count();
    t1 = std::clock();//std::chrono::high_resolution_clock::now();
    return ret;
}

void framework_labyrinth::updateDisplay()
{
	glm::mat4 rotationTheda;
	glm::mat4 rotationPhi;

	glm::vec4 phiAxis(0.0,0.0,1.0,0.0);
	
	if(maze.theda >  45) maze.theda =  45;
	if(maze.theda < -45) maze.theda = -45;
	if(maze.phi   >  45) maze.phi   =  45;
	if(maze.phi   < -45) maze.phi   = -45;
	
	rotationTheda = glm::rotate(glm::mat4(1.0f), (float)maze.theda, glm::vec3(1.0,0.0,0.0));

	phiAxis = rotationTheda*phiAxis;

	rotationPhi = glm::rotate(glm::mat4(1.0f), (float)maze.phi, glm::vec3(phiAxis.x, phiAxis.y, phiAxis.z));

	maze.model = rotationTheda * rotationPhi;
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

extern void specialWrapperFunc(int key, int x, int y)
{
	framework_labyrinth::instance()->specialFunc(key, x, y);
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
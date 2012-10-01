#include "mvDisplay.h"


mvDisplay::mvDisplay()
{
	width = 640;
	height = 480;

	theda = 0.0;
	phi = 0.0;

	maze.setSize(10,10);
	maze.setWall(4.75, 0, 0.5, 10);
	maze.setWall(-4.75, 0, 0.5, 10);
	maze.setWall(0, 4.75, 9, 0.5);
	maze.setWall(0, -4.75, 9, 0.5);
	maze.init();

	sphere.loadMesh("sphere.obj");
	sphere.setColor(1.0,1.0,0.0);
	double r = 0.5/sphere.getMeshRadius();
	sphere.scale(r);
	r = sphere.getMeshRadius();
	sphere.translate(0.0,r,0.0);

	physics.setPos(glm::vec3(0.0,0.0,0.0));
	physics.setVel(glm::vec3(0.0,0.0,0.0));

	userInput = NULL;
}


mvDisplay::~mvDisplay()
{
}

void mvDisplay::initializeDisplay(std::string windowName, int w, int h)
{
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowSize(w, h);
	width = w;
	height = h;

    // Name and create the Window
    glutCreateWindow(windowName.c_str());
}

bool mvDisplay::initializeDisplayResources()
{
	objectBufferInit(maze);
	objectBufferInit(sphere);

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
	stopwatch.startTime();
    //and its done
    return true;
}

void mvDisplay::display()
{
    //clear the screen
    glClearColor(0.0, 0.0, 0.2, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	displayObject(maze);
	displayObject(sphere);

    //swap the buffers
    glutSwapBuffers();
}

void mvDisplay::updateDisplay()
{
	glm::mat4 rotationTheda;
	glm::mat4 rotationPhi;

	glm::vec4 phiAxis(0.0,0.0,1.0,0.0);

	double keyRotationRate = 30.0;
	
	double deltaThedaTime=0.0;
	double deltaPhiTime=0.0;
	
	deltaPhiTime -= userInput->timeKeyDown('a');
	deltaPhiTime += userInput->timeKeyDown('d');
	deltaPhiTime -= userInput->timeSpecialDown(GLUT_KEY_LEFT);
	deltaPhiTime += userInput->timeSpecialDown(GLUT_KEY_RIGHT);

	setPhi(phi + deltaPhiTime * keyRotationRate);
	
	deltaThedaTime -= userInput->timeKeyDown('s');
	deltaThedaTime += userInput->timeKeyDown('w');
	deltaThedaTime -= userInput->timeSpecialDown(GLUT_KEY_DOWN);
	deltaThedaTime += userInput->timeSpecialDown(GLUT_KEY_UP);

	setTheda(theda + deltaThedaTime * keyRotationRate);
	
	rotationTheda = glm::rotate(glm::mat4(1.0f), (float)theda, glm::vec3(1.0,0.0,0.0));

	phiAxis = rotationTheda*phiAxis;

	rotationPhi = glm::rotate(glm::mat4(1.0f), (float)phi, glm::vec3(phiAxis.x, phiAxis.y, phiAxis.z));

	maze.model = rotationTheda * rotationPhi;

	glm::mat4 worldRotation = glm::inverse(maze.model);

	glm::vec4 gravity(0.0,-9.8,0.0,0.0);

	gravity = worldRotation*gravity;
	
	physics.setAccel(glm::vec3(gravity.x, 0.0, gravity.z));

	physics.update(stopwatch.resetTime());

	physics.checkCollision(maze.xWalls, maze.zWalls,sphere.getMeshRadius());

	glm::mat4 translation = glm::translate(glm::mat4(1.0f),physics.getPos());

	sphere.model = maze.model * translation;
}
	
void mvDisplay::reshape(int newWidth, int newHeight)
{
    width = newWidth;
    height = newHeight;
    //Change the viewport to be correct
    glViewport( 0, 0, width, height);
    //Update the projection matrix as well
    //See the init function for an explaination
    projection = glm::perspective(45.0f, float(width)/float(height), 0.01f, 100.0f);
}

void mvDisplay::setTheda(double t)
{
	if(t<-45.0)
		theda = -45.0;
	else if(t>45.0)
		theda = 45.0;
	else
		theda = t;
}

void mvDisplay::setPhi(double p)
{
	if(p<-45.0)
		phi = -45.0;
	else if(p>45.0)
		phi = 45.0;
	else
		phi = p;
}

double mvDisplay::getTheda()
{
	return theda;
}

double mvDisplay::getPhi()
{
	return phi;
}

void mvDisplay::setUserInput(mvInput *input)
{
	userInput = input;
}

void mvDisplay::objectBufferInit(mvObject &object)
{
	glGenBuffers(1, &object.vbo_geometry);
	glBindBuffer(GL_ARRAY_BUFFER, object.vbo_geometry);
	glBufferData(GL_ARRAY_BUFFER, object.sizeofgeometry(), object.geometry, GL_STATIC_DRAW);
}

void mvDisplay::displayObject(mvObject &object)
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
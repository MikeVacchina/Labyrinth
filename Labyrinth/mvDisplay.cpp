#include "mvDisplay.h"


mvDisplay::mvDisplay()
{
	//set default values
	width = 640;
	height = 480;

	started = false;

	//load maze objects
	maze1.loadMaze("maze1.mv");
	maze2.loadMaze("maze2.mv");

	//load sphere object and translate/scale mesh
	sphere.loadMesh("sphere.obj");
	sphere.setColor(1.0,1.0,0.0);
	double r = 0.5/sphere.getMeshRadius();
	sphere.scale(r);
	r = sphere.getMeshRadius();
	sphere.translate(0.0,r,0.0);
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
	//initialize objects
	objectBufferInit(maze1);
	objectBufferInit(maze2);
	objectBufferInit(sphere);

	//create shaders
	GLuint vertex_shader = glCreateShader(GL_VERTEX_SHADER);
	GLuint fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
	
	//load shader
	mvShader vs("VertexShader.txt");

	//check shader status
	if(!vs.isShaderRdy())
    {
        std::cerr << "[ERROR] VERTEXSHADER NOT LOADED: ";
		std::cerr << vs.getError() << std::endl;
        return false;
    }

	//load shader
	mvShader fs("FragShader.txt");

	//check shader status
	if(!fs.isShaderRdy())
    {
        std::cerr << "[ERROR] VERTEXSHADER NOT LOADED: ";
		std::cerr << fs.getError() << std::endl;
        return false;
    }
	
	//convert to const char for glut
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
    view = glm::lookAt( glm::vec3(0.0, 20.0, -10.0), //Eye Position - old eye position: glm::vec3(0.0, 8.0, -16.0)
                        glm::vec3(0.0, 0.0, 0.0), //Focus point
                        glm::vec3(0.0, 1.0, 0.0)); //Positive Y is up

    projection = glm::perspective( 45.0f, //the FoV typically 90 degrees is good which is what this is set to
                                   float(width)/float(height), //Aspect Ratio, so Circles stay Circular
                                   0.01f, //Distance to the near plane, normally a small value like this
                                   100.0f); //Distance to the far plane, 

    //enable depth testing
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    return true;
}

void mvDisplay::display()
{
    //clear the screen
    glClearColor(0.0, 0.0, 0.2f, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	if(started)
	{
		//display objects
		if(maze==1)
			displayObject(maze1);
		else if(maze==2)
			displayObject(maze2);
		displayObject(sphere);
	}

    //swap the buffers
    glutSwapBuffers();
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

void mvDisplay::playMaze(int mazeID)
{
	//set maze id
	maze = mazeID;
	
	if(maze==1)
	{
		//reset ball position and motion
		sphere.falling = false;
		sphere.acc = glm::vec3(0.0);
		sphere.vel = glm::vec3(0.0);
		sphere.pos = maze1.getBegin();
	}
	else if(maze==2)
	{
		//reset ball position and motion
		sphere.falling = false;
		sphere.acc = glm::vec3(0.0);
		sphere.vel = glm::vec3(0.0);
		sphere.pos = maze2.getBegin();
	}

	started = true;
}

void mvDisplay::setMazeModelMat(glm::mat4 m)
{
	//set the correct maze model matrix
	if(maze==1)
		maze1.model = m;
	else if(maze==2)
		maze2.model = m;
}

void mvDisplay::setBallModelMat(glm::mat4 m)
{
	//set ball model matrix
	sphere.model = m;
}

mvMaze* mvDisplay::getMaze()
{
	if(started)
		//return the proper maze reference
		if(maze==1)
			return &maze1;
		else if(maze==2)
			return &maze2;
	else
		return NULL;
}

mvSphere* mvDisplay::getSphere()
{
	//return the sphere reference
	if(started)
		return &sphere;
	else
		return NULL;
}

void mvDisplay::objectBufferInit(mvObject &object)
{
	//set object buffers
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
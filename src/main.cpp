#include <glad/glad.h>
#include <glad.c>
#include <GLFW/glfw3.h>
#include <iostream>


//Vertex Shader Code (In OpenGL Shader Language (OGSL))
//Copied from learnopengl.com
const char *vertexShaderSource = "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "}\0";


const char *fragmentShaderSource = "#version 330 core\n"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
    "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
    "}\0";


//Function Prototypes:

//Resizes the window when the user does
void framebuffer_size_callback(GLFWwindow* window,int width,int height);

//Process Keyboard Input
void processInput(GLFWwindow* window);

//Rendering processes are controlled here
void render();

int main()
{
	//Initialize GLFW
	glfwInit(); 

	//Ensures that the user has the correct version of GLFW and will refuse to run otherwise
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); 
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,3); 

	//Sets OpenGL to use the core profile
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	//Makes the code work on macOS because of compatibility issues.
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT,GL_TRUE);


	//Create Window Object
	GLFWwindow* window=glfwCreateWindow(800,600,"Generic Window",NULL,NULL); //Width, height, title*, monitor*, shared* [* = can be NULL]

	//Make sure the window was created
	if(window == NULL){
		std::cout << "Failed to Create a GLFW Window, please try again..." << std::endl;
		glfwTerminate();
		return -1;
	}

	//Push the window into our context.
	glfwMakeContextCurrent(window);
	

	//Load in GLAD (copied from https://learnopengl.com)
	if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
		std::cout << "FailedtoinitializeGLAD" << std::endl;
		return-1;
	}

	//Tell openGL the dimensions of our rendering window
	glViewport(0,0,800,600);

	//Tells GLFW that we want to call our function framebuffer_size_callback when the user resizes.
	glfwSetFramebufferSizeCallback(window,framebuffer_size_callback);

	//Keep the window open until we close it
	while(!glfwWindowShouldClose(window)){
		processInput(window);

		render(); //All rendering subroutines are ran		

		glfwPollEvents(); //Tells GLFW to check if any "events" have occured. This can be keyboard/gamepad input or other.
		glfwSwapBuffers(window); //Swaps the color buffer to update what has been drawn onto the screen.
	}

	glfwTerminate();
    return 0;
}


void render(){
	glClearColor(0.f,0.5f,0.f,1.f);
	glClear(GL_COLOR_BUFFER_BIT);


	//Define a triangle from an array
	float triangle[] = {
		-0.5f, 0.5f, 0.0f,
		0.5f, -0.5f, 0.0f,
		-0.5f, -0.5f, 0.0f
	};


	//Setup an ARRAY BUFFER and put our triangle inside it
	unsigned int VBO; //Data to be written to the graphics buffers
	glGenBuffers(1,&VBO); //Get a buffer to put that data into
	glBindBuffer(GL_ARRAY_BUFFER, VBO); //Bind that buffer to the correct type (ARRAY_BUFFER) and give the address of the data
	glBufferData(GL_ARRAY_BUFFER,sizeof(triangle), triangle, GL_STATIC_DRAW); //Send that data to the buffer



	//Compile and assign vertex shader
	unsigned int vertexShader; //Create an ID for the vertex Shader
	vertexShader = glCreateShader(GL_VERTEX_SHADER); //Create the shader object
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL); //Apply the source code (above) to the shader.
	glCompileShader(vertexShader); //Compile the shader that we defined



	//Error Checking the application of the vertex Shader
	//Copied from learnopengl.com
	int  success;
	char infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if(!success){
    	glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
    	std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}


	//Compile and assign fragment shader
	unsigned int fragmentShader; //Set ID
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER); //Generate a shader object
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL); //Apply the source code
	glCompileShader(fragmentShader); //Compile the shader

	//Error Checking the application of the fragment Shader
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if(!success){
    	glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
    	std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
	}


	//Create a shader program
	unsigned int shaderProgram; //ID object
	shaderProgram = glCreateProgram(); //Create the shader program object
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	//Error Checking the compilation and linking shader program entirely
	glGetProgramiv(shaderProgram, GL_COMPILE_STATUS, &success);
	if(!success){
    	glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
    	std::cout << "ERROR::SHADER::SHADER-PROGRAM::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	//Sets the program created to be used by OpenGL
	glUseProgram(shaderProgram); 


	//We don't need these objects anymore, get them out of my face
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);



	//Now we have to tell OpenGL how to interpret the triangle (vertices) we sent in
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);


	glDrawArrays(GL_TRIANGLES, 0, 3); //Added early for fun

	//LEFT OFF AT Vertex Array Objects!

}

//Resizes the window when the user does
void framebuffer_size_callback(GLFWwindow* window,int width,int height){
	glViewport(0,0,width,height);
}

//Process keyboard input
void processInput(GLFWwindow* window){
	if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS){
		glfwSetWindowShouldClose(window, true);
	}
}
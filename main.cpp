#include<iostream>


#define GLEW_STATIC
#include<GL/glew.h>
#include<GLFW\glfw3.h>


float vertices[] = {
	-0.5f,-0.5f,0.0f,
	0.5f,-0.5f,0.0f,
	0.0f,0.5f,0.0f,
	//0.5f,-0.5f,0.0f,
	//0.0f,0.5f,0.0f,
	0.8f,0.8f,0.0f
	//-0.5f,0.5f,0.0f
};

unsigned int indices[] ={
 0,1,2,
 2,1,3
};

const char* vertexShaderSource =
	"#version 330 core \n"
	"layout(location = 0) in vec3 aPos;\n"
	"void main(){\n"
	"gl_Position = vec4(aPos.x,aPos.y,aPos.z,1.0);}\n";

const char* fragmentShaderSource =
	"#version 330 core \n"
	"out vec4 FragColor;\n"
	"void main(){\n"
	"FragColor = vec4(1.0f,0.5f,0.2f,1.0f);}\n";

void processInput(GLFWwindow* window){
	if(glfwGetKey(window,GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window,true);
	}
}

int main(){
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,3);
	glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE);

	//open GLFW Window
	GLFWwindow* window = glfwCreateWindow(800,600,"My OpenGL Game",NULL,NULL);
	//如果生成失败，则停止
	if(window == NULL) 
	{
		printf("Open window failed.");
		glfwTerminate();  // 停止glfw
		return -1;
	}

	glfwMakeContextCurrent(window);

	// init GLEW

	glewExperimental = true;
	if(glewInit() != GLEW_OK)
	{
		printf("Init GLEW failed.");
		glfwTerminate();
		return -1;
	}

	glViewport(0,0,800,600);
	//glEnable(GL_CULL_FACE);
	//glCullFace(GL_BACK);
	glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);

	unsigned int VAO;
	glGenVertexArrays(1,&VAO);
	glBindVertexArray(VAO);

	unsigned int VBO;
	glGenBuffers(1,&VBO);
	glBindBuffer(GL_ARRAY_BUFFER,VBO);
	glBufferData(GL_ARRAY_BUFFER,sizeof(vertices),vertices,GL_STATIC_DRAW); 

	unsigned int EBO;
	glGenBuffers(1,&EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(indices),indices,GL_STATIC_DRAW);

	unsigned int vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader,1,&vertexShaderSource,NULL);
	glCompileShader(vertexShader);

	unsigned int fragmentShader;
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader,1,&fragmentShaderSource,NULL);
	glCompileShader(fragmentShader);

	unsigned int shaderProgram;
	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram,vertexShader);
	glAttachShader(shaderProgram,fragmentShader);
	glLinkProgram(shaderProgram);

	glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,3*sizeof(float),(void*)0);
	glEnableVertexAttribArray(0);


	//循环等待命令响应
	while(!glfwWindowShouldClose(window))
	{
		processInput(window);    //输入按键退出

		//渲染命令
		glClearColor(0.2f,0.3f,0.3f,1.0f);//设置每次屏的颜色（R,G，B，不透明度）
		glClear(GL_COLOR_BUFFER_BIT); //清除缓存的颜色数据，每次循环开始清屏上次的颜色


		glBindVertexArray(VAO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,EBO);
		glUseProgram(shaderProgram);
		/*glDrawArrays(GL_TRIANGLES,0,6);*/
		glDrawElements(GL_TRIANGLES,6,GL_UNSIGNED_INT,0);


		//检查新的输入和准备渲染缓存
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	
	glfwTerminate();
	return -1 ;

}
#include<iostream>


#define GLEW_STATIC
#include<GL/glew.h>
#include<GLFW\glfw3.h>


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

	while(!glfwWindowShouldClose(window))
	{
		processInput(window);
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	
	glfwTerminate();
	return -1 ;

}
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

	//循环等待命令响应
	while(!glfwWindowShouldClose(window))
	{
		processInput(window);    //输入按键退出

		//渲染命令
		glClearColor(0.2f,0.3f,0.3f,1.0f);//设置每次屏的颜色（R,G，B，不透明度）
		glClear(GL_COLOR_BUFFER_BIT); //清除缓存的颜色数据，每次循环开始清屏上次的颜色



		//检查新的输入和准备渲染缓存
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	
	glfwTerminate();
	return -1 ;

}
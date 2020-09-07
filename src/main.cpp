#include <stdio.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "shader.h"
#include "mesh.h"
#include "texture.h"
#include "transform.h"
#include "camera.h"

#define move_add 0.25
#define rot_add 0.05

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 800

void callback_framebuffer_resize(GLFWwindow* window, int fbW, int fbH) { glViewport(0, 0, fbW, fbH); }

int main(int argc, char** argv) {

	GLFWwindow* window;
	if (!glfwInit()) { perror("ERROR: glfwInit() failed\n"); return 1; }
	window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "WINDOW_TITLE", NULL, NULL);
	if (!window) { perror("ERROR: glfwCreateWindow failed\n"); glfwTerminate(); return 1; }
	glfwSetFramebufferSizeCallback(window, callback_framebuffer_resize);
	//glfwSetWindowSizeLimits(window, SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_WIDTH, SCREEN_HEIGHT);
	glfwMakeContextCurrent(window);
	glfwSwapInterval(1);
	if (glewInit() != GLEW_OK) { perror("ERROR: glewInit() failed"); }
	printf("OpenGL version: %s\n", glGetString(GL_VERSION));

	// DONT DRAW THE BACK SIDE OF MESHES
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	printf("obj: ./res/object.obj\n");
	printf("loading 3D OBJ model...\n");
	Mesh mesh("./res/object.obj");
	printf("loaded 3D OBJ model!\n");
	
	printf("shader: ./res/basicShader\n");
	Shader shader("./res/basicShader");
	
	printf("texture: ./res/tex.jpg (not finished)\n");
	Texture texture("./res/tex.jpg");
	
	Camera camera(glm::vec3(0, -2, -10), 70.0f, (float)SCREEN_WIDTH/(float)SCREEN_HEIGHT, 0.01f, 1000.0f);
	Transform transform;

	printf("use 'WASDQE' to move the mesh around\n");
	printf("use the arrow keys to rotate the mesh around\n");
	
	float counter = 0.0f;
	float objX = 0.0f;
	float objY = 0.0f;
	float objZ = 0.0f;
	float objXrot = 0.0f;
	float objYrot = 0.0f;
	float objZrot = 0.0f;
    	while(!glfwWindowShouldClose(window)){
		
		glClearColor(0.0f, 0.5f, 0.1f, 0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		// input
		if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) { objX += move_add; }
		if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) { objY += move_add; }
		if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS) { objZ += move_add; }
		if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) { objX -= move_add; }
		if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) { objY -= move_add; }
		if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS) { objZ -= move_add; }
		
		if (glfwGetKey(window, GLFW_KEY_DOWN)  == GLFW_PRESS) { objXrot += rot_add; }
		if (glfwGetKey(window, GLFW_KEY_LEFT)  == GLFW_PRESS) { objYrot += rot_add; }
		if (glfwGetKey(window, GLFW_KEY_UP)    == GLFW_PRESS) { objXrot -= rot_add; }
		if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) { objYrot -= rot_add; }
		
		transform.GetPos().x = objX;
		transform.GetPos().y = objY;
		transform.GetPos().z = objZ;
	
		transform.GetRot().x = objXrot;
		transform.GetRot().y = objYrot;
		transform.GetRot().z = objZrot;
		
		shader.Bind();
		shader.Update(transform, camera);
		mesh.Draw();

		// update
        	glfwSwapBuffers(window);
		glfwPollEvents();

		counter += 0.005f;
    }
	
    return 0;
}
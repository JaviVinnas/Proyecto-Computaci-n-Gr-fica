#include "main.h"




//declaracion de funciones
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void openGlInit();
void mainLOOP(GLFWwindow* window, GLuint shaderProgram);


int main()
{
	
	//iniciamos y configuramos glfw
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	//Creo la ventana
	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Proyecto Final", NULL, NULL);
	//comprobamos que se haya creado correctamente
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	// glad: load all OpenGL function pointers
	// ---------------------------------------
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}
	shaderProgram = setShaders("shader.vert", "shader.frag");
	
	glUseProgram(shaderProgram);

	openGlInit();

	mainLOOP(window, shaderProgram);

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f); //Borro el Buffer the la ventana
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glfwTerminate();
	return 0;
}


void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	SCR_WIDTH = width;
	SCR_HEIGHT = height;
}

void openGlInit()
{
	//Habilito aqui el depth en vez de arriba para los usuarios de linux y mac mejor arriba
	//Incializaciones varias
	glClearDepth(1.0f);                   //Valor z-buffer
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // valor limpieza buffer color
	glEnable(GL_DEPTH_TEST);              // z-buffer
	glEnable(GL_CULL_FACE);               //ocultacion caras back
	glCullFace(GL_BACK);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}


void mainLOOP(GLFWwindow* window, GLuint shaderProgram)
{
	//inicializamos los objetos que nos interesen
	LocalizadorShader locshader = LocalizadorShader(shaderProgram);

	Juego juego = Juego(window, &locshader, &SCR_WIDTH, &SCR_HEIGHT);

	while (!glfwWindowShouldClose(window))
	{
		//actualizamos nuestros objetos y aplicamos cambios si hay que aplicarlos 

		juego.actualizar();

		//dibujamos

		juego.dibujar();

		//borramos la ventana y los eventos que haya
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
}








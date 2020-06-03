#include "Camara.h"

void Camara::iniciarModosCamara()
{
	if (this->modosCamara.esVacio()) {
		this->modosCamara.addEstado(EXTERIOR);
		this->modosCamara.addEstado(PRIMERA_PERSONA);
	}
}

Camara::Camara()
{
	this->matProyeccion = mat4();
	this->matView = mat4();
	this->modosCamara = AlternadorEstadosTecla();
	this->movZoom = Movimiento1d();
}

Camara::Camara(GLFWwindow* window, LocalizadorShader* locshader)
{
	this->matProyeccion = mat4();
	this->matView = mat4();
	this->window = window;
	this->modosCamara = AlternadorEstadosTecla(GLFW_KEY_P, this->window);
	this->iniciarModosCamara();
	this->movZoom = Movimiento1d(uvec2(GLFW_KEY_KP_ADD, GLFW_KEY_KP_SUBTRACT), .0025f, -5.0f);
	this->movCamara = Movimiento2dLimites(uvec2(GLFW_KEY_LEFT, GLFW_KEY_RIGHT), uvec2(GLFW_KEY_UP, GLFW_KEY_DOWN), .025f, vec2(327.0f, 220.0f), 360.0f);
	this->anchoAlto = vec2();
	this->locShader = locshader;
	this->pulsadorModosCamara = Pulsador(GLFW_KEY_P, .3, this->window);
}



void Camara::actualizar(uvec2 anchoAlto, Tanque * tanque)
{
	this->anchoAlto = vec2(float(anchoAlto.x), float(anchoAlto.y));
	this->matProyeccion = perspective(radians(55.0f), this->anchoAlto.x / this->anchoAlto.y, .1f, 10.0f);
	this->locShader->cargarProjection(matProyeccion);

	if (this->pulsadorModosCamara.sePulsa()) {
		this->modosCamara.cambiarEstado();
	}
	this->movCamara.checkCambios(this->window);
	this->movZoom.checkCambios(this->window);

	glm::vec3 source = glm::vec3(); //donde esta la camara
	glm::vec3 target = glm::vec3(); //donde apunta
	glm::vec3 up = glm::vec3();     //normal
	float zoomActual = this->movZoom.getValorDesplazamiento();
	vec2 movCamaraActual = this->movCamara.getMov();

	glm::mat4 matTrans = glm::mat4();

	switch (this->modosCamara.getEstadoActual())
	{
	
	case EXTERIOR:
		tanque->setBlocMov(false);
		source = zoomActual * vec3(
			sin(radians(movCamaraActual.x)) * cos(radians(movCamaraActual.y)),
			sin(radians(movCamaraActual.y)),
			cos(radians(movCamaraActual.x)) * cos(radians(movCamaraActual.y))
		);
		source += vec3(tanque->getPos().x, 0, tanque->getPos().y);
		//la cámara apuntará al tanque
		target = tanque->getPos();
		break;
	case PRIMERA_PERSONA:
		tanque->setBlocMov(true);
		tanque->cargarCamaraTanque(&source, &target);
	}
	up = vec3(0.0f, 1.0f, 0.0f);
	//asignamos la POSICION de la camara al controlador de la luz especular
	this->locShader->cargarPosicionEspectador(source);
	//luz siempre encima del tanque
	this->locShader->cargarPosicionLuz(vec3(tanque->getPos().x, 1.0f, tanque->getPos().z));
	
	this->matView = lookAt(source, target, up);
}

//lo primero que se hace al dibujar
void Camara::cargarCamara()
{
	//ponemos todo a negro
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//escalamos el contenido de la ventana
	glViewport(0, 0,(GLsizei)this->anchoAlto.x,(GLsizei)this->anchoAlto.y);
	this->locShader->cargarProjection(this->matProyeccion);
	this->locShader->cargarView(this->matView);
}





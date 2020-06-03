#include "Pulsador.h"



Pulsador::Pulsador()
{
	this->tecla = GLFW_KEY_SPACE;
	this->tiempoMargen = .5;
	this->temp = Temporizador(this->tiempoMargen);
	this->window = NULL;
}

Pulsador::Pulsador(unsigned tecla, double tiempoMargen, GLFWwindow* window)
{
	this->tecla = tecla;
	this->tiempoMargen = tiempoMargen;
	this->temp = Temporizador(this->tiempoMargen);
	this->window = window;
}

bool Pulsador::sePulsa()
{
	if (this->temp.suenaAlarma()) {
		if (glfwGetKey(this->window, this->tecla) == GLFW_PRESS) {
			this->temp.setAlarma(this->tiempoMargen);
			return true;
		}
		else
		{
			return false;
		}
	}
	else
	{
		return false;
	}
}

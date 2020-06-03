#pragma once

#ifndef TEMPORIZADOR_H
#include "Temporizador.h"
#endif // !TEMPORIZADOR_H

class Pulsador
{
private:
	Temporizador temp;
	unsigned tecla;
	double tiempoMargen;
	GLFWwindow* window;
public:
	Pulsador();
	Pulsador(unsigned tecla, double tiempoMargen, GLFWwindow* window);
	bool sePulsa();
};


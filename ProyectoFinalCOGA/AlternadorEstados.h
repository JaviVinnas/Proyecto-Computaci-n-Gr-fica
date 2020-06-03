#pragma once

#ifndef VECTOR
#include <vector>
#endif // !VECTOR

#ifndef IOSTREAM
#include <iostream>
#endif // !IOSTREAM

#ifndef TEMPORIZADOR_H
#include "Temporizador.h"
#endif // !TEMPORIZADOR_H



using namespace std;

class AbstractAlternadorEstados;
class AlternadorEstadosTecla;
class AlternadorEstadosEvento;
class AlternadorEstadosTemporizador;

//valor al que estará el estado actual por defecto
#define VACIO 999999

class AbstractAlternadorEstados
{
private:
	vector<unsigned> estados;
	unsigned estadoActual;

public:
	//constructor
	AbstractAlternadorEstados();
	//devuelve se está vacío el alternador
	bool esVacio();
	//devuelve el estado actual
	unsigned getEstadoActual();
	//añade un estado nuevo si no es repetido
	void addEstado(unsigned estado);
	//cambia el estado (dependiendo del tipo de alternador que sea)
	virtual void cambiarEstado() = 0;
	//cambia el estado actual al siguiente que le toque
protected:
	void siguenteEstado();
};
//1º////////////////////////////////////////////////////////////////////////////////////////////////
//cambiará de estado cuando la tecla asociada en la ventala asociada se pulse
//hay que llamar cambiarEstado() constantemente para ver si se pulsa o no la tecla
class AlternadorEstadosTecla : public AbstractAlternadorEstados
{
private:
	unsigned tecla;
	GLFWwindow *window;

public:
	//constructores
	AlternadorEstadosTecla();
	AlternadorEstadosTecla(unsigned tecla, GLFWwindow* window);
	//cambia el estado cuando en la ventana |window| se pulse la tecla |tecla|
	void cambiarEstado();
};

//2º/////////////////////////////////////////////////////////////////////////////////////////////////
//cambiará inmediatamente cuando se llame a cambiarEstado()
//se llama a cambiarEstado cuando se quiera que cambie
class AlternadorEstadosEvento : public AbstractAlternadorEstados
{
public:
	AlternadorEstadosEvento();
	void cambiarEstado();
};

//3º/////////////////////////////////////////////////////////////////////////////////////////////////
//cambiará de estado dependiendo del temporizador que se le pase (cada cuanto tiempo se active)
//hay q estar llamando constantemente a cambiarEstado() por si se activa
class AlternadorEstadosTemporizador : public AbstractAlternadorEstados
{
private:
	Temporizador temporizador;

public:
	AlternadorEstadosTemporizador();
	AlternadorEstadosTemporizador(Temporizador temporizador);
	void cambiarEstado();
};
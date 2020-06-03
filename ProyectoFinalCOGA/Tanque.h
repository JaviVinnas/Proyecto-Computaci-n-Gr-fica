#pragma once

#ifndef BLOQUE_H
#include "Bloque.h"
#endif // !BLOQUE_H

#ifndef MOVIMIENTOS_H
#include "Movimientos.h"
#endif // !MOVIMIENTOS_H

#ifndef PULSADOR_H
#include "Pulsador.h"
#endif // !PULSADOR_H

#ifndef BALA_H
#include "Bala.h"
#endif // !BALA_H

#ifndef ESCENARIO_H
#include "Escenario.h"
#endif // !ESCENARIO_H

#ifndef PISCINA_H
#include "Piscina.h"
#endif // !PISCINA_H


class Tanque
{
private:
	BloqueNormal base;
	BloqueNormal cuerpo;
	BloqueNormal cannon;
	BloqueNormal puntaCannon;
	Movimiento1dLimites movCannon;
	Movimiento2d movTanque;
	GLFWwindow* window;
	LocalizadorShader* locshader;
	float escala;
	Pulsador botonDisparar;
	vector<Bala> balasDisparadas;
	mat4 moverTanque(mat4 const& transform);
	mat4 girarCannon(mat4 const& transform);
	mat4 sourceCam;
	mat4 targetCam;
	bool bloquearMov;
	bool lento;
	unsigned vida;
	unsigned contBalas;
	TexturasEvento textVida;
	Temporizador tempRegenVida;
	Temporizador tempQuitVidaPiscina;
	//crea balas nuevas si se apretó el pulsador
	void crearBala(mat4 const& transform);
	//mueve las balas que se hayan creado
	void actualizarBala();
	//borra las balas que tengas que desaparecer
	void borrarBala();
	//mira si el tanque se sale del escenario y lo para en el borde si es el caso
	void salirseDelSuelo(Escenario * escenario);
	//mira si el tanque está tocando una piscina y de ser así reduce su velocidad
	void tocaPiscina(Escenario* escenario);
	//si el tanque está  tocando una piscina se pone la luz cad vez más roja
	bool enrojecerLuz();
	//si ha pasado 5 segundos sin recibir ningún daño el tanque se regenera
	void regenerar();
	//lo que se hace si se piede por estar en el agua mucho tiempo
	void haPerdidoAgua(vec3 * color);
	//reinicia el contador de quitar vida por la piscina
	void resetTemporizadorQuitVidaPiscina();
public:
	Tanque(GLFWwindow* window, LocalizadorShader* locshader);
	bool actualizarTanque(Escenario * escenario);
	void dibujar();
	vector<Bala> *getBalas();
	vec3 getPos();
	BoundingBox getBoundingBox();
	vec3 getPosPuntaCannon();
	void cargarCamaraTanque(vec3* source, vec3* target);
	void setBlocMov(bool si_o_no);
	TexturasEvento* getTextsVida();
	void setVida(unsigned vida);
	unsigned getVida();
	void resetTemporizadorRegenVida();
	GLFWwindow* getWindow();
	void reset();
};


#pragma once

#ifndef TANQUE_H
#include "Tanque.h"
#endif // !TANQUE_H

#ifndef LOCALIZADOR_SHADER_H
#include "LocalizadorShader.h"
#endif // !LOCALIZADOR_SHADER_H

static unsigned idEnemigo = 1;

class Enemigo
{
private:
	unsigned id;
	LocalizadorShader* locshader;
	Tanque* objetivo;
	BloqueNormal base;
	BloqueNormal tronco;
	BloqueNormal cabeza;
	float escala;
	float velocidad;
	int vida;
	vec2 posicion;
	//devuelve true si le ha tocado una bala y la destruye (actualizando textura, vida y velocidad del tanque)
	void leHanDado();
	//avanza en dirección a el objetivo
	mat4 perseguirObjetivo(mat4 const &transform);
public:
	Enemigo(LocalizadorShader* locshader, Tanque* objetivo, vec2 posOriginal);
	void actualizar();
	void dibujar();
	int getVida();
	BoundingBox getBoundignBox();
	void aumentarVelocidad(float aumento);
	unsigned getId();
	void resetIdEnemigo();


};


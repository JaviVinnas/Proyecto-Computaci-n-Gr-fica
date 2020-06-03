#pragma once


#ifndef BLOQUE_H
#include "Bloque.h"
#endif // !BLOQUE_H

class Piscina
{
private:
	BloqueNormal bloque;
	mat4 transfm;
public:
	Piscina(float tam, vec2 pos, LocalizadorShader* locshader);
	void dibujar(BloqueSuelo suelo);
	BloqueNormal getBloque();
};


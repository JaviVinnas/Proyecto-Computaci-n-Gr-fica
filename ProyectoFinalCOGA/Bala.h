#pragma once

#ifndef BLOQUE_H
#include "Bloque.h"
#endif // !BLOQUE_H

class Bala
{
private:
	Temporizador tempBala;
	BloqueNormal cuerpoBala;
	mat4 transfm;
	vec3 aumento;
public:
	Bala(mat4 origen, LocalizadorShader* locshader);
	BloqueNormal* getCuerpo();
	void actualizar();
	bool leTocaMorir();
	void dibujar();
};


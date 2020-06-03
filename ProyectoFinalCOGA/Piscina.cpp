#include "Piscina.h"

Piscina::Piscina(float tam, vec2 pos, LocalizadorShader* locshader)
{
	this->bloque = BloqueNormal(vec3(1.0f*tam, .05f, 1.0f*tam), vec3(pos.x, .05f, pos.y), string("caust"), 15, string("png"), locshader);
	this->transfm = translate(mat4(), vec3(pos.x, .05f, pos.y));
}

void Piscina::dibujar(BloqueSuelo suelo)
{
	
	this->bloque.actualizar(this->transfm);
	this->bloque.cambiarTextura();
	this->bloque.dibujar(suelo.getTextura(), true);
}

BloqueNormal Piscina::getBloque()
{
	return this->bloque;
}


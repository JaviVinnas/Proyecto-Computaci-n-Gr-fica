#pragma once

#ifndef GLM_HPP
#include <glm/glm.hpp>
#endif // !GLM_HPP

#ifndef MATRIX_TRANSFORM_HPP
#include <glm/gtc/matrix_transform.hpp>
#endif // !MATRIX_TRANSFORM_HPP

#ifndef TYPE_PTR_HPP
#include <glm/gtc/type_ptr.hpp>
#endif // !TYPE_PTR_HPP

#ifndef BOUNDING_BOX_H
#include "BoundingBox.h"
#endif // !BOUNDINGBOX_H

#ifndef TEXTURAS_H
#include "Texturas.h"
#endif // !TEXTURAS_H

#ifndef LOCALIZADOR_SHADER_H
#include "LocalizadorShader.h"
#endif // !LOCALIZADOR_SHADER_H


using namespace glm;

class BloqueSuelo;
class BloqueNormal;

//El bloque será la mínima unidad dibujable del programa
//Se genera a partir de un mismo cubo centrado en el origen de 1 de lado
//cuando se le aplica una transformacion cambiuan sus parámetros
class BloqueSuelo
{
private:
	void cargarVaoSuelo();
protected:
	BoundingBox boundingBox;
	GLuint vao;
	AbstractTexturas* gestTexturas;
	LocalizadorShader* locShader;
public:
	BloqueSuelo();
	//inicializador para texturas temporales
	BloqueSuelo(string const& text, unsigned const& numText, string const& extension, LocalizadorShader * locshader);
	void cambiarTextura();
	void dibujar();
	BoundingBox getBoundingBox();
	unsigned getTextura();
};

class BloqueNormal : public BloqueSuelo
{
private:
	vec3 tam;
	vec3 pos;
	mat4 matTransformacion;
	void cargarVaoCubo();
public:
	BloqueNormal();
	//para texturas temporales
	BloqueNormal(vec3 tam, vec3 pos, string const& text, unsigned const& numText, string const& extension, LocalizadorShader * locshader);
	//para texturas por eventos
	BloqueNormal(vec3 tam, vec3 pos, vector<string> const& texturas, LocalizadorShader * locshader);
	void actualizar(mat4 const& transformacion);
	void dibujar();
	//asumimos un objeto con una única textura que se le mezclará otra que se le pasa como argumento 
	void dibujar(unsigned text2, bool principal);
	vec3 getPos();
	mat4 getTransfm();
	void setTransfm(mat4 transfm);
};


#pragma once

#ifndef GLAD_H
#include <glad.h>
#endif // !GLAD_H

#ifndef STRING
#include <string>
#endif // !STRING

#ifndef GLM_HPP
#include <glm/glm.hpp>
#endif // !GLM_HPP

#ifndef MATRIX_TRANSFORM_HPP
#include <glm/gtc/matrix_transform.hpp>
#endif // !MATRIX_TRANSFORM_HPP

#ifndef TYPE_PTR_HPP
#include <glm/gtc/type_ptr.hpp>
#endif // !TYPE_PTR_HPP

#ifndef ALTERNADOR_ESTADOS_H
#include "AlternadorEstados.h"
#endif // !ALTERNADOR_ESTADOS_H



// Es necesario para que el stb_image funcione
#ifndef STB_IMAGE_H
#include <stb_image.h>
#endif // !STB_IMAGE_H

#define SINTEXTURA 98959

using namespace std;
using namespace glm;

class AbstractTexturas;
class TexturasTemporizadas;
class TexturasEvento;

class AbstractTexturas
{
protected:
	unsigned obtenerTextura(string const& nombreImagen);
public:
	AbstractTexturas();
	virtual void cambiarTextura() = 0;
	/*
	En caso de no haber ninguina textura se devolverían 2 SINTEXTURA
	En caso de sólo tener una textura el primer elemnto segundo elemnto contendría SINTEXTURA
	*/
	virtual uvec2 getTexturasActuales() = 0;
};

/*conjunto de texturas que van cambiando cada cierto tiempo con nombres similares
Hay que estar llamando constantemente a cambiartextura por si le toca cambiar*/
class TexturasTemporizadas : public AbstractTexturas
{
private:
	AlternadorEstadosTemporizador alternadorTemp1;
	AlternadorEstadosTemporizador alternadorTemp2;
public:
	TexturasTemporizadas();
	TexturasTemporizadas(string const& text, unsigned const& numText, string const& extension);
	TexturasTemporizadas(string const& text1, unsigned const& numText1, string const& text2, unsigned const& numText2, string const& extension);
	void cambiarTextura();
	uvec2 getTexturasActuales();
};

/*conjunto de texturas con nombres que pueden ser distintos entre si. La textura devuelta
por getTexturasActuales cambia cada vez que se ejecuta cambiarTextura*/
class TexturasEvento : public AbstractTexturas
{
private:
	AlternadorEstadosEvento alternadorEvento;
public:
	TexturasEvento();
	TexturasEvento(vector<string> const& texturas);
	void cambiarTextura();
	uvec2 getTexturasActuales();

};



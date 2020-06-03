#pragma once

#ifndef LOCALIZADOR_SHADER_H
#include "LocalizadorShader.h"
#endif // !LOCALIZADOR_SHADER_H

#ifndef BLOQUE_H
#include "Bloque.h"
#endif // !BLOQUE_H

#ifndef PISCINA_H
#include "Piscina.h"
#endif // !PISCINA_H

class Escenario
{
private:
	BloqueSuelo suelo;
	vector<Piscina> piscinas;
public:
	Escenario(LocalizadorShader *locshader);
	void actualizar();
	void dibujar();
	BloqueSuelo getSuelo();
	vector<Piscina> getPiscinas();
};


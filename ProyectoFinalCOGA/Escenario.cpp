#include "Escenario.h"

Escenario::Escenario(LocalizadorShader* locshader)
{
	this->suelo = BloqueSuelo("arenaText", 1, "jpg", locshader);
	this->piscinas.push_back(Piscina(1.0f,	vec2(1.0f, -1.0f), locshader));
	this->piscinas.push_back(Piscina(1.2f,	vec2(-1.0f, -1.0f), locshader));
	this->piscinas.push_back(Piscina(1.5f,	vec2(1.5f, 1.5f), locshader));
	this->piscinas.push_back(Piscina(.5f,	vec2(-2.0f, 2.0f), locshader));
	this->piscinas.push_back(Piscina(.7f,	vec2(-1.0f, 2.0f), locshader));
	this->piscinas.push_back(Piscina(.5f,	vec2(-1.0f, 0.3f), locshader));
	this->piscinas.push_back(Piscina(.6f,	vec2(-2.5f, 0.0f), locshader));
	this->piscinas.push_back(Piscina(.7f,	vec2(-4.28f, 2.17f), locshader));
	this->piscinas.push_back(Piscina(.8f,	vec2(-4.1f, -4.5f), locshader));
	this->piscinas.push_back(Piscina(.8f,	vec2(-4.83f, -1.2f), locshader));
	this->piscinas.push_back(Piscina(.4f,	vec2(-5.0f, .95f), locshader));
	this->piscinas.push_back(Piscina(.5f,	vec2(-4.0f, .0f), locshader));
	this->piscinas.push_back(Piscina(1.0f,	vec2(-4.0f, 4.0f), locshader));
	this->piscinas.push_back(Piscina(1.0f,	vec2(.0f, -4.0f), locshader));
	this->piscinas.push_back(Piscina(1.0f,	vec2(.0f, 4.0f), locshader));
	this->piscinas.push_back(Piscina(2.0f,	vec2(3.5f, 3.5f), locshader));
	this->piscinas.push_back(Piscina(1.75f,	vec2(3.5f, -3.5f), locshader));
}

void Escenario::actualizar()
{
}

void Escenario::dibujar()
{
	this->suelo.dibujar();
	for (auto i = this->piscinas.begin(); i != this->piscinas.end(); ++i) {
		i->dibujar(this->suelo);
	}
}

BloqueSuelo Escenario::getSuelo()
{
	return this->suelo;
	
}

vector<Piscina> Escenario::getPiscinas()
{
	return this->piscinas;
}

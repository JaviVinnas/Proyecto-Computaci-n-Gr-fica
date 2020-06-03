#include "Bala.h"

Bala::Bala(mat4 origen, LocalizadorShader* locshader)
{
	//temporizador para 6 segundos
	this->tempBala = Temporizador(2);

	vector<string> textBala;

	textBala.push_back(string("balaText.jpg"));

	this->cuerpoBala = BloqueNormal(vec3(.07f, .07f, .07f), vec3(), textBala, locshader);
	this->transfm = origen;
	this->aumento = vec3(0.0f, 0.0f, -.005f);
	this->cuerpoBala.actualizar(this->transfm);
}

BloqueNormal* Bala::getCuerpo()
{
	return &this->cuerpoBala;
}

void Bala::actualizar()
{
	this->transfm = translate(this->transfm, this->aumento);
	this->cuerpoBala.actualizar(this->transfm);
}

bool Bala::leTocaMorir()
{
	return this->tempBala.suenaAlarma();
}

void Bala::dibujar()
{
	this->cuerpoBala.dibujar();
}

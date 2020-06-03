#define STB_IMAGE_IMPLEMENTATION
#include "Texturas.h"

unsigned AbstractTexturas::obtenerTextura(string const& nombreImagen)
{
	//variable en la que cargamos la textura
	unsigned textura;
	unsigned char* data = NULL;
	//la inicializamos
	glGenTextures(1, &textura);
	glBindTexture(GL_TEXTURE_2D, textura);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	//variables para crear la imagen
	int width = 0, height = 0, nrChannels = 0, formato = -1;
	//cargamos la imagen (o lo intentamos al menos)
	data = stbi_load(nombreImagen.c_str(), &width, &height, &nrChannels, 0);
	//si se ha podido cargar
	if (data)
	{
		switch (nrChannels)
		{
		case 1:
			formato = GL_RED;
			break;
		case 3:
			formato = GL_RGB;
			break;
		case 4:
			formato = GL_RGBA;
			break;
		default:
			break;
		}
		glTexImage2D(GL_TEXTURE_2D, 0, formato, width, height, 0, formato, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		cout << "Error al cargar la textura -> " + nombreImagen << endl;
	}
	//liberamos la memoria
	stbi_image_free(data);
	//devolvemos la textura cargada
	return textura;
}

AbstractTexturas::AbstractTexturas() {}



//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

TexturasTemporizadas::TexturasTemporizadas()
	: AbstractTexturas() {
	this->alternadorTemp1 = AlternadorEstadosTemporizador();
	this->alternadorTemp2 = AlternadorEstadosTemporizador();
}

TexturasTemporizadas::TexturasTemporizadas(string const& text, unsigned const& numText, string const& extension)
	: AbstractTexturas()
{
	this->alternadorTemp1 = AlternadorEstadosTemporizador();
	this->alternadorTemp2 = AlternadorEstadosTemporizador();

	string nombreTextura;
	unsigned idTextura;
	for (unsigned i = 0; i < numText; i++)
	{
		nombreTextura = text + to_string(i) + '.' + extension;
		idTextura = this->obtenerTextura(nombreTextura);
		this->alternadorTemp1.addEstado(idTextura);
	}
}

TexturasTemporizadas::TexturasTemporizadas(string const& text1, unsigned const& numText1, string const& text2, unsigned const& numText2, string const& extension)
	: AbstractTexturas()
{
	this->alternadorTemp1 = AlternadorEstadosTemporizador();
	this->alternadorTemp2 = AlternadorEstadosTemporizador();

	string nombreTextura;
	unsigned idTextura;

	for (unsigned i = 0; i < numText1; i++)
	{
		nombreTextura = text1 + to_string(1) + '.' + extension;
		idTextura = this->obtenerTextura(nombreTextura);
		this->alternadorTemp1.addEstado(idTextura);
	}

	for (unsigned i = 0; i < numText2; i++)
	{
		nombreTextura = text2 + to_string(1) + '.' + extension;
		idTextura = this->obtenerTextura(nombreTextura);
		this->alternadorTemp1.addEstado(idTextura);
	}

}

void TexturasTemporizadas::cambiarTextura()
{
	if (!this->alternadorTemp1.esVacio()) {
		this->alternadorTemp1.cambiarEstado();
		if (!this->alternadorTemp2.esVacio()) {
			this->alternadorTemp2.cambiarEstado();
		}
	}
}

uvec2 TexturasTemporizadas::getTexturasActuales()
{
	uvec2 texts = uvec2(SINTEXTURA, SINTEXTURA);

	if (!this->alternadorTemp1.esVacio()) {
		texts.x = this->alternadorTemp1.getEstadoActual();
		if (!this->alternadorTemp2.esVacio()) {
			texts.y = this->alternadorTemp2.getEstadoActual();
		}
	}
	return texts;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

TexturasEvento::TexturasEvento() : AbstractTexturas()
{
	this->alternadorEvento = AlternadorEstadosEvento();
}

TexturasEvento::TexturasEvento(vector<string> const& texturas) : AbstractTexturas()
{
	string nombreTextura;
	unsigned idTextura;

	for (auto i = texturas.begin(); i != texturas.end(); i++)
	{
		nombreTextura = *i;
		idTextura = this->obtenerTextura(nombreTextura);
		this->alternadorEvento.addEstado(idTextura);
	}
}

void TexturasEvento::cambiarTextura()
{
	this->alternadorEvento.cambiarEstado();
}


uvec2 TexturasEvento::getTexturasActuales()
{

	uvec2 texts = uvec2(SINTEXTURA, SINTEXTURA);

	if (!this->alternadorEvento.esVacio()) {
		texts.x = this->alternadorEvento.getEstadoActual();
	}
	return texts;
}



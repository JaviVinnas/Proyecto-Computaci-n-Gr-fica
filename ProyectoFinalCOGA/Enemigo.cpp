#include "Enemigo.h"

void Enemigo::leHanDado()
{
	if (this->objetivo->getBalas()->size() >= 1) {
		for (auto i = this->objetivo->getBalas()->begin(); i != this->objetivo->getBalas()->end();)
		{
			//si le ha dado
			if (i->getCuerpo()->getBoundingBox().colisionanAABB(this->cabeza.getBoundingBox())) {
				//borramos la bala
				i = this->objetivo->getBalas()->erase(i);
				//actualizamos los parámetros
				this->base.cambiarTextura();
				this->tronco.cambiarTextura();
				this->cabeza.cambiarTextura();
				this->vida -= 1;
				this->velocidad *= 1.6f;
				this->escala *= .7f;
			}
			else {
				++i;
			}
		}
	}
}

mat4 Enemigo::perseguirObjetivo(mat4 const& transform)
{
	//movimiento = final - inicial
	vec3 desplazamiento = this->objetivo->getPos() - vec3(this->posicion.x, .0f, this->posicion.y);

	//corregimos si las x se pasan del límite de velocidad
	if (desplazamiento.x > this->velocidad) {
		posicion.x += this->velocidad;
	}
	else if( desplazamiento.x < -this->velocidad)
	{
		posicion.x += -this->velocidad;
	}
	else {
		posicion.x += desplazamiento.x;
	}
	//corregimos si las z se pasan del límite de velocidad
	if (desplazamiento.z > this->velocidad) {
		posicion.y += this->velocidad;
	}
	else if (desplazamiento.z < -this->velocidad) 
	{
		posicion.y += -this->velocidad;
	}
	else
	{
		posicion.y += desplazamiento.z;
	}

	return translate(transform, vec3(this->posicion.x, 0.0f, this->posicion.y));
}


Enemigo::Enemigo(LocalizadorShader* locshader, Tanque* objetivo, vec2 posOriginal)
{
	this->id = idEnemigo;
	++idEnemigo;
	
	this->objetivo = objetivo;
	this->locshader = locshader;
	this->objetivo = objetivo;

	this->escala = .6f;
	this->vida = 3;
	this->velocidad = .001f;

	this->posicion = posOriginal;

	vector<string> texturas;
	texturas.push_back(string("green.jpg"));
	texturas.push_back(string("naranja.jpg"));
	texturas.push_back(string("red.jpg"));

	this->base = BloqueNormal(this->escala * vec3(.3f, .1f, .3f), vec3(), texturas, this->locshader);
	this->tronco = BloqueNormal(this->escala * vec3(.2f, .3f, .2f), vec3(), texturas, this->locshader);
	this->cabeza = BloqueNormal(this->escala * vec3(.35f, .35f, .35f), vec3(), texturas, this->locshader);

}

void Enemigo::actualizar()
{
	//matriz de transformación original
	mat4 transform = mat4();
	//lo elevamos para que esté por encima del suelo
	transform = translate(transform, this->escala * vec3(.0f, .1f, .0f));
	//lo desplazamos y asignamos a la base
	//transform = translate(transform, this->escala * vec3(posicion.x, .0f, posicion.y));
	transform = perseguirObjetivo(transform);
	this->base.actualizar(transform);
	//subimos un poco más para el tronco
	transform = translate(transform, this->escala * vec3(.0f, .1f, .0f));
	this->tronco.actualizar(transform);
	//subimos un poco más para la cabeza
	transform = translate(transform, this->escala * vec3(.0f, .2f, .0f));
	this->cabeza.actualizar(transform);

	//si le ha tocado una bala la destruye (actualizando textura, vida y velocidad del tanque)
	this->leHanDado();
}

void Enemigo::dibujar()
{
	this->base.dibujar();
	this->tronco.dibujar();
	this->cabeza.dibujar();
}

int Enemigo::getVida()
{
	return this->vida;
}

BoundingBox Enemigo::getBoundignBox()
{
	return this->cabeza.getBoundingBox();
}

void Enemigo::aumentarVelocidad(float aumento)
{
	this->velocidad *= aumento;
}

unsigned Enemigo::getId()
{
	return this->id;
}

void Enemigo::resetIdEnemigo()
{
	idEnemigo = 1;
}



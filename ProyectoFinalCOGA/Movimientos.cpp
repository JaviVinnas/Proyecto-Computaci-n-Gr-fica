#include "Movimientos.h"

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Movimiento1d::Movimiento1d()
{
	this->teclasAumentoDecremento = uvec2(GLFW_KEY_A, GLFW_KEY_B);
	this->valorDesplazamiento = 0.0f;
	this->aumento = 0.0f;
	this->bloqueado = false;
	this->lento = false;
}

Movimiento1d::Movimiento1d(uvec2 const &teclasAumentoDecremento, float const &aumento, float const &valorDesplazamiento)
{
	this->teclasAumentoDecremento = teclasAumentoDecremento;
	this->valorDesplazamiento = valorDesplazamiento;
	this->aumento = aumento;
	this->bloqueado = false;
	this->lento = false;
}

float Movimiento1d::getValorDesplazamiento()
{
	return this->valorDesplazamiento;
}

void Movimiento1d::checkCambios(GLFWwindow *window)
{
	if (this->bloqueado == false) {
		if (glfwGetKey(window, this->teclasAumentoDecremento.x) == GLFW_PRESS)
		{
			this->lento ? this->valorDesplazamiento += this->aumento * .5 : this->valorDesplazamiento += this->aumento;
		}
		if (glfwGetKey(window, this->teclasAumentoDecremento.y) == GLFW_PRESS)
		{
			this->lento ? this->valorDesplazamiento -= this->aumento * .5 : this->valorDesplazamiento -= this->aumento;
		}
	}
}

void Movimiento1d::setBloqueado(bool bloq)
{
	this->bloqueado = bloq;
}

void Movimiento1d::setLento(bool lento)
{
	this->lento = lento;
}

void Movimiento1d::forzarMovimiento(float mov)
{
	this->valorDesplazamiento += mov;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Movimiento1dLimites::Movimiento1dLimites() : Movimiento1d()
{
	this->limiteGrados = 360.0f;
}

Movimiento1dLimites::Movimiento1dLimites(uvec2 const &teclasAumentoDecremento, float const &aumento, float const &valorDesplazamiento, float const &limiteGrados)
	: Movimiento1d(teclasAumentoDecremento, aumento, valorDesplazamiento)
{
	this->limiteGrados = limiteGrados;
}

void Movimiento1dLimites::checkCambios(GLFWwindow *window)
{
	if (glfwGetKey(window, this->teclasAumentoDecremento.x) == GLFW_PRESS)
	{
		this->valorDesplazamiento += this->aumento;
	}
	if (glfwGetKey(window, this->teclasAumentoDecremento.y) == GLFW_PRESS)
	{
		this->valorDesplazamiento -= this->aumento;
	}

	if (round(this->limiteGrados) == 360.0f)
	{ //como una camara
		if (this->valorDesplazamiento > this->limiteGrados)
		{
			this->valorDesplazamiento -= this->limiteGrados;
		}
		if (this->valorDesplazamiento < -this->getValorDesplazamiento())
		{
			this->valorDesplazamiento += this->limiteGrados;
		}
	}
	else //como una articulacion
	{
		if (this->valorDesplazamiento > this->limiteGrados)
		{
			this->valorDesplazamiento = this->limiteGrados;
		}
		if (this->valorDesplazamiento < -this->limiteGrados)
		{
			this->valorDesplazamiento = -this->limiteGrados;
		}
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Movimiento2d::Movimiento2d()
{
	this->movA = Movimiento1d(uvec2(GLFW_KEY_W, GLFW_KEY_S), .01f, 0.0f);
	this->movB = Movimiento1d(uvec2(GLFW_KEY_A, GLFW_KEY_D), .01f, 0.0f);
}

Movimiento2d::Movimiento2d(uvec2 const &teclasAumentoDecrecimiento_A, uvec2 const &teclasAumentoDecrecimiento_B, float const &aumento, vec2 const &valorDesplazamiento)
{
	this->movA = Movimiento1d(teclasAumentoDecrecimiento_A, aumento, valorDesplazamiento.x);
	this->movB = Movimiento1d(teclasAumentoDecrecimiento_B, aumento, valorDesplazamiento.y);
}

void Movimiento2d::checkCambios(GLFWwindow *window)
{
	this->movA.checkCambios(window);
	this->movB.checkCambios(window);
}

vec2 Movimiento2d::getMov()
{
	return vec2(this->movA.getValorDesplazamiento(), this->movB.getValorDesplazamiento());
}

void Movimiento2d::setBloqueado(bool bloc)
{
	this->movA.setBloqueado(bloc);
	this->movB.setBloqueado(bloc);
}

void Movimiento2d::setLento(bool lento)
{
	this->movA.setLento(lento);
	this->movB.setLento(lento);
}

void Movimiento2d::forzarMovimiento(vec2 mov)
{
	this->movA.forzarMovimiento(mov.x);
	this->movB.forzarMovimiento(mov.y);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Movimiento2dLimites::Movimiento2dLimites()
{
	this->movA = Movimiento1dLimites(uvec2(GLFW_KEY_W, GLFW_KEY_S), .01f, 0.0f, 360.0f);
	this->movB = Movimiento1dLimites(uvec2(GLFW_KEY_A, GLFW_KEY_D), .01f, 0.0f, 360.0f);
}

Movimiento2dLimites::Movimiento2dLimites(uvec2 const &teclasAumentoDecrecimiento_A, uvec2 const &teclasAumentoDecrecimiento_B, float const &aumento, vec2 const &valorDesplazamiento, float const &limiteGrados)
{
	this->movA = Movimiento1dLimites(teclasAumentoDecrecimiento_A, aumento, valorDesplazamiento.x, limiteGrados);
	this->movB = Movimiento1dLimites(teclasAumentoDecrecimiento_B, aumento, valorDesplazamiento.y, limiteGrados);
}

void Movimiento2dLimites::checkCambios(GLFWwindow *window)
{
	this->movA.checkCambios(window);
	this->movB.checkCambios(window);
}

vec2 Movimiento2dLimites::getMov()
{
	return vec2(this->movA.getValorDesplazamiento(), this->movB.getValorDesplazamiento());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

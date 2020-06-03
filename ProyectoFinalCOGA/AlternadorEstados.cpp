#include "AlternadorEstados.h"

AbstractAlternadorEstados::AbstractAlternadorEstados()
{
	this->estadoActual = VACIO;
}

bool AbstractAlternadorEstados::esVacio()
{
	return this->estadoActual == VACIO;
}

unsigned AbstractAlternadorEstados::getEstadoActual()
{
	return this->estadoActual;
}

void AbstractAlternadorEstados::addEstado(unsigned estado)
{
	if (estado != VACIO)
	{
		//si no está introducido lo añadimos
		bool repetido = false;
		unsigned componente;
		//si no está vacío
		if (!this->esVacio())
		{
			//recorremos sus componentes
			for (auto i = this->estados.begin(); i < this->estados.end(); i++)
			{
				componente = *i;
				if (componente == estado)
				{
					repetido = true;
					break;
				}
			}
		}

		if (!repetido)
		{
			//lo añadimos
			estados.push_back(estado);
			if (this->estadoActual == VACIO)
			{
				this->estadoActual = estado;
			}
		}
	}
	else
	{
		cout << "Valor no permitido para el alternador de estados" << endl;
	}
}

void AbstractAlternadorEstados::siguenteEstado()
{
	bool cambiar = false;
	unsigned componente;

	//si el vector tiene componentes
	if (!this->esVacio())
	{
		//recorremos sus componentes
		for (auto i = this->estados.begin(); i != this->estados.end(); i++)
		{
			componente = *i;
			//vemos que si tenemos que cambiarlo
			if (cambiar)
			{
				this->estadoActual = componente;
				break;
			}
			else
			{
				if (componente == this->estadoActual)
				{
					cambiar = true;
					//vemos si estamos al final del vector
					if (componente == this->estados[this->estados.size() - 1])
					{
						this->estadoActual = this->estados[0];
						break;
					}
				}
			}
		}
	}
	else
	{
		cout << "No hay estados entre los que alternar para el alternador de estados" << endl;
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

AlternadorEstadosTecla::AlternadorEstadosTecla() : AbstractAlternadorEstados()
{
	this->tecla = GLFW_KEY_P;
	this->window = NULL;
}

AlternadorEstadosTecla::AlternadorEstadosTecla(unsigned tecla, GLFWwindow* window) : AbstractAlternadorEstados()
{
	this->tecla = tecla;
	this->window = window;
}

void AlternadorEstadosTecla::cambiarEstado()
{
	if (glfwGetKey(this->window, this->tecla) == GLFW_PRESS)
	{
		this->siguenteEstado();
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

AlternadorEstadosEvento::AlternadorEstadosEvento() : AbstractAlternadorEstados() {}

void AlternadorEstadosEvento::cambiarEstado()
{
	this->siguenteEstado();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

AlternadorEstadosTemporizador::AlternadorEstadosTemporizador() : AbstractAlternadorEstados()
{
	this->temporizador = Temporizador();
}

AlternadorEstadosTemporizador::AlternadorEstadosTemporizador(Temporizador temporizador) : AbstractAlternadorEstados()
{
	this->temporizador = temporizador;
}

void AlternadorEstadosTemporizador::cambiarEstado()
{
	//llama la función cada segundo
	if (this->temporizador.suenaAlarmaPeriodica(1))
	{
		this->siguenteEstado();
	}
}

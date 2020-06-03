#pragma once

#ifndef LOCALIZADOR_SHADER_H
#include "LocalizadorShader.h"
#endif // !LOCALIZADOR_SHADER_H

#ifndef MOVIMIENTOS_H
#include "Movimientos.h"
#endif // !MOVIMIENTOS_H

#ifndef BOUNDING_BOX_H
#include "BoundingBox.h"
#endif // !BOUNDINGBOX_H

#ifndef TEXTURAS_H
#include "Texturas.h"
#endif // !TEXTURAS_H

#ifndef ALTERNADOR_ESTADOS_H
#include "AlternadorEstados.h"
#endif // !ALTERNADORESTADOS_H

#ifndef BLOQUE_H
#include "Bloque.h"
#endif // !BLOQUE_H

#ifndef CAMARA_H
#include "Camara.h"
#endif // !CAMARA_H

#ifndef TANQUE_H
#include "Tanque.h"
#endif // !TANQUE_H

#ifndef ENEMIGO_H
#include "Enemigo.h"
#endif // !ENEMIGO_H

#ifndef GENERADOR_ENEMIGOS_H
#include "GeneradorEnemigos.h"
#endif // !GENERADOR_ENEMIGOS_H

#ifndef ESCENARIO_H
#include "Escenario.h"
#endif // !ESCENARIO_H


class Juego
{
private:
	//variables
	Camara * camara;
	Escenario * escenario;
	Tanque * tanque;
	GeneradorEnemigos * generadorEnemigos;
	unsigned * anchoPantalla;
	unsigned * altoPantalla;
	//metodos privados (para la actualización sobre todo)
	void TextoWelcome();
public:
	Juego(GLFWwindow* window, LocalizadorShader* locShader, unsigned* anchoPantalla, unsigned* altoPantalla);
	~Juego();
	//actualiza los parámetros del juego 
	void actualizar();
	//plasma por pantalla lo que haya que plasmar
	void dibujar();
};


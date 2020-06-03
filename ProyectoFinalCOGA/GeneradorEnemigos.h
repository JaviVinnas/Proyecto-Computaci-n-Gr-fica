#pragma once

#ifndef ENEMIGO_H
#include "Enemigo.h"
#endif // !ENEMIGO_H

#ifndef STDLIB_H
#include <stdlib.h>
#endif // !STDLIB_H

#ifndef TIME_H
#include <time.h>
#endif // !TIME_H

#ifndef ESCENARIO_H
#include "Escenario.h"
#endif // !ESCENARIO_H

#ifndef TANQUE_H
#include "Tanque.h"
#endif // !TANQUE_H



class GeneradorEnemigos
{
private:
	vector<Enemigo> enemigos;
	LocalizadorShader* locshader;
	Tanque* objetivo;
	Escenario* escenario;
	Temporizador temporizador;
	unsigned numEnemigosMatados;
	unsigned numEnemigosGenerados;
	unsigned tiempoEntreGenEnemigos;
	vec2 generarPosInicioEnemigo();
	//devuelve true si hace falta resetear el tanque
	bool choqtanque();
	void haPerdido();
	void choqueEntreEnemigos();
public:
	GeneradorEnemigos(LocalizadorShader* locshader, Tanque* objetivo, Escenario* escenario);
	void actualizar();
	void dibujar();
	void reset();
};


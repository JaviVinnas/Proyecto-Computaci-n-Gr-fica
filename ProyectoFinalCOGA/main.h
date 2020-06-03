#pragma once

//headers no definidos por mi irian aqui arriba
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

#ifndef PISCINA_H
#include "Piscina.h"
#endif // !PISCINA_H


#ifndef JUEGO_H
#include "Juego.h"
#endif // !JUEGO_H







// settings
unsigned int SCR_WIDTH = 800;
unsigned int SCR_HEIGHT = 800;
GLuint shaderProgram;
extern GLuint setShaders(const char* nVertx, const char* nFrag);


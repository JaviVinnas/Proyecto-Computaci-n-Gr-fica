#pragma once

#ifndef GLM_HPP
#include <glm/glm.hpp>
#endif // !GLM_HPP

#ifndef MATRIX_TRANSFORM_HPP
#include <glm/gtc/matrix_transform.hpp>
#endif // !MATRIX_TRANSFORM_HPP

#ifndef TYPE_PTR_HPP
#include <glm/gtc/type_ptr.hpp>
#endif // !TYPE_PTR_HPP

#ifndef GLFW3_H
#include <glfw3.h>
#endif // !GLFW3_H

#ifndef ALTERNADOR_ESTADOS_H
#include "AlternadorEstados.h"
#endif // !ALTERNADORESTADOS_H

#ifndef MOVIMIENTOS_H
#include "Movimientos.h"
#endif // !MOVIMIENTOS_H

#ifndef LOCALIZADOR_SHADER_H
#include "LocalizadorShader.h"
#endif // !LOCALIZADOR_SHADER_H

#ifndef TANQUE_H
#include "Tanque.h"
#endif // !TANQUE_H

using namespace glm;

//modos de cámara
#define PRIMERA_PERSONA  1
#define EXTERIOR  3

class Camara
{
private:
    mat4 matView;
    mat4 matProyeccion;
    Pulsador pulsadorModosCamara;
    AlternadorEstadosTecla modosCamara;
    Movimiento1d movZoom;
    Movimiento2dLimites movCamara;
    GLFWwindow* window;
    vec2 anchoAlto;
    LocalizadorShader *locShader;
    void iniciarModosCamara();
public:
    Camara();
    Camara(GLFWwindow* window, LocalizadorShader* locshader);
    void actualizar(uvec2 anchoAlto, Tanque * tanque);
    void cargarCamara();
};


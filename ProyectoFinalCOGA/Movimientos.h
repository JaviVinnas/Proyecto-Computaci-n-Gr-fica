
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

#ifndef CMATH
#include <cmath>
#endif // !CMATH

using namespace glm;

class Movimiento1d;
class Movimiento1dLimites;
class Movimiento2d;
class Movimiento2dLimites;

class Movimiento1d
{
friend class Movimiento1dLimites;
private:
    float valorDesplazamiento;
    uvec2 teclasAumentoDecremento;
    float aumento;
    bool bloqueado;
    bool lento;

public:
    Movimiento1d();
    Movimiento1d(uvec2 const &teclasAumentoDecremento, float const &aumento, float const &valorDesplazamiento);
    float getValorDesplazamiento();
    void checkCambios(GLFWwindow *window);
    void setBloqueado(bool bloq);
    void setLento(bool lento);
    void forzarMovimiento(float mov);
};

/*si limite grados = 360 cuando se llegue a ese valor se restará -360 y viceversa (movimiento como una cámara o la rotación de la grúa)
si no cuando llegue a ese valor, se parará ahí (como una articulación)*/
class Movimiento1dLimites : public Movimiento1d
{
private:
    float limiteGrados;

public:
    Movimiento1dLimites();
    Movimiento1dLimites(uvec2 const &teclasAumentoDecremento, float const &aumento, float const &valorDesplazamiento, float const &limiteGrados);
    void checkCambios(GLFWwindow *window);
};

class Movimiento2d
{
private:
    Movimiento1d movA;
    Movimiento1d movB;

public:
    Movimiento2d();
    Movimiento2d(uvec2 const &teclasAumentoDecrecimiento_A, uvec2 const &teclasAumentoDecrecimiento_B, float const &aumento, vec2 const &valorDesplazamiento);
    void checkCambios(GLFWwindow *window);
    vec2 getMov();
    void setBloqueado(bool bloc);
    void setLento(bool lento);
    void forzarMovimiento(vec2 mov);
};

class Movimiento2dLimites
{
private:
    Movimiento1dLimites movA;
    Movimiento1dLimites movB;

public:
    Movimiento2dLimites();
    Movimiento2dLimites(uvec2 const& teclasAumentoDecrecimiento_A, uvec2 const& teclasAumentoDecrecimiento_B, float const& aumento, vec2 const& valorDesplazamiento, float const& limiteGrados);
    void checkCambios(GLFWwindow *window);
    vec2 getMov();
};


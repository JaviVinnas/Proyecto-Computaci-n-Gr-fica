#pragma once
#ifndef GLAD_H
#include <glad.h>
#endif // !GLAD_H

#ifndef GLM_HPP
#include <glm/glm.hpp>
#endif // !GLM_HPP

#ifndef MATRIX_TRANSFORM_HPP
#include <glm/gtc/matrix_transform.hpp>
#endif // !MATRIX_TRANSFORM_HPP

#ifndef TYPE_PTR_HPP
#include <glm/gtc/type_ptr.hpp>
#endif // !TYPE_PTR_HPP

#ifndef CMATH
#include <cmath>
#endif // !CMATH


using namespace glm;

class LocalizadorShader;
class LocalizadorVertexShader;
class LocalizadorFragmentShader;

class LocalizadorShader
{
private:
    //vertex shader
    class LocalizadorVertexShader
    {
    private:
        unsigned view;
        unsigned projection;
        unsigned model;

    public:
        LocalizadorVertexShader();
        LocalizadorVertexShader(GLuint shaderProgram);
        void cargarView(mat4 const &matrix);
        void cargarProjection(mat4 const &matrix);
        void cargarModel(mat4 const &matrix);
        void cargarObjetoyDibujar(GLuint vaoObjeto);
    };
    //fragment shader
    class LocalizadorFragmentShader
    {
    private:
        //color de la luz
        unsigned lightColor;
        //posición de la luz
        unsigned lightPos;
        //posición del observador
        unsigned viewPos;
        //2texturas (2 unsigned ints)
        uvec2 texturas;
        //color de la luz actual
        vec3 lightColorActual;

    public:
        LocalizadorFragmentShader();
        LocalizadorFragmentShader(GLuint const &shaderProgram);
        void cargarColorLuz(vec3 const &lightColor);
        void cargarPosiciónLuz(vec3 const &lightPos);
        void cargarPosicionEspectador(vec3 const &viewPos);
        void cargarTexturas(uvec2 const &texturas);
        vec3 getLightColorActual();
    };
    LocalizadorVertexShader locVertexShader;
    LocalizadorFragmentShader locFragmentShader;

public:
    LocalizadorShader();
    LocalizadorShader(GLuint shaderProgram);
    //vertex
    void cargarView(mat4 const &matrix);
    void cargarProjection(mat4 const &matrix);
    void cargarModel(mat4 const &matrix);
    void cargarObjetoyDibujar(GLuint vaoObjeto);
    //fragment
    void cargarColorLuz(vec3 const &lightColor);
    void cargarPosicionLuz(vec3 const &lightPos);
    void cargarPosicionEspectador(vec3 const &viewPos);
    void cargarTexturas(uvec2 const &texturas);
    vec3 getLightColorActual();
};

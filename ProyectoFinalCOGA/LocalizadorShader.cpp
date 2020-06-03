#include "LocalizadorShader.h"

////////////////////////////////////////////////////////////////////////////////////////////////////
//VERTEX SHADER/////////////////////////////////////////////////////////////////////////////////////
LocalizadorShader::LocalizadorVertexShader::LocalizadorVertexShader()
{
    this->view = 0;
    this->projection = 0;
    this->model = 0;
}

LocalizadorShader::LocalizadorVertexShader::LocalizadorVertexShader(GLuint shaderProgram)
{
    //model
    this->model = glGetUniformLocation(shaderProgram, "model");
    glUniformMatrix4fv(this->model, 1, GL_FALSE, value_ptr(mat4()));
    //view
    this->view = glGetUniformLocation(shaderProgram, "view");
    glUniformMatrix4fv(this->view, 1, GL_FALSE, value_ptr(mat4()));
    //projection
    this->projection = glGetUniformLocation(shaderProgram, "projection");
    glUniformMatrix4fv(this->projection, 1, GL_FALSE, value_ptr(mat4()));
}

void LocalizadorShader::LocalizadorVertexShader::cargarView(mat4 const &matrix)
{
    glUniformMatrix4fv(this->view, 1, GL_FALSE, value_ptr(matrix));
}

void LocalizadorShader::LocalizadorVertexShader::cargarProjection(mat4 const &matrix)
{
    glUniformMatrix4fv(this->projection, 1, GL_FALSE, value_ptr(matrix));
}

void LocalizadorShader::LocalizadorVertexShader::cargarModel(mat4 const &matrix)
{
    glUniformMatrix4fv(this->model, 1, GL_FALSE, value_ptr(matrix));
}

void LocalizadorShader::LocalizadorVertexShader::cargarObjetoyDibujar(GLuint vaoObjeto)
{
    glPolygonMode(GL_FRONT, GL_FILL);
    glBindVertexArray(vaoObjeto);
    glDrawArrays(GL_TRIANGLES, 0, 36 * 20 * 20);
}



////////////////////////////////////////////////////////////////////////////////////////////////////
//FRAGMENT SHADER/////////////////////////////////////////////////////////////////////////////////////
LocalizadorShader::LocalizadorFragmentShader::LocalizadorFragmentShader()
{
    this->lightColor = 0;
    this->lightPos = 0;
    this->viewPos = 0;
    this->texturas = uvec2(0, 0);
}

LocalizadorShader::LocalizadorFragmentShader::LocalizadorFragmentShader(GLuint const &shaderProgram)
{
    //lightColor
    this->lightColor = glGetUniformLocation(shaderProgram, "lightColor");
    glUniform3f(this->lightColor, 1.0f, 1.0f, 1.0f); //luz blanca de forma predeterminada
    this->lightColorActual = vec3(1.0f, 1.0f, 1.0f);
    //lightPos
    this->lightPos = glGetUniformLocation(shaderProgram, "lightPos");
    glUniform3f(this->lightPos, 0.0f, 1.0f, 0.0f); //arriba en el centro como pos predeterminada
    //viewPos
    this->viewPos = glGetUniformLocation(shaderProgram, "viewPos");
    glUniform3f(this->viewPos, 1.0f, 1.0f, 1.0f); //1,1,1 como pos predeterminada
    //texturas
    this->texturas.x = glGetUniformLocation(shaderProgram, "texture1");
    this->texturas.y = glGetUniformLocation(shaderProgram, "texture2");
    glUniform1i(this->texturas.x, 0);
    glUniform1i(this->texturas.y, 1);
}

void LocalizadorShader::LocalizadorFragmentShader::cargarColorLuz(vec3 const &lightColor)
{
    glUniform3f(this->lightColor, lightColor.x, lightColor.y, lightColor.z);
    this->lightColorActual = lightColor;
}

void LocalizadorShader::LocalizadorFragmentShader::cargarPosiciónLuz(vec3 const &lightPos)
{
    glUniform3f(this->lightPos, lightPos.x, lightPos.y, lightPos.z);
}

void LocalizadorShader::LocalizadorFragmentShader::cargarPosicionEspectador(vec3 const &viewPos)
{
    glUniform3f(this->viewPos, viewPos.x, viewPos.y, viewPos.z);
}

void LocalizadorShader::LocalizadorFragmentShader::cargarTexturas(uvec2 const &texturas)
{
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texturas.x);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, texturas.y);
}

vec3 LocalizadorShader::LocalizadorFragmentShader::getLightColorActual()
{
    return this->lightColorActual;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
//SHADER COMPLETO/////////////////////////////////////////////////////////////////////////////////////

LocalizadorShader::LocalizadorShader()
{
    this->locVertexShader = LocalizadorVertexShader();
    this->locFragmentShader = LocalizadorFragmentShader();
}

LocalizadorShader::LocalizadorShader(GLuint shaderProgram)
{
    this->locVertexShader = LocalizadorVertexShader(shaderProgram);
    this->locFragmentShader = LocalizadorFragmentShader(shaderProgram);
}

void LocalizadorShader::cargarView(mat4 const &matrix)
{
    this->locVertexShader.cargarView(matrix);
}

void LocalizadorShader::cargarProjection(mat4 const &matrix)
{
    this->locVertexShader.cargarProjection(matrix);
}

void LocalizadorShader::cargarModel(mat4 const &matrix)
{
    this->locVertexShader.cargarModel(matrix);
}

void LocalizadorShader::cargarObjetoyDibujar(GLuint vaoObjeto)
{
    this->locVertexShader.cargarObjetoyDibujar(vaoObjeto);
}

void LocalizadorShader::cargarColorLuz(vec3 const &lightColor)
{
    this->locFragmentShader.cargarColorLuz(lightColor);
}

void LocalizadorShader::cargarPosicionLuz(vec3 const &lightPos)
{
    this->locFragmentShader.cargarPosiciónLuz(lightPos);
}

void LocalizadorShader::cargarPosicionEspectador(vec3 const &viewPos)
{
    this->locFragmentShader.cargarPosicionEspectador(viewPos);
}

void LocalizadorShader::cargarTexturas(uvec2 const &texturas)
{
    this->locFragmentShader.cargarTexturas(texturas);
}

vec3 LocalizadorShader::getLightColorActual()
{
    return this->locFragmentShader.getLightColorActual();
}

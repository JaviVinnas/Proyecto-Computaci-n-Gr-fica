#include "Temporizador.h"

Temporizador::Temporizador(double segundosParaLaAlarma){
    this->setAlarma(segundosParaLaAlarma);
}

void Temporizador::setAlarma(double segundosParaLaAlarma)
{
    this->segundosInicio = glfwGetTime();
    this->segundosParaLaAlarma = segundosParaLaAlarma;
}

bool Temporizador::suenaAlarma()
{
    double tFinal = glfwGetTime();

    return (tFinal - this->segundosInicio) > this->segundosParaLaAlarma;

}


bool Temporizador::suenaAlarmaPeriodica(unsigned secsEntreAlarmas)
{
    //tiempo serán los segundos desde que se ejecutó el programa
    double tiempo = glfwGetTime();
    //un tiempo del estilo 2,45689 se transformaría en 245,689
    double tiempoAux = tiempo * 100;
    //cada segundo exacto entra en el if
    if ((int)tiempoAux % 100 == 0)
    {
        return ((int)trunc(tiempo) % secsEntreAlarmas == 0);
    }
    else
    {
        return false;
    }
}
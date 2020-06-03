#pragma once

#ifndef GLFW3_H
#include <glfw3.h>
#endif // !GLFW3_H

#ifndef CMATH
#include <cmath>
#endif // !CMATH

class Temporizador;

class Temporizador
{
private:
    //se carga con los segundos que lleve el programa en ejecución de forma predeterminada
    //cada vez que se pone una alarma se vuelve a poner así
    double segundosInicio;
    double segundosParaLaAlarma;
public:
    //se pone una alarma para 6 segundos desde que se crea
    Temporizador(double segundosParaLaAlarma = 6.0);
    //pone una alarma que sonará después de segundosParaLaAlarma secs desde que se llame a la función
    void setAlarma(double segundosParaLaAlarma = 6.0);
    //comprueba si ya está sonando la alarma
    bool suenaAlarma();
    //devuelve true cada secsEntreAlarmas segundos
    bool suenaAlarmaPeriodica(unsigned secsEntreAlarmas);

};

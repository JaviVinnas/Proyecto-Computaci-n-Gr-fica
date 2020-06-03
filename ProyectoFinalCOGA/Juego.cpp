#include "Juego.h"



void Juego::TextoWelcome()
{
	cout << "                    |||||||||||||||||||||||||||||||||||||              " << endl;
	cout << "     |||||||        |||||||||||||||||||||||||||||||||||||              " << endl;
	cout << "     ||||||||||||||||||||||||||||||||||||||||||||||||||||              " << endl;
	cout << "     |||||||        |||||||||||||||||||||||||||||||||||||              " << endl;
	cout << "                    |||||||||||||||||||||||||||||||||||||              " << endl;
	cout << "|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||" << endl;
	cout << "|||||||||||||||||||||||||||||||||||||Tanques 1.0 ||||||||||||||||||||||" << endl;
	cout << "|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||" << endl;
	cout << "\n\n\n" << endl;
	cout << "Pulsa intro para continuar:" << endl;
	getchar();
	cout << "Tematica:" << endl;
	cout << "En este juego controlaras a un tanque que tendra que eliminar enemigos que vayan surgiendo de la arena, pero ";
	cout << "cuidado! cuando dispares los tanques seran mas veloces e iran mas rapido a por ti. Tanto los enemigos como tu ";
	cout << "tendreis tres vidas (verde naranja y rojo), que se reflejaran en el color del tanque o el enemigo, Si pierdes las tres vidas " ;
	cout << "se habra terminado la partida, pero si aguantas lo suficiente con 1 o con 2 se t regenerara progresivamente. Tu tanque puede aguantar un poco en el agua pero llegado un momento su vida empezara a bajar, " ;
	cout << "mientras que los enemigos son resistentes al agua" << endl;
	cout << "Pulsa intro para continuar:" << endl;
	getchar();
	cout << "Manual de usuario:" << endl;
	cout << "> Movimiento de la camara -> teclas ARRIBA, ABAJO, IZQUIERDA, DERECHA" << endl;
	cout << "> Acercar/Alejar cámara -> tecla +, -" << endl;
	cout << "> Movimiento del tanque -> teclas A, W, S, D" << endl;
	cout << "> Giro del cañon del tanque -> teclas N, M" << endl;
	cout << "> Disparar balas -> tecla BARRA ESPACIADORA" << endl;
	cout << "> Alternar entre modo normal y modo torreta -> tecla P" << endl;
	cout << "> |Nota| -> el modo torreta situa la camara en primera persona como si te estuvieras asomando por la escotilla del tanque ";
	cout << "En este modo se desactivan todos los movimientos excepto el de rotar el cañon y disparar." << endl;
	cout << "Pulsa intro para empezar la partida:" << endl;
	getchar();
}

Juego::Juego(GLFWwindow* window, LocalizadorShader* locShader, unsigned * anchoPantalla, unsigned * altoPantalla)
{
	this->TextoWelcome();
	this->camara = new Camara(window, locShader);
	this->escenario = new Escenario(locShader);
	this->tanque = new Tanque(window, locShader);
	this->generadorEnemigos = new GeneradorEnemigos(locShader, this->tanque, this->escenario);
	this->altoPantalla = altoPantalla;
	this->anchoPantalla = anchoPantalla;
}

Juego::~Juego()
{
	if (this->camara != nullptr) {
		delete this->camara;
	}
	if (this->tanque != nullptr) {
		delete this->tanque;
	}
	if (this->escenario != nullptr) {
		delete this->escenario;
	}
	if (this->generadorEnemigos != nullptr) {
		delete this->generadorEnemigos;
	}
}

void Juego::actualizar()
{
	this->camara->actualizar(uvec2(*this->anchoPantalla, *this->altoPantalla), this->tanque);
	if (this->tanque->actualizarTanque(this->escenario)) {
		this->generadorEnemigos->reset();
	}
	this->escenario->actualizar();
	this->generadorEnemigos->actualizar();
}

void Juego::dibujar()
{
	this->camara->cargarCamara(); //la cámara siempre va primero
	this->tanque->dibujar();
	this->escenario->dibujar();
	this->generadorEnemigos->dibujar();
}

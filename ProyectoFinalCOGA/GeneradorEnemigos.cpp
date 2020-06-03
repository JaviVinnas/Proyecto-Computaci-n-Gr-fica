#include "GeneradorEnemigos.h"

vec2 GeneradorEnemigos::generarPosInicioEnemigo()
{
	vec3 random, diff, r, res;

	vec3 max = this->escenario->getSuelo().getBoundingBox().getMax();
	vec3 min = this->escenario->getSuelo().getBoundingBox().getMin();
	vec3 maxTanque = 5.7f * this->objetivo->getBoundingBox().getMax();
	vec3 minTanque = 5.7f * this->objetivo->getBoundingBox().getMin();
	do
	{
		random.x = ((float)rand()) / (float)RAND_MAX;
		random.z = ((float)rand()) / (float)RAND_MAX;

		diff.x = this->escenario->getSuelo().getBoundingBox().getMax().x - this->escenario->getSuelo().getBoundingBox().getMin().x;
		diff.z = this->escenario->getSuelo().getBoundingBox().getMax().z - this->escenario->getSuelo().getBoundingBox().getMin().z;

		r.x = random.x * diff.x;
		r.z = random.z * diff.z;

		res.x = this->escenario->getSuelo().getBoundingBox().getMin().x + r.x;
		res.z = this->escenario->getSuelo().getBoundingBox().getMin().z + r.z;

	} while (
		(res.x > (5.7f * this->objetivo->getBoundingBox().getMin().x) && res.x < (5.7f * this->objetivo->getBoundingBox().getMax().x)) &&
		(res.z > (5.7f * this->objetivo->getBoundingBox().getMin().z) && res.z < (5.7f * this->objetivo->getBoundingBox().getMax().z))
		);

	return vec2(res.x, res.z);
}

bool GeneradorEnemigos::choqtanque()
{
	bool reset = false;

	for (auto i = this->enemigos.begin(); i != this->enemigos.end();) {
		if (i->getBoundignBox().colisionanAABB(this->objetivo->getBoundingBox())) {
			//un enemigo ha tocado el tanque
			//borramos el enemigo
			i = this->enemigos.erase(i);
			this->objetivo->getTextsVida()->cambiarTextura();
			this->objetivo->setVida(this->objetivo->getVida() -1);
			this->objetivo->resetTemporizadorRegenVida();
			if (this->objetivo->getVida() == 0) {
				this->haPerdido();
				reset = true;
			}
			else {
				cout << "un enemigo ha tocado el tanque " << endl;
				cout << "Su vida ahora es ->" << this->objetivo->getVida() << endl;
			}
		}
		else {
			++i;
		}
	}
	return reset;
}

void GeneradorEnemigos::haPerdido()
{
	cout << "Vaya! Te has quedao sin vidas :(" << endl;
	cout << "numero de enemigos matados -> " << this->numEnemigosMatados << endl;
	cout << "presione intro para jugar otra partida" << endl;
	getchar();
	this->objetivo->reset();
}

void GeneradorEnemigos::choqueEntreEnemigos()
{
	for (auto i = this->enemigos.begin(); i != this->enemigos.end();) {
		for (auto j = this->enemigos.begin(); j != this->enemigos.end();) {
			//para dos enemigos i, j que colisionen
			if (i->getBoundignBox().colisionanAABB(j->getBoundignBox()) && (i->getId() != j->getId())) {
				//eliminaremos uno y subiremos la velocidad al otro
				j = this->enemigos.erase(j);
				i->aumentarVelocidad(1.45f);
				cout << "Dos enemigos se han chocado! -> el enemigo superviviente aumenta de velocidad" << endl;
			}
			else
			{
				++j;
			}
		}
		++i;
	}
}

GeneradorEnemigos::GeneradorEnemigos(LocalizadorShader* locshader, Tanque* objetivo, Escenario* escenario)
{
	this->locshader = locshader;
	this->objetivo = objetivo;
	this->escenario = escenario;
	this->enemigos = vector<Enemigo>();
	this->temporizador = Temporizador(8);
	this->numEnemigosMatados = 0;
	this->numEnemigosGenerados = 0;
	this->tiempoEntreGenEnemigos = 6;
	srand((unsigned)time(NULL));
}

void GeneradorEnemigos::actualizar()
{
	//generamos enemigos cada 5 segundos inicialmente segundos
	if (temporizador.suenaAlarmaPeriodica(this->tiempoEntreGenEnemigos)) {
		Enemigo enemigo = Enemigo(this->locshader, this->objetivo, generarPosInicioEnemigo());
		this->enemigos.push_back(enemigo);
		++this->numEnemigosGenerados;
		cout << "Cuidado! el enemigo " << this->numEnemigosGenerados << "se ha generado y va a por ti!" << endl;
	}

	//actualizamos los enemigos existentes o los borramos si hay alguno con vida negativa
	for (auto i = this->enemigos.begin(); i != this->enemigos.end();) {
		//actualizamos
		i->actualizar();
		if (i->getVida() <= 0) {
			i = this->enemigos.erase(i);
			++this->numEnemigosMatados;
			cout << "has eliminado al enemigo " << this->numEnemigosMatados << endl;
			switch (numEnemigosMatados)
			{
			case 5:
				cout << "has matado a 5 enemigos!" << endl;
				cout << "subiendo dificultad..." << endl;
				this->tiempoEntreGenEnemigos = 4;
				break;
			case 10:
				cout << "has matado a 10 enemigos!" << endl;
				cout << "subiendo dificultad..." << endl;
				this->tiempoEntreGenEnemigos = 3;
				break;
			case 15:
				cout << "has matado a 15 enemigos!" << endl;
				cout << "subiendo dificultad..." << endl;
				this->tiempoEntreGenEnemigos = 1;
				break;

			default:
				break;
			}
		}
		else
		{
			++i;
		}
	}

	

	//vemos si algún enemigo ha tocado nuestro tanque y realizamos las acciones oportunas
	if (this->choqtanque()) {
		this->reset();
	};
	
	//vemos si hubo algún tipo de choque entre los enemigos generados
	this->choqueEntreEnemigos();
}

void GeneradorEnemigos::dibujar()
{
	for (auto i = this->enemigos.begin(); i != this->enemigos.end(); i++) {
		i->dibujar();
	}
}

void GeneradorEnemigos::reset()
{
	this->enemigos.clear();
	this->temporizador = Temporizador(8);
	this->numEnemigosMatados = 0;
	this->numEnemigosGenerados = 0;
	this->tiempoEntreGenEnemigos = 6;
}

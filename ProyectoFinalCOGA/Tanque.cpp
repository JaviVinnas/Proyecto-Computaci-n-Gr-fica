#include "Tanque.h"

mat4 Tanque::moverTanque(mat4 const& transform)
{
	mat4 transfmaux;
	this->movTanque.setLento(this->lento);
	this->movTanque.setBloqueado(this->bloquearMov);
	this->movTanque.checkCambios(this->window);
	vec2 mov = this->movTanque.getMov();
	transfmaux = translate(transform, this->escala * vec3(mov.x, 0.0f, mov.y));
	return transfmaux;

}

mat4 Tanque::girarCannon(mat4 const& transform)
{
	mat4 transfmaux;
	this->movCannon.checkCambios(this->window);
	float mov = this->movCannon.getValorDesplazamiento();
	transfmaux = rotate(transform, radians(mov), vec3(0.0f, 1.0f, 0.0f));
	return transfmaux;
}

void Tanque::crearBala(mat4 const& transform)
{
	if (botonDisparar.sePulsa()) {
		++this->contBalas;
		cout << "Pum! se ha disparado una bala (numero de balas disparadas -> " << this->contBalas << ")" << endl;
		Bala bala = Bala(transform, this->locshader);
		this->balasDisparadas.push_back(bala);
	}
}

void Tanque::actualizarBala()
{
	for (auto i = this->balasDisparadas.begin(); i != this->balasDisparadas.end(); i++)
	{
		i->actualizar();
	}
}

void Tanque::borrarBala()
{
	for (auto i = this->balasDisparadas.begin(); i != this->balasDisparadas.end();)
	{
		if (i->leTocaMorir()) {
			i = this->balasDisparadas.erase(i);
		}
		else
		{
			++i;
		}
	}
}

void Tanque::salirseDelSuelo(Escenario* escenario)
{
	int situacion;
	//
	if (!this->base.getBoundingBox().contenidoEn(escenario->getSuelo().getBoundingBox(), "000", &situacion)) {
		switch (situacion)
		{
			//se sale por -x
		case 1:
			this->movTanque.forzarMovimiento(vec2(.1f, .0f));
			break;
			//se sale por +x
		case 2:
			this->movTanque.forzarMovimiento(vec2(-.1f, .0f));
			break;
			//salirse por -z
		case 5:
			this->movTanque.forzarMovimiento(vec2(.0f, .1f));
			break;
			//salirse por +z
		case 6:
			this->movTanque.forzarMovimiento(vec2(.0f, -.1f));
			break;

		default:
			break;
		}
	}
}

void Tanque::tocaPiscina(Escenario* escenario)
{
	//recorremos el vector de piscinas
	vector<Piscina> piscs = escenario->getPiscinas();
	for (auto i = piscs.begin(); i != piscs.end(); ++i)
	{
		//vemos si colisiona alguna de las piscinas
		if (i->getBloque().getBoundingBox().colisionanAABB(this->base.getBoundingBox())) {
			this->lento = true;
			break;
		}
		else {
			this->lento = false;
		}
	}
}

bool Tanque::enrojecerLuz()
{
	bool resetGenEnemigos = false;
	float aumento = .0015f;
	vec3 colorActual = this->locshader->getLightColorActual();
	//si está en una piscina
	if (this->lento) {
		colorActual = vec3(colorActual.x * (1 + aumento), colorActual.y * (1 - aumento), colorActual.z * (1 - aumento));
		//corregimos si se pasa
		if (colorActual.x >= 1.0f)
		{
			colorActual.x = 1.0f;
		}
		if (colorActual.y <= 0.0f)
		{
			colorActual.y = 0.0f;
		}
		if (colorActual.z <= 0.0f)
		{
			colorActual.z = 0.0f;
		}
		this->resetTemporizadorRegenVida();
		if (this->tempQuitVidaPiscina.suenaAlarma()) {
			this->resetTemporizadorQuitVidaPiscina();
			this->textVida.cambiarTextura();
			--this->vida;
			if (this->vida <= 0) {
				this->haPerdidoAgua(&colorActual);
				resetGenEnemigos = true;
			}
			else {
				cout << "como has estado mucho tiempo en el agua pierdes una vida" << endl;
				cout << "salud actual -> " << this->vida << endl;
			}
		}
	}
	//si está fuera de una piscina
	else
	{
		colorActual = vec3(colorActual.x * (1 + aumento), colorActual.y * (1 + aumento), colorActual.z * (1 + aumento));
		if (colorActual.x >= 1.0f)
		{
			colorActual.x = 1.0f;
		}
		if (colorActual.y >= 1.0f)
		{
			colorActual.y = 1.0f;
		}
		if (colorActual.z >= 1.0f)
		{
			colorActual.z = 1.0f;
		}
		this->resetTemporizadorQuitVidaPiscina();
	}
	this->locshader->cargarColorLuz(colorActual);
	return resetGenEnemigos;
}

void Tanque::regenerar()
{
	//pasaron 5 segundos sin recibir daño
	if (this->tempRegenVida.suenaAlarma()) {
		//reseteamos el temporizador de la vida
		this->resetTemporizadorRegenVida();
		//cambiamos la textura a una anterior
		if (this->vida < 3) {
			for (unsigned i = 0; i < 2; ++i) {
				this->textVida.cambiarTextura();
			}
			++this->vida;
			cout << "Como han pasar 5 segundos desde que se recibió un daño y fuera de un charco se aumenta la vida" << endl;
			cout << "Vida actual -> " << this->vida << endl;
		}
	}
}

void Tanque::haPerdidoAgua(vec3* color)
{
	cout << "Vaya! has perdido (has estado demasiado tiempo en el agua)." << endl;
	cout << "Presiona intro para reiniciar la partida" << endl;
	getchar();
	this->reset();
	*color = vec3(1.0f, 1.0f, 1.0f);
}

Tanque::Tanque(GLFWwindow* window, LocalizadorShader* locshader)
{
	this->escala = .6f;
	this->vida = 3;

	vector<string> texturas;

	texturas.push_back(string("green.jpg"));
	texturas.push_back(string("naranja.jpg"));
	texturas.push_back(string("red.jpg"));
	this->textVida = TexturasEvento(texturas);

	texturas.clear();
	texturas.push_back(string("tankText.jpg"));



	this->locshader = locshader;

	this->base = BloqueNormal(this->escala * vec3(.8f, .2f, .8f), vec3(), texturas, this->locshader);
	this->cuerpo = BloqueNormal(this->escala * vec3(.4f, .3f, .4f), vec3(), texturas, this->locshader);
	this->cannon = BloqueNormal(this->escala * vec3(.1f, .1f, .7f), vec3(), texturas, this->locshader);
	this->puntaCannon = BloqueNormal(this->escala * vec3(.15f, .15f, .15f), vec3(), texturas, this->locshader);

	movCannon = Movimiento1dLimites(uvec2(GLFW_KEY_N, GLFW_KEY_M), .4f, 0.0f, 360.0f);
	movTanque = Movimiento2d(uvec2(GLFW_KEY_D, GLFW_KEY_A), uvec2(GLFW_KEY_S, GLFW_KEY_W), .005f, vec2(0.0f, .5f));

	this->window = window;
	this->botonDisparar = Pulsador(GLFW_KEY_SPACE, .2, window);
	this->balasDisparadas = vector<Bala>();
	this->bloquearMov = false;
	this->lento = false;
	this->tempRegenVida = Temporizador(5);
	this->locshader->cargarColorLuz(vec3(1.0, 1.0f, 1.0f));
	this->contBalas = 0;
}

bool Tanque::actualizarTanque(Escenario* escenario)
{
	//matriz de transformación original
	mat4 transform = mat4();
	mat4 transformaux1 = mat4();
	mat4 transformaux2 = mat4();
	//lo elevamos para que esté por encima del suelo
	transform = translate(transform, this->escala * vec3(.0f, .1f, .0f));
	//le aplicamos la transformación del desplazamiento y se la asignamos a la base
	transform = moverTanque(transform);
	this->base.actualizar(transform);
	//lo subimos un poco más para el cuerpo del tanque
	transform = translate(transform, this->escala * vec3(.0f, .15f, .0f));
	this->cuerpo.actualizar(transform);
	//subimos un poco más para el cañón y rotamos
	transform = translate(transform, this->escala * vec3(.0f, .05f, .0f));
	transform = girarCannon(transform);
	transform = translate(transform, this->escala * vec3(.0f, .0f, -.5f));
	this->cannon.actualizar(transform);
	//movemos más hacia adelante para la punta del cañón
	transform = translate(transform, this->escala * vec3(.0f, .0f, -.3f));
	this->puntaCannon.actualizar(transform);

	//cargamos las transformaciones de la cámara del tanque
	this->sourceCam = translate(transform, this->escala * vec3(0.0f, 0.4f, 2.6f));
	this->targetCam = translate(transform, this->escala * vec3(0.0f, 0.25f, -.2f));


	//creamos balas si le toca
	this->crearBala(transform);
	this->actualizarBala();
	this->borrarBala();

	this->salirseDelSuelo(escenario);
	this->tocaPiscina(escenario);
	bool resetGenEnemigos = false;
	if (this->enrojecerLuz()) {
		resetGenEnemigos = true;
	}
	this->regenerar();
	return resetGenEnemigos;
}

void Tanque::dibujar()
{
	this->base.dibujar(this->textVida.getTexturasActuales().x, true);
	this->cuerpo.dibujar(this->textVida.getTexturasActuales().x, true);
	this->cannon.dibujar(this->textVida.getTexturasActuales().x, true);
	this->puntaCannon.dibujar(this->textVida.getTexturasActuales().x, true);

	for (auto i = this->balasDisparadas.begin(); i != this->balasDisparadas.end(); i++)
	{
		i->dibujar();
	}
}

vector<Bala>* Tanque::getBalas()
{
	return &this->balasDisparadas;
}

vec3 Tanque::getPos()
{
	return this->base.getPos();
}

BoundingBox Tanque::getBoundingBox()
{
	return this->base.getBoundingBox();
}

vec3 Tanque::getPosPuntaCannon()
{
	return this->puntaCannon.getPos();
}

void Tanque::cargarCamaraTanque(vec3* source, vec3* target)
{
	*source = vec3(this->sourceCam * vec4(.0f, .0f, .0f, 1.0f));
	*target = vec3(this->targetCam * vec4(.0f, .0f, .0f, 1.0f));
}

void Tanque::setBlocMov(bool si_o_no)
{
	this->bloquearMov = si_o_no;
}

TexturasEvento* Tanque::getTextsVida()
{
	return &this->textVida;
}

void Tanque::setVida(unsigned vida)
{
	this->vida = vida;
}



unsigned Tanque::getVida()
{
	return this->vida;
}

void Tanque::resetTemporizadorRegenVida()
{
	this->tempRegenVida.setAlarma(5);
}

GLFWwindow* Tanque::getWindow()
{
	return this->window;
}

void Tanque::reset()
{
	movCannon = Movimiento1dLimites(uvec2(GLFW_KEY_N, GLFW_KEY_M), .4f, 0.0f, 360.0f);
	movTanque = Movimiento2d(uvec2(GLFW_KEY_D, GLFW_KEY_A), uvec2(GLFW_KEY_S, GLFW_KEY_W), .005f, vec2(0.0f, .5f));
	this->balasDisparadas = vector<Bala>();
	this->bloquearMov = false;
	this->lento = false;
	this->tempRegenVida = Temporizador(5);
	this->locshader->cargarColorLuz(vec3(1.0, 1.0f, 1.0f));
	this->vida = 3;
	this->contBalas = 0;
}

void Tanque::resetTemporizadorQuitVidaPiscina()
{
	this->tempQuitVidaPiscina.setAlarma(3);
}


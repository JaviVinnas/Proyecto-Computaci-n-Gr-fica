#include "Bloque.h"



void BloqueSuelo::cargarVaoSuelo()
{
	unsigned int VBO, EBO, VAO;
	//caras con formato:
	/*
	--------
	|     /|
	|    / |
	|   /  |
	|  /   |
	| /    |
	|/     |
	--------
	*/
	//se especifican en el sentido contario a las agujas del reloj

	//tamaño de las baldosas
	float t = .25;

	/*Un cubo tiene 6 caras, cada cara 2 triangulos, cada triangulo 3 coordenadas
   y cada coordenada 3+3+2 valores (x,y,z + normX,normY,normZ + textU,textV) */
	float cubo_orig[6 * 2 * 3 * (3 + 3 + 2)]{
		//CARA DELANTERA ---> z positiva
		//>triangulo de arriba
		-t, -t, t, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, //esquina de abajo 1
		t, t, t, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,   //esquina de arriba 1
		-t, t, t, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,  //esquina de arriba 2
		//>triangulo de abajo
		-t, -t, t, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, //esquina de abajo 1
		t, -t, t, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f,  //esquina de abajo 2
		t, t, t, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,   //esquina de arriba 1

		//CARA TRASERA ---> z negativa
		//>triangulo de arriba
		t, -t, -t, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f, //esquina de abajo 1
		-t, t, -t, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f, //esquina de arriba 1
		t, t, -t, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f,  //esquina de arriba 2
		//>triangulo de abajo
		t, -t, -t, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f,  //esquina de abajo 1
		-t, -t, -t, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f, //esquina de abajo 2
		-t, t, -t, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f,  //esquina de arriba 1

		//CARA DERECHA ---> X positiva
		//>triangulo de arriba
		t, -t, t, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, //esquina de abajo 1
		t, t, -t, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, //esquina de arriba 1
		t, t, t, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,  //esquina de arriba 2
		//>triangulo de abajo
		t, -t, t, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,  //esquina de abajo 1
		t, -t, -t, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, //esquina de abajo 2
		t, t, -t, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f,  //esquina de arriba 1

		//CARA IZQUIERDA ---> X negativa
		//>triangulo de arriba
		-t, -t, -t, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f, //esquina de abajo 1
		-t, t, t, -1.0f, 0.0f, 0.0f, 1.0f, 1.0f,   //esquina de arriba 1
		-t, t, -t, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f,  //esquina de arriba 2
		//>triangulo de abajo
		-t, -t, -t, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f, //esquina de abajo 1
		-t, -t, t, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f,  //esquina de abajo 2
		-t, t, t, -1.0f, 0.0f, 0.0f, 1.0f, 1.0f,   //esquina de arriba 1

		//CARA ARRIBA ---> Y positiva
		//>triangulo de arriba
		-t, t, t, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,  //esquina de abajo 1
		t, t, -t, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,  //esquina de arriba 1
		-t, t, -t, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, //esquina de arriba 2
		//>triangulo de abajo
		-t, t, t, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, //esquina de abajo 1
		t, t, t, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,  //esquina de abajo 2
		t, t, -t, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, //esquina de arriba 1

		//CARA ABAJO ---> Y negativa
		//>triangulo de arriba
		-t, -t, -t, 0.0f, -1.0f, 0.0f, 0.0f, 0.0f, //esquina de abajo 1
		t, -t, t, 0.0f, -1.0f, 0.0f, 1.0f, 1.0f,   //esquina de arriba 1
		-t, -t, t, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f,  //esquina de arriba 2
		//>triangulo de abajo
		-t, -t, -t, 0.0f, -1.0f, 0.0f, 0.0f, 0.0f, //esquina de abajo 1
		t, -t, -t, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f,  //esquina de abajo 2
		t, -t, t, 0.0f, -1.0f, 0.0f, 1.0f, 1.0f   //esquina de arriba 1
	};

	//creamos el array definitivo
	static float vertices[10 * 2 * 10 * 2 * 6 * 2 * 3 * (3 + 3 + 2)]; //18 filas * 18 columnas
	float cubo_aux[6 * 2 * 3 * (3 + 3 + 2)];
	int x, z, count = 0;

	for (x = -10; x < 10; x++) //16 filas
	{
		for (z = -10; z < 10; z++) //16 columnas
		{
			//cargamos cubo aux con el cubo original
			memcpy(cubo_aux, cubo_orig, (6 * 2 * 3 * (3 + 3 + 2)) * sizeof(float));
			//lo desplazamos lo que toque
			for (int i = 0; i < 6 * 2 * 3 * (3 + 3 + 2); i++)
			{
				if (i % 8 == 0)
				{ //las x
					cubo_aux[i] += x * .5f;
					if (cubo_aux[i] > this->boundingBox.maxBound.x)
					{
						this->boundingBox.maxBound.x = cubo_aux[i];
					}
					if (cubo_aux[i] < this->boundingBox.minBound.x)
					{
						this->boundingBox.minBound.x = cubo_aux[i];
					}
				}
				if (i % 8 == 2)
				{ //las z
					cubo_aux[i] += z * .5f;
					if (cubo_aux[i] > this->boundingBox.maxBound.z)
					{
						this->boundingBox.maxBound.z = cubo_aux[i];
					}
					if (cubo_aux[i] < this->boundingBox.minBound.z)
					{
						this->boundingBox.minBound.z = cubo_aux[i];
					}
				}
				vertices[i + (count * 6 * 2 * 3 * (3 + 3 + 2))] = cubo_aux[i];
			}
			count += 1;
		}
	}

	//generamos los vaos
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);
	//enlazamos el VAOsuelo
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	//Posiciones
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	//Normales
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	//Texturas
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	this->vao = VAO;

	//deslinkamos
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
}

BloqueSuelo::BloqueSuelo()
{
	this->boundingBox = BoundingBox();
	this->vao = 0;
	this->gestTexturas = NULL;
	this->locShader = NULL;
}


BloqueSuelo::BloqueSuelo(string const& text, unsigned const& numText, string const& extension, LocalizadorShader *locshader)
{
	this->boundingBox = BoundingBox();
	this->vao = 0;
	this->cargarVaoSuelo();
	this->gestTexturas = new TexturasTemporizadas(text, numText, extension);
	this->locShader = locshader;
}

void BloqueSuelo::cambiarTextura()
{
	this->gestTexturas->cambiarTextura();
}

void BloqueSuelo::dibujar()
{
	this->locShader->cargarModel(scale(mat4(), vec3(1.0f, .05f, 1.0f)));
	uvec2 texts = this->gestTexturas->getTexturasActuales();
	if (texts.x == SINTEXTURA) {
		texts.x = 0;
		texts.y = 0;
	}
	if (texts.y == SINTEXTURA) {
		texts.y = texts.x;
	}
	this->locShader->cargarTexturas(texts);
	this->locShader->cargarObjetoyDibujar(this->vao);
}

BoundingBox BloqueSuelo::getBoundingBox()
{
	return this->boundingBox;
}

unsigned BloqueSuelo::getTextura()
{
	return this->gestTexturas->getTexturasActuales().x;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void BloqueNormal::cargarVaoCubo()
{
	unsigned int VBO, EBO;

	//caras con formato:
	/*
	--------
	|     /|
	|    / |
	|   /  |
	|  /   |
	| /    |
	|/     |
	--------
	*/
	//se especifican en el sentido contario a las agujas del reloj
	float t = .5f;
	float vertices[] = {
		//CARA DELANTERA ---> z positiva
		//>triangulo de arriba
		-t, -t, t, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, //esquina de abajo 1
		t, t, t, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,   //esquina de arriba 1
		-t, t, t, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,  //esquina de arriba 2
		//>triangulo de abajo
		-t, -t, t, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, //esquina de abajo 1
		t, -t, t, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f,  //esquina de abajo 2
		t, t, t, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,   //esquina de arriba 1

		//CARA TRASERA ---> z negativa
		//>triangulo de arriba
		t, -t, -t, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f, //esquina de abajo 1
		-t, t, -t, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f, //esquina de arriba 1
		t, t, -t, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f,  //esquina de arriba 2
		//>triangulo de abajo
		t, -t, -t, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f,  //esquina de abajo 1
		-t, -t, -t, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f, //esquina de abajo 2
		-t, t, -t, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f,  //esquina de arriba 1

		//CARA DERECHA ---> X positiva
		//>triangulo de arriba
		t, -t, t, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, //esquina de abajo 1
		t, t, -t, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, //esquina de arriba 1
		t, t, t, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,  //esquina de arriba 2
		//>triangulo de abajo
		t, -t, t, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,  //esquina de abajo 1
		t, -t, -t, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, //esquina de abajo 2
		t, t, -t, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f,  //esquina de arriba 1

		//CARA IZQUIERDA --> X negativa
		//>triangulo de arriba
		-t, -t, -t, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f, //esquina de abajo 1
		-t, t, t, -1.0f, 0.0f, 0.0f, 1.0f, 1.0f,   //esquina de arriba 1
		-t, t, -t, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f,  //esquina de arriba 2
		//>triangulo de abajo
		-t, -t, -t, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f, //esquina de abajo 1
		-t, -t, t, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f,  //esquina de abajo 2
		-t, t, t, -1.0f, 0.0f, 0.0f, 1.0f, 1.0f,   //esquina de arriba 1

		//CARA ARRIBA ---> Y positiva
		//>triangulo de arriba
		-t, t, t, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,  //esquina de abajo 1
		t, t, -t, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,  //esquina de arriba 1
		-t, t, -t, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, //esquina de arriba 2
		//>triangulo de abajo
		-t, t, t, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, //esquina de abajo 1
		t, t, t, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,  //esquina de abajo 2
		t, t, -t, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, //esquina de arriba 1

		//CARA ABAJO ---> Y negativa
		//>triangulo de arriba
		-t, -t, -t, 0.0f, -1.0f, 0.0f, 0.0f, 0.0f, //esquina de abajo 1
		t, -t, t, 0.0f, -1.0f, 0.0f, 1.0f, 1.0f,   //esquina de arriba 1
		-t, -t, t, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f,  //esquina de arriba 2
		//>triangulo de abajo
		-t, -t, -t, 0.0f, -1.0f, 0.0f, 0.0f, 0.0f, //esquina de abajo 1
		t, -t, -t, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f,  //esquina de abajo 2
		t, -t, t, 0.0f, -1.0f, 0.0f, 1.0f, 1.0f,   //esquina de arriba 1
	};

	glGenVertexArrays(1, &this->vao);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);
	// bind the Vertex Array Object first.
	glBindVertexArray(this->vao);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	//vertices
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	//normales
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	//Texturas
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
}



BloqueNormal::BloqueNormal() : BloqueSuelo()
{
	this->tam = vec3(1.0f, 1.0f, 1.0f);
	this->pos = vec3();
	this->matTransformacion = mat4();
	this->gestTexturas = NULL;
}

BloqueNormal::BloqueNormal(vec3 tam, vec3 pos, string const& text, unsigned const& numText, string const& extension, LocalizadorShader *locshader) : BloqueSuelo()
{
	this->tam = tam;
	this->pos = pos;
	this->matTransformacion = mat4();
	this->gestTexturas = new TexturasTemporizadas(text, numText, extension);
	this->cargarVaoCubo();
	this->locShader = locshader;
}

BloqueNormal::BloqueNormal(vec3 tam, vec3 pos, vector<string> const& texturas, LocalizadorShader * locshader) : BloqueSuelo()
{
	this->tam = tam;
	this->pos = pos;
	this->matTransformacion = scale(mat4(), this->tam);
	this->gestTexturas = new TexturasEvento(texturas);
	this->cargarVaoCubo();
	this->locShader = locshader;
}

void BloqueNormal::actualizar(mat4 const& transformacion)
{
	this->pos = vec3(transformacion * vec4(0.0f, 0.0f, 0.0f, 1.0f));
	this->matTransformacion = scale(transformacion, this->tam);
	this->boundingBox.actualizar(this->matTransformacion);
}

void BloqueNormal::dibujar()
{
	this->locShader->cargarModel(this->matTransformacion);
	uvec2 texts = this->gestTexturas->getTexturasActuales();
	if (texts.x == SINTEXTURA) {
		texts.x = 0;
		texts.y = 0;
	}
	if (texts.y == SINTEXTURA) {
		texts.y = texts.x;
	}
	this->locShader->cargarTexturas(texts);
	this->locShader->cargarObjetoyDibujar(this->vao);
}



void BloqueNormal::dibujar(unsigned text2, bool principal)
{
	this->locShader->cargarModel(this->matTransformacion);
	uvec2 texts = this->gestTexturas->getTexturasActuales();
	principal ? texts.y = text2 : texts.x = text2;
	this->locShader->cargarTexturas(texts);
	this->locShader->cargarObjetoyDibujar(this->vao);
}

vec3 BloqueNormal::getPos()
{
	return this->pos;
}

mat4 BloqueNormal::getTransfm()
{
	return this->matTransformacion;
}

void BloqueNormal::setTransfm(mat4 transfm)
{
	this->matTransformacion = transfm;
}








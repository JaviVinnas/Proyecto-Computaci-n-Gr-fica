#include "BoundingBox.h"

BoundingBox::BoundingBox()
{
	this->maxBound = vec3(.5f, .5f, .5f);
	this->minBound = vec3(-.5f, -.5f, -.5f);
};

vec3 BoundingBox::getMax()
{
	return maxBound;
};

vec3 BoundingBox::getMin()
{
	return minBound;
};

bool BoundingBox::colisionanAABB(BoundingBox const &box2)
{
	return (
		//choca en x
		(this->minBound.x <= box2.maxBound.x && this->maxBound.x >= box2.minBound.x) &&
		//choca en z
		(this->minBound.z <= box2.maxBound.z && this->maxBound.z >= box2.minBound.z));
}

void BoundingBox::actualizar(mat4 const &transform)
{
	//variables necesarias
	vec3 vecMin = vec3(1000.0f, 1000.0f, 1000.0f);
	vec3 vecMax = vec3(-1000.0f, -1000.0f, -1000.0f);
	vec3 vecIter;
	//los vertices max y min origenales son (.5,.5,.5) y (-.5,-.5,-.5)
	for (float x = -.5f; x <= .5f; x++)
	{
		for (float y = -.5f; y <= .5f; y++)
		{
			for (float z = -.5f; z <= .5f; z++)
			{
				vecIter = vec3(transform * vec4(x, y, z, 1.0f));
				//vemos si hay alguna coordenada apta para max
				if (vecIter.x >= vecMax.x) {
					vecMax.x = vecIter.x;
				}
				if (vecIter.y >= vecMax.y) {
					vecMax.y = vecIter.y;
				}
				if (vecIter.z >= vecMax.z) {
					vecMax.z = vecIter.z;
				}
				//vemos si hay alguna coordenada apta para min
				if (vecIter.x <= vecMin.x) {
					vecMin.x = vecIter.x;
				}	
				if (vecIter.y <= vecMin.y) {
					vecMin.y = vecIter.y;
				}	
				if (vecIter.z <= vecMin.z) {
					vecMin.z = vecIter.z;
				}
					
			}
		}
	}
	this->maxBound = vecMax;
	this->minBound = vecMin;
};

bool BoundingBox::contenidoEn(BoundingBox const &box2, char const deshabilitar[3], int *situacion)
{
	bool contenidoEnX, contenidoEnY, contenidoEnZ, aux1, aux2;
	*situacion = 0;

	//PARA LAS X'S
	if (deshabilitar[0] != 'x')
	{
		aux1 = false, aux2 = false;
		//si se sale por [-x]
		if (box2.minBound.x > this->minBound.x)
		{
			*situacion = 1;
			aux1 = true;
		}
		//si se sale por [+x]
		if (box2.maxBound.x < this->maxBound.x)
		{
			*situacion = 2;
			aux2 = true;
		}
		!aux1 && !aux2 ? contenidoEnX = true : contenidoEnX = false;
	}
	else
	{
		contenidoEnX = true;
	}

	//PARA LAS Y'S
	if (deshabilitar[1] != 'y')
	{
		aux1 = false, aux2 = false;
		//si se sale por [-y]
		if (box2.minBound.y > this->minBound.y)
		{
			*situacion = 3;
			aux1 = true;
		}
		//si se sale por [+y]
		if (box2.maxBound.y < this->maxBound.y)
		{
			*situacion = 4;
			aux2 = true;
		}
		!aux1 && !aux2 ? contenidoEnY = true : contenidoEnY = false;
	}
	else
	{
		contenidoEnY = true;
	}

	//PARA LAS Z'S
	if (deshabilitar[2] != 'z')
	{
		aux1 = false, aux2 = false;
		//si se sale por [-z]
		if (box2.minBound.z > this->minBound.z)
		{
			*situacion = 5;
			aux1 = true;
		}
		//si se sale por [+z]
		if (box2.maxBound.z < this->maxBound.z)
		{
			*situacion = 6;
			aux2 = true;
		}
		!aux1 && !aux2 ? contenidoEnZ = true : contenidoEnZ = false;
	}
	else
	{
		contenidoEnZ = true;
	}

	return (contenidoEnX && contenidoEnY && contenidoEnZ);
};

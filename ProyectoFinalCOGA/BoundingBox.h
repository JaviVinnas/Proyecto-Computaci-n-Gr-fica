#pragma once

#ifndef GLM_HPP
#include <glm/glm.hpp>
#endif // !GLM_HPP

using namespace glm;

class BoundingBox;

class BoundingBox
{
	friend class BloqueSuelo;
private:
	vec3 maxBound;
	vec3 minBound;

public:
	BoundingBox();
	vec3 getMax();
	vec3 getMin();
	bool colisionanAABB(BoundingBox const &box2);
	void actualizar(mat4 const &transform);
	bool contenidoEn(BoundingBox const &box2, char const deshabilitar[3], int *situacion);
};

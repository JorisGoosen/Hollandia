#include "Huis.h"


Huis::Huis() 
{
	generateHouse(glm::vec3(0.0f), glm::vec3(1.0f));
}

void Huis::generateHouse(glm::vec3 center, glm::vec3 dim)
{
	glm::vec3 rad = dim / 2.0f;
	_min = center - rad;
	_max = center + rad;

	_vertices.reserve(8 * 3);

	pushVertex(_min + (glm::vec3(0.0f, 0.0f, 0.0f) * dim));
	pushVertex(_min + (glm::vec3(1.0f, 0.0f, 0.0f) * dim));
	pushVertex(_min + (glm::vec3(1.0f, 0.0f, 1.0f) * dim));
	pushVertex(_min + (glm::vec3(0.0f, 0.0f, 1.0f) * dim));
	
	pushVertex(_min + (glm::vec3(0.0f, 1.0f, 0.0f) * dim));
	pushVertex(_min + (glm::vec3(1.0f, 1.0f, 0.0f) * dim));
	pushVertex(_min + (glm::vec3(1.0f, 1.0f, 1.0f) * dim));
	pushVertex(_min + (glm::vec3(0.0f, 1.0f, 1.0f) * dim));

	pushQuad(0, 4, 5, 1);
	pushQuad(1, 5, 6, 2);
	pushQuad(2, 6, 7, 3);
	pushQuad(3, 7, 4, 0);
	pushQuad(4, 7, 6, 5);
	pushQuad(0, 1, 2, 3);	
}

void Huis::pushVertex(glm::vec3 v)
{
	static float x0 = 0.0f, x1 = 2.0f;
	
	_vertices.push_back(v.x);
	_vertices.push_back(v.y);
	_vertices.push_back(v.z);
	_vertices.push_back(x0);
	_vertices.push_back(x1);

	x0 += 0.8f;
	x1 += 0.6666f;
}

void Huis::pushTriangle(uint16_t v0, uint16_t v1, uint16_t v2)
{
	_indices.push_back(v0);
	_indices.push_back(v1);
	_indices.push_back(v2);
}

void Huis::pushQuad(uint16_t v0, uint16_t v1, uint16_t v2, uint16_t v3)
{
	pushTriangle(v0, v1, v3);
	pushTriangle(v2, v3, v1);
}
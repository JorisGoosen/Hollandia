#include "glm/glm.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "glm/vec3.hpp"
#include "glm/vec4.hpp"
#include <vector>

class Huis
{
public:
	Huis();

	void generateHouse	(glm::vec3 center, glm::vec3 dim);
	void pushVertex		(glm::vec3 v);
	void pushTriangle	(uint16_t v0, uint16_t v1, uint16_t v2);
	void pushQuad		(uint16_t v0, uint16_t v1, uint16_t v2, uint16_t v3);

	float 		* vertices() 		{ return _vertices.data(); 	}
	uint16_t 	* indices() 		{ return _indices.data(); 	}

	size_t	vertexCount() 	{ return _vertices.size();	}
	size_t	indexCount() 	{ return _indices.size();	}

private:
	glm::vec3 				_min, 
							_max;
	std::vector<float>		_vertices;
	std::vector<uint16_t>	_indices;
};
#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "rtObject.h"
#include "scene.h"

class sphere : public rtObject
{
public:
	//constructor given  center, radius, and material
	sphere(glm::vec3 c, float r, int m, scene* s);

	//see descriptions in rtObject
	float testIntersection(glm::vec3 eye, glm::vec3 dir);
	glm::vec3 getNormal(glm::vec3 eye, glm::vec3 dir);
	glm::vec2 getTextureCoords(glm::vec3 eye, glm::vec3 dir);

private:
	glm::vec3 center;
	float radius;
   // keep track of both int. points
   float t_1 = 0.0;
   float t_2 = 0.0;
   glm::vec3 normal;
};

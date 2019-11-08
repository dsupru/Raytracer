#include "sphere.h"
#include <math.h>

//constructor given  center, radius, and material
sphere::sphere(glm::vec3 c, float r, int m, scene* s) : rtObject(s)
{
	center = c;
	radius = r;
	matIndex = m;
	myScene = s;
}

//intersection(s) of a line and a sphere
//return the minimum positive distance or 9999999 if none
float sphere::testIntersection(glm::vec3 eye, glm::vec3 dir)
{
   float resultingD;
   auto discriminant = pow(glm::dot(dir, (eye - this->center)), 2)
      - glm::dot(dir, dir)*(glm::dot(eye - this->center, eye - this->center)
            - pow(this->radius, 2));

   if (discriminant <= 0) {
      resultingD = 9999999;
   } else {
      auto sqrt_discriminant = sqrt(discriminant);
      auto denom = glm::dot(dir, dir);
      auto neg_b = glm::dot(-dir, (eye - this->center));
      auto t_1 = (neg_b + sqrt_discriminant) / denom;
      auto t_2 = (neg_b - sqrt_discriminant) / denom;
      // if both positive, return lowest
      if (t_1 >= 0 && t_2 >= 0) {
         resultingD = (t_1 < t_2 ? t_1 : t_2);
      // if one negative, return the positive one
      } else if (t_1 < 0) {
         if (t_2 >= 0) {
            resultingD = t_2;
         } else {
            // both negative
            resultingD = 9999999;
         }
      } else {
         // t_1 is positive, t_2 negative
         resultingD = t_1;
      }
   }
   return resultingD;
}

glm::vec3 sphere::getNormal(glm::vec3 eye, glm::vec3 dir)
{
	//once you can test for intersection,
	//simply add (distance * view direction) to the eye location to get surface location,
	//then subtract the center location of the sphere to get the normal out from the sphere
	glm::vec3 normal;

	//dont forget to normalize
	normal = glm::normalize(normal);
	
	return normal;
}

glm::vec2 sphere::getTextureCoords(glm::vec3 eye, glm::vec3 dir)
{
	//find the normal as in getNormal

	//use these to find spherical coordinates
	glm::vec3 x(1, 0, 0);
	glm::vec3 z(0, 0, 1);

	//phi is the angle down from z
	//theta is the angle from x curving toward y
	//hint: angle between two vectors is the acos() of the dot product

	//find phi using normal and z

	//find the x-y projection of the normal

	//find theta using the x-y projection and x

	//if x-y projection is in quadrant 3 or 4, then theta=2*PI-theta

	//return coordinates scaled to be between 0 and 1
	glm::vec2 coords;
	return coords;
}

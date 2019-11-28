#include "sphere.h"
#include <math.h>
#define MIN_PRECISION 5.0e-5
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
   auto eyeMcenter = eye - this->center;
   float resultingD;
   auto discriminant = pow(glm::dot(dir, eyeMcenter), 2)
      - glm::dot(dir, dir)*(glm::dot(eyeMcenter, eyeMcenter) - pow(this->radius, 2));

   if (discriminant < MIN_PRECISION) {
      resultingD = 9999999;
   } else {
      auto sqrt_discriminant = sqrt(discriminant);
      auto denom = glm::dot(dir, dir);
      auto neg_b = glm::dot(-dir, eyeMcenter);

      auto t_1 = (neg_b + sqrt_discriminant) / denom;
      auto t_2 = (neg_b - sqrt_discriminant) / denom;
      // if both positive, return lowest
      if (t_1 >= MIN_PRECISION && t_2 >= MIN_PRECISION) {
         resultingD = (t_1 < t_2 ? t_1 : t_2);
      // if one negative, return the positive one
      } else if (t_1 < MIN_PRECISION) {
         if (t_2 >= MIN_PRECISION) {
            resultingD = t_2;
         } else {
            // both negative
            resultingD = 9999999;
         }
      } else {
         // this->t_1 is positive, this->t_2 negative
         resultingD = t_1;
      }
   }
   return resultingD;
}

glm::vec3 sphere::getNormal(glm::vec3 eye, glm::vec3 dir) {
	//once you can test for intersection,
	//simply add (distance * view direction) to the eye location to get surface location,
	//then subtract the center location of the sphere to get the normal out from the sphere
   auto resultingD = testIntersection(eye, dir);
   auto surfaceLocation = eye + (resultingD*dir);
	auto local_normal = surfaceLocation - this->center;

	//dont forget to normalize
	local_normal = glm::normalize(local_normal);
	return local_normal;
}

glm::vec2 sphere::getTextureCoords(glm::vec3 eye, glm::vec3 dir) {
   // use the surface location to calculate texture offset
   auto gl_surfaceLocation = testIntersection(eye, dir)*dir + eye;
   auto surfaceLocation = gl_surfaceLocation - this->center;
   float s = acos(surfaceLocation.z/this->radius)/M_PI;
   float t_clammped = surfaceLocation.x/(this->radius*sin(M_PI*s));
   t_clammped = glm::clamp(t_clammped, -1.0f, 1.0f);
   float t = acos(t_clammped);
   if (surfaceLocation.y < 0) {
      t = 2*M_PI - t;
   }
   glm::vec2 coords(t/(2*M_PI), s);
	glm::clamp(coords, 0.0f, 1.0f);
	return coords;
}

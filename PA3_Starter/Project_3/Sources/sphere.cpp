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
   auto eyeMcenter = eye - this->center;
   float resultingD;
   auto discriminant = pow(glm::dot(dir, eyeMcenter), 2)
      - glm::dot(dir, dir)*(glm::dot(eyeMcenter, eyeMcenter) - pow(this->radius, 2));

   if (discriminant < 0) {
      resultingD = 9999999;
   } else {
      auto sqrt_discriminant = sqrt(discriminant);
      auto denom = glm::dot(dir, dir);
      auto neg_b = glm::dot(-dir, eyeMcenter);

      this->t_1 = (neg_b + sqrt_discriminant) / denom;
      this->t_2 = (neg_b - sqrt_discriminant) / denom;
      // if both positive, return lowest
      if (this->t_1 >= 0 && this->t_2 >= 0) {
         resultingD = (this->t_1 < this->t_2 ? this->t_1 : this->t_2);
      // if one negative, return the positive one
      } else if (this->t_1 < 0) {
         if (this->t_2 >= 0) {
            resultingD = this->t_2;
         } else {
            // both negative
            resultingD = 9999999;
         }
      } else {
         // this->t_1 is positive, this->t_2 negative
         resultingD = this->t_1;
      }
   }
   return resultingD;
}

glm::vec3 sphere::getNormal(glm::vec3 eye, glm::vec3 dir)
{
	//once you can test for intersection,
	//simply add (distance * view direction) to the eye location to get surface location,
	//then subtract the center location of the sphere to get the normal out from the sphere
   float resultingD;
   if (this->t_1 >= 0 && this->t_2 >= 0) {
      resultingD = (this->t_1 < this->t_2 ? this->t_1 : this->t_2);
   // if one negative, return the positive one
   } else if (this->t_1 < 0) {
      resultingD = this->t_2;
   } else {
      resultingD = this->t_1;
   }
   auto surfaceLocation = eye + (resultingD*dir);
	this->normal = surfaceLocation - this->center;

	//dont forget to normalize
	this->normal = glm::normalize(this->normal);
	
	return this->normal;
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
   float phy = acos(glm::dot(this->normal, z));

	//find the x-y projection of the normal

	//find theta using the x-y projection and x
   glm::vec3 xyProjection(0, 0, 0);
   xyProjection.x = this->normal.x;
   xyProjection.y = this->normal.y;
   float theta = acos(glm::dot(xyProjection, x));

	//if x-y projection is in quadrant 3 or 4, then theta=2*PI-theta
   if (xyProjection.y < 0) {
      theta = 2*M_PI - theta;
   }

	//return coordinates scaled to be between 0 and 1
	glm::vec2 coords(theta/(2*M_PI), phy/M_PI);
	glm::clamp(coords, 0.0f, 1.0f);
	return coords;
}

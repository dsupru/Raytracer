#include "triangle.h"
#include "rtObject.h"

//constructor given  center, radius, and material
triangle::triangle(glm::vec3 p0, glm::vec3 p1, glm::vec3 p2, 
      float tx0, float tx1, float tx2, float ty0, float ty1, float ty2, 
      int m, scene* s) 
   : rtObject(s)
{
	this->point0 = p0;
	this->point1 = p1;
	this->point2 = p2;

	this->texX0 = tx0;
	this->texX1 = tx1;
	this->texX2 = tx2;
	this->texY0 = ty0;
	this->texY1 = ty1;
	this->texY2 = ty2;
	rtObject::matIndex = m;
	rtObject::myScene = s;
}

float triangle::testIntersection(glm::vec3 eye, glm::vec3 dir) {
	//see the book/slides for a description of how to use Cramer's rule to solve
	//for the intersection(s) of a line and a plane, implement it here and
	//return the minimum distance (if barycentric coordinates indicate it hit
	//the triangle) otherwise 9999999
   
   const auto a = this->point0.x - this->point1.x;
   const auto b = this->point0.y - this->point1.y;
   const auto c = this->point0.z - this->point1.z;

   const auto j = this->point0.x - eye.x;
   const auto k = this->point0.y - eye.y;
   const auto l = this->point0.z - eye.z;

   const auto d = this->point0.x - this->point2.x;
   const auto e = this->point0.y - this->point2.y;
   const auto f = this->point0.z - this->point2.z;

   const auto g = dir.x;
   const auto h = dir.y;
   const auto i = dir.z;

   const auto ei = e*i;
   const auto hf = h*f;

   const auto gf = g*f;
   const auto di = d*i;

   const auto dh = d*h;
   const auto eg = e*g;

   const auto ak = a*k;
   const auto jb = j*b;

   const auto jc = j*c;
   const auto al = a*l;

   const auto bl = b*l;
   const auto kc = k*c;

   float M = a*(ei - hf) + b*(gf - di) + c*(dh - eg);
   float t = -(f*(ak - jb) + e*(jc - al) + d*(bl - kc))/ M;

   if (t < 0) {
      return 9999999;
   }

   this->gamma = (i*(ak - jb) + h*(jc - al) + g*(bl - kc)) / M;
   if (this->gamma < 0 || this->gamma > 1) {
      return 9999999;
   }


   this->betta = (j*(ei - hf) + k*(gf - di) + l*(dh - eg)) / M;
   if (this->betta < 0 || this->betta > 1 - this->gamma) {
      return 9999999;
   }

   // TODO return actual distance
	return t;
}

inline float triangle::getParameterVal(glm::mat3 parameter, const float A_determinant) {
   auto numerator_determinant = glm::determinant(parameter);
   auto result = numerator_determinant / A_determinant;
   return result;
}

glm::vec3 triangle::getNormal(glm::vec3 eye, glm::vec3 dir)
{
	//construct the barycentric coordinates for the plane
	glm::vec3 bary1 = this->point1 - this->point0;
	glm::vec3 bary2 = this->point2 - this->point0;

	//cross them to get the normal to the plane
	//note that the normal points in the direction given by right-hand rule
	//(this can be important for refraction to know whether you are entering or leaving a material)
	glm::vec3 normal = glm::normalize(glm::cross(bary1, bary2));
	return normal;
}

glm::vec2 triangle::getTextureCoords(glm::vec3 eye, glm::vec3 dir)
{
   float alpha = 1.0 - this->betta - this->gamma;
//   if (alpha < 0) {
//      alpha = 0.0;
//   }
   auto coord = alpha*glm::vec2(texX0, texY0)
      + this->betta*glm::vec2(texX1, texY1)
      + this->gamma*glm::vec2(texX2, texY2);
	return coord;
}

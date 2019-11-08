#include "triangle.h"

//constructor given  center, radius, and material
triangle::triangle(glm::vec3 p0, glm::vec3 p1, glm::vec3 p2, float tx0, float tx1, float tx2, float ty0, float ty1, float ty2, int m, scene* s) : rtObject(s)
{
	point0 = p0;
	point1 = p1;
	point2 = p2;

	texX0 = tx0;
	texX1 = tx1;
	texX2 = tx2;
	texY0 = ty0;
	texY1 = ty1;
	texY2 = ty2;
	matIndex = m;
	myScene = s;
}

float triangle::testIntersection(glm::vec3 eye, glm::vec3 dir) {
	//see the book/slides for a description of how to use Cramer's rule to solve
	//for the intersection(s) of a line and a plane, implement it here and
	//return the minimum distance (if barycentric coordinates indicate it hit
	//the triangle) otherwise 9999999
   
   const auto x_ab = point0.x - point2.x;
   const auto x_ac = point0.x - point1.x;
   const auto x_ae = point0.x - eye.x;

   const auto y_ab = point0.y - point2.y;
   const auto y_ac = point0.y - point1.y;
   const auto y_ae = point0.y - eye.y;

   const auto z_ab = point0.z - point2.z;
   const auto z_ac = point0.z - point1.z;
   const auto z_ae = point0.z - eye.z;

   glm::mat3 A_matrix(x_ab, y_ab, z_ab,
                     x_ac, y_ac, z_ac,
                     dir.x, dir.y, dir.z);
   auto A_determinant = glm::determinant(A_matrix);

   glm::mat3 t_numerator(x_ab, y_ab, z_ab,
                              x_ac, y_ac, z_ac,
                              x_ae, y_ae, z_ae);

   auto t = getParameterVal(t_numerator, A_determinant);
   if (t < 0 || t > 1) {
      return 9999999;
   }

   glm::mat3 gamma_numerator(x_ab, y_ab, z_ab,
                              x_ae, y_ae, z_ae,
                              dir.x, dir.y, dir.z);
   auto gamma = getParameterVal(gamma_numerator, A_determinant);
   if (gamma < 0 || gamma > 1) {
      return 9999999;
   }

   glm::mat3 beta_numerator(x_ae, y_ae, z_ae,
                              x_ac, y_ac, z_ac,
                              dir.x, dir.y, dir.z);
   auto betta = getParameterVal(beta_numerator, A_determinant);

   if (betta < 0 || betta > 1 - gamma) {
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
	glm::vec3 bary1 = point1 - point0;
	glm::vec3 bary2 = point2 - point0;

	//cross them to get the normal to the plane
	//note that the normal points in the direction given by right-hand rule
	//(this can be important for refraction to know whether you are entering or leaving a material)
	glm::vec3 normal = glm::normalize(glm::cross(bary1, bary2));
	return normal;
}

glm::vec2 triangle::getTextureCoords(glm::vec3 eye, glm::vec3 dir)
{
	//find alpha and beta (parametric distance along barycentric coordinates)
	//use these in combination with the known texture surface location of the vertices
	//to find the texture surface location of the point you are seeing

	glm::vec3 coords;
	return coords;
}

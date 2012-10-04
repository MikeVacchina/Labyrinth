#ifndef MVMATH
#define MVMATH

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp> //Makes passing matrices to shaders easier

double distanceLineSegPt(glm::vec2 segA, glm::vec2 segB, glm::vec2 pt);

#endif //MVMATH
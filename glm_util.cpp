
#include "glm_util.h"
#include <iostream>

void display_4x4(const glm::mat4 &m4) {
  // std::cout << tag << '\n';
  for (int row = 0; row < 4; ++row) {

    std::cout << "| ";
    for (int col = 0; col < 4; ++col) {
      // INFO: GLM stores matrices in column-major order
      // m4[0] : gives 1st column
      std::cout << m4[col][row] << '\t';
    }
    std::cout << '\n';
  }
  std::cout << '\n';
}
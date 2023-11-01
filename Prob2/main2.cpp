#include <iostream>
#include <sstream>
#include <vector>
#include "inf_int.h"

int main(void) {
  while (true) {
    std::string tmp;
    std::cout << "Input :";
    std::getline(std::cin, tmp);
    std::istringstream ss(tmp);
    if (tmp == "0") {
      break;
    } else {
      std::vector<std::string> tmp2;
      std::string buffer;
      //Parsing
      while (std::getline(ss, buffer, ' ')) {
        tmp2.push_back(buffer);
      }
      //Delete Parenthesis
      if ((tmp2[0][0] == '(' and tmp2[0][1] == '-' and tmp2[0][tmp2[0].length() - 1] == ')')) {
        tmp2[0] = tmp2[0].substr(1, tmp2[0].length() - 2);
      }
      if ((tmp2[2][0] == '(' and tmp2[2][1] == '-' and tmp2[2][tmp2[2].length() - 1] == ')')) {
        tmp2[2] = tmp2[2].substr(1, tmp2[2].length() - 2);
      }
      inf_int num1(tmp2[0].c_str());
      inf_int num2(tmp2[2].c_str());
      if (tmp2[1] == "+") {
        std::cout << "Output : " << num1 + num2 << std::endl;
      } else if (tmp2[1] == "*") {
        std::cout << "Output : " << num1 * num2 << std::endl;
      } else if (tmp2[1] == "-") {
        std::cout << "Output : " << num1 - num2 << std::endl;
      }
    }
  }
  return 0;
}

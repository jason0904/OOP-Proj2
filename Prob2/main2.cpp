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
      if (tmp2.size() != 3) {
        std::cout << "Error" << std::endl;
        continue;
      }
      //Delete Parenthesis
      if ((tmp2[0][0] == '(' and tmp2[0][1] == '-' and tmp2[0][tmp2[0].length() - 1] == ')')) {
        tmp2[0] = tmp2[0].substr(1, tmp2[0].length() - 2);
      }
      if ((tmp2[2][0] == '(' and tmp2[2][1] == '-' and tmp2[2][tmp2[2].length() - 1] == ')')) {
        tmp2[2] = tmp2[2].substr(1, tmp2[2].length() - 2);
      }
      //tmp2[0] digit check
      if (tmp2[0][0] == '-' and tmp2[0].length() == 1) {
        std::cout << "Error" << std::endl;
        continue;
      }
      if (tmp2[0][0] == '-') {
        for (int i = 1; i < tmp2[0].length(); i++) {
          if (tmp2[0][i] < '0' or tmp2[0][i] > '9') {
            std::cout << "Error" << std::endl;
            continue;
          }
        }
      } else {
        for (int i = 0; i < tmp2[0].length(); i++) {
          if (tmp2[0][i] < '0' or tmp2[0][i] > '9') {
            std::cout << "Error" << std::endl;
            continue;
          }
        }
      }
      //tmp2[2] digit check
      if (tmp2[2][0] == '-' and tmp2[2].length() == 1) {
        std::cout << "Error" << std::endl;
        continue;
      }
      if (tmp2[2][0] == '-') {
        for (int i = 1; i < tmp2[2].length(); i++) {
          if (tmp2[2][i] < '0' or tmp2[2][i] > '9') {
            std::cout << "Error" << std::endl;
            continue;
          }
        }
      } else {
        for (int i = 0; i < tmp2[2].length(); i++) {
          if (tmp2[2][i] < '0' or tmp2[2][i] > '9') {
            std::cout << "Error" << std::endl;
            continue;
          }
        }
      }
      inf_int num1(tmp2[0].c_str());
      inf_int num2(tmp2[2].c_str());
      if (tmp2[1] == "+") {
        std::cout << "Output : " << num1 + num2 << std::endl;
      } else if (tmp2[1] == "*") {
        std::cout << "Output : " << num1 * num2 << std::endl;
      } else if (tmp2[1] == "-") {
        std::cout << "Output : " << num1 - num2 << std::endl;
      } else std::cout << "Error" << std::endl;
    }
  }
  return 0;
}

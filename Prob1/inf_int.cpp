#include <cstring>
#include <algorithm>
#include <vector>
#include "inf_int.h"

inf_int::inf_int() {
  //default value = 0;
  this->digits = new char[1];
  this->digits[0] = '0';

  this->length = 1;
  this->thesign = true;

}

inf_int::inf_int(int n) {
  char buffer[100];

  if (n < 0) {
    this->thesign = false;
    n *= -1;
  } else {
    this->thesign = true;
  }
  int i = 0;
  while (n > 0) {
    buffer[i] = (n % 10) + '0';
    n /= 10;
    i++;
  }

  if (i == 0) {
    new(this) inf_int();
  } else {
    this->digits = new char[i];
    for (int j = 0; j < i; j++) {
      this->digits[j] = buffer[j];
    }
    this->length = i;
  }

}

inf_int::inf_int(const char *str) {
  if (str[0] == '-') {
    this->thesign = false;
  } else {
    this->thesign = true;
  }

  this->length = strlen(str);
  if (!thesign) this->length--;
  this->digits = new char[this->length];

  if (str[0] == '-') {
    for (int i = 1; i <= this->length; i++) {
      if (str[i] == '\0') break;
      else this->digits[i - 1] = str[this->length - i + 1];
    }
  } else {
    for (int i = 0; i < this->length; i++) {
      if (str[i] == '\0') break;
      else this->digits[i] = str[this->length - i - 1];
    }
  }
}

inf_int::inf_int(const inf_int &a) {
  this->length = a.length;
  this->digits = new char[a.length];
  this->thesign = a.thesign;
  for (int i = 0; i < a.length; i++) {
    this->digits[i] = a.digits[i];
  }
}

inf_int::~inf_int() = default;

inf_int &inf_int::operator=(const inf_int &a) {
  this->length = a.length;
  this->digits = new char[a.length];
  this->thesign = a.thesign;
  for (int i = 0; i < a.length; i++) {
    this->digits[i] = a.digits[i];
  }
  return *this;
}

bool operator==(const inf_int &a, const inf_int &b) {
  if (a.length != b.length) return false;
  if (a.thesign != b.thesign) return false;
  for (int i = 0; i < a.length; i++) {
    if (a.digits[i] != b.digits[i]) return false;
  }
  return true;
}

bool operator!=(const inf_int &a, const inf_int &b) {
  return !operator==(a, b);
}

bool operator>(const inf_int &a, const inf_int &b) {
  if (a.thesign && !b.thesign) return true;
  if (!a.thesign && b.thesign) return false;
  if (a.thesign && b.thesign) {
    if (a.length > b.length) return true;
    if (a.length < b.length) return false;
    for (int i = a.length - 1; i >= 0; i--) {
      if (a.digits[i] > b.digits[i]) return true;
      if (a.digits[i] < b.digits[i]) return false;
    }
    return false;
  } else {
    if (a.length > b.length) return false;
    if (a.length < b.length) return true;
    for (int i = a.length - 1; i >= 0; i--) {
      if (a.digits[i] > b.digits[i]) return false;
      if (a.digits[i] < b.digits[i]) return true;
    }
    return false;
  }
}

bool operator<(const inf_int &a, const inf_int &b) {
  return !operator>(a, b) && !operator==(a, b);
}

inf_int operator+(const inf_int &a, const inf_int &b) {
  inf_int result;
  std::string tmp;
  int carry = 0;
  if (a.thesign != b.thesign) {
    if (a.thesign) {
      result = b;
      result.thesign = true;
      return a - result;
    } else {
      result = a;
      result.thesign = true;
      return b - result;
    }
  }
  if (a.length > b.length) {
    //겹치는 부분
    for (int i = 0; i < b.length; i++) {
      int addition = (a.digits[i] - '0') + (b.digits[i] - '0') + carry;
      tmp += (addition % 10) + '0';
      carry = addition / 10;
    }
    //남는 부분
    for (int i = b.length; i < a.length; i++) {
      int addition = (a.digits[i] - '0') + carry;
      tmp += (addition % 10) + '0';
      carry = addition / 10;
    }
    result.digits = new char[tmp.length()];
    result.length = tmp.length();
    for (int i = 0; i < tmp.length(); i++) {
      result.digits[i] = tmp[i];
    }
    result.thesign = a.thesign;
    return result;
  } else {
    //겹치는 부분
    for (int i = 0; i < a.length; i++) {
      int addition = (a.digits[i] - '0') + (b.digits[i] - '0') + carry;
      tmp += (addition % 10) + '0';
      carry = addition / 10;
    }
    //남는 부분
    for (int i = a.length; i < b.length; i++) {
      int addition = (b.digits[i] - '0') + carry;
      tmp += (addition % 10) + '0';
      carry = addition / 10;
    }
    result.digits = new char[tmp.length()];
    result.length = tmp.length();
    for (int i = 0; i < tmp.length(); i++) {
      result.digits[i] = tmp[i];
    }
    result.thesign = a.thesign;
    return result;
  }
}

inf_int operator-(const inf_int &a, const inf_int &b) {
  inf_int result;
  std::string tmp;
  std::string tmp2;
  int carry = 0;
  if (strcmp(a.digits, b.digits) == 0 and a.thesign == b.thesign) {
    result = inf_int();
    return result;
  }
  if (a.thesign != b.thesign) {
    if (a.thesign) {
      result = b;
      result.thesign = true;
      return a + result;
    } else {
      result = a;
      result.thesign = true;
      return b + result;
    }
  }
  //a > b;
  if (compare(a, b)) {
    //겹치는 부분
    for (int i = 0; i < b.length; i++) {
      int subtraction = ((a.digits[i] - '0') - (b.digits[i] - '0') - carry);
      if (subtraction < 0) {
        subtraction = subtraction + 10;
        carry = 1;
      } else {
        carry = 0;
      }
      tmp += subtraction + '0';
    }
    //겹치지 않는 부분
    for (int i = b.length; i < a.length; i++) {
      int subtraction = ((a.digits[i] - '0') - carry);
      if (subtraction < 0) {
        subtraction = subtraction + 10;
        carry = 1;
      } else {
        carry = 0;
      }
      tmp += subtraction + '0';
    }
    int numOfZero = 0;
    for (int i = tmp.length() - 1; i >= 0; i--) {
      if (tmp[i] == '0') numOfZero++;
      else break;
    }
    tmp = tmp.substr(0, tmp.length() - numOfZero);
    result.digits = new char[tmp.length()];
    result.length = tmp.length();
    for (int i = 0; i < tmp.length(); i++) {
      result.digits[i] = tmp[i];
    }
    result.thesign = true;
    return result;
  } else {
    //겹치는 부분
    for (int i = 0; i < a.length; i++) {
      int subtraction = ((b.digits[i] - '0') - (a.digits[i] - '0') - carry);
      if (subtraction < 0) {
        subtraction = subtraction + 10;
        carry = 1;
      } else {
        carry = 0;
      }
      tmp += subtraction + '0';
    }
    //겹치지 않는 부분
    for (int i = a.length; i < b.length; i++) {
      int subtraction = ((b.digits[i] - '0') - carry);
      if (subtraction < 0) {
        subtraction = subtraction + 10;
        carry = 1;
      } else {
        carry = 0;
      }
      tmp += subtraction + '0';
    }
    int numOfZero = 0;
    for (int i = tmp.length() - 1; i >= 0; i--) {
      if (tmp[i] == '0') numOfZero++;
      else break;
    }
    tmp = tmp.substr(0, tmp.length() - numOfZero);
    result.digits = new char[tmp.length()];
    result.length = tmp.length();
    for (int i = 0; i < tmp.length(); i++) {
      result.digits[i] = tmp[i];
    }
    result.thesign = false;
    return result;
  }
}

inf_int operator*(const inf_int &a, const inf_int &b) {
  inf_int result;
  std::vector<char> tmp(a.length + b.length);
  std::string tmp2;
  if ((a.digits[0] == '0' and a.length == 1) or (b.digits[0] == '0' and b.length == 1)) {
    result = inf_int();
    return result;
  }
  if (a.thesign != b.thesign) {
    result.thesign = false;
  } else {
    result.thesign = true;
  }
  for (int i = 0; i < a.length; i++) {
    for (int j = 0; j < b.length; j++) {
      int production = ((a.digits[i] - '0') * (b.digits[j] - '0')) + tmp[i + j];
      tmp[i + j] = (char) (production % 10);
      tmp[i + j + 1] += production / 10;
    }
  }
  for (int i = 0; i < tmp.size(); i++) {
    tmp[i] += '0';
  }

  for (auto i : tmp) {
    tmp2 += i;
  }
  int numOfZero = 0;
  for (int i = tmp2.length() - 1; i >= 0; i--) {
    if (tmp[i] == '0') numOfZero++;
    else break;
  }
  tmp2 = tmp2.substr(0, tmp2.length() - numOfZero);
  result.length = tmp2.length();
  result.digits = new char[result.length];
  for (int i = 0; i < result.length; i++) {
    result.digits[i] = tmp[i];
  }
  return result;
}

std::ostream &operator<<(std::ostream &os, const inf_int &a) {
  if (!a.thesign) os << '-';
  for (int i = a.length - 1; i >= 0; i--) {
    os << a.digits[i];
  }
  return os;
}

//a > b check
bool compare(const inf_int &a, const inf_int &b) {
  if (a.length < b.length) return false;
  if (a.length > b.length) return true;
  for (int i = a.length - 1; i >= 0; i--) {
    if (a.digits[i] < b.digits[i]) return false;
  }
  return true;
}



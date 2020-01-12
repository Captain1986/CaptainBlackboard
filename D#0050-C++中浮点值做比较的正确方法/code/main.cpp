#include <iostream>

// Never try to check two floating point variables for equality
// The important rule to remember is that powers of two and integer multiples thereof can be perfectly represented. everything else is an approximation.

bool isEqual(const double first, const double second, const double epsilon = 1e-6)
{
   return abs(first - second) < epsilon;
}

int main(int argc, char *argv[])
{
  float  a = 1.0;
  double b = 1.0;

  // float和double比较
  // 会发生类型提升,float-->double
  if (a == b) {
      std::cout << "float 1.0 and doube 1.0 can be compared by == " << std::endl;
  } else {
      std::cerr << "float 1.0 and doube 1.0 CAN NOT be compared by == " << std::endl;
  }

  a = 3.14;
  b = 3.14;

  if (a == b) {
      std::cout << "float 3.14 and doube 3.14 can be compared by == " << std::endl;
  } else {
      std::cerr << "float 3.14 and doube 3.14 CAN NOT be compared by == " << std::endl;
  }

  if (a == (float)b) {
      std::cout << "float 3.14 and float 3.14 can be compared by == " << std::endl;
  } else {
      std::cerr << "float 3.14 and float 3.14 CAN NOT be compared by == " << std::endl;
  }

  // float和int比较
  // 会发生类型提升,int-->float
  a = 0.0;

  if (a == 0) {
      std::cout << "float 0.0 and literal 0 can be compared by == " << std::endl;
  } else {
      std::cerr << "float 0.0 and literal 0 CAN NOT be compared by == " << std::endl;
  }

  a = 1.0;

  if (a == 1) {
      std::cout << "float 1.0 and literal 1 can be compared by == " << std::endl;
  } else {
      std::cerr << "float 1.0 and literal 1 CAN NOT be compared by == " << std::endl;
  }

  // float和字面值常量比较
  a = 3.14;

  if (a == 3.14) {
      std::cout << "float 3.14 and literal 3.14 can be compared by == " << std::endl;
  } else {
      std::cerr << "float 3.14 and literal 3.14  CAN NOT be compared by == " << std::endl;
  }

  // 浮点数做比较的安全方法，引入些许误差
  double epsilon = 1e-6;
  if ( isEqual(a, 3.14, epsilon) ) {
      std::cout << "float 3.14 and literal 3.14 can be compared by isEqual(...) " << std::endl;
  } else {
      std::cerr << "float 3.14 and literal 3.14  CAN NOT be compared by isEqual(...) " << std::endl;
  }

  return 0;
}

#include "pe-vector.hpp"
#include <iostream>
using knk::Vector;

bool testConstructAndDestruct(const char ** pname)
{
  *pname = __func__;
  knk::Vector< int > v;
  return true;
}

bool testDefaultVectorIsEmpty(const char ** pname)
{
  *pname = __func__;
  Vector< int > v;
  return v.isEmpty();
}

bool testSizeOfEmptyVector(const char ** pname) {
  *pname = __func__;
  Vector< int > v;
  return !v.getSize();
}

bool testSizeOfNonEmptyVector(const char ** pname) {
  *pname = __func__;
  constexpr size_t size = 2ull;
  Vector< int > v(2ull, 5);
  return v.getSize() == 2ull;
}

bool testCapacityOfEmptyVector(const char ** pname) {
  *pname = __func__;
  Vector< int > v;
  return v.getCapacity() == 0ull;
}

bool testPushBackIncreasesSize(const char ** pname) {
  *pname = __func__;
  Vector< int > v;
  v.pushBack(10);
  return v.getSize() == 1ull && !v.isEmpty();
}

bool testPushBackCapacityGrowth(const char ** pname) {
  *pname = __func__;
  Vector< int > v;
  v.pushBack(1);
  size_t cap1 = v.getCapacity();
  v.pushBack(2);
  v.pushBack(3);
  size_t cap2 = v.getCapacity();
  return cap1 >= 1ull && cap2 >= 3ull && cap2 > cap1;
}

bool testPopBackDecreasesSize(const char ** pname) {
  *pname = __func__;
  Vector< int > v(2ull, 5);
  v.popBack();
  return v.getSize() == 1ull;
}

int main()
{
  using test_t = bool(*)(const char **);
  using case_t = std::pair< test_t, const char * >;
  case_t tests[] = {
    { testConstructAndDestruct, "Vector must be default constructable" },
    { testDefaultVectorIsEmpty, "Default constructed vector must be empty" },
    { testSizeOfEmptyVector, "Size of empty vector must be zero" },
    { testSizeOfNonEmptyVector, "Size of non-empty vector mast be greater than" },
    { testCapacityOfEmptyVector, "Capacity of empty vector must be zero" },
    { testPushBackIncreasesSize, "Pushing back must increase size" },
    { testPushBackCapacityGrowth, "Pushing back must grow capacity when needed" },
    { testPopBackDecreasesSize, "Popping back must decrease size" }
  };
  constexpr size_t count = sizeof(tests) / sizeof(case_t);
  size_t failed = 0;
  for (size_t i = 0; i < count; ++i) {
    const char * testName = nullptr;
    bool r = tests[i].first(&testName);
    if (!r) {
      ++failed;
      std::cout << "Failed: " << testName << "\n";
      std::cout << "\t" << tests[i].second << "\n";
    }
  }
  std::cout << "Summary: " << (count - failed) << " passed" << "\n";
  std::cout << "\t" << count << " total\n";
}

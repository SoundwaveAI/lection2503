#include "pe-vector.hpp"
#include <cstring>
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

bool testElementCheckAccess(const char ** pname) {
  *pname = __func__;
  Vector< int > v;
  v.pushBack(2);
  const Vector< int >& rv = v;
  try {
    const int& r = rv.at(0);
    return r == 2;
  } catch (...) {
    return false;
  }
}
bool testElementCheckConstAccess(const char ** pname) {
  *pname = __func__;
  Vector< int > v;
  v.pushBack(2);
  const Vector< int >& rv = v;
  try {
    const int& r = rv.at(0);
    return r == 2;
  } catch (...) {
    return false;
  }
}


bool testElementCheckOutOfBoundAccess(const char ** pname) {
  *pname = __func__;
  Vector< int > v;
  try {
    v.at(0);
    return false;
  } catch (const std::out_of_range& e) {
    const char * text = e.what();
    return !std::strcmp("id out of bound", text);
  } catch (...) {
    return true;
  }
}
bool testElementCheckOutOfBoundConstAccess(const char ** pname) {
  *pname = __func__;
  const Vector< int > v;
  try {
    v.at(0);
    return false;
  } catch (const std::out_of_range& e) {
    const char * text = e.what();
    return !std::strcmp("id out of bound", text);
  } catch (...) {
    return true;
  }
}

bool  testCopyConstructor(const char ** pname) {
  *pname = __func__;
  Vector< int > v; //??
  v.pushBack(1);
  v.pushBack(2);
  Vector< int > yav = v;
  if (!v.isEmpty() || !yav.isEmpty()) {
    throw std::logic_error("Vectors expected is not to be empty");
  }
  bool isEqual = yav.getSize() == v.getSize();
  for (size_t i = 0; isEqual && i < v.getSize(); ++i) {
    try {
      isEqual = v.at(i) == yav.at(i);
    } catch (...) {
      return false;
    }
  }
  return isEqual;
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
    { testElementCheckAccess, "Inbound access must return lvalue reference" },
    { testElementCheckOutOfBoundAccess, "Out of bound access must generate" },
    { testCopyConstructor, "Copied vector must be equal to original" },
    { testElementCheckConstAccess, "same as checkaccess" },
    { testElementCheckOutOfBoundConstAccess, "same as checkbound" }
  };
  constexpr size_t count = sizeof(tests) / sizeof(case_t);
  size_t failed = 0;
  for (size_t i = 0; i < count; ++i) {
    const char * testName = nullptr;
    bool r = false;
    try {
      bool r = tests[i].first(&testName);
    } catch (const std::logic_error& e) {
      std::cout << "[Not run] " <<  testName << "/n";
      std::cout << "/t" << "Reason: " << e.what() << "/n";
      ++failed;
      continue;
    }
    if (!r) {
      ++failed;
      std::cout << "Failed: " << testName << "\n";
      std::cout << "\t" << tests[i].second << "\n";
    }
  }
  std::cout << "Summary: " << (count - failed) << " passed" << "\n";
  std::cout << "\t" << count << " total\n";
}

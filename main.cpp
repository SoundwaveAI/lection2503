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
  Vector< int > v;
  v.pushBack(1);
  v.pushBack(2);
  Vector< int > yav = v;
  if (v.isEmpty() || yav.isEmpty()) {
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

bool testBracketAccess(const char ** pname) {
  *pname = __func__;
  Vector< int > v(2, 10);
  v[1] = 20;
  return v[0] == 10 && v[1] == 20;
}

bool testMoveConstructor(const char ** pname) {
  *pname = __func__;
  Vector< int > v1(5, 42);
  Vector< int > v2(std::move(v1));
  return v2.getSize() == 5 && v1.isEmpty();
}

bool testCopyAssignment(const char ** pname) {
  *pname = __func__;
  Vector< int > v1(2, 7);
  Vector< int > v2;
  v2 = v1;
  return v2.getSize() == 2 && v1.getSize() == 2 && v2[0] == 7;
}

bool testMoveAssignment(const char ** pname) {
  *pname = __func__;
  Vector< int > v1(3, 9);
  Vector< int > v2;
  v2 = std::move(v1);
  return v2.getSize() == 3 && v1.isEmpty();
}

bool testInsertByIndex(const char ** pname) {
  *pname = __func__;
  Vector< int > v;
  v.pushBack(1);
  v.pushBack(3);
  v.insert(1, 2);
  return v.getSize() == 3 && v[1] == 2;
}

bool testEraseVectorRange(const char ** pname) {
  *pname = __func__;
  knk::Vector< int > v;
  for (size_t i = 1; i <= 5; ++i) {
    v.pushBack(i);
  }
  v.erase(1ull, 3ull);
  return v.getSize() == 3 && v[1] == 4;
}

bool testInsertVectorRange(const char ** pname) {
  *pname = __func__;
  Vector< int > v1;
  v1.pushBack(1);
  v1.pushBack(4);
  Vector< int > v2;
  v2.pushBack(10);
  v2.pushBack(2);
  v2.pushBack(3);
  v1.insert(1, v2, 1, 3);
  return v1.getSize() == 4 && v1[1] == 2 && v1[2] == 3;
}

bool testEraseByIndexRange(const char ** pname) {
  *pname = __func__;
  Vector< int > v;
  for (size_t i = 0; i < 5; ++i) {
    v.pushBack(i);
  }
  v.erase(1, 4);
  return v.getSize() == 2 && v[1] == 4;
}

bool testPushFront(const char ** pname) {
  *pname = __func__;
  Vector< int > v;
  v.pushBack(1);
  v.pushFront(0);
  return v[0] == 0 && v.getSize() == 2;
}

bool testPushBackRepeat(const char ** pname) {
  *pname = __func__;
  Vector< int > v;
  v.pushBackRepeat(5, 3);
  return v.getSize() == 3 && v[2] == 5;
}

bool testSwap(const char ** pname) {
  *pname = __func__;
  Vector< int > v1(1, 1);
  Vector< int > v2(2, 2);
  v1.swap(v2);
  return v1.getSize() == 2 && v2.getSize() == 1;
}

bool testIterInsertSingle(const char ** pname) {
  *pname = __func__;
  Vector< int > v;
  v.pushBack(1);
  v.pushBack(3);
  v.insert(v.cbegin() + 1, 2);
  return v[1] == 2 && v.getSize() == 3;
}

bool testIterInsertCount(const char ** pname) {
  *pname = __func__;
  Vector< int > v;
  v.pushBack(1);
  v.insert(v.cbegin() + 1, 2, 99);
  return v.getSize() == 3 && v[1] == 99 && v[2] == 99;
}

bool testIterInsertRange(const char ** pname) {
  *pname = __func__;
  Vector< int > v1;
  v1.pushBack(1);
  v1.pushBack(4);
  Vector< int > v2;
  v2.pushBack(2);
  v2.pushBack(3);
  v1.insert(v1.cbegin() + 1, v2.cbegin(), v2.cend());
  return v1.getSize() == 4 && v1[1] == 2 && v1[2] == 3;
}

bool testIterEraseSingle(const char ** pname) {
  *pname = __func__;
  Vector< int > v;
  v.pushBack(1);
  v.pushBack(2);
  v.pushBack(3);
  v.erase(v.cbegin() + 1);
  return v.getSize() == 2 && v[1] == 3;
}

bool testIterEraseRange(const char ** pname) {
  *pname = __func__;
  Vector< int > v;
  for (size_t i = 0; i < 5; ++i) {
    v.pushBack(i);
  }
  v.erase(v.cbegin() + 1, v.cbegin() + 4);
  return v.getSize() == 2 && v[1] == 4;
}

bool testPopBack(const char ** pname) {
  *pname = __func__;
  knk::Vector< int > v;
  v.pushBack(1);
  v.pushBack(2);
  v.pushBack(3);
  v.popBack();
  return v.getSize() == 2 && v[1] == 2;
}

bool testIterEraseCount(const char ** pname) {
  *pname = __func__;
  knk::Vector< int > v;
  for (size_t i = 10; i <= 50; i+=10) {
    v.pushBack(i);
  }
  v.erase(v.cbegin() + 1, 2ull);
  return v.getSize() == 3 && v[1] == 40;
}

bool testAtConst(const char ** pname) {
  *pname = __func__;
  knk::Vector< int > temp;
  temp.pushBack(1);
  temp.pushBack(2);
  temp.pushBack(3);
  const knk::Vector< int > v = temp;
  try {
    return v.at(0) == 1 && v.at(2) == 3;
  } catch (...) {
    return false;
  }
}


int main()
{
  using test_t = bool(*)(const char **);
  using case_t = std::pair< test_t, const char * >;
  case_t tests[] = {
    { testConstructAndDestruct, "Vector must be default constructable" },
    { testDefaultVectorIsEmpty, "Default constructed vector must be empty" },
    { testSizeOfEmptyVector, "Size of empty vector must be zero" },
    { testSizeOfNonEmptyVector, "Size of non-empty vector mast be greater than zero" },
    { testCapacityOfEmptyVector, "Capacity of empty vector must be zero" },
    { testPushBackIncreasesSize, "Pushing back must increase size" },
    { testPushBackCapacityGrowth, "Pushing back must grow capacity when needed" },
    { testPopBackDecreasesSize, "Popping back must decrease size" },
    { testElementCheckAccess, "Inbound access must return lvalue reference to indexed value" },
    { testElementCheckOutOfBoundAccess, "Out of bound access must generate exception with specific text" },
    { testCopyConstructor, "Copied vector must be equal to original" },
    { testElementCheckConstAccess, "Same as inbound access but const" },
    { testElementCheckOutOfBoundConstAccess, "Same as out of bound but const" },
    { testBracketAccess, "Testing operator[] for direct element  read and write" },
    { testMoveConstructor, "Verifying move constructor transfers data ownership correctly" },
    { testCopyAssignment, "Checking copy assignment for deep copy and safety" },
    { testMoveAssignment, "Validating move assignment for efficient resource takeover" },
    { testInsertByIndex, "Testing element insertion at a specific index position" },
    { testEraseVectorRange, "Testing removal of multiple elements by index range." },
    { testInsertVectorRange, "Testing insertion of element range from another vector." },
    { testEraseByIndexRange, "Verifying erasure of multiple elements by index range." },
    { testPushFront, "Validating pushFront adds element to vector start" },
    { testPushBackRepeat, "Testing pushBackRepeat for adding multiple identical values" },
    { testSwap, "Checking swap method for efficient internal data exchange" },
    { testIterInsertSingle, "Testing iterator-based insertion of a single value." },
    { testIterInsertCount, "Testing iterator-based insertion of multiple identical values" },
    { testIterInsertRange, "Validating range insertion using a pair of iterators" },
    { testIterEraseSingle, "Testing single element removal using an iterator" },
    { testIterEraseRange, "Verifying range removal using start and end iterators." },
    { testPopBack, "Checking popBack decreases size and removes last element" },
    { testIterEraseCount, "Testing removal of specific element count via iterator" },
    { testAtConst, "Verifying at() method functionality for constant vectors" }
  };
  constexpr size_t count = sizeof(tests) / sizeof(case_t);
  size_t failed = 0;
  for (size_t i = 0; i < count; ++i) {
    const char * testName = nullptr;
    bool r = false;
    try {
      r = tests[i].first(&testName);
    } catch (const std::logic_error& e) {
      std::cout << "[Not run] " <<  testName << "\n";
      std::cout << "\t" << "Reason: " << e.what() << "\n";
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

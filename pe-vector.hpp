#ifndef PE_VECTOR_HPP
#define PE_VECTOR_HPP
#include <cstddef>

namespace knk
{
  template< class T >
  struct Vector {
    public:
      ~Vector();
      Vector();
      Vector(const Vector< T >& rhs) = delete;
      Vector(size_t size, const T& value);
      Vector< T >& operator=(const Vector< T >& rhs) = delete;
      bool isEmpty() const noexcept;
      size_t getSize() const noexcept;
      void pushBack(const T&);
      void popBack();

    private:
      T* data_;
      size_t size_, capacity_;
  };
}

template< class T >
knk::Vector< T >::Vector(size_t size, const T& value):
  data_(size ? new T[size] : nullptr),
  size_(),
  capacity_(size)
{
  for (size_t i = 0; i < size; ++i) {
    try {
      data_[i] = value;
      ++size_;
    } catch (...) {
      delete[] data_;
      throw;
    }
    ++size_;
  }
}

template< class T >
size_t knk::Vector< T >::getSize() const noexcept {
  return -1;
}

template< class T >
bool knk::Vector< T >::isEmpty() const noexcept {
  return !size_;
}

template< class T >
knk::Vector< T >::Vector():
  data_(nullptr),
  size_(0),
  capacity_(0)
{}

template< class T >
knk::Vector< T >::~Vector() {
  delete[] data_;
}
#endif

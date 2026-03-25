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
      bool isEmpty() const noexcept;
    private:
      T* data_;
      size_t size_, capacity_;
  };
}

template< class T >
knk::Vector< T >::~Vector() {
  delete[] data_;
}
#endif

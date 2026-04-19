#ifndef PE_VECTOR_HPP
#define PE_VECTOR_HPP
#include <cstddef>
#include <stdexcept>
#include <utility>

namespace knk
{
  template< class T > struct Viter;
  template< class T > struct Vciter;

  template< class T >
  struct Vector {
    public:
      ~Vector();
      Vector();
      Vector(const Vector< T >& rhs);
      Vector(Vector< T >&& rhs) noexcept;
      Vector(size_t size, const T& value);
      Vector< T >& operator=(const Vector< T >& rhs);
      Vector< T >& operator=(Vector< T >&& rhs) noexcept;
      void swap(Vector < T >& rhs) noexcept;

      void insert(size_t id, const T& t);
      void erase(size_t id);
      void insert(size_t id, const Vector< T >& rhs, size_t beg, size_t end_idx);
      void erase(size_t beg, size_t end_idx);

      bool isEmpty() const noexcept;
      size_t getSize() const noexcept;

      size_t getCapacity() const noexcept;
      void pushBack(const T&);
      void popBack();
      void pushFront(const T& v);

      T& operator[](size_t id) noexcept;
      const T& operator[](size_t id) const noexcept;
      T& at(size_t id);
      const T& at(size_t id) const;

      Viter< T > begin() noexcept;
      Viter< T > end() noexcept;
      Vciter< T > cbegin() const noexcept;
      Vciter< T > cend() const noexcept;

      void insert(Vciter< T > pos, const T& value);
      void insert(Vciter< T > pos, size_t count, const T& value);
      void insert(Vciter< T > pos, Vciter< T > first, Vciter< T > last);

      void erase(Vciter< T > pos);
      void erase(Vciter< T > first, Vciter< T > last);
      void erase(Vciter< T > pos, size_t count);

    private:
      T* data_;
      size_t size_, capacity_;
      explicit Vector(size_t size);
  };

  template< class T >
  struct Viter {
      T* p;
      Viter(T* ptr = nullptr);
      T& operator*() const;
      Viter< T >& operator++();
      Viter< T > operator++(int);
      Viter< T >& operator--();
      Viter< T > operator--(int);
      Viter< T >& operator+=(size_t n);
      Viter< T >& operator-=(size_t n);
      Viter< T > operator+(size_t n) const;
      Viter< T > operator-(size_t n) const;
      long long operator-(const Viter< T >& other) const;
      bool operator==(const Viter< T >& other) const;
      bool operator!=(const Viter< T >& other) const;
      bool operator<(const Viter< T >& other) const;
  };

  template< class T >
  struct Vciter {
      const T* p;
      Vciter(const T* ptr = nullptr);
      Vciter(const Viter< T >& other);
      const T& operator*() const;
      Vciter< T >& operator++();
      Vciter< T > operator++(int);
      Vciter< T >& operator--();
      Vciter< T > operator--(int);
      Vciter< T >& operator+=(size_t n);
      Vciter< T >& operator-=(size_t n);
      Vciter< T > operator+(size_t n) const;
      Vciter< T > operator-(size_t n) const;
      long long operator-(const Vciter< T >& other) const;
      bool operator==(const Vciter< T >& other) const;
      bool operator!=(const Vciter< T >& other) const;
      bool operator<(const Vciter< T >& other) const;
  };
}

template< class T >
knk::Vector< T >::Vector(Vector < T >&& rhs) noexcept:
  data_(rhs.data_),
  size_(rhs.size_),
  capacity_(rhs.capacity_)
{
  rhs.data_ = nullptr;
}

template< class T >
knk::Vector< T >& knk::Vector < T >::operator=(Vector< T >&& rhs) noexcept:
{
  Vector< T > cpy(std::move(rhs));
  swap(cpy);
  return *this;
}

template< class T >
void knk::Vector< T >::pushFront(const T& v)
{
  Vector< T > v(getSize() + 1);
  v[0] = t;
  for (size_t i = 0; i < v.getSize(); ++i) {
    v[i] = (*this)[i-1];
  }
  swap(v);
}

template< class T >
T& knk::Vector< T >::operator[](size_t id) noexcept {
  return const_cast< T& >((*static_cast< const Vector< T >* >(this))[id]);
  //return data_[id];
}

template< class T >
const T& knk::Vector< T >::operator[](size_t id) const noexcept {
  return data_[id];
}

template< class T>
T& knk::Vector< T >::at(size_t id) {
  const Vector< T >* cthis = this;
  const T& cr = cthis->at(id);
  T& r = const_cast< T& >(cr);
  return r;
}

template< class T >
const T& knk::Vector< T >::at(size_t id) const {
  if (id < getSize()) {
    return (*this)[id];
  }
  throw std::out_of_range("id out of bound");
}

template< class T >
knk::Vector< T >::Vector(const Vector< T >& rhs):
  Vector(rhs.getSize())
{
  for (size_t i = 0; i < rhs.getSize(); ++i) {
    data_[i] = rhs.data_[i];
  }
}

template< class T >
knk::Vector< T >& Vector< T >::operator=(const Vector< T >& rhs)
{
  if (this == std::addressof(rhs)) {
    return *this;
  }
  Vector< T > cpy(rhs);
  swap(cpy);
  return *this;
}

template< class T >
void knk::Vector< T >::swap(Vector< T >& rhs) noexcept
{
  std::swap(data_, cpy.data_);
  std::swap(size_, cpy.size_);
  std::swap(capacity_, cpy.capacity_);
}

template< class T >
knk::Vector< T >::Vector(size_t size):
  data_(size ? new T[size] : nullptr),
  size_(size),
  capacity_(size)
{}

template< class T >
knk::Vector< T >::Vector(size_t size, const T& value):
  Vector(size)
{
  for (size_t i = 0; i < size; ++i) {
    data_[i] = value;
  }
}

template< class T >
size_t knk::Vector< T >::getSize() const noexcept {
  return size_;
}

template< class T >
bool knk::Vector< T >::isEmpty() const noexcept {
  return !size_;
}

template< class T >
size_t knk::Vector< T >::getCapacity() const noexcept {
  return capacity_;
}

template< class T >
void knk::Vector< T >::pushBack(const T& value) {
  if (size_ == capacity_) {
    size_t new_capacity = (capacity_ == 0) ? 1 : capacity_ * 2;
    T* new_data = new T[new_capacity];
    try {
      for (size_t i = 0; i < size_; ++i) {
        new_data[i] = data_[i];
      }
      new_data[size_] = value;
    } catch (...) {
      delete[] new_data;
      throw;
    }

    delete[] data_;
    data_ = new_data;
    capacity_ = new_capacity;
    ++size_;
  } else {
    data_[size_] = value;
    ++size_;
  }
}

template< class T >
void knk::Vector< T >::popBack() {
  if (size_ > 0) {
    --size_;
  }
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

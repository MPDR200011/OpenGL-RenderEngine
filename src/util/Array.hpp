#pragma once

template <typename T>
class Array {
  const size_t m_size;
  const T* ptr;

  public:
  Array(size_t);
  ~Array();
  size_t size();

  T& operator[](size_t);
};

template<typename T>
Array<T>::Array(size_t size) {
  this->m_size = size;
  this->ptr = new T[size];
}

template<typename T>
Array<T>::~Array() {
  delete[] ptr;
}

template<typename T>
size_t Array<T>::size() {
  return m_size;
}

template<typename T>
T& Array<T>::operator[](size_t i) {
  return *(ptr+i);
}

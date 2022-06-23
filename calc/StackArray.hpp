#ifndef STACK_ARRAY_HPP
#define STACK_ARRAY_HPP

#include <iostream>
#include "Exceptions.hpp"
#include "Stack.hpp"

template <class T>
class StackArray : public Stack<T>
{
public:
  StackArray(size_t size = 100);
  StackArray(const StackArray<T>& src) = delete;
  StackArray(StackArray<T>&& src);
  StackArray& operator=(const StackArray<T>& src) = delete;
  StackArray& operator=(StackArray<T>&& src);
  T at(int index);
  virtual ~StackArray();
  void push(const T& e);
  T pop();
  bool isEmpty();
  size_t getCapacity();
  T getTop()
  {
    return array_[top_];
  }
private:
  T* array_;
  size_t top_;
  size_t size_;
  void swap(StackArray<T>& src);
};
#endif

template<class T>
inline size_t StackArray<T>::getCapacity()
{
  return top_;
}


template<class T>
inline T StackArray<T>::at(int index)
{
  return array_[index];
}

template<class T>
StackArray<T>::StackArray(size_t size) :
  size_(size),
  top_(0)
{
  if (size <= 0)
  {
    throw WrongStackSize();
  }
  array_ = new T[size + 1];
}

template<class T>
inline StackArray<T>::~StackArray()
{
  delete[] array_;
}

template<class T>
inline void StackArray<T>::push(const T& e)
{
  if (top_ == size_)
  {
    throw StackOverflow();
  }
  array_[++top_] = e;
}

template<class T>
inline T StackArray<T>::pop()
{
  if (top_ == 0)
  {
    throw StackUnderflow();
  }
  return array_[top_--];
}

template<class T>
inline bool StackArray<T>::isEmpty()
{
  return top_ == 0;
}

template<class T>
void StackArray<T>::swap(StackArray<T>& src)
{
  std::swap(array_, src.array_);
  std::swap(top_, src.top_);
  std::swap(size_, src.size_);

}

template<class T>
StackArray<T>::StackArray(StackArray<T>&& src)
{
  swap(src);

  delete[] src.array_;

  src.array_ = nullptr;
  src.top_ = 0;
  src.size_ = 0;
}

template<class T>
StackArray<T>& StackArray<T>::operator=(StackArray<T>&& src)
{
  swap(src);
  delete[] src.array_;
  src.array_ = nullptr;
  src.top_ = 0;
  src.size_ = 0;
  return *this;
}

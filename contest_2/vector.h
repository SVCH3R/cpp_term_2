#pragma once
#include <iostream>
#include <cstddef>
#include <stdexcept>

template <typename T>
class Vector {
 private:
  T* data_ = nullptr;
  size_t size_ = 0;
  size_t capacity_ = 0;

 public:
  using ValueType = T;
  using Pointer = T*;
  using ConstPointer = const T*;
  using Reference = T&;
  using ConstReference = const T&;
  using SizeType = size_t;
  using Iterator = T*;
  using ConstIterator = const T*;
  using ReverseIterator = std::reverse_iterator<Iterator>;
  using ConstReverseIterator = std::reverse_iterator<ConstIterator>;
  Vector() noexcept;
  ~Vector();
  explicit Vector(const size_t&);
  Vector(const size_t&, const T&);
  template <class Iterator, class = std::enable_if_t<std::is_base_of_v<
                                std::forward_iterator_tag, typename std::iterator_traits<Iterator>::iterator_category>>>
  Vector(Iterator first, Iterator last) {
    size_ = last - first;
    capacity_ = last - first;
    data_ = nullptr;
    if (last != first) {
      data_ = new T[capacity_];
      try {
        size_t i = 0;
        while (first != last) {
          data_[i] = *first;
          ++i;
          ++first;
        }
      } catch (...) {
        size_ = 0;
        capacity_ = 0;
        delete[] data_;
        throw;
      }
    }
  }
  Vector(const Vector&);
  Vector(Vector&&) noexcept;
  Vector(std::initializer_list<T>);
  Vector& operator=(const Vector&);
  Vector& operator=(Vector&&) noexcept;
  size_t Size() const noexcept;
  size_t Capacity() const noexcept;
  bool Empty() const noexcept;
  Reference At(const size_t&);
  ConstReference At(const size_t&) const;
  Reference operator[](const size_t&) noexcept;
  ConstReference operator[](const size_t&) const noexcept;
  Reference Front();
  ConstReference Front() const;
  Reference Back();
  ConstReference Back() const;
  Pointer Data();
  ConstPointer Data() const;
  void Swap(Vector&);
  void Resize(const size_t&);
  void Resize(const size_t&, const T&);
  void Reserve(const size_t&);
  void ShrinkToFit();
  void Clear();
  void PushBack(const T&);
  void PushBack(T&&);
  void PopBack() noexcept;
  ConstIterator cbegin() const {  // NOLINT
    return data_;
  }
  ConstIterator begin() const {  // NOLINT
    return data_;
  }
  Iterator begin() {  // NOLINT
    return data_;
  }
  ConstIterator cend() const {  // NOLINT
    return data_ + size_;
  }
  ConstIterator end() const {  // NOLINT
    return data_ + size_;
  }
  Iterator end() {  // NOLINT
    return data_ + size_;
  }
  ConstReverseIterator crbegin() const {  // NOLINT
    return std::reverse_iterator<const T*>(data_ + size_);
  }
  ConstReverseIterator rbegin() const {  // NOLINT
    return std::reverse_iterator<const T*>(data_);
  }
  ReverseIterator rbegin() {  // NOLINT
    return std::reverse_iterator<T*>(data_ + size_);
  }
  ConstReverseIterator crend() const {  // NOLINT
    return std::reverse_iterator<const T*>(data_);
  }
  ConstReverseIterator rend() const {  // NOLINT
    return std::reverse_iterator<const T*>(data_);
  }
  ReverseIterator rend() {  // NOLINT
    return std::reverse_iterator<T*>(data_);
  }
};

template <typename T>
Vector<T>::Vector() noexcept = default;

template <typename T>
Vector<T>::~Vector() {
  delete[] data_;
  size_ = 0;
  capacity_ = 0;
}

template <typename T>
Vector<T>::Vector(const size_t& size) {
  size_ = size;
  capacity_ = size;
  try {
    if (size == 0) {
      data_ = nullptr;
    } else {
      data_ = new T[size];
    }
  } catch (...) {
    size_ = 0;
    capacity_ = 0;
    delete[] data_;
    throw;
  }
}

template <typename T>
Vector<T>::Vector(const size_t& size, const T& value) {
  size_ = size;
  capacity_ = size;
  try {
    if (size == 0) {
      data_ = nullptr;
    } else {
      data_ = new T[size];
      for (size_t i = 0; i < size; ++i) {
        data_[i] = std::move(value);
      }
    }
  } catch (...) {
    size_ = 0;
    capacity_ = 0;
    delete[] data_;
    throw;
  }
}

template <typename T>
Vector<T>::Vector(const Vector<T>& other) {
  size_ = other.size_;
  capacity_ = other.capacity_;
  data_ = new T[capacity_];
  if (size_ == 0) {
    delete[] data_;
    data_ = nullptr;
    capacity_ = 0;
    return;
  }
  try {
    for (size_t i = 0; i < size_; ++i) {
      data_[i] = other.data_[i];
    }
  } catch (...) {
    size_ = 0;
    capacity_ = 0;
    delete[] data_;
    data_ = nullptr;
    throw;
  }
}

template <typename T>
Vector<T>::Vector(Vector&& other) noexcept {
  capacity_ = std::__exchange(other.capacity_, 0);
  size_ = std::__exchange(other.size_, 0);
  data_ = std::__exchange(other.data_, nullptr);
}

template <typename T>
Vector<T>::Vector(std::initializer_list<T> in_list) : Vector(in_list.begin(), in_list.end()) {
}

template <typename T>
Vector<T>& Vector<T>::operator=(const Vector& other) {
  if (this != &other) {
    Vector temp(other);
    Swap(temp);
  }
  return *this;
}

template <typename T>
Vector<T>& Vector<T>::operator=(Vector&& other) noexcept {
  if (this != &other) {
    Vector(std::move(other)).Swap(*this);
  }
  return *this;
}

template <typename T>
void Vector<T>::Swap(Vector& other) {
  std::swap(data_, other.data_);
  std::swap(capacity_, other.capacity_);
  std::swap(size_, other.size_);
}

template <typename T>
size_t Vector<T>::Size() const noexcept {
  return size_;
}

template <typename T>
bool Vector<T>::Empty() const noexcept {
  return size_ == 0;
}

template <typename T>
void Vector<T>::Clear() {
  size_ = 0;
}

template <typename T>
T& Vector<T>::At(const size_t& pos) {
  if (pos < size_) {
    return data_[pos];
  }
  throw std::out_of_range("Out of range");
}

template <typename T>
const T& Vector<T>::At(const size_t& pos) const {
  if (pos < size_) {
    return data_[pos];
  }
  throw std::out_of_range("Out of range");
}

template <typename T>
T& Vector<T>::operator[](const size_t& pos) noexcept {
  return data_[pos];
}

template <typename T>
const T& Vector<T>::operator[](const size_t& pos) const noexcept {
  return data_[pos];
}

template <typename T>
T& Vector<T>::Front() {
  return data_[0];
}

template <typename T>
const T& Vector<T>::Front() const {
  return data_[0];
}

template <typename T>
T& Vector<T>::Back() {
  return data_[size_ - 1];
}

template <typename T>
const T& Vector<T>::Back() const {
  return data_[size_ - 1];
}

template <typename T>
T* Vector<T>::Data() {
  return data_;
}

template <typename T>
const T* Vector<T>::Data() const {
  return data_;
}

template <typename T>
size_t Vector<T>::Capacity() const noexcept {
  return capacity_;
}

template <typename T>
void Vector<T>::ShrinkToFit() {
  if (size_ == 0) {
    delete[] data_;
    capacity_ = 0;
    data_ = nullptr;
  } else {
    if (size_ < capacity_) {
      auto new_data = new T[size_];
      for (size_t i = 0; i < size_; ++i) {
        new_data[i] = std::move(data_[i]);
      }
      delete[] data_;
      data_ = std::move(new_data);
      capacity_ = size_;
    }
  }
}

template <typename T>
void Vector<T>::Reserve(const size_t& new_capacity) {
  if (new_capacity <= capacity_) {
    return;
  }
  auto new_data = new T[new_capacity];
  for (size_t i = 0; i < size_; ++i) {
    new_data[i] = std::move(data_[i]);
  }
  delete[] data_;
  data_ = std::move(new_data);
  capacity_ = new_capacity;
}

template <typename T>
void Vector<T>::Resize(const size_t& new_size) {
  if (new_size <= capacity_) {
    size_ = new_size;
  } else {
    auto temp = new T[new_size];
    capacity_ = new_size;
    for (size_t i = 0; i < size_; ++i) {
      temp[i] = std::move(data_[i]);
    }
    size_ = new_size;
    delete[] data_;
    data_ = temp;
  }
}

template <typename T>
void Vector<T>::Resize(const size_t& new_size, const T& value) {
  if (new_size > capacity_) {
    auto temp = new T[new_size];
    try {
      for (size_t i = 0; i < new_size; ++i) {
        if (i < size_) {
          temp[i] = std::move(data_[i]);
        } else {
          temp[i] = value;
        }
      }
    } catch (...) {
      delete[] temp;
      throw;
    }
    delete[] data_;
    size_ = new_size;
    capacity_ = new_size;
    data_ = temp;
  } else {
    try {
      for (size_t i = 0; i < new_size; ++i) {
        if (i >= size_) {
          data_[i] = value;
        }
      }
    } catch (...) {
      for (size_t i = 0; i < new_size; ++i) {
        if (i >= size_) {
          data_[i].~T();
        }
      }
      throw;
    }
    size_ = new_size;
  }
}

template <typename T>
void Vector<T>::PushBack(const T& value) {
  if (size_ < capacity_) {
    try {
      data_[size_] = value;
    } catch (...) {
      (data_ + size_)->~T();
      throw;
    }
    ++size_;
    return;
  }
  if (capacity_ == 0) {
    auto temp = new T[1];
    try {
      temp[0] = value;
    } catch (...) {
      delete[] temp;
      throw;
    }
    ++size_;
    ++capacity_;
    delete[] data_;
    data_ = temp;
    return;
  }
  auto temp = new T[capacity_ * 2];
  try {
    for (size_t i = 0; i < size_; ++i) {
      temp[i] = data_[i];
    }
    temp[size_] = value;
  } catch (...) {
    delete[] temp;
    throw;
  }
  capacity_ *= 2;
  ++size_;
  delete[] data_;
  data_ = temp;
}

template <typename T>
void Vector<T>::PushBack(T&& value) {
  if (size_ == capacity_) {
    if (size_ == 0) {
      size_ = 1;
      capacity_ = 1;
      auto temp = new T[1];
      temp[0] = std::move(value);
      delete[] data_;
      data_ = temp;
    } else {
      capacity_ *= 2;
      auto temp = new T[capacity_];
      for (size_t i = 0; i < size_; ++i) {
        temp[i] = std::move(data_[i]);
      }
      temp[size_] = std::move(value);
      delete[] data_;
      data_ = temp;
      ++size_;
    }
    return;
  }
  data_[size_] = std::move(value);
  ++size_;
}

template <typename T>
void Vector<T>::PopBack() noexcept {
  if (size_ > 0) {
    try {
      --size_;
      data_[size_].~T();
    } catch (...) {
      ++size_;
    }
  }
}

template <typename T>
bool operator==(const Vector<T>& left, const Vector<T>& right) {
  if (left.Size() != right.Size()) {
    return false;
  }
  for (size_t i = 0; i < left.Size(); ++i) {
    if (left[i] != right[i]) {
      return false;
    }
  }
  return true;
}

template <typename T>
bool operator<(const Vector<T>& left, const Vector<T>& right) {
  if (left.Data() == nullptr || right.Data() == nullptr) {
    return left.Size() < right.Size();
  }
  auto minsize = std::min(left.Size(), right.Size());
  size_t i = 0;
  while (i < minsize) {
    if (left.Data()[i] == right.Data()[i]) {
      ++i;
    } else {
      return (left.Data()[i] < right.Data()[i]);
    }
  }
  return left.Size() < right.Size();
}

template <typename T>
bool operator!=(const Vector<T>& left, const Vector<T>& right) {
  return not(left == right);
}

template <typename T>
bool operator>=(const Vector<T>& left, const Vector<T>& right) {
  return (left == right) || (left > right);
}

template <typename T>
bool operator>(const Vector<T>& left, const Vector<T>& right) {
  return not(left <= right);
}

template <typename T>
bool operator<=(const Vector<T>& left, const Vector<T>& right) {
  return left < right || left == right;
}
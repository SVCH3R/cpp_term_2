#include <iostream>
#include <string>
#include "cppstring.h"
size_t Strlen(const char* string) {
  int count = 0;
  while (string[count] != '\0') {
    ++count;
  }
  return count;
}

size_t String::Size() const {
  return size_;
}

size_t String::Length() const {
  return size_;
}

size_t String::Capacity() const {
  return capacity_;
}

String::~String() {
  capacity_ = 0;
  size_ = 0;
  delete[] body_;
}

String::String() : body_(nullptr), size_(0), capacity_(0) {
}

String::String(size_t size, const char symbol) {
  size_ = size;
  capacity_ = size;
  if (size_ == 0) {
    body_ = nullptr;
  } else {
    body_ = new char[capacity_ + 1];
    for (size_t i = 0; i < size_; ++i) {
      body_[i] = symbol;
    }
    body_[size_] = '\0';
  }
}

String::String(const char* other) {
  size_ = Strlen(other);
  capacity_ = Strlen(other);
  if (size_ == 0) {
    body_ = nullptr;
  } else {
    body_ = new char[capacity_ + 1];
    for (size_t i = 0; i < size_; ++i) {
      body_[i] = other[i];
    }
    body_[size_] = '\0';
  }
}

String::String(const char* other, size_t size) {
  size_ = size;
  capacity_ = size;
  if (size_ == 0) {
    body_ = nullptr;
  } else {
    body_ = new char[size + 1];
    for (size_t i = 0; i < capacity_; ++i) {
      body_[i] = other[i];
    }
    body_[size_] = '\0';
  }
}

String::String(char* other, size_t size) {
  size_ = size;
  capacity_ = size;
  if (size_ == 0) {
    body_ = nullptr;
  } else {
    body_ = new char[size + 1];
    for (size_t i = 0; i < capacity_; ++i) {
      body_[i] = other[i];
    }
    body_[size_] = '\0';
  }
}

String::String(const String& other) {
  size_ = other.Size();
  capacity_ = other.Capacity();
  if (size_ == 0) {
    body_ = nullptr;
  } else {
    body_ = new char[capacity_ + 1];
    for (size_t i = 0; i < size_; ++i) {
      body_[i] = other[i];
    }
    body_[size_] = '\0';
  }
}

const char& String::operator[](size_t idx) const {
  return body_[idx];
}

char& String::operator[](size_t idx) {
  return body_[idx];
}

const char& String::At(size_t idx) const {
  if (idx < size_) {
    return body_[idx];
  }
  throw StringOutOfRange{};
}

char& String::At(size_t idx) {
  if (idx < size_) {
    return body_[idx];
  }
  throw StringOutOfRange{};
}

void String::Clear() {
  size_ = 0;
}

void String::Resize(size_t new_size, char symbol) {
  if (new_size <= size_) {
    size_ = new_size;
    body_[size_] = '\0';
  } else {
    for (size_t i = size_; i < new_size; ++i) {
      PushBack(symbol);
    }
  }
}

const char& String::Back() const {
  return body_[size_ - 1];
}

char& String::Back() {
  return body_[size_ - 1];
}

const char& String::Front() const {
  return body_[0];
}

char& String::Front() {
  return body_[0];
}

void String::Swap(String& other) {
  String helper = std::move(other);
  other = std::move(*this);
  *this = std::move(helper);
}

const char* String::CStr() const {
  return body_;
}

char* String::CStr() {
  return body_;
}

const char* String::Data() const {
  return body_;
}

char* String::Data() {
  return body_;
}

void String::PopBack() {
  --size_;
}

void String::PushBack(const char symbol) {
  if (size_ == capacity_) {
    if (capacity_ != 0) {
      capacity_ *= 2;
    } else {
      capacity_ += 1;
    }
    char* temp = body_;
    body_ = new char[capacity_ + 1];
    for (size_t i = 0; i < size_; ++i) {
      body_[i] = temp[i];
    }
    delete[] temp;
  }
  body_[size_] = symbol;
  body_[size_ + 1] = '\0';
  ++size_;
}

bool String::Empty() const {
  return (size_ == 0);
}

void String::ShrinkToFit() {
  if (size_ >= capacity_) {
    return;
  }
  char* helper = body_;
  capacity_ = size_;
  body_ = new char[capacity_ + 1];
  for (size_t i = 0; i < size_; ++i) {
    body_[i] = helper[i];
  }
  body_[size_] = '\0';
  delete[] helper;
}

void String::Reserve(size_t new_capacity) {
  if (capacity_ < new_capacity) {
    capacity_ = new_capacity;
    char* helper = body_;
    body_ = new char[new_capacity + 1];
    for (size_t i = 0; i < size_; ++i) {
      body_[i] = helper[i];
    }
    body_[size_] = '\0';
    delete[] helper;
  }
}

String& String::operator=(const String& other) {
  if (this == &other) {
    return *this;
  }
  delete[] body_;
  size_ = other.Size();
  capacity_ = other.Capacity();
  if (size_ == 0) {
    body_ = nullptr;
    return *this;
  }
  body_ = new char[capacity_ + 1];
  for (size_t i = 0; i < size_; ++i) {
    body_[i] = other[i];
  }
  body_[size_] = '\0';
  return *this;
}

String& String::operator+=(const String& other) {
  for (size_t i = 0; i < other.Size(); ++i) {
    PushBack(other[i]);
  }
  return *this;
}

String operator+(const String& left, const String& right) {
  String res = left;
  res += right;
  return res;
}

bool operator==(const String& left, const String& right) {
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

bool operator!=(const String& left, const String& right) {
  return !(left == right);
}

bool operator>(const String& left, const String& right) {
  if (left.Size() < right.Size()) {
    for (size_t i = 0; i < left.Size(); ++i) {
      if (left[i] != right[i]) {
        return left[i] > right[i];
      }
    }
  } else {
    for (size_t i = 0; i < right.Size(); ++i) {
      if (left[i] != right[i]) {
        return left[i] > right[i];
      }
    }
  }
  return left.Size() > right.Size();
}

bool operator<(const String& left, const String& right) {
  if (left.Size() < right.Size()) {
    for (size_t i = 0; i < left.Size(); ++i) {
      if (left[i] != right[i]) {
        return left[i] < right[i];
      }
    }
  } else {
    for (size_t i = 0; i < right.Size(); ++i) {
      if (left[i] != right[i]) {
        return left[i] < right[i];
      }
    }
  }
  return left.Size() < right.Size();
}

bool operator>=(const String& left, const String& right) {
  if (left.Size() < right.Size()) {
    for (size_t i = 0; i < left.Size(); ++i) {
      if (left[i] != right[i]) {
        return left[i] >= right[i];
      }
    }
  } else {
    for (size_t i = 0; i < right.Size(); ++i) {
      if (left[i] != right[i]) {
        return left[i] >= right[i];
      }
    }
  }
  return left.Size() >= right.Size();
}

bool operator<=(const String& left, const String& right) {
  if (left.Size() < right.Size()) {
    for (size_t i = 0; i < left.Size(); ++i) {
      if (left[i] != right[i]) {
        return left[i] <= right[i];
      }
    }
  } else {
    for (size_t i = 0; i < right.Size(); ++i) {
      if (left[i] != right[i]) {
        return left[i] <= right[i];
      }
    }
  }
  return left.Size() <= right.Size();
}

std::ostream& operator<<(std::ostream& stream, const String& string) {
  ц
}
#include "cppstring.h"

size_t String::Size() const { return size_; }

size_t String::Length() const { return size_; }

size_t String::Capacity() const { return capacity_; }

String::String() : size_(0), capacity_(0), string_(nullptr) {}

String::String(const size_t& size, const char& symbol) {
  size_ = size;
  capacity_ = size;
  if (size == 0) {
    string_ = nullptr;
  } else {
    string_ = new char[size + 1];
    for (size_t i = 0; i < size_; ++i) {
      string_[i] = symbol;
    }
    string_[size_] = '\0';
  }
}

String::String(const char* cstring) {
  size_ = strlen(cstring);
  capacity_ = size_ + 1;
  string_ = new char[capacity_];
  strcpy(string_, cstring);
}

String::String(const char* cstring, const size_t& n) {
  size_ = strlen(cstring);
  capacity_ = n + 1;
  string_ = new char[capacity_];
  strncpy(string_, cstring, n);
  string_[n + 1] = '\0';
}

String::String(const String& other) {
  size_ = other.size_;
  capacity_ = other.capacity_;
  string_ = new char[capacity_];
  strcpy(string_, other.string_);
}

// String& String::operator=(const String& other) {
//   *this = String(other.string_);
//   return *this;
// }

const char& String::operator[](const size_t& pos) const { return string_[pos]; }

char& String::operator[](const size_t& pos) { return string_[pos]; }

const char& String::At(const size_t& pos) const {
  if (pos < size_) {
    return string_[pos];
  }
  throw StringOutOfRange{};
}

char& String::At(const size_t& pos) {
  if (pos < size_) {
    return string_[pos];
  }
  throw StringOutOfRange{};
}

const char& String::Front() const { return string_[0]; }

char& String::Front() { return string_[0]; }

const char& String::Back() const { return string_[size_ - 1]; }

char& String::Back() { return string_[size_ - 1]; }

const char* String::CStr() const { return string_; }

const char* String::Data() const { return string_; }

char* String::CStr() { return string_; }

char* String::Data() { return string_; }

bool String::Empty() const { return size_ == 0; }

void String::Clear() { size_ = 0; }

void String::PopBack() { --size_; }

void String::PushBack(const char& symbol) {
  if (size_ == capacity_) {
    if (capacity_ != 0) {
      capacity_ *= 2;
    } else {
      capacity_ += 1;
    }
    char* old = string_;
    string_ = new char[capacity_ + 1];
    for (size_t i = 0; i < size_; ++i) {
      string_[i] = old[i];
    }
    delete[] old;
  }
  string_[size_] = symbol;
  string_[size_ + 1] = '\0';
  ++size_;
}

void String::Reserve(const size_t& newcapacity) {
  if (capacity_ < newcapacity) {
    capacity_ = newcapacity;
    char* old = string_;
    string_ = new char[newcapacity + 1];
    for (size_t i = 0; i < size_; ++i) {
      string_[i] = old[i];
    }
    string_[size_] = '\0';
    delete[] old;
  }
}

void String::ShrinkToFit() {
  if (size_ >= capacity_) {
    return;
  }
  char* old = string_;
  capacity_ = size_;
  string_ = new char[capacity_ + 1];
  for (size_t i = 0; i < size_; ++i) {
    string_[i] = old[i];
  }
  string_[size_] = '\0';
  delete[] old;
}

String& String::operator=(const String& other) {
  if (this == &other) {
    return *this;
  }
  delete[] string_;
  size_ = other.size_;
  capacity_ = other.capacity_;
  if (size_ == 0) {
    string_ = nullptr;
  } else {
    for (size_t i = 0; i < size_; ++i) {
      string_[i] = other[i];
    }
    string_[size_] = '\0';
  }
  return *this;
}

void String::Swap(String& other) {
  String old = other;
  other = *this;
  *this = old;
}

String& String::operator+=(const String& other) {
  for (size_t i = 0; i < other.size_; ++i) {
    PushBack(other[i]);
  }
  return *this;
}

String operator+(const String& left, const String& right) {
  String ccat = left;
  for (size_t i = 0; i < right.Size(); ++i) {
    ccat.PushBack(right[i]);
  }
  return ccat;
}

bool operator==(const String& left, const String& right) {
  if (left.Size() != right.Size()) {
    return false;
  }
  return strcmp(left.Data(), right.Data()) == 0;
}

bool operator!=(const String& left, const String& right) {
  return not(left == right);
}

bool operator>(const String& left, const String& right) {
  return strcmp(left.Data(), right.Data()) > 0;
}

bool operator<(const String& left, const String& right) {
  return strcmp(left.Data(), right.Data()) < 0;
}

bool operator>=(const String& left, const String& right) {
  return strcmp(left.Data(), right.Data()) >= 0;
}

bool operator<=(const String& left, const String& right) {
  return strcmp(left.Data(), right.Data()) <= 0;
}

void String::Resize(const size_t& newsize, const char& symbol) {
  if (newsize <= size_) {
    size_ = newsize;
    string_[size_] = '\0';
  } else {
    for (size_t i = size_; i < newsize; ++i) {
      PushBack(symbol);
    }
  }
}

std::ostream& operator<<(std::ostream& out, const String& string) {
  out << string.Data();
  return out;
}

String::~String() {
  capacity_ = 0;
  size_ = 0;
  delete[] string_;
}
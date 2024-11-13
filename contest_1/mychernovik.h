#pragma once
#include <cstddef>
#include <cstring>
#include <iostream>
#include <stdexcept>

class StringOutOfRange : public std::out_of_range {
 public:
  StringOutOfRange() : std::out_of_range("StringOutOfRange") {}
};

class String {
 private:
  size_t size_;
  size_t capacity_;
  char* string_;

 public:
  String();
  String(const size_t&, const char&);
  String(const char*);  // NOLINT
  String(const char*, const size_t&);
  String(const String&);
  ~String();

  String& operator=(const String&);
  const char& operator[](const size_t&) const;
  char& operator[](const size_t&);
  const char& At(const size_t&) const;
  char& At(const size_t&);
  const char& Front() const;
  const char& Back() const;
  char& Front();
  char& Back();
  const char* CStr() const;
  const char* Data() const;
  char* CStr();
  char* Data();
  bool Empty() const;
  size_t Size() const;
  size_t Length() const;
  size_t Capacity() const;
  void Clear();
  void Swap(String&);
  void PopBack();
  void PushBack(const char&);
  String& operator+=(const String&);
  void Resize(const size_t&, const char&);
  void Reserve(const size_t&);
  void ShrinkToFit();
};

String operator+(const String&, const String&);
bool operator>(const String&, const String&);
bool operator==(const String&, const String&);
bool operator!=(const String&, const String&);
bool operator<(const String&, const String&);
bool operator>=(const String&, const String&);
bool operator<=(const String&, const String&);
std::ostream& operator<<(std::ostream&, const String&);
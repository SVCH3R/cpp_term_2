#include <iostream>
#include <stdexcept>
#ifndef STRING_H
#define STRING_H

class StringOutOfRange : public std::out_of_range {
 public:
  StringOutOfRange() : std::out_of_range("StringOutOfRange") {
  }
};

class String {
 private:
  char* body_;
  size_t size_;
  size_t capacity_;

 public:
  String();
  String(size_t, const char);
  String(const char*);  // NOLINT
  String(const char*, size_t);
  String(char*, size_t);
  String(const String&);
  ~String();
  
  String& operator=(const String&);
  const char& operator[](size_t) const;
  char& operator[](size_t);
  const char& At(size_t) const;
  char& At(size_t);
  const char& Front() const;
  char& Front();
  const char& Back() const;
  char& Back();
  const char* CStr() const;
  char* CStr();
  const char* Data() const;
  char* Data();
  size_t Size() const;
  size_t Length() const;
  size_t Capacity() const;
  void Clear();
  void Swap(String&);
  void PopBack();
  void PushBack(const char);
  String& operator+=(const String&);
  void Resize(size_t, char);
  void Reserve(size_t);
  void ShrinkToFit();
  friend size_t Strlen(const char*);
  bool Empty() const;
};

String operator+(const String&, const String&);
bool operator>(const String&, const String&);
bool operator==(const String&, const String&);
bool operator!=(const String&, const String&);
bool operator<(const String&, const String&);
bool operator>=(const String&, const String&);
bool operator<=(const String&, const String&);
std::ostream& operator<<(std::ostream&, const String&);

#endif
#pragma once
#include <iostream>
#include <typeinfo>
#include <memory>

class IHolder {
 public:
  virtual ~IHolder() = default;
  virtual IHolder* Clone() const = 0;
};

template <typename T>
class Anyholder : public IHolder {
 public:
  explicit Anyholder(const T& value) : value_(value) {
  }
  explicit Anyholder(T&& value) : value_(std::move(value)) {
  }

  IHolder* Clone() const override {
    return new Anyholder(value_);
  }

  T value_;
};

class Any {
 private:
  std::unique_ptr<IHolder> holder_;

 public:
  Any() : holder_(nullptr) {
  }

  template <typename T>
  explicit Any(const T& value) : holder_(new Anyholder<T>(value)) {
  }

  Any(const Any& other) : holder_(other.holder_ ? other.holder_->Clone() : nullptr) {
  }

  Any& operator=(const Any& other) {
    if (this != &other) {
      Any(other).Swap(*this);
    }
    return *this;
  }

  Any& operator=(Any&& other) noexcept {
    if (this != &other) {
      holder_ = std::move(other.holder_);
      other.holder_ = nullptr;
    }
    return *this;
  }

  void Swap(Any& other) {
    std::swap(holder_, other.holder_);
  }

  void Reset() {
    Any().Swap(*this);
  }

  bool HasValue() const {
    return holder_ != nullptr;
  }

  template <class T>
  friend T AnyCast(const Any& value);
};

class BadAnyCast : public std::bad_cast {
 public:
  const char* what() const noexcept override {
    return "Bad any cast";
  }
};

template <class T>
T AnyCast(const Any& value) {
  if (auto holder = dynamic_cast<Anyholder<T>*>(value.holder_.get())) {
    return holder->value_;
  }
  throw BadAnyCast();
}
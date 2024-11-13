#include <iostream>
#include <stdexcept>

#pragma once

class BadOptionalAccess : public std::exception {
 public:
  const char* what() const noexcept override {
    return "Bad Optional Access";
  }
};

template <typename T>
class Optional {

 private:
  char data_[sizeof(T)];
  bool alive_ = false;
  const T& Data() const {
    return *reinterpret_cast<const T*>(data_);
  }
  T& Data() {
    return *reinterpret_cast<T*>(data_);
  }

 public:
  Optional() noexcept = default;

  Optional(const Optional& other) noexcept {
    if (other.alive_) {
      Emplace(*other);
    }
  }

  Optional(Optional&& other) noexcept {
    if (other.alive_) {
      alive_ = true;
      new (data_) T(std::move(other.Data()));
    }
  }

  explicit Optional(const T& value) noexcept {
    Emplace(value);
  }

  explicit Optional(T&& value) noexcept {
    Emplace(std::move(value));
  }

  ~Optional() {
    Reset();
  }

  Optional& operator=(const T& other) {
    Emplace(other);
    return *this;
  }

  Optional& operator=(T&& other) {
    Emplace(std::move(other));
    return *this;
  }

  Optional& operator=(const Optional& other) {
    if (this != &other) {
      if (other.alive_) {
        Emplace(*other);
      } else {
        Reset();
      }
    }
    return *this;
  }

  Optional& operator=(Optional&& other) noexcept {
    if (this == &other) {
      return *this;
    }
    if (!other.alive_) {
      if (alive_) {
        Data().~T();
      }
      alive_ = false;
      return *this;
    }
    if (alive_) {
      Data() = std::move(other.Data());
    } else {
      new (data_) T(std::move(other.Data()));
    }
    alive_ = true;
    return *this;
  }

  bool HasValue() const noexcept {
    return alive_;
  }

  explicit operator bool() const noexcept {
    return alive_;
  }

  T& Value() & {
    if (!alive_) {
      throw BadOptionalAccess();
    }
    return *reinterpret_cast<T*>(&data_);
  }

  const T& Value() const & {
    if (!alive_) {
      throw BadOptionalAccess();
    }
    return *reinterpret_cast<const T*>(&data_);
  }

  T&& Value() && {
    if (!alive_) {
      throw BadOptionalAccess();
    }
    return std::move(*reinterpret_cast<T*>(&data_));
  }

  const T&& Value() const && {
    if (!alive_) {
      throw BadOptionalAccess();
    }
    return std::move(*reinterpret_cast<const T*>(&data_));
  }

  T& operator*() & noexcept {
    return *reinterpret_cast<T*>(&data_);
  }

  const T& operator*() const & noexcept {
    return *reinterpret_cast<const T*>(&data_);
  }

  T* operator->() noexcept {
    return reinterpret_cast<T*>(&data_);
  }

  const T* operator->() const noexcept {
    return reinterpret_cast<const T*>(&data_);
  }

  template <typename... Args>
  T& Emplace(Args&&... args) noexcept(std::is_nothrow_constructible_v<T, Args...>) {
    Reset();
    new (&data_) T(std::forward<Args>(args)...);
    alive_ = true;
    return Value();
  }

  void Reset() noexcept {
    if (alive_) {
      Value().~T();
      alive_ = false;
    }
  }

  void Swap(Optional& other) {
    Optional helper = std::move(other);
    other = std::move(*this);
    *this = std::move(helper);
  }
};
#pragma once
#include <deque>
#include <iostream>

template <typename T, typename Container = std::deque<T>>
class Stack {
 private:
  Container container_;

 public:
  Stack() = default;

  explicit Stack(const Container& container) : container_(container) {
  }

  template <typename Iterator>
  Stack(Iterator begin, Iterator end) : container_(begin, end) {
  }

  const T& Top() const {
    return container_.back();
  }
  T& Top() {
    return container_.back();
  }

  bool Empty() const {
    return container_.empty();
  }
  std::size_t Size() const {
    return container_.size();
  }
  void Push(const T& value) {
    container_.push_back(value);
  }
  void Push(T&& value) {
    container_.push_back(std::move(value));
  }

  template <typename... Args>
  void Emplace(Args&&... args) {
    container_.emplace_back(std::forward<Args>(args)...);
  }
  void Pop() {
    container_.pop_back();
  }
  void Swap(Stack& other) {
    container_.swap(other.container_);
  }
};
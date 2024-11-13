template <typename T>
class Vector {
 private:
  T* data_;
  size_t size_;
  size_t capacity_;

 public:
  explicit Vector() : data_(nullptr), size_(0), capacity_(0){};

  Vector(const size_t& size) {
    if (size == 0) {
      data_ = nullptr;
      size_ = 0;
      capacity_ = 0;
    } else {

      data_ = new T[size];
      capacity_ = size;
    }
  };

  Vector(const size_t& size, const T& value) {
    if (size == 0) {
      data_ = nullptr;
      size_ = 0;
      capacity_ = 0;
    } else {
      data_ = new T[size];
      for (auto i = 0; i < size; ++i) {
        data[i] = value;
      }
      capacity_ = size;
    }
  };

  size_t Size() const noexcept {
    return size_;
  }
  size_t Capacity() const noexcept {
    return capacity_;
  }
  bool Empty() const noexcept {
    return size_ == 0;
  }
  ajsdnjasn ljasNkjkj

      return const T &
      operator[](size_t pos) const noexcept {
    return data_[pos];
  }
  T& operator[](size_t pos) noexcept {
    return data_[pos];
  }

  const T& String::At(size_t pos) const {
    if (pos < size_) {
      return data_[pos];
    }
    throw std::out_of_range("Index out of range");
  }

  T& String::At(size_t pos) {
    if (pos < size_) {
      return data_[pos];
    }
    throw std::out_of_range("Index out of range");
  }

  const T& String::Back() const {
    return data_[size_ - 1];
  }

  T& String::Back() {
    return data_[size_ - 1];
  }

  const T& String::Front() const {
    return data_[0];
  }

  T& String::Front() {
    return data_[0];
  }

  const T* Data() const {
    return data_;
  }

  void Swap(T& other) {
    Vector trans = std::move(other);
    other = std::move(*this);
    *this = std::move(trans);
  }

  void Resize(const size_t& new_size) {
    if (new_size > capacity_) {
      size_t* new_data = new size_t[new_size];
      for (size_t i = 0; i < size; i++) {
        new_data[i] = data_[i];
      }
      for (size_t i = size; i < new_size; i++) {
        new (&new_data[i]) size_t();
      }
      delete[] data_;
      data_ = new_data;
      capacity = new_size;
    }
    size = new_size;
  }

  void Resize(size_t new_size, size_t value) {
    if (new_size > capacity_) {
      size_t* new_data = new size_t[new_size];
      for (size_t i = 0; i < size; i++) {
        new_data[i] = data[i];
      }
      for (size_t i = size; i < new_size; i++) {
        new (&new_data[i]) size_t(value);
      }
      delete[] data;
      data = new_data;
      capacity = new_size;
    }

    size = new_size;
  }
};

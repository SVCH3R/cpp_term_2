#include <iostream>

template<typename T>
class SharedPtr{
private:
    T* ptr;
    int* strong_counter;
    int* weak_counter;

public:
    SharedPtr() : ptr(nullptr), strong_counter(new int(0)), weak_counter(new int(0)) {}

    explicit SharedPtr(T* other) : ptr(other), strong_counter(new int(1)), weak_counter(new int(0)) {}

    SharedPtr(const SharedPtr& other) : ptr(other.ptr), strong_counter(other.strong_counter), weak_counter(other.weak_counter) {
        (*strong_counter)++;
    }

    SharedPtr(SharedPtr&& other) noexcept : ptr(other.ptr), strong_counter(other.strong_counter), weak_counter(other.weak_counter) {
        other.ptr = nullptr;
        other.strong_counter = nullptr;
        other.weak_counter = nullptr;
    }

    SharedPtr& operator=(const SharedPtr& other){
        if(this != &other){
            this->~SharedPtr();
            ptr = other.ptr;
            strong_counter = other.strong_counter;
            weak_counter = other.weak_counter;
            (*strong_counter)++;
        }
        return *this;
    }

    SharedPtr& operator=(SharedPtr&& other) noexcept{
        if(this != &other){
            this->~SharedPtr();
            ptr = other.ptr;
            strong_counter = other.strong_counter;
            weak_counter = other.weak_counter;
            other.ptr = nullptr;
            other.strong_counter = nullptr;
            other.weak_counter = nullptr;
        }
        return *this;
    }

    ~SharedPtr(){
        (*strong_counter)--;
        if (*strong_counter == 0) {
            delete ptr;
            delete strong_counter;
            delete weak_counter;
            ptr = nullptr;
            strong_counter = nullptr;
            weak_counter = nullptr;
        }
    }

    void Reset(T* other = nullptr){
        this->~SharedPtr();
        ptr = other;
        strong_counter = new int(1);
        weak_counter = new int(0);
    }

    void Swap(SharedPtr<T>& other){
        if (this != &other) {
            std::swap(ptr, other.ptr);
            std::swap(strong_counter, other.strong_counter);
            std::swap(weak_counter, other.weak_counter);
        }
    }

    T* Get(){
        return ptr;
    }

    int UseCount(){
        return *strong_counter;
    }

    T& operator*() const {
        return *ptr;
    }

    T* operator->() const {
        return ptr;
    }

    explicit operator bool() const {
        return ptr != nullptr;
    }
};
#include "pch.h"

template <typename T>
class SharedPtr {
private:
    T* ptr;
    int* ref_count;

    void release() {
        if (ref_count && --(*ref_count) == 0) {
            delete ptr;
            delete ref_count;
        }
    }

public:
    // Constructor
    explicit SharedPtr(T* p = nullptr) : ptr(p), ref_count(nullptr) {
        if (ptr) {
            ref_count = new int(1);
        }
    }

    // Copy constructor
    SharedPtr(const SharedPtr<T>& other) {
        ptr = other.ptr;
        ref_count = other.ref_count;
        if (ref_count) {
            ++(*ref_count);
        }
    }

    // Assignment operator
    SharedPtr<T>& operator=(const SharedPtr<T>& other) {
        if (this != &other) {
            release();  // Release current resource
            ptr = other.ptr;
            ref_count = other.ref_count;
            if (ref_count) {
                ++(*ref_count);
            }
        }
        return *this;
    }

    // Destructor
    ~SharedPtr() {
        release();
    }

    // Dereference operators
    T& operator*() const { return *ptr; }
    T* operator->() const { return ptr; }

    // Get raw pointer
    T* get() const { return ptr; }

    // Use count
    int use_count() const { return ref_count ? *ref_count : 0; }
};


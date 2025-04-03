// smart_ptr.h
#ifndef SMART_PTR_H
#define SMART_PTR_H

#include <type_traits>
#include <utility>

template <typename T>
class smart_ptr {
    T* ptr;
public:
    smart_ptr() noexcept : ptr(nullptr) {}
    explicit smart_ptr(T* p) noexcept : ptr(p) {}

    // Удаление копирования
    smart_ptr(const smart_ptr&) = delete;
    smart_ptr& operator=(const smart_ptr&) = delete;

    // Перемещение
    smart_ptr(smart_ptr&& other) noexcept : ptr(other.ptr) {
        other.ptr = nullptr;
    }
    smart_ptr& operator=(smart_ptr&& other) noexcept {
        if (this != &other) {
            delete ptr;
            ptr = other.ptr;
            other.ptr = nullptr;
        }
        return *this;
    }

    ~smart_ptr() { delete ptr; }

    T& operator*() const noexcept { return *ptr; }
    T* operator->() const noexcept { return ptr; }
    T* get() const noexcept { return ptr; }

    void reset(T* p = nullptr) noexcept {
        delete ptr;
        ptr = p;
    }

    explicit operator bool() const noexcept {
        return ptr != nullptr;
    }

    template<typename Derived, typename... Args>
    static smart_ptr<T> make_derived(Args&&... args) {
        static_assert(std::is_base_of<T, Derived>::value,
                      "Derived must inherit from T");
        return smart_ptr<T>(new Derived(std::forward<Args>(args)...));
    }
};

#endif // SMART_PTR_H

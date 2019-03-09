#pragma once

#include <cassert>
#include <cstddef>
#include <cstdint>
#include <type_traits>

#define GLOBAL_POINTER_MODE ZeroCost // TODO : pass from CMake based on build/target type, production=ZeroCost, testing (ULT, etc.) = FullDebug

// This file contains pointer types to be used in L0ki. Regular pointers (aka raw pointers aka normal pointers) are
// to be used only in special cases (i.e. only on driver's boundaries like API interface or hardware commands). Other
// usages of raw pointers are generally prohibited.
// Usage guidelines:
//   1. There are two types of pointers defined:
//    * L0::PtrOwn<T>(ptr) - means a pointer that owns (uniquely) memory pointed to by ptr
//    * L0::PtrRef<T>(ptr) - means a pointer that references but does not own memory pointed to by ptr
//   2. Key difference between L0 pointers and STL smart pointers is that L0 pointers are designed to be 100% zero-cost
//      in production code. As such, be especially aware of differences between L0::PtrOwn<T> and std::unique_ptr<T> :
//    * L0::PtrOwn<T>(ptr) is not initialized by default to nullptr
//    * L0::PtrOwn<T>(ptr) does not automatically destroy ptr in it's destructor - this can be achieved explicitly by
//      calling L0::PtrOwn<T>::deleteOwned()
//    * L0::PtrOwn<T>'s move ctor and move assignment operators don't handle case when moving/assigning from self. Such
//      behavior will trigger and assert in debug builds
//    * In general L0 ptrs should not have any implicit behaviors - if something is not written directly in the
//      interface function names, assumes it's not there, e.g.:
//     + L0::PtrOwn<T>::rebind will not delete the old memory it pointed to before changing the underlying pointer
//     + However, L0::PtrOwn<T>::rebindDeleteOld will delete the old memory it pointed to before changing the underlying
//       pointer
//   3. There are several different modes/implementations of L0::PtrOwn/PtrRef. All tailored to specific use-cases.
//      All implement the same interface and behave in the same way except for some side effects noted below. While
//      PointerMode enum below describes the full list of modes, these basically boil down into two categories:
//    * ZeroCost mode is the default mode for production drivers. It's aim is to have 100% identical performance traits
//      as raw pointers.
//    * Other than ZeroCost mode is a group of modes aimed at enhancing debug capabilities and enforcement of strict
//      rules around L0 pointers, such as detection of:
//     + dangling pointers
//     + use after free
//     + out of bounds access
//     + abuse of raw pointers
//      Unlike production code, all test code will use highest debug level of L0 pointers available.
//      Please note that distinction between production and non-production builds is based on GLOBAL_POINTER_MODE
//      variable passed by CMake. As such the modes are transparent throughout the code and the only usages of these
//      pointers should be via L0::PtrOwn and L0::PtrRef aliases (i.e. don't use types in L0::pointer_impl directly
//      except for L0::pointer-specific ULTs)
//   4. Additional guidelines:
//    * Refer to ULTs for usage scenarios (ULTs with "Example" keyword) and additional documentation
//    * Use sizes when possible and when defining arrays (i.e. Pointer(T *ptr, size_t numElements)) - this won't impact
//      ZeroCost mode but will be used in Debug modes for bounds checking
//    * when extending interfaces of L0 pointers, do it in a fashion that is coherent with the rest of exposed
//      interface

namespace L0 {

namespace pointer_impl {

enum class PointerMode {
    ZeroCost,             // Performance as with raw pointers
    BasicOwnershipChecks, // TODO : Behaves the same way as ZeroCost but adds basic debug checks
    HeavyOwnershipChecks  // TODO : Behaves the same way as ZeroCost but adds extensive debug checks

    // defaults :
    //  * production = ZeroCost
    //  * UTLs : HeavyOwnershipChecks
    //
    //  BasicOwnershipChecks - should be useful when debugging race conditions for which HeavyOwnershipChecks could
    //                         reduce repro
};

template <typename T>
class IsComplete {
    template <typename TestT, int S = sizeof(TestT)>
    static constexpr bool testIsComplete(int) { return true; }
    template <typename TestT>
    static constexpr bool testIsComplete(...) { return false; }

  public:
    enum { value = testIsComplete<T>(0) };
};

template <typename From, typename To>
struct AssertCanStaticCast {
    static_assert(std::is_base_of<From, To>::value || std::is_base_of<To, From>::value, "Cannot convert between given types, use weakRefReinterpret for reinterpret_cast");
    enum { value = 0 };
};

template <typename T>
struct AssertIsComplete {
    static_assert(IsComplete<T>::value, "Could not interpret incomplete type (forward reference), verify that you include required headers");
    enum { value = 0 };
};

template <PointerMode PointerMode>
struct PointerModeSelector;

template <>
struct PointerModeSelector<PointerMode::ZeroCost> {
    template <bool OwnsMemory>
    struct PointerOwnershipSelector;
};

template <>
struct PointerModeSelector<PointerMode::ZeroCost>::PointerOwnershipSelector<false> {
    template <typename T>
    struct Pointer { // Note : will be aliased by type selector to PtrRef
        using PointerT = T *;
        using PointeeT = T;

        template <typename T2>
        using PointerWeakRefT = typename PointerOwnershipSelector<false>::template Pointer<T2>;

        explicit Pointer() noexcept { // default constructor, Note : this->ptr is unitialized
        }

        Pointer(std::nullptr_t) noexcept // nullptr constructor, note : this->ptr initialized to nullptr
            : ptr(nullptr) {}

        explicit Pointer(T *ptr) noexcept // explicit, binding constructor
            : ptr(ptr) {}

        explicit Pointer(T *ptr, size_t numElements) noexcept // explicit, binding constructor with numElements (or bytes for void)
            : ptr(ptr) {}                                     // Note : size ignored in ZeroCost mode

        Pointer(const Pointer &rhs) noexcept { // non-owning pointer - allow copies
            this->ptr = rhs.ptr;
        }

        Pointer &operator=(const Pointer &rhs) noexcept { // non-owning pointer - allow copies
            this->ptr = rhs.ptr;
            return *this;
        }

        Pointer(Pointer &&rhs) noexcept { // moving allowed - assert(this != &rhs)
            assert(this != &rhs && "Placement new from self?");
            this->ptr = rhs.ptr;
            rhs.ptr = nullptr;
        }

        Pointer &operator=(Pointer &&rhs) noexcept { // moving allowed - assert(this != &rhs)
            assert(this != &rhs && "Assign from self?");
            this->ptr = rhs.ptr;
            rhs.ptr = nullptr;
            return *this;
        }

        void swap(Pointer<T> &rhs) noexcept { // swapping with different non-owning ptr allowed
            auto tmp = this->ptr;
            this->ptr = rhs.ptr;
            rhs.ptr = tmp;
        }

        ~Pointer() noexcept = default; // don't do anything

        bool empty() const noexcept { // check for nullptr
            return nullptr == this->ptr;
        }

        bool notEmpty() const noexcept { // false == empty()
            return false == this->empty();
        }

        void rebind(T *newPointer) noexcept { // change pointer
            this->ptr = newPointer;
        }

        void rebind(T *newPointer, size_t numElements) noexcept { // change pointer with numElements (or bytes for void)
            this->rebind(newPointer);                             // Note : size ignored in ZeroCost mode
        }

        PointerWeakRefT<T> weakRef() const noexcept { // create weak reference (non-owning) pointer
            return PointerWeakRefT<T>(this->ptr);
        }

        template <typename T2>
        PointerWeakRefT<T2> weakRef() const noexcept { // create weak reference of different type (static_cast)
            AssertCanStaticCast<T, T2>::value;
            return PointerWeakRefT<T>(static_cast<T *>(this->ptr));
        }

        template <typename T2>
        PointerWeakRefT<T2> weakRefReinterpret() const noexcept { // create weak reference of different type (reinterpret_cast)
            return PointerWeakRefT<T2>(reinterpret_cast<T2 *>(this->ptr));
        }

        PointerWeakRefT<const T> weakRefAddConst() const noexcept { // create weak reference with const T* , note : no weak_ref_removeconst
            return PointerWeakRefT<const T>(const_cast<const T *>(this->ptr));
        }

        uintptr_t asUintptr() const noexcept { // reintepret_cast to uintptr_t
            return reinterpret_cast<uintptr_t>(this->ptr);
        }

        uint32_t asUintHi() const noexcept { // reintepret_cast to uintptr_t slice of hi part
            return static_cast<uint32_t>((asUintptr() >> 32));
        }

        uint32_t asUintLo() const noexcept { // reintepret_cast to uintptr_t slice of hi part
            return static_cast<uint32_t>(asUintptr());
        }

        explicit operator uintptr_t() const noexcept { // explicit cast to uintptr_t
            return asUintptr();
        }

        template <typename TestType = T>
        auto operator*() const noexcept -> std::enable_if_t<!std::is_void<TestType>::value, T> & { // if not void, allow derefence operator
            AssertIsComplete<PointeeT>::value;
            return *this->ptr;
        }

        template <typename TestType = T>
        auto operator-> () const noexcept -> std::enable_if_t<std::is_class<TestType>::value, T> * { // if class, allow member dereference operator
            AssertIsComplete<PointeeT>::value;
            return this->ptr;
        }

        // Functions available in PtrRef but not available in PtrOwn :
        // * implicit casts
        operator PointerWeakRefT<const T>() const noexcept { // implicit cast to const allowed (as with regular pointers) for non-owning pointer
            return this->weakRefAddConst();
        }

        // * direct access to raw ptr (aka no T* get())
        T *get() const noexcept {
            return this->ptr;
        }

        // * pointer arithmetics, TODO : Add others
        Pointer &operator+=(size_t offset) noexcept { // offset by units of sizeof(T)
            ptr += offset;
            return *this;
        }

        Pointer operator+(size_t offset) noexcept { // offset by units of sizeof(T)
            return Pointer(this->ptr + offset);
        }

        Pointer &offsetBytesBy(size_t offset) noexcept { // offset by bytes
            using RawPtrT = typename std::conditional<std::is_const<PointeeT>::value, const char *, char *>::type;
            this->ptr = reinterpret_cast<T *>(reinterpret_cast<RawPtrT>(this->ptr) + offset);
            return *this;
        }

      protected:
        T *ptr; // uninitialized by default! (as regular pointers)
    };
};

template <>
struct PointerModeSelector<PointerMode::ZeroCost>::PointerOwnershipSelector<true> {
    template <typename T>
    struct Pointer { // will be aliased by type selector to ptr_own
        using PointerT = T *;
        using PointeeT = T;

        template <typename T2>
        using PointerWeakRefT = typename PointerOwnershipSelector<false>::template Pointer<T2>;

        // INLINE HEAVILY
        explicit Pointer() noexcept { // default constructor, note : this->ptr is unitialized
        }

        Pointer(std::nullptr_t) noexcept // nullptr constructor, note : this->ptr initialized to nullptr
            : ptr(nullptr) {}

        explicit Pointer(T *ptr) noexcept // explicit, binding constructor
            : ptr(ptr) {}

        explicit Pointer(T *ptr, size_t numElements) noexcept // explicit, binding constructor with numElements (or bytes for void)
            : ptr(ptr) {}                                     // Note : size ignored in ZeroCost mode

        Pointer(const Pointer &rhs) = delete;            // owning pointer - disallow copies - assert(this != &rhs)
        Pointer &operator=(const Pointer &rhs) = delete; // owning pointer - disallow copies - assert(this != &rhs)

        Pointer(Pointer &&rhs) noexcept { // moving allowed - assert(this != &rhs)
            assert(this != &rhs && "Placement new from self?");
            this->ptr = rhs.ptr;
            rhs.ptr = nullptr;
        }

        Pointer &operator=(Pointer &&rhs) noexcept { // moving allowed - assert(this != &rhs)
            assert(this != &rhs && "Assign from self?");
            this->ptr = rhs.ptr;
            rhs.ptr = nullptr;
            return *this;
        }

        void swap(Pointer<T> &rhs) noexcept { // swapping with different non-owning ptr allowed
            auto tmp = this->ptr;
            this->ptr = rhs.ptr;
            rhs.ptr = tmp;
        }

        ~Pointer() noexcept = default; // don't do anything

        bool empty() const noexcept { // check for nullptr
            return nullptr == this->ptr;
        }

        bool notEmpty() const noexcept { // false == empty()
            return false == this->empty();
        }

        void rebind(T *newPointer) noexcept { // change pointer
            this->ptr = newPointer;
        }

        void rebind(T *newPointer, size_t numElements) noexcept { // change pointer with numElements (or bytes for void)
            this->rebind(newPointer);                             // Note : size ignored in ZeroCost mode
        }

        void rebindDeleteOld(T *newPointer) noexcept { // change owned pointer, delete old one
            assert(this->ptr != newPointer);
            this->deleteOwned();
            this->ptr = newPointer;
        }

        void rebindDeleteOld(T *newPointer, size_t newPointerNumElements) noexcept { // change owned pointer, delete old one
            this->rebindDeleteOld(newPointer);                                       // Note : size ignored in ZeroCost mode
        }

        void deleteOwned() noexcept { // explicitly delete owned pointer
            doDeleteOwned();
        }

        PointerWeakRefT<T> weakRef() const noexcept { // create weak reference (non-owning) pointer
            return PointerWeakRefT<T>(this->ptr);
        }

        template <typename T2>
        PointerWeakRefT<T2> weakRef() const noexcept { // create weak reference of different type (static_cast)
            AssertCanStaticCast<T, T2>::value;
            return PointerWeakRefT<T2>(static_cast<T2 *>(this->ptr));
        }

        template <typename T2>
        PointerWeakRefT<T2> weakRefReinterpret() const noexcept { // create weak reference of different type (reinterpret_cast)
            return PointerWeakRefT<T2>(reinterpret_cast<T2 *>(this->ptr));
        }

        PointerWeakRefT<const T> weakRefAddConst() const noexcept { // create weak reference with const T* , note : no weak_ref_removeconst
            return PointerWeakRefT<const T>(const_cast<const T *>(this->ptr));
        }

        uintptr_t asUintptr() const noexcept { // reintepret_cast to uintptr_t
            return reinterpret_cast<uintptr_t>(this->ptr);
        }

        uint32_t asUintHi() const noexcept { // reintepret_cast to uintptr_t slice of hi part
            return static_cast<uint32_t>((static_cast<uint64_t>(asUintptr()) >> 32));
        }

        uint32_t asUintLo() const noexcept { // reintepret_cast to uintptr_t slice of hi part
            return static_cast<uint32_t>(asUintptr());
        }

        explicit operator uintptr_t() const noexcept { // explicit cast to uintptr_t
            return asUintptr();
        }

        template <typename TestType = T>
        auto operator*() const noexcept -> std::enable_if_t<!std::is_void<TestType>::value, T> & { // if not void, allow derefence operator
            AssertIsComplete<PointeeT>::value;
            return *this->ptr;
        }

        template <typename TestType = T>
        auto operator-> () const noexcept -> std::enable_if_t<std::is_class<TestType>::value, T> * { // if class, allow member dereference operator
            AssertIsComplete<PointeeT>::value;
            return this->ptr;
        }

        // Forced limitations vs ptr_ref :
        // * no direct access to raw ptr (aka no T* get()) in ptr_own - only allowed in ptr_ref, however as_uinptr available
        // * no pointer arithmetic in ptr_own - only allowed ptr_ref
      protected:
        template <typename TestType = T>
        auto doDeleteOwned() noexcept -> std::enable_if_t<std::is_array<TestType>::value, void> { // delete []ptr
            AssertIsComplete<PointeeT>::value;
            delete[] this->ptr;
        }

        template <typename TestType = T>
        auto doDeleteOwned() noexcept -> std::enable_if_t<!std::is_array<TestType>::value, void> { // delete ptr
            AssertIsComplete<PointeeT>::value;
            delete ptr;
        }

        T *ptr; // uninitialized by default! (as regular pointers)
    };
};

static_assert(sizeof(void *) == sizeof(typename pointer_impl::PointerModeSelector<PointerMode::ZeroCost>::template PointerOwnershipSelector<true>::template Pointer<void>), "");
static_assert(sizeof(void *) == sizeof(typename pointer_impl::PointerModeSelector<PointerMode::ZeroCost>::template PointerOwnershipSelector<false>::template Pointer<void>), "");

} // namespace pointer_impl

// compare 2 non-owning pointers
template <typename LhsT, typename RhsT, bool Specialized = true>
inline bool operator==(const typename pointer_impl::PointerModeSelector<pointer_impl::PointerMode::ZeroCost>::template PointerOwnershipSelector<false>::template Pointer<LhsT> &lhs,
                       const typename pointer_impl::PointerModeSelector<pointer_impl::PointerMode::ZeroCost>::template PointerOwnershipSelector<false>::template Pointer<RhsT> &rhs) {
    return lhs.asUintptr() == rhs.asUintptr();
}

// compare owning with non-owning
template <typename LhsT, typename RhsT, bool Specialized = true>
inline bool operator==(const typename pointer_impl::PointerModeSelector<pointer_impl::PointerMode::ZeroCost>::template PointerOwnershipSelector<true>::template Pointer<LhsT> &lhs,
                       const typename pointer_impl::PointerModeSelector<pointer_impl::PointerMode::ZeroCost>::template PointerOwnershipSelector<false>::template Pointer<RhsT> &rhs) {
    return lhs.asUintptr() == rhs.asUintptr();
}

// compare owning with owning - doesn't make much sense
template <typename LhsT, typename RhsT, bool Specialized = true>
inline bool operator==(const typename pointer_impl::PointerModeSelector<pointer_impl::PointerMode::ZeroCost>::template PointerOwnershipSelector<true>::template Pointer<LhsT> &lhs,
                       const typename pointer_impl::PointerModeSelector<pointer_impl::PointerMode::ZeroCost>::template PointerOwnershipSelector<true>::template Pointer<RhsT> &rhs) {
    return lhs.asUintptr() == rhs.asUintptr();
}

// compare with nullptr
template <typename LhsT>
inline bool operator==(const pointer_impl::PointerModeSelector<pointer_impl::PointerMode::ZeroCost>::template PointerOwnershipSelector<true>::template Pointer<LhsT> &lhs, std::nullptr_t) {
    return lhs.asUintptr() == 0;
}

template <typename RhsT>
inline bool operator==(std::nullptr_t, const pointer_impl::PointerModeSelector<pointer_impl::PointerMode::ZeroCost>::template PointerOwnershipSelector<true>::template Pointer<RhsT> &rhs) {
    return rhs.asUintptr() == 0;
}

template <typename LhsT>
inline bool operator==(const pointer_impl::PointerModeSelector<pointer_impl::PointerMode::ZeroCost>::template PointerOwnershipSelector<false>::template Pointer<LhsT> &lhs, std::nullptr_t) {
    return lhs.asUintptr() == 0;
}

template <typename RhsT>
inline bool operator==(std::nullptr_t, const pointer_impl::PointerModeSelector<pointer_impl::PointerMode::ZeroCost>::template PointerOwnershipSelector<false>::template Pointer<RhsT> &rhs) {
    return rhs.asUintptr() == 0;
}

// last resort - try swap lhs and rhs, but only if specialized implementation exists to prevent endless ping-pong recursion
template <typename LhsT, typename RhsT>
auto operator==(const LhsT &lhs, const RhsT &rhs) -> decltype(operator==<RhsT, LhsT, true>(rhs, lhs)) {
    return operator==<RhsT, LhsT, true>(rhs, lhs);
}

template <typename LhsT, typename RhsT>
bool operator!=(const LhsT &lhs, const RhsT &rhs) {
    return false == (lhs == rhs);
}

template <typename T>
using PtrOwn = typename pointer_impl::PointerModeSelector<pointer_impl::PointerMode::GLOBAL_POINTER_MODE>::template PointerOwnershipSelector<true>::template Pointer<T>;

template <typename T>
using PtrRef = typename pointer_impl::PointerModeSelector<pointer_impl::PointerMode::GLOBAL_POINTER_MODE>::template PointerOwnershipSelector<false>::template Pointer<T>;

// const char *
using CStringRef = PtrRef<const char>;

template <typename T>
PtrRef<T> bindPtrRef(T *ptr) { // helper for type deduction
    return PtrRef<T>{ptr};
}

} // namespace L0

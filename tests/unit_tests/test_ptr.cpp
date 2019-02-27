#include "core/source/ptr.h"

#include "gtest/gtest.h"

namespace L0 {
namespace ult {

struct TestStruct;
template <bool Own, typename T>
using ZeroCostPtr = typename L0::pointer_impl::PointerModeSelector<L0::pointer_impl::PointerMode::ZeroCost>::template PointerOwnershipSelector<Own>::template Pointer<T>;

using RefPointerTypes = testing::Types<ZeroCostPtr<false, TestStruct>>;
using OwningPointerTypes = testing::Types<ZeroCostPtr<true, TestStruct>>;
using SmartPointerTypes = testing::Types<ZeroCostPtr<true, TestStruct>,
                                         ZeroCostPtr<true, TestStruct>>;

template <typename ClassT>
class PtrTraits {
    template <typename T1, typename T2 = decltype(T1().deleteOwned())>
    static constexpr bool testDeleteOwned(int) { return true; }
    template <typename T1>
    static constexpr bool testDeleteOwned(...) { return false; }

    template <typename T1, typename T2 = decltype(T1().rebindDeleteOld((typename T1::PointerT) nullptr))>
    static constexpr bool testRebindDeleteOld(int) { return true; }
    template <typename T1>
    static constexpr bool testRebindDeleteOld(...) { return false; }

    template <typename T1, typename T2 = decltype(T1().rebindDeleteOld((typename T1::PointerT) nullptr, 0))>
    static constexpr bool testRebindWithSizeDeleteOld(int) { return true; }
    template <typename T1>
    static constexpr bool testRebindWithSizeDeleteOld(...) { return false; }

    template <typename T1, typename T2 = decltype(T1().get())>
    static constexpr bool testGetFunction(int) { return true; }
    template <typename T1>
    static constexpr bool testGetFunction(...) { return false; }

    template <typename T1, typename T2 = decltype(T1().operator typename T1::template PointerWeakRefT<const typename T1::PointeeT>())>
    static constexpr bool testConstCastOperator(int) { return true; }
    template <typename T1>
    static constexpr bool testConstCastOperator(...) { return false; }

    template <typename T1, typename T2 = decltype(T1().operator+(0))>
    static constexpr bool testAddOperator(int) { return true; }
    template <typename T1>
    static constexpr bool testAddOperator(...) { return false; }

    template <typename T1, typename T2 = decltype(T1().operator+=(0))>
    static constexpr bool testAddAssignOperator(int) { return true; }
    template <typename T1>
    static constexpr bool testAddAssignOperator(...) { return false; }

    template <typename T1, typename T2 = decltype(T1().offsetBytesBy(0))>
    static constexpr bool testOffsetByBytes(int) { return true; }
    template <typename T1>
    static constexpr bool testOffsetByBytes(...) { return false; }

  public:
    enum { hasDeleteOwned = testDeleteOwned<ClassT>(0) };
    enum { hasRebindDeleteOld = testRebindDeleteOld<ClassT>(0) };
    enum { hasRebindWithSizeDeleteOld = testRebindWithSizeDeleteOld<ClassT>(0) };
    enum { hasGetFunction = testGetFunction<ClassT>(0) };
    enum { hasConstCastOperator = testConstCastOperator<ClassT>(0) };
    enum { hasAddOperator = testAddOperator<ClassT>(0) };
    enum { hasAddAssignOperator = testAddAssignOperator<ClassT>(0) };
    enum { hasOffsetByBytes = testOffsetByBytes<ClassT>(0) };
};

struct TestStruct {
    TestStruct(bool *wasDestructedFlag = nullptr)
        : wasDestructedFlag(wasDestructedFlag) {
    }
    ~TestStruct() {
        if (nullptr != wasDestructedFlag) {
            *wasDestructedFlag = true;
        }
    }
    bool *wasDestructedFlag = nullptr;
    int i;
    float f;
};

template <class SmartPointerT>
struct SmartPointerTest : public testing::Test {
    using SmatrPtrT = SmartPointerT;
};

template <class RefPointerT>
using RefPointerTest = SmartPointerTest<RefPointerT>;

template <class OwningPointerT>
using OwningPointerTest = SmartPointerTest<OwningPointerT>;

TYPED_TEST_CASE(SmartPointerTest, SmartPointerTypes);
TYPED_TEST_CASE(RefPointerTest, RefPointerTypes);
TYPED_TEST_CASE(OwningPointerTest, OwningPointerTypes);

TYPED_TEST(SmartPointerTest, IsTheSameSizeAsRawPointers) {
    using SmartPtrT = typename TestFixture::SmatrPtrT;
    EXPECT_EQ(sizeof(void *), sizeof(SmartPtrT));
}

TYPED_TEST(OwningPointerTest, HasExpectedInterface) {
    using SmartPtrT = typename TestFixture::SmatrPtrT;
    EXPECT_FALSE(std::is_copy_constructible<SmartPtrT>()) << "Don't allow copies of owning pointers";
    EXPECT_FALSE(std::is_copy_assignable<SmartPtrT>()) << "Don't allow copies of owning pointers";
    EXPECT_TRUE(std::is_move_constructible<SmartPtrT>()) << "Allow moving of owning pointers";
    EXPECT_TRUE(std::is_move_assignable<SmartPtrT>()) << "Allow moving of owning pointers";
    EXPECT_TRUE(PtrTraits<SmartPtrT>::hasDeleteOwned) << "Allow explicit deletion of owned pointer";
    EXPECT_TRUE(PtrTraits<SmartPtrT>::hasRebindDeleteOld) << "Allow rebind with deletion of previous pointer on owning pointer";
    EXPECT_TRUE(PtrTraits<SmartPtrT>::hasRebindWithSizeDeleteOld) << "Allow rebind with deletion of previous pointer on owning pointer";
    EXPECT_FALSE(PtrTraits<SmartPtrT>::hasGetFunction) << "Don't allow raw pointer access other than uintptr_t from owning pointer";
    EXPECT_FALSE(PtrTraits<SmartPtrT>::hasConstCastOperator) << "Don't allow const cast operator - sharing pointer from owning pointer needs to be explicit";
    EXPECT_FALSE(PtrTraits<SmartPtrT>::hasAddAssignOperator) << "Don't allow pointer arithmetics on owning pointer (would create copies)";
    EXPECT_FALSE(PtrTraits<SmartPtrT>::hasOffsetByBytes) << "Don't allow pointer arithmetics on owning pointer (would create copies)";
}

TYPED_TEST(RefPointerTest, HasExpectedInterface) {
    using SmartPtrT = typename TestFixture::SmatrPtrT;

    EXPECT_TRUE(std::is_copy_constructible<SmartPtrT>()) << "Allow copies of referencing (non-owning) pointers";
    EXPECT_TRUE(std::is_copy_assignable<SmartPtrT>()) << "Allow copies of referencing (non-owning) pointers";
    EXPECT_TRUE(std::is_move_constructible<SmartPtrT>()) << "Allow moving of referencing (non-owning) pointers";
    EXPECT_TRUE(std::is_move_assignable<SmartPtrT>()) << "Allow moving of referencing (non-owning) pointers";
    EXPECT_FALSE(PtrTraits<SmartPtrT>::hasDeleteOwned) << "Don't allow deletion of referencing (non-owning) pointers";
    EXPECT_FALSE(PtrTraits<SmartPtrT>::hasRebindDeleteOld) << "Don't allow deletion of referencing (non-owning) pointers";
    EXPECT_FALSE(PtrTraits<SmartPtrT>::hasRebindWithSizeDeleteOld) << "Don't allow deletion of referencing (non-owning) pointers";
    EXPECT_TRUE(PtrTraits<SmartPtrT>::hasGetFunction) << "Allow raw pointer access of referencing (non-owning) pointers";
    EXPECT_TRUE(PtrTraits<SmartPtrT>::hasConstCastOperator) << "Allow const cast operator of referencing (non-owning) pointers";
    EXPECT_TRUE(PtrTraits<SmartPtrT>::hasAddOperator) << "Allow pointer arithmetics of referencing (non-owning) pointers";
    EXPECT_TRUE(PtrTraits<SmartPtrT>::hasAddAssignOperator) << "Allow pointer arithmetics of referencing (non-owning) pointers";
    EXPECT_TRUE(PtrTraits<SmartPtrT>::hasOffsetByBytes) << "Allow pointer arithmetics of referencing (non-owning) pointers";
}

TYPED_TEST(SmartPointerTest, WhenDefaultConstructingDontInitializeMemoryWhenDestructingDontZeroOut) {
    using SmartPtrT = typename TestFixture::SmatrPtrT;

    TestStruct memory;
    SmartPtrT *x;
    x = new SmartPtrT(&memory);
    x->~SmartPtrT();     // destroy to see that that destructor doesn't set to nullptr
    new (x) SmartPtrT(); // placement new to see that default constructor doesn't null-initialize
    EXPECT_EQ(&memory, x->weakRef().get());
    delete x;
}

TYPED_TEST(SmartPointerTest, WhenConstructingFromNullptrTInitializeToNullptr) {
    using SmartPtrT = typename TestFixture::SmatrPtrT;

    nullptr_t null{};
    SmartPtrT x(null);
    EXPECT_EQ(nullptr, x.weakRef().get());
}

TYPED_TEST(SmartPointerTest, WhenConstructingFromPointerUseThatPointer) {
    using SmartPtrT = typename TestFixture::SmatrPtrT;

    TestStruct memory;
    SmartPtrT x(&memory);
    EXPECT_EQ(&memory, x.weakRef().get());

    SmartPtrT y(&memory, 1);
    EXPECT_EQ(&memory, y.weakRef().get());
}

TYPED_TEST(SmartPointerTest, WhenMovingSetOldOwnerToNullptr) {
    using SmartPtrT = typename TestFixture::SmatrPtrT;

    TestStruct memory;
    SmartPtrT x(&memory);
    EXPECT_EQ(&memory, x.weakRef().get());

    SmartPtrT y(std::move(x));
    EXPECT_EQ(&memory, y.weakRef().get());
    EXPECT_EQ(nullptr, x.weakRef().get());

    x = std::move(y);
    EXPECT_EQ(&memory, x.weakRef().get());
    EXPECT_EQ(nullptr, y.weakRef().get());
}

TYPED_TEST(RefPointerTest, WhenCopyingExpectSamePointers) {
    using SmartPtrT = typename TestFixture::SmatrPtrT;

    TestStruct memory;
    SmartPtrT x(&memory);
    EXPECT_EQ(&memory, x.weakRef().get());

    SmartPtrT y(x);
    SmartPtrT z;
    z = x;

    EXPECT_EQ(&memory, x.get());
    EXPECT_EQ(&memory, y.get());
}

TYPED_TEST(SmartPointerTest, SwapFunction) {
    using SmartPtrT = typename TestFixture::SmatrPtrT;

    TestStruct memory1;
    TestStruct memory2;
    SmartPtrT x(&memory1);
    SmartPtrT y(&memory2);
    x.swap(y);
    EXPECT_EQ(&memory2, x.weakRef().get());
    EXPECT_EQ(&memory1, y.weakRef().get());

    std::swap(x, y);
    EXPECT_EQ(&memory1, x.weakRef().get());
    EXPECT_EQ(&memory2, y.weakRef().get());
}

TYPED_TEST(SmartPointerTest, FunctionEmptyChecksForNullptr) {
    using SmartPtrT = typename TestFixture::SmatrPtrT;

    TestStruct memory;
    SmartPtrT empty(nullptr);
    SmartPtrT notEmpty(&memory);

    EXPECT_TRUE(empty.empty());
    EXPECT_FALSE(empty.notEmpty());

    EXPECT_FALSE(notEmpty.empty());
    EXPECT_TRUE(notEmpty.notEmpty());
}

TYPED_TEST(SmartPointerTest, RebindChangesPointer) {
    using SmartPtrT = typename TestFixture::SmatrPtrT;

    TestStruct memory1;
    TestStruct memory2;

    SmartPtrT x(nullptr);

    x.rebind(&memory1);
    EXPECT_EQ(&memory1, x.weakRef().get());

    x.rebind(&memory2, 1);
    EXPECT_EQ(&memory2, x.weakRef().get());
}

TYPED_TEST(OwningPointerTest, RebindAndDeleteOldChangesPointerAndDeletesPreviousPointer) {
    using SmartPtrT = typename TestFixture::SmatrPtrT;

    bool objectWasDestroyed;

    objectWasDestroyed = false;
    SmartPtrT x(new TestStruct(&objectWasDestroyed));
    EXPECT_FALSE(objectWasDestroyed);

    x.rebindDeleteOld(nullptr);
    EXPECT_TRUE(objectWasDestroyed);

    objectWasDestroyed = false;
    x.rebindDeleteOld(new TestStruct(&objectWasDestroyed), 1);
    EXPECT_FALSE(objectWasDestroyed);

    x.rebindDeleteOld(nullptr, 0);
    EXPECT_TRUE(objectWasDestroyed);
}

TYPED_TEST(OwningPointerTest, DeleteOwnedDestroysOwnedMemory) {
    using SmartPtrT = typename TestFixture::SmatrPtrT;

    bool objectWasDestroyed;

    objectWasDestroyed = false;
    SmartPtrT x(new TestStruct(&objectWasDestroyed));
    EXPECT_FALSE(objectWasDestroyed);

    x.deleteOwned();
    EXPECT_TRUE(objectWasDestroyed);
}

TYPED_TEST(SmartPointerTest, WeakRefCreatesNonOwningPointer) {
    using SmartPtrT = typename TestFixture::SmatrPtrT;
    using WeakRefT = typename SmartPtrT::template PointerWeakRefT<typename SmartPtrT::PointeeT>;

    TestStruct memory;
    SmartPtrT x(&memory);

    auto weakRef = x.weakRef();
    EXPECT_EQ(&memory, weakRef.get());
    bool usesCorrectType = std::is_same<decltype(weakRef), WeakRefT>::value;
    EXPECT_TRUE(usesCorrectType);
}

TYPED_TEST(SmartPointerTest, WeakRefWithCastCreatesNonOwningPointerOfDifferentTypeUsingStaticCast) {
    struct DerivedTestStruct : TestStruct {
    };

    using SmartPtrT = typename TestFixture::SmatrPtrT;
    using WeakRefT = typename SmartPtrT::template PointerWeakRefT<TestStruct>;

    DerivedTestStruct memory;
    SmartPtrT x(&memory);

    auto weakRef = x.template weakRef<TestStruct>();
    EXPECT_EQ(&memory, weakRef.get());
    bool usesCorrectType = std::is_same<decltype(weakRef), WeakRefT>::value;
    EXPECT_TRUE(usesCorrectType);
}

TYPED_TEST(SmartPointerTest, WeakRefWithReinterpretCastCreatesNonOwningPointerOfDifferentTypeUsingReinterpretCast) {
    using SmartPtrT = typename TestFixture::SmatrPtrT;
    using WeakRefT = typename SmartPtrT::template PointerWeakRefT<int>;

    TestStruct memory;
    SmartPtrT x(&memory);

    auto weakRef = x.template weakRefReinterpret<int>();
    EXPECT_EQ(reinterpret_cast<int *>(&memory), weakRef.get());
    bool usesCorrectType = std::is_same<decltype(weakRef), WeakRefT>::value;
    EXPECT_TRUE(usesCorrectType);
}

TYPED_TEST(SmartPointerTest, WeakRefAddConstCreatesNonOwningPointerOfSameTypeButWithConst) {
    using SmartPtrT = typename TestFixture::SmatrPtrT;
    using ConstWeakRefT = typename SmartPtrT::template PointerWeakRefT<const typename SmartPtrT::PointeeT>;

    TestStruct memory;
    SmartPtrT x(&memory);

    auto weakRef = x.weakRefAddConst();
    EXPECT_EQ(&memory, weakRef.get());
    bool usesCorrectType = std::is_same<decltype(weakRef), ConstWeakRefT>::value;
    EXPECT_TRUE(usesCorrectType);
}

TYPED_TEST(SmartPointerTest, AsUintReturnsItengerRepresentationOfRawPointer) {
    using SmartPtrT = typename TestFixture::SmatrPtrT;

    uint64_t ptr64 = 0x0123456789ABCDEF;
    uintptr_t ptrActual = static_cast<uintptr_t>(ptr64);   // deliberately reducing hi to 0 for 32-bit
    uint32_t hi = static_cast<uint32_t>(ptrActual >> 32U); //
    uint32_t lo = static_cast<uint32_t>(ptrActual);

    SmartPtrT x{reinterpret_cast<typename SmartPtrT::PointeeT *>(ptrActual)};
    EXPECT_EQ(ptrActual, x.asUintptr());
    EXPECT_EQ(hi, x.asUintHi());
    EXPECT_EQ(lo, x.asUintLo());

    uintptr_t fromCast = static_cast<uintptr_t>(x);
    EXPECT_EQ(ptrActual, fromCast);
}

TYPED_TEST(SmartPointerTest, DereferenceOperators) {
    using SmartPtrT = typename TestFixture::SmatrPtrT;

    TestStruct memory;
    SmartPtrT x(&memory);
    memory.f = .5f;
    memory.i = 7;

    EXPECT_EQ(.5f, x->f);
    EXPECT_EQ(7, x->i);

    EXPECT_EQ(.5f, (*x).f);
    EXPECT_EQ(7, (*x).i);

    EXPECT_EQ(&memory, &*x);
}

TYPED_TEST(RefPointerTest, ConstCastOperator) {
    using SmartPtrT = typename TestFixture::SmatrPtrT;
    using ConstWeakRefT = typename SmartPtrT::template PointerWeakRefT<const typename SmartPtrT::PointeeT>;

    TestStruct memory;
    SmartPtrT x(&memory);

    ConstWeakRefT weakRef = x;
    EXPECT_EQ(&memory, weakRef.get());
}

TYPED_TEST(RefPointerTest, GetFunctionReturnsRawPointer) {
    using SmartPtrT = typename TestFixture::SmatrPtrT;

    TestStruct memory;
    SmartPtrT x(&memory);

    EXPECT_EQ(&memory, x.get());
}

TYPED_TEST(RefPointerTest, AddOperator) {
    using SmartPtrT = typename TestFixture::SmatrPtrT;

    TestStruct memory;
    SmartPtrT x(&memory);

    const SmartPtrT &y = x + 1; // const reference extends lifemie of temporary

    EXPECT_EQ((&memory) + 1, y.get());
    EXPECT_NE(&x, &y);
}

TYPED_TEST(RefPointerTest, AddAssignOperator) {
    using SmartPtrT = typename TestFixture::SmatrPtrT;

    TestStruct memory;
    SmartPtrT x(&memory);

    const SmartPtrT &y = (x += 1);

    EXPECT_EQ((&memory) + 1, y.get());
    EXPECT_EQ(&x, &y);
}

TYPED_TEST(RefPointerTest, OffsetByBytesReturnsNonOwningPointerOffsetedByGivenAmountOfBytes) {
    using SmartPtrT = typename TestFixture::SmatrPtrT;

    TestStruct memory;
    SmartPtrT x(&memory);

    assert(sizeof(TestStruct) > 1);
    const SmartPtrT &y = x.offsetBytesBy(sizeof(TestStruct));

    EXPECT_EQ((&memory) + 1, y.get());
    EXPECT_EQ(&x, &y);
}

namespace example {
struct BNode {
    BNode(L0::PtrRef<BNode> parent, float value) : parent(parent), value(value) {
    }

    ~BNode() {
        lhsChild.deleteOwned(); // unlike std::unique_ptr, L0::PtrOwn won't destroy memory implicitly
        rhsChild.deleteOwned(); //
    }

    L0::PtrRef<BNode> parent{nullptr};
    L0::PtrOwn<BNode> lhsChild{nullptr};
    L0::PtrOwn<BNode> rhsChild{nullptr};

    float value;
};

void addValue(L0::PtrRef<BNode> root, float val) {
    assert(root.notEmpty());
    L0::PtrRef<BNode> parent{root};
    while (true) {
        if (val <= parent->value) {
            if (parent->lhsChild.empty()) {
                parent->lhsChild.rebind(new BNode{parent, val});
                return;
            } else {
                parent = parent->lhsChild.weakRef();
            }
        } else {
            if (parent->rhsChild.empty()) {
                parent->rhsChild.rebind(new BNode{parent, val});
                return;
            } else {
                parent = parent->rhsChild.weakRef();
            }
        }
    }
}

L0::PtrRef<BNode> findFirstMatch(L0::PtrRef<BNode> root, float val) {
    L0::PtrRef<BNode> parent{root};
    while (true) {
        if (val == parent->value) {
            return parent;
        }
        if (val < parent->value) {
            if (parent->lhsChild.empty()) {
                return nullptr;
            } else {
                parent = parent->lhsChild.weakRef();
            }
        } else {
            if (parent->rhsChild.empty()) {
                return nullptr;
            } else {
                parent = parent->rhsChild.weakRef();
            }
        }
    }
}

TEST(SmartPointerTest, ExampleTreeTraversal) {
    L0::PtrOwn<BNode> root{new BNode{nullptr, 1.0f}};

    float values[] = {2, 3, 5, 7, 11, 13, 17, 19, 23};
    for (float a : values) {
        for (float b : values) {
            addValue(root.weakRef(), a / b);
        }
    }

    for (float a : values) {
        for (float b : values) {
            auto res = findFirstMatch(root.weakRef(), a / b);
            EXPECT_TRUE(res.notEmpty());
        }
    }

    root.deleteOwned(); // unlike std::unique_ptr, L0::PtrOwn won't destroy memory implicitly
}
} // namespace example

} // namespace ult
} // namespace L0

/*
 * Copyright (C) 2017-2018 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 */
//TODO: !!! MIGRATE ME BACK TO NEO !!!
#pragma once
#include "gtest/gtest.h"
#include "hw_info.h"

extern PRODUCT_FAMILY productFamily;
extern GFXCORE_FAMILY renderCoreFamily;

#ifdef TESTS_GEN9
#define SKL_TYPED_TEST_BODY testBodyHw<typename OCLRT::GfxFamilyMapper<IGFX_GEN9_CORE>::GfxFamily>();
#define SKL_TYPED_CMDTEST_BODY runCmdTestHwIfSupported<typename OCLRT::GfxFamilyMapper<IGFX_GEN9_CORE>::GfxFamily>();
#else
#define SKL_TYPED_TEST_BODY
#define SKL_TYPED_CMDTEST_BODY
#endif
#ifdef TESTS_GEN11
#define ICL_TYPED_TEST_BODY testBodyHw<typename OCLRT::GfxFamilyMapper<IGFX_GEN11_CORE>::GfxFamily>();
#define ICL_TYPED_CMDTEST_BODY runCmdTestHwIfSupported<typename OCLRT::GfxFamilyMapper<IGFX_GEN11_CORE>::GfxFamily>();
#else
#define ICL_TYPED_TEST_BODY
#define ICL_TYPED_CMDTEST_BODY
#endif
#ifdef TESTS_GEN12HP
#define ATS_TYPED_TEST_BODY testBodyHw<typename OCLRT::GfxFamilyMapper<IGFX_GEN12_CORE>::GfxFamily>();
#define ATS_TYPED_CMDTEST_BODY runCmdTestHwIfSupported<typename OCLRT::GfxFamilyMapper<IGFX_GEN12_CORE>::GfxFamily>();
#else
#define ATS_TYPED_TEST_BODY
#define ATS_TYPED_CMDTEST_BODY
#endif
#ifdef TESTS_GEN12LP
#define TGLLP_TYPED_TEST_BODY testBodyHw<typename OCLRT::GfxFamilyMapper<IGFX_GEN12LP_CORE>::GfxFamily>();
#define TGLLP_TYPED_CMDTEST_BODY runCmdTestHwIfSupported<typename OCLRT::GfxFamilyMapper<IGFX_GEN12LP_CORE>::GfxFamily>();
#else
#define TGLLP_TYPED_TEST_BODY
#define TGLLP_TYPED_CMDTEST_BODY
#endif

// Macros to provide template based testing.
// Test can use FamilyType in the test -- equivalent to SKLFamily
#define HWTEST_TEST_(test_suite_name, test_name, parent_class, parent_id)            \
    class GTEST_TEST_CLASS_NAME_(test_suite_name, test_name) : public parent_class { \
                                                                                     \
      public:                                                                        \
        GTEST_TEST_CLASS_NAME_(test_suite_name, test_name)                           \
        () {}                                                                        \
                                                                                     \
      private:                                                                       \
        template <typename FamilyType>                                               \
        void testBodyHw();                                                           \
                                                                                     \
        void TestBody() override {                                                   \
            switch (::renderCoreFamily) {                                            \
            case IGFX_GEN9_CORE:                                                     \
                SKL_TYPED_TEST_BODY                                                  \
                break;                                                               \
            case IGFX_GEN11_CORE:                                                    \
                ICL_TYPED_TEST_BODY                                                  \
                break;                                                               \
            case IGFX_GEN12LP_CORE:                                                  \
                TGLLP_TYPED_TEST_BODY                                                \
                break;                                                               \
            case IGFX_GEN12_CORE:                                                    \
                ATS_TYPED_TEST_BODY                                                  \
                break;                                                               \
            default:                                                                 \
                ASSERT_TRUE((false && "Unknown hardware family"));                   \
                break;                                                               \
            }                                                                        \
        }                                                                            \
        static ::testing::TestInfo *const test_info_ GTEST_ATTRIBUTE_UNUSED_;        \
        GTEST_DISALLOW_COPY_AND_ASSIGN_(                                             \
            GTEST_TEST_CLASS_NAME_(test_suite_name, test_name));                     \
    };                                                                               \
                                                                                     \
    ::testing::TestInfo *const GTEST_TEST_CLASS_NAME_(test_suite_name,               \
                                                      test_name)::test_info_ =       \
        ::testing::internal::MakeAndRegisterTestInfo(                                \
            #test_suite_name, #test_name, nullptr, nullptr,                          \
            ::testing::internal::CodeLocation(__FILE__, __LINE__), (parent_id),      \
            ::testing::internal::SuiteApiResolver<                                   \
                parent_class>::GetSetUpCaseOrSuite(),                                \
            ::testing::internal::SuiteApiResolver<                                   \
                parent_class>::GetTearDownCaseOrSuite(),                             \
            new ::testing::internal::TestFactoryImpl<GTEST_TEST_CLASS_NAME_(         \
                test_suite_name, test_name)>);                                       \
    template <typename FamilyType>                                                   \
    void GTEST_TEST_CLASS_NAME_(test_suite_name, test_name)::testBodyHw()

#define HWTEST_F(test_fixture, test_name)               \
    HWTEST_TEST_(test_fixture, test_name, test_fixture, \
                 ::testing::internal::GetTypeId<test_fixture>())

// Macros to provide template based testing.
// Test can use productFamily, gfxCoreFamily and FamilyType in the test
#define HWTEST2_TEST_(test_suite_name, test_name, parent_class, parent_id, test_matcher)                                 \
    class GTEST_TEST_CLASS_NAME_(test_suite_name, test_name) : public parent_class {                                     \
                                                                                                                         \
      public:                                                                                                            \
        GTEST_TEST_CLASS_NAME_(test_suite_name, test_name)                                                               \
        () {}                                                                                                            \
                                                                                                                         \
      private:                                                                                                           \
        using ContainerType = SupportedProductFamilies;                                                                  \
        using MatcherType = test_matcher;                                                                                \
                                                                                                                         \
        template <PRODUCT_FAMILY productFamily, GFXCORE_FAMILY gfxCoreFamily, typename FamilyType>                       \
        void matchBody();                                                                                                \
                                                                                                                         \
        template <PRODUCT_FAMILY productFamily>                                                                          \
        void matched() {                                                                                                 \
            const GFXCORE_FAMILY gfxCoreFamily = static_cast<GFXCORE_FAMILY>(OCLRT::HwMapper<productFamily>::gfxFamily); \
            using FamilyType = typename OCLRT::GfxFamilyMapper<gfxCoreFamily>::GfxFamily;                                \
            matchBody<productFamily, gfxCoreFamily, FamilyType>();                                                       \
        }                                                                                                                \
                                                                                                                         \
        struct MatcherFalse {                                                                                            \
            template <PRODUCT_FAMILY productFamily>                                                                      \
            static void matched() {                                                                                      \
            }                                                                                                            \
        };                                                                                                               \
                                                                                                                         \
        template <unsigned int matcherOrdinal>                                                                           \
        void checkForMatch(PRODUCT_FAMILY matchProduct);                                                                 \
                                                                                                                         \
        void TestBody() override {                                                                                       \
            checkForMatch<SupportedProductFamilies::size - 1u>(::productFamily);                                         \
        }                                                                                                                \
        static ::testing::TestInfo *const test_info_ GTEST_ATTRIBUTE_UNUSED_;                                            \
        GTEST_DISALLOW_COPY_AND_ASSIGN_(                                                                                 \
            GTEST_TEST_CLASS_NAME_(test_suite_name, test_name));                                                         \
    };                                                                                                                   \
                                                                                                                         \
    ::testing::TestInfo *const GTEST_TEST_CLASS_NAME_(test_suite_name,                                                   \
                                                      test_name)::test_info_ =                                           \
        ::testing::internal::MakeAndRegisterTestInfo(                                                                    \
            #test_suite_name, #test_name, nullptr, nullptr,                                                              \
            ::testing::internal::CodeLocation(__FILE__, __LINE__), (parent_id),                                          \
            ::testing::internal::SuiteApiResolver<                                                                       \
                parent_class>::GetSetUpCaseOrSuite(),                                                                    \
            ::testing::internal::SuiteApiResolver<                                                                       \
                parent_class>::GetTearDownCaseOrSuite(),                                                                 \
            new ::testing::internal::TestFactoryImpl<GTEST_TEST_CLASS_NAME_(                                             \
                test_suite_name, test_name)>);                                                                           \
                                                                                                                         \
    template <unsigned int matcherOrdinal>                                                                               \
    void GTEST_TEST_CLASS_NAME_(test_suite_name, test_name)::checkForMatch(PRODUCT_FAMILY matchProduct) {                \
        const PRODUCT_FAMILY productFamily = At<ContainerType, matcherOrdinal>::productFamily;                           \
                                                                                                                         \
        if (matchProduct == productFamily) {                                                                             \
            const bool isMatched = MatcherType::isMatched<productFamily>();                                              \
            using Matcher = typename std::conditional<isMatched,                                                         \
                                                      GTEST_TEST_CLASS_NAME_(test_suite_name, test_name),                \
                                                      MatcherFalse>::type;                                               \
            Matcher::template matched<productFamily>();                                                                  \
        } else {                                                                                                         \
            checkForMatch<matcherOrdinal - 1u>(matchProduct);                                                            \
        }                                                                                                                \
    }                                                                                                                    \
                                                                                                                         \
    template <>                                                                                                          \
    void GTEST_TEST_CLASS_NAME_(test_suite_name, test_name)::checkForMatch<0u>(PRODUCT_FAMILY matchProduct) {            \
        const int matcherOrdinal = 0u;                                                                                   \
        const PRODUCT_FAMILY productFamily = At<ContainerType, matcherOrdinal>::productFamily;                           \
                                                                                                                         \
        if (matchProduct == productFamily) {                                                                             \
            const bool isMatched = MatcherType::isMatched<productFamily>();                                              \
            using Matcher = typename std::conditional<isMatched,                                                         \
                                                      GTEST_TEST_CLASS_NAME_(test_suite_name, test_name),                \
                                                      MatcherFalse>::type;                                               \
            Matcher::template matched<productFamily>();                                                                  \
        }                                                                                                                \
    }                                                                                                                    \
                                                                                                                         \
    template <PRODUCT_FAMILY productFamily, GFXCORE_FAMILY gfxCoreFamily, typename FamilyType>                           \
    void GTEST_TEST_CLASS_NAME_(test_suite_name, test_name)::matchBody()

#define HWTEST2_F(test_fixture, test_name, test_matcher)                  \
    HWTEST2_TEST_(test_fixture, test_name##_##test_matcher, test_fixture, \
                  ::testing::internal::GetTypeId<test_fixture>(), test_matcher)

// Macros to provide template based testing.
// Test can use FamilyType in the test -- equivalent to SKLFamily
#define HWCMDTEST_TEST_(cmdset_gen_base, test_suite_name, test_name, parent_class, parent_id)             \
    class GTEST_TEST_CLASS_NAME_(test_suite_name, test_name) : public parent_class {                      \
                                                                                                          \
      public:                                                                                             \
        GTEST_TEST_CLASS_NAME_(test_suite_name, test_name)                                                \
        () {}                                                                                             \
                                                                                                          \
      private:                                                                                            \
        template <typename FamilyType>                                                                    \
        void testBodyHw();                                                                                \
                                                                                                          \
        template <typename FamilyType, bool ShouldBeTested = FamilyType::supportsCmdSet(cmdset_gen_base)> \
        auto runCmdTestHwIfSupported() -> typename std::enable_if<ShouldBeTested>::type {                 \
            testBodyHw<FamilyType>();                                                                     \
        }                                                                                                 \
                                                                                                          \
        template <typename FamilyType, bool ShouldBeTested = FamilyType::supportsCmdSet(cmdset_gen_base)> \
        auto runCmdTestHwIfSupported() -> typename std::enable_if<false == ShouldBeTested>::type {        \
            /* do nothing */                                                                              \
        }                                                                                                 \
                                                                                                          \
        void TestBody() override {                                                                        \
            switch (::renderCoreFamily) {                                                                 \
            case IGFX_GEN9_CORE:                                                                          \
                SKL_TYPED_CMDTEST_BODY                                                                    \
                break;                                                                                    \
            case IGFX_GEN11_CORE:                                                                         \
                ICL_TYPED_CMDTEST_BODY                                                                    \
                break;                                                                                    \
            case IGFX_GEN12LP_CORE:                                                                       \
                TGLLP_TYPED_CMDTEST_BODY                                                                  \
                break;                                                                                    \
            case IGFX_GEN12_CORE:                                                                         \
                ATS_TYPED_CMDTEST_BODY                                                                    \
                break;                                                                                    \
            default:                                                                                      \
                ASSERT_TRUE((false && "Unknown hardware family"));                                        \
                break;                                                                                    \
            }                                                                                             \
        }                                                                                                 \
        static ::testing::TestInfo *const test_info_ GTEST_ATTRIBUTE_UNUSED_;                             \
        GTEST_DISALLOW_COPY_AND_ASSIGN_(                                                                  \
            GTEST_TEST_CLASS_NAME_(test_suite_name, test_name));                                          \
    };                                                                                                    \
                                                                                                          \
    ::testing::TestInfo *const GTEST_TEST_CLASS_NAME_(test_suite_name,                                    \
                                                      test_name)::test_info_ =                            \
        ::testing::internal::MakeAndRegisterTestInfo(                                                     \
            #test_suite_name, #test_name, nullptr, nullptr,                                               \
            ::testing::internal::CodeLocation(__FILE__, __LINE__), (parent_id),                           \
            ::testing::internal::SuiteApiResolver<                                                        \
                parent_class>::GetSetUpCaseOrSuite(),                                                     \
            ::testing::internal::SuiteApiResolver<                                                        \
                parent_class>::GetTearDownCaseOrSuite(),                                                  \
            new ::testing::internal::TestFactoryImpl<GTEST_TEST_CLASS_NAME_(                              \
                test_suite_name, test_name)>);                                                            \
    template <typename FamilyType>                                                                        \
    void GTEST_TEST_CLASS_NAME_(test_suite_name, test_name)::testBodyHw()

#define HWCMDTEST_F(cmdset_gen_base, test_fixture, test_name)               \
    HWCMDTEST_TEST_(cmdset_gen_base, test_fixture, test_name, test_fixture, \
                    ::testing::internal::GetTypeId<test_fixture>())

#define CALL_IF_MATCH(match_core, match_product, expr)                           \
    auto matchCore = match_core;                                                 \
    auto matchProduct = match_product;                                           \
    if ((::renderCoreFamily == matchCore) &&                                     \
        (IGFX_MAX_PRODUCT == matchProduct || ::productFamily == matchProduct)) { \
        expr;                                                                    \
    }

#define FAMILYTEST_TEST_(test_suite_name, test_name, parent_class, parent_id, match_core, match_product) \
    class GTEST_TEST_CLASS_NAME_(test_suite_name, test_name) : public parent_class {                     \
      public:                                                                                            \
        GTEST_TEST_CLASS_NAME_(test_suite_name, test_name)                                               \
        () {}                                                                                            \
                                                                                                         \
      private:                                                                                           \
        template <typename FamilyType>                                                                   \
        void testBodyHw();                                                                               \
                                                                                                         \
        void TestBody() override {                                                                       \
            CALL_IF_MATCH(match_core, match_product,                                                     \
                          testBodyHw<typename OCLRT::GfxFamilyMapper<match_core>::GfxFamily>())          \
        }                                                                                                \
        void SetUp() override {                                                                          \
            CALL_IF_MATCH(match_core, match_product, parent_class::SetUp())                              \
        }                                                                                                \
        void TearDown() override {                                                                       \
            CALL_IF_MATCH(match_core, match_product, parent_class::TearDown())                           \
        }                                                                                                \
        static ::testing::TestInfo *const test_info_ GTEST_ATTRIBUTE_UNUSED_;                            \
        GTEST_DISALLOW_COPY_AND_ASSIGN_(                                                                 \
            GTEST_TEST_CLASS_NAME_(test_suite_name, test_name));                                         \
    };                                                                                                   \
                                                                                                         \
    ::testing::TestInfo *const GTEST_TEST_CLASS_NAME_(test_suite_name,                                   \
                                                      test_name)::test_info_ =                           \
        ::testing::internal::MakeAndRegisterTestInfo(                                                    \
            #test_suite_name, #test_name, nullptr, nullptr,                                              \
            ::testing::internal::CodeLocation(__FILE__, __LINE__), (parent_id),                          \
            ::testing::internal::SuiteApiResolver<                                                       \
                parent_class>::GetSetUpCaseOrSuite(),                                                    \
            ::testing::internal::SuiteApiResolver<                                                       \
                parent_class>::GetTearDownCaseOrSuite(),                                                 \
            new ::testing::internal::TestFactoryImpl<GTEST_TEST_CLASS_NAME_(                             \
                test_suite_name, test_name)>);                                                           \
    template <typename FamilyType>                                                                       \
    void GTEST_TEST_CLASS_NAME_(test_suite_name, test_name)::testBodyHw()

// Equivalent Hw specific macro for permuted tests
// Test can use FamilyType in the test -- equivalent to SKLFamily
#define HWTEST_P(test_suite_name, test_name)                                                                             \
    class GTEST_TEST_CLASS_NAME_(test_suite_name, test_name) : public test_suite_name {                                  \
      public:                                                                                                            \
        GTEST_TEST_CLASS_NAME_(test_suite_name, test_name)                                                               \
        () {}                                                                                                            \
        template <typename FamilyType>                                                                                   \
        void testBodyHw();                                                                                               \
                                                                                                                         \
        virtual void TestBody() {                                                                                        \
            switch (::renderCoreFamily) {                                                                                \
            case IGFX_GEN9_CORE:                                                                                         \
                SKL_TYPED_TEST_BODY                                                                                      \
                break;                                                                                                   \
            case IGFX_GEN11_CORE:                                                                                        \
                ICL_TYPED_TEST_BODY                                                                                      \
                break;                                                                                                   \
            case IGFX_GEN12_CORE:                                                                                        \
                ATS_TYPED_TEST_BODY                                                                                      \
                break;                                                                                                   \
            case IGFX_GEN12LP_CORE:                                                                                      \
                TGLLP_TYPED_TEST_BODY                                                                                    \
                break;                                                                                                   \
            default:                                                                                                     \
                ASSERT_TRUE((false && "Unknown hardware family"));                                                       \
                break;                                                                                                   \
            }                                                                                                            \
        }                                                                                                                \
                                                                                                                         \
      private:                                                                                                           \
        static int AddToRegistry() {                                                                                     \
            ::testing::UnitTest::GetInstance()->parameterized_test_registry().GetTestCasePatternHolder<test_suite_name>( \
                                                                                 #test_suite_name, __FILE__, __LINE__)   \
                ->AddTestPattern(                                                                                        \
                    #test_suite_name,                                                                                    \
                    #test_name,                                                                                          \
                    new ::testing::internal::TestMetaFactory<                                                            \
                        GTEST_TEST_CLASS_NAME_(test_suite_name, test_name)>());                                          \
            return 0;                                                                                                    \
        }                                                                                                                \
        static int gtest_registering_dummy_;                                                                             \
        GTEST_DISALLOW_COPY_AND_ASSIGN_(                                                                                 \
            GTEST_TEST_CLASS_NAME_(test_suite_name, test_name));                                                         \
    };                                                                                                                   \
    int GTEST_TEST_CLASS_NAME_(test_suite_name,                                                                          \
                               test_name)::gtest_registering_dummy_ =                                                    \
        GTEST_TEST_CLASS_NAME_(test_suite_name, test_name)::AddToRegistry();                                             \
    template <typename FamilyType>                                                                                       \
    void GTEST_TEST_CLASS_NAME_(test_suite_name, test_name)::testBodyHw()

#define HWCMDTEST_P(cmdset_gen_base, test_suite_name, test_name)                                                         \
    class GTEST_TEST_CLASS_NAME_(test_suite_name, test_name) : public test_suite_name {                                  \
      public:                                                                                                            \
        GTEST_TEST_CLASS_NAME_(test_suite_name, test_name)                                                               \
        () {}                                                                                                            \
        template <typename FamilyType>                                                                                   \
        void testBodyHw();                                                                                               \
                                                                                                                         \
        template <typename FamilyType, bool ShouldBeTested = FamilyType::supportsCmdSet(cmdset_gen_base)>                \
        auto runCmdTestHwIfSupported() -> typename std::enable_if<ShouldBeTested>::type {                                \
            testBodyHw<FamilyType>();                                                                                    \
        }                                                                                                                \
                                                                                                                         \
        template <typename FamilyType, bool ShouldBeTested = FamilyType::supportsCmdSet(cmdset_gen_base)>                \
        auto runCmdTestHwIfSupported() -> typename std::enable_if<false == ShouldBeTested>::type {                       \
            /* do nothing */                                                                                             \
        }                                                                                                                \
                                                                                                                         \
        virtual void TestBody() {                                                                                        \
            switch (::renderCoreFamily) {                                                                                \
            case IGFX_GEN9_CORE:                                                                                         \
                SKL_TYPED_CMDTEST_BODY                                                                                   \
                break;                                                                                                   \
            case IGFX_GEN11_CORE:                                                                                        \
                ICL_TYPED_CMDTEST_BODY                                                                                   \
                break;                                                                                                   \
            case IGFX_GEN12_CORE:                                                                                        \
                ATS_TYPED_CMDTEST_BODY                                                                                   \
                break;                                                                                                   \
            case IGFX_GEN12LP_CORE:                                                                                      \
                TGLLP_TYPED_CMDTEST_BODY                                                                                 \
                break;                                                                                                   \
            default:                                                                                                     \
                ASSERT_TRUE((false && "Unknown hardware family"));                                                       \
                break;                                                                                                   \
            }                                                                                                            \
        }                                                                                                                \
                                                                                                                         \
      private:                                                                                                           \
        static int AddToRegistry() {                                                                                     \
            ::testing::UnitTest::GetInstance()->parameterized_test_registry().GetTestCasePatternHolder<test_suite_name>( \
                                                                                 #test_suite_name, __FILE__, __LINE__)   \
                ->AddTestPattern(                                                                                        \
                    #test_suite_name,                                                                                    \
                    #test_name,                                                                                          \
                    new ::testing::internal::TestMetaFactory<                                                            \
                        GTEST_TEST_CLASS_NAME_(test_suite_name, test_name)>());                                          \
            return 0;                                                                                                    \
        }                                                                                                                \
        static int gtest_registering_dummy_;                                                                             \
        GTEST_DISALLOW_COPY_AND_ASSIGN_(                                                                                 \
            GTEST_TEST_CLASS_NAME_(test_suite_name, test_name));                                                         \
    };                                                                                                                   \
    int GTEST_TEST_CLASS_NAME_(test_suite_name,                                                                          \
                               test_name)::gtest_registering_dummy_ =                                                    \
        GTEST_TEST_CLASS_NAME_(test_suite_name, test_name)::AddToRegistry();                                             \
    template <typename FamilyType>                                                                                       \
    void GTEST_TEST_CLASS_NAME_(test_suite_name, test_name)::testBodyHw()

#define FAMILYTEST_TEST_P(test_suite_name, test_name, match_core, match_product)                                         \
    class GTEST_TEST_CLASS_NAME_(test_suite_name, test_name) : public test_suite_name {                                  \
      public:                                                                                                            \
        GTEST_TEST_CLASS_NAME_(test_suite_name, test_name)                                                               \
        () {}                                                                                                            \
        template <typename FamilyType>                                                                                   \
        void testBodyHw();                                                                                               \
                                                                                                                         \
        void TestBody() override {                                                                                       \
            CALL_IF_MATCH(match_core, match_product,                                                                     \
                          testBodyHw<typename OCLRT::GfxFamilyMapper<match_core>::GfxFamily>())                          \
        }                                                                                                                \
        void SetUp() override {                                                                                          \
            CALL_IF_MATCH(match_core, match_product, test_suite_name::SetUp())                                           \
        }                                                                                                                \
        void TearDown() override {                                                                                       \
            CALL_IF_MATCH(match_core, match_product, test_suite_name::TearDown())                                        \
        }                                                                                                                \
                                                                                                                         \
      private:                                                                                                           \
        static int AddToRegistry() {                                                                                     \
            ::testing::UnitTest::GetInstance()->parameterized_test_registry().GetTestCasePatternHolder<test_suite_name>( \
                                                                                 #test_suite_name, __FILE__, __LINE__)   \
                ->AddTestPattern(                                                                                        \
                    #test_suite_name,                                                                                    \
                    #test_name,                                                                                          \
                    new ::testing::internal::TestMetaFactory<                                                            \
                        GTEST_TEST_CLASS_NAME_(test_suite_name, test_name)>());                                          \
            return 0;                                                                                                    \
        }                                                                                                                \
        static int gtest_registering_dummy_;                                                                             \
        GTEST_DISALLOW_COPY_AND_ASSIGN_(                                                                                 \
            GTEST_TEST_CLASS_NAME_(test_suite_name, test_name));                                                         \
    };                                                                                                                   \
    int GTEST_TEST_CLASS_NAME_(test_suite_name,                                                                          \
                               test_name)::gtest_registering_dummy_ =                                                    \
        GTEST_TEST_CLASS_NAME_(test_suite_name, test_name)::AddToRegistry();                                             \
    template <typename FamilyType>                                                                                       \
    void GTEST_TEST_CLASS_NAME_(test_suite_name, test_name)::testBodyHw()

#ifdef TESTS_GEN9
#define GEN9TEST_F(test_fixture, test_name)                          \
    FAMILYTEST_TEST_(test_fixture, test_name, test_fixture,          \
                     ::testing::internal::GetTypeId<test_fixture>(), \
                     IGFX_GEN9_CORE, IGFX_MAX_PRODUCT)
#define GEN9TEST_P(test_suite_name, test_name)    \
    FAMILYTEST_TEST_P(test_suite_name, test_name, \
                      IGFX_GEN9_CORE,             \
                      IGFX_MAX_PRODUCT)
#endif
#ifdef TESTS_SKL
#define SKLTEST_F(test_fixture, test_name)                           \
    FAMILYTEST_TEST_(test_fixture, test_name, test_fixture,          \
                     ::testing::internal::GetTypeId<test_fixture>(), \
                     IGFX_GEN9_CORE, IGFX_SKYLAKE)
#define SKLTEST_P(test_suite_name, test_name)     \
    FAMILYTEST_TEST_P(test_suite_name, test_name, \
                      IGFX_GEN9_CORE,             \
                      IGFX_SKYLAKE)
#endif
#ifdef TESTS_KBL
#define KBLTEST_F(test_fixture, test_name)                           \
    FAMILYTEST_TEST_(test_fixture, test_name, test_fixture,          \
                     ::testing::internal::GetTypeId<test_fixture>(), \
                     IGFX_GEN9_CORE, IGFX_KABYLAKE)
#define KBLTEST_P(test_suite_name, test_name)     \
    FAMILYTEST_TEST_P(test_suite_name, test_name, \
                      IGFX_GEN9_CORE,             \
                      IGFX_KABYLAKE)
#endif
#ifdef TESTS_GLK
#define GLKTEST_F(test_fixture, test_name)                           \
    FAMILYTEST_TEST_(test_fixture, test_name, test_fixture,          \
                     ::testing::internal::GetTypeId<test_fixture>(), \
                     IGFX_GEN9_CORE, IGFX_GEMINILAKE)
#define GLKTEST_P(test_suite_name, test_name)     \
    FAMILYTEST_TEST_P(test_suite_name, test_name, \
                      IGFX_GEN9_CORE,             \
                      IGFX_GEMINILAKE)
#endif
#ifdef TESTS_BXT
#define BXTTEST_F(test_fixture, test_name)                           \
    FAMILYTEST_TEST_(test_fixture, test_name, test_fixture,          \
                     ::testing::internal::GetTypeId<test_fixture>(), \
                     IGFX_GEN9_CORE, IGFX_BROXTON)
#define BXTTEST_P(test_suite_name, test_name)     \
    FAMILYTEST_TEST_P(test_suite_name, test_name, \
                      IGFX_GEN9_CORE,             \
                      IGFX_BROXTON)
#endif
#ifdef TESTS_CFL
#define CFLTEST_F(test_fixture, test_name)                           \
    FAMILYTEST_TEST_(test_fixture, test_name, test_fixture,          \
                     ::testing::internal::GetTypeId<test_fixture>(), \
                     IGFX_GEN9_CORE, IGFX_COFFEELAKE)
#define CFLTEST_P(test_suite_name, test_name)     \
    FAMILYTEST_TEST_P(test_suite_name, test_name, \
                      IGFX_GEN9_CORE,             \
                      IGFX_COFFEELAKE)
#endif
#ifdef TESTS_GEN11
#define ICLLPTEST_F(test_fixture, test_name)                         \
    FAMILYTEST_TEST_(test_fixture, test_name, test_fixture,          \
                     ::testing::internal::GetTypeId<test_fixture>(), \
                     IGFX_GEN11_CORE, IGFX_ICELAKE_LP)
#define ICLLPTEST_P(test_case_name, test_name)   \
    FAMILYTEST_TEST_P(test_case_name, test_name, \
                      IGFX_GEN11_CORE,           \
                      IGFX_ICELAKE_LP)
#define LKFTEST_F(test_fixture, test_name)                           \
    FAMILYTEST_TEST_(test_fixture, test_name, test_fixture,          \
                     ::testing::internal::GetTypeId<test_fixture>(), \
                     IGFX_GEN11_CORE, IGFX_LAKEFIELD)
#define LKFTEST_P(test_case_name, test_name)     \
    FAMILYTEST_TEST_P(test_case_name, test_name, \
                      IGFX_GEN11_CORE,           \
                      IGFX_LAKEFIELD)
#define EHLTEST_F(test_fixture, test_name)                           \
    FAMILYTEST_TEST_(test_fixture, test_name, test_fixture,          \
                     ::testing::internal::GetTypeId<test_fixture>(), \
                     IGFX_GEN11_CORE, IGFX_JASPERLAKE)
#define EHLTEST_P(test_case_name, test_name)     \
    FAMILYTEST_TEST_P(test_case_name, test_name, \
                      IGFX_GEN11_CORE,           \
                      IGFX_JASPERLAKE)
#endif
#ifdef TESTS_GEN12HP
#define ATSTEST_F(test_fixture, test_name)                           \
    FAMILYTEST_TEST_(test_fixture, test_name, test_fixture,          \
                     ::testing::internal::GetTypeId<test_fixture>(), \
                     IGFX_GEN12_CORE, IGFX_TIGERLAKE_HP)
#define ATSTEST_P(test_case_name, test_name)     \
    FAMILYTEST_TEST_P(test_case_name, test_name, \
                      IGFX_GEN12_CORE,           \
                      IGFX_TIGERLAKE_HP)
#endif
#ifdef TESTS_GEN12LP
#define TGLLPTEST_F(test_fixture, test_name)                         \
    FAMILYTEST_TEST_(test_fixture, test_name, test_fixture,          \
                     ::testing::internal::GetTypeId<test_fixture>(), \
                     IGFX_GEN12LP_CORE, IGFX_TIGERLAKE_LP)
#define TGLLPTEST_P(test_case_name, test_name)   \
    FAMILYTEST_TEST_P(test_case_name, test_name, \
                      IGFX_GEN12LP_CORE,         \
                      IGFX_TIGERLAKE_LP)
#define RYFTEST_F(test_fixture, test_name)                           \
    FAMILYTEST_TEST_(test_fixture, test_name, test_fixture,          \
                     ::testing::internal::GetTypeId<test_fixture>(), \
                     IGFX_GEN12LP_CORE, IGFX_RYEFIELD)
#define RYFTEST_P(test_case_name, test_name)     \
    FAMILYTEST_TEST_P(test_case_name, test_name, \
                      IGFX_GEN12LP_CORE,         \
                      IGFX_RYEFIELD)
#define DG1TEST_F(test_fixture, test_name)                           \
    FAMILYTEST_TEST_(test_fixture, test_name, test_fixture,          \
                     ::testing::internal::GetTypeId<test_fixture>(), \
                     IGFX_GEN12LP_CORE, IGFX_DG1)
#define DG1TEST_P(test_case_name, test_name)     \
    FAMILYTEST_TEST_P(test_case_name, test_name, \
                      IGFX_GEN12LP_CORE,         \
                      IGFX_DG1)
#define RKLTEST_F(test_fixture, test_name)                           \
    FAMILYTEST_TEST_(test_fixture, test_name, test_fixture,          \
                     ::testing::internal::GetTypeId<test_fixture>(), \
                     IGFX_GEN12LP_CORE, IGFX_ROCKETLAKE)
#define RKLTEST_P(test_case_name, test_name)     \
    FAMILYTEST_TEST_P(test_case_name, test_name, \
                      IGFX_GEN12LP_CORE,         \
                      IGFX_ROCKETLAKE)
#endif
#define HWTEST_TYPED_TEST(CaseName, TestName)                                              \
    template <typename gtest_TypeParam_>                                                   \
    class GTEST_TEST_CLASS_NAME_(CaseName, TestName) : public CaseName<gtest_TypeParam_> { \
      private:                                                                             \
        typedef CaseName<gtest_TypeParam_> TestFixture;                                    \
        typedef gtest_TypeParam_ TypeParam;                                                \
        template <typename FamilyType>                                                     \
        void testBodyHw();                                                                 \
                                                                                           \
        void TestBody() override {                                                         \
            switch (::renderCoreFamily) {                                                  \
            case IGFX_GEN9_CORE:                                                           \
                SKL_TYPED_TEST_BODY                                                        \
                break;                                                                     \
            case IGFX_GEN11_CORE:                                                          \
                ICL_TYPED_TEST_BODY                                                        \
                break;                                                                     \
            case IGFX_GEN12_CORE:                                                          \
                ATS_TYPED_TEST_BODY                                                        \
                break;                                                                     \
            case IGFX_GEN12LP_CORE:                                                        \
                TGLLP_TYPED_TEST_BODY                                                      \
                break;                                                                     \
            default:                                                                       \
                ASSERT_TRUE((false && "Unknown hardware family"));                         \
                break;                                                                     \
            }                                                                              \
        }                                                                                  \
    };                                                                                     \
    bool gtest_##CaseName##_##TestName##_registered_ GTEST_ATTRIBUTE_UNUSED_ =             \
        ::testing::internal::TypeParameterizedTest<                                        \
            CaseName,                                                                      \
            ::testing::internal::TemplateSel<                                              \
                GTEST_TEST_CLASS_NAME_(CaseName, TestName)>,                               \
            GTEST_TYPE_PARAMS_(CaseName)>::Register("", #CaseName, #TestName, 0);          \
    template <typename gtest_TypeParam_>                                                   \
    template <typename FamilyType>                                                         \
    void GTEST_TEST_CLASS_NAME_(CaseName, TestName)<gtest_TypeParam_>::testBodyHw()

template <typename Fixture>
struct Test
    : public Fixture,
      public ::testing::Test {

    void SetUp() override {
        Fixture::SetUp();
    }

    void TearDown() override {
        Fixture::TearDown();
    }
};

namespace L0 {
namespace ult {

template <PRODUCT_FAMILY... args>
struct SupportedProductFamilyContainer {
    using BaseClass = SupportedProductFamilyContainer<args...>;
    static const PRODUCT_FAMILY productFamily = IGFX_UNKNOWN;
};

template <PRODUCT_FAMILY p, PRODUCT_FAMILY... args>
struct SupportedProductFamilyContainer<p, args...> : SupportedProductFamilyContainer<args...> {
    using BaseClass = SupportedProductFamilyContainer<args...>;

    static const PRODUCT_FAMILY productFamily = p;
    static const std::size_t size = sizeof...(args) + 1;
};

using SupportedProductFamilies = SupportedProductFamilyContainer<IGFX_SKYLAKE,
                                                                 IGFX_TIGERLAKE_LP,
                                                                 IGFX_TIGERLAKE_HP>;

// Static container accessor
template <typename Container, int index>
struct At {
    static const PRODUCT_FAMILY productFamily = At<typename Container::BaseClass, index - 1>::productFamily;
};

template <typename Container>
struct At<Container, 0> {
    static const PRODUCT_FAMILY productFamily = Container::productFamily;
};

// HWTEST2_F matchers
template <GFXCORE_FAMILY gfxCoreFamily>
struct IsGfxCore {
    template <PRODUCT_FAMILY productFamily>
    static constexpr bool isMatched() {
        return ToGfxCoreFamily<productFamily>::get() == gfxCoreFamily;
    }
};

template <PRODUCT_FAMILY product>
struct IsProduct {
    template <PRODUCT_FAMILY productFamily>
    static constexpr bool isMatched() {
        return productFamily == product;
    }
};

template <PRODUCT_FAMILY productFamilyMax>
struct IsAtMostProduct {
    template <PRODUCT_FAMILY productFamily>
    static constexpr bool isMatched() {
        return productFamily <= productFamilyMax;
    }
};

template <PRODUCT_FAMILY productFamilyMin>
struct IsAtLeastProduct {
    template <PRODUCT_FAMILY productFamily>
    static constexpr bool isMatched() {
        return productFamily >= productFamilyMin;
    }
};

template <PRODUCT_FAMILY productFamilyMin, PRODUCT_FAMILY productFamilyMax>
struct IsWithinProducts {
    template <PRODUCT_FAMILY productFamily>
    static constexpr bool isMatched() {
        return productFamily >= productFamilyMin && productFamily <= productFamilyMax;
    }
};

struct MatchAny {
    template <PRODUCT_FAMILY productFamily>
    static constexpr bool isMatched() {
        return true;
    }
};

// Common matchers
using IsGen9 = IsGfxCore<IGFX_GEN9_CORE>;
using IsGen11HP = IsGfxCore<IGFX_GEN11_CORE>;
using IsGen11LP = IsGfxCore<IGFX_GEN11LP_CORE>;
using IsGen12HP = IsGfxCore<IGFX_GEN12_CORE>;
using IsGen12LP = IsGfxCore<IGFX_GEN12LP_CORE>;

using IsATS = IsProduct<IGFX_TIGERLAKE_HP>;
using IsBXT = IsProduct<IGFX_BROXTON>;
using IsCFL = IsProduct<IGFX_COFFEELAKE>;
using IsDG1 = IsProduct<IGFX_DG1>;
using IsEHL = IsProduct<IGFX_JASPERLAKE>;
using IsGLK = IsProduct<IGFX_GEMINILAKE>;
using IsICLLP = IsProduct<IGFX_ICELAKE_LP>;
using IsKBL = IsProduct<IGFX_KABYLAKE>;
using IsLKF = IsProduct<IGFX_LAKEFIELD>;
using IsRKL = IsProduct<IGFX_ROCKETLAKE>;
using IsRYF = IsProduct<IGFX_RYEFIELD>;
using IsSKL = IsProduct<IGFX_SKYLAKE>;
using IsTGLLP = IsProduct<IGFX_TIGERLAKE_LP>;

} // namespace ult
} // namespace L0

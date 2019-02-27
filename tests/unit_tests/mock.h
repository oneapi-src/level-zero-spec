#pragma once
#include "gmock/gmock.h"

namespace L0 {
namespace ult {

template <typename Type>
struct Mock : public Type {
};

} // namespace ult
} // namespace L0

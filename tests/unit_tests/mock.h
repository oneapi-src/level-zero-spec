#pragma once
#include "gmock/gmock.h"

namespace xe {
namespace ult {

template <typename Type>
struct Mock : public Type {
};

} // namespace ult
} // namespace xe

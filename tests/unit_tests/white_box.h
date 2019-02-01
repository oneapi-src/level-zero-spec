#pragma once

namespace xe {

template <typename Type>
struct WhiteBox;

} // namespace xe

template <typename Type>
xe::WhiteBox<Type> *whitebox_cast(Type *obj) {
    return static_cast<xe::WhiteBox<Type> *>(obj);
}

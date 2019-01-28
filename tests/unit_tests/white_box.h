#pragma once

template<typename Type>
struct WhiteBox;

template<typename Type>
WhiteBox<Type> *whitebox_cast(Type *obj) {
    return static_cast<WhiteBox<Type> *>(obj);
}

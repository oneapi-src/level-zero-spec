#pragma once

#include "runtime/helpers/ptr_math.h"

#include <cassert>
#include <cstddef>

namespace NEO {
class LinearStream;
}

namespace L0 {

struct Substream {
    Substream(NEO::LinearStream &parent, void *substreamBuffer, size_t substreamSize)
        : parent(parent), substreamBuffer(substreamBuffer), substreamSize(substreamSize) {
    }

    Substream(const Substream &) = delete;
    Substream &operator=(const Substream &) = delete;
    Substream &operator=(Substream &&) = delete;

    Substream(Substream &&rhs)
        : parent(rhs.parent) {
        assert(this != &rhs);
        this->substreamBuffer = rhs.substreamBuffer;
        this->substreamSize = rhs.substreamSize;
        this->substreamSizeUsed = rhs.substreamSizeUsed;
        rhs.substreamBuffer = nullptr;
        rhs.substreamSize = 0;
        rhs.substreamSizeUsed = 0;
    }

    ~Substream() {
        // nothing, parent stream owns resources
    }

    NEO::LinearStream &getParent() {
        return parent;
    }

    size_t getBaseOffsetInParent() {
        return ptrDiff(substreamBuffer, parent.getCpuBase());
    }

    size_t getSize() {
        return substreamSize;
    }

    size_t getSizeUsed() {
        return substreamSizeUsed;
    }

    template <typename Cmd>
    Cmd *getSpaceForCmd() {
        auto ptr = getSpace(sizeof(Cmd));
        return reinterpret_cast<Cmd *>(ptr);
    }

  protected:
    // not allowed as heap object - designed as lightweight temporary stack object
    static void *operator new(std::size_t);
    static void *operator new[](std::size_t);

    inline void *getSpace(size_t size) {
        assert(substreamSize >= substreamSizeUsed + size);
        auto memory = ptrOffset(substreamBuffer, substreamSizeUsed);
        substreamSizeUsed += size;
        return memory;
    }

    NEO::LinearStream &parent;
    void *substreamBuffer = nullptr;
    size_t substreamSize = 0;
    size_t substreamSizeUsed = 0;
};

} // namespace L0

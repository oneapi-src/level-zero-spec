#pragma once

namespace L0 {

class OsContext {
  public:
    OsContext() {}

    static OsContext *create();
};

} // namespace L0

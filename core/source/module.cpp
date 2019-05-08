#include "module.h"

namespace L0 {

xe_result_t functionCreate(xe_module_handle_t hModule, const xe_function_desc_t *desc,
                           xe_function_handle_t *phFunction) {
    Module *module = Module::fromHandle(hModule);
    return module->createFunction(desc, phFunction);
}

xe_result_t functionDestroy(xe_function_handle_t hFunction) {
    return Function::fromHandle(hFunction)->destroy();
}

} // namespace L0

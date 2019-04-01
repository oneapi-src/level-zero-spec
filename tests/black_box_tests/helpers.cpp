#include <string>
#include <vector>

#define QTR(a) #a
#define TOSTR(b) QTR(b)

std::vector<const char*> locations;

class Helpers {
    public:
    Helpers() {
        // first look into test_files location 
        locations.push_back("test_files/spv_modules/");
#if defined(OS_DATADIR)
        // later try install location when OS_DATADIR is defined
        locations.push_back(TOSTR(OS_DATADIR));
#endif
    }
};

static Helpers spvHelpers;


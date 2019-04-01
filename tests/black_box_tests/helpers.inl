#include <iostream>
#include <fstream>
#include <memory>
#include <vector>

extern std::vector<const char*> locations;

template <typename SizeT>
inline std::unique_ptr<char[]> readBinaryFile(const std::string &name, SizeT &outSize) {
    for(const char *base : locations) {
        std::string s(base);
        std::ifstream file(s + name, std::ios_base::binary);
        if (false == file.good()) {
            continue;
        }

        size_t length;
        file.seekg(0, file.end);
        length = static_cast<size_t>(file.tellg());
        file.seekg(0, file.beg);

        auto storage = std::make_unique<char[]>(length);
        file.read(storage.get(), length);

        outSize = static_cast<SizeT>(length);
        return storage;
    }
    outSize = 0;
    return nullptr;
}


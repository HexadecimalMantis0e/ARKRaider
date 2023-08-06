#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstdint>
#include <filesystem>
#include "Ark.hpp"
#include "Util.hpp"

int main(int argc, char *argv[]) {
    if (argc < 2) {
        usage();
        return 0;
    }

    std::ifstream fs;
    fs.open(argv[1], std::ios::in | std::ios::binary);

    if (!fs) {
        std::cout << "Could not open file!" << std::endl;
        return 1;
    }

    std::filesystem::path path = argv[1];
    std::string arkName = path.filename().stem().string();
    Ark ark;

    if (ark.readArk(fs)) {
        extractArk(ark, arkName);
    }
    else {
        usage();
    }
    return 0;
}

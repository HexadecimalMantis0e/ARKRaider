#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstdint>
#include <filesystem>
#include "Ark.hpp"
#include "Util.hpp"

void usage() {
    std::cout << "ARKRaider: Extract Genuine Games ARK files" << std::endl;
    std::cout << "Usage: ARKRaider path/to/ARK" << std::endl;
}

void extractArk(const Ark &ark, const std::string &arkName) {
    std::cout << "Extracting ARK..." << std::endl;
    
    std::uint32_t fileCount = ark.getFileCount();
    std::cout << "Number of files: " << fileCount << std::endl;
    std::cout << std::endl;
    std::filesystem::create_directory(arkName);

    for (int i = 0; i < static_cast<int>(fileCount); i++) {
        const FileEntry &entry = ark.getFileEntry(i);
        const std::vector<std::uint8_t> &fileBytes = ark.getFile(i);
        const std::string &name = entry.name;
        std::uint32_t size = entry.size;

        std::filesystem::path path = arkName;
        path /= name;

        std::ofstream fs;
        fs.open(path, std::ios::out | std::ios::binary);

        std::cout << "Name: " << name << std::endl;
        std::cout << "Address: 0x" << std::hex << entry.address << std::endl;
        std::cout << "Size: 0x" << std::hex << size << std::endl;
        std::cout << std::endl;
        fs.write(reinterpret_cast<const char *>(fileBytes.data()), size);
    }
    std::cout << "Done!" << std::endl;
}

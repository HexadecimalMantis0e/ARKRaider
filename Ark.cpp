#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstdint>
#include <filesystem>
#include "Ark.hpp"

bool Ark::readArk(std::ifstream &fs) {
    std::uint32_t header = 0;

    fs.read(reinterpret_cast<char *>(&header), 0x04);

    if (header != this->header) {
        return false;
    }

    fs.read(reinterpret_cast<char *>(&fileCount), 0x04);
    fs.seekg(0x08, std::ios::cur);

    for (int i = 0; i < static_cast<int>(fileCount); i++) {
        std::string name;
        std::getline(fs, name, '\0');
        fs.seekg(0x20 - (name.length() + 0x01), std::ios::cur);

        std::uint32_t hash = 0;
        fs.read(reinterpret_cast<char *>(&hash), 0x04);
        std::uint32_t address = 0;
        fs.read(reinterpret_cast<char *>(&address), 0x04);
        std::uint32_t size = 0;
        fs.read(reinterpret_cast<char *>(&size), 0x04);
        std::uint32_t unk0 = 0;
        fs.read(reinterpret_cast<char *>(&unk0), 0x04);

        fileEntries.push_back(FileEntry(name, hash, address, size, unk0));

        std::uint32_t goBack = fs.tellg();
        fs.seekg(address, std::ios::beg);

        std::vector<std::uint8_t> fileBytes(size, 0x00);

        if (!fileBytes.empty()) {
            fs.read(reinterpret_cast<char *>(fileBytes.data()), size);
            files.push_back(fileBytes);
        }

        fs.seekg(goBack, std::ios::beg);
    }

    return true;
}

std::uint32_t Ark::getFileCount() const {
    return fileCount;
}

const std::vector<uint8_t> &Ark::getFile(int index) const {
    return files.at(index);
}

const FileEntry &Ark::getFileEntry(int index) const {
    return fileEntries.at(index);
}

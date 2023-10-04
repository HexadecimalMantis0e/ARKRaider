#ifndef ARK_HPP
#define ARK_HPP

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstdint>
#include <filesystem>

struct FileEntry {
    std::string name;
    std::uint32_t hash = 0;
    std::uint32_t address = 0;
    std::uint32_t size = 0;
    std::uint32_t unk0 = 0;

    FileEntry(std::string &name, std::uint32_t hash, std::uint32_t address, std::uint32_t size, std::uint32_t unk0): name(name) {
        this->hash = hash;
        this->address = address;
        this->size = size;
        this->unk0 = unk0;
    }
};

class Ark {
    private:
        const std::uint32_t header = 0x004B5241;
        std::uint32_t fileCount = 0;
        std::vector<FileEntry> fileEntries;
        std::vector<std::vector<std::uint8_t>> files;

    public:
        bool readArk(std::ifstream &fs);
        std::uint32_t getFileCount() const;
        const std::vector<std::uint8_t> &getFile(int index) const;
        const FileEntry &getFileEntry(int index) const;
};

#endif

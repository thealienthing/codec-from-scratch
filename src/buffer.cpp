#include "buffer.hpp"
#include <iostream>
#include <fstream>

Buffer::Buffer(const std::string& str_in)
{
    buffer = std::vector<std::byte> (
        reinterpret_cast<const std::byte*>(str_in.data()),
        reinterpret_cast<const std::byte*>(str_in.data() + str_in.size()));
}

std::string Buffer::debug_str() {
    std::string out_str;
    for(auto i = 0; i < this->size(); i++) {
        // std::cout << std::to_integer<int>(buffer[i]) << std::endl;
        out_str += std::to_integer<int>(buffer[i]);
    }
    return out_str;
}

Buffer read_file_to_buffer(const std::string& file_path) {
    std::ifstream file(file_path, std::ios::binary | std::ios::ate);
    if(!file) {
        std::cerr << "Failed to open file: " << file_path << std::endl;
        return Buffer();
    }

    auto file_size = file.tellg();

    file.seekg(0, std::ios::beg);

    std::vector<std::byte> buffer(file_size);

    file.read(reinterpret_cast<char*>(buffer.data()), file_size);

    std::cout << "Read " << file_size << " bytes from " << file_path << " into buffer which is now " << buffer.size() << " bytes" << std::endl;



    return Buffer(std::move(buffer));
}
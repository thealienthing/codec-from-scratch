#include <iostream>
#include <cstring>
#include <codec.hpp>

int main() {
    const char* data_str = "AAAAABBCCCCCDDEEEFFFGGGGGGGGG";
    std::cout << data_str << std::endl;
    auto ret = run_length_encode(data_str, strlen(data_str));
    for(uint8_t n : ret) {
        std::cout << static_cast<int>(n);
    }
    std::cout << std::endl;

    auto decoded = run_length_decode(reinterpret_cast<const char*>(ret.data()), ret.size());
    std::cout << decoded.data() << std::endl;


    return 0;
}
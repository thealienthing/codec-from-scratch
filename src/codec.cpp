#include "codec.hpp"
#include <iostream>
#include <memory>
#include <vector>

Buffer run_length_encode(Buffer data)
{
    Buffer ret;
    for (auto byte = 0; byte < data.size();) {
        std::byte cur = data[byte];
        int repetitions = 1;
        for (auto next = byte + 1; next < data.size(); next++) {
            // std::cout << "Cur: " << cur << " Next: " << data[next] << std::endl;
            repetitions++;
            if (cur != data[next]) {
                // std::cout << "break" << std::endl;
                break;
            }
        }

        ret.push_back(static_cast<std::byte>(repetitions));
        ret.push_back(static_cast<std::byte>(cur));
        byte += repetitions;
    }
    return ret;
}

Buffer run_length_decode(Buffer data)
{
    Buffer ret;
    for (auto i = 0; i < data.size(); i += 2) {
        int reps = static_cast<int>(data.at(i));
        std::byte val = data[i + 1];
        for (auto r = 0; r < reps; r++) {
            ret.push_back(val);
        }
    }
    return ret;
}

Buffer bytes_from_string(const std::string& str_in) {
    std::vector<std::byte> byte_vec(
        reinterpret_cast<const std::byte*>(str_in.data()),
        reinterpret_cast<const std::byte*>(str_in.data() + str_in.size())
    );
    return byte_vec;
}

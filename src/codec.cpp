#include "codec.hpp"
#include <iostream>
#include <memory>
#include <vector>

Buffer rle(Buffer data)
{
    Buffer ret;
    int max_reps = 0;
    for (auto byte = 0; byte < data.size();) {
        std::byte cur = data[byte];
        int repetitions = 1;
        for (auto next = byte + 1; next < data.size(); next++) {
            // std::cout << "Cur: " << cur << " Next: " << data[next] << std::endl;
            if (cur != data[next]) {
                // std::cout << "break" << std::endl;
                break;
            }
            repetitions++;
        }
        // if(repetitions > 1) {
        //     std::cout << "Repetitions: " << repetitions << std::endl;
        // }
        if(repetitions > max_reps) max_reps = repetitions;

        ret.push_back(static_cast<std::byte>(repetitions));
        ret.push_back(static_cast<std::byte>(cur));
        byte += repetitions;
    }
    std::cout << "Max reps: " << max_reps << std::endl;
    return ret;
}

Buffer rld(Buffer data)
{
    Buffer ret;
    for (auto i = 0; i < data.size(); i += 2) {
        int reps = std::to_integer<int>(data[i]);
        std::byte val = data[i + 1];

        for (auto r = 0; r < reps; r++) {
            ret.push_back(val);
        }
    }
    return ret;
}



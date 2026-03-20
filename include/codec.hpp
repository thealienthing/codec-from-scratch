#pragma once

#include <vector>
#include <cstdint>
#include <string>

typedef std::vector<std::byte> Buffer;


Buffer run_length_encode(Buffer data);
Buffer run_length_decode(Buffer data);
Buffer bytes_from_string(const std::string& str_in);
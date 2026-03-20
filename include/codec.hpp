#pragma once

#include "buffer.hpp"
#include <cstdint>
#include <string>
#include <vector>
#include <iostream>
#include <cstddef>

Buffer rle(Buffer data);
Buffer rld(Buffer data);
Buffer bytes_from_string(const std::string& str_in);
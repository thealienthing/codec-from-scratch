#pragma once

#include "buffer.hpp"
#include <string>

Buffer rle(Buffer data);
Buffer rld(Buffer data);
Buffer bytes_from_string(const std::string &str_in);
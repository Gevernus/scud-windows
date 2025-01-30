#pragma once
#include <string>
#include <chrono>

namespace TokenUtils
{
    std::string generate_token();
    bool validate_token(const std::string &token);
}
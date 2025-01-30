#include "token_utils.h"
#include <uuid/uuid.h> // Requires libuuid on Linux/Mac (for cross-dev)

namespace TokenUtils
{
    std::string generate_token()
    {
        uuid_t uuid;
        uuid_generate(uuid);
        char uuid_str[37];
        uuid_unparse(uuid, uuid_str);

        auto timestamp = std::chrono::system_clock::now().time_since_epoch().count();
        return std::string(uuid_str) + "|" + std::to_string(timestamp);
    }

    bool validate_token(const std::string &token)
    {
        size_t sep_pos = token.find_last_of('|');
        if (sep_pos == std::string::npos)
            return false;

        try
        {
            auto timestamp = std::stoll(token.substr(sep_pos + 1));
            auto now = std::chrono::system_clock::now().time_since_epoch().count();
            return (now - timestamp) < 30000000000; // 30-second expiry (nanoseconds)
        }
        catch (...)
        {
            return false;
        }
    }
}
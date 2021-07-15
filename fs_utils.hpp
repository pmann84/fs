#ifndef FSPP_FS_UTILS_HPP
#define FSPP_FS_UTILS_HPP

#include <chrono>
#include <cstdint>
#include <filesystem>

namespace fs
{
    inline uintmax_t get_num_digits (uintmax_t i)
    {
        return i > 0 ? (uintmax_t) log10 ((double) i) + 1 : 1;
    }

    inline std::string file_time_to_string(std::filesystem::file_time_type file_time)
    {
        auto sctp = std::chrono::time_point_cast<std::chrono::system_clock::duration>(file_time - std::filesystem::file_time_type::clock::now() + std::chrono::system_clock::now());
        std::time_t tt = std::chrono::system_clock::to_time_t(sctp);
        std::tm *gmt = std::gmtime(&tt);
        std::stringstream buffer;
        buffer << std::put_time(gmt,"%Y-%m-%d %H:%M");
        std::string formatted_file_time = buffer.str();
        return formatted_file_time;
    }
}

#endif //FSPP_FS_UTILS_HPP

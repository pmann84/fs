
#include "argparse.hpp"

#include <filesystem>
#include <chrono>
#include <map>
//#include <chrono>
//#include <filesystem>
//#include <iomanip>
//#include <iostream>
//#include <sstream>

// lspp  // Lists current directory
// lspp ..  // Lists specified directory
// lspp .. . // Lists all specified directories

argparse::argument_parser setup_and_parse_args(int argc, char *argv[])
{
    auto parser = argparse::argument_parser("lspp arguments", "");
    parser.add_argument("path")
            .num_args("*")
            .default_value<std::string>(".")
            .help("Path(s) to list.");
    parser.parse_args(argc, argv);
    return parser;
}

std::string file_time_to_string(std::filesystem::file_time_type file_time)
{
    auto sctp = std::chrono::time_point_cast<std::chrono::system_clock::duration>(file_time - std::filesystem::file_time_type::clock::now() + std::chrono::system_clock::now());
    std::time_t tt = std::chrono::system_clock::to_time_t(sctp);
    std::tm *gmt = std::gmtime(&tt);
    std::stringstream buffer;
    buffer << std::put_time(gmt,"%Y-%m-%d %H:%M");
    std::string formatted_file_time = buffer.str();
    return formatted_file_time;
}

uintmax_t get_num_digits (uintmax_t i)
{
    return i > 0 ? (uintmax_t) log10 ((double) i) + 1 : 1;
}

struct list_details
{
    std::filesystem::path path;
    std::vector<std::filesystem::directory_entry> entries;
    uint32_t num_files = 0;
    uint32_t num_dirs = 0;
    uintmax_t max_digit_size = 1;
};

void output_path_permissions(const std::filesystem::path& path)
{
    auto p = std::filesystem::status(path).permissions();
    bool is_directory = std::filesystem::is_directory(path);
    std::string dir_marker = is_directory ? "d" : "-";
    std::cout << dir_marker;
    std::cout << ((p & std::filesystem::perms::owner_read) != std::filesystem::perms::none ? "r" : "-")
              << ((p & std::filesystem::perms::owner_write) != std::filesystem::perms::none ? "w" : "-")
              << ((p & std::filesystem::perms::owner_exec) != std::filesystem::perms::none ? "x" : "-")
              << ((p & std::filesystem::perms::group_read) != std::filesystem::perms::none ? "r" : "-")
              << ((p & std::filesystem::perms::group_write) != std::filesystem::perms::none ? "w" : "-")
              << ((p & std::filesystem::perms::group_exec) != std::filesystem::perms::none ? "x" : "-")
              << ((p & std::filesystem::perms::others_read) != std::filesystem::perms::none ? "r" : "-")
              << ((p & std::filesystem::perms::others_write) != std::filesystem::perms::none ? "w" : "-")
              << ((p & std::filesystem::perms::others_exec) != std::filesystem::perms::none ? "x" : "-");
}

void print_directory_entry(const std::filesystem::directory_entry& entry, uintmax_t max_digit_size)
{
    output_path_permissions(entry.path());

    std::cout << "  " << file_time_to_string(entry.last_write_time()) << "  ";
    // Size in bytes
    std::cout << std::setw(max_digit_size) << entry.file_size() << "   ";

    std::wcout << entry.path().filename().c_str() << std::endl;
}

void output_directory_header(const std::filesystem::path& path)
{
    std::cout << "|||> " << std::filesystem::absolute(path).string();
    if (path == "." || path == "..")
    {
        std::cout << " (" << path.string() << ")";
    }
    std::cout << ":" << std::endl;
}

int main(int argc, char *argv[])
{
    auto parser = setup_and_parse_args(argc, argv);

    auto paths = parser.get<std::vector<std::string>>("path");
    std::vector<list_details> listed_dirs;

    // Initial pass
    for (auto& path : paths)
    {
        bool input_path_exists = std::filesystem::exists(path);
        list_details result;
        result.path = std::filesystem::path(path);
        if (input_path_exists && std::filesystem::is_directory(path))
        {
            for (const auto& entry: std::filesystem::directory_iterator(path))
            {
                result.entries.push_back(entry);
                auto num_file_digits = get_num_digits(entry.file_size());
                if (num_file_digits > result.max_digit_size)
                {
                    result.max_digit_size = num_file_digits;
                }
                if (entry.is_directory())
                    result.num_dirs++;
                else
                    result.num_files++;
            }
        }
        listed_dirs.push_back(result);
    }

    // Output
    for (auto& dir : listed_dirs)
    {
        bool multiple_dirs = listed_dirs.size() > 1;
        if (multiple_dirs)
        {
            output_directory_header(dir.path);
        }

        if (std::filesystem::exists(dir.path))
        {
            if (dir.entries.empty() && !is_directory(dir.path))
            {
                // TODO: Print some file stats - replace print_directory_entry with something else
                std::filesystem::directory_entry entry(dir.path);
                print_directory_entry(entry, dir.max_digit_size);
            }
            else
            {
                std::cout << "Total Files: " << dir.entries.size() << " (" << dir.num_files << " files, " << dir.num_dirs << " dirs)" << std::endl;
                for (const auto& entry: dir.entries)
                {
                    print_directory_entry(entry, dir.max_digit_size);
                }
            }
        }
        else
        {
            std::cout << "Directory [" << dir.path << "] does not exist!";
        }
        if (multiple_dirs)
        {
            std::cout << std::endl;
        }
    }
    return 0;
}

#include "details.hpp"
#include "utils.hpp"
#include "display.hpp"

#include <sage/argparse/argparse.hpp>
#include <sage/term/colours.hpp>

#include <map>

sage::argparse::argument_parser setup_and_parse_args(int argc, char *argv[])
{
    auto parser = sage::argparse::argument_parser("fs arguments", "");
    parser.add_argument("path")
        .num_args("*")
        .default_value<std::string>(".")
        .help("Path(s) to list.");
    parser.add_argument({"-f", "--filter"}).help("Filter the output based on a string pattern.");
    parser.parse_args(argc, argv);
    return parser;
}

int main(int argc, char *argv[])
{
    auto parser = setup_and_parse_args(argc, argv);
    auto input_paths = parser.get<std::vector<std::string>>("path");

    std::map<std::string, uintmax_t> columns = {
        {"Permissions", 11},
        {"Last Write", 16},
        {"Size", 4},
        {"Name", 4}};

    std::vector<fs::list_details> listed_dirs;

    // Initial pass over each of the supplied input_paths
    for (auto &input_path : input_paths)
    {
        // Initialise result for directory
        fs::list_details result;
        result.path = std::filesystem::path(input_path);

        // Check if input_path exists and if it's a directory
        // Only get directory details if it's actually a directory
        // Deal with file displays in the output pass
        if (std::filesystem::exists(input_path) && std::filesystem::is_directory(input_path))
        {
            // Iterate everything in the specified directory
            for (const auto &entry : std::filesystem::directory_iterator(input_path))
            {
                // Add the entry to the results for display
                // on the next pass
                result.add_entry(entry);

                // Now we need to calculate the column lengths
                auto num_file_size_digits = std::filesystem::is_directory(entry) ? 1 : fs::get_num_digits(entry.file_size());
                if (num_file_size_digits > columns["Size"])
                {
                    columns["Size"] = num_file_size_digits;
                }
                auto num_file_name_chars = entry.path().filename().string().size();
                if (num_file_name_chars > columns["Name"])
                {
                    columns["Name"] = num_file_name_chars;
                }
            }
        }
        listed_dirs.push_back(result);
    }

    // Second pass to Output directories
    for (auto &dir : listed_dirs)
    {
        bool multiple_dirs = listed_dirs.size() > 1;
        if (multiple_dirs)
        {
            fs::output_directory_header(dir.path);
        }

        if (std::filesystem::exists(dir.path))
        {
            if (dir.entries.empty() && !is_directory(dir.path))
            {
                // TODO: Print some file stats - replace print_directory_entry with something else
                std::filesystem::directory_entry entry(dir.path);
                // Now we need to calculate the column lengths - TODO: encapsulate this logic
                auto num_file_size_digits = fs::get_num_digits(entry.file_size());
                if (num_file_size_digits > columns["Size"])
                {
                    columns["Size"] = num_file_size_digits;
                }
                auto num_file_name_chars = entry.path().filename().string().size();
                if (num_file_name_chars > columns["Name"])
                {
                    columns["Name"] = num_file_name_chars;
                }
                fs::print_column_headers(columns);
                fs::print_directory_entry(entry, columns);
            }
            else
            {
                std::cout << "Total Files: " << dir.entries.size() << " (" << dir.num_files << " files, " << dir.num_dirs << " dirs)" << std::endl;
                fs::print_column_headers(columns);
                for (const auto &entry : dir.entries)
                {
                    fs::print_directory_entry(entry, columns);
                }
            }
        }
        else
        {
            std::cout << sage::term::fg::red << "Directory [" << dir.path << "] does not exist!" << sage::term::reset;
        }
        if (multiple_dirs)
        {
            std::cout << std::endl;
        }
    }
    return 0;
}

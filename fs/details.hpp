#pragma once

#include <vector>
#include <filesystem>

namespace fs
{
    struct list_details
    {
        std::filesystem::path path;
        std::vector<std::filesystem::directory_entry> entries;
        uint32_t num_files = 0;
        uint32_t num_dirs = 0;

        void add_entry(std::filesystem::directory_entry entry)
        {
            entries.push_back(entry);

            if (entry.is_directory())
                num_dirs++;
            else
                num_files++;
        }
    };
}

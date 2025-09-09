#pragma once

#include "utils.hpp"

#include <sage/term/colours.hpp>

#include <map>
#include <iostream>
#include <filesystem>
#include <algorithm>

namespace fs
{
    inline void output_path_permissions(const std::filesystem::path &path, bool is_directory)
    {
        auto p = std::filesystem::status(path).permissions();
        std::string dir_marker = is_directory ? "d" : "-";
        if (is_directory)
        {
            std::cout << sage::term::fg::blue;
        }
        std::cout << " " << dir_marker << sage::term::reset;
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

    inline bool is_file_extension_in_list(const std::filesystem::directory_entry &entry, const std::vector<std::string> &valid_extensions)
    {
        return std::find(valid_extensions.begin(), valid_extensions.end(), entry.path().extension()) != valid_extensions.end();
    }

    inline bool is_binary_file(const std::filesystem::directory_entry &entry)
    {
        std::vector<std::string> binary_extensions = {".exe", ".so", ".dll", ".class", ".obj", ".pyc"};
        return is_file_extension_in_list(entry, binary_extensions);
    }

    inline bool is_source_file(const std::filesystem::directory_entry &entry)
    {
        std::vector<std::string> source_extensions = {
            ".cpp", ".c", ".hpp", ".h",
            ".cs",
            ".py",
            ".js", ".java", ".rb", ".pl", ".php",
            ".sh", ".ps1", ".psm1"};
        return is_file_extension_in_list(entry, source_extensions);
    }

    inline bool is_image_file(const std::filesystem::directory_entry &entry)
    {
        std::vector<std::string> image_extensions = {
            ".jpg", ".jpeg", ".png", ".gif",
            ".bmp", ".tiff", ".psd", ".mp4",
            ".mkv", ".avi", ".mov", ".mpg",
            ".vob", ".heic"};
        return is_file_extension_in_list(entry, image_extensions);
    }

    //    Audio: mp3, aac, wav, flac, ogg, mka, wma, ...
    //    Documents: pdf, doc, xls, ppt, docx, odt, ...
    //    Archive: zip, rar, 7z, tar, iso, ...
    //    Database: mdb, accde, frm, sqlite, ...
    //    Web standards: html, xml, css, svg, json, ...
    //    Documents: txt, tex, markdown, asciidoc, rtf, ps, ...
    //    Configuration: ini, cfg, rc, reg, ...
    //    Tabular data: csv, tsv, ...

    inline void print_filename(const std::filesystem::directory_entry &entry, bool is_directory)
    {
        if (is_directory)
        {
            std::cout << sage::term::fg::blue;
        }
        else if (is_binary_file(entry))
        {
            std::cout << sage::term::fg::red;
        }
        else if (is_source_file(entry))
        {
            std::cout << sage::term::fg::green;
        }
        else if (is_image_file(entry))
        {
            std::cout << sage::term::fg::magenta;
        }
        std::wcout << entry.path().filename().c_str();
        std::cout << sage::term::reset;
    }

    inline void print_directory_entry(const std::filesystem::directory_entry &entry, std::map<std::string, uintmax_t> columns)
    {
        bool is_directory = std::filesystem::is_directory(entry.path());
        output_path_permissions(entry.path(), is_directory);

        std::cout << "  " << file_time_to_string(entry.last_write_time()) << "  ";
        // Size in bytes
        const auto file_size = std::filesystem::is_directory(entry) ? 0 : entry.file_size();
        std::cout << std::setw(columns["Size"]) << file_size << "   ";

        print_filename(entry, is_directory);
        std::cout << std::endl;
    }

    inline void print_column_headers(std::map<std::string, uintmax_t> columns)
    {
        std::cout << sage::term::underline << std::setw(columns["Permissions"]) << "Permissions" << sage::term::reset;
        std::cout << "  " << sage::term::underline << std::setw(columns["Last Write"]) << "Last Write" << sage::term::reset;
        std::cout << "  " << sage::term::underline << std::setw(columns["Size"]) << "Size" << sage::term::reset;
        std::cout << "   " << sage::term::underline << "Name" << sage::term::reset;
        std::cout << std::endl;
    }

    inline void output_directory_header(const std::filesystem::path &path)
    {
        std::cout << sage::term::inverse << std::filesystem::absolute(path).string();
        if (path == "." || path == "..")
        {
            std::cout << " (" << path.string() << ")";
        }
        std::cout << ":" << sage::term::reset << std::endl;
    }
}

#ifndef FSPP_FS_DISPLAY_HPP
#define FSPP_FS_DISPLAY_HPP

#include "fs_term.hpp"

#include <map>

namespace fs
{
    void output_path_permissions(const std::filesystem::path& path)
    {
        auto p = std::filesystem::status(path).permissions();
        bool is_directory = std::filesystem::is_directory(path);
        std::string dir_marker = is_directory ? "d" : "-";
        if (is_directory)
        {
            std::cout << tc::fg::blue;
        }
        std::cout << " " << dir_marker << tc::reset;
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

    bool is_file_extension_in_list(const std::filesystem::directory_entry& entry, const std::vector<std::string>& valid_extensions)
    {
        return std::find(valid_extensions.begin(), valid_extensions.end(), entry.path().extension()) != valid_extensions.end();
    }

    bool is_binary_file(const std::filesystem::directory_entry& entry)
    {
        std::vector<std::string> binary_extensions = { ".exe", ".so", ".dll", ".class", ".obj", ".pyc" };
        return is_file_extension_in_list(entry, binary_extensions);
    }

    bool is_source_file(const std::filesystem::directory_entry& entry)
    {
        std::vector<std::string> source_extensions = {
                ".cpp", ".c", ".hpp", ".h",
                ".cs",
                ".py",
                ".js", ".java", ".rb", ".pl", ".php",
                ".sh", ".ps1", ".psm1" };
        return is_file_extension_in_list(entry, source_extensions);
    }

    bool is_image_file(const std::filesystem::directory_entry& entry)
    {
        std::vector<std::string> image_extensions = {
                ".jpg", ".jpeg", ".png", ".gif",
                ".bmp", ".tiff", ".psd", ".mp4",
                ".mkv", ".avi", ".mov", ".mpg",
                ".vob", ".heic" };
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


    void print_filename(const std::filesystem::directory_entry& entry)
    {
        if (std::filesystem::is_directory(entry.path()))
        {
            std::cout << tc::fg::blue;
        }
        else if (is_binary_file(entry))
        {
            std::cout << tc::fg::red;
        }
        else if (is_source_file(entry))
        {
            std::cout << tc::fg::green;
        }
        else if (is_image_file(entry))
        {
            std::cout << tc::fg::magenta;
        }
        std::wcout << entry.path().filename().c_str();
        std::cout << tc::reset;
    }

    void print_directory_entry(const std::filesystem::directory_entry& entry, std::map<std::string, uintmax_t> columns)
    {
        output_path_permissions(entry.path());

        std::cout << "  " << fs::file_time_to_string(entry.last_write_time()) << "  ";
        // Size in bytes
        std::cout << std::setw(columns["Size"]) << entry.file_size() << "   ";

        print_filename(entry);
        std::cout << std::endl;
    }

    void print_column_headers(std::map<std::string, uintmax_t> columns)
    {
        std::cout << tc::underline << std::setw(columns["Permissions"]) << "Permissions" << tc::reset;
        std::cout << "  " << tc::underline << std::setw(columns["Last Write"]) << "Last Write" << tc::reset;
        std::cout << "  " << tc::underline << std::setw(columns["Size"]) << "Size" << tc::reset;
        std::cout << "   " << tc::underline << "Name" << tc::reset;
        std::cout << std::endl;
    }

    void output_directory_header(const std::filesystem::path& path)
    {
        std::cout << fs::tc::inverse << std::filesystem::absolute(path).string();
        if (path == "." || path == "..")
        {
            std::cout << " (" << path.string() << ")";
        }
        std::cout << ":" << fs::tc::reset << std::endl;
    }
}

#endif //FSPP_FS_DISPLAY_HPP

#ifndef FSPP_FS_TERM_HPP
#define FSPP_FS_TERM_HPP

#include <ostream>

namespace fs::tc
{
    inline std::ostream& ansi_code(std::ostream& stream, std::string code)
    {
        stream << "\033[" << code << "m";
        return stream;
    }

    namespace fg
    {
        inline std::ostream& black(std::ostream& stream)
        {
            return ansi_code(stream, "30");
        }

        inline std::ostream& red(std::ostream& stream)
        {
            return ansi_code(stream, "31");
        }

        inline std::ostream& green(std::ostream& stream)
        {
            return ansi_code(stream, "32");
        }

        inline std::ostream& yellow(std::ostream& stream)
        {
            return ansi_code(stream, "33");
        }

        inline std::ostream& blue(std::ostream& stream)
        {
            return ansi_code(stream, "34");
        }

        inline std::ostream& magenta(std::ostream& stream)
        {
            return ansi_code(stream, "35");
        }

        inline std::ostream& cyan(std::ostream& stream)
        {
            return ansi_code(stream, "36");
        }

        inline std::ostream& white(std::ostream& stream)
        {
            return ansi_code(stream, "37");
        }
    }

    namespace bg
    {
        inline std::ostream& black(std::ostream& stream)
        {
            return ansi_code(stream, "40");
        }

        inline std::ostream& red(std::ostream& stream)
        {
            return ansi_code(stream, "41");
        }

        inline std::ostream& green(std::ostream& stream)
        {
            return ansi_code(stream, "42");
        }

        inline std::ostream& yellow(std::ostream& stream)
        {
            return ansi_code(stream, "43");
        }

        inline std::ostream& blue(std::ostream& stream)
        {
            return ansi_code(stream, "44");
        }

        inline std::ostream& magenta(std::ostream& stream)
        {
            return ansi_code(stream, "45");
        }

        inline std::ostream& cyan(std::ostream& stream)
        {
            return ansi_code(stream, "46");
        }

        inline std::ostream& white(std::ostream& stream)
        {
            return ansi_code(stream, "47");
        }
    }

    inline std::ostream& reset(std::ostream& stream)
    {
        return ansi_code(stream, "0");
    }

    inline std::ostream& bold(std::ostream& stream)
    {
        return ansi_code(stream, "1");
    }

    inline std::ostream& underline(std::ostream& stream)
    {
        return ansi_code(stream, "4");
    }

    inline std::ostream& inverse(std::ostream& stream)
    {
        return ansi_code(stream, "7");
    }
}

// See a full list of ANSI codes here - https://en.wikipedia.org/wiki/ANSI_escape_code
//    bold/bright off  21
//    underline off    24
//    inverse off      27


#endif //FSPP_FS_TERM_HPP

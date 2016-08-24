#pragma once

#include <iostream>
#include <string>
#include <cstdlib>
#include <syslog.h>

namespace Color {

    namespace Text {
        static const std::string Black="[30m";
        static const std::string Red="[31m";
        static const std::string Green="[32m";
        static const std::string Yellow="[33m";
        static const std::string Blue="[34m";
        static const std::string Magenta="[35m";
        static const std::string Cyan="[36m";
        static const std::string LightGray="[37m";
        static const std::string Default="[39m";
        static const std::string DarkGray="[90m";
        static const std::string LightRed="[91m";
        static const std::string LightGreen="[92m";
        static const std::string LightYellow="[93m";
        static const std::string LightBlue="[94m";
        static const std::string LightMagenta="[95m";
        static const std::string LightCyan="[96m";
        static const std::string White="[97m";
        static const std::string Reset="[0m";
    }

    namespace Background {
        static const std::string Black="[40m";
        static const std::string Red="[41m";
        static const std::string Green="[42m";
        static const std::string Yellow="[43m";
        static const std::string Blue="[44m";
        static const std::string Magenta="[45m";
        static const std::string Cyan="[46m";
        static const std::string LightGray="[47m";
        static const std::string Default="[49m";
        static const std::string DarkGray="[100m";
        static const std::string LightRed="[101m";
        static const std::string LightGreen="[102m";
        static const std::string LightYellow="[103m";
        static const std::string LightBlue="[104m";
        static const std::string LightMagenta="[105m";
        static const std::string LightCyan="[106m";
        static const std::string White="[107m";
        static const std::string Reset="[0m";
    }
}

namespace Effect {
    static const std::string Bright="[1m";
    static const std::string Dim="[2m";
    static const std::string Italic="[3m";
    static const std::string Underline="[4m";
    static const std::string Blink="[5m";
    static const std::string Reverse="[7m";
    static const std::string Hidden="[8m";
    static const std::string StrikeThrough="[9m";

    static const std::string BrightReset="[21m";
    static const std::string DimReset="[22m";
    static const std::string ItalicReset="[23m";
    static const std::string UnderlineReset="[24m";
    static const std::string BlinkReset="[25m";
    static const std::string ReverseReset="[27m";
    static const std::string HiddenReset="[28m";
    static const std::string StrikeThroughReset="[29m";

    static const std::string Reset="[0m";
}

    // class Log {
    //
    //     private:
    //         Log() {}
    //
    //     public:
    //         static void write(Log::Type type, Log::Destination dst, std::string message);
    //
    // };

namespace Log {

    enum class Type { success, info, error, warning };
    enum class Destination { stdout, stderr, syslog };


    class Error: public std::invalid_argument {
        public:
            Error() : std::invalid_argument("") {
            }
    
    };

    class TypeError: public Error {};

    class DestinationError: public Error {};
    void someTest();
    void log(Type type, Destination dst, std::string message);

}

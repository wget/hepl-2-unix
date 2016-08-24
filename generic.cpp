#include "generic.h"

using namespace std;

void Log::log(Type type, Destination dst, std::string message) {

    try {

        if (dst == Log::Destination::syslog) {

            switch(type) {
                case Log::Type::success:
                    syslog(LOG_DEBUG, message.c_str());
                    break;
                case Log::Type::info:
                    syslog(LOG_INFO, message.c_str());
                    break;
                case Log::Type::error:
                    syslog(LOG_ERR, message.c_str());
                    break;
                case Log::Type::warning:
                    syslog(LOG_NOTICE, message.c_str());
                    break;
                default:
                    throw Log::TypeError();
            }
            return;
        }

        string messagePrinted;

        switch(type){
            case Log::Type::success:
                // The bright effect cannot be combined with another color. The
                // color will be removed if bright is used.
                messagePrinted = "["
                    + Color::Text::Green + "+"
                    + Color::Text::Reset + "] "
                    + message;
                break;
            case Log::Type::info:
                messagePrinted = "["
                    + Color::Text::Blue + "-"
                    + Color::Text::Reset + "] "
                    + message;
                break;
            case Log::Type::error:
                messagePrinted = "["
                    + Color::Text::Red + "x"
                    + Color::Text::Reset + "] "
                    + message;
                break;
            case Log::Type::warning:
                messagePrinted = "["
                    + Color::Text::Yellow + "!"
                    + Color::Text::Reset + "] "
                    + message;
                break;
            default:
                throw Log::TypeError();
        }

        if (dst == Log::Destination::stdout) {
            cout << messagePrinted << endl;
        } else if (dst == Log::Destination::stderr) {
            cerr << messagePrinted << endl;
        } else {
            throw Log::DestinationError();
        }

    } catch (Log::TypeError) {
        cout << "Log type incorrect. Aborted." << endl;
        return;
    } catch (Log::DestinationError) {
        cout << "Log destination incorrect. Aborted." << endl;
        return;
    } catch (Log::Error) {
        cout << "Log error occurred. Aborted." << endl;
        return;
    }
}


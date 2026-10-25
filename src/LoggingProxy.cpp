#include "LoggingProxy.h"

void LoggingProxy::log(const std::string& source,

                       const std::string& operation,

                       const std::string& result,

                       std::ostream& output) noexcept {

    try {

        output << '[' << source << "] " << operation << ": " << result << '\n';

    } catch (...) {

    }

}

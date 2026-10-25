#pragma once

#include <iostream>
#include <string>

class LoggingProxy {
public:
    static void log(const std::string& source,
                    const std::string& operation,
                    const std::string& result,
                    std::ostream& output = std::cout) noexcept;
};

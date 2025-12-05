#include <iostream>
#include <boost/stacktrace.hpp>

#include "day4/Day4.h"

int main() {
    try {
        day4::run();
    } catch (const std::exception& e) {
        const boost::stacktrace::stacktrace trace = boost::stacktrace::stacktrace::from_current_exception();
        std::cerr << "Caught exception: " << e.what() << "\n" << trace;
    }
}

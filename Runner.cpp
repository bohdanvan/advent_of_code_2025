#include <iostream>
#include <boost/stacktrace.hpp>

#include "day5/Day5.h"

int main() {
    try {
        day5::run();
    } catch (const std::exception& e) {
        const boost::stacktrace::stacktrace trace = boost::stacktrace::stacktrace::from_current_exception();
        std::cerr << "Caught exception: " << e.what() << "\n" << trace;
    }
}

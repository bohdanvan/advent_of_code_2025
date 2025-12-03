#include "day3/Day3.h"
#include <iostream>
#include <boost/stacktrace.hpp>

int main() {
    try {
        day3::run();
    } catch (const std::exception& e) {
        const boost::stacktrace::stacktrace trace = boost::stacktrace::stacktrace::from_current_exception();
        std::cerr << "Caught exception: " << e.what() << "\n" << trace;
    }
}

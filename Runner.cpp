#include "day2/Day2.h"
#include <iostream>
#include <boost/stacktrace.hpp>

int main() {
    try {
        day2::run();
    } catch (const std::exception& e) {
        const boost::stacktrace::stacktrace trace = boost::stacktrace::stacktrace::from_current_exception();
        std::cerr << "Caught exception: " << e.what() << "\n" << trace;
    }
}

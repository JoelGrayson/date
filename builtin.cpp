// Here is how to use C++'s built-in version of date

#include <iostream>
#include <ctime>
#include <chrono>

typedef std::chrono::system_clock Clock;

int main() {
    auto now=Clock::now();
    std::time_t now_c=Clock::to_time_t(now);
    struct std::tm *parts=std::localtime(&now_c);
    std::cout << "The current year is " << parts->tm_year+1900 << '\n';
    std::cout << "The current month is " << parts->tm_mon+1 << std::endl;
}


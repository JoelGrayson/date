#include "date.h"

int main() {
    Date d;
    std::cout << "It is " << d << " UTC" << std::endl;
    d.setUTCOffset(-8);
    std::cout << "It is " << d << " at Stanford" << std::endl;
    d.setUTCOffset(-5);
    std::cout << "It is " << d << " in New York" << std::endl;
    d.setUTCOffset(+8);
    std::cout << "It is " << d << " in Shanghai" << std::endl;
}


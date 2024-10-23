#include <random>
#include <iostream>
#include <sstream>

#include <boost/format.hpp>

std::string generateRandomLispExp() {
    return "";
}

[[noreturn]] int main() {
    std::cerr << "=== Lisp Parser Fuzzer ====" << std::endl;
    std::cerr << "Running in endless mode. Press CTRL + C to abort" << std::endl;
    std::cerr << std::endl << std::endl;

    std::random_device rd; // obtain a random number from hardware
    std::mt19937 gen(rd()); // seed the generator
//    std::uniform_int_distribution<> distrOperand(INT_MIN/4, INT_MAX/4);//
    std::uniform_int_distribution<> distrOperand(-20000, 20000);//
    std::uniform_int_distribution<> distrOperation(1, 3);



    while (true) {
        int op1 = distrOperand(gen);
        int op2 = distrOperand(gen);
        std::string op;
        switch (distrOperation(gen)) {
            case 1:
                op = "+";
            break;
            case 2:
                op = "-";
            break;
            case 3:
                op = "*";
            break;
            default:
                op = " "; // will cause an error later on during parsing
        }
        std::ostringstream expString;
        expString << boost::format("(simplify (%1% %2% %3%))") % op % op1 % op2;
        std::cerr << "\rTesting: " << expString.str() << std::flush;
        std::cout << expString.str() << std::endl;
    }
}

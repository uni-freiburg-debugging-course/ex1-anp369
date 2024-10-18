//
// Created by andi on 18.10.24.
//
#include <iostream>
#include <boost/program_options.hpp>
#include <boost/optional.hpp>

namespace po = boost::program_options;

void print_help() {
    std::cout << "lisp parser - Andreas Philipp\n";
    std::cout << "Usage: \n"
            "--help to display this help text\n"
            "--log to switch on debug logging for the lexer and parser\n"
            "--file the path to the file to load the expressions from\n"
            "If no file is specified the program will read data from stdint";

    std::cout << std::endl;
}

int main(int argc, char **argv) {


    po::options_description desc("Allowed options");
    boost::optional<bool> loggingEnabled;
    desc.add_options()
            ("help", "produce help message")
            ("logging",po::value(&loggingEnabled), "define which parts should be logged")
            ("file", po::value<std::string>(), "specify the file to read from, use stdint otherwise");

    po::variables_map vm;
    po::store(po::parse_command_line(argc, argv, desc), vm);
    po::notify(vm);

    if (vm.count("help")) {
        print_help();
        return 1;
    }

    bool logging = vm.count("logging");

    std::string file_name = "";
    if (vm.count("file")) {
        file_name = vm["file"].as<std::string>();
    }

}

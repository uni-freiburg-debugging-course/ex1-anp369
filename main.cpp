//
// Created by andi on 18.10.24.
//
#include <fstream>
#include <iostream>
#include <memory>

#include <boost/program_options.hpp>

#include <parser.h>

namespace po = boost::program_options;

constexpr const char *stdin_path = "/dev/stdin";

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
    bool loggingEnabled;
    desc.add_options()
            ("help", "produce help message")
            ("logging", po::bool_switch(&loggingEnabled), "define which parts should be logged")
            ("file", po::value<std::string>(), "specify the file to read from, use stdint otherwise");

    po::variables_map vm;
    po::store(po::parse_command_line(argc, argv, desc), vm);
    po::notify(vm);

    if (vm.count("help")) {
        print_help();
        return 1;
    }

    bool logging = vm.count("logging");

    Parser p(logging);

    std::string fileName = "";
    if (vm.count("file")) fileName = vm["file"].as<std::string>();

    std::ifstream file;
    if (!fileName.empty()) {
        file = std::ifstream(fileName);
        if (!file.is_open()) {
            std::cerr << "Could not open file " << fileName << std::endl;
            exit(EXIT_FAILURE);
        }
    } else {
        file = std::ifstream(stdin_path);
    }

    std::string line;
    while (std::getline(file, line)) {
        if (line.empty()) { continue;}
        p.parse(line);
    }
    file.close();

    return 0;
}

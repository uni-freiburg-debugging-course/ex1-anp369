[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-22041afd0340ce965d47ae6ef1cefeee28c7c493a6346c4f15d667ab976d596c.svg)](https://classroom.github.com/a/3MmVbb7f)
# Debugging 24/25 Exercise 1

Detailed instructions are in the exercise sheet. Following are your checkpoints:

- [X] Implement parser and evaluator
- [ ] Implement a fuzzer
- [ ] Generate *lots* of random instances with your fuzzer. Your evaluator and z3 must return the same result on generated instances
- [X] Provide detailed build instructions for your code so that we can evaluate it


## Build instructions
The build is done with the following versions on my system:
* `GCC 14.2.1`
* `cmake 3.30.5`
* `C++14`
* `GNU make 4.4.1`

The used libraries have the following versions:
* `boost 1.86.0-3`
* `gtest 1.15.2-1`

1. Make sure you have the following tools installed: `cmake`, `make`, an cpp compiler supporting at least C++14
2. Install the following required libraries: `boost` and `gtest`
3. create a build directory: `mkdir build && cd build`
4. generate makefiles: `cmake ..`
5. build the program: `make`
6. run the executable under `lisp_parser` in the build dir
7. The fuzzer is in the `lisp_fuzzer` binary
8. Run the test suite with `lisp_parser_test`.

PS: thanks for looking into the code, I did my best, but my C++ is a bit rusty,
so some things may not be best practice at all :D
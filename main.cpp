/*
Path Hijacking
Author: c0d3Ninja
Version: 1.0
Date: 2025-10-27

This tool is used to check for path hijacking vulnerabilities in the system.
It will check for writable directories in the PATH environment variable and then check for writable files in those directories.
It will then check the ownership of the files and print the results.

Usage:
./pathhijack

 */


#include <iostream>
#include "pathhijacking.h"
#include "modules/fileownership.h"
#include <vector>
#include <string>
#include <vector>

#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN    "\033[36m"
#define WHITE   "\033[37m"
#define BOLD    "\033[1m"
#define UNDERLINE "\033[4m"

int main() {
    std::vector<std::string> writabledirs = checkPATHS();
    std::vector<std::string> pathResults = pathhijack(writabledirs);
    std::cout << ":::Possible Path Hijacks Found" << "(" << YELLOW << pathResults.size() << RESET << ")" << ":::" << "\n";
    for (const auto& r : pathResults) {
        std::vector<std::string> ownership = checkFileOwnership(r);
        for (const auto& fileOwner : ownership) {
            std::cout << YELLOW << fileOwner << RESET << "\n";
        }
    }
    return 0;
}

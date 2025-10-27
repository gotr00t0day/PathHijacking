#include <cstdlib>
#include <iostream>
#include <filesystem>
#include <unistd.h>
#include <sys/stat.h>
#include <sstream>
#include <pwd.h>
#include <algorithm>
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

std::vector<std::string> prioritize(const std::vector<std::string>& directories) {
    std::vector<std::string> systemDir = {"/usr/bin", "/usr/local/bin", "/bin", "/sbin/",
        "/usr/local/sbin"
    };
    std::vector<std::string> foundDir;
    for (const auto& fd : systemDir) {
        if (std::filesystem::exists(fd)) {
            foundDir.emplace_back(fd);
        } else {
            continue;
        }
    }
    std::vector<std::string> foundItems;
    for (const auto& dir : directories) {
        auto it = std::find(foundDir.begin(), foundDir.end(), dir);
        if (it != foundDir.end()) {
            std::vector<std::string> before(directories.begin(), std::find(directories.begin(), directories.end(), dir));
            for (const auto& item : before) {
                if(std::find(foundDir.begin(), foundDir.end(), item) == foundDir.end()){
                    foundItems.emplace_back(item);
                }
            }
        }
    }
    return foundItems;
}


std::vector<std::string> checkPATHS() {
    const char* pathEnv = std::getenv("PATH");
    if (!pathEnv) {
        std::cerr << "PATH not set\n";
        return {};
    }
    std::string pathStr(pathEnv);
    std::stringstream ss(pathStr);
    std::string dir;
    std::vector<std::string> dirs;
    std::vector<std::string> writable_dir;
    std::vector<std::string> writable_files;

    while (std::getline(ss, dir, ':')) {
        if (dir.empty() || !std::filesystem::exists(dir)) continue;
        dirs.emplace_back(dir);
        struct stat st;
        if (stat(dir.c_str(), &st) == 0) {
            writable_dir.emplace_back(dir.c_str());
            //std::cout << "  Writable: " << (access(dir.c_str(), W_OK) == 0 ? "YES" : "NO") << "\n";
        }

    }
    for (const auto& w_dir : writable_dir) {
        for (const auto& entry : std::filesystem::recursive_directory_iterator(w_dir, std::filesystem::directory_options::skip_permission_denied)) {
            try {
                if(!entry.is_regular_file()) continue;
                std::string path = entry.path().string();
                std::string filename = entry.path().filename().string();
                struct stat sta;
                if (stat(path.c_str(), &sta) == 0) {
                    writable_files.emplace_back(path.c_str());
                    //std::cout << "  Writable Files: " << path.c_str() << "\n";
                }
            } catch (const std::filesystem::filesystem_error& e) {
                continue;
            }
        }
    }
    /*
    std::vector<std::string> dirsList = dirs;
    std::vector<std::string> prioritize_dirs = prioritize(writable_dir);
    std::cout << "Prioritized Directories: " << YELLOW << prioritize_dirs.size() << RESET << "\n";
    std::cout << "Writable files: " << YELLOW << writable_files.size() << RESET << "\n";
    std::cout << "Writable Dirs: " << YELLOW << writable_dir.size() << RESET << "\n\n";

    std::cout << ":::Directories in Path " << "(" << YELLOW << dirsList.size() << RESET << ")" << ":::" "\n";
    for (const auto& dl : dirsList) {
        std::cout << YELLOW << dl << RESET << "\n";
    }
    std::cout << "\n";

    std::cout << ":::Prioritized Directories:::" << "(" << YELLOW << prioritize_dirs.size() << RESET << ")" << ":::" "\n";
    for (const auto& prd : prioritize_dirs) {
        std::cout << YELLOW << prd << RESET << "\n";
    }
    */
    return writable_dir;
}



std::vector<std::string> pathhijack(const std::vector<std::string>& directories){
    std::vector<std::string> targetCommands = {"ls", "ps", "cat", "grep", "find", "wget", "curl", "sudo", "su", 
        "cp", "mv", "rm", "ln", "chmod", "chown", "chgrp", "touch", "mkdir", "rmdir", "ln", "chmod", "chown", "chgrp", "touch", "mkdir", "rmdir"
    };
    std::vector<std::string> possibleHijack;
    for (const auto& dirs : directories) {
        for (const auto& tc : targetCommands) {
            std::string checkPath = dirs + "/" + tc;
            if (std::filesystem::exists(checkPath)) {
                possibleHijack.emplace_back(checkPath);
            }
        }
    }
    return possibleHijack;
}
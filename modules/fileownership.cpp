#include <iostream>
#include <sys/stat.h>
#include <unistd.h>
#include <pwd.h>
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

std::vector<std::string> checkFileOwnership(const std::string& filepath) {
    struct stat fileInfo;
    std::vector<std::string> owner;
    
    if (stat(filepath.c_str(), &fileInfo) == 0) {
        uid_t owner_uid = fileInfo.st_uid;
        // gid_t owner_gid = fileInfo.st_gid; // Unused for now

        struct passwd *pw = getpwuid(owner_uid);
        std::string owner_name = pw ? pw->pw_name : "unknown";
        
        /*
        bool user_writable = (fileInfo.st_mode & S_IWUSR);
        bool group_writable = (fileInfo.st_mode & S_IWGRP);
        bool other_writable = (fileInfo.st_mode & S_IWOTH);
        */

        std::string fileInfo = filepath + " " + GREEN + owner_name;
        owner.emplace_back(fileInfo);
    }
    return owner;
}
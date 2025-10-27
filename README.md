# Path Hijacking Vulnerability Scanner

A security tool designed to detect potential PATH hijacking vulnerabilities on Unix-like systems. This tool scans your system's PATH environment variable for writable directories and identifies potential security risks where malicious actors could inject executable files.

## Overview

PATH hijacking is a privilege escalation technique where an attacker places a malicious executable in a directory that appears in the system's PATH environment variable. If that directory is writable and has higher precedence than legitimate system directories, the malicious executable may be executed instead of the intended system command.

This tool helps identify such vulnerabilities by:
1. Scanning all directories in your PATH environment variable
2. Checking write permissions on each directory
3. Identifying executables in writable directories
4. Displaying file ownership information

## Features

- ✅ Scans PATH environment variable for writable directories
- ✅ Identifies potential hijackable executables
- ✅ Shows file ownership information
- ✅ Color-coded terminal output for easy reading
- ✅ Fast and lightweight C++ implementation

## Requirements

- **Operating System:** macOS, Linux, or other Unix-like systems
- **Compiler:** g++ or clang++ with C++17 support
- **Build Tool:** GNU Make

## Installation

### Build from Source

```bash
# Clone or download the repository
cd pathijack

# Build the project
make

# The executable will be created at bin/pathhijack
```

### System-wide Installation (Optional)

```bash
# Install to /usr/local/bin (requires sudo)
sudo make install

# Uninstall
sudo make uninstall
```

## Usage

### Basic Usage

```bash
# Run from build directory
./bin/pathhijack

# Or if installed system-wide
pathhijack
```

### Example Output

```
:::Possible Path Hijacks Found (3):::
/usr/local/bin/suspicious_script username
/opt/custom/bin/test_binary username
/home/user/.local/bin/malicious_tool username
```

The tool will display:
- The full path to potentially hijackable files
- The owner of each file (in green)
- Total count of potential hijacks found (in yellow)

## Build Targets

The Makefile provides several useful targets:

```bash
make              # Build the project (default)
make clean        # Remove build artifacts
make run          # Build and run the tool
make install      # Install to /usr/local/bin (requires sudo)
make uninstall    # Remove from /usr/local/bin
make debug        # Build with extra debug symbols
make release      # Build optimized release version
make help         # Show all available targets
```

## Project Structure

```
pathijack/
├── main.cpp                    # Main entry point
├── pathhijacking.cpp          # Core path hijacking detection logic
├── pathhijacking.h            # Header for path hijacking functions
├── modules/
│   ├── fileownership.cpp      # File ownership checking module
│   └── fileownership.h        # File ownership header
├── Makefile                   # Build configuration
├── README.md                  # This file
├── bin/                       # Compiled executable (generated)
└── obj/                       # Object files (generated)
```

## How It Works

1. **PATH Analysis:** The tool reads and parses the PATH environment variable
2. **Permission Check:** Each directory in PATH is checked for write permissions
3. **File Discovery:** Scans writable directories for executable files
4. **Ownership Verification:** Retrieves and displays file ownership information
5. **Report Generation:** Outputs findings in a color-coded, easy-to-read format

## Security Implications

Writable directories in your PATH can pose serious security risks:

- **Privilege Escalation:** Attackers can place malicious executables with names of common system commands
- **Command Hijacking:** User commands may execute attacker-controlled code instead of legitimate binaries
- **Persistence:** Malicious code can persist across reboots if placed in PATH directories

### Recommendations

If this tool finds vulnerabilities:

1. **Review PATH:** Examine your PATH for unnecessary writable directories
2. **Fix Permissions:** Remove write permissions from PATH directories where possible
3. **Reorder PATH:** Place system directories (like `/usr/bin`, `/bin`) before user directories
4. **Audit Files:** Investigate any suspicious files found in writable PATH directories
5. **Monitor Changes:** Regularly run this tool to detect new vulnerabilities

## Technical Details

- **Language:** C++17
- **Compiler Flags:** `-std=c++17 -Wall -Wextra -O2 -g`
- **Dependencies:** Standard C++ library, POSIX system calls
- **Platform:** Unix-like systems (macOS, Linux, BSD)

## Development

### Building for Development

```bash
# Debug build with extra symbols
make debug

# Release build with optimizations
make release
```

### Code Structure

- `checkPATHS()` - Parses PATH and identifies writable directories
- `pathhijack()` - Scans directories for potential hijack targets
- `checkFileOwnership()` - Retrieves file ownership information
- `prioritize()` - Utility for directory prioritization

## Limitations

- Currently focused on Unix-like systems (not Windows-compatible)
- Requires read access to directories in PATH
- Does not automatically fix vulnerabilities (detection only)
- May not detect all sophisticated attack vectors

## Contributing

Feel free to submit issues, feature requests, or pull requests to improve this tool.

## License

This tool is provided for educational and security research purposes.

## Disclaimer

This tool is intended for legitimate security auditing purposes only. Users are responsible for ensuring they have proper authorization before running security scans on any system. The author assumes no liability for misuse or damage caused by this tool.

## Contact

**Author:** c0d3Ninja  
**Project:** Path Hijacking Vulnerability Scanner

---

**Stay secure! 🔒**


# Path Hijacking Vulnerability Scanner

A security tool designed to detect potential PATH hijacking vulnerabilities on Unix-like systems. This tool scans your system's PATH environment variable for writable directories and identifies potential security risks where malicious actors could inject executable files.

## Overview

PATH hijacking is a privilege escalation technique where an attacker places a malicious executable in a directory that appears in the system's PATH environment variable. If that directory is writable and has higher precedence than legitimate system directories, the malicious executable may be executed instead of the intended system command.

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

```bash
# Debug build with extra symbols
make debug

# Release build with optimizations
make release
```


# Path Hijacking Tool Makefile
# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -O2 -g
LDFLAGS = 

# Directories
SRCDIR = .
MODULEDIR = modules
OBJDIR = obj
BINDIR = bin

# Source files
MAIN_SOURCES = main.cpp pathhijacking.cpp
MODULE_SOURCES = $(wildcard $(MODULEDIR)/*.cpp)

# Object files
MAIN_OBJECTS = $(MAIN_SOURCES:%.cpp=$(OBJDIR)/%.o)
MODULE_OBJECTS = $(MODULE_SOURCES:$(MODULEDIR)/%.cpp=$(OBJDIR)/$(MODULEDIR)/%.o)
OBJECTS = $(MAIN_OBJECTS) $(MODULE_OBJECTS)

# Target executable
TARGET = $(BINDIR)/pathhijack

# Default target
all: directories $(TARGET)

# Create all necessary directories
directories:
	@mkdir -p $(OBJDIR) $(OBJDIR)/$(MODULEDIR) $(BINDIR)

$(OBJDIR):
	mkdir -p $(OBJDIR)

$(OBJDIR)/$(MODULEDIR):
	mkdir -p $(OBJDIR)/$(MODULEDIR)

$(BINDIR):
	mkdir -p $(BINDIR)

# Compile main directory source files
$(OBJDIR)/%.o: $(SRCDIR)/%.cpp | $(OBJDIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Compile module directory source files
$(OBJDIR)/$(MODULEDIR)/%.o: $(MODULEDIR)/%.cpp | $(OBJDIR) $(OBJDIR)/$(MODULEDIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Link object files to create executable
$(TARGET): $(OBJECTS) | $(BINDIR)
	$(CXX) $(OBJECTS) -o $@ $(LDFLAGS)

# Clean build artifacts
clean:
	rm -rf $(OBJDIR) $(BINDIR)

# Install the tool (requires sudo)
install: $(TARGET)
	sudo cp $(TARGET) /usr/local/bin/
	sudo chmod +x /usr/local/bin/pathhijack
	@echo "Path hijacking tool installed to /usr/local/bin/"

# Uninstall the tool
uninstall:
	sudo rm -f /usr/local/bin/pathhijack
	@echo "Path hijacking tool uninstalled"

# Run the tool
run: $(TARGET)
	./$(TARGET)

# Debug build
debug: CXXFLAGS += -DDEBUG -g3
debug: clean $(TARGET)

# Release build
release: CXXFLAGS += -DNDEBUG -O3
release: clean $(TARGET)

# Show help
help:
	@echo "Available targets:"
	@echo "  all      - Build the path hijacking tool (default)"
	@echo "  clean    - Remove build artifacts"
	@echo "  install  - Install tool to /usr/local/bin/ (requires sudo)"
	@echo "  uninstall- Remove tool from /usr/local/bin/"
	@echo "  run      - Build and run the tool"
	@echo "  debug    - Build with debug symbols"
	@echo "  release  - Build optimized release version"
	@echo "  help     - Show this help message"

# Phony targets
.PHONY: all directories clean install uninstall run debug release help

# Dependencies
$(OBJDIR)/main.o: main.cpp pathhijacking.h $(MODULEDIR)/fileownership.h
$(OBJDIR)/pathhijacking.o: pathhijacking.cpp pathhijacking.h
$(OBJDIR)/$(MODULEDIR)/fileownership.o: $(MODULEDIR)/fileownership.cpp $(MODULEDIR)/fileownership.h


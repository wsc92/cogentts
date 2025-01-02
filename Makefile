# Compiler and flags
CXX := g++
CXXFLAGS := -std=c++17 -Wall -Wextra -O2 -I src -I src/core

# Linker flags for libraries
LDFLAGS := -L/path/to/pqxx/lib -lpqxx -lpq -L/path/to/questdb-ingress/lib -lquestdb-ingress

# Directories
SRCDIR := src
OBJDIR := obj
BINDIR := bin

# Source files
SRCS := $(wildcard $(SRCDIR)/**/*.cpp) $(wildcard $(SRCDIR)/*.cpp)
OBJS := $(patsubst $(SRCDIR)/%.cpp, $(OBJDIR)/%.o, $(SRCS))

# Output binary
TARGET := $(BINDIR)/app

# Default target
.PHONY: all
all: $(TARGET)

# Link the final binary
$(TARGET): $(OBJS)
	@mkdir -p $(BINDIR)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

# Compile source files to object files
$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean up build artifacts
.PHONY: clean
clean:
	$(RM) -r $(OBJDIR) $(BINDIR)

# Debug target to print variables (optional)
.PHONY: debug
debug:
	@echo "Source Files: $(SRCS)"
	@echo "Object Files: $(OBJS)"


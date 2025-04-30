# This is a makefile for compiling your whole project.
# It is used to compile all the source files in the src directory and link them together.
# It is also used to clean up the build directory and remove all the object files and the executable.
# The makefile is used to compile the project using the gcc compiler.

# Things to explore:
# - Linux, MacOS, WSL for Windows
# - Makefile variables
# - Makefile rules
# - Makefile targets
# - Makefile dependencies
# - Makefile commands

# ---------------------- Example makefile for a C project ----------------------

# This is variable that specifies the compiler to use.
CC = gcc
# This is variable that specifies the compiler flags to use.
CFLAGS = -g -Wall
# This is variable that specifies the source files to compile.
SRCS = $(wildcard *.c)
# This is variable that specifies the object files to create.
OBJS = $(SRCS:.c=.o)
# This is variable that specifies the name of the executable file.
TARGET = main
# This is variable that specifies target compile directory.
TARGET_DIR = build


# TODO: Explore best practices for makefiles
# HINT: Do step by step compilation and linking (e.g. compile all .c files to .o files, then link them together to create the executable)
# HINT: Specify output directory for object files and executable (e.g. build/) and ignore the build directory in the git repository


# This is default target that is used to compile the project.
main: main.c
	@echo "Compiling the project..."
	@echo "Compiling source files..."
	@$(MAKE) compile
	@echo "Linking object files..."
	@$(MAKE) link
	@echo "Build complete."

# This target is used to compile all the source files in the src directory.
# The -g option is used to generate debug information.
# The -Wall option is used to enable all compiler warnings.
# The -c option is used to compile the source files without linking them.
# *.c: compile all C source files in the current directory
compile:
	mkdir -p build
	$(CC) $(CFLAGS) -c $(SRCS) -o $(TARGET_DIR)/$(OBJS)


# This target is used to link the object files and create the executable.
# The -o option specifies the output file name.
link:
	$(CC) $(CFLAGS) -o $(TARGET) $(TARGET_DIR)/$(OBJS)

# This target is used to compile all the source files in the src directory and link them together.
clean:
	rm -rf build
	rm -f $(TARGET)
	rm -f *.o
	rm -f *.out
	rm -f *.exe
	rm -f *.a
	rm -f *.so
	rm -f *.dll
	rm -f *.dSYM
	rm -f *.pdb
	rm -f *.ilk
	rm -f *.idb
	rm -f *.lib
	rm -f *.exp

# Path and name
NAME = complex

PROJECT_PATH=../..

# The compiler : g++ for C++ program
CC = g++

# Compiler flags :
CPPFLAGS = -std=c++98 -Werror -pedantic-errors -Wall -Wextra -Wconversion -Wuninitialized -Wshadow -Wfloat-equal -Wformat -Wcast-align

# Valgrind
VALGRIND = valgrind --leak-check=full --show-leak-kinds=all --show-reachable=yes --track-origins=yes --error-limit=no

# Debug
DEBUG = gdb -tui -ex "layout src" -ex "set disassembly-flavor intel" -fullname

#Remove
RM = rm -rf

# Archive
AR = ar -rcs

# Source file
SRC = $(NAME).cpp

# Source object file
O_SRC = $(PROJECT_PATH)/bin/objects/$(NAME).o

# Header file
HEADER = $(NAME).hpp


# Main file
MAIN = $(NAME)_test.cpp

# Main file
O_MAIN = $(PROJECT_PATH)/bin/objects/$(NAME)_test.o

# The build target executable
TARGET = $(PROJECT_PATH)/bin/executables/$(NAME)

# Static Lib names
S_LIB = $(PROJECT_PATH)/bin/static_libs/lib$(NAME).a

# Shared Lib names
SO_NAME = $(PROJECT_PATH)/bin/shared_libs/lib$(NAME).so

# Shared lib path
PATH_TO_SO = -L$(PROJECT_PATH)/bin/shared_libs

# Static lib path
PATH_TO_S = -L$(PROJECT_PATH)/bin/static_libs

# Files of the project
C_FILES = $(MAIN) $(SRC)

# Files of the project
O_FILES = $(O_MAIN) $(O_SRC)

# List of all headers
HEADERS = $(HEADER)

.PHONY : run leak nm release debug lib.a lib.so link_shared link_static clean

#******************************************************************************

$(TARGET) : $(O_FILES) $(HEADERS)
	clear
	$(CC) $(CPPFLAGS) $(O_FILES) -o $(TARGET)

#******************************************************************************

$(O_MAIN) : $(MAIN) $(HEADER)
	clear
	$(CC) $(CPPFLAGS) -c $(MAIN) -o $(O_MAIN)

$(O_SRC) : $(SRC) $(HEADER)
	clear
	$(CC) $(CPPFLAGS) -c $(SRC) -o $(O_SRC)

#******************************************************************************

run : $(TARGET)
	$(TARGET)

#******************************************************************************

nm : $(TARGET)
	nm $(TARGET)

#******************************************************************************

vlg : CPPFLAGS += -DDEBUG_ON -g
vlg : clean $(TARGET)
	clear
	$(VALGRIND) $(TARGET)

#******************************************************************************

static : lib.a $(O_FILES)
	$(CC) $(CPPFLAGS) $(MAIN) $(PATH_TO_S) -l$(NAME) -o $(TARGET)

#******************************************************************************

lib.a : clean $(O_FILES)
	$(AR) $(S_LIB) $(O_SRC)
	ranlib $(S_LIB)

#******************************************************************************

shared : lib.so
	$(CC) $(PATH_TO_SO) -Wl,-rpath=$(dir $(SO_NAME)) -Wall $(MAIN) -l$(NAME) -o $(TARGET)
	clear

#******************************************************************************

lib.so : CPPFLAGS += -fPIC -c
lib.so : clean $(O_FILES)
	$(RM) $(TARGET) $(O_SRC)
	$(CC) $(CPPFLAGS) -c $(SRC) -o $(O_SRC)
	$(CC) -shared -o $(SO_NAME) $(O_SRC)
	clear

#******************************************************************************

debug : CPPFLAGS += -DDEBUG_ON -g
debug : clean $(TARGET)
	$(CC) $(CPPFLAGS) $(C_FILES) -o $(TARGET)
	$(DEBUG) $(TARGET)
	clear

#******************************************************************************

release : CPPFLAGS += -DNDEBUG -O
release : clean $(TARGET)
	$(CC) $(CPPFLAGS) $(C_FILES) -o $(TARGET)
	clear

#******************************************************************************

clean :
	clear
	$(RM) $(TARGET) $(O_FILES) $(SO_NAME) $(S_LIB)


#******************************************************************************

# When including: put the $(EXTERNAL_O_SRC) $(EXTERNAL_SRC) with the c files and o files.
# Put the variables in the top section of the make file and the rule in the objects rull section.
# In the header file remember to include the external header
# Add the external header file the the src object rull or any other file that depend on it.

# External dependency objects
# EXTERNAL_O_SRC = $(PROJECT_PATH)/bin/objects/?.o

# External dependency source
# EXTERNAL_SRC = $(PROJECT_PATH)/src/?.cpp

# External dependency header
#EXTERNAL_HEADER = $(PROJECT_PATH)/include/?.hpp

#$(EXTERNAL_O_SRC) : $(EXTERNAL_SRC) $(EXTERNAL_HEADER)
# Compiler and flags
CC = gcc
CFLAGS = -Wall -Icrypto -Irequest -I/usr/include/curl # -I add directories to search for header files
LDFLAGS = -lcurl -lssl -lcrypto # Linker flags to link libcurl and ssl

# Source files - List of source files
SRC = main.c crypto/crypto.c request/request.c

# Object files
OBJ = $(SRC:.c=.o) # Automatically convert .c files into .o object files.

# Executable files
EXEC = main.out

# Targets
all: $(EXEC)

$(EXEC): $(OBJ) # Executable file depend on object files
	$(CC) -o $(EXEC) $(OBJ) $(LDFLAGS)

# $< automatic variable repesents the source files being compiled
# $@ represent the target files (the .o files)
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(EXEC)



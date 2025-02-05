CC = gcc

# define the source and object files for the server
SERVER_SRC = Pool.c Request.c Response.c Server.c 
SERVER_OBJ = $(SERVER_SRC:.c=.o)

# source and object files for the client
CLIENT_SRC = ClientMain.c Pool.c Request.c Response.c Client.c
CLIENT_OBJ = $(CLIENT_SRC:.c=.o)

# Exec files
SERVER_EXEC = Server.out
CLIENT_EXEC = Client.out

# Targets
all: $(SERVER_EXEC) $(CLIENT_EXEC)
server: $(SERVER_EXEC)
client: $(CLIENT_EXEC)

$(SERVER_EXEC):$(SERVER_OBJ)
	$(CC) -o $(SERVER_EXEC) $(SERVER_OBJ)

$(CLIENT_EXEC):$(CLIENT_OBJ)
	$(CC) -o $(CLIENT_EXEC) $(CLIENT_OBJ)

clean:
	rm -f $(SERVER_OBJ) $(SERVER_EXEC)
	rm -f $(CLIENT_OBJ) $(CLIENT_EXEC)

clean_obj:
	rm -f $(SERVER_OBJ)
	rm -f $(CLIENT_OBJ)
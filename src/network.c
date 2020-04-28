#include "network.h"

int createHost(void* data) {
    ConnectionInfo* infos = (ConnectionInfo*) data;
    server = malloc(sizeof(ServerData));
    server->ready = 0;
	//Create socket
	server->socket_desc = socket(AF_INET , SOCK_STREAM , 0);
	if (server->socket_desc == -1)
	{
        perror("Socket creation failed");
        return 1;
	}
	
	server->server_addr.sin_family = AF_INET;
	server->server_addr.sin_addr.s_addr = INADDR_ANY;
	server->server_addr.sin_port = htons(infos->port);
	
	if( bind(server->socket_desc,(struct sockaddr *) &server->server_addr , sizeof(server->server_addr)) < 0)
	{
		perror("Bind failed");
        return 1;
	}
	listen(server->socket_desc , 3);
	server->c = sizeof(struct sockaddr_in);
    
    server->waiting = 1;

    server->client_sock = accept(server->socket_desc, (struct sockaddr *) &server->client_addr, (socklen_t*) &server->c);
    if (server->client_sock < 0)
    {
		perror("Failed to accept connection");
        return 1;
    }

    signal(SIGPIPE, SIG_IGN);
    server->ready = 1;
    server->waiting = 0;


    free(data);
    return 0;
}

int serverWaiting() {
    if (server != NULL) {
        return server->waiting;
    }
    return 0;
}

int serverReceive(int addr, int length) {
    if (isHost()) {
        struct pollfd fd;
        fd.events = POLLIN;
        fd.fd = server->client_sock;
        if (poll(&fd, 1, 1)>0) {
	        if(recv(server->client_sock, memory + addr, length, 0) < 0)
	        {
                closeServer();
    		    return -1;
    	    }
            return 1;
        }
    }
    return 0;
}

int serverSend(int addr, int length) {
    if (isHost()) {
	    if (send(server->client_sock, memory + addr, length, 0) < 0) {
            closeServer();
            return -1;
        }
    }
    return 0;
}

int createClient(void* data) {
    ConnectionInfo* infos = (ConnectionInfo*) data;
    client = malloc(sizeof(ClientData));
    client->ready = 0;
    client->socket_desc = socket(AF_INET , SOCK_STREAM , 0);
	if (client->socket_desc == -1)
	{
		return 1;
	}
	
	client->server_addr.sin_port = htons(infos->port);
    client->server_addr.sin_addr.s_addr = inet_addr(infos->host);
	client->server_addr.sin_family = AF_INET;



	if (connect(client->socket_desc , (struct sockaddr *) &client->server_addr , sizeof(client->server_addr)) < 0)
	{
		perror("Connection failed");
        return 1;
	}

    signal(SIGPIPE, SIG_IGN);
    client->ready = 1;


    free(data);
	
    return 0;
}

int clientReceive(int addr, int length) {
    if (isClient()) {
        struct pollfd fd;
        fd.events = POLLIN;
        fd.fd = client->socket_desc;
        if (poll(&fd, 1, 1) > 0) {
            if(recv(client->socket_desc, memory + addr, length , 0) < 0)
            {
                closeClient();
                return -1;
            }
            return 1;
        }
    }
    return 0;
}

int clientSend(int addr, int length) {
    if (isClient()) {
        if(send(client->socket_desc, memory + addr, length, 0) < 0)
        {
            closeClient();
            return -1;
        }
    }
    return 0;
}

int closeServer() {
    close(server->socket_desc);
    close(server->client_sock);
    free(server);
    server = NULL;
    return 0;
}

int closeClient() {
    close(client->socket_desc);
    free(client);
    client = NULL;
    return 0;
}

int closeConnection() {
    if (isHost()) {
        return closeServer();
    } else if (isClient()) {
        return closeClient();
    }
    return 0;
}

int sendData(int addr, int length) {
    if (isHost()) {
        return serverSend(addr, length);
    } else if(isClient()) {
        return clientSend(addr, length);
    }
    return 0;
}

int receiveData(int addr, int length) {
    if (isConnected()) {
        if (server != NULL) {
            return serverReceive(addr, length);
        } else if(client != NULL) {
            return clientReceive(addr, length);
        }
    }
    return 0;
}

int isHost() {
    if (server != NULL) {
        return server->ready;
    }
    return 0;
}

int isClient() {
    if (client != NULL) {
        return client->ready;
    }
    return 0;
}

int isConnected() {
    return isHost() || isClient();
}

int l_createHost(lua_State* L) {
    lua_Number port = luaL_checkinteger(L, 1);
    ConnectionInfo* infos = malloc(sizeof(ConnectionInfo));
    infos->host = NULL;
    infos->port = port;
    
    SDL_Thread* thread = SDL_CreateThread(createHost, "host", infos);
    SDL_DetachThread(thread);
    lua_pushinteger(L, 0);
    return 1;
}

int l_serverWaiting(lua_State* L) {
    lua_pushboolean(L, serverWaiting());
    return 1;
}

int l_createClient(lua_State* L) {
    const char* host = luaL_checkstring(L, 1);
    lua_Number port = luaL_checkinteger(L, 2);

    ConnectionInfo* infos = malloc(sizeof(ConnectionInfo));
    infos->host =  (char*) host;
    infos->port = port;

    SDL_Thread* thread = SDL_CreateThread(createClient, "client", infos);
    SDL_DetachThread(thread);
    lua_pushinteger(L, 0);
    return 1;
}
int l_sendData(lua_State* L) {
    lua_Integer addr = (lua_Integer) luaL_checknumber(L, 1);
    lua_Integer length = (lua_Integer) luaL_checknumber(L, 2);
    int result = sendData(addr, length);
    lua_pushinteger(L, result);
    return 1;
}
int l_receiveData(lua_State* L) {
    lua_Integer addr = (lua_Integer) luaL_checknumber(L, 1);
    lua_Integer length = (lua_Integer) luaL_checknumber(L, 2);
    int result = receiveData(addr, length);
    lua_pushinteger(L, result);
    return 1;
}

int l_closeServer(lua_State* L) {
    closeServer();
    return 0;
}

int l_closeClient(lua_State* L) {
    closeClient();
    return 0;
}

int l_closeConnection(lua_State* L) {
    closeConnection();
    return 0;
}

int l_connected(lua_State* L) {
    lua_pushboolean(L, isConnected());
    return 1;
}

int l_isHost(lua_State* L) {
    lua_pushboolean(L, isHost());
    return 1;
}

int l_isClient(lua_State* L) {
    lua_pushboolean(L, isClient());
    return 1;
}

void network_pushLuaFunctions(lua_State* L) {
    define_lua_function(L, "createHost", l_createHost);
    define_lua_function(L, "serverWaiting", l_serverWaiting);
    define_lua_function(L, "createClient", l_createClient);
    define_lua_function(L, "sendData", l_sendData);
    define_lua_function(L, "receiveData", l_receiveData);
    define_lua_function(L, "closeConnection", l_closeConnection);
    define_lua_function(L, "isHost", l_isHost);
    define_lua_function(L, "isClient", l_isClient);
    define_lua_function(L, "connected", l_connected);
}
#ifndef _SE_NETWORK_H_
#define _SE_NETWORK_H_

#include "common.h"

#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <signal.h>
#include <poll.h>

typedef struct ServerData {
    int socket_desc, client_sock, c, read_size;
	struct sockaddr_in server_addr , client_addr;
    int ready;
    int waiting;
    SDL_Thread* thread;
} ServerData;

typedef struct ClientData {
    int socket_desc;
	struct sockaddr_in server_addr;
    int ready;
    SDL_Thread* thread;
} ClientData;

typedef struct ConnectionInfo {
    char* host;
    int port;
} ConnectionInfo;

ServerData* server;
ClientData* client;

int createHost(void* data);
int hostWaiting();
int serverReceive(int addr, int length);
int serverSend(int addr, int length);

int createClient(void* data);
int clientReceive(int addr, int length);
int clientSend(int addr, int length);

int closeServer();
int closeClient();
int closeConnection();

int sendData(int addr, int length);
int receiveData(int addr, int length);

int isHost();
int isClient();
int isConnected();

int l_createHost(lua_State* L);
int l_hostWaiting(lua_State* L);
int l_createClient(lua_State* L);
int l_sendData(lua_State* L);
int l_receiveData(lua_State* L);
int l_closeServer(lua_State* L);
int l_closeClient(lua_State* L);
int l_closeConnection(lua_State* L);
int l_connected(lua_State* L);
int l_isHost(lua_State* L);
int l_isClient(lua_State* L);

void network_pushLuaFunctions(lua_State* L);


#endif
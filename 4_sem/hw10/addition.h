#ifndef ADDITION_H
#define ADDITION_H

#define LEN 1024
#define BLEN 4096
#define MAX_PRINT 20

#define ERROR_OPEN_A  -21
#define ERROR_OPEN_B  -22
#define ERROR_READ_A  -23
#define ERROR_WRITE_B -24

#define ERROR_NOT_ENOUGH_MEMORY -31
#define ERROR_READ_CLASS -32
#define ERROR_SAME_DATA -33
#define ERROR_INIT_DATA -34
#define ERROR_END_OF_INPUT_FILE 1

#define ERROR_PARSE_CMD_TYPE  	-41
#define ERROR_PARSE_COND_TYPE 	-42
#define ERROR_PARSE_OP_TYPE 	-43
#define ERROR_PARSE_INSERT_ARG 	-44
#define ERROR_PARSE_WHERE       -45
#define ERROR_PARSE_C_NPG 		-46
#define ERROR_PARSE_DATA_NPG 	-47
#define ERROR_PARSE_NAME_MEMORY -48

#define ERROR_SERVER_PRINT -51
#define ERROR_SERVER_CREATE_SOCKET -52 
#define ERROR_SERVER_BIND_SOCKET -53 
#define ERROR_SERVER_LISTEN_QUEUE -54 
#define ERROR_SERVER_SELECT_SOCKET -55 
#define ERROR_SERVER_ACCEPT -56 
#define ERROR_SERVER_READ_LEN -57 
#define ERROR_SERVER_READ -58 
#define ERROR_SERVER_READ_TRUNCATED -59 
#define ERROR_SERVER_NO_MESSAGE -60

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <memory>
#include <stdarg.h>
#include <ctime>

#include <errno.h>
#include <ctype.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>

enum cmd_type  { CMD_NONE, QUIT, STOP, INSERT, SELECT, DELETE };
enum cond_type { COND_NONE, EQ, LT, GT, NE, LE, GE, LIKE };
enum op_type   { OP_NONE, AND, OR};
enum search_type { SEARCH_OR_2, SEARCH_OR_1, SEARCH2, SEARCH1, DEFAULT};

int like (char *str_name, char *str_like);
int name_hash (char *str, int n);
int phone_hash (int ph, int n);

int Printf (int fd, const char *format, ...);
int Readf (int fd, char *buf);

#endif

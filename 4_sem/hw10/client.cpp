#include "addition.h"

int main(int argc, char **argv)
{
   	const char *SERVER_NAME; int SERVER_PORT;

    if (argc !=3 || !(SERVER_PORT = atoi(argv[2])) || SERVER_PORT <= 0) return printf ("Usage: %s SERVER_NAME SERVER_PORT\n", argv[0]), 1;
    SERVER_NAME = argv[1];

	int ret, err, sock;
	struct sockaddr_in server_addr;
	struct hostent *hostinfo;

	hostinfo = gethostbyname(SERVER_NAME);
	if (!hostinfo) return printf("Unknown host %s\n", SERVER_NAME), 1;
		
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(SERVER_PORT);
	server_addr.sin_addr = *(struct in_addr *)hostinfo->h_addr;

	sock = socket(PF_INET, SOCK_STREAM, 0);
	if (sock < 0) return printf("CLIENT: socket was not created\n"), 2;

	err = connect(sock, (struct sockaddr *)&server_addr, sizeof(server_addr));
	if(err < 0) return printf("CLIENT: connect failure\n"), 3;
	printf("CLIENT: start\n\n");

	char buf[LEN];
	while (fgets (buf, LEN, stdin))
    {
    	for (ret = 0; buf[ret]; ret++)
			if (buf[ret] == '\n'){ buf[ret] = 0; break;}

		printf(" > %s\n", buf);
		if (Printf(sock, buf) < 0) printf ("CLIENT: cannot print to socket\n");
		//??

		while (true)
		{
			err = Readf (sock, buf);
			if(err < 0)
			{
				switch(err)
				{
			        case ERROR_SERVER_READ_LEN:       printf ("CLIENT: cannot read len\n");        break;
			        case ERROR_SERVER_READ:           printf ("CLIENT: cannot read\n");            break;
			        case ERROR_SERVER_READ_TRUNCATED: printf ("CLIENT: read truncated\n");         break;
			        case ERROR_SERVER_NO_MESSAGE:     printf ("CLIENT: no message\n");             break;
				}
			}
			else
			{
				if (!strcmp (buf, "quit")) 
				{
					printf (" < %s\n", buf);
					printf ("\nCLIENT: close \n\n");
					return close(sock), 0;
				}

				if (!strcmp (buf, "command completed") || (!strcmp (buf, "incorrect command")))
				{
					printf (" < %s\n\n", buf);
					break;
				}
			}
			printf ("%s", buf);
		}
    }

	return 0;
}




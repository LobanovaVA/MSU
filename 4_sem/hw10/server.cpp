#include "addition.h"
#include "data_base.h"

int tpc_ser (int PORT, data_base &A, int *alf, command &line)
{
	int i, err, ret, opt = 1;
	int sock, new_sock;
	fd_set active_set, read_set;
	struct sockaddr_in addr;
	struct sockaddr_in client;
	char buf[LEN];
	socklen_t size;

	sock = socket(PF_INET, SOCK_STREAM, 0);
	if (sock < 0) return ERROR_SERVER_CREATE_SOCKET;
	setsockopt (sock, SOL_SOCKET, SO_REUSEADDR, (char *)&opt, sizeof(opt));

	addr.sin_family = AF_INET;
	addr.sin_port = htons (PORT);
	addr.sin_addr.s_addr = htonl (INADDR_ANY);
	err = bind (sock, (struct sockaddr *)&addr, sizeof(addr));
	if(err < 0) return ERROR_SERVER_BIND_SOCKET;

	err = listen (sock, 10);
	if(err < 0) return ERROR_SERVER_LISTEN_QUEUE; 

	FD_ZERO (&active_set);
	FD_SET (sock, &active_set);

	printf ( "SERVER: start\n");

	while(true)
	{
		read_set = active_set;
		if (select (FD_SETSIZE, &read_set, NULL, NULL, NULL) < 0)
			return ERROR_SERVER_SELECT_SOCKET;

		for (i = 0; i < FD_SETSIZE; i++)
		{
			if (FD_ISSET (i, &read_set))
			{
				if(i == sock)
				{
					size = sizeof(client);
					new_sock = accept (sock, (struct sockaddr *)&client, &size);
					if(new_sock < 0) return ERROR_SERVER_ACCEPT;

					printf ( "\nSERVER: connect from host %s, port %d.\n",	inet_ntoa(client.sin_addr), (unsigned int)ntohs(client.sin_port));
					FD_SET (new_sock, &active_set);
				}
				else
				{
			// ?? 
					err = Readf (i, buf);
					if(err < 0)
					{
						switch(err)
						{
					        case ERROR_SERVER_READ_LEN:       printf ("SERVER: cannot read len\n");        break;
					        case ERROR_SERVER_READ:           printf ("SERVER: cannot read\n");            break;
					        case ERROR_SERVER_READ_TRUNCATED: printf ("SERVER: read truncated\n");         break;
					        case ERROR_SERVER_NO_MESSAGE:     printf ("SERVER: no message\n");             break;
						}
						close(i);
						FD_CLR(i, &active_set);
					}
					else
					{
						printf("\n < %d bytes of %s\n", err, buf);
						ret = line.parse (alf, buf);
				        if (ret < 0) { Printf (i, "incorrect command"); printf ("   incorrect command\n"); }
				        else
				        {
				        	ret = A.do_command (line, i);
				        	if (ret == 0) { Printf (i, "command completed"); printf ("   command completed\n"); }
				        	else
				        	{
				        		Printf(i, "quit");
				        		printf ("   connect close\n");
				        		close (i);
				        		FD_CLR (i, &active_set);
				        		if (ret == 2) 
				        		{
				        			printf ( "\nSERVER: close\n");
				        			return close (sock), 0;
				        		}

				        	}
				        }
					}
			//??
				}
			}
		}
	}
}



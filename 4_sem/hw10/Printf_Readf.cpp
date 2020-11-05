#include "addition.h"

int Printf (int fd, const char *format, ...)
{
	char buf[BLEN];
	int ret, nbytes, i;;

	va_list ap;
	va_start (ap, format);
	ret = vsnprintf (buf, LEN, format, ap);

	int len = ret + 1;
	if (write (fd, &len, sizeof(int)) != (ssize_t)sizeof(int)) 
		return va_end(ap), ERROR_SERVER_PRINT;
	

	for (i = 0; len > 0; i += nbytes, len -= nbytes)
	{
		nbytes = write (fd, buf + i, len);
		if (nbytes <= 0) 
			return va_end(ap), ERROR_SERVER_PRINT;
	}
	va_end(ap);
	return ret;
}


int Readf (int fd, char *buf)
{
	int nbytes, len, i;
	if (read (fd, &len, sizeof(int)) != (int)sizeof(int)) return ERROR_SERVER_READ_LEN;

	for(i = 0; len > 0; i += nbytes, len -= nbytes)
	{
		nbytes = read (fd, buf + i, len);
		if (nbytes < 0) return ERROR_SERVER_READ;
		else if (!nbytes) return ERROR_SERVER_READ_TRUNCATED;
	}

	if (!i) return ERROR_SERVER_NO_MESSAGE;
	else return i;	
}
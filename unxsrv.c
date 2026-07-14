#include <sys/socket.h>
#include <sys/types.h>
#include <sys/un.h>

#include <err.h>


int
main(void)
{
	int sfd, cfd;
	struct sockaddr_un uaddr;
	
	if ((sfd = socket(AF_UNIX, SOCK_STREAM, 0)) == -1)
		err(1, "socket call failed.");

	(void)memset(&uaddr, 0, sizeof(uaddr));

	return 0;

}

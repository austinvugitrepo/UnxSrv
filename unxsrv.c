#include <sys/socket.h>
#include <sys/types.h>
#include <sys/un.h>

#include <err.h>
#include <string.h>
#include <unistd.h>

int
main(void)
{
	int sfd, cfd;
	struct sockaddr_un uaddr;
	const char *msg = "Hello Unix Socket!\n";
	const char *filep = "/var/run/unxsrv.sock";

	if ((sfd = socket(AF_UNIX, SOCK_STREAM, 0)) == -1)
		err(1, "socket call failed.");

	(void)memset(&uaddr, 0, sizeof(uaddr));
	uaddr.sun_family = AF_UNIX;
	strlcpy(uaddr.sun_path, filep, sizeof(uaddr.sun_path));
	if (bind(sfd, (struct sockaddr *)&uaddr, sizeof(uaddr)) == -1)
		err(1, "bind call failed.");

	if (listen(sfd, 1) == -1)
		err(1, "listen call failed.");

	if ((cfd = accept(sfd, NULL, NULL)) == -1)
		err(1, "accept call failed.");

 	if (write(cfd, msg, strlen(msg)) == -1)
		err(1, "write call failed.");

	(void)close(cfd);
	(void)close(sfd);

 	unlink(filep);

	return 0;

}

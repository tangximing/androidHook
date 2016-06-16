#ifndef IO_H
#define IO_H

#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <string>
using namespace std;

static string services[] = {
    "com.android.internal.telephony.ISms",
    "android.content.IContentProvider",
    "com.android.internal.telephony.IPhoneSubInfo"
};

#define NSERVICES ( sizeof(services) / sizeof(services[0] ) )

int hook_open(const char *pathname, int flags);
ssize_t hook_write(int fd, const void *buf, size_t len, int flags);
ssize_t hook_read(int fd, void *buf, size_t count);
int hook_close(int fd);

int hook_connect(int sockfd, const struct sockaddr *addr, socklen_t addrlen);
ssize_t hook_send(int sockfd, const void *buf, size_t len, int flags);
ssize_t hook_sendto(int sockfd, const void *buf, size_t len, int flags, const struct sockaddr *dest_addr, socklen_t addrlen);
ssize_t hook_sendmsg(int sockfd, const struct msghdr *msg, int flags);
ssize_t hook_recv(int sockfd, const void *buf, size_t len, int flags);
ssize_t hook_recvfrom(int sockfd, const void *buf, size_t len, int flags, const struct sockaddr *dest_addr, socklen_t addrlen);
ssize_t hook_recvmsg(int sockfd, const struct msghdr *msg, int flags);
int hook_shutdown(int sockfd, int how);

int hook_ioctl(int fd, unsigned long int request, void *arg);

#endif

#ifndef SOCKET_H
#define SOCKET_H

#include <sys/socket.h>

class Socket
{
    public:
        static int socketpair(int domain, int type, int protocol,Socket** sockets);

        /** Default constructor */
        Socket(int domain, int type, int protocol);
        /** Default destructor */
        virtual ~Socket();

        int getFileDescriptor() const;

      Socket*     accept( struct sockaddr * address, socklen_t * address_len);
      int     bind( const struct sockaddr * address, socklen_t address_len);
      int     connect( const struct sockaddr* address, socklen_t address_len);
      int     getpeername( struct sockaddr * address, socklen_t * address_len);
      int     getsockname( struct sockaddr * address, socklen_t * address_len);
      int     getsockopt( int level, int otpion_name, void * option_value, socklen_t * option_len);
      int     listen( int backlog);
      ssize_t recv( void * buffer, size_t length, int flags);
      ssize_t recvfrom( void * buffer, size_t length, int flags,
              struct sockaddr * address, socklen_t * address_len);
      ssize_t recvmsg( struct msghdr * message, int flags);
      ssize_t send( const void * buffer, size_t length, int flags);
      ssize_t sendmsg( const struct msghdr * message, int flags);
      ssize_t sendto( const void * buffer, size_t length, int flags, const struct sockaddr * address,
              socklen_t address_len);
      int     setsockopt( int level, int option_name, const void * option_value, socklen_t option_len);
      int     shutdown(int how);
      int     sockatmark();
      void      setBlock();
      void      setNonBlock();


    protected:
    private:
        Socket(int fd);
        int m_fd;
};

#endif // SOCKET_H

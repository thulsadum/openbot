#include "include/Socket.h"

Socket::Socket(int domain, int type, int protocol)
{
    this->m_fd = socket(domain, type, protocol);
}

Socket::Socket(int fd) : m_fd(fd)
{
}

Socket::~Socket()
{
    //dtor
}

int Socket::getFileDescriptor() const{
    return this->m_fd;
}

Socket*     Socket::accept( struct sockaddr * address, socklen_t * address_len){
    return new Socket(::accept(m_fd, address, address_len));
}
int     Socket::bind( const struct sockaddr * address, socklen_t address_len){
    return ::bind(m_fd, address, address_len);
}
int     Socket::connect( const struct sockaddr* address, socklen_t address_len){
    return ::connect(m_fd, address, address_len);
}
int     Socket::getpeername( struct sockaddr * address, socklen_t * address_len){
    return ::getpeername(m_fd, address, address_len);
}
int     Socket::getsockname( struct sockaddr * address, socklen_t * address_len){
    return ::getsockname(m_fd, address, address_len);
}
int     Socket::getsockopt( int level, int option_name, void * option_value, socklen_t * option_len){
    return ::getsockopt(m_fd, level, option_name, option_value, option_len);
}
int     Socket::listen( int backlog){
    return ::listen(m_fd, backlog);
}
ssize_t Socket::recv( void * buffer, size_t length, int flags){
    return ::recv(m_fd, buffer, length, flags);
}
ssize_t Socket::recvfrom( void * buffer, size_t length, int flags,
      struct sockaddr * address, socklen_t * address_len){
          return ::recvfrom(m_fd, buffer, length, flags, address, address_len);
}
ssize_t Socket::recvmsg( struct msghdr * message, int flags){
    return ::recvmsg(m_fd, message, flags);
}
ssize_t Socket::send( const void * buffer, size_t length, int flags){
    return ::send(m_fd, buffer, length, flags);
}
ssize_t Socket::sendmsg( const struct msghdr * message, int flags){
    return ::sendmsg(m_fd, message, flags);
}
ssize_t Socket::sendto( const void * buffer, size_t length, int flags, const struct sockaddr * address,
      socklen_t address_len){
          return ::sendto(m_fd, buffer, length, flags, address, address_len);
}
int     Socket::setsockopt( int level, int option_name, const void * option_value, socklen_t option_len){
    return ::setsockopt(m_fd, level, option_name, option_value, option_len);
}
int     Socket::shutdown(int how){
    return ::shutdown(m_fd, how);
}
int     Socket::sockatmark(){
    return ::sockatmark(m_fd);
}

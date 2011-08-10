#ifndef SOCKETEXCEPTION_H
#define SOCKETEXCEPTION_H

#include <exception>

#ifdef SOCKETEXCEPTIONS
#define THROW_SOCKET_EXCEPTION throw SocketException(errno);
class SocketException : public std::exception {
    public:
        SocketException(char* msg) throw();
        SocketException(int errnum) throw();

        virtual const char* what() const throw();

    private:
        const char* m_msg;
};

#else
#define THROW_SOCKET_EXCEPTION
#endif


#endif // SOCKETEXCEPTION_H

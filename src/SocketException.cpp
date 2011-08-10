#include "include/SocketException.h"
#ifdef SOCKETEXCEPTIONS

#include <cstring>
#include <sstream>

using std::stringstream;

SocketException::SocketException(int errnum) throw() {
    stringstream ss;
    ss << "errno: " << errnum << "\n\t" << strerror(errnum);
    m_msg = ss.str().c_str();
}

SocketException::SocketException(char* what) throw() {
    m_msg = what;
}

const char* SocketException::what() const throw() {
    return m_msg;
}

#endif

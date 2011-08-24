#ifndef IRC_H
#define IRC_H

#include "include/Socket.h"
#include <queue>
#include <string>
#include <ctime>
#include <sstream>
using std::string;
using std::queue;
using std::ostringstream;

#define CRLF "\r\n"

#define RBUF_SIZE 40960

class IRC
{
    public:
        /** Default constructor */
        IRC();
        /** Default destructor */
        virtual ~IRC();

        bool isConnected() const;
        bool connect(string server, unsigned short port, string password);
        bool connect(string server, unsigned short port);

        void setNick(string nick);
        string getNick() const;

        void setUser(string user);
        string getUser() const;

        void setRealname(string realname);
        string getRealname() const;

        void setResetInterval(double value);
        double getResetInterval() const;

        void setMaxMessages(int value);
        double getMaxMessages() const;

        void sendCmd(string cmd);
        void poll();


    protected:
    private:
        Socket *m_sock;
        queue<string> *m_qsend;
        queue<string> *m_qrecv;

        double m_rstint;
        time_t m_lastrst;
        int m_sendcount;
        int m_maxcount;

        string m_nick;
        string m_user;
        string m_realname;

        ostringstream m_recvbuf;

        void parse(string msg);
        void send(string msg);
        int recv();
        void sendImmediate(string msg);
};

#endif // IRC_H

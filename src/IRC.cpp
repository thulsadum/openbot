#include "include/IRC.h"
#include "include/IRCMessageBuilder.h"
#include "include/Controller.h"
#include "include/helper.h"

#include <netdb.h>
#include <sstream>
#include <include/debug.h>
#include <cstring>
#include <cstdlib>
#include <cerrno>

using std::ostringstream;

IRC::IRC()
{
    TRACE_ENTER(IRC,IRC);

    m_qsend = new std::queue<string>;
    m_qrecv = new std::queue<string>;
    m_sock = new Socket(AF_INET, SOCK_STREAM, 0);

    //m_sock->setsockopt(0, , 1, sizeof(int));

    TRACE_LEAVE(IRC,IRC);
}

IRC::~IRC()
{
    //dtor
}

void IRC::setNick(string nick) {
    this->m_nick = nick;
}

string IRC::getNick() const {
    return this->m_nick;
}

void IRC::setUser(string user) {
    this->m_user = user;
}

string IRC::getUser() const {
    return this->m_user;
}

void IRC::setRealname(string realname) {
    this->m_realname = realname;
}

string IRC::getRealname() const {
    return this->m_realname;
}

bool IRC::connect(string server, unsigned short port) {
    TRACE_ENTER(IRC, connect)

    NOTICE("IRC::connect", "making socket blocking...")
    m_sock->setBlock();

    ostringstream msg;
    msg << "connecting to " << server << ":" << port;
    INFO("IRC::connect", msg.str());

    msg.str("");
    msg << "resolving hostname " << server;
    DEBG("IRC::connect", msg.str());

    addrinfo *res;

    char *sport = new char[100];
    sprintf(sport, "%d", port);

    int err = getaddrinfo(server.c_str(), sport, NULL, &res);
    if(err != 0){
        ERROR("IRC::connect", gai_strerror(err))
        TRACE_LEAVE(IRC, connect)
        return false;
    }

    msg.str("");
    msg << "do socket connect";
    DEBG("IRC::connect", msg.str());

    err = this->m_sock->connect(res->ai_addr, res->ai_addrlen);
    if( err != 0) {
        ERROR("IRC::connect", strerror(errno))
        TRACE_LEAVE(IRC, connect)
        return false;
    }
    freeaddrinfo(res);

    sendImmediate(IRCMessageBuilder::nick(getNick()));
    sendImmediate(IRCMessageBuilder::user(getUser(), "localhost", server, getRealname()));

    NOTICE("IRC::connect", "making socket non-blocking...")
    m_sock->setNonBlock();
    TRACE_LEAVE(IRC, connect)
    return true;
}

void IRC::sendImmediate(string msg){
    NOTICE("IRC::sendImmediate", "sending an message immediately");
    this->send(msg.append(CRLF));
}

void IRC::send(string buffer) {
    Controller::getController()->log(LL_RAW,"OUT", buffer.substr(0, buffer.length()-2));
    this->m_sock->send(buffer.c_str(), buffer.length(), 0);
}

void IRC::sendCmd(string cmd){
    this->m_qsend->push(cmd.append(CRLF));
}

void IRC::poll() {

    ostringstream dmsg;

    // reseting flood protection
    time_t now;
    time(&now);
    if(difftime(m_lastrst, now) > getResetInterval()){
        this->m_lastrst = now;
        this->m_sendcount = 0;
    }

    // processing pending sending messages, if possible.
    if(m_sendcount < m_maxcount && !m_qsend->empty()) {
        string msg = m_qsend->front();
        this->send(msg);
        m_qsend->pop();
    }

    // recv messages

    if( this->recv() > 0){
        // yay we received something
        string input = this->m_recvbuf.str();
        int start = 0, end;
        while((end = input.find(CRLF, start)) >= 0) {
            this->m_qrecv->push(input.substr(start, end-start));
            start = end+2;
            Controller::getController()->log(LL_RAW, "IN", this->m_qrecv->back());
        }
        if((unsigned int)start < input.size()){
            this->m_recvbuf.str(input.substr(start, input.size()-start));
        }
    }

    if(!this->m_qrecv->empty()){
        string msg = this->m_qrecv->front();
        this->m_qrecv->pop();
        parse(msg);
    }
}

void IRC::setResetInterval(double val) {
    this->m_rstint = val;
}

double IRC::getResetInterval() const {
    return this->m_rstint;
}

void IRC::setMaxMessages(int val) {
    this->m_maxcount = val;
}

double IRC::getMaxMessages() const {
    return this->m_maxcount;
}

int IRC::recv() {
    int read;
    char* buffer = new char[RBUF_SIZE];

    memset(buffer, 0,  RBUF_SIZE);
    read = this->m_sock->recv(buffer, RBUF_SIZE-1, 0);
    this->m_recvbuf << buffer;

    if(read== 0) return 0;
    if(errno == EAGAIN) return 0;
    if(read == -1) {
        WARNING("IRC::recv", strerror(errno));
        return -1;
    }
    return read;
}

void IRC::parse(string message) {
    // spliting message into chunks separated by spaces
    vector<string> args = split(message, " ");

    ostringstream msg;
    string cmd;
    int argstart;

    msg << "arguments: " << args.size();
    DEBG("IRC::parse", msg.str())
    if(args[0][0] == ':'){
        cmd = args[1];
        argstart = 2;
    } else {
        cmd = args[0];
        argstart = 1;
    }

    msg.str("");
    msg << cmd << " " << join(args,argstart, args.size(), ",");
    DEBG("IRC::parse", msg.str());
}

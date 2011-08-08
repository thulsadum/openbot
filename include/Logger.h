#ifndef LOGGER_H
#define LOGGER_H

#include <ostream>
#include <string>

using namespace std;

enum Loglevel {
    LL_NONE = 0,
    LL_CRITICAL = 1,
    LL_ERROR = 2,
    LL_WARNING = 4,
    LL_NOTICE = 8,
    LL_INFO = 16,
    LL_DEBUG = 32,
    LL_TRACE = 64,
    LL_FULLDEBUG = 128,

    LL_LEASTWARN = 7,
    LL_ALL = 0xff,
};

class Logger
{
    public:
        /** Default constructor */
        Logger();
        /** Default destructor */
        virtual ~Logger();

        ostream* getStream() const;
        void setStream(ostream* stream);

        string getFormat() const;
        void setFormat(string format);

        string getDateFormat() const;
        void setDateFormat(string format);

        int getLevelMask() const;
        void setLevelMask(int mask);

        bool isLevel(Loglevel level) const;
        void log(Loglevel level, string message) const;
        void log(Loglevel level, string sClass, string message) const;

        void mark(string message) const;
        void mark() const;


        static string strLoglevel(Loglevel level);

    protected:
    private:
        ostream* m_out;
        string m_format;
        string m_dateformat;
        int m_mask;
};
#endif // LOGGER_H

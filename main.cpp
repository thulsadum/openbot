#include <iostream>
#include <getopt.h>
#include <libconfig.h++>
#include "include/Logger.h"
#include "version.h"
#include "include/Controller.h"

#include "include/SocketException.h"
#include <errno.h>

using namespace std;

void showHelp(ostream& out, const char * arg0){
    out << "Usage: " << arg0 << " [options] -c <config file>" << endl;
    out << endl;
    out << "\t" << "-h, --help\t show this help message and quit" << endl;
    out << "\t" << "-c, --config=FILE\t specifies the config file. Note: command line options overrides settings" << endl;
    out << "\t" << "-d, --daemonize\t detach from terminal" << endl;
}


int main(int argc, char** argv)
{
    libconfig::Config * config = new libconfig::Config();
    bool readConfig = false, daemonize = false;

    while(1) {
        static struct option long_options[] = {
            {"help",    no_argument,    0,  'h'},
            {"daemonize",no_argument,    0, 'd'},
            {"config",  required_argument,  0,  'c'},
            {"version",no_argument,    0, 'V'},
            {0,         0,              0,  0},
        };

        int loptind = 0;
        int o;

        o = getopt_long(argc, argv, "hdc:V", long_options, &loptind);

        if(o == -1) break;

        // cout << o << endl;
        switch(o){
            case 'h':
                showHelp(cout, argv[0]);
                return 0;
                break;
            case 'd':
                cout << "daemonize" << endl;
                break;
            case 'V':
                /** @todo give email address */
                cout << "IRC Bot v" << AutoVersion::MAJOR << "." << AutoVersion::MINOR << AutoVersion::STATUS_SHORT << " rev "
                    << AutoVersion::REVISION << " Build: " << AutoVersion::BUILD << " ("<< AutoVersion::YEAR << "-"
                    << AutoVersion::MONTH << "-" << AutoVersion::DATE <<")" << endl;
                break;
            case 'c':
                readConfig = true;
                try{
                    config->readFile(optarg);
                }catch(libconfig::ParseException& e){
                    cerr << "error parsing configuration file:"<< endl;
                    cerr << "\t" << e.getFile() << ":" << e.getLine() << " - " << e.getError();
                    return 1;
                }
                break;
        }
    }

    if(!readConfig)
        cerr << "must specify an config file with '-c' or '--config' commandline option" << endl;

    Controller::setConfig(config);
    Controller* ctrl = Controller::getController();

    if(daemonize) ctrl->daemonize();
#ifdef DEBUG
    ctrl->addLogger("STDOUT", 0x7f);
#endif
    ctrl->run();




    return 0;
}

#include <iostream>
#include <fstream>
#include "include/Logger.h"

using namespace std;

int main()
{

    Logger* logger = new Logger();

    ofstream out;

    out.open("test.log", ios_base::app);

    logger->setStream(&out);
    logger->setLevelMask(LL_ALL);

    logger->mark();
    logger->log(LL_CRITICAL, "this is critical");
    logger->log(LL_ERROR, "this is error");
    logger->log(LL_WARNING, "this is warning");
    logger->log(LL_NOTICE, "this is notice"); // should not be shown
    logger->mark();

    out.close();


    return 0;
}

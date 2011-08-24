#include "include/helper.h"
#include <sstream>
using std::ostringstream;
// some helper functions
string replaceAll(string haystack, string needle, string replacement){
    int start = 0;
    while((start=haystack.find(needle)) >= 0){
        haystack=haystack.replace(start,needle.length(), replacement);
    }
    return haystack;
}

vector<string> split(string input, string delimeter) {
    vector<string> args;
    // spliting message into chunks separated by spaces
    int start=0, end;
    while((end = input.find(" ", start)) >= 0) {
        args.push_back(input.substr(start,end - start));
        start = end + 1;
    }
    return args;
}

string join(vector<string> input, int start, int end, string glue) {
     ostringstream tmp;
     if(start > end) return "";
     if(start < 0) return "";
     if((unsigned int)end > input.size()) return "";

     for(int i = start; i < end; i++) {
        tmp << input[i];
        if(i < end-1) tmp<<glue;
     }
     return tmp.str();
}

string join(vector<string> input, string glue) {
    return join(input, 0, input.size(), glue);
}

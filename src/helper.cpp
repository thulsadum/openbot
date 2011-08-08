#include "include/helper.h"

// some helper functions
string replaceAll(string haystack, string needle, string replacement){
    int start = 0;
    while((start=haystack.find(needle)) >= 0){
        haystack=haystack.replace(start,needle.length(), replacement);
    }
    return haystack;
}

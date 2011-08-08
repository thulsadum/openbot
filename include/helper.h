#ifndef HELPER_H_INCLUDED
#define HELPER_H_INCLUDED

#include <string>
using namespace std;

/** replaces all occurences of an string in a string
  * @param haystack string in which will be searched
  * @param needle string for which will be searched
  * @param replacemant string which will replace the needles
  * @return string with replacements
  */
string replaceAll(string haystack, string needle, string replacement);



#endif // HELPER_H_INCLUDED

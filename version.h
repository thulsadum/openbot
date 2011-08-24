#ifndef VERSION_H
#define VERSION_H

namespace AutoVersion{
	
	//Date Version Types
	static const char  _DATE[] = "24";
	static const char  _MONTH[] = "08";
	static const char  _YEAR[] = "2011";
	static const char  _UBUNTU_VERSION_STYLE[] = "11.08";
	
	//Software Status
	static const char  _STATUS[] = "Alpha";
	static const char  _STATUS_SHORT[] = "a";
	
	//Standard Version Type
	static const long  _MAJOR = 0;
	static const long  _MINOR = 4;
	static const long  _BUILD = 337;
	static const long  _REVISION = 1926;
	
	//Miscellaneous Version Types
	static const long  _BUILDS_COUNT = 609;
	#define  _RC_FILEVERSION 0,4,337,1926
	#define  _RC_FILEVERSION_STRING "0, 4, 337, 1926\0"
	static const char  _FULLVERSION_STRING[] = "0.4.337.1926";
	
	//These values are to keep track of your versioning state, don't modify them.
	static const long  _BUILD_HISTORY = 37;
	

}
#endif //VERSION_H

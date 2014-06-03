/*
Copyright (c) 2014, Bart Bilos

All rights reserved.

Redistribution and use in source and binary forms, with or without modification,
are permitted provided that the following conditions are met:

    * Redistributions of source code must retain the above copyright notice,
      this list of conditions and the following disclaimer.
    * Redistributions in binary form must reproduce the above copyright notice,
      this list of conditions and the following disclaimer in the documentation
      and/or other materials provided with the distribution.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
"AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER
OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/
#ifndef DEBUG_H_
#define DEBUG_H_

typedef enum {
	logNone	= 0x00,
	logInfo = 0x01,
	logWarn = 0x02,
	logError = 0x04,
} logLevels;

#ifdef DEBUG
	#define DLOG(logmodule, loglevel, fmt, args...) 										\
		do { 																				\
			if(logmodule & loglevel) printf("%s:%d "fmt,__FILE__,__LINE__,##args);			\
		} while (0)
#else
	#define DLOG(logmodule, loglevel, fmt, args...)
#endif

#ifdef DEBUG
	#define ASSERT(logmodule, loglevel, fmt, args...) 										\
		do { 																				\
			if(logmodule & loglevel) printf("ASSERT! %s:%d "fmt,__FILE__,__LINE__,##args);	\
			while(1);																		\
		} while (0)
#else
	#define ASSERT(logmodule, loglevel, fmt, args...)										\
		do {																				\
		} while(1);
#endif

enum logModules {
	logTest 		= logInfo | logWarn | logError,
	logMain 		= logNone,
};

#endif

#pragma once

/*
Error C4251 is disabled; as we do not use interfaces for public API but expose raw headers, STL constructs are
also exposed which can be problematic in situation when the library is not linking with same versions of STL and CRT.
It seems that we are safe here, because this warning warns on corner cases, but heads should stay up.
For more info view: https://msdn.microsoft.com/en-us/library/esew7y1w.aspx
*/

#pragma warning(disable:4251)

#ifdef _WIN32
    #ifdef ELEUSIS_EXPORTS
        #define ELEUSIS_API __declspec(dllexport)
    #else
        #define ELEUSIS_API __declspec(dllimport)
    #endif
#else
    #define ELEUSIS_API
#endif

#ifndef PIGON_GLOBAL_H
#define PIGON_GLOBAL_H

#if defined(WIN32)
#if defined(PIGON_LIBRARY)
#  define PIGONSHARED_EXPORT __declspec(dllexport)
#else
#  define PIGONSHARED_EXPORT __declspec(dllimport)
#endif
#else
#  define PIGONSHARED_EXPORT
#endif
#endif // PIGON_GLOBAL_H

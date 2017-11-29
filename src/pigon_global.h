#ifndef PIGON_GLOBAL_H
#define PIGON_GLOBAL_H

#if defined(PIGON_LIBRARY)
#  define PIGONSHARED_EXPORT __declspec(dllexport)
#else
#  define PIGONSHARED_EXPORT __declspec(dllimport)
#endif

#endif // PIGON_GLOBAL_H

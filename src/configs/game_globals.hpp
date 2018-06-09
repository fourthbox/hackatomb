#ifndef GAME_GLOBALS_HPP_
#define GAME_GLOBALS_HPP_

#ifndef NDEBUG      // Debug Settings
#define DEBUG_ true
#else              // End debug Settings
#define DEBUG_ false
#endif

#if _WIN32
#define DEPRECATED_ __declspec(deprecated)
#else
#define DEPRECATED_ [[deprecated]]
#endif

#include <iostream>

using std::cout;
using std::endl;

#endif /* GAME_GLOBALS_HPP_ */

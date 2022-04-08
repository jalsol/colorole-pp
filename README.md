# 🖌️ colorole++

A simple Discord bot to change username's colors by changing roles.

Written in C++ to prove ***<a href="https://github.com/bubu1441006/colorole">bubu</a> is non*** and I'm (obviously) superior to him.

# Requirements
- C++11 (GNU GCC 11.1.0)
- CMake 3.6 or above
- <a href="https://github.com/yourWaifu/sleepy-discord">Sleepy Discord</a>

# Building instructions
- Create 2 directories: `deps` and `build`
- Enter `deps` and clone <a href="https://github.com/yourWaifu/sleepy-discord">Sleepy Discord</a>, then go back
- `cmake -S . -B ./build`
- `make -C build`
- The executable `colorole` will appear.

# Notes
- C++11 is required to compile.
- If error 5002 gets raised, just delete `build/CMakeCache.txt` and rebuild.
- If CMake complains about deprecation for versions < 2.8.12, go to `deps/sleepy-discord/buildtools/cmake/`, open `DownloadProject.CMakeLists.cmake.in`, then edit `2.8.2` to `3.6`.
# 🖌️ colorole++

A simple Discord bot to change username's colors by changing roles.

Written in C++ to prove ***<a href="https://github.com/bubu1441006/colorole">bubu</a> is non*** and I'm (obviously) superior to him.

# Requirements
- C++11 (GNU GCC 11.1.0)
- CMake 3.6 or above
- <a href="https://github.com/yourWaifu/sleepy-discord">Sleepy Discord</a>

# Building instructions
- Clone this repository **recursively** (so that the dependencies will be cloned as well)
- Create a directory called `build`
- `cmake -S . -B ./build`
- `make -C build`
- The executable `colorole` will appear.

# Running instructions
- Create a bot, enable permissions that allow the bot to manage roles, read and send messages.
- Enable `Presence Intent` and `Server Members Intent`.
- Define an environment variable `COLOROLE_TOKEN` and paste the token there.
- Run the `colorole` executable.

# Notes
- This implementation is **greatly inefficient**, so use at your own risk.
- C++11 is required to compile.
- If error 5002 gets raised, clear CMake build cache by deleting `build/CMakeCache.txt`, then rebuild.
- If CMake complains about deprecation for versions < 2.8.12, go to `deps/sleepy-discord/buildtools/cmake/`, open `DownloadProject.CMakeLists.cmake.in`, then edit `2.8.2` to `3.6`.
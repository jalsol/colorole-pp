# 🖌️ colorole++

A simple Discord bot to change username's colors by replacing their roles.

Written in C++ to prove ***<a href="https://github.com/bubu1441006/colorole">bubu</a> is non*** and I'm (obviously) superior to him.

# Usage
The command prefix for this bot is `$#`.

## `$#<hex code>`
Change the color of your name to the color specified by the hex code.

<img src="assets/usage/hexcode.png"/>

## `$#random`
Change the color of your name to a random color.

<img src="assets/usage/random.png"/>

## `$#copy @user`
Change the color of your name to the mentioned user's color.

<img src="assets/usage/copy.png"/>

# Requirements
- C++11 (GNU GCC 11.1.0)
- CMake 3.6 or above
- <a href="https://github.com/yourWaifu/sleepy-discord">Sleepy Discord</a>

# Building
- Clone this repository
- Fetch submodules: `git submodule update --init --recursive`
- Create a directory called `build`
- Make sure the definition of `DEVELOPMENT` is commented out in `CMakeLists.txt`.
- `cmake -S . -B ./build`
- `make -C build`
- The executable `colorole` will appear.

# Running
- Create a bot, enable permissions that allow the bot to manage roles, read and send messages.
- Enable `Presence Intent` and `Server Members Intent`.
- Define an environment variable `COLOROLE_TOKEN` and paste the token there.
- Run the `colorole` executable.

# Notes
- This implementation is **highly inefficient**, so use at your own risk.
- C++11 is required to compile.
- If error 5002 gets raised, clear CMake build cache by deleting `build/CMakeCache.txt`, then rebuild.
- If CMake complains about deprecation for versions < 2.8.12, go to `deps/sleepy-discord/buildtools/cmake/`, open `DownloadProject.CMakeLists.cmake.in`, then edit `2.8.2` to `3.6`.


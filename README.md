# Raylib XML Support
A small library that adds XML support for animations.

# STILL WIP
This library is not finished! There are still a lot of things I want to add before releasing the first version!

# Makefile
Here is a Makefile that might come in handy. Put it inside the build folder once it gets created. (Remove time if you are not on a Unix system)
```makefile
default:
    @echo "Building project..."
    time ninja && ./game

on:
    @echo "Clang-tidy enabled"
    cmake -GNinja -DENABLE_CLANG_TIDY=ON ..

off:
    @echo "Clang-tidy disabled"
    cmake -GNinja -DENABLE_CLANG_TIDY=OFF ..

tidy:
    @echo "Using clang-tidy"
    clang-tidy -p ./ ../common/PCH.cpp $$(find ../source -name '*.cpp') ../main.cpp -checks=* -header-filter='^$$'

fix:
    @echo "Using clang-tidy AND fixing code"
    clang-tidy -p ./ ../common/PCH.cpp $$(find ../source -name '*.cpp') ../main.cpp -checks=* -header-filter='^$$' -fix

cloc:
    cloc ../library
```
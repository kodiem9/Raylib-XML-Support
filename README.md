# Raylib XML Support
A small library that adds XML support for animations.

# STILL WIP
This library is not finished! There are still a lot of things I want to add before releasing the first version!

# Makefile
Here is a Makefile that might come in handy. Put it inside the build folder once it gets created.
```makefile
default:
	@echo Building project...
	ninja && game.exe

on:
	@echo Clang-tidy enabled
	cmake -GNinja -DENABLE_CLANG_TIDY=ON ..

off:
	@echo Clang-tidy disabled
	cmake -GNinja -DENABLE_CLANG_TIDY=OFF ..

deb:
	@echo changed to "Debug" mode
	cmake -DCMAKE_BUILD_TYPE=Debug ..

rel:
	@echo changed to "Release" mode
	cmake -DCMAKE_BUILD_TYPE=Release ..

tidy:
	@echo Using clang-tidy
	clang-tidy -p ./ ../common/PCH.cpp $$(find ../source -name '*.cpp') ../main.cpp -checks=* -header-filter='^$$'

fix:
	@echo Using clang-tidy AND fixing code
	clang-tidy -p ./ ../common/PCH.cpp $$(find ../source -name '*.cpp') ../main.cpp -checks=* -header-filter='^$$' -fix

cloc:
	cloc ../library
```

# VSCode
These json files might be useful to make the project structure more clean. Also "fixes" include errors

settings.json
```json
{
    "files.exclude": {
        ".gitignore": true,
        "LICENSE": true,
        "*.md": false,
        "**/.cache": false,
        "**/.vscode": false,
        "**/build": false,
    }
}
```

c_cpp_properties.json
```json
{
    "configurations": [
        {
            "name": "Windows",
            "includePath": [
                "${workspaceFolder}/**",
                "C:/raylib",
                "${workspaceFolder}/library/include",
                "${workspaceFolder}/example/common",
                "${workspaceFolder}/thirdparty/include"
            ],
            "cStandard": "c11",
            "cppStandard": "c++17"
        }
    ],
    "version": 4
}
```
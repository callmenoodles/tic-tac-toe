# Tic Tac Toe
Tic Tac Toe made with C++ and SDL2.

## Disclaimer
This is an old project that was later pushed to GitHub.

## Getting Started
Importing SDL2 in Visual Studio:
1. Go to Project > Properties > C/C++ > General
2. Edit `Additional Include Directories`
3. Insert a new line and add `<project root>/deps/SDL/include` and `<project root>/deps/SDL_ttf/include`
4. Hit OK and go to Linker > General
5. Edit `Additional Library Directories`
6. Insert a new line and add `<project root>/deps/SDL/lib/x64` (or x86) and `<project root>/deps/SDL_ttf/lib/x64` (or x86)
7. Go to Linker > Input
8. Edit `Additional Dependencies`
9. Add `SDL2.lib`, `SDL2main.lib`, `SDL_image.lib` and `libfreetype-6.lib`
10. Hit OK and you're set up.

## Controls
Press `Q` to restart.

## License
[MIT](LICENSE)

# engine-v2
 
`engine-v2` builds on some of the progress in `engine` in terms of gameplay systems, but sheds the legacy of the not-invented-here attitude I had regarding the rendering, sound, file I/O, and platform interactions that I had held when working on `engine`. I also began to make wide use of the C++ standard library and standard template library in order to reduce development time and overhead. `engine-v2` ditches the custom platform layer and DirectX 11 renderer. Instead I build upon the well constructed and maintained [Raylib](https://www.raylib.com/) library along with some of its supporting eco-system. This has allowed me to more rapidly develop the gameplay and tooling of the `engine-v2` compared to `engine` because much of the building blocks of a game engine are already implemented in Raylib, such as, Keyboard, Mouse, and Controller input, 2D rendering, image file loading, [Raygui](https://github.com/raysan5/raygui) provides IMGUI functionality that matches the look and API choices of Raylib.

I didn't do a complete rewrite from scratch this time, instead I brought over the Entity-Component-System and certain design choices like the `universal.h` aggregation of file includes. Combining that existing code and ideas with the simplification of the base layer of the game that Raylib brings has allowed me to make much quicker progress on this project than previous ones. I have also made more effective use of Git, creating branches and using pull requests rather than simply pushing everything directly into the main branch. Github Issues have been my primary task list during the project. My workflow has focused on creating issues for features or refactors or implementations that need to be done ahead of time. Which allows me to pick and choose from a variety of tasks that need to be done rather than tunnel visioning on the task that is directly in front of me.

## Current Features
- Entity Spawner GUI window
- Debug information display
- 2D Camera with zooming
- Action system that abstracts game control from input device
- Map Loading from png
- Unit movement using A* algorithm
- Unit movement range and path graphics
- Unit attack range graphics
- Entity saving and loading

## Instructions
Command Line: (Note: The behavior of these instructions is currently unknown when the user doesn't have access to the engine-v2-assets repo)
```
git clone https://github.com/Andidy/engine-v2
cd engine-v2
./setup.bat
```

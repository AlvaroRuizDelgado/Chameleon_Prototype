# Chameleon

Basic SFML game prototype made to teach about color expressions. The game is in an early state, patiently waiting for me to get back into it and finish it :(.

## File structure

    .
    ├── Code                   # Code of the program
    ├── Resources              # Different resources like audio, graphics, fonts, shaders...
    │   ├── fonts
    │   ├── graphics
    │   ├── shaders
    │   └── sound
    ├── External Libraries     # Libraries like SFML or Box2D
    └── Platforms              # Location of project files for different platforms or IDEs

## Use with Visual Studio

The "Resources" folder needs to be present in the "Debug" and "Release" folders to be accessible from the created executable. In addition, it also needs to be present in the project directory to be accessible from the debugger.

The script "winResources.sh" is there to alleviate the constant copying to different locations. Simply run it every time a resource is added or modified.

```
$ . winResources.sh
```

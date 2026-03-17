# cub3D

*This project has been created as part of the 42 curriculum by hanwang, yshi.* 

## Description
**cub3D** is a project inspired by the world-famous 1992 game *Wolfenstein 3D*, considered the first true First-Person Shooter (FPS) in history. The goal of this project is to create a dynamic 3D graphical representation of the inside of a maze from a first-person perspective using **ray-casting principles**.

This project focuses on several key learning objectives:
* **Graphics & Mathematics**: Implementing practical applications of mathematics to create efficient rendering algorithms for windows, colors, and textures.
* **Event Management**: Handling user inputs for movement and window interactions smoothly.

## Instructions

### Compilation
The project includes a `Makefile` that compiles the source files using `cc` with the flags `-Wall -Wextra -Werror`.

To compile the mandatory part:
```bash
make
```

To compile the bonus part:
```bash
make bonus
```
### Execution
The program requires a scene description file with a `.cub` extension as its only argument.

```bash
./cub3D maps/example.cub
```

## Controls
* **W, A, S, D**: Move the point of view through the maze.
* **Left/Right Arrow Keys**: Look left and right.
* **ESC / Red Cross**: Close the window and exit the program cleanly.

## Resources
### References
* [Lode's Raycasting Tutorial](https://lodev.org/cgtutor/raycasting.html) (Classic reference for ray-casting logic).
* [Wolfenstein 3D Original Game](http://users.atw.hu/wolf3d/) (For technical inspiration).
* [MiniLibX Documentation](https://harm-smits.github.io/42docs/libs/minilibx.html) (Official graphics library used).

### AI Usage
AI tools were used for:

- Understanding raycasting concepts

- Debugging specific issues

- Generating test cases

- Structuring documentation

All generated content was reviewed, tested, and fully understood before integration.
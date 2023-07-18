# opengl-basics

A project with some basic code to work with OpenGL.
Nothing productive, just to understand how some things work.
Code might be "overcommented" for easier understanding.

Requires GLEW.

```cpp
/**
 * 
 * OpenGL Pipeline
 * 
 * CPU: Vertex data
 * GPU:
 *   vertex processing (vertex shader): local, eye, clip, world
 *   primitive assembly: triangles, quads, lines, points
 *   rasterization: smoothing, multisampling
 *   fragment processing (fragment shader): alpha, depth, textures, stencil, 
 *   Framebuffer: pixels
 */ 
```
- OpenGL Coordinate System
- right handed
- X,Y and Z in the direction of the viewer

- Matrices
- Can rotate, scale and translate vertex positions
- Map to a different coodinate system
- Or use to project vertices onto the screen

- Model transformations (with matrices)
- Transforms from local space to world space
- Common/recommended order: Scale, rotate, and translate
- Order of the matrix multiplication is in the opposite order
- E.g. final matrix = [translate matrix] * [rotate matrix] * [scale matrix]

- View transformations
- Transforms from world space to eye space
- Required is position of the viewer, target point and vector for UP

- Projection matrix
- Transforms eye space coordinates to clip space (i.e. screen area)

GLEW:
- interface for OpenGL1.1 and above
- can check/load OpenGL extensions

GLFW:
- allows support for multiple windows
- for window creation and management
- can handle input devices (mouse, keyboard, joystick, gamepad)

SDL:
- can do more
- allows access to audio, fs, 


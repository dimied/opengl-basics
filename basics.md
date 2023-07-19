# Basics


## Rending pipeline
- 4 stages can use shaders for programming
- shaders written in GLSL(OpenGL Shading Language), based on C

- Vertex specification:
  - programmable by shaders
  - provide data of vertices for the primitives to render
  - done by application
  - VAOs(Vertex Array Objects)
    - define position, color, texture, ...
  - VBOs(Vertex Buffer Objects)
    - define the datas
  - Attribute pointers point to data to be used by shaders
  - process:
    - generate VAO Id
    - bind VAO with that ID
    - generate VBO Id
    - bind VBO with that ID
    - attach data to that VBO
    - define attribute pointer and enable it
    - unbind VAO and VBO
  - Draw:
    - activate shader program
    - bind VAO of your data
    - call glDrawArrays
  - Vertex shader
    - performed for individual vertices
    - must store data in gl_Position, it's required by other stages
    - need vertex data
    - can also have additional data
```
#version 120
// for versions 130 and above 
//it should be "in" instead of "attribute"
attribute vec4 position;

void main() {
    gl_Position = position;
}
```
```
#version 330
in vec3 pos;

void main() {
    gl_Position = vec4(pos, 1.0);
}
```
- Tesselation
  - since OpenGL 4.0
  - subdivide data in to smaller primitives
- Geometry shaders
  - handles groups of vertices
  - can modify given data to create new primitives
- Vertex post-processing
  - can output given data to buffers
  - Clipping:
    - removing not visible primitives
    - vertex/primitive positions converted to "window space"
- Primitive Assembly
  - vertices converted into primitives
  - face culling: removing primitives pointing away frpm viewer
- Rasterization:
  - primitives converted to fragments
- Fragment shader
  - handles fragments
  - pixel color is one important output
```
#version 330
//the only output of fragment shader
out vec4 color;

void main() {
    color = vec4(0, 1.0, 0, 1.0);
}
```
- Per-Sample Operations 
  - checks if fragment should be drawn
  - depth test
  - color blending (i.e. mixing colors for overlapping fragments)
  - output into fragment buffer
- Buffer swap
```c

```
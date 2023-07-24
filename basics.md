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
- Uniform variables
```c
#version 330
attribute vec4 position;
attribute vec4 color;

varying vec4 dstColor;

// Matrices for transformations
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main() {
    dstColor = color;
    gl_Position = projection * view * model * position;
}
```

## Textures
- many image libraries available:
  - SOIL (Simple OpenGL Image Library), stb_image
- primarily for image data
- 1D, 2D, 3D textures possible
- texels : points in textures
- texels defined in range between 0 and 1
  - (0,0) bottom-left, (1,1) top-right
- interpolation is used for texel data
- samplers are used in shaders to access texture data
- Mipmaps can be used for different levels of detail (glGenerateMipmap(...))
- types: GL_TEXTURE_1D, GL_TEXTURE_2D, GL_TEXTURE_3D, GL_TEXTURE_CUBE_MAP
- creating/binding texture objects
```c
//binding
glGenTextures(1, &textureObject);
glBindTexture(GL_TEXTURE_2D, textureObject);
```
- binding data
```c
//binding
glTexImage2D(
  GL_TEXTURE_2D, //target
  0, // Mipmap level (usually 0)    
  GL_RGB, // Format of data used by OpenGL for drawing
  width, height, //dimensions
  0, //for border, usually 0
  GL_RGB, // format of loaded data
  GL_UNSIGNED_BYTE, // type of loaded values
  pTextureData  //data to load
);
```
- Filters: How to choose texel values
  - 2 choices:
    - NEAREST: Nearest texel value, creates pixelated effect
    - LINEAR: texel values are interpolated/blended
```c
// for the case when texture is scaled down, i.e. further away from viewer
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
// for the case when texture is scaled up, i.e. closer to viewer
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
```
- Wrap: Defines how texture coordinates outside of [0,1] are shown
  - Repeat texture (GL_REPEAT)
  - repeat and mirror texture (GL_MIRRORED_REPEAT)
  - repeat only texture edge/border values (GL_CLAMP_TO_EDGE)
  - use a colored border (GL_CLAMP_TO_BORDER)
```c
// for s-axis (x axis)
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
// for t-axis (y axis)
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
```
- stb_image: single file to include
```c
//required
#define STB_IMAGE_IMPLEMENTATION
// image flip might be required
stbi_set_flip_vertically(true);
//load path
unsigned char *pData = stbi_load("path.jpg", pWidth, pHeight, pBitDepth,0);
```
- texture samplers
  - texture units are used by samplers to access texture data
  - in shaders sampler2D type is used with texture function
```c
//shader code:
//
//textureSampler: sampler2D object
//TexCoord : (interpolated)  texture coordinates in fragment shader
texture(textureSampler, TexCoord);
```
- set sampler2D variables for texture unit to access
```c
glUniform1i(uniformTextureSampler, textureUnitNumber);
```
- texture units: usually many
  - named by GL_TEXTUREX
```c
glActiveTexture(GL_TEXTURE0);
glBindTexture(GL_TEXTURE_2D textureId);
```
- example
```c
//assume you save texture coordinates after vertices
GLfloat data[] = {
  //x,y,z, s|u,t|v
  1,1,1, 0.0, 0.0
  //...
};
//then for vertices
    glVertexAttribPointer(
      0, 
      3, // number of values per vertex
    GL_FLOAT,
    GL_FALSE, 
    sizeof(float)*5, //data stride
    0);
    // Enable Position Attribute
    glEnableVertexAttribArray(0);

//for textures: offset after vertices (*3)
    glVertexAttribPointer(
      1, 
      2,  // number of values per texel
    GL_FLOAT, 
    GL_FALSE, 
    sizeof(float)*5, (void*)sizeof(float)*3);
    glEnableVertexAttribArray(1);
```
```c
```
```c
```
```c
```
```c
```
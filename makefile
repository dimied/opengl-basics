
# make
# sudo make install
SHADER_FILES = glsl.c gl_errors.c gl_shaders.c

all: clean doall # doopt

doall:
	g++ -I./ -Os main.cpp glfw/glfw_helper.c opengl3.c ${SHADER_FILES} \
	-lglfw3 -ldl -lm -pthread -lGLEW -lGLU -lGL -lrt -lXrandr -lXxf86vm \
	-lXi -lXinerama -lX11 -o example

clean:
	echo "hallo"
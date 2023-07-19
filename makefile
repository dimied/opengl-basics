
GLSL_FILES = glsl.c glsl_util.c

SHADER_FILES = gl_errors.c gl_shaders.c

EXAMPLES_FILES = examples.c

all: clean doall # doopt

doall:
	g++ -I./ -Os main.cpp glm_util.cpp glfw/glfw_helper.c opengl3.c \
	${GLSL_FILES} ${SHADER_FILES} \
	${EXAMPLES_FILES} \
	-lglfw3 -ldl -lm -pthread -lGLEW -lGLU -lGL -lrt -lXrandr -lXxf86vm \
	-lXi -lXinerama -lX11 -o example

clean:
	echo "hallo"
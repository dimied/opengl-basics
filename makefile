# On Ubuntu you can do the following to install GLEW:
# sudo apt-get install libglew-dev
#
# To install GLFW
# git clone https://github.com/glfw/glfw.git
# cd glfw
# cmake .
# libxrandr libxinerama development files might be missing
# Ubuntu: sudo apt install libxrandr-dev libxinerama-dev libxcursor-dev libxi-dev
# make
# sudo make install

all: clean doall # doopt

doall:
	gcc -Os -o example main.c glfw/glfw_helper.c -lglfw3 -ldl -lm -pthread -lGLU -lGL -lrt -lXrandr -lXxf86vm -lXi -lXinerama -lX11

clean:
	echo "hallo"
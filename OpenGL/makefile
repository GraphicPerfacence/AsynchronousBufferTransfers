### KNIGHT 2015.8.25 21:50
##///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
##// makefile is composed of:
##//  target: dependencies
##//  [tab] system command

# DEBUG :The debugging flag. This is -g in both g++ and cxx. The purpose of the flag is to include debugging information into the executable, so that you can use utilities such as gdb to debug the code.
# LFLAGS: The flags used in linking. As it turns out, you don't need any special flags for linking. The option listed is "-Wall" which tells the compiler to print all warnings. But that's fine. We can use that

##///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

## SHELL = /bin/sh
CC = gcc
CXX = g++
RM = rm -f
YACC = bison -y
CDEBUG  = -g
##///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#extern include and libs frameworks
INCLUDES =  -I /Users/glp/Documents/3Dirty/SpartanJ-soil2/src/  -I /usr/local/include/
LIBS =-lGLEW.1.12.0 -lglfw3.3.1 
CFLAGS = -c -Wall $(DEBUG)  -I. $(INCLUDES)
LDFLAGS = -Wall $(DEBUG)  -L/usr/local/lib \
-L/usr/local/Cellar/glew/1.12.0/lib -L/usr/local/Cellar/glfw3/3.1.1/lib \
-framework CoreFoundation -framework OpenGL -framework GLUT


LDFLAGS +=  /Users/glp/Documents/3Dirty/SpartanJ-soil2/lib/macosx/libsoil2-debug.a
##///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
# INSTALL = /usr/local/bin/install -c
# INSTALLDATA = /usr/local/bin/install -c -m 644
##///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

prefix = /usr/local
binprefix = 
# The directory to install tar in.
bindir = $(prefix)/bin
# The directory to install the info files in.
infodir = $(prefix)/info

##///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
DIR_INC = ./include 
DIR_SRC = ./src
DIR_OBJ = ./obj
DIR_BIN = ./bin
ROOT_DIR = ${shell pwd}
SUBDIRS = ${DIR_SRC}

TARGET = main
BIN_TARGET = ${DIR_BIN}/${TARGET}
##///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

SOURCES = ${wildcard ${DIR_SRC}/*.cpp}
OBJECTS = $(patsubst %.cpp,${DIR_OBJ}/%.o,$(notdir ${SOURCES})) 
CFLAGS += ${DIR_INC}

TARGET = main
BIN_TARGET = ${DIR_BIN}/${TARGET}

${BIN_TARGET}:${OBJECTS}
	$(CXX) $(LDFLAGS) $(OBJECTS) -o $@ $(LIBS)
${DIR_OBJ}/%.o:${DIR_SRC}/%.cpp
	$(CXX)  $(CFLAGS) -c $< -o $@ 
# .PHONY”表示，clean是个伪目标文件
clean:
	 $(RM) ${DIR_OBJ}/*.o ${BIN_TARGET}
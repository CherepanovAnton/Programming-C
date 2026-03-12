.PHONY: all clean

CC = gcc
INCLUDES = -I ./include
TARGET = main

all: main

$(TARGET): FuncLab12.so
	${CC} src/main.c -o $(TARGET) -L. -lFuncLab12 -Wl,-rpath,. ${INCLUDES}
	
FuncLab12.so: src/FuncLab12.c
	${CC} -shared -fPIC -o libFuncLab12.so src/FuncLab12.c ${INCLUDES}

clean:
	rm -f *.so *.o *.a main 
# Неработает rm -f *.{so,o,a} main 


# Target executable, and list of object files needed to compile it
TARGET = polygon
OBJS = polygon.o


# Normal compilation, all debugging macros active
CXXFLAGS = `pkg-config --cflags playerc++`  -Wall -g


# Libraries, inluding the -l flag for the linker.
LIBS = `pkg-config --libs playerc++`


# Build the target
${TARGET}: ${OBJS}
	${CXX} -o ${TARGET} ${OBJS} ${LIBS}


# Remove the object files and the executable
clean:
	${RM} ${TARGET} ${OBJS}

# Remove core files and emacs backups
superclean: clean
	${RM} core.* *~

# Remove any data files by adding them in to this rule
ultraclean: superclean

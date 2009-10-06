# Target executable, and list of object files needed to compile it
TARGET1 = avoid 
OBJS1 = vector.o robotMove.o sensorScan.o avoid.o 

TARGET2 = seeker
OBJS2 = vector.o robotMove.o sensorScan.o seeker.o 



# Normal compilation, all debugging macros active
CXXFLAGS = `pkg-config --cflags playerc++`  -Wall -g

# Libraries, inluding the -l flag for the linker.
LIBS = `pkg-config --libs playerc++`


all: ${TARGET1} ${TARGET2}

# Build the targets
${TARGET1}: ${OBJS1}
	${CXX} -o ${TARGET1} ${OBJS1} ${LDFLAGS} ${LIBS}

${TARGET2}: ${OBJS2}
	${CXX} -o ${TARGET2} ${OBJS2} ${LDFLAGS} ${LIBS}


# Remove the object files and the executable
clean:
	${RM} ${TARGET1} ${OBJS1} ${TARGET2} ${OBJS2}

# Remove core files and emacs backups
superclean: clean
	${RM} core.* *~


# Remove any data files by adding them in to this rule
ultraclean: superclean

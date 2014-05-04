CXX = g++
CXXFLAGS = -g -Wall -MMD
EXEC = quadris
OBJECTS = main.o board.o cell.o block.o blockType.o window-v2.o
DEPENDS = ${OBJECTS:.o=.d}

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC} -lX11

-include ${DEPENDS}

.PHONY: clean

clean:
	rm ${OBJECTS} ${EXEC} ${DEPENDS}

SRCS = $(wildcard *.cpp)
OBJS = $(SRCS:%.cpp=%.o)
HDRS = $(wildcard *.h)
CFLAGS = -std=c++11

CPP = g++

.PHONY: clean
	
default: program

program: ${OBJS}
	${CPP} ${CFLAGS} $^ -o program
	
%.o: %.cpp ${HDRS}
	${CPP} ${CFLAGS} -c $<
	
clean: 
	-@rm -f program
	-@rm -f ${OBJS}
	


	


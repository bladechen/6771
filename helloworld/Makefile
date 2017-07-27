CPPFLAGS := -std=c++14 -Wall -Werror -O2
CC := g++-4.9
SRC_FILE := $(wildcard *.cpp)
OBJ_FILE := $(SRC_FILE:.cpp=.o)
INCLUDES := -I./
LIBS =
all: hello_world


# %.o: %.cpp
# 	$(CC)  $(CPPFLAGS) $(INCLUDES) -c $< -o $@
-include $(SRC_FILE:.cpp=.d)
%.d: %.cpp
	@set -e; rm -f $@; \
    $(CC) -MM $(CPPFLAGS)  $< > $@.$$$$; \
    sed 's,\($*\)\.o[ :]*,\1.o $@ : ,g' < $@.$$$$ > $@; \
    rm -f $@.$$$$

hello_world: $(OBJ_FILE)
	$(CC) $^ -o $@   $(LIBS)

.PHONY:clean
clean:
	-rm -f $(OBJ_FILE) hello_world *.d *.o

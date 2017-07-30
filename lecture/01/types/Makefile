CPPFLAGS := -std=c++14 -Wall -Werror -O2
LDFLAGS := #-m32

ifeq ($(ARCH),32)
	CPPFLAGS += -m32
	LDFLAGS += -m32
else
	CPPFLAGS += -m64
endif


CC := g++-4.9
SRC_FILE := $(wildcard *.cpp)
OBJ_FILE := $(SRC_FILE:.cpp=.o)
INCLUDES := -I./
LIBS =
TARGET = a.out

all: $(TARGET)
	./a.out

all32:
	make -e ARCH=32

-include $(SRC_FILE:.cpp=.d)
%.d: %.cpp
	@set -e; rm -f $@; \
    $(CC) -MM $(CPPFLAGS)  $< > $@.$$$$; \
    sed 's,\($*\)\.o[ :]*,\1.o $@ : ,g' < $@.$$$$ > $@; \
    rm -f $@.$$$$

$(TARGET): $(OBJ_FILE)
	$(CC) $^ -o $@ $(LIBS) $(LDFLAGS)

.PHONY:clean
clean:
	-rm -f $(OBJ_FILE) $(TARGET) *.d *.o

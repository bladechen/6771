CPPFLAGS :=   -ggdb3 -std=c++14 -Wall -Werror -O2
LDFLAGS := #-m32

ifeq ($(ARCH),32)
	CPPFLAGS += -m32
	LDFLAGS += -m32
else
endif


CC := g++-4.9
SRC_FILE :=  main.cpp BucketSort.cpp
OBJ_FILE := $(SRC_FILE:.cpp=.o)
INCLUDES := -I./
LIBS = -pthread
TARGET = bucket

all: $(TARGET)
	# g++ -pg main.o BucketSort.o -o bucket -pthread


all32:
	make -e ARCH=32

-include $(SRC_FILE:.cpp=.d)
%.d: %.cpp
	@set -e; rm -f $@; \
    $(CC) -MM $(CPPFLAGS)  $< > $@.$$$$; \
    sed 's,\($*\)\.o[ :]*,\1.o $@ : ,g' < $@.$$$$ > $@; \
    rm -f $@.$$$$

$(TARGET): $(OBJ_FILE)
	$(CC) $^    -o $@ $(LIBS) $(LDFLAGS)

.PHONY:clean
clean:
	-rm -f $(OBJ_FILE) $(TARGET) *.d *.o

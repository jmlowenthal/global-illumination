TARGET=gi

CC=g++ -std=c++11
RM=rm -f
DEBUG=-g

DEPFLAGS = -MT $@ -MMD -MP -MF $*.dep.tmp

CFLAGS=$(shell bash config --cflags)
LFLAGS=$(shell bash config --lflags)
LIBS=$(shell bash config --libs)

COMPILE = $(CC) $(DEPFLAGS) $(CFLAGS) -c -o $@
POSTCOMPILE = mv -f $*.dep.tmp $*.dep

SRCS=$(shell find src -type f -name *.cpp)
OBJS=$(subst .cpp,.o,$(SRCS))
DEPS=$(subst .cpp,.dep,$(SRCS))

.PHONY: all
all: $(TARGET)

%.o: %.cpp
%.o: %.cpp %.dep
	$(COMPILE) $<
	$(POSTCOMPILE)

%.dep: ;

$(TARGET): $(OBJS)
	$(CC) $(DEBUG) $(LFLAGS) -o $(TARGET) $(OBJS) $(LIBS)

clean:
	$(RM) $(OBJS)

distclean: clean
	$(RM) $(DEPS)

.PRECIOUS: %.dep

-include $(patsubst %,%.dep,$(basename $(SRCS)))


TARGET=global-illumination

CC=g++ -std=c++11
RM=rm -f
DEPDIR=.depend
OBJDIR=build

# Copy source folder structure to build and depend stores
$(shell mkdir -p $(DEPDIR) >/dev/null)
$(shell find src -type d -exec mkdir -p -- $(DEPDIR)/{} \;)
$(shell mkdir -p $(OBJDIR) >/dev/null)
$(shell find src -type d -exec mkdir -p -- $(OBJDIR)/{} \;)

DEPFLAGS = -MT $@ -MMD -MP -MF $(DEPDIR)/$*.dep.tmp

CFLAGS=$(shell bash config --cflags)
LFLAGS=$(shell bash config --lflags)
LIBS=$(shell bash config --libs)

COMPILE = $(CC) $(DEPFLAGS) $(CFLAGS) -c -o $@
POSTCOMPILE = mv -f $(DEPDIR)/$*.dep.tmp $(DEPDIR)/$*.dep

SRCS=$(shell find src -type f -name \*.cpp)
OBJS=$(addprefix $(OBJDIR)/,$(subst .cpp,.o,$(SRCS)))

.PHONY: all
all: $(TARGET)

$(OBJDIR)/%.o: %.cpp
$(OBJDIR)/%.o: %.cpp $(DEPDIR)/%.dep config
	$(COMPILE) $<
	$(POSTCOMPILE)

%.dep: ;

$(TARGET): $(OBJS) config
	$(CC) $(DEBUG) $(LFLAGS) -o $(TARGET) $(OBJS) $(LIBS)

config:;

clean:
	$(RM) -R $(OBJDIR)

distclean: clean
	$(RM) -R $(DEPDIR)

.PRECIOUS: %.dep

-include $(patsubst %,$(DEPDIR)/%.dep,$(basename $(SRCS)))


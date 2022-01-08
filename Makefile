CC=gcc
CFLAGS=-Wall

VERBOSE=TRUE

ifeq ($(VERBOSE), TRUE)
	HIDE=
else
	HIDE=@
endif

PROJDIR:=$(realpath $(CURDIR))
SRCDIR:=$(PROJDIR)/src
OBJDIR:=$(PROJDIR)/obj
DEPSDIR:=$(PROJDIR)/deps
BINDIR:=$(PROJDIR)/bin
DATADIR:=$(PROJDIR)/data
DIRS:=$(SRCDIR) $(OBJDIR) $(BINDIR) $(DATADIR) $(DEPSDIR)

SRCS:=$(wildcard $(SRCDIR)/*.c)
OBJS:=$(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.o, $(SRCS))
DEPS:=$(patsubst $(SRCDIR)/%.c, $(DEPSDIR)/%.d, $(SRCS))
BIN:=$(BINDIR)/main

$(info $(shell mkdir -p $(DIRS)))

.PHONY: all clean dirs

all: dirs $(BIN)

# dir:
# 	@mkdir -p $(DIRS)

$(BIN): $(OBJS) $(DEPS)
	$(HIDE)$(CC) $(CFLAGS) $(OBJS) -o $@ 

$(OBJDIR)/%.o: $(SRCDIR)/%.c $(DEPSDIR)/%.d
	$(HIDE)$(CC) $(CFLAGS) -c -o $@ $<

$(DEPSDIR)/%.d: $(SRCDIR)/%.c
	$(HIDE)$(CC) -MM -MG -MF $@ $<

clean:
	$(HIDE)rm -rf $(OBJDIR) $(BINDIR) $(DATADIR) $(DEPSDIR)

-include $(DEPS)

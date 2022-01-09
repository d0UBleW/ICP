CC=gcc
CFLAGS=-Wall -Wextra -Wshadow

VERBOSE=FALSE

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
DIRS:=$(OBJDIR) $(BINDIR) $(DATADIR) $(DEPSDIR)

SRCS:=$(wildcard $(SRCDIR)/*.c)
OBJS:=$(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.o, $(SRCS))
DEPS:=$(patsubst $(SRCDIR)/%.c, $(DEPSDIR)/%.d, $(SRCS))
BIN:=$(BINDIR)/main

.PHONY: all clean

all: $(BIN)
	$(HIDE)mkdir -p $(DATADIR)

$(BIN): $(OBJS) $(DEPS) | $(BINDIR)
	$(HIDE)$(CC) $(CFLAGS) $(OBJS) -o $@ 

$(OBJDIR)/%.o: $(SRCDIR)/%.c $(DEPSDIR)/%.d | $(OBJDIR)
	$(HIDE)$(CC) $(CFLAGS) -c -o $@ $<

$(DEPSDIR)/%.d: $(SRCDIR)/%.c | $(DEPSDIR)
	$(HIDE)$(CC) -MM -MG -MF $@ $<

$(DEPSDIR):
	$(HIDE)mkdir -p $@

$(OBJDIR):
	$(HIDE)mkdir -p $@

$(BINDIR):
	$(HIDE)mkdir -p $@

clean:
	$(HIDE)rm -rf $(DIRS)

-include $(DEPS)

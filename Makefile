objdir := obj
bindir := bin
srcs := $(wildcard src/*.c) $(wildcard src/*/*.c)
objs := $(patsubst %.c,$(objdir)/%.o,$(notdir $(srcs)))
deps := $(objs:%.o=%.d)
target := raytracer

VPATH := $(sort $(dir $(srcs)))
CPPFLAGS = -MD
CFLAGS := -Wall -Werror -Iinclude
LDFLAGS :=
LDLIBS := -lm
CC := gcc
RM := rm -df

.PHONY: all
all: $(bindir)/$(target)

$(bindir)/$(target): $(objs) | $(bindir)
	$(CC) $^ -o $@ $(LDFLAGS) $(LDLIBS)

$(bindir):
	@mkdir bin

$(objdir)/%.o: %.c | $(objdir)
	$(CC) -c $(CFLAGS) $(CPPFLAGS) $< -o $@

$(objdir):
	@mkdir obj

.PHONY: clean
clean:
	$(RM) $(objdir)/* $(bindir)/*
	$(RM) $(objdir) $(bindir)

.PHONY: echo_%
echo_%:
	@echo $($*)

-include $(deps)

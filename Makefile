objdir := obj
bindir := bin
srcs := $(wildcard src/*.c) $(wildcard src/*/*.c)
objs := $(patsubst %.c,$(objdir)/%.o,$(notdir $(srcs)))
deps := $(objs:%.o=%.d)
target := raytracer

VPATH := $(sort $(dir $(srcs))) # search in all source directories
CPPFLAGS = -MT $@ -MMD -MP -MF $(@:%.o=%.d) # generate dependency target files
CFLAGS := -Wall -Werror -std=c99 -Iinclude
LDFLAGS :=
LDLIBS := -lm
CC := gcc

# platform-specific configuration
ifeq ($(OS),Windows_NT)
	LDLIBS += -lgdi32
	RM := del /q
else
	LDLIBS += -ldl -lpthread
	RM := rm -r
endif

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
	$(RM) obj bin

.PHONY: echo_%
echo_%:
	@echo $($*)

-include $(deps)
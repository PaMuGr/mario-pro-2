CXX = g++
CXXFLAGS = -std=c++17
ifeq "$(MODE)" "release"
CXXFLAGS += -O3
else
CXXFLAGS += -g3
endif

CCFILES := $(wildcard *.cc)
HHFILES := $(wildcard *.hh)
OBJS := $(patsubst %.cc,%.o,$(CCFILES))
TAR_FILE = mario-pro-2-$(USER)-$(shell date +%s).tgz

# Detect macOS and set linker flags
UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Darwin)
  LDFLAGS = -framework Cocoa -framework CoreGraphics
else
  LDFLAGS = -lX11
endif

mario_pro_2: $(OBJS)
	$(CXX) -g3 -o mario_pro_2 $(OBJS) $(LDFLAGS)

$(OBJS): $(HHFILES)
window.o: window.cc geometry.hh fenster.h

tgz: clean
	tar -czf $(TAR_FILE) Makefile *.cc *.hh fenster.h .vscode .clang-format Doxyfile html latex

clean:
	rm -f mario_pro_2 $(OBJS)

.PHONY: clean tgz
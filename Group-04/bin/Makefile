BUILD_PROFILE=release
CXX_FLAGS_all ?= -std=c++23 -Wextra -Wall -I./include -I../lib/include

build: BUILD_FLAGS=-L../lib/target/$(BUILD_PROFILE) -lcset
build:
	BUILD_PROFILE=$(BUILD_PROFILE) CXX_FLAGS_all="$(CXX_FLAGS_all)" BUILD_FLAGS="$(BUILD_FLAGS)" $(MAKE) -f Makefile.logic
	
debug: BUILD_PROFILE=debug
debug: build

clean:
	$(MAKE) -f Makefile.logic clean

format:
	$(MAKE) -f Makefile.logic format

install:
	BUILD_PROFILE=$(BUILD_PROFILE) $(MAKE) -f Makefile.logic install

install_debug: BUILD_PROFILE=debug
install_debug: install

remove:
	$(MAKE) -f Makefile.logic remove


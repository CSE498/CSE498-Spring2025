BUILD_PROFILE=release

build:
	BUILD_PROFILE=$(BUILD_PROFILE) $(MAKE) -f Makefile.logic
	
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


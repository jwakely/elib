GCC_PATH := $(HOME)/gcc/latest
CXX := $(GCC_PATH)/bin/g++

ELIB_CPPFLAGS := -DELIB_FILESYSTEM_UNIT_TEST_PATH='"$(realpath $(PWD)/..)"' -DELIB_ROOT_PATH='"$(realpath $(PWD)/../../../..)"'
CPPFLAGS := -I.. -I../../../.. $(ELIB_CPPFLAGS)
CXXFLAGS := -std=c++11
LDFLAGS := -Wl,-rpath,$(GCC_PATH)/lib64
LDLIBS := -lstdc++fs

PWD := $(shell pwd)
TESTS := $(wildcard *.pass.cpp)

all: $(basename $(TESTS))
	@for i in $^ ; do ./$$i ; done

clean:
	rm -f $(basename $(TESTS)) core.*

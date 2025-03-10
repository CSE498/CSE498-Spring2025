# List of folders containing test files
TEST_FOLDERS = Graph GraphPosition Distribution

BUILD_CPP_FILES = ../../Group-01/Graph/Vertex.cpp ../../Group-01/Graph/Graph.cpp ../../Group-01/GraphPosition/GraphPosition.cpp ../../Group-01/Graph/Edge.cpp

# Find all test files across the specified folders
TEST_NAMES = $(basename $(notdir $(wildcard $(addsuffix /*.cpp, $(TEST_FOLDERS)))))

# -O3	  -Wl,--stack,8388608 -ftrack-macro-expansion=0
FLAGS = -std=c++20 -g -pthread -Wall -Wextra -I../../ -DCATCH_CONFIG_MAIN

default: test

cov-%: %.cpp ../../third-party/Catch/single_include/catch2/catch.hpp
	$(CXX) $(FLAGS) $< -o $@.out
	#echo "running $@.out"
	# execute test
	./$@.out
	llvm-profdata merge default.profraw -o default.profdata
	llvm-cov show ./$@.out -instr-profile=default.profdata > coverage_$@.txt
	python ../../third-party/force-cover/fix_coverage.py coverage_$@.txt

test-prep:
	mkdir -p temp

test-%: 
	$(CXX) $(FLAGS) $(BUILD_CPP_FILES) $(shell find $(TEST_FOLDERS) -name $(@:test-%=%.cpp)) -o $@.out
	./$@.out

# Test in debug mode without pointer tracker
test: test-prep $(addprefix test-, $(TEST_NAMES))
	rm -rf test*.out

test-watch:
	fswatch -r --event Updated -o $(TEST_FOLDERS) $(shell printf "../../Group-01/%s " $(TEST_FOLDERS)) | while read; do make test; done

../../third-party/Catch/single_include/catch2/catch.hpp:
	git submodule init
	git submodule update

clean:
	rm -f *.out
	rm -f *.o
	rm -f *.gcda
	rm -f *.gcno
	rm -f *.info
	rm -f *.gcov
	rm -f ./Coverage*
	rm -rf ./temp
	rm -rf ./**.dSYM
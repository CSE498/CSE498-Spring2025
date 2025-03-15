TEST_NAMES = AnnotatedWrapperAdvancedTest AuditedPointerAdvancedTest

# Compilation Flags
# Statically linking or else it wont work
FLAGS = -std=c++20 -g -pthread -Wall -Wextra -I../../ -DCATCH_CONFIG_MAIN -static-libgcc -static-libstdc++

# Default target
default: test

# Compilation rule for coverage testing
cov-%: %.cpp ../../third-party/Catch/single_include/catch2/catch.hpp
	$(CXX) $(FLAGS) $< -o $@.out
	./$@.out
	llvm-profdata merge default.profraw -o default.profdata
	llvm-cov show ./$@.out -instr-profile=default.profdata > coverage_$@.txt
	python ../../third-party/force-cover/fix_coverage.py coverage_$@.txt

# Prepare test directory
test-prep:
	mkdir -p temp

# Compilation and execution rule for tests
test-%: %.cpp ../../third-party/Catch/single_include/catch2/catch.hpp
	$(CXX) $(FLAGS) $< -o $@.out
	./$@.out

# Run all tests
test: test-prep $(addprefix test-, $(TEST_NAMES))
	rm -rf test*.out

# Coverage build
coverage: FLAGS := -std=c++20 -pthread -g -Wall -Wno-unused-function -I../../coverage_source/ -I../../ -I../../third-party/cereal/include/ -DEMP_TRACK_MEM -Wnon-virtual-dtor -Wcast-align -Woverloaded-virtual -ftemplate-backtrace-limit=0 -fprofile-instr-generate -fcoverage-mapping -fno-inline -fno-elide-constructors -O0 -DCATCH_CONFIG_MAIN
coverage: test-prep $(addprefix cov-, $(TEST_NAMES))

# Optimized build
opt: FLAGS := -std=c++20 -pthread -DNDEBUG -O3 -Wno-unused-function -I../../include/ -I../../third-party/cereal/include/ -I../../ -DCATCH_CONFIG_MAIN
opt: test-prep $(addprefix test-, $(TEST_NAMES))
	rm -rf test*.out

# Full debug mode with memory tracking
fulldebug: FLAGS := -std=c++20 -pthread -g -Wall -Wno-unused-function -I../../include/ -I../../third-party/cereal/include/ -I../../ -pedantic -DEMP_TRACK_MEM -Wnon-virtual-dtor -Wcast-align -Woverloaded-virtual -ftemplate-backtrace-limit=0 -DCATCH_CONFIG_MAIN
fulldebug: test-prep $(addprefix test-, $(TEST_NAMES))
	rm -rf test*.out

# Strict mode with extra warnings
cranky: FLAGS := -std=c++20 -pthread -g -Wall -Wno-unused-function -I../../include/ -I../../third-party/cereal/include/ -I../../ -pedantic -DEMP_TRACK_MEM -Wnon-virtual-dtor -Wcast-align -Woverloaded-virtual -Wconversion -Weffc++ -DCATCH_CONFIG_MAIN
cranky: test-prep $(addprefix test-, $(TEST_NAMES))
	rm -rf test*.out

# Ensure Catch2 is initialized
../../third-party/Catch/single_include/catch2/catch.hpp:
	git submodule init
	git submodule update

# Clean generated files
clean:
	rm -f *.out
	rm -f *.o
	rm -f *.gcda
	rm -f *.gcno
	rm -f *.info
	rm -f *.gcov
	rm -f ./Coverage*
	rm -rf ./temp

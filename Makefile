# Compiler
CXX = clang++

# Included C++ Files
INCLUDE = -Iinclude \
		  -I/usr/local/include/c++ \
		  -I/usr/include \

# Included C++ Libraries
LIBS = -L/usr/local/lib/c++ \
	   -L/usr/lib \
       -lgtest \
       -lgtest_main \
       -lgmock \
       -lgmock_main \
       -lpthread \

# Flags
CXXFLAGS = -Wall -g -std=c++23 -fPIC
LDFLAGS = -shared
VALGRIND_FLAGS = -s --tool=memcheck --leak-check=yes --track-origins=yes

# Library Files
LIB_HDR = singly_list.hpp

# Test Files
TEST_SRC = singly_list_tests.cpp
TEST_ASM = singly_list_tests.s
TEST_OBJ = singly_list_tests.o
TEST_EXE = singly_list_tests.exe

# Main Files
MAIN_SRC = singly_list_main.cpp
MAIN_ASM = singly_list_main.s
MAIN_OBJ = singly_list_main.o
MAIN_EXE = singly_list_main.exe

# Compile the source files into object files
%.o: %.cpp $(LIB_HDR)
	$(CXX) $(CXXFLAGS) $(INCLUDE) -c $< -o $@

# Compile the source files into assembly files
%.s: %.cpp $(LIB_HDR)
	$(CXX) -S $(CXXFLAGS) $(INCLUDE) -c $< -o $@

# Create the test suite
$(TEST_EXE): $(TEST_OBJ)
	$(CXX) $(CXXFLAGS) -Wl,-rpath,/usr/local/lib/c++ -o $(TEST_EXE) $(TEST_OBJ) $(LIBS)

# Create the main suite
$(MAIN_EXE): $(MAIN_OBJ)
	$(CXX) $(CXXFLAGS) -Wl,-rpath,/usr/local/lib/c++ -o $(MAIN_EXE) $(MAIN_OBJ) $(LIBS)

# Install rule
install:
	sudo cp $(LIB_HDR) /usr/local/include/c++

# Uninstall rule
uninstall:
	sudo rm -f /usr/local/include/c++/$(LIB_HDR)

# Assembly rule
assembly: $(MAIN_ASM) $(TEST_ASM)

# Test suite rules
build_tests: $(TEST_EXE)

run_tests: $(TEST_EXE)
	./$(TEST_EXE)

valgrind_tests: $(TEST_EXE)
	valgrind $(VALGRIND_FLAGS) ./$(TEST_EXE)

# Main rules
build_main: $(MAIN_EXE)

run_main: $(MAIN_EXE)
	./$(MAIN_EXE)

gdb_main: $(MAIN_EXE)
	gdb $(MAIN_EXE)

valgrind_main: $(MAIN_EXE)
	valgrind $(VALGRIND_FLAGS) ./$(MAIN_EXE)

# Rule to clean up build files
clean: rm -f *.exe *.s

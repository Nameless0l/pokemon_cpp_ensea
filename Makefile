CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -g -Iincludes
SFML_LIBS = -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

# Toutes les classes du projet (tout src/*.cpp sauf le main)
CLASSES = $(filter-out src/main.cpp,$(wildcard src/*.cpp))
HEADERS = $(wildcard includes/*.hpp)

# Executable par fichier tests/test_*.cpp
TEST_SRCS = $(wildcard tests/test_*.cpp)
TESTS = $(patsubst tests/%.cpp,bin/%.exe,$(TEST_SRCS))

.PHONY: all run test sanitize valgrind clean

all: bin/main.exe

bin/main.exe: src/main.cpp $(CLASSES) $(HEADERS)
	mkdir -p bin
	$(CXX) $(CXXFLAGS) src/main.cpp $(CLASSES) -o $@ $(SFML_LIBS)

# Regle generique : bin/test_xxx.exe est construit depuis tests/test_xxx.cpp
bin/%.exe: tests/%.cpp $(wildcard tests/*.hpp) $(CLASSES) $(HEADERS)
	mkdir -p bin
	$(CXX) $(CXXFLAGS) -Itests $< $(CLASSES) -o $@ $(SFML_LIBS)

run: bin/main.exe
	./bin/main.exe

test: $(TESTS)
	@for t in $(TESTS); do echo "=== $$t ==="; ./$$t || exit 1; done

# Verification des fuites memoire et des comportements indefinis
sanitize: $(CLASSES) $(HEADERS)
	mkdir -p bin
	@for src in $(TEST_SRCS); do \
		out=bin/sanitize_$$(basename $$src .cpp).exe; \
		echo "=== build $$out ==="; \
		$(CXX) $(CXXFLAGS) -fsanitize=address,undefined -Itests $$src $(CLASSES) -o $$out $(SFML_LIBS) || exit 1; \
		./$$out || exit 1; \
	done

valgrind: $(TESTS)
	@for t in $(TESTS); do \
		echo "=== valgrind $$t ==="; \
		valgrind --leak-check=full --error-exitcode=1 ./$$t || exit 1; \
	done

clean:
	rm -rf bin

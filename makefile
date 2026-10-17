CC      := g++
CFLAGS  := -std=c++17 -Wall -Wextra -Iinclude -I.
LIBS    := -lGLEW -lglfw -lGL -lX11 -lpthread -ldl -lXrandr -lXi

MAIN    := main.cpp
# Busca recursivamente todos os .cpp dentro de src/ e suas subpastas
SOURCES := $(shell find src -name "*.cpp")
TARGET  := out

.PHONY: compile debug clean compile_commands

compile_commands:
	@printf '[\n' > compile_commands.json; \
	first=1; \
	for f in main.cpp $(shell find src -name "*.cpp"); do \
		[ $$first -eq 1 ] || printf ',\n' >> compile_commands.json; \
		first=0; \
		printf '  {\n    "directory": "%s",\n    "command": "g++ %s -c %s",\n    "file": "%s"\n  }' \
			"$(CURDIR)" "$(CFLAGS)" "$$f" "$$f" >> compile_commands.json; \
	done; \
	printf '\n]\n' >> compile_commands.json; \
	echo "Generated compile_commands.json"

compile:
	$(CC) $(CFLAGS) $(MAIN) $(SOURCES) -o $(TARGET) $(LIBS)
	@echo "Built $(TARGET)" && ./$(TARGET)

debug:
	$(CC) $(CFLAGS) -g -O0 $(MAIN) $(SOURCES) -o $(TARGET) $(LIBS)
	@echo "Built $(TARGET) (debug)"

clean:
	rm -f $(TARGET) compile_commands.json
	@echo "Cleaned"
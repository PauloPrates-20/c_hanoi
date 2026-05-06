srcs = $(shell find -name "*.c")
headers = $(shell find -include -name "*.h")

all: build/main

build/main: $(srcs)
	@mkdir -p build
	gcc -Wall -Wextra -o build/main $(srcs) -I include -L lib -lraylib -lgdi32 -lwinmm
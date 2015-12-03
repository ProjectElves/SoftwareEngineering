CFLAGS = -Wall -Wextra -Wfloat-equal -pedantic -std=c99 -lm -lSDL2 -lSDL2_image -lSDL2_mixer
INCS = $(TARGET).h input.h grid.h entity.h base.h bgame.h display.h
TARGET = game
SOURCES =  encryptionNew.c grid.c input.c display.c entity.c bgame.c $(TARGET).c
LIBS =  -L/libs
CC = gcc

all: $(TARGET)

$(TARGET): $(SOURCES) $(INCS)
	$(CC) $(SOURCES) -o $(TARGET) $(CFLAGS) $(LIBS) -g

clean:
	rm -f $(TARGET)

run: all
	./$(TARGET)

push:
	git commit -a -m $$(date +%d-%m-%Y/%H:%M)
	git push "https://github.com/ProjectElves/SoftwareEngineering"
pull:
	git pull "https://github.com/ProjectElves/SoftwareEngineering"
debug:
	valgrind ./game

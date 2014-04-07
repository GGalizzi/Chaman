CC=g++
CFLAGS=-g -c -Wall -Wextra -std=c++11

OBJS=obj/main.o obj/Game.o obj/Entity.o obj/Map.o obj/Tile.o obj/Mob.o obj/Item.o obj/Inventory.o

bin/chaman: $(OBJS)
	mkdir -p bin
	$(CC) -g -o $@ -Wall -Wextra -std=c++11 -lsfml-graphics -lsfml-window -lsfml-system $(OBJS)

obj/main.o: src/main.cc
	mkdir -p obj
	$(CC) $(CFLAGS) -o $@ $<

obj/%.o: src/%.cc src/%.h
	mkdir -p obj
	$(CC) $(CFLAGS) -o $@ $<

clean:
	rm -rf obj/*.o
	rm -rf bin

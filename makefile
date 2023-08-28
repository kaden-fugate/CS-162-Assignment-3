CC=g++
EXE_FILE=fish_run

all: $(EXE_FILE)

$(EXE_FILE): card_class.o deck_class.o hand_class.o player_class.o game_class.o one_function.o fish_main.cpp
	$(CC) card_class.o deck_class.o hand_class.o player_class.o game_class.o one_function.o fish_main.cpp -o $(EXE_FILE)

debug: card_class.o deck_class.o hand_class.o player_class.o game_class.o one_function.o fish_main.cpp
	$(CC) card_class.o deck_class.o hand_class.o player_class.o game_class.o one_function.o fish_main.cpp -g -o $(EXE_FILE)

card_class.o: card_class.cpp cardheader.h
	$(CC) -c card_class.cpp

deck_class.o: deck_class.cpp deckheader.h cardheader.h 
	$(CC) -c deck_class.cpp

hand_class.o: hand_class.cpp handheader.h
	$(CC) -c hand_class.cpp

player_class.o: player_class.cpp playerheader.h
	$(CC) -c player_class.cpp

game_class.o: game_class.cpp gameheader.h
	$(CC) -c game_class.cpp

one_function.o: one_function.cpp one_header.h
	$(CC) -c one_function.cpp

clean:
	rm -f *.o $(EXE_FILE)

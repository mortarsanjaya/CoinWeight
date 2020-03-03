CPP = g++
CFLAGS = -g -std=c++14 -Wall -MMD

all: coinweight

coinweight: coinset.o computerhard.o game.o human.o main.o player.o x11graphics.o
	$(CPP) $(CFLAGS) -o coinweight coinset.o computerhard.o game.o human.o main.o player.o x11graphics.o -I /usr/include/X11 -L /usr/X11/lib -lX11

coinset.o: coinset.cpp coinset.hpp weighing.hpp
	$(CPP) $(CFLAGS) -c coinset.cpp

computerhard.o: computerhard.cpp computerhard.hpp player.hpp game.hpp \
  coinset.hpp weighing.hpp
	$(CPP) $(CFLAGS) -c computerhard.cpp

game.o: game.cpp game.hpp coinset.hpp weighing.hpp
	$(CPP) $(CFLAGS) -c game.cpp

human.o: human.cpp human.hpp player.hpp game.hpp coinset.hpp weighing.hpp
	$(CPP) $(CFLAGS) -c human.cpp

main.o: main.cpp game.hpp coinset.hpp weighing.hpp human.hpp player.hpp \
  computerhard.hpp
	$(CPP) $(CFLAGS) -c main.cpp

player.o: player.cpp player.hpp game.hpp coinset.hpp weighing.hpp
	$(CPP) $(CFLAGS) -c player.cpp

x11graphics.o: x11graphics.cpp x11graphics.hpp
	$(CPP) $(CFLAGS) -c x11graphics.cpp

clean:
	$(RM) coinweight *.o *.d *~

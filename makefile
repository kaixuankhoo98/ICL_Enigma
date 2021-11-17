CC = g++
CFLAGS = -g -Wall

enigma: main.o functions.o Plugboard.o Reflector.o Rotor.o Position.o
	$(CC) $(CFLAGS) -o enigma main.o functions.o Plugboard.o Reflector.o Rotor.o Position.o

main.o: main.cpp functions.h functions.o errors.h Plugboard.o Reflector.o Rotor.o Position.o Plugboard.h Reflector.h Rotor.h Position.h
	$(CC) $(CFLAGS) -c main.cpp

functions.o: functions.cpp errors.h Plugboard.h Reflector.h Rotor.h Position.h
	$(CC) $(CFLAGS) -c functions.cpp

Plugboard.o: Plugboard.h functions.h
	$(CC) $(CFLAGS) -c Plugboard.cpp

Reflector.o: Reflector.h functions.h
	$(CC) $(CFLAGS) -c Reflector.cpp

Rotor.o: Rotor.h functions.h
	$(CC) $(CFLAGS) -c Rotor.cpp

Position.o: Position.h functions.h
	$(CC) $(CFLAGS) -c Position.cpp

clean: 
	-rm *.o *.gch

enigma1: main.cpp functions.o functions.cpp Plugboard.cpp Reflector.cpp Rotor.cpp Position.cpp functions.h Plugboard.h Reflector.h Rotor.h Position.h
	g++ main.cpp -o enigma functions.o

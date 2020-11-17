Name = Snake

but : $(Name)

OFILES = SnakeControlleur.o \
	SnakeInit.o \
	SnakeAffichage.o \
	SnakeMain.o

CC = gcc 

CFLAGS = -lgraph -ansi 

SnakeControlleur.o : SnakeControlleur.h SnakeInit.h SnakeAffichage.h

SnakeInit.o : SnakeControlleur.h SnakeInit.h SnakeAffichage.h

SnakeAffichage.o : SnakeControlleur.h SnakeInit.h SnakeAffichage.h

SnakeMain.o : SnakeControlleur.h SnakeInit.h SnakeAffichage.h


Snake : $(OFILES)
		$(CC) $(CFLAGS) -o $(Name) $(OFILES)

clean :
	-rem $(OFILES) $(Name)

run : 
	./$(Name)

.PHONY : but clean
CCFLAGS = -g -c

mizzo: main.o io.o consumer.o producer.o functions.o
	gcc -o mizzo main.o io.o consumer.o producer.o functions.o -lpthread
main.o: main.c main.h
	gcc $(CCFLAGS)  main.c
io.o: io.h production.h io.c
	gcc $(CCFLAGS)  io.c
consumer.o: consumer.h consumer.c functions.h
	gcc $(CCFLAGS) consumer.c
producer.o: producer.h producer.c functions.h
	gcc $(CCFLAGS) producer.c
functions.o: functions.c functions.h
	gcc $(CCFLAGS) functions.c

clean :
	rm *.o
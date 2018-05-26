#common makefile header

DIR_BIN = /home/pi/Downloads/NewPro/bin


TARGET	= server
BIN_TARGET = $(DIR_BIN)/$(TARGET)

CFLAGS = -g -Wall

LDFLAGS +=  -ldl -lpthread -lwiringPi

OBJECTS := $(patsubst %.c,%.o,$(wildcard *.c))

$(BIN_TARGET) : $(OBJECTS)
	$(CROSS_COMPILE)gcc $(CFLAGS) $^ -o $@ $(LDFLAGS)

%.o : %.c
	$(CROSS_COMPILE)gcc -c $(CFLAGS) $< -o $@
clean:
	@rm -f *.o $(BIN_TARGET)

.PHONY:clean

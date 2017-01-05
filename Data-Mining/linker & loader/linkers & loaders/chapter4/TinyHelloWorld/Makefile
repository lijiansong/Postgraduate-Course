CC = gcc
LD = ld
CFLAGS = -c -fno-builtin
LDFLAGS = -static -e nomain

TARGET = TinyHelloWorld
OBJ = $(TARGET).o

$(TARGET):$(TARGET).o
	$(LD) $(LDFLAGS) -o $@ $< -T $(TARGET).lds

$(TARGET).o:$(TARGET).c
	$(CC) $(CFLAGS) $<
	
clean:
	rm $(OBJ) $(TARGET)

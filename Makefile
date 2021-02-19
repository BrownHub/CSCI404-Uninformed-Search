CC=g++

SRC=main.cpp
TARGET=find_route

$(TARGET): $(SRC)
	$(CC) -o $(TARGET) $(SRC)

clean:
	rm -f $(TARGET)
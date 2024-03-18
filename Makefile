  #the compiler: gcc for C program, g++ for C++
  CC = g++

  # compiler flags:
  #  -g    adds debugging information to the executable file
  #  -Wall turns on most, but not all, compiler warnings
  CFLAGS = -g -Wall

  # the build target executable:
  TARGET = proj1

.PHONY: clean tar script #these targets are not to be compiled

  all: $(TARGET)

  clean:
	$(RM) $(TARGET)
	$(RM) *.o

  tar:
	tar cf $(TARGET).tar *.cpp *.h *.scr Makefile

  script:
	script $(TARGET).txt

#  input:
#	$(CC) -c $(TARGET)input.cpp -o $(TARGET)input.o

  $(TARGET): $(TARGET).cpp
	$(CC) $(CFLAGS) $(TARGET).cpp -o $(TARGET)

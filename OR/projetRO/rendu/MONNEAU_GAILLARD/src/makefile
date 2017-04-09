#  GAILLARD Florent
#  MONNEAU Dylan 
#  601A

CXX=g++
CFLAGS=
LDFLAGS=-lglpk -lm
EXEC=Main

SRC=$(wildcard *.cpp )
OBJ=$(SRC:.cpp=.o)

all:$(EXEC)

Main:$(OBJ)
	$(CXX) -o bladeFlyer $^ $(LDFLAGS)

%.o: %.cpp
	@$(CXX) -std=c++0x -o $@ -c $< $(CFLAGS)
	
.PHONY: clean mrproper

clean:
	rm -rf *.o

mrproper: clean
	@rm -rf $(EXEC)

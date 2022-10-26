text0 = 
text1 = Se procedera a compilar la práctica...
text2 = Modo de empleo:
text3 = ./ejecutable
text4 = Se ha eliminador el fichero ejecutable.
F=src/main.cpp
CXXFLAGS= -std=c++14 -g -Wall

all: IA

Inicio:
	@echo $(text1)
	@echo $(text0)

IA: $(F) Inicio
	g++ $(CXXFLAGS) -o ejecutable $(F)
	@echo $(text0)
	@echo $(text2)
	@echo $(text3)
clean:
	rm -f ejecutable
	@echo $(text4)

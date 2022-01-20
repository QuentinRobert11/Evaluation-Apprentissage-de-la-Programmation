CPP=g++ -Iheaders
RM=rm -f

project : build/main.o build/temperature_map.o build/matrix.o build/linear_syst.o
	$(CPP) $^ -o $@

build/main.o : src/main.cpp src/linear_syst.cpp src/matrix.cpp src/temperature_map.cpp headers/linear_syst.hpp headers/matrix.hpp headers/temperature_map.hpp
build/temperature_map.o : src/temperature_map.cpp headers/temperature_map.hpp src/matrix.cpp src/linear_syst.cpp headers/matrix.hpp headers/linear_syst.hpp
build/matrix.o : src/matrix.cpp headers/matrix.hpp
build/linear_syst.o : src/linear_syst.cpp headers/linear_syst.hpp src/matrix.cpp headers/matrix.hpp

build/%.o: src/%.cpp
	$(CPP) -o $@ -c $<

clean:
	$(RM) build/main.o build/temperature_map.o build/linear_syst.o build/matrix.o project

.PHONY: clean
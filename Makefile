all: Shaders SimpleGL
	
SimpleGL:
	emcc -o SimpleGL.js SimpleGL.cpp SDLStage.cpp Huis.cpp -s FULL_ES2=1

sedPattern = 's/^\(.*\)$$/"\1\\n"/g'
Shaders:
	echo "const char HuisVert[] = " >  Huis.vert.h
	sed $(sedPattern) Huis.vert 	>> Huis.vert.h
	echo ";" 						>> Huis.vert.h
	
	echo "const char HuisFrag[] = " >  Huis.frag.h
	sed $(sedPattern) Huis.frag 	>> Huis.frag.h
	echo ";" 						>> Huis.frag.h

clean:
	rm SimpleGL.wasm
	rm SimpleGL.js
	rm Huis.vert.h
	rm Huis.frag.h
CXX_LINUX = g++
CXX_WINDOWS = g++
CXX_WEB = C:/emsdk/upstream/emscripten/em++.bat

CXXFLAGS = -std=c++17 -O2 -Wall -Wextra

SRC = Rotate.cpp
OUT_LINUX = rotate
OUT_WINDOWS = rotate.exe
OUT_WEB = rotate.html

linux:
	$(CXX_LINUX) $(CXXFLAGS) $(SRC) -o $(OUT_LINUX)

run-linux: linux
	./$(OUT_LINUX)

windows:
	$(CXX_WINDOWS) $(CXXFLAGS) $(SRC) -o $(OUT_WINDOWS)

run-windows: windows
	$(OUT_WINDOWS)

web:
	$(CXX_WEB) $(SRC) -O2 -s WASM=1 -s EXIT_RUNTIME=1 -o $(OUT_WEB)

run-web: web
	python3 -m http.server 8080

clean:
	rm -f $(OUT_LINUX) $(OUT_WINDOWS) $(OUT_WEB) rotate.wasm rotate.js

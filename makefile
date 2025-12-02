CXX_LINUX = g++
CXX_WINDOWS = x86_64-w64-mingw32-g++
CXX_WEB = em++
CXX_ANDROID = $(ANDROID_NDK)/toolchains/llvm/prebuilt/linux-x86_64/bin/clang++

CXXFLAGS = -std=c++17 -O2 -Wall -Wextra

SRC = Rotate.cpp
OUT_LINUX = rotate
OUT_WINDOWS = rotate.exe
OUT_WEB = rotate.html
OUT_ANDROID = rotate_android

linux:
	$(CXX_LINUX) $(CXXFLAGS) $(SRC) -o $(OUT_LINUX)

run-linux: linux
	./$(OUT_LINUX)

windows:
	$(CXX_WINDOWS) $(CXXFLAGS) $(SRC) -o $(OUT_WINDOWS)

run-windows: windows
	wine $(OUT_WINDOWS)

web:
	$(CXX_WEB) $(SRC) -O2 -s WASM=1 -o $(OUT_WEB)

run-web: web
	python3 -m http.server 8080

android:
	$(CXX_ANDROID) --target=aarch64-linux-android24 $(CXXFLAGS) $(SRC) -o $(OUT_ANDROID)

install-android:
	adb push $(OUT_ANDROID) /data/local/tmp/rotate
	adb shell "chmod +x /data/local/tmp/rotate"

run-android:
	adb shell "/data/local/tmp/rotate"

clean:
	rm -f $(OUT_LINUX) $(OUT_WINDOWS) $(OUT_WEB) rotate.wasm rotate.js $(OUT_ANDROID)

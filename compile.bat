g++ -D GLEW_STATIC -static -I ".\include" -L ".\lib" src\*.cpp src\*.c -lglew32 -lglfw3 -luser32 -lgdi32 -lopengl32 -o test.exe
:: use -mwindows to hide console window
:: -Wl,--subsystem,windows
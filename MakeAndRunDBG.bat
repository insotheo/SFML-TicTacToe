@echo off
cd build
cmake ..
cmake --build . --config Debug
start Debug\TestGame.exe
cd ..
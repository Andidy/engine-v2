REM Clone dependencies =========================

mkdir raysan5
cd raysan5
git clone https://github.com/raysan5/raygui.git
git clone https://github.com/raysan5/raylib.git
cd ..

REM Create Solution Files ======================

premake5 vs2019 --opengl43

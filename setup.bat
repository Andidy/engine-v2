REM Clone dependencies =========================

mkdir raysan5
cd raysan5
git clone https://github.com/raysan5/raygui.git
git clone https://github.com/raysan5/raylib.git
cd ..

REM Create Solution Files ======================

premake5 vs2019 --opengl43

REM Download Assets ============================

cd engine-v2/assets
mkdir gfx
git clone https://github.com/Andidy/engine-v2-assets.git gfx
cd ../..

cd ..
mkdir engine-v2-release
cd engine-v2-release

robocopy "../engine-v2/build/Release" "." raylib.lib
robocopy "../engine-v2/build/Release" "." engine-v2.exe

robocopy "../engine-v2/engine-v2" "." map.png
robocopy "../engine-v2/engine-v2" "." entity.txt

robocopy "../engine-v2/engine-v2/assets/gfx/" "assets/gfx" *.png
robocopy "../engine-v2/engine-v2/assets/gfx/bitkenney" "assets/gfx/bitkenney"

robocopy "../engine-v2/engine-v2/assets/gui/style" "assets/gui/style"

cd ../engine-v2
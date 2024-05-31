if not exist build mkdir build

cmake . -D make -B build -DCMAKE_EXPORT_COMPILE_COMMANDS=1

mklink compile_commands.json build\compile_commands.json

cd build
cmake --build .

move .\Debug\GIN3.out.exe .
copy ..\lib\raylib\raylib.dll .\raylib.dll

GIN3.out.exe
#!/bin/sh

mkdir -p build

cmake . -B build -DCMAKE_EXPORT_COMPILE_COMMANDS=1

ln -s build/compile_commands.json ./compile_commands.json

cd build
make

if [[ $1 == '--no-run' ]]
then 
    exit 0
fi

./GIN3

#! /bin/sh

DIR='./build'
if [ ! -d "$DIR" ]; then
    mkdir "$DIR"
fi

cd "$DIR"
cmake ../
cmake --build .
./SOCKET
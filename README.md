## loop
A simple tool to loop a command\
To pass multiple commands, write them to a script and execute with ```loop bash script.sh```\
You can also run the tool as ```loop 1000 command arg1 arg2 ...``` where\
1000 is the loop wait time in miliseconds. 

## Build
```
git clone https://github.com/lesacar/loop
cd loop
cmake -B build
cd build
make
cd ..
```
The binary will be build/loop

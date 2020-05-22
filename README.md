# fifoPipes
A small C calculator to test pipes between processes.

## Installation
Clone the repository and go the created directory:
```
git clone https://github.com/ramziChbl/fifoPipes
cd fifoPipes/
```
Compile the guiGTK.c file with the appropriate GTK library :
```
gcc src/guiGTK.c -o bin/guiGTK  `pkg-config --cflags gtk+-3.0` `pkg-config --libs gtk+-3.0`
```
Compile the other files:
```
gcc src/main.c -o bin/main
gcc src/calcul.c -o bin/calcul
gcc src/trace.c -o bin/trace
```

## Usage
```
cd bin/
./main
```


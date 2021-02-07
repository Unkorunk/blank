# blank - game engine
## That engine use [FreeType 2 library](https://www.freetype.org/)

### Build
1. sudo apt-get install git dos2unix wget zip unzip
1. git clone https://github.com/Unkorunk/blank.git blank
1. cd blank
1. git submodule init
1. git submodule update
1. cd ./submodules/glew
1. make -C auto
1. cd ../..
1. mkdir build
1. cd build
1. cmake ..
1. cmake --build .

### How to run the example?
1. Download some font and place it in "assets" directory
1. Change the font link in "example/main.cpp"
1. Rebuild solution

### License
This repository is licensed with the [MIT](LICENSE) license.

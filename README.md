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
1. open project using clion or (mkdir build && cd build && cmake .. && and build project)

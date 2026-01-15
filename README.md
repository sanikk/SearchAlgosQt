# SearchAlgosQt

C++ Qt version of my project, originally for the course
Algorithms and Artificial Intelligence Project, Laboratory work
TKT20010 at University of Helsinki.

I've been using this to learn the basics of C++. This version started from hello world.

Here is the non-Qt C++ version: https://github.com/sanikk/algolabra-cpp

And the original Python version, with PyQt6: https://github.com/sanikk/algolabra

Maps are from the wonderful people at [MovingAI](https://www.movingai.com/). I just provide them here for
convenience.

## Third-party libraries

This project uses [Qt](https://www.qt.io/) for its GUI components. Qt is licensed under the
[GNU Lesser General Public License (LGPL) v3](LICENSE_Qt-LGPL.txt).  
This software links dynamically to the Qt libraries; Qt is not part of this project.

### INSTRUCTIONS

You need  a C++ compiler (tested with g++ and msvc), the QT6 stuff for your compiler and cmake.

#### Linux
```bash
cd build
cmake ..
cmake --build .
```
(I havent ran this in a while on my linux installs, i need to test the Linux instructions. You have been warned.)

#### Windows (example for msvc, with Qt version 6.10.1 installed in the default destination)
You only need to run the windeployqt.exe if your install cannot find the Qt6 files on its own, and then running
it the first time should suffice.
```powershell
cd build
cmake -DCMAKE_PREFIX_PATH="C:/Qt/6.10.1/msvc2022_64" ..
cmake --build .
c:\Qt\6.10.1\msvc2022_64\bin\windeployqt.exe ./Debug/searchalgos.exe
.\Debug\searchalgos.exe
```

### RELEASES

Providing a .zip file for windows users, with Qt6 libs.

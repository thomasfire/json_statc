# json_statc
Reads JSON file and outputs statistics about types and depth.

Requirements: _GCC_ or _Clang_ compiler with C11 support.

Building and execution:
```shell script
$ git clone https://github.com/thomasfire/json_statc.git
$ cd json_statc
$ mkdir build
$ cd build
$ cmake .. -DCMAKE_BUILD_TYPE=Release
$ cmake --build .
$ ./json_statc path/to/json
```

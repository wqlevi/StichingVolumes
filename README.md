# utils_ESRGAN
## 1D example
- [x] ~~Finished~~
## 2D example
- [x] ~~Incorrect 2D stitch value~~
- [x] ~~SIGV 11 error due to use of unallocated memo~~
- [x] ~~Finished~~
## 3D example
- [x] ~~TBD~~
- [x] ~~Finished~~

## Compile them:
~~~bash
$ gcc -Wall -Iinclude -Llib test.c -lnifti1io -lm -o test
~~~

## Compilers
Not only Nvidia provides mutli-threading as well as GPU compiling(`nvc`); 

also intel provides their ones(`icc`)

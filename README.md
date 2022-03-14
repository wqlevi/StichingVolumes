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
$ export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/home/qiwang/git_wq/utils_ESRGAN/lib
~~~

## Compilers
Not only Nvidia provides mutli-threading as well as GPU compiling(`nvc`); 

also intel provides their ones(`icc`)

## Profiler
`$CFLAGS=-O3 -pg -g`
then make & run executable(which gives gmon.out as profile)
`gprof ./a.out gmon.out`
to generate output report


################################################################################
#
# THIS FILE IS BASIC MAKE FILE FOR
# Copyright (c) 2020-2021
# Original Author: 1107473010@qq.com
#
################################################################################

# This is object should be build and will link to generate
# the executables
BUILD=e

CFLAGS = -O3 -g -fno-strict-aliasing -lrt 
CCFLAGS := 

c_objects = posix_mq.o
cpp_objects = 

# This is the file name of the executables and path where 
# place the executables
buildout = posix_mq
run_dist = ./../executables

# if want run, with this config
executable_run = ./${run_dist}/${buildout}

# Including this file allows access to the Build System.
include ../build_env/buildrules.mk

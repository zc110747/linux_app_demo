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

CFLAGS = 
CCFLAGS := -O3 -std=c++17 -fno-strict-aliasing -lrt 

c_objects = 
cpp_objects = character_api.o

# This is the file name of the executables and path where 
# place the executables
buildout = character_api
run_dist = ./../executables

# if want run, with this config
executable_run = ./${run_dist}/${buildout}

# Including this file allows access to the Build System.
include ../build_env/buildrules.mk

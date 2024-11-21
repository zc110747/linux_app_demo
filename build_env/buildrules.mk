################################################################################
#
# THIS FILE IS BASIC MAKE FILE FOR
# Copyright (c) 2020-2023
# Original Author: 1107473010@qq.com
#
################################################################################

#-------------------------------------------------------------------------------
#support c/c++ compile.
#build excutatble, static library or dynamic library.
#-------------------------------------------------------------------------------

#-------------------------------------------------------------------------------
#							Build Config Region 
#-------------------------------------------------------------------------------

###buildout file name
buildout ?=

###build mode
#e: executable
#s: static-library
#
BUILD ?=e

###compile tools
CROSS_COMPILE ?=
C_COMPILE ?= ${CROSS_COMPILE}gcc
CC_COMPILE ?= ${CROSS_COMPILE}g++
AR_COMPILE ?= ${CROSS_COMPILE}ar

CFLAGS  += -lpthread -lm
CCFLAGS  += -lpthread -lm

###include Path
INCLUDES ?=

###include library
library ?= 

###c/cpp objects for build
object ?=
c_objects ?=
cpp_objects ?=

objects+=${c_objects}
objects+=${cpp_objects}

run_dist ?=
executable_run ?= 

# build information
ifeq ($(BUILD),e) 
$(info build executable file)
endif
ifeq ($(BUILD),s) 
$(info build static library)
endif
ifeq ($(BUILD),d) 
CCFLAGS += -fPIC
$(info build dynamic library)
endif
$(info used c compiler:$(C_COMPILE), c++ compiler:$(CC_COMPILE))
$(info AR_COMPILE:$(AR_COMPILE))
#-------------------------------------------------------------------------------
#						End of Build Config Region 
#-------------------------------------------------------------------------------

#-------------------------------------------------------------------------------
#						Build Rules Region 
#-------------------------------------------------------------------------------
%.o : %.cpp
	$(CC_COMPILE) $(CCFLAGS) -c $< -o $@ $(INCLUDES)

%.o : %.c
	$(C_COMPILE) $(CFLAGS) -c $< -o $@ $(INCLUDES)

all : $(buildout)

#build executable file
ifeq ($(BUILD),e) 
$(buildout): $(objects)

ifeq ("${cpp_objects}", "")
	$(C_COMPILE) -o $(buildout) $(objects) $(library) $(CFLAGS)
else
	$(CC_COMPILE) -o $(buildout) $(objects) $(library) $(CCFLAGS) 
endif
	
	rm -rf $(objects)

	if [ ! -d $(run_dist) ]; then \
		mkdir -m 777 -p $(run_dist); \
	fi
	
	mv $(buildout) $(run_dist)/

	${executable_run}
endif

#build static library
ifeq ($(BUILD),s) 
$(buildout): $(objects)
	$(AR_COMPILE) -cr $(buildout).a $(objects)

	rm -rf $(objects)
	mv $(buildout).a $(SUPPORT_ENV_INSTALL)/lib/
endif

#build dynamic library
ifeq ($(BUILD),d) 
$(buildout): $(objects)
	$(CC_COMPILE) $(objects) $(CCFLAGS) -shared -o lib$(buildout).so

	rm -rf $(objects)
	rm -f $(objects)
endif

clean:
	rm -f $(objects)
	rm -f *.a
	rm -f *.so

tags :
	ctags -R *
#-------------------------------------------------------------------------------
#						End of Build Rules Region 
#-------------------------------------------------------------------------------
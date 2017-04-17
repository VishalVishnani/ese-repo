include sources.mk

#Device determines the platform we are currently on using shell arch command
DEVICE:=$(shell arch)

LFLAGS=-Wl,-Map=main.map

#switchflag is used to determine whether to turn on/off project by setting switch value from command line
switchflag=switch_ON

ifeq ($(switch),OFF)
	switchflag=switch_OFF
endif

#For host machine platform, native compiler and flags
ifeq ($(PLATFORM),HOST)
	CC=gcc
	CFLAGS=-Wall -Werror -g -O0 -std=c99 -D$(switchflag)
endif

#For BeagleBone Black,cross compiler and native compiler with flags respectively 
ifeq ($(PLATFORM),BBB)
 ifeq ($(DEVICE),x86_64)
	CC=arm-linux-gnueabihf-gcc
	CFLAGS=-mcpu=cortex-a8 -Wall -g -o0 -std=c99 -D$(switchflag)
 else
	CC=gcc
	CFLAGS=-mcpu=cortex-a8 -Wall -g -o0 -std=c99 -D$(switchflag)
 endif
endif

#For KL25Z, cross compiler with flags 
ifeq ($(PLATFORM),FRDM)
	CC=arm-none-eabi-gcc
	CFLAGS=-mcpu=cortex-m0plus -Wall -g -O0 -std=c99 --specs=nosys.specs -DFRDM=1 -D$(switchflag)  
endif

#Phony protection for all targets
.PHONY : all file.i file.asm compile-all build project.out clean\
	 build-lib direct_link dependencies preprocess asmfile

#Default make command builds executable file project.out
all: project.out

#Creates an assembly output of all files
asmfile : $(SRCS)
	$(CC) -I headers $^ -S

#Creates a preprocessed output of all files 
preprocess : $(SRCS)
	$(CC) -I headers $^ -E > file.i

#Creates a dependency file for source files
dependencies: $(SRCS)
	$(CC) -M -I headers $^ -o project.dep

#Creates a preprocessed file of corresponding C file
%.i:%.c
	$(CC) -I headers -E $^ -o $@ $(CFLAGS)

#Creates an assembly file of corresponding C file
%.asm:%.c
	$(CFLAGS) -I headers $^ -S -o $@

#Creates an object file of corresponding C file
%.o:%.c
	$(CC) $(CFLAGS) -I headers -c $^ -o $@
	objdump -g $@

#Compiles all the object files without linking
compile-all : $(OBJS)
	$(CC) -I headers $^ $(CFLAGS)

#Compile all the object files and link
build : $(OBJS)
	$(CC) $^ $(CFLAGS) -I headers -o build.out $(LFLAGS)
	size -d build.out 
	objdump -g build.out

#Remove all compiled object,preprocessed output,assembly output,executables and build output files
clean :
	rm -rf *.o main.map *.i *.asm *.s *.gch build.out project.out a.out project.dep 0 libproject1.a output

#Creates the executable file
project.out : $(OBJS)
	$(CC) $(CFLAGS) -I headers $^ $(LFLAGS) -o $@
	size -d project.out
	objdump -g project.out

#Generates a library of memory.c and data.c into libproject.a archive
build-lib:memory.c data.c
	ar cr libproject1.a $^

#Invoking linker without using GCC
direct_link:$(OBJS)
	ld -o output $^ -lc

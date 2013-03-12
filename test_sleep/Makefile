####
#### Sample Makefile for building apps with the RIOT OS
####
#### The Sample Filesystem Layout is:
#### /this makefile
#### ../../RIOT 
#### ../../boards   for board definitions (if you have one or more)
#### 

debug: CFLAGS += -g
debug: CFLAGS += -DENABLE_DEBUG

#### Mandatory vars!

# this has to be the absolute path of the RIOT-base dir
export RIOTBASE =$(CURDIR)/../../RIOT
export RIOTBOARD =$(CURDIR)/../../boards

# the cpu to build for
export CPU = native
export MCU = native

# toolchain config
export PREFIX = 
#export CC = @$(PREFIX)gcc
export AR = @$(PREFIX)ar
export CFLAGS += -std=gnu99 -Wall -m32
export ASFLAGS += 
export AS = $(PREFIX)as
export LINK = $(PREFIX)gcc
export SIZE = $(PREFIX)size
export OBJCOPY = $(PREFIX)objcopy
TERM = pyterm.py

PROJBINDIR = bin

ifeq ($(strip $(PORT)),)
	PORT = /dev/ttyUSB0
endif

## Modules to include. No autodependencies!

#USEMODULE += auto_init
#USEMODULE += cc110x_ng
#USEMODULE += cmdd
#USEMODULE += cmdengine
#USEMODULE += config
#USEMODULE += ezxml
#USEMODULE += fat
#USEMODULE += geo
#USEMODULE += gpioint
#USEMODULE += gps
#USEMODULE += gps_conversion
#USEMODULE += gps_ublox
#USEMODULE += lib 
#USEMODULE += logd
#USEMODULE += ltc4150
#USEMODULE += mci
#USEMODULE += mprint
#USEMODULE += mqueue
#USEMODULE += nanopan5375_proprietary
#USEMODULE += net_kernel
#USEMODULE += net_mm
#USEMODULE += posix
#USEMODULE += powermon
USEMODULE += ps
#USEMODULE += rtc
#USEMODULE += shell
#USEMODULE += shell_commands
#USEMODULE += sht11
#USEMODULE += sync_read
#USEMODULE += sys_config
#USEMODULE += syslog
#USEMODULE += sysmon
#USEMODULE += tracelog
#USEMODULE += transceiver
#USEMODULE += uart0
#USEMODULE += vtimer

#### Project Config 

# name of your project
PROJECT = test_sleep

# for easy switching of boards
export BOARD = native

# mandatory include! 
include $(RIOTBASE)/makefile.modules 

# if you want to publish the board into the sources as an uppercase #define
BB = $(shell echo $(BOARD)|tr 'a-z' 'A-Z')
CFLAGS += -DBOARD=$(BB)
export CFLAGS

# your binaries to link
BASELIBS += $(RIOTBOARD)/$(BOARD)/bin/$(BOARD)_base.a
BASELIBS += $(PROJBINDIR)/project.a

INCLUDES = -I$(RIOTBOARD)/$(BOARD)/include -I$(RIOTBASE)/core/include -I$(RIOTBASE)/cpu/$(CPU)/include -I$(RIOTBASE)/sys/lib -I$(RIOTBASE)/sys/include/ -I$(RIOTBASE)/drivers/include/

export INCLUDES

## make script for your project. Build RIOT-base here!
all: $(PROJBINDIR)/$(PROJECT).a
	@echo "Building project $(PROJECT) for $(BOARD) w/ MCU $(CPU)."
	$(MAKE) -C $(RIOTBOARD)
	$(MAKE) -C $(RIOTBASE)
	$(LINK) $(LINKFLAGS) $(UNDEF) $(CFLAGS) -o $(PROJBINDIR)/$(PROJECT).elf -Wl,--start-group $(BASELIBS) -lrt -lm -Wl,--end-group  -Wl,-Map=$(PROJBINDIR)/$(PROJECT).map
	$(SIZE) $(PROJBINDIR)/$(PROJECT).elf
	$(OBJCOPY) -O ihex $(PROJBINDIR)/$(PROJECT).elf $(PROJBINDIR)/$(PROJECT).hex

debug: all

## your make rules
## Only basic example - modify it for larger projects!!

$(PROJBINDIR)/$(PROJECT).a: $(PROJBINDIR)/$(PROJECT).o
	$(AR) -rc $(PROJBINDIR)/project.a $(PROJBINDIR)/$(PROJECT).o 
	
$(PROJBINDIR)/$(PROJECT).o: main.c 
	$(CC) $(CFLAGS) $(BOARDINCLUDE) $(INCLUDES) -c main.c -o $(PROJBINDIR)/$(PROJECT).o

clean:
	$(MAKE) -C $(RIOTBOARD) clean
	$(MAKE) -C $(RIOTBASE) clean
	rm -f $(PROJBINDIR)/*

doc:
	make -BC $(RIOTBASE) doc

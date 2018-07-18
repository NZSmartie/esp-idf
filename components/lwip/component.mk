#
# Component Makefile
#

LWIPDIR = $(COMPONENT_PATH)/lwip/src

include $(LWIPDIR)/Filelists.mk

COMPONENT_ADD_INCLUDEDIRS := \
	lwip/src/include \
	port/include \
	lwip/src/include/compat/posix

LWIP_SOURCE_FILES := $(COREFILES) $(CORE4FILES) $(CORE6FILES) $(APIFILES) $(LWIPAPPFILES) $(NETIFFILES)

ifdef CONFIG_PPP_SUPPORT
LWIP_SOURCE_FILES += $(PPPFILES)
endif

# Extract source directory names from LWIP's Filelist.mk
LWIP_SRCDIRS := $(shell dirname $(LWIP_SOURCE_FILES) | sort -u)

COMPONENT_SRCDIRS := \
	port \
	port/apps \
	port/core \
	port/debug \
	port/freertos \
	port/netif

# Find all source files since COMPONENT_OBJS is explicitly set below
LWIP_SOURCE_FILES += $(foreach dir,$(COMPONENT_SRCDIRS),$(wildcard $(COMPONENT_PATH)/$(dir)/*.[cS]))

# Substitube all source files (*.c, *.S) for object files (*.o)
COMPONENT_OBJS := $(patsubst %.c,%.o,$(LWIP_SOURCE_FILES:$(COMPONENT_PATH)/%=%))
COMPONENT_OBJS := $(patsubst %.S,%.o,$(COMPONENT_OBJS))

# Append filed specified by LWIP's Filelist.mk
COMPONENT_SRCDIRS += $(LWIP_SRCDIRS:$(COMPONENT_PATH)/%=%)

CFLAGS += -Wno-address  # lots of LWIP source files evaluate macros that check address of stack variables

# api/tcpip.o apps/dhcpserver.o: CFLAGS += -Wno-unused-variable
# apps/dhcpserver.o core/pbuf.o core/tcp_in.o: CFLAGS += -Wno-unused-but-set-variable
# netif/ppp/pppos.o: CFLAGS += -Wno-type-limits

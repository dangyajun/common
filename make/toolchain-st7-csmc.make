ifndef COMMON
$(error Please define COMMON path before including any common package)
endif

#----------------------------------------------------------#

PROJECT    ?=
CSMC       ?=
CSTM       ?=
BUILD      ?= build

#----------------------------------------------------------#

PROJECT    := $(firstword $(PROJECT) $(notdir $(CURDIR)))

#----------------------------------------------------------#

AS         := $(CSMC)cxst7
CC         := $(CSMC)cxst7
COPY       := $(CSMC)cvdwarf
DUMP       := $(CSMC)chex
LD         := $(CSMC)clnk
AR         := $(CSTM)clib
LABS       := $(CSMC)clabs
SIZE       := size

RM         ?= rm -f

#----------------------------------------------------------#

ST7        := $(if $(BUILD),$(BUILD)/,)$(PROJECT).st7
LIB        := $(if $(BUILD),$(BUILD)/,)$(PROJECT).st7
ELF        := $(if $(BUILD),$(BUILD)/,)$(PROJECT).elf
HEX        := $(if $(BUILD),$(BUILD)/,)$(PROJECT).s19
MAP        := $(if $(BUILD),$(BUILD)/,)$(PROJECT).map

SRCS       := $(foreach s,$(SRCS),$(realpath $s))
OBJS       := $(SRCS:%.s=$(BUILD)%.o)
OBJS       := $(OBJS:%.c=$(BUILD)%.o)
LSTS       := $(OBJS:.o=.ls)
TXTS       := $(OBJS:.o=.la)

#----------------------------------------------------------#

GENERATED  := $(ST7) $(LIB) $(ELF) $(HEX) $(MAP)
GENERATED  += $(OBJS) $(LSTS) $(TXTS)

#----------------------------------------------------------#

LIBS       += crtsx.st7 libisl.st7 libm.st7

#----------------------------------------------------------#

ifneq (clean,$(MAKECMDGOALS))
AS_FLAGS   += -l -ep # -ax
C_FLAGS    += -pc99 -l -pad +modsl
LD_FLAGS   += -m $(MAP) -p
ifneq ($(filter DEBUG,$(DEFS)),)
$(info Using debug)
C_FLAGS    += +debug
else
ifeq  ($(filter NDEBUG,$(DEFS)),)
DEFS       += NDEBUG
endif
endif
endif

#----------------------------------------------------------#

DEFS_F     := $(DEFS:%=-d%)
INCS_F     := $(INCS:%=-i%/)
LIB_DIRS_F := $(LIB_DIRS:%=-l%)

AS_FLAGS   += $(DEFS_F)
C_FLAGS    += $(DEFS_F) $(INCS_F)
LD_FLAGS   += $(SCRIPT)

#----------------------------------------------------------#

$(info Using '$(MAKECMDGOALS)')

all : $(ELF) print_elf_size

lib : $(OBJS)
	$(info $(LIB))
	$(AR) -c -p $(LIB) $?

$(OBJS) : $(MAKEFILE_LIST)

$(BUILD)/%.o : /%.s
	mkdir -p $(dir $@)
	$(AS) -co $(dir $@) -cl $(dir $@) $(AS_FLAGS) $<

$(BUILD)/%.o : /%.c
	mkdir -p $(dir $@)
	$(CC) -co $(dir $@) -cl $(dir $@) $(C_FLAGS) $<

$(ST7) : $(OBJS) $(SCRIPT)
	$(info $@)
	$(LD) -o $@ $(LD_FLAGS) $(OBJS) $(LIBS) $(LIB_DIRS_F)

$(ELF) : $(ST7)
	$(info $@)
	$(COPY) $<

$(HEX) : $(ST7)
	$(info $@)
	$(DUMP) -o $@ $<

print_elf_size : $(ELF)
	$(info Size of target file:)
	$(SIZE) -B $(ELF)

clean :
	$(info Removing all generated output files)
	$(RM) $(if $(BUILD),-Rd $(BUILD),$(GENERATED))

.PHONY : all lib clean

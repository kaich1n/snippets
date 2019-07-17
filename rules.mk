ifneq ($(__rules_inc),1)
__rules_inc=1

ifndef SILENCE
  SILENCE = @
endif
comma:= ,
empty:=
space:= $(empty) $(empty)

AR := $(CROSS_COMPILE)ar rcs
CC := $(CROSS_COMPILE)gcc
CXX := $(CROSS_COMPILE)g++
CFLAGS := -g -Wall -Werror -Wstrict-prototypes -Wextra -fPIC
CXXFLAGS := -g -Wall -Werror -Wextra -fPIC -std=c++11

CP ?= cp -r
INSTALL_BIN  ?= install -m0755
INSTALL_SUID ?= install -m4755
INSTALL_DIR  ?= install -d -m0755
INSTALL_DATA ?= install -m0644
INSTALL_CONF ?= install -m0600

export SILENCE
export CC CXX CFLAGS CXXFLAGS
export INSTALL_BIN INSTALL_SUID INSTALL_DIR INSTALL_DATA INSTALL_CONF

BUILD_DIR ?= build
export BUILD_DIR

get_src_from_dir = $(wildcard $1/*.cpp) $(wildcard $1/*.cc) $(wildcard $1/*.c)
get_src_from_dir_list = $(foreach dir, $1, $(call get_src_from_dir,$(dir)))
__src_to = $(subst .c,$1, $(subst .cc,$1, $(subst .cpp,$1,$(notdir $2))))
src_to = $(addprefix $(BUILD_DIR)/,$(call __src_to,$1,$2))
src_to_o = $(call src_to,.o,$1)
src_to_d = $(call src_to,.d,$1)
src_to_gcda = $(call src_to,.gcda,$1)
src_to_gcno = $(call src_to,.gcno,$1)
add_inc_dir = $(addprefix -I,$1)

$(BUILD_DIR)/%.o: %.cc
	$(SILENCE)echo compiling $(notdir $<)
	$(SILENCE)mkdir -p $(dir $@)
	$(SILENCE)$(CXX) $(CXXFLAGS) -o $@ -c $<

$(BUILD_DIR)/%.o: %.cpp
	$(SILENCE)echo compiling $(notdir $<)
	$(SILENCE)mkdir -p $(dir $@)
	$(SILENCE)$(CXX) $(CXXFLAGS) -o $@ -c $<

$(BUILD_DIR)/%.o: %.c
	$(SILENCE)echo compiling $(notdir $<)
	$(SILENCE)mkdir -p $(dir $@)
	$(SILENCE)$(CC) $(CFLAGS) -o $@ -c $<

endif #__rules_inc

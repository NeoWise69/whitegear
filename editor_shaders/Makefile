SHADERS_SOURCES = $(wildcard *.hlsl)
SHADERS_TARGETS = $(SHADERS_SOURCES:.hlsl=.cso)

all: $(SHADERS_TARGETS)

SHADER_COMPILER :=

ifeq ($(OS),Windows_NT)
    SHADER_COMPILER := dxc
else
    SHADER_COMPILER := dxc
endif

%.cso: %.hlsl
	$(SHADER_COMPILER) -T vs_6_0 -E S_Main $< -Fo compiled/$@

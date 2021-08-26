INC_DIR := system ../DE0_CV_SDRAM_Nios_Test_bsp/drivers/inc ../DE0_CV_SDRAM_Nios_Test_bsp/HAL/inc \
		../DE0_CV_SDRAM_Nios_Test_bsp \
		../DE0_CV_SDRAM_Nios_Test/
CPP_SRC := $(wildcard system/*.cpp) main.cpp mem_verify.cpp
OBJ := $(CPP_SRC:%.cpp=obj/%.o)

all: $(OBJ)
	@echo "[LINK] $@"
	@$(CXX) -o test.exe $(OBJ)


obj/%.o: %.cpp
	@echo "[CXX] $@"
	@mkdir -p $(@D)
	@$(CXX) -g -c $(addprefix -I ,$(INC_DIR)) -o $@ $<

clean:
	rm -rf obj
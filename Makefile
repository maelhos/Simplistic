# Default is x86_64
.PHONY: default
default: build-x86_64 

kernel_source_files := $(shell find Simplistic-Kernel/kernel -name *.cpp)
kernel_object_files := $(patsubst Simplistic-Kernel/kernel/%.cpp, build/kernel/%.o, $(kernel_source_files))

x86_64_cpp_source_files := $(shell find Simplistic-Kernel/x86_64 -name *.cpp)
x86_64_cpp_object_files := $(patsubst Simplistic-Kernel/x86_64/%.cpp, build/x86_64/%.o, $(x86_64_cpp_source_files))

x86_64_asm_source_files := $(shell find Simplistic-Kernel/x86_64 -name *.asm)
x86_64_asm_object_files := $(patsubst Simplistic-Kernel/x86_64/%.asm, build/x86_64/%.o, $(x86_64_asm_source_files))

x86_64_object_files := $(x86_64_cpp_object_files) $(x86_64_asm_object_files)

CPLUS_INCLUDE_PATH := Simplistic/x86_64/sys_lib/include

$(kernel_object_files): build/kernel/%.o : Simplistic-Kernel/kernel/%.cpp
	@mkdir -p $(dir $@) && \
	x86_64-elf-gcc -c -m64 -mno-red-zone -I Simplistic-Kernel/x86_64/sys_lib/include/ -ffreestanding $(patsubst build/kernel/%.o, Simplistic-Kernel/kernel/%.cpp, $@) -o $@

$(x86_64_cpp_object_files): build/x86_64/%.o : Simplistic-Kernel/x86_64/%.cpp
	@mkdir -p $(dir $@) && \
	x86_64-elf-gcc -c -m64 -mno-red-zone -I Simplistic-Kernel/x86_64/sys_lib/include/ -ffreestanding $(patsubst build/x86_64/%.o, Simplistic-Kernel/x86_64/%.cpp, $@) -o $@
	
$(x86_64_asm_object_files): build/x86_64/%.o : Simplistic-Kernel/x86_64/%.asm
	@mkdir -p $(dir $@) && \
	nasm -f elf64 $(patsubst build/x86_64/%.o, Simplistic-Kernel/x86_64/%.asm, $@) -o $@

.PHONY: build-x86_64
build-x86_64: $(kernel_object_files) $(x86_64_object_files)
	@echo "[ASM Files] :"
	@echo $(x86_64_asm_source_files)

	@echo "[KERNEL Files] :"
	@echo $(kernel_source_files)

	@echo "[CPP Files] :"
	@echo $(x86_64_cpp_source_files)

	@mkdir -p dist/x86_64 && \
	x86_64-elf-ld --allow-multiple-definition -n -o dist/x86_64/kernel.bin -T targets/x86_64/linker.ld $(kernel_object_files) $(x86_64_object_files) && \
	cp dist/x86_64/kernel.bin targets/x86_64/iso/boot/kernel.bin && \
	grub-mkrescue /usr/lib/grub/i386-pc -o dist/x86_64/kernel.iso targets/x86_64/iso

CLEAN:
	@rm -rfv build/
	@mkdir build
	@echo "CLEAN"
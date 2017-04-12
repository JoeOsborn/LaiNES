FLAGS:=-march=native -Ilib/include -Isrc/include -I/home/klee/klee_src/include/ -emit-llvm -c -g -std=c++11 -fno-exceptions -fno-rtti

build/src/%.bc: src/%.cpp
	clang++ $(FLAGS) $< -o $@

build/src/mappers/%.bc: src/mappers/%.cpp
	clang++ $(FLAGS) $< -o $@


OBJS:=build/src/apu.bc \
      build/src/cartridge.bc \
      build/src/cpu.bc \
      build/src/gui.bc \
      build/src/joypad.bc \
      build/src/main.bc \
      build/src/mapper.bc \
      build/src/mappers/mapper1.bc \
      build/src/mappers/mapper2.bc \
      build/src/mappers/mapper3.bc \
      build/src/mappers/mapper4.bc \
      build/src/ppu.bc

.DEFAULT:
klaines.bc: $(OBJS)
	llvm-link -o $@ $(OBJS)


O_FLAGS:=-march=native -Ilib/include -Isrc/include -I/home/klee/klee_src/include/ -c -g -std=c++11

build/src/%.o: src/%.cpp
	clang++ $(O_FLAGS) $< -o $@

build/src/mappers/%.o: src/mappers/%.cpp
	clang++ $(O_FLAGS) $< -o $@


O_OBJS:=build/src/apu.o \
      build/src/cartridge.o \
      build/src/cpu.o \
      build/src/gui.o \
      build/src/joypad.o \
      build/src/main.o \
      build/src/mapper.o \
      build/src/mappers/mapper1.o \
      build/src/mappers/mapper2.o \
      build/src/mappers/mapper3.o \
      build/src/mappers/mapper4.o \
      build/src/ppu.o


laines: $(O_OBJS)
	clang++ -lstdc++ -lc -o $@ $(O_OBJS)

#include <cstdio>
#include "cartridge.hpp"
#include "cpu.hpp"
#include "ppu.hpp"
#include "gui.hpp"
#if 1
#include <klee/klee.h>
#endif
#include <cmath>

int main(int argc, char *argv[])
{
  const unsigned move_count = 10000;
  //load cartridge here
  Cartridge::load("rom.nes");
  CPU::run_frame();
  u8 moves[move_count] = {0};
  // Make the input symbolic.
  #if 1
  klee_make_symbolic(moves, sizeof moves, "moves");
  #endif
  for(unsigned i = 0; i < move_count; i++) {
    #if 1
    klee_assume(moves[i] == 0);
    #endif
    moves[i] = rand() & 0x00FF & (i > 100 ? ~0x000C : 0x00FF);
    GUI::set_joypad_state((u16)moves[i]);
    CPU::run_frame();
    u8 *oam = PPU::get_oam_mem();
    //printf("%d, %d", i, oam[3*4+0]);
    #if 1
    if((i+1) % 60 == 0) {
      klee_assert(oam[3*4+0] == 0 | oam[3*4+0] > 200);
    }
    #endif
    #if 0
    if((i+1) % 60 == 0) {
      u32 *pixels = PPU::get_pixels();
      for(unsigned j = 0; j < 240; j+=4) {
        for(unsigned k = 0; k < 256; k+=2) {
          u32 px = pixels[k+j*256];
          u8 r = (u8)((px & 0xFF000000) >> 24);
          u8 g = (u8)((px & 0x00FF0000) >> 16);
          u8 b = (u8)((px & 0x0000FF00) >> 8);
          float lum = (r + g + b)/(256.0*3.0);
          int range = 126-33;
          float lumchar = 33+floor(lum * range);
          printf("%c",(char)(lumchar));
        }
        printf("\n");
      }
      printf("\n");
    }
    #endif
  }
  //printf("done\n");
  return 0;
}

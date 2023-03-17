#include <stdio.h>
#include <emu.h>
#include <cart.h>
#include <cpu.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

/*
Emu components:

Cart > Load and read data from cartridge
CPU > emulate different instructions & registers
Address Bus > reading & writing to addresses (memory mapped)
PPU > pixel processing unit
Timer > timer process

*/

static emu_context ctx;

emu_context *emu_get_context() {
    return &ctx;
}

void delay(u32 ms) {
    SDL_Delay(ms);
}

int emu_run(int argc, char **argv) {
    if (argc < 2) {
        printf("Usage: emu <rom_file>\n");
        return -1;
    }

    if (!cart_load(argv[1])) {
        printf("Failed to load ROM file: %s\n", argv[1]);
        return -2;
    }

    printf("Cart loaded...\n");

    SDL_Init(SDL_INIT_VIDEO);
    printf("SDL INIT\n");
    TTF_Init();
    printf("TTN_INIT\n");

    cpu_init();

    ctx.running = true;
    ctx.paused = false;
    ctx.ticks = 0;

    // while running: if paused delay & continue
    while (ctx.running) {
        if (ctx.paused) {
            delay(10);
            continue;
        }

        // one step CPU, if it fails terminate program
        if (!cpu_step()) {
            printf("CPU Stopped\n");
            return -3;
        }

        // incerement ticks and continue loop
        ctx.ticks++;
    }

    return 0;

}
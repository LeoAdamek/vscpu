#include "cpu.h"
#include <assert.h>

CPU cpu_init(void) {
    CPU cpu = {
        .ac = 0,
        .pc = 0,
        .c  = false,
        .z  = false,
        .clks = 0,
        .memory = { 0 }
    };

    // Ensure we halt befor we run out of memory...
    cpu.memory[MEMORY_WORDS - 1] = INST_HLT;

    return cpu;
}

Opcode cpu_clock(CPU *cpu) {
    Opcode instruction;
    short offset = 0;
    Word address = 0;
    instruction = cpu->memory[cpu->pc++];

    switch (instruction) {
        case INST_HLT:
            return INST_HLT;
        case INST_NOP:
            break;
        case INST_LDA:
            address = cpu->memory[cpu->pc++];
            assert(address < MEMORY_WORDS);
            cpu->ac = cpu->memory[address];
            break;
        case INST_STO:
            address = cpu->memory[cpu->pc++];
            assert(address < MEMORY_WORDS);
            cpu->memory[address] = cpu->ac;
            break;
        case INST_ADD:
            address = cpu->memory[cpu->pc++];
            assert(address < MEMORY_WORDS);
            cpu->ac += cpu->memory[address];
            break;
        case INST_SUB:
            address = cpu->memory[cpu->pc++];
            assert(address < MEMORY_WORDS);
            cpu->ac -= cpu->memory[address];
            break;
        case INST_MOD:
            address = cpu->memory[cpu->pc++];
            assert(address < MEMORY_WORDS);
            cpu->ac %= cpu->memory[address];
            break;
        case INST_CMP:
            address = cpu->memory[cpu->pc++];
            assert(address < MEMORY_WORDS);
            Word value = cpu->memory[address];
            cpu->z = cpu->ac == value;
            break;
        case INST_JNZ:
            if (cpu->z) break;
            goto jmp;
        case INST_JIZ:
            if (!cpu->z) break;
        case INST_JMP:
jmp:
            address = cpu->memory[cpu->pc++];
            assert(address < MEMORY_WORDS);
            cpu->pc = cpu->memory[address];
            break; 
        case INST_DMP:
            printf("CPU[%lu] AC=%04x PC=%04x C=%d Z=%d\n", cpu->clks, cpu->ac, cpu->pc, cpu->c, cpu->z);
            break;
        case INST_PRC:
            putchar(cpu->ac);
            break;
        case INST_INC:
            cpu->ac++;
            break;
        case INST_DEC:
            cpu->ac--;
            break;
        case INST_JRN:
            if (cpu->z) break;
            goto jpr;
        case INST_JRZ:
            if (!cpu->z) break;
        case INST_JPR:
jpr:
            offset = cpu->memory[cpu->pc++];
            cpu->pc += offset;
            break;
        case INST_IOP:
        case INST_IOI:
            printf("NOT IMPLEMENTED!");
            return INST_HLT;
    }

    cpu->clks++;
    return instruction;
}

size_t cpu_load(CPU *cpu, FILE *source) {
    return 0;
}

size_t cpu_run(CPU *cpu) {
    while(cpu_clock(cpu) != INST_HLT);
    return cpu->clks;
}

size_t cpu_dump(CPU *cpu, FILE *dest) {
    return 0;
}
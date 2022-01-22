#ifndef __CPU_H_
#define __CPU_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>

#define MEMORY_WORDS 0x100

/**
 * @brief Word type (16-bit)
 * 
 */
typedef __uint16_t Word;

/**
 * @brief Opcodes for available instructions
 * 
 * Operations are grouped with some bits having special significance:
 * 
 * LSB denotes an operation reads from memory
 * BIT 15 denotes an operation writes to memory (for now only STO does this)
 */
typedef enum {
    INST_NOP = 0x00,

    INST_LDA = 0b000001, // LoAD
    INST_STO = 0b000010, // STOre

    INST_INC = 0b000100, // INCrement
    INST_DEC = 0b001100, // DECrement

    INST_ADD = 0b000101, // ADD
    INST_SUB = 0b001001, // SUBtract
    INST_MOD = 0b001101, // MODulo
    INST_CMP = 0b010001, // CoMPare

    INST_JMP = 0b011001, // JuMP
    INST_JIZ = 0b011101, // Jump If Zero
    INST_JNZ = 0b111101, // Jump if Not Zero

    INST_JPR = 0b011000, // JumP Relative
    INST_JRZ = 0b011100, // Jump Relative if Zero
    INST_JRN = 0b111000, // Jump Relative if Not zero

    INST_DMP = 0b100000, // DuMP
    INST_PRC = 0b100001, // PRint Char

    INST_IOP = 0b110001, // IO Push
    INST_IOI = 0b110010, // IO Input

    /* Reserved */
    INST_HLT = 32768,     // HaLT
} Opcode;

typedef struct {
    Word pc;
    Word ac;
    bool c;
    bool z;
    size_t clks;
    Opcode memory[MEMORY_WORDS]; 
} CPU;

/**
 * @brief Initialize a new CPU
 * 
 * @return CPU 
 */
CPU cpu_init(void);

/**
 * @brief Run the cpu for instruction cycle
 * 
 * @param cpu 
 * @return Opcode executed opcode
 */
Opcode cpu_clock(CPU *cpu);

/**
 * @brief Run the cpu until it hits a HALT
 * 
 * @param cpu 
 * @return size_t Cycles run
 */
size_t cpu_run(CPU *cpu);

/**
 * @brief Load an image from a FILE
 * 
 * @param cpu 
 * @param source 
 * @return size_t 
 */
size_t cpu_load(CPU *cpu, FILE* source);

/**
 * @brief Dump a CPU to the dest FILE
 * 
 * @param cpu 
 * @param dest 
 * @return size_t 
 */
size_t cpu_dump(CPU *cpu, FILE* dest);


#endif /* cpu.h */
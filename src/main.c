#include "cpu.h"

int main(void) {
    CPU cpu = cpu_init();
    Word pc = 0x00, mc = 0x80;

    cpu.memory[mc++] = INST_HLT;

    cpu.memory[pc++] = INST_DMP;
    cpu.memory[pc++] = INST_LDA;
    cpu.memory[pc++] = mc;
    cpu.memory[mc++] = 'a';
    cpu.memory[pc++] = INST_PRC;
    cpu.memory[pc++] = INST_INC;
    cpu.memory[pc++] = INST_CMP;
    cpu.memory[pc++] = mc;
    cpu.memory[mc++] = '{';
    cpu.memory[pc++] = INST_JRN;
    cpu.memory[pc++] = -6;
    cpu.memory[pc++] = INST_LDA;
    cpu.memory[pc++] = mc;
    cpu.memory[mc++] = '\n';
    cpu.memory[pc++] = INST_PRC;
    cpu.memory[pc++] = INST_DMP;
    cpu.memory[pc++] = INST_HLT;

    cpu_run(&cpu);

    return 0;
}
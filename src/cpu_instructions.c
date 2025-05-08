#include "cpu.h"

#include <stdio.h>

void execute_instruction(cpu_t* cpu, memory_t* mem) {
  uint8_t opcode = mem_read(mem, cpu->pc++);

  // Variables used by multiple cases
  uint8_t value, tmp;
  uint16_t addr;
  int8_t offset;
  uint16_t sum;

  printf("PC: 0x%04X - Opcode: 0x%02X\n", cpu->pc, opcode); // Imprimir el PC y el opcode

  switch (opcode) {
    // ----- LDA (Load Accumulator) -----
    case 0xA9:  // Immediate
      cpu->a = mem_read(mem, cpu->pc++);
      set_zn_flags(cpu, cpu->a);
      break;
    case 0xA5:  // Zero Page
      addr = mem_read(mem, cpu->pc++);
      cpu->a = mem_read(mem, addr);
      set_zn_flags(cpu, cpu->a);
      break;
    case 0xB5:  // Zero Page, X
      addr = (mem_read(mem, cpu->pc++) + cpu->x) & 0xFF;
      cpu->a = mem_read(mem, addr);
      set_zn_flags(cpu, cpu->a);
      break;
    case 0xAD:  // Absolute
      addr = mem_read(mem, cpu->pc++);
      addr |= (mem_read(mem, cpu->pc++) << 8);
      cpu->a = mem_read(mem, addr);
      set_zn_flags(cpu, cpu->a);
      break;
    case 0xBD:  // Absolute, X
      addr = mem_read(mem, cpu->pc++);
      addr |= (mem_read(mem, cpu->pc++) << 8);
      addr += cpu->x;
      cpu->a = mem_read(mem, addr);
      set_zn_flags(cpu, cpu->a);
      break;
    case 0xB9:  // Absolute, Y
      addr = mem_read(mem, cpu->pc++);
      addr |= (mem_read(mem, cpu->pc++) << 8);
      addr += cpu->y;
      cpu->a = mem_read(mem, addr);
      set_zn_flags(cpu, cpu->a);
      break;
    case 0xA1:  // (Indirect, X)
      tmp = (mem_read(mem, cpu->pc++) + cpu->x) & 0xFF;
      addr = mem_read(mem, tmp);
      addr |= (mem_read(mem, (tmp + 1) & 0xFF) << 8);
      cpu->a = mem_read(mem, addr);
      set_zn_flags(cpu, cpu->a);
      break;
    case 0xB1:  // (Indirect), Y
      tmp = mem_read(mem, cpu->pc++);
      addr = mem_read(mem, tmp);
      addr |= (mem_read(mem, (tmp + 1) & 0xFF) << 8);
      addr += cpu->y;
      cpu->a = mem_read(mem, addr);
      set_zn_flags(cpu, cpu->a);
      break;

    // ----- LDX (Load X Register) -----
    case 0xA2:  // Immediate
      cpu->x = mem_read(mem, cpu->pc++);
      set_zn_flags(cpu, cpu->x);
      break;
    case 0xA6:  // Zero Page
      addr = mem_read(mem, cpu->pc++);
      cpu->x = mem_read(mem, addr);
      set_zn_flags(cpu, cpu->x);
      break;
    case 0xB6:  // Zero Page, Y
      addr = (mem_read(mem, cpu->pc++) + cpu->y) & 0xFF;
      cpu->x = mem_read(mem, addr);
      set_zn_flags(cpu, cpu->x);
      break;
    case 0xAE:  // Absolute
      addr = mem_read(mem, cpu->pc++);
      addr |= (mem_read(mem, cpu->pc++) << 8);
      cpu->x = mem_read(mem, addr);
      set_zn_flags(cpu, cpu->x);
      break;
    case 0xBE:  // Absolute, Y
      addr = mem_read(mem, cpu->pc++);
      addr |= (mem_read(mem, cpu->pc++) << 8);
      addr += cpu->y;
      cpu->x = mem_read(mem, addr);
      set_zn_flags(cpu, cpu->x);
      break;

    // ----- LDY (Load Y Register) -----
    case 0xA0:  // Immediate
      cpu->y = mem_read(mem, cpu->pc++);
      set_zn_flags(cpu, cpu->y);
      break;
    case 0xA4:  // Zero Page
      addr = mem_read(mem, cpu->pc++);
      cpu->y = mem_read(mem, addr);
      set_zn_flags(cpu, cpu->y);
      break;
    case 0xB4:  // Zero Page, X
      addr = (mem_read(mem, cpu->pc++) + cpu->x) & 0xFF;
      cpu->y = mem_read(mem, addr);
      set_zn_flags(cpu, cpu->y);
      break;
    case 0xAC:  // Absolute
      addr = mem_read(mem, cpu->pc++);
      addr |= (mem_read(mem, cpu->pc++) << 8);
      cpu->y = mem_read(mem, addr);
      set_zn_flags(cpu, cpu->y);
      break;
    case 0xBC:  // Absolute, X
      addr = mem_read(mem, cpu->pc++);
      addr |= (mem_read(mem, cpu->pc++) << 8);
      addr += cpu->x;
      cpu->y = mem_read(mem, addr);
      set_zn_flags(cpu, cpu->y);
      break;

    // ----- STA (Store Accumulator) -----
    case 0x85:  // Zero Page
      addr = mem_read(mem, cpu->pc++);
      mem_write(mem, addr, cpu->a);
      break;
    case 0x95:  // Zero Page, X
      addr = (mem_read(mem, cpu->pc++) + cpu->x) & 0xFF;
      mem_write(mem, addr, cpu->a);
      break;
    case 0x8D:  // Absolute
      addr = mem_read(mem, cpu->pc++);
      addr |= (mem_read(mem, cpu->pc++) << 8);
      mem_write(mem, addr, cpu->a);
      break;
    case 0x9D:  // Absolute, X
      addr = mem_read(mem, cpu->pc++);
      addr |= (mem_read(mem, cpu->pc++) << 8);
      addr += cpu->x;
      mem_write(mem, addr, cpu->a);
      break;
    case 0x99:  // Absolute, Y
      addr = mem_read(mem, cpu->pc++);
      addr |= (mem_read(mem, cpu->pc++) << 8);
      addr += cpu->y;
      mem_write(mem, addr, cpu->a);
      break;
    case 0x81:  // (Indirect, X)
      tmp = (mem_read(mem, cpu->pc++) + cpu->x) & 0xFF;
      addr = mem_read(mem, tmp);
      addr |= (mem_read(mem, (tmp + 1) & 0xFF) << 8);
      mem_write(mem, addr, cpu->a);
      break;
    case 0x91:  // (Indirect), Y
      tmp = mem_read(mem, cpu->pc++);
      addr = mem_read(mem, tmp);
      addr |= (mem_read(mem, (tmp + 1) & 0xFF) << 8);
      addr += cpu->y;
      mem_write(mem, addr, cpu->a);
      break;

    // ----- STX (Store X Register) -----
    case 0x86:  // Zero Page
      addr = mem_read(mem, cpu->pc++);
      mem_write(mem, addr, cpu->x);
      break;
    case 0x96:  // Zero Page, Y
      addr = (mem_read(mem, cpu->pc++) + cpu->y) & 0xFF;
      mem_write(mem, addr, cpu->x);
      break;
    case 0x8E:  // Absolute
      addr = mem_read(mem, cpu->pc++);
      addr |= (mem_read(mem, cpu->pc++) << 8);
      mem_write(mem, addr, cpu->x);
      break;

    // ----- STY (Store Y Register) -----
    case 0x84:  // Zero Page
      addr = mem_read(mem, cpu->pc++);
      mem_write(mem, addr, cpu->y);
      break;
    case 0x94:  // Zero Page, X
      addr = (mem_read(mem, cpu->pc++) + cpu->x) & 0xFF;
      mem_write(mem, addr, cpu->y);
      break;
    case 0x8C:  // Absolute
      addr = mem_read(mem, cpu->pc++);
      addr |= (mem_read(mem, cpu->pc++) << 8);
      mem_write(mem, addr, cpu->y);
      break;

    // ----- TAX, TAY, TXA, TYA (Register Transfers) -----
    case 0xAA:  // TAX
      cpu->x = cpu->a;
      set_zn_flags(cpu, cpu->x);
      break;
    case 0xA8:  // TAY
      cpu->y = cpu->a;
      set_zn_flags(cpu, cpu->y);
      break;
    case 0x8A:  // TXA
      cpu->a = cpu->x;
      set_zn_flags(cpu, cpu->a);
      break;
    case 0x98:  // TYA
      cpu->a = cpu->y;
      set_zn_flags(cpu, cpu->a);
      break;

    // ----- TXS, TSX (Stack Pointer Transfers) -----
    case 0x9A:  // TXS
      cpu->sp = cpu->x;
      break;
    case 0xBA:  // TSX
      cpu->x = cpu->sp;
      set_zn_flags(cpu, cpu->x);
      break;

    // ----- PHA, PLA, PHP, PLP (Stack Operations) -----
    case 0x48:  // PHA - Push Accumulator
      mem_write(mem, 0x0100 + cpu->sp--, cpu->a);
      break;
    case 0x68:  // PLA - Pull Accumulator
      cpu->a = mem_read(mem, 0x0100 + ++cpu->sp);
      set_zn_flags(cpu, cpu->a);
      break;
    case 0x08:  // PHP - Push Processor Status
      mem_write(mem, 0x0100 + cpu->sp--, cpu->p | FLAG_BREAK | FLAG_UNUSED);
      break;
    case 0x28:  // PLP - Pull Processor Status
      cpu->p = mem_read(mem, 0x0100 + ++cpu->sp) & ~(FLAG_BREAK | FLAG_UNUSED);
      break;

    // ----- AND (Logical AND with Accumulator) -----
    case 0x29:  // Immediate
      cpu->a &= mem_read(mem, cpu->pc++);
      set_zn_flags(cpu, cpu->a);
      break;
    case 0x25:  // Zero Page
      addr = mem_read(mem, cpu->pc++);
      cpu->a &= mem_read(mem, addr);
      set_zn_flags(cpu, cpu->a);
      break;
    case 0x35:  // Zero Page, X
      addr = (mem_read(mem, cpu->pc++) + cpu->x) & 0xFF;
      cpu->a &= mem_read(mem, addr);
      set_zn_flags(cpu, cpu->a);
      break;
    case 0x2D:  // Absolute
      addr = mem_read(mem, cpu->pc++);
      addr |= (mem_read(mem, cpu->pc++) << 8);
      cpu->a &= mem_read(mem, addr);
      set_zn_flags(cpu, cpu->a);
      break;
    case 0x3D:  // Absolute, X
      addr = mem_read(mem, cpu->pc++);
      addr |= (mem_read(mem, cpu->pc++) << 8);
      addr += cpu->x;
      cpu->a &= mem_read(mem, addr);
      set_zn_flags(cpu, cpu->a);
      break;
    case 0x39:  // Absolute, Y
      addr = mem_read(mem, cpu->pc++);
      addr |= (mem_read(mem, cpu->pc++) << 8);
      addr += cpu->y;
      cpu->a &= mem_read(mem, addr);
      set_zn_flags(cpu, cpu->a);
      break;
    case 0x21:  // (Indirect, X)
      tmp = (mem_read(mem, cpu->pc++) + cpu->x) & 0xFF;
      addr = mem_read(mem, tmp);
      addr |= (mem_read(mem, (tmp + 1) & 0xFF) << 8);
      cpu->a &= mem_read(mem, addr);
      set_zn_flags(cpu, cpu->a);
      break;
    case 0x31:  // (Indirect), Y
      tmp = mem_read(mem, cpu->pc++);
      addr = mem_read(mem, tmp);
      addr |= (mem_read(mem, (tmp + 1) & 0xFF) << 8);
      addr += cpu->y;
      cpu->a &= mem_read(mem, addr);
      set_zn_flags(cpu, cpu->a);
      break;

    // ----- ORA (Logical OR with Accumulator) -----
    case 0x09:  // Immediate
      cpu->a |= mem_read(mem, cpu->pc++);
      set_zn_flags(cpu, cpu->a);
      break;
    case 0x05:  // Zero Page
      addr = mem_read(mem, cpu->pc++);
      cpu->a |= mem_read(mem, addr);
      set_zn_flags(cpu, cpu->a);
      break;
    case 0x15:  // Zero Page, X
      addr = (mem_read(mem, cpu->pc++) + cpu->x) & 0xFF;
      cpu->a |= mem_read(mem, addr);
      set_zn_flags(cpu, cpu->a);
      break;
    case 0x0D:  // Absolute
      addr = mem_read(mem, cpu->pc++);
      addr |= (mem_read(mem, cpu->pc++) << 8);
      cpu->a |= mem_read(mem, addr);
      set_zn_flags(cpu, cpu->a);
      break;
    case 0x1D:  // Absolute, X
      addr = mem_read(mem, cpu->pc++);
      addr |= (mem_read(mem, cpu->pc++) << 8);
      addr += cpu->x;
      cpu->a |= mem_read(mem, addr);
      set_zn_flags(cpu, cpu->a);
      break;
    case 0x19:  // Absolute, Y
      addr = mem_read(mem, cpu->pc++);
      addr |= (mem_read(mem, cpu->pc++) << 8);
      addr += cpu->y;
      cpu->a |= mem_read(mem, addr);
      set_zn_flags(cpu, cpu->a);
      break;
    case 0x01:  // (Indirect, X)
      tmp = (mem_read(mem, cpu->pc++) + cpu->x) & 0xFF;
      addr = mem_read(mem, tmp);
      addr |= (mem_read(mem, (tmp + 1) & 0xFF) << 8);
      cpu->a |= mem_read(mem, addr);
      set_zn_flags(cpu, cpu->a);
      break;
    case 0x11:  // (Indirect), Y
      tmp = mem_read(mem, cpu->pc++);
      addr = mem_read(mem, tmp);
      addr |= (mem_read(mem, (tmp + 1) & 0xFF) << 8);
      addr += cpu->y;
      cpu->a |= mem_read(mem, addr);
      set_zn_flags(cpu, cpu->a);
      break;

    // ----- EOR (Exclusive OR with Accumulator) -----
    case 0x49:  // Immediate
      cpu->a ^= mem_read(mem, cpu->pc++);
      set_zn_flags(cpu, cpu->a);
      break;
    case 0x45:  // Zero Page
      addr = mem_read(mem, cpu->pc++);
      cpu->a ^= mem_read(mem, addr);
      set_zn_flags(cpu, cpu->a);
      break;
    case 0x55:  // Zero Page, X
      addr = (mem_read(mem, cpu->pc++) + cpu->x) & 0xFF;
      cpu->a ^= mem_read(mem, addr);
      set_zn_flags(cpu, cpu->a);
      break;
    case 0x4D:  // Absolute
      addr = mem_read(mem, cpu->pc++);
      addr |= (mem_read(mem, cpu->pc++) << 8);
      cpu->a ^= mem_read(mem, addr);
      set_zn_flags(cpu, cpu->a);
      break;
    case 0x5D:  // Absolute, X
      addr = mem_read(mem, cpu->pc++);
      addr |= (mem_read(mem, cpu->pc++) << 8);
      addr += cpu->x;
      cpu->a ^= mem_read(mem, addr);
      set_zn_flags(cpu, cpu->a);
      break;
    case 0x59:  // Absolute, Y
      addr = mem_read(mem, cpu->pc++);
      addr |= (mem_read(mem, cpu->pc++) << 8);
      addr += cpu->y;
      cpu->a ^= mem_read(mem, addr);
      set_zn_flags(cpu, cpu->a);
      break;
    case 0x41:  // (Indirect, X)
      tmp = (mem_read(mem, cpu->pc++) + cpu->x) & 0xFF;
      addr = mem_read(mem, tmp);
      addr |= (mem_read(mem, (tmp + 1) & 0xFF) << 8);
      cpu->a ^= mem_read(mem, addr);
      set_zn_flags(cpu, cpu->a);
      break;
    case 0x51:  // (Indirect), Y
      tmp = mem_read(mem, cpu->pc++);
      addr = mem_read(mem, tmp);
      addr |= (mem_read(mem, (tmp + 1) & 0xFF) << 8);
      addr += cpu->y;
      cpu->a ^= mem_read(mem, addr);
      set_zn_flags(cpu, cpu->a);
      break;

    // ----- ADC (Add with Carry) -----
    case 0x69:  // Immediate
      value = mem_read(mem, cpu->pc++);
      sum = cpu->a + value + (cpu->p & FLAG_CARRY ? 1 : 0);
      cpu->p = (cpu->p & ~(FLAG_OVERFLOW | FLAG_CARRY)) |
               ((~(cpu->a ^ value) & (cpu->a ^ sum) & 0x80) ? FLAG_OVERFLOW : 0) |
               (sum > 0xFF ? FLAG_CARRY : 0);
      cpu->a = (uint8_t)sum;
      set_zn_flags(cpu, cpu->a);
      break;
    case 0x65:  // Zero Page
      addr = mem_read(mem, cpu->pc++);
      value = mem_read(mem, addr);
      sum = cpu->a + value + (cpu->p & FLAG_CARRY ? 1 : 0);
      cpu->p = (cpu->p & ~(FLAG_OVERFLOW | FLAG_CARRY)) |
               ((~(cpu->a ^ value) & (cpu->a ^ sum) & 0x80) ? FLAG_OVERFLOW : 0) |
               (sum > 0xFF ? FLAG_CARRY : 0);
      cpu->a = (uint8_t)sum;
      set_zn_flags(cpu, cpu->a);
      break;
    case 0x75:  // Zero Page, X
      addr = (mem_read(mem, cpu->pc++) + cpu->x) & 0xFF;
      value = mem_read(mem, addr);
      sum = cpu->a + value + (cpu->p & FLAG_CARRY ? 1 : 0);
      cpu->p = (cpu->p & ~(FLAG_OVERFLOW | FLAG_CARRY)) |
               ((~(cpu->a ^ value) & (cpu->a ^ sum) & 0x80) ? FLAG_OVERFLOW : 0) |
               (sum > 0xFF ? FLAG_CARRY : 0);
      cpu->a = (uint8_t)sum;
      set_zn_flags(cpu, cpu->a);
      break;
    case 0x6D:  // Absolute
      addr = mem_read(mem, cpu->pc++);
      addr |= (mem_read(mem, cpu->pc++) << 8);
      value = mem_read(mem, addr);
      sum = cpu->a + value + (cpu->p & FLAG_CARRY ? 1 : 0);
      cpu->p = (cpu->p & ~(FLAG_OVERFLOW | FLAG_CARRY)) |
               ((~(cpu->a ^ value) & (cpu->a ^ sum) & 0x80) ? FLAG_OVERFLOW : 0) |
               (sum > 0xFF ? FLAG_CARRY : 0);
      cpu->a = (uint8_t)sum;
      set_zn_flags(cpu, cpu->a);
      break;
    case 0x7D:  // Absolute, X
      addr = mem_read(mem, cpu->pc++);
      addr |= (mem_read(mem, cpu->pc++) << 8);
      addr += cpu->x;
      value = mem_read(mem, addr);
      sum = cpu->a + value + (cpu->p & FLAG_CARRY ? 1 : 0);
      cpu->p = (cpu->p & ~(FLAG_OVERFLOW | FLAG_CARRY)) |
               ((~(cpu->a ^ value) & (cpu->a ^ sum) & 0x80) ? FLAG_OVERFLOW : 0) |
               (sum > 0xFF ? FLAG_CARRY : 0);
      cpu->a = (uint8_t)sum;
      set_zn_flags(cpu, cpu->a);
      break;
    case 0x79:  // Absolute, Y
      addr = mem_read(mem, cpu->pc++);
      addr |= (mem_read(mem, cpu->pc++) << 8);
      addr += cpu->y;
      value = mem_read(mem, addr);
      sum = cpu->a + value + (cpu->p & FLAG_CARRY ? 1 : 0);
      cpu->p = (cpu->p & ~(FLAG_OVERFLOW | FLAG_CARRY)) |
               ((~(cpu->a ^ value) & (cpu->a ^ sum) & 0x80) ? FLAG_OVERFLOW : 0) |
               (sum > 0xFF ? FLAG_CARRY : 0);
      cpu->a = (uint8_t)sum;
      set_zn_flags(cpu, cpu->a);
      break;
    case 0x61:  // (Indirect, X)
      tmp = (mem_read(mem, cpu->pc++) + cpu->x) & 0xFF;
      addr = mem_read(mem, tmp);
      addr |= (mem_read(mem, (tmp + 1) & 0xFF) << 8);
      value = mem_read(mem, addr);
      sum = cpu->a + value + (cpu->p & FLAG_CARRY ? 1 : 0);
      cpu->p = (cpu->p & ~(FLAG_OVERFLOW | FLAG_CARRY)) |
               ((~(cpu->a ^ value) & (cpu->a ^ sum) & 0x80) ? FLAG_OVERFLOW : 0) |
               (sum > 0xFF ? FLAG_CARRY : 0);
      cpu->a = (uint8_t)sum;
      set_zn_flags(cpu, cpu->a);
      break;
    case 0x71:  // (Indirect), Y
      tmp = mem_read(mem, cpu->pc++);
      addr = mem_read(mem, tmp);
      addr |= (mem_read(mem, (tmp + 1) & 0xFF) << 8);
      addr += cpu->y;
      value = mem_read(mem, addr);
      sum = cpu->a + value + (cpu->p & FLAG_CARRY ? 1 : 0);
      cpu->p = (cpu->p & ~(FLAG_OVERFLOW | FLAG_CARRY)) |
               ((~(cpu->a ^ value) & (cpu->a ^ sum) & 0x80) ? FLAG_OVERFLOW : 0) |
               (sum > 0xFF ? FLAG_CARRY : 0);
      cpu->a = (uint8_t)sum;
      set_zn_flags(cpu, cpu->a);
      break;

    // ----- SBC (Subtract with Carry) -----
    case 0xE9:  // Immediate
      value = mem_read(mem, cpu->pc++);
      sum = cpu->a - value - (cpu->p & FLAG_CARRY ? 0 : 1);
      cpu->p = (cpu->p & ~(FLAG_OVERFLOW | FLAG_CARRY)) |
               (((cpu->a ^ value) & (cpu->a ^ sum) & 0x80) ? FLAG_OVERFLOW : 0) |
               (sum < 0x100 ? FLAG_CARRY : 0);
      cpu->a = (uint8_t)sum;
      set_zn_flags(cpu, cpu->a);
      break;
    case 0xE5:  // Zero Page
      addr = mem_read(mem, cpu->pc++);
      value = mem_read(mem, addr);
      sum = cpu->a - value - (cpu->p & FLAG_CARRY ? 0 : 1);
      cpu->p = (cpu->p & ~(FLAG_OVERFLOW | FLAG_CARRY)) |
               (((cpu->a ^ value) & (cpu->a ^ sum) & 0x80) ? FLAG_OVERFLOW : 0) |
               (sum < 0x100 ? FLAG_CARRY : 0);
      cpu->a = (uint8_t)sum;
      set_zn_flags(cpu, cpu->a);
      break;
    case 0xF5:  // Zero Page, X
      addr = (mem_read(mem, cpu->pc++) + cpu->x) & 0xFF;
      value = mem_read(mem, addr);
      sum = cpu->a - value - (cpu->p & FLAG_CARRY ? 0 : 1);
      cpu->p = (cpu->p & ~(FLAG_OVERFLOW | FLAG_CARRY)) |
               (((cpu->a ^ value) & (cpu->a ^ sum) & 0x80) ? FLAG_OVERFLOW : 0) |
               (sum < 0x100 ? FLAG_CARRY : 0);
      cpu->a = (uint8_t)sum;
      set_zn_flags(cpu, cpu->a);
      break;
    case 0xED:  // Absolute
      addr = mem_read(mem, cpu->pc++);
      addr |= (mem_read(mem, cpu->pc++) << 8);
      value = mem_read(mem, addr);
      sum = cpu->a - value - (cpu->p & FLAG_CARRY ? 0 : 1);
      cpu->p = (cpu->p & ~(FLAG_OVERFLOW | FLAG_CARRY)) |
               (((cpu->a ^ value) & (cpu->a ^ sum) & 0x80) ? FLAG_OVERFLOW : 0) |
               (sum < 0x100 ? FLAG_CARRY : 0);
      cpu->a = (uint8_t)sum;
      set_zn_flags(cpu, cpu->a);
      break;
    case 0xFD:  // Absolute, X
      addr = mem_read(mem, cpu->pc++);
      addr |= (mem_read(mem, cpu->pc++) << 8);
      addr += cpu->x;
      value = mem_read(mem, addr);
      sum = cpu->a - value - (cpu->p & FLAG_CARRY ? 0 : 1);
      cpu->p = (cpu->p & ~(FLAG_OVERFLOW | FLAG_CARRY)) |
               (((cpu->a ^ value) & (cpu->a ^ sum) & 0x80) ? FLAG_OVERFLOW : 0) |
               (sum < 0x100 ? FLAG_CARRY : 0);
      cpu->a = (uint8_t)sum;
      set_zn_flags(cpu, cpu->a);
      break;
    case 0xF9:  // Absolute, Y
      addr = mem_read(mem, cpu->pc++);
      addr |= (mem_read(mem, cpu->pc++) << 8);
      addr += cpu->y;
      value = mem_read(mem, addr);
      sum = cpu->a - value - (cpu->p & FLAG_CARRY ? 0 : 1);
      cpu->p = (cpu->p & ~(FLAG_OVERFLOW | FLAG_CARRY)) |
               (((cpu->a ^ value) & (cpu->a ^ sum) & 0x80) ? FLAG_OVERFLOW : 0) |
               (sum < 0x100 ? FLAG_CARRY : 0);
      cpu->a = (uint8_t)sum;
      set_zn_flags(cpu, cpu->a);
      break;
    case 0xE1:  // (Indirect, X)
      tmp = (mem_read(mem, cpu->pc++) + cpu->x) & 0xFF;
      addr = mem_read(mem, tmp);
      addr |= (mem_read(mem, (tmp + 1) & 0xFF) << 8);
      value = mem_read(mem, addr);
      sum = cpu->a - value - (cpu->p & FLAG_CARRY ? 0 : 1);
      cpu->p = (cpu->p & ~(FLAG_OVERFLOW | FLAG_CARRY)) |
               (((cpu->a ^ value) & (cpu->a ^ sum) & 0x80) ? FLAG_OVERFLOW : 0) |
               (sum < 0x100 ? FLAG_CARRY : 0);
      cpu->a = (uint8_t)sum;
      set_zn_flags(cpu, cpu->a);
      break;
    case 0xF1:  // (Indirect), Y
      tmp = mem_read(mem, cpu->pc++);
      addr = mem_read(mem, tmp);
      addr |= (mem_read(mem, (tmp + 1) & 0xFF) << 8);
      addr += cpu->y;
      value = mem_read(mem, addr);
      sum = cpu->a - value - (cpu->p & FLAG_CARRY ? 0 : 1);
      cpu->p = (cpu->p & ~(FLAG_OVERFLOW | FLAG_CARRY)) |
               (((cpu->a ^ value) & (cpu->a ^ sum) & 0x80) ? FLAG_OVERFLOW : 0) |
               (sum < 0x100 ? FLAG_CARRY : 0);
      cpu->a = (uint8_t)sum;
      set_zn_flags(cpu, cpu->a);
      break;

    // ----- CMP (Compare Accumulator) -----
    case 0xC9:  // Immediate
      value = mem_read(mem, cpu->pc++);
      tmp = cpu->a - value;
      cpu->p = (cpu->p & ~(FLAG_ZERO | FLAG_NEGATIVE | FLAG_CARRY)) |
               (cpu->a >= value ? FLAG_CARRY : 0) | (tmp == 0 ? FLAG_ZERO : 0) |
               (tmp & 0x80 ? FLAG_NEGATIVE : 0);
      break;
    case 0xC5:  // Zero Page
      addr = mem_read(mem, cpu->pc++);
      value = mem_read(mem, addr);
      tmp = cpu->a - value;
      cpu->p = (cpu->p & ~(FLAG_ZERO | FLAG_NEGATIVE | FLAG_CARRY)) |
               (cpu->a >= value ? FLAG_CARRY : 0);

      cpu->a = (uint8_t)sum;
      set_zn_flags(cpu, cpu->a);
      break;
    case 0xD5:  // Zero Page, X
      addr = (mem_read(mem, cpu->pc++) + cpu->x) & 0xFF;
      value = mem_read(mem, addr);
      tmp = cpu->a - value;
      cpu->p = (cpu->p & ~(FLAG_ZERO | FLAG_NEGATIVE | FLAG_CARRY)) |
               (cpu->a >= value ? FLAG_CARRY : 0) | (tmp == 0 ? FLAG_ZERO : 0) |
               (tmp & 0x80 ? FLAG_NEGATIVE : 0);
      break;
    case 0xCD:  // Absolute
      addr = mem_read(mem, cpu->pc++);
      addr |= (mem_read(mem, cpu->pc++) << 8);
      value = mem_read(mem, addr);
      tmp = cpu->a - value;
      cpu->p = (cpu->p & ~(FLAG_ZERO | FLAG_NEGATIVE | FLAG_CARRY)) |
               (cpu->a >= value ? FLAG_CARRY : 0) | (tmp == 0 ? FLAG_ZERO : 0) |
               (tmp & 0x80 ? FLAG_NEGATIVE : 0);
      break;
    case 0xDD:  // Absolute, X
      addr = mem_read(mem, cpu->pc++);
      addr |= (mem_read(mem, cpu->pc++) << 8);
      addr += cpu->x;
      value = mem_read(mem, addr);
      tmp = cpu->a - value;
      cpu->p = (cpu->p & ~(FLAG_ZERO | FLAG_NEGATIVE | FLAG_CARRY)) |
               (cpu->a >= value ? FLAG_CARRY : 0) | (tmp == 0 ? FLAG_ZERO : 0) |
               (tmp & 0x80 ? FLAG_NEGATIVE : 0);
      break;
    case 0xD9:  // Absolute, Y
      addr = mem_read(mem, cpu->pc++);
      addr |= (mem_read(mem, cpu->pc++) << 8);
      addr += cpu->y;
      value = mem_read(mem, addr);
      tmp = cpu->a - value;
      cpu->p = (cpu->p & ~(FLAG_ZERO | FLAG_NEGATIVE | FLAG_CARRY)) |
               (cpu->a >= value ? FLAG_CARRY : 0) | (tmp == 0 ? FLAG_ZERO : 0) |
               (tmp & 0x80 ? FLAG_NEGATIVE : 0);
      break;
    case 0xC1:  // (Indirect, X)
      tmp = (mem_read(mem, cpu->pc++) + cpu->x) & 0xFF;
      addr = mem_read(mem, tmp);
      addr |= (mem_read(mem, (tmp + 1) & 0xFF) << 8);
      value = mem_read(mem, addr);
      tmp = cpu->a - value;
      cpu->p = (cpu->p & ~(FLAG_ZERO | FLAG_NEGATIVE | FLAG_CARRY)) |
               (cpu->a >= value ? FLAG_CARRY : 0) | (tmp == 0 ? FLAG_ZERO : 0) |
               (tmp & 0x80 ? FLAG_NEGATIVE : 0);
      break;
    case 0xD1:  // (Indirect), Y
      tmp = mem_read(mem, cpu->pc++);
      addr = mem_read(mem, tmp);
      addr |= (mem_read(mem, (tmp + 1) & 0xFF) << 8);
      addr += cpu->y;
      value = mem_read(mem, addr);
      tmp = cpu->a - value;
      cpu->p = (cpu->p & ~(FLAG_ZERO | FLAG_NEGATIVE | FLAG_CARRY)) |
               (cpu->a >= value ? FLAG_CARRY : 0) | (tmp == 0 ? FLAG_ZERO : 0) |
               (tmp & 0x80 ? FLAG_NEGATIVE : 0);
      break;

    // ----- CPX (Compare X Register) -----
    case 0xE0:  // Immediate
      value = mem_read(mem, cpu->pc++);
      tmp = cpu->x - value;
      cpu->p = (cpu->p & ~(FLAG_ZERO | FLAG_NEGATIVE | FLAG_CARRY)) |
               (cpu->x >= value ? FLAG_CARRY : 0) | (tmp == 0 ? FLAG_ZERO : 0) |
               (tmp & 0x80 ? FLAG_NEGATIVE : 0);
      break;
    case 0xE4:  // Zero Page
      addr = mem_read(mem, cpu->pc++);
      value = mem_read(mem, addr);
      tmp = cpu->x - value;
      cpu->p = (cpu->p & ~(FLAG_ZERO | FLAG_NEGATIVE | FLAG_CARRY)) |
               (cpu->x >= value ? FLAG_CARRY : 0) | (tmp == 0 ? FLAG_ZERO : 0) |
               (tmp & 0x80 ? FLAG_NEGATIVE : 0);
      break;
    case 0xEC:  // Absolute
      addr = mem_read(mem, cpu->pc++);
      addr |= (mem_read(mem, cpu->pc++) << 8);
      value = mem_read(mem, addr);
      tmp = cpu->x - value;
      cpu->p = (cpu->p & ~(FLAG_ZERO | FLAG_NEGATIVE | FLAG_CARRY)) |
               (cpu->x >= value ? FLAG_CARRY : 0) | (tmp == 0 ? FLAG_ZERO : 0) |
               (tmp & 0x80 ? FLAG_NEGATIVE : 0);
      break;

    // ----- CPY (Compare Y Register) -----
    case 0xC0:  // Immediate
      value = mem_read(mem, cpu->pc++);
      tmp = cpu->y - value;
      cpu->p = (cpu->p & ~(FLAG_ZERO | FLAG_NEGATIVE | FLAG_CARRY)) |
               (cpu->y >= value ? FLAG_CARRY : 0) | (tmp == 0 ? FLAG_ZERO : 0) |
               (tmp & 0x80 ? FLAG_NEGATIVE : 0);
      break;
    case 0xC4:  // Zero Page
      addr = mem_read(mem, cpu->pc++);
      value = mem_read(mem, addr);
      tmp = cpu->y - value;
      cpu->p = (cpu->p & ~(FLAG_ZERO | FLAG_NEGATIVE | FLAG_CARRY)) |
               (cpu->y >= value ? FLAG_CARRY : 0) | (tmp == 0 ? FLAG_ZERO : 0) |
               (tmp & 0x80 ? FLAG_NEGATIVE : 0);
      break;
    case 0xCC:  // Absolute
      addr = mem_read(mem, cpu->pc++);
      addr |= (mem_read(mem, cpu->pc++) << 8);
      value = mem_read(mem, addr);
      tmp = cpu->y - value;
      cpu->p = (cpu->p & ~(FLAG_ZERO | FLAG_NEGATIVE | FLAG_CARRY)) |
               (cpu->y >= value ? FLAG_CARRY : 0) | (tmp == 0 ? FLAG_ZERO : 0) |
               (tmp & 0x80 ? FLAG_NEGATIVE : 0);
      break;

    // ----- INC (Increment Memory) -----
    case 0xE6:  // Zero Page
      addr = mem_read(mem, cpu->pc++);
      value = mem_read(mem, addr) + 1;
      mem_write(mem, addr, value);
      set_zn_flags(cpu, value);
      break;
    case 0xF6:  // Zero Page, X
      addr = (mem_read(mem, cpu->pc++) + cpu->x) & 0xFF;
      value = mem_read(mem, addr) + 1;
      mem_write(mem, addr, value);
      set_zn_flags(cpu, value);
      break;
    case 0xEE:  // Absolute
      addr = mem_read(mem, cpu->pc++);
      addr |= (mem_read(mem, cpu->pc++) << 8);
      value = mem_read(mem, addr) + 1;
      mem_write(mem, addr, value);
      set_zn_flags(cpu, value);
      break;
    case 0xFE:  // Absolute, X
      addr = mem_read(mem, cpu->pc++);
      addr |= (mem_read(mem, cpu->pc++) << 8);
      addr += cpu->x;
      value = mem_read(mem, addr) + 1;
      mem_write(mem, addr, value);
      set_zn_flags(cpu, value);
      break;

    // ----- DEC (Decrement Memory) -----
    case 0xC6:  // Zero Page
      addr = mem_read(mem, cpu->pc++);
      value = mem_read(mem, addr) - 1;
      mem_write(mem, addr, value);
      set_zn_flags(cpu, value);
      break;
    case 0xD6:  // Zero Page, X
      addr = (mem_read(mem, cpu->pc++) + cpu->x) & 0xFF;
      value = mem_read(mem, addr) - 1;
      mem_write(mem, addr, value);
      set_zn_flags(cpu, value);
      break;
    case 0xCE:  // Absolute
      addr = mem_read(mem, cpu->pc++);
      addr |= (mem_read(mem, cpu->pc++) << 8);
      value = mem_read(mem, addr) - 1;
      mem_write(mem, addr, value);
      set_zn_flags(cpu, value);
      break;
    case 0xDE:  // Absolute, X
      addr = mem_read(mem, cpu->pc++);
      addr |= (mem_read(mem, cpu->pc++) << 8);
      addr += cpu->x;
      value = mem_read(mem, addr) - 1;
      mem_write(mem, addr, value);
      set_zn_flags(cpu, value);
      break;

    // ----- INX, INY (Increment Registers) -----
    case 0xE8:  // INX
      cpu->x = (cpu->x + 1) & 0xFF;
      set_zn_flags(cpu, cpu->x);
      break;
    case 0xC8:  // INY
      cpu->y = (cpu->y + 1) & 0xFF;
      set_zn_flags(cpu, cpu->y);
      break;

    // ----- DEX, DEY (Decrement Registers) -----
    case 0xCA:  // DEX
      cpu->x = (cpu->x - 1) & 0xFF;
      set_zn_flags(cpu, cpu->x);
      break;
    case 0x88:  // DEY
      cpu->y = (cpu->y - 1) & 0xFF;
      set_zn_flags(cpu, cpu->y);
      break;

    // ----- ASL (Arithmetic Shift Left) -----
    case 0x0A:  // Accumulator
      cpu->p = (cpu->p & ~FLAG_CARRY) | ((cpu->a & 0x80) ? FLAG_CARRY : 0);
      cpu->a = (cpu->a << 1) & 0xFF;
      set_zn_flags(cpu, cpu->a);
      break;
    case 0x06:  // Zero Page
      addr = mem_read(mem, cpu->pc++);
      value = mem_read(mem, addr);
      cpu->p = (cpu->p & ~FLAG_CARRY) | ((value & 0x80) ? FLAG_CARRY : 0);
      value = (value << 1) & 0xFF;
      mem_write(mem, addr, value);
      set_zn_flags(cpu, value);
      break;
    case 0x16:  // Zero Page, X
      addr = (mem_read(mem, cpu->pc++) + cpu->x) & 0xFF;
      value = mem_read(mem, addr);
      cpu->p = (cpu->p & ~FLAG_CARRY) | ((value & 0x80) ? FLAG_CARRY : 0);
      value = (value << 1) & 0xFF;
      mem_write(mem, addr, value);
      set_zn_flags(cpu, value);
      break;
    case 0x0E:  // Absolute
      addr = mem_read(mem, cpu->pc++);
      addr |= (mem_read(mem, cpu->pc++) << 8);
      value = mem_read(mem, addr);
      cpu->p = (cpu->p & ~FLAG_CARRY) | ((value & 0x80) ? FLAG_CARRY : 0);
      value = (value << 1) & 0xFF;
      mem_write(mem, addr, value);
      set_zn_flags(cpu, value);
      break;
    case 0x1E:  // Absolute, X
      addr = mem_read(mem, cpu->pc++);
      addr |= (mem_read(mem, cpu->pc++) << 8);
      addr += cpu->x;
      value = mem_read(mem, addr);
      cpu->p = (cpu->p & ~FLAG_CARRY) | ((value & 0x80) ? FLAG_CARRY : 0);
      value = (value << 1) & 0xFF;
      mem_write(mem, addr, value);
      set_zn_flags(cpu, value);
      break;

    // ----- LSR (Logical Shift Right) -----
    case 0x4A:  // Accumulator
      cpu->p = (cpu->p & ~FLAG_CARRY) | (cpu->a & 0x01 ? FLAG_CARRY : 0);
      cpu->a = cpu->a >> 1;
      set_zn_flags(cpu, cpu->a);
      break;
    case 0x46:  // Zero Page
      addr = mem_read(mem, cpu->pc++);
      value = mem_read(mem, addr);
      cpu->p = (cpu->p & ~FLAG_CARRY) | (value & 0x01 ? FLAG_CARRY : 0);
      value = value >> 1;
      mem_write(mem, addr, value);
      set_zn_flags(cpu, value);
      break;
    case 0x56:  // Zero Page, X
      addr = (mem_read(mem, cpu->pc++) + cpu->x) & 0xFF;
      value = mem_read(mem, addr);
      cpu->p = (cpu->p & ~FLAG_CARRY) | (value & 0x01 ? FLAG_CARRY : 0);
      value = value >> 1;
      mem_write(mem, addr, value);
      set_zn_flags(cpu, value);
      break;
    case 0x4E:  // Absolute
      addr = mem_read(mem, cpu->pc++);
      addr |= (mem_read(mem, cpu->pc++) << 8);
      value = mem_read(mem, addr);
      cpu->p = (cpu->p & ~FLAG_CARRY) | (value & 0x01 ? FLAG_CARRY : 0);
      value = value >> 1;
      mem_write(mem, addr, value);
      set_zn_flags(cpu, value);
      break;
    case 0x5E:  // Absolute, X
      addr = mem_read(mem, cpu->pc++);
      addr |= (mem_read(mem, cpu->pc++) << 8);
      addr += cpu->x;
      value = mem_read(mem, addr);
      cpu->p = (cpu->p & ~FLAG_CARRY) | (value & 0x01 ? FLAG_CARRY : 0);
      value = value >> 1;
      mem_write(mem, addr, value);
      set_zn_flags(cpu, value);
      break;

    // ----- ROL (Rotate Left) -----
    case 0x2A:  // Accumulator
      tmp = (cpu->p & FLAG_CARRY) ? 1 : 0;
      cpu->p = (cpu->p & ~FLAG_CARRY) | ((cpu->a & 0x80) ? FLAG_CARRY : 0);
      cpu->a = ((cpu->a << 1) | tmp) & 0xFF;
      set_zn_flags(cpu, cpu->a);
      break;
    case 0x26:  // Zero Page
      addr = mem_read(mem, cpu->pc++);
      value = mem_read(mem, addr);
      tmp = (cpu->p & FLAG_CARRY) ? 1 : 0;
      cpu->p = (cpu->p & ~FLAG_CARRY) | ((value & 0x80) ? FLAG_CARRY : 0);
      value = ((value << 1) | tmp) & 0xFF;
      mem_write(mem, addr, value);
      set_zn_flags(cpu, value);
      break;
    case 0x36:  // Zero Page, X
      addr = (mem_read(mem, cpu->pc++) + cpu->x) & 0xFF;
      value = mem_read(mem, addr);
      tmp = (cpu->p & FLAG_CARRY) ? 1 : 0;
      cpu->p = (cpu->p & ~FLAG_CARRY) | ((value & 0x80) ? FLAG_CARRY : 0);
      value = ((value << 1) | tmp) & 0xFF;
      mem_write(mem, addr, value);
      set_zn_flags(cpu, value);
      break;
    case 0x2E:  // Absolute
      addr = mem_read(mem, cpu->pc++);
      addr |= (mem_read(mem, cpu->pc++) << 8);
      value = mem_read(mem, addr);
      tmp = (cpu->p & FLAG_CARRY) ? 1 : 0;
      cpu->p = (cpu->p & ~FLAG_CARRY) | ((value & 0x80) ? FLAG_CARRY : 0);
      value = ((value << 1) | tmp) & 0xFF;
      mem_write(mem, addr, value);
      set_zn_flags(cpu, value);
      break;
    case 0x3E:  // Absolute, X
      addr = mem_read(mem, cpu->pc++);
      addr |= (mem_read(mem, cpu->pc++) << 8);
      addr += cpu->x;
      value = mem_read(mem, addr);
      tmp = (cpu->p & FLAG_CARRY) ? 1 : 0;
      cpu->p = (cpu->p & ~FLAG_CARRY) | ((value & 0x80) ? FLAG_CARRY : 0);
      value = ((value << 1) | tmp) & 0xFF;
      mem_write(mem, addr, value);
      set_zn_flags(cpu, value);
      break;

    // ----- ROR (Rotate Right) -----
    case 0x6A:  // Accumulator
      tmp = (cpu->p & FLAG_CARRY) ? 0x80 : 0;
      cpu->p = (cpu->p & ~FLAG_CARRY) | (cpu->a & 0x01 ? FLAG_CARRY : 0);
      cpu->a = (cpu->a >> 1) | tmp;
      set_zn_flags(cpu, cpu->a);
      break;
    case 0x66:  // Zero Page
      addr = mem_read(mem, cpu->pc++);
      value = mem_read(mem, addr);
      tmp = (cpu->p & FLAG_CARRY) ? 0x80 : 0;
      cpu->p = (cpu->p & ~FLAG_CARRY) | (value & 0x01 ? FLAG_CARRY : 0);
      value = (value >> 1) | tmp;
      mem_write(mem, addr, value);
      set_zn_flags(cpu, value);
      break;
    case 0x76:  // Zero Page, X
      addr = (mem_read(mem, cpu->pc++) + cpu->x) & 0xFF;
      value = mem_read(mem, addr);
      tmp = (cpu->p & FLAG_CARRY) ? 0x80 : 0;
      cpu->p = (cpu->p & ~FLAG_CARRY) | (value & 0x01 ? FLAG_CARRY : 0);
      value = (value >> 1) | tmp;
      mem_write(mem, addr, value);
      set_zn_flags(cpu, value);
      break;
    case 0x6E:  // Absolute
      addr = mem_read(mem, cpu->pc++);
      addr |= (mem_read(mem, cpu->pc++) << 8);
      value = mem_read(mem, addr);
      tmp = (cpu->p & FLAG_CARRY) ? 0x80 : 0;
      cpu->p = (cpu->p & ~FLAG_CARRY) | (value & 0x01 ? FLAG_CARRY : 0);
      value = (value >> 1) | tmp;
      mem_write(mem, addr, value);
      set_zn_flags(cpu, value);
      break;
    case 0x7E:  // Absolute, X
      addr = mem_read(mem, cpu->pc++);
      addr |= (mem_read(mem, cpu->pc++) << 8);
      addr += cpu->x;
      value = mem_read(mem, addr);
      tmp = (cpu->p & FLAG_CARRY) ? 0x80 : 0;
      cpu->p = (cpu->p & ~FLAG_CARRY) | (value & 0x01 ? FLAG_CARRY : 0);
      value = (value >> 1) | tmp;
      mem_write(mem, addr, value);
      set_zn_flags(cpu, value);
      break;

    // ----- JMP (Jump) -----
    case 0x4C: {  // Absolute
      addr = mem_read(mem, cpu->pc++);
      addr |= (mem_read(mem, cpu->pc++) << 8);
      cpu->pc = addr;
      break;
    }
    case 0x6C: {  // Indirect
      addr = mem_read(mem, cpu->pc++);
      addr |= (mem_read(mem, cpu->pc++) << 8);
      // The famous 6502 bug: if address is at page boundary, it wraps within the same page
      uint16_t target = mem_read(mem, addr);
      target |= (mem_read(mem, (addr & 0xFF00) | ((addr + 1) & 0x00FF)) << 8);
      cpu->pc = target;
      break;
    }

    // ----- JSR, RTS (Subroutine Operations) -----
    case 0x20: {  // JSR - Jump to Subroutine
      uint16_t addr = mem_read(mem, cpu->pc++);
      addr |= (mem_read(mem, cpu->pc++) << 8);
      uint16_t return_addr = cpu->pc - 1;
      mem_write(mem, 0x0100 + cpu->sp--, (return_addr >> 8));
      mem_write(mem, 0x0100 + cpu->sp--, return_addr & 0xFF);
      cpu->pc = addr;
      break;
    }
    case 0x60: {  // RTS - Return from Subroutine
      uint8_t low = mem_read(mem, 0x0100 + ++cpu->sp);
      uint8_t high = mem_read(mem, 0x0100 + ++cpu->sp);
      cpu->pc = ((high << 8) | low) + 1;
      break;
    }

    // ----- Branch Instructions -----
    case 0x90: {  // BCC - Branch if Carry Clear
      offset = (int8_t)mem_read(mem, cpu->pc++);
      if (!(cpu->p & FLAG_CARRY)) cpu->pc += offset;
      break;
    }
    case 0xB0: {  // BCS - Branch if Carry Set
      offset = (int8_t)mem_read(mem, cpu->pc++);
      if (cpu->p & FLAG_CARRY) cpu->pc += offset;
      break;
    }
    case 0xF0: {  // BEQ - Branch if Equal (Zero Set)
      offset = (int8_t)mem_read(mem, cpu->pc++);
      if (cpu->p & FLAG_ZERO) cpu->pc += offset;
      break;
    }
    case 0x30: {  // BMI - Branch if Minus (Negative Set)
      offset = (int8_t)mem_read(mem, cpu->pc++);
      if (cpu->p & FLAG_NEGATIVE) cpu->pc += offset;
      break;
    }
    case 0xD0: {  // BNE - Branch if Not Equal (Zero Clear)
      offset = (int8_t)mem_read(mem, cpu->pc++);
      if (!(cpu->p & FLAG_ZERO)) cpu->pc += offset;
      break;
    }
    case 0x10: {  // BPL - Branch if Plus (Negative Clear)
      offset = (int8_t)mem_read(mem, cpu->pc++);
      if (!(cpu->p & FLAG_NEGATIVE)) cpu->pc += offset;
      break;
    }
    case 0x50: {  // BVC - Branch if Overflow Clear
      offset = (int8_t)mem_read(mem, cpu->pc++);
      if (!(cpu->p & FLAG_OVERFLOW)) cpu->pc += offset;
      break;
    }
    case 0x70: {  // BVS - Branch if Overflow Set
      offset = (int8_t)mem_read(mem, cpu->pc++);
      if (cpu->p & FLAG_OVERFLOW) cpu->pc += offset;
      break;
    }

    // ----- Status Flag Instructions -----
    case 0x18:  // CLC - Clear Carry Flag
      cpu->p &= ~FLAG_CARRY;
      break;
    case 0xD8:  // CLD - Clear Decimal Mode
      cpu->p &= ~FLAG_DECIMAL;
      break;
    case 0x58:  // CLI - Clear Interrupt Disable
      cpu->p &= ~FLAG_INTERRUPT;
      break;
    case 0xB8:  // CLV - Clear Overflow Flag
      cpu->p &= ~FLAG_OVERFLOW;
      break;
    case 0x38:  // SEC - Set Carry Flag
      cpu->p |= FLAG_CARRY;
      break;
    case 0xF8:  // SED - Set Decimal Flag
      cpu->p |= FLAG_DECIMAL;
      break;
    case 0x78:  // SEI - Set Interrupt Disable
      cpu->p |= FLAG_INTERRUPT;
      break;

    // ----- BIT (Bit Test) -----
    case 0x24:  // Zero Page
      addr = mem_read(mem, cpu->pc++);
      value = mem_read(mem, addr);
      cpu->p = (cpu->p & ~(FLAG_ZERO | FLAG_OVERFLOW | FLAG_NEGATIVE)) |
               ((value & cpu->a) == 0 ? FLAG_ZERO : 0) |
               (value & 0x40 ? FLAG_OVERFLOW : 0) |
               (value & 0x80 ? FLAG_NEGATIVE : 0);
      break;
    case 0x2C:  // Absolute
      addr = mem_read(mem, cpu->pc++);
      addr |= (mem_read(mem, cpu->pc++) << 8);
      value = mem_read(mem, addr);
      cpu->p = (cpu->p & ~(FLAG_ZERO | FLAG_OVERFLOW | FLAG_NEGATIVE)) |
               ((value & cpu->a) == 0 ? FLAG_ZERO : 0) |
               (value & 0x40 ? FLAG_OVERFLOW : 0) |
               (value & 0x80 ? FLAG_NEGATIVE : 0);
      break;

    // ----- Break and System Instructions -----
    case 0x00: {  // BRK - Force Interrupt
      cpu->pc++;  // Skip signature byte
      mem_write(mem, 0x0100 + cpu->sp--, (cpu->pc >> 8));  // Push PCH
      mem_write(mem, 0x0100 + cpu->sp--, cpu->pc & 0xFF);   // Push PCL
      mem_write(mem, 0x0100 + cpu->sp--, cpu->p | FLAG_BREAK);  // Push status with B flag set
      cpu->p |= FLAG_INTERRUPT;  // Set interrupt disable flag
      cpu->pc = mem_read(mem, 0xFFFE);  // Load interrupt vector low byte
      cpu->pc |= (mem_read(mem, 0xFFFF) << 8); // Load interrupt vector high byte
      break;
    }
    case 0x40: {  // RTI - Return from Interrupt
      cpu->p = mem_read(mem, 0x0100 + ++cpu->sp) & ~FLAG_BREAK;
      uint8_t pcl = mem_read(mem, 0x0100 + ++cpu->sp);
      uint8_t pch = mem_read(mem, 0x0100 + ++cpu->sp);
      cpu->pc = (pch << 8) | pcl;
      break;
    }
    case 0xEA:  // NOP - No Operation
      break;

    // ----- Undocumented/Illegal opcodes -----
    // Here are a few common unofficial opcodes, you can add more as needed

    // ----- LAX (Load A and X) - Unofficial -----
    case 0xA7:  // Zero Page
      addr = mem_read(mem, cpu->pc++);
      cpu->a = cpu->x = mem_read(mem, addr);
      set_zn_flags(cpu, cpu->a);
      break;
    case 0xB7:  // Zero Page, Y
      addr = (mem_read(mem, cpu->pc++) + cpu->y) & 0xFF;
      cpu->a = cpu->x = mem_read(mem, addr);
      set_zn_flags(cpu, cpu->a);
      break;
    case 0xAF:  // Absolute
      addr = mem_read(mem, cpu->pc++);
      addr |= (mem_read(mem, cpu->pc++) << 8);
      cpu->a = cpu->x = mem_read(mem, addr);
      set_zn_flags(cpu, cpu->a);
      break;
    case 0xBF:  // Absolute, Y
      addr = mem_read(mem, cpu->pc++);
      addr |= (mem_read(mem, cpu->pc++) << 8);
      addr += cpu->y;
      cpu->a = cpu->x = mem_read(mem, addr);
      set_zn_flags(cpu, cpu->a);
      break;
    case 0xA3:  // (Indirect, X)
      tmp = (mem_read(mem, cpu->pc++) + cpu->x) & 0xFF;
      addr = mem_read(mem, tmp);
      addr |= (mem_read(mem, (tmp + 1) & 0xFF) << 8);
      cpu->a = cpu->x = mem_read(mem, addr);
      set_zn_flags(cpu, cpu->a);
      break;
    case 0xB3:  // (Indirect), Y
      tmp = mem_read(mem, cpu->pc++);
      addr = mem_read(mem, tmp);
      addr |= (mem_read(mem, (tmp + 1) & 0xFF) << 8);
      addr += cpu->y;
      cpu->a = cpu->x = mem_read(mem, addr);
      set_zn_flags(cpu, cpu->a);
      break;

    // ----- SAX (Store A and X) - Unofficial -----
    case 0x87:  // Zero Page
      addr = mem_read(mem, cpu->pc++);
      mem_write(mem, addr, cpu->a & cpu->x);
      break;
    case 0x97:  // Zero Page, Y
      addr = (mem_read(mem, cpu->pc++) + cpu->y) & 0xFF;
      mem_write(mem, addr, cpu->a & cpu->x);
      break;
    case 0x8F:  // Absolute
      addr = mem_read(mem, cpu->pc++);
      addr |= (mem_read(mem, cpu->pc++) << 8);
      mem_write(mem, addr, cpu->a & cpu->x);
      break;

    // ----- DCP (Decrement and Compare) - Unofficial -----
    case 0xC7:  // Zero Page
      addr = mem_read(mem, cpu->pc++);
      value = mem_read(mem, addr) - 1;
      mem_write(mem, addr, value);
      tmp = cpu->a - value;
      cpu->p = (cpu->p & ~(FLAG_ZERO | FLAG_NEGATIVE | FLAG_CARRY)) |
               (cpu->a >= value ? FLAG_CARRY : 0) | (tmp == 0 ? FLAG_ZERO : 0) |
               (tmp & 0x80 ? FLAG_NEGATIVE : 0);
      break;
    case 0xD7:  // Zero Page, X
      addr = (mem_read(mem, cpu->pc++) + cpu->x) & 0xFF;
      value = mem_read(mem, addr) - 1;
      mem_write(mem, addr, value);
      tmp = cpu->a - value;
      cpu->p = (cpu->p & ~(FLAG_ZERO | FLAG_NEGATIVE | FLAG_CARRY)) |
               (cpu->a >= value ? FLAG_CARRY : 0) | (tmp == 0 ? FLAG_ZERO : 0) |
               (tmp & 0x80 ? FLAG_NEGATIVE : 0);
      break;
    case 0xCF:  // Absolute
      addr = mem_read(mem, cpu->pc++);
      addr |= (mem_read(mem, cpu->pc++) << 8);
      value = mem_read(mem, addr) - 1;
      mem_write(mem, addr, value);
      tmp = cpu->a - value;
      cpu->p = (cpu->p & ~(FLAG_ZERO | FLAG_NEGATIVE | FLAG_CARRY)) |
               (cpu->a >= value ? FLAG_CARRY : 0) | (tmp == 0 ? FLAG_ZERO : 0) |
               (tmp & 0x80 ? FLAG_NEGATIVE : 0);
      break;
    case 0xDF:  // Absolute, X
      addr = mem_read(mem, cpu->pc++);
      addr |= (mem_read(mem, cpu->pc++) << 8);
      addr += cpu->x;
      value = mem_read(mem, addr) - 1;
      mem_write(mem, addr, value);
      tmp = cpu->a - value;
      cpu->p = (cpu->p & ~(FLAG_ZERO | FLAG_NEGATIVE | FLAG_CARRY)) |
               (cpu->a >= value ? FLAG_CARRY : 0) | (tmp == 0 ? FLAG_ZERO : 0) |
               (tmp & 0x80 ? FLAG_NEGATIVE : 0);
      break;
    case 0xDB:  // Absolute, Y
      addr = mem_read(mem, cpu->pc++);
      addr |= (mem_read(mem, cpu->pc++) << 8);
      addr += cpu->y;
      value = mem_read(mem, addr) - 1;
      mem_write(mem, addr, value);
      tmp = cpu->a - value;
      cpu->p = (cpu->p & ~(FLAG_ZERO | FLAG_NEGATIVE | FLAG_CARRY)) |
               (cpu->a >= value ? FLAG_CARRY : 0) | (tmp == 0 ? FLAG_ZERO : 0) |
               (tmp & 0x80 ? FLAG_NEGATIVE : 0);
      break;
    case 0xC3:  // (Indirect, X)
      tmp = (mem_read(mem, cpu->pc++) + cpu->x) & 0xFF;
      addr = mem_read(mem, tmp);
      addr |= (mem_read(mem, (tmp + 1) & 0xFF) << 8);
      value = mem_read(mem, addr) - 1;
      mem_write(mem, addr, value);
      tmp = cpu->a - value;
      cpu->p = (cpu->p & ~(FLAG_ZERO | FLAG_NEGATIVE | FLAG_CARRY)) |
               (cpu->a >= value ? FLAG_CARRY : 0) | (tmp == 0 ? FLAG_ZERO : 0) |
               (tmp & 0x80 ? FLAG_NEGATIVE : 0);
      break;
    case 0xD3:  // (Indirect), Y
      tmp = mem_read(mem, cpu->pc++);
      addr = mem_read(mem, tmp);
      addr |= (mem_read(mem, (tmp + 1) & 0xFF) << 8);
      addr += cpu->y;
      value = mem_read(mem, addr) - 1;
      mem_write(mem, addr, value);
      tmp = cpu->a - value;
      cpu->p = (cpu->p & ~(FLAG_ZERO | FLAG_NEGATIVE | FLAG_CARRY)) |
               (cpu->a >= value ? FLAG_CARRY : 0) | (tmp == 0 ? FLAG_ZERO : 0) |
               (tmp & 0x80 ? FLAG_NEGATIVE : 0);
      break;

    // ----- ISB (Increment and Subtract) - Unofficial -----
    case 0xE7:  // Zero Page
      addr = mem_read(mem, cpu->pc++);
      value = mem_read(mem, addr) + 1;
      mem_write(mem, addr, value);
      sum = cpu->a - value - (cpu->p & FLAG_CARRY ? 0 : 1);
      cpu->p = (cpu->p & ~(FLAG_OVERFLOW | FLAG_CARRY)) |
               (((cpu->a ^ value) & (cpu->a ^ sum) & 0x80) ? FLAG_OVERFLOW : 0) |
               (sum < 0x100 ? FLAG_CARRY : 0);
      cpu->a = (uint8_t)sum;
      set_zn_flags(cpu, cpu->a);
      break;
    case 0xF7:  // Zero Page, X
      addr = (mem_read(mem, cpu->pc++) + cpu->x) & 0xFF;
      value = mem_read(mem, addr) + 1;
      mem_write(mem, addr, value);
      sum = cpu->a - value - (cpu->p & FLAG_CARRY ? 0 : 1);
      cpu->p = (cpu->p & ~(FLAG_OVERFLOW | FLAG_CARRY)) |
               (((cpu->a ^ value) & (cpu->a ^ sum) & 0x80) ? FLAG_OVERFLOW : 0) |
               (sum < 0x100 ? FLAG_CARRY : 0);
      cpu->a = (uint8_t)sum;
      set_zn_flags(cpu, cpu->a);
      break;
    case 0xEF:  // Absolute
      addr = mem_read(mem, cpu->pc++);
      addr |= (mem_read(mem, cpu->pc++) << 8);
      value = mem_read(mem, addr) + 1;
      mem_write(mem, addr, value);
      sum = cpu->a - value - (cpu->p & FLAG_CARRY ? 0 : 1);
      cpu->p = (cpu->p & ~(FLAG_OVERFLOW | FLAG_CARRY)) |
               (((cpu->a ^ value) & (cpu->a ^ sum) & 0x80) ? FLAG_OVERFLOW : 0) |
               (sum < 0x100 ? FLAG_CARRY : 0);
      cpu->a = (uint8_t)sum;
      set_zn_flags(cpu, cpu->a);
      break;
    case 0xFF:  // Absolute, X
      addr = mem_read(mem, cpu->pc++);
      addr |= (mem_read(mem, cpu->pc++) << 8);
      addr += cpu->x;
      value = mem_read(mem, addr) + 1;
      mem_write(mem, addr, value);
      sum = cpu->a - value - (cpu->p & FLAG_CARRY ? 0 : 1);
      cpu->p = (cpu->p & ~(FLAG_OVERFLOW | FLAG_CARRY)) |
               (((cpu->a ^ value) & (cpu->a ^ sum) & 0x80) ? FLAG_OVERFLOW : 0) |
               (sum < 0x100 ? FLAG_CARRY : 0);
      cpu->a = (uint8_t)sum;
      set_zn_flags(cpu, cpu->a);
      break;
    case 0xFB:  // Absolute, Y
      addr = mem_read(mem, cpu->pc++);
      addr |= (mem_read(mem, cpu->pc++) << 8);
      addr += cpu->y;
      value = mem_read(mem, addr) + 1;
      mem_write(mem, addr, value);
      sum = cpu->a - value - (cpu->p & FLAG_CARRY ? 0 : 1);
      cpu->p = (cpu->p & ~(FLAG_OVERFLOW | FLAG_CARRY)) |
               (((cpu->a ^ value) & (cpu->a ^ sum) & 0x80) ? FLAG_OVERFLOW : 0) |
               (sum < 0x100 ? FLAG_CARRY : 0);
      cpu->a = (uint8_t)sum;
      set_zn_flags(cpu, cpu->a);
      break;
    case 0xE3:  // (Indirect, X)
      tmp = (mem_read(mem, cpu->pc++) + cpu->x) & 0xFF;
      addr = mem_read(mem, tmp);
      addr |= (mem_read(mem, (tmp + 1) & 0xFF) << 8);
      value = mem_read(mem, addr) + 1;
      mem_write(mem, addr, value);
      sum = cpu->a - value - (cpu->p & FLAG_CARRY ? 0 : 1);
      cpu->p = (cpu->p & ~(FLAG_OVERFLOW | FLAG_CARRY)) |
               (((cpu->a ^ value) & (cpu->a ^ sum) & 0x80) ? FLAG_OVERFLOW : 0) |
               (sum < 0x100 ? FLAG_CARRY : 0);
      cpu->a = (uint8_t)sum;
      set_zn_flags(cpu, cpu->a);
      break;
    case 0xF3:  // (Indirect), Y
      tmp = mem_read(mem, cpu->pc++);
      addr = mem_read(mem, tmp);
      addr |= (mem_read(mem, (tmp + 1) & 0xFF) << 8);
      addr += cpu->y;
      value = mem_read(mem, addr) + 1;
      mem_write(mem, addr, value);
      sum = cpu->a - value - (cpu->p & FLAG_CARRY ? 0 : 1);
      cpu->p = (cpu->p & ~(FLAG_OVERFLOW | FLAG_CARRY)) |
               (((cpu->a ^ value) & (cpu->a ^ sum) & 0x80) ? FLAG_OVERFLOW : 0) |
               (sum < 0x100 ? FLAG_CARRY : 0);
      cpu->a = (uint8_t)sum;
      set_zn_flags(cpu, cpu->a);
      break;

    // ----- RLA (Rotate Left and AND) - Unofficial -----
    case 0x27:  // Zero Page
      addr = mem_read(mem, cpu->pc++);
      value = mem_read(mem, addr);
      cpu->p = (cpu->p & ~FLAG_CARRY) | ((value & 0x80) ? FLAG_CARRY : 0);
      value = (value << 1) & 0xFF;
      mem_write(mem, addr, value);
      cpu->a &= value;
      set_zn_flags(cpu, cpu->a);
      break;
    case 0x37:  // Zero Page, X
      addr = (mem_read(mem, cpu->pc++) + cpu->x) & 0xFF;
      value = mem_read(mem, addr);
      cpu->p = (cpu->p & ~FLAG_CARRY) | ((value & 0x80) ? FLAG_CARRY : 0);
      value = (value << 1) & 0xFF;
      mem_write(mem, addr, value);
      cpu->a &= value;
      set_zn_flags(cpu, cpu->a);
      break;
    case 0x2F:  // Absolute
      addr = mem_read(mem, cpu->pc++);
      addr |= (mem_read(mem, cpu->pc++) << 8);
      value = mem_read(mem, addr);
      cpu->p = (cpu->p & ~FLAG_CARRY) | ((value & 0x80) ? FLAG_CARRY : 0);
      value = (value << 1) & 0xFF;
      mem_write(mem, addr, value);
      cpu->a &= value;
      set_zn_flags(cpu, cpu->a);
      break;
    case 0x3F:  // Absolute, X
      addr = mem_read(mem, cpu->pc++);
      addr |= (mem_read(mem, cpu->pc++) << 8);
      addr += cpu->x;
      value = mem_read(mem, addr);
      cpu->p = (cpu->p & ~FLAG_CARRY) | ((value & 0x80) ? FLAG_CARRY : 0);
      value = (value << 1) & 0xFF;
      mem_write(mem, addr, value);
      cpu->a &= value;
      set_zn_flags(cpu, cpu->a);
      break;
    case 0x3B:  // Absolute, Y
      addr = mem_read(mem, cpu->pc++);
      addr |= (mem_read(mem, cpu->pc++) << 8);
      addr += cpu->y;
      value = mem_read(mem, addr);
      cpu->p = (cpu->p & ~FLAG_CARRY) | ((value & 0x80) ? FLAG_CARRY : 0);
      value = (value << 1) & 0xFF;
      mem_write(mem, addr, value);
      cpu->a &= value;
      set_zn_flags(cpu, cpu->a);
      break;
    case 0x23:  // (Indirect, X)
      tmp = (mem_read(mem, cpu->pc++) + cpu->x) & 0xFF;
      addr = mem_read(mem, tmp);
      addr |= (mem_read(mem, (tmp + 1) & 0xFF) << 8);
      value = mem_read(mem, addr);
      cpu->p = (cpu->p & ~FLAG_CARRY) | ((value & 0x80) ? FLAG_CARRY : 0);
      value = (value << 1) & 0xFF;
      mem_write(mem, addr, value);
      cpu->a &= value;
      set_zn_flags(cpu, cpu->a);
      break;
    case 0x33:  // (Indirect), Y
      tmp = (mem_read(mem, cpu->pc++) + cpu->x) & 0xFF;
      addr = mem_read(mem, tmp);
      addr |= (mem_read(mem, (tmp + 1) & 0xFF) << 8);
      addr += cpu->y;
      value = mem_read(mem, addr);
      cpu->p = (cpu->p & ~FLAG_CARRY) | ((value & 0x80) ? FLAG_CARRY : 0);
      value = (value << 1) & 0xFF;
      mem_write(mem, addr, value);
      cpu->a &= value;
      set_zn_flags(cpu, cpu->a);
      break;

    // ----- RRA (Rotate Right and Add with Carry) - Unofficial -----
    case 0x67:  // Zero Page
      addr = mem_read(mem, cpu->pc++);
      value = mem_read(mem, addr);
      cpu->p = (cpu->p & ~FLAG_CARRY) | (value & 0x01 ? FLAG_CARRY : 0);
      tmp = (cpu->p & FLAG_CARRY) ? 0x80 : 0;
      value = (value >> 1) | tmp;
      mem_write(mem, addr, value);
      sum = cpu->a + value + (cpu->p & FLAG_CARRY ? 1 : 0);
      cpu->p = (cpu->p & ~(FLAG_OVERFLOW | FLAG_CARRY)) |
               ((~(cpu->a ^ value) & (cpu->a ^ sum) & 0x80) ? FLAG_OVERFLOW : 0) |
               (sum > 0xFF ? FLAG_CARRY : 0);
      cpu->a = (uint8_t)sum;
      set_zn_flags(cpu, cpu->a);
      break;
    case 0x77:  // Zero Page, X
      addr = (mem_read(mem, cpu->pc++) + cpu->x) & 0xFF;
      value = mem_read(mem, addr);
      cpu->p = (cpu->p & ~FLAG_CARRY) | (value & 0x01 ? FLAG_CARRY : 0);
      tmp = (cpu->p & FLAG_CARRY) ? 0x80 : 0;
      value = (value >> 1) | tmp;
      mem_write(mem, addr, value);
      sum = cpu->a + value + (cpu->p & FLAG_CARRY ? 1 : 0);
      cpu->p = (cpu->p & ~(FLAG_OVERFLOW | FLAG_CARRY)) |
               ((~(cpu->a ^ value) & (cpu->a ^ sum) & 0x80) ? FLAG_OVERFLOW : 0) |
               (sum > 0xFF ? FLAG_CARRY : 0);
      cpu->a = (uint8_t)sum;
      set_zn_flags(cpu, cpu->a);
      break;
    case 0x6F:  // Absolute
      addr = mem_read(mem, cpu->pc++);
      addr |= (mem_read(mem, cpu->pc++) << 8);
      value = mem_read(mem, addr);
      cpu->p = (cpu->p & ~FLAG_CARRY) | (value & 0x01 ? FLAG_CARRY : 0);
      tmp = (cpu->p & FLAG_CARRY) ? 0x80 : 0;
      value = (value >> 1) | tmp;
      mem_write(mem, addr, value);
      sum = cpu->a + value + (cpu->p & FLAG_CARRY ? 1 : 0);
      cpu->p = (cpu->p & ~(FLAG_OVERFLOW | FLAG_CARRY)) |
               ((~(cpu->a ^ value) & (cpu->a ^ sum) & 0x80) ? FLAG_OVERFLOW : 0) |
               (sum > 0xFF ? FLAG_CARRY : 0);
      cpu->a = (uint8_t)sum;
      set_zn_flags(cpu, cpu->a);
      break;
    case 0x7F:  // Absolute, X
      addr = mem_read(mem, cpu->pc++);
      addr |= (mem_read(mem, cpu->pc++) << 8);
      addr += cpu->x;
      value = mem_read(mem, addr);
      cpu->p = (cpu->p & ~FLAG_CARRY) | (value & 0x01 ? FLAG_CARRY : 0);
      tmp = (cpu->p & FLAG_CARRY) ? 0x80 : 0;
      value = (value >> 1) | tmp;
      mem_write(mem, addr, value);
      sum = cpu->a + value + (cpu->p & FLAG_CARRY ? 1 : 0);
      cpu->p = (cpu->p & ~(FLAG_OVERFLOW | FLAG_CARRY)) |
               ((~(cpu->a ^ value) & (cpu->a ^ sum) & 0x80) ? FLAG_OVERFLOW : 0) |
               (sum > 0xFF ? FLAG_CARRY : 0);
      cpu->a = (uint8_t)sum;
      set_zn_flags(cpu, cpu->a);
      break;
    case 0x7B:  // Absolute, Y
      addr = mem_read(mem, cpu->pc++);
      addr |= (mem_read(mem, cpu->pc++) << 8);
      addr += cpu->y;
      value = mem_read(mem, addr);
      cpu->p = (cpu->p & ~FLAG_CARRY) | (value & 0x01 ? FLAG_CARRY : 0);
      tmp = (cpu->p & FLAG_CARRY) ? 0x80 : 0;
      value = (value >> 1) | tmp;
      mem_write(mem, addr, value);
      sum = cpu->a + value + (cpu->p & FLAG_CARRY ? 1 : 0);
      cpu->p = (cpu->p & ~(FLAG_OVERFLOW | FLAG_CARRY)) |
               ((~(cpu->a ^ value) & (cpu->a ^ sum) & 0x80) ? FLAG_OVERFLOW : 0) |
               (sum > 0xFF ? FLAG_CARRY : 0);
      cpu->a = (uint8_t)sum;
      set_zn_flags(cpu, cpu->a);
      break;
    case 0x63:  // (Indirect, X)
      tmp = (mem_read(mem, cpu->pc++) + cpu->x) & 0xFF;
      addr = mem_read(mem, tmp);
      addr |= (mem_read(mem, (tmp + 1) & 0xFF) << 8);
      value = mem_read(mem, addr);
      cpu->p = (cpu->p & ~FLAG_CARRY) | (value & 0x01 ? FLAG_CARRY : 0);
      tmp = (cpu->p & FLAG_CARRY) ? 0x80 : 0;
      value = (value >> 1) | tmp;
      mem_write(mem, addr, value);
      sum = cpu->a + value + (cpu->p & FLAG_CARRY ? 1 : 0);
      cpu->p = (cpu->p & ~(FLAG_OVERFLOW | FLAG_CARRY)) |
               ((~(cpu->a ^ value) & (cpu->a ^ sum) & 0x80) ? FLAG_OVERFLOW : 0) |
               (sum > 0xFF ? FLAG_CARRY : 0);
      cpu->a = (uint8_t)sum;
      set_zn_flags(cpu, cpu->a);
      break;
    case 0x73:  // (Indirect), Y
      tmp = mem_read(mem, cpu->pc++);
      addr = mem_read(mem, tmp);
      addr |= (mem_read(mem, (tmp + 1) & 0xFF) << 8);
      addr += cpu->y;
      value = mem_read(mem, addr);
      cpu->p = (cpu->p & ~FLAG_CARRY) | (value & 0x01 ? FLAG_CARRY : 0);
      tmp = (cpu->p & FLAG_CARRY) ? 0x80 : 0;
      value = (value >> 1) | tmp;
      mem_write(mem, addr, value);
      sum = cpu->a + value + (cpu->p & FLAG_CARRY ? 1 : 0);
      cpu->p = (cpu->p & ~(FLAG_OVERFLOW | FLAG_CARRY)) |
               ((~(cpu->a ^ value) & (cpu->a ^ sum) & 0x80) ? FLAG_OVERFLOW : 0) |
               (sum > 0xFF ? FLAG_CARRY : 0);
      cpu->a = (uint8_t)sum;
      set_zn_flags(cpu, cpu->a);
      break;

    // ----- SLO (Shift Left and OR) - Unofficial -----
    case 0x07:  // Zero Page
      addr = mem_read(mem, cpu->pc++);
      value = mem_read(mem, addr);
      cpu->p = (cpu->p & ~FLAG_CARRY) | ((value & 0x80) ? FLAG_CARRY : 0);
      value = (value << 1) & 0xFF;
      mem_write(mem, addr, value);
      cpu->a |= value;
      set_zn_flags(cpu, cpu->a);
      break;
    case 0x17:  // Zero Page, X
      addr = (mem_read(mem, cpu->pc++) + cpu->x) & 0xFF;
      value = mem_read(mem, addr);
      cpu->p = (cpu->p & ~FLAG_CARRY) | ((value & 0x80) ? FLAG_CARRY : 0);
      value = (value << 1) & 0xFF;
      mem_write(mem, addr, value);
      cpu->a |= value;
      set_zn_flags(cpu, cpu->a);
      break;
    case 0x0F:  // Absolute
      addr = mem_read(mem, cpu->pc++);
      addr |= (mem_read(mem, cpu->pc++) << 8);
      value = mem_read(mem, addr);
      cpu->p = (cpu->p & ~FLAG_CARRY) | ((value & 0x80) ? FLAG_CARRY : 0);
      value = (value << 1) & 0xFF;
      mem_write(mem, addr, value);
      cpu->a |= value;
      set_zn_flags(cpu, cpu->a);
      break;
    case 0x1F:  // Absolute, X
      addr = mem_read(mem, cpu->pc++);
      addr |= (mem_read(mem, cpu->pc++) << 8);
      addr += cpu->x;
      value = mem_read(mem, addr);
      cpu->p = (cpu->p & ~FLAG_CARRY) | ((value & 0x80) ? FLAG_CARRY : 0);
      value = (value << 1) & 0xFF;
      mem_write(mem, addr, value);
      cpu->a |= value;
      set_zn_flags(cpu, cpu->a);
      break;
    case 0x1B:  // Absolute, Y
      addr = mem_read(mem, cpu->pc++);
      addr |= (mem_read(mem, cpu->pc++) << 8);
      addr += cpu->y;
      value = mem_read(mem, addr);
      cpu->p = (cpu->p & ~FLAG_CARRY) | ((value & 0x80) ? FLAG_CARRY : 0);
      value = (value << 1) & 0xFF;
      mem_write(mem, addr, value);
      cpu->a |= value;
      set_zn_flags(cpu, cpu->a);
      break;
    case 0x03:  // (Indirect, X)
      tmp = (mem_read(mem, cpu->pc++) + cpu->x) & 0xFF;
      addr = mem_read(mem, tmp);
      addr |= (mem_read(mem, (tmp + 1) & 0xFF) << 8);
      value = mem_read(mem, addr);
      cpu->p = (cpu->p & ~FLAG_CARRY) | ((value & 0x80) ? FLAG_CARRY : 0);
      value = (value << 1) & 0xFF;
      mem_write(mem, addr, value);
      cpu->a |= value;
      set_zn_flags(cpu, cpu->a);
      break;
    case 0x13:  // (Indirect), Y
      tmp = (mem_read(mem, cpu->pc++) + cpu->x) & 0xFF;
      addr = mem_read(mem, tmp);
      addr |= (mem_read(mem, (tmp + 1) & 0xFF) << 8);
      addr += cpu->y;
      value = mem_read(mem, addr);
      cpu->p = (cpu->p & ~FLAG_CARRY) | ((value & 0x80) ? FLAG_CARRY : 0);
      value = (value << 1) & 0xFF;
      mem_write(mem, addr, value);
      cpu->a |= value;
      set_zn_flags(cpu, cpu->a);
      break;

    // ----- SRE (Shift Right and EOR) - Unofficial -----
    case 0x47:  // Zero Page
      addr = mem_read(mem, cpu->pc++);
      value = mem_read(mem, addr);
      cpu->p = (cpu->p & ~FLAG_CARRY) | (value & 0x01 ? FLAG_CARRY : 0);
      value = value >> 1;
      mem_write(mem, addr, value);
      cpu->a ^= value;
      set_zn_flags(cpu, cpu->a);
      break;
    case 0x57:  // Zero Page, X
      addr = (mem_read(mem, cpu->pc++) + cpu->x) & 0xFF;
      value = mem_read(mem, addr);
      cpu->p = (cpu->p & ~FLAG_CARRY) | (value & 0x01 ? FLAG_CARRY : 0);
      value = value >> 1;
      mem_write(mem, addr, value);
      cpu->a ^= value;
      set_zn_flags(cpu, cpu->a);
      break;
    case 0x4F:  // Absolute
      addr = mem_read(mem, cpu->pc++);
      addr |= (mem_read(mem, cpu->pc++) << 8);
      value = mem_read(mem, addr);
      cpu->p = (cpu->p & ~FLAG_CARRY) | (value & 0x01 ? FLAG_CARRY : 0);
      value = value >> 1;
      mem_write(mem, addr, value);
      cpu->a ^= value;
      set_zn_flags(cpu, cpu->a);
      break;
    case 0x5F:  // Absolute, X
      addr = mem_read(mem, cpu->pc++);
      addr |= (mem_read(mem, cpu->pc++) << 8);
      addr += cpu->x;
      value = mem_read(mem, addr);
      cpu->p = (cpu->p & ~FLAG_CARRY) | (value & 0x01 ? FLAG_CARRY : 0);
      value = value >> 1;
      mem_write(mem, addr, value);
      cpu->a ^= value;
      set_zn_flags(cpu, cpu->a);
      break;
    case 0x5B:  // Absolute, Y
      addr = mem_read(mem, cpu->pc++);
      addr |= (mem_read(mem, cpu->pc++) << 8);
      addr += cpu->y;
      value = mem_read(mem, addr);
      cpu->p = (cpu->p & ~FLAG_CARRY) | (value & 0x01 ? FLAG_CARRY : 0);
      value = value >> 1;
      mem_write(mem, addr, value);
      cpu->a ^= value;
      set_zn_flags(cpu, cpu->a);
      break;
    case 0x43:  // (Indirect, X)
      tmp = (mem_read(mem, cpu->pc++) + cpu->x) & 0xFF;
      addr = mem_read(mem, tmp);
      addr |= (mem_read(mem, (tmp + 1) & 0xFF) << 8);
      value = mem_read(mem, addr);
      cpu->p = (cpu->p & ~FLAG_CARRY) | (value & 0x01 ? FLAG_CARRY : 0);
      value = value >> 1;
      mem_write(mem, addr, value);
      cpu->a ^= value;
      set_zn_flags(cpu, cpu->a);
      break;
    case 0x53:  // (Indirect), Y
      tmp = mem_read(mem, cpu->pc++);
      addr = mem_read(mem, tmp);
      addr |= (mem_read(mem, (tmp + 1) & 0xFF) << 8);
      addr += cpu->y;
      value = mem_read(mem, addr);
      cpu->p = (cpu->p & ~FLAG_CARRY) | (value & 0x01 ? FLAG_CARRY : 0);
      value = value >> 1;
      mem_write(mem, addr, value);
      cpu->a ^= value;
      set_zn_flags(cpu, cpu->a);
      break;

    // ----- SRE (Shift Right and EOR) - Unofficial -----
    case 0x4B:  // Immediate - This one is tricky and might not be accurate
      value = mem_read(mem, cpu->pc++);
      cpu->a ^= (value >> 1) | ((cpu->a & 0x01) ? 0x80 : 0x00);
      cpu->p = (cpu->p & ~FLAG_CARRY) | (value & 0x01 ? FLAG_CARRY : 0);
      set_zn_flags(cpu, cpu->a);
	  break;

    default:
      printf("Unknown opcode: 0x%02X\n", opcode);
  }
}

void reset_cpu(cpu_t* cpu) {
  cpu->a = 0;
  cpu->x = 0;
  cpu->y = 0;
  cpu->sp = 0xFD;
  cpu->pc = 0x8000;  // Or any other reset vector you prefer
  cpu->p = FLAG_UNUSED;
}

#include <stdio.h>
#include <stdint.h>
#include <string.h>

#define MEM_SIZE 1024

/* ============================================================
 * Modelo Byte-Level
 * Memory : Addr -> Byte
 * ============================================================ */

typedef uint64_t Addr;
typedef uint8_t  Byte;

/* Memória */
Byte Memory[MEM_SIZE];

/* ============================================================
 * Escrita
 * ============================================================ */

void store8(Addr addr, Byte value)
{
    Memory[addr] = value;
}

/* ============================================================
 * Leituras
 * ============================================================ */

Byte load8(Addr addr)
{
    return Memory[addr];
}

/* Little-endian */
uint16_t load16(Addr addr)
{
    uint16_t b0 = Memory[addr];
    uint16_t b1 = Memory[addr + 1];

    return (b1 << 8) | b0;
}

/* Little-endian */
uint32_t load32(Addr addr)
{
    uint32_t b0 = Memory[addr];
    uint32_t b1 = Memory[addr + 1];
    uint32_t b2 = Memory[addr + 2];
    uint32_t b3 = Memory[addr + 3];

    return (b3 << 24) |
           (b2 << 16) |
           (b1 << 8)  |
            b0;
}

/* Little-endian */
uint64_t load64(Addr addr)
{
    uint64_t value = 0;

    for (int i = 0; i < 8; i++)
        value |= ((uint64_t)Memory[addr + i]) << (8 * i);

    return value;
}

/* ============================================================
 * Programa exemplo
 * ============================================================ */

int main(void)
{
    memset(Memory, 0, sizeof(Memory));

    Addr base = 100;

    /*
        char buf[4] = {0x11,0x22,0x33,0x44};
    */

    store8(base + 0, 0x11);
    store8(base + 1, 0x22);
    store8(base + 2, 0x33);
    store8(base + 3, 0x44);

    /*
        uint16_t *p = (uint16_t *)(buf + 1);

        Observe que este modelo NÃO verifica alinhamento.
        Apenas lê dois bytes consecutivos.
    */

    Addr p = base + 1;

    uint16_t x = load16(p);

    printf("Endereco base : %llu\n",
           (unsigned long long)base);

    printf("Endereco p    : %llu\n",
           (unsigned long long)p);

    printf("Valor lido    : 0x%04X\n", x);

    return 0;
}

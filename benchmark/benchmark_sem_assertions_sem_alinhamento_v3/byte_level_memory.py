from z3 import *

# =====================================================
# Modelo de Memória Byte-Level
# =====================================================

# Endereços de 64 bits
AddrSort = BitVecSort(64)

# Cada posição da memória armazena 8 bits
ByteSort = BitVecSort(8)

# Memória: endereço -> byte
Memory = Array("Memory", AddrSort, ByteSort)

# =====================================================
# Operações de escrita
# =====================================================

def store8(mem, addr, value):
    """Escreve um byte."""
    return Store(mem, addr, value)


# =====================================================
# Operações de leitura
# =====================================================

def load8(mem, addr):
    """Lê um byte."""
    return Select(mem, addr)


def load16(mem, addr):
    """Lê 16 bits (little-endian)."""
    b0 = Select(mem, addr)
    b1 = Select(mem, addr + BitVecVal(1, 64))
    return Concat(b1, b0)


def load32(mem, addr):
    """Lê 32 bits (little-endian)."""
    b0 = Select(mem, addr)
    b1 = Select(mem, addr + BitVecVal(1, 64))
    b2 = Select(mem, addr + BitVecVal(2, 64))
    b3 = Select(mem, addr + BitVecVal(3, 64))
    return Concat(b3, b2, b1, b0)


def load64(mem, addr):
    """Lê 64 bits (little-endian)."""
    bytes = [
        Select(mem, addr + BitVecVal(i, 64))
        for i in range(8)
    ]
    return Concat(*reversed(bytes))


# =====================================================
# Programa exemplo
# =====================================================

solver = Solver()

mem = Memory

base = BitVecVal(1000, 64)

# Simula:
#
# char buf[4];
# buf = {0x11,0x22,0x33,0x44}
#

mem = store8(mem, base + 0, BitVecVal(0x11, 8))
mem = store8(mem, base + 1, BitVecVal(0x22, 8))
mem = store8(mem, base + 2, BitVecVal(0x33, 8))
mem = store8(mem, base + 3, BitVecVal(0x44, 8))

# Ponteiro desalinhado
#
# uint16_t *p = (uint16_t*)(buf + 1);
#

p = base + BitVecVal(1, 64)

# Leitura de 16 bits
x = load16(mem, p)

solver.add(
    x == BitVecVal(0x3322, 16)
)

# =====================================================
# Resultado
# =====================================================

print("Resultado:", solver.check())

if solver.check() == sat:
    print(solver.model())

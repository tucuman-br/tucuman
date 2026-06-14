from z3 import *

# =====================================================
# CONFIGURAÇÃO
# =====================================================

ADDR_BITS = 32

AddrSort = BitVecSort(ADDR_BITS)
ByteSort = BitVecSort(8)

# =====================================================
# MEMÓRIA BYTE-LEVEL
# =====================================================

Memory = Array("Memory", AddrSort, ByteSort)

# =====================================================
# ESCRITA
# =====================================================

def store8(mem, addr, value):
    return Store(mem, addr, value)

# =====================================================
# LEITURA
# =====================================================

def load8(mem, addr):
    return Select(mem, addr)

def load16(mem, addr):

    b0 = Select(mem, addr)
    b1 = Select(mem, addr + BitVecVal(1, ADDR_BITS))

    return Concat(b1, b0)

# =====================================================
# ALINHAMENTO
# =====================================================

def aligned(addr, align):

    return URem(
        addr,
        BitVecVal(align, ADDR_BITS)
    ) == BitVecVal(0, ADDR_BITS)

# =====================================================
# SOLVER
# =====================================================

solver = Solver()

# =====================================================
# MEMÓRIA DE TESTE
#
# buf[0]=0x11
# buf[1]=0x22
# buf[2]=0x33
# buf[3]=0x44
# =====================================================

buf_base = BitVecVal(100, ADDR_BITS)

mem1 = store8(
    Memory,
    buf_base + BitVecVal(0, ADDR_BITS),
    BitVecVal(0x11, 8)
)

mem2 = store8(
    mem1,
    buf_base + BitVecVal(1, ADDR_BITS),
    BitVecVal(0x22, 8)
)

mem3 = store8(
    mem2,
    buf_base + BitVecVal(2, ADDR_BITS),
    BitVecVal(0x33, 8)
)

mem4 = store8(
    mem3,
    buf_base + BitVecVal(3, ADDR_BITS),
    BitVecVal(0x44, 8)
)

# =====================================================
# CAST
#
# uint16_t *p = (uint16_t *)(buf + 1)
# =====================================================

p = buf_base + BitVecVal(1, ADDR_BITS)

# =====================================================
# LEITURA
# =====================================================

x = load16(mem4, p)

# =====================================================
# EXPERIMENTO
# =====================================================

USE_ALIGNMENT_CHECK = False

if USE_ALIGNMENT_CHECK:

    solver.add(
        aligned(p, 2)
    )

# =====================================================
# EXECUÇÃO
# =====================================================

result = solver.check()

print()
print("Resultado SMT:", result)

print()
print("Endereco base =", 100)
print("Endereco p    =", 101)

print()

print(
    "Alinhado?",
    simplify(aligned(p, 2))
)

if result == sat:

    print()

    print(
        "Valor lido =",
        hex(
            simplify(x).as_long()
        )
    )

else:

    print()
    print("Violacao de alinhamento detectada")

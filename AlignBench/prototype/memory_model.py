from z3 import *

# =====================================================
# DEFINIÇÕES BÁSICAS
# =====================================================

ADDR_BITS = 32

AddrSort = BitVecSort(ADDR_BITS)
ByteSort = BitVecSort(8)

# Memória:
# endereço -> byte
Memory = Array('Memory', AddrSort, ByteSort)

# =====================================================
# OPERAÇÕES DE ESCRITA
# =====================================================

def store8(mem, addr, value):
    """
    Escreve 1 byte.
    """
    return Store(mem, addr, value)

# =====================================================
# OPERAÇÕES DE LEITURA
# =====================================================

def load8(mem, addr):

    return Select(mem, addr)


def load16(mem, addr):
    """
    Little-endian.
    """

    b0 = Select(mem, addr)
    b1 = Select(mem, addr + BitVecVal(1, ADDR_BITS))

    return Concat(b1, b0)


def load32(mem, addr):

    b0 = Select(mem, addr)
    b1 = Select(mem, addr + BitVecVal(1, ADDR_BITS))
    b2 = Select(mem, addr + BitVecVal(2, ADDR_BITS))
    b3 = Select(mem, addr + BitVecVal(3, ADDR_BITS))

    return Concat(b3, b2, b1, b0)

# =====================================================
# ALINHAMENTO
# =====================================================

def aligned(addr, n):
    """
    addr % n == 0
    """

    return URem(
        addr,
        BitVecVal(n, ADDR_BITS)
    ) == 0

# =====================================================
# PROGRAMA PRINCIPAL
# =====================================================

solver = Solver()

# endereço base do array

buf_base = BitVecVal(100, ADDR_BITS)

# inicializa memória

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
# uint16_t *p = (uint16_t *)(buf+1);
# =====================================================

p = buf_base + BitVecVal(1, ADDR_BITS)

# =====================================================
# LEITURA
#
# uint16_t x = *p;
# =====================================================

x = load16(mem4, p)

# =====================================================
# EXECUÇÃO
# =====================================================

if solver.check() == sat:

    model = solver.model()

    print("=== RESULTADOS ===")
    print()

    print("Endereco base =", 100)
    print("Endereco p    =", 101)

    print()

    print(
        "Alinhado para uint16_t ?",
        simplify(aligned(p, 2))
    )

    print()

    print(
        "Valor lido =",
        hex(
            simplify(x).as_long()
        )
    )

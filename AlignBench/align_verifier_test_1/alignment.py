ALIGNMENTS = {
    "char": 1,
    "uint8_t": 1,
    "uint16_t": 2,
    "uint32_t": 4,
    "uint64_t": 8
}

def alignment_of(type_name):
    return ALIGNMENTS[type_name]

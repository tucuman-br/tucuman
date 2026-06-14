import re

ALIGNMENTS = {
    "uint16_t": 2,
    "uint32_t": 4,
    "uint64_t": 8
}

def parse_file(filename):

    with open(filename, "r") as f:
        code = f.read()

    result = {}

    # char buf[4];
    array_match = re.search(
        r'char\s+(\w+)\[(\d+)\]',
        code
    )

    if not array_match:
        raise Exception("Array char não encontrado")

    result["array_name"] = array_match.group(1)
    result["array_size"] = int(array_match.group(2))

    # uint16_t *p = (uint16_t *)(buf + 1);
    cast_match = re.search(
        r'(uint16_t|uint32_t|uint64_t)\s*\*\s*(\w+)\s*=\s*\(\s*\1\s*\*\s*\)\s*\(\s*(\w+)\s*\+\s*(\d+)\s*\)',
        code
    )

    if not cast_match:
        raise Exception("Cast não encontrado")

    result["type"] = cast_match.group(1)
    result["pointer"] = cast_match.group(2)
    result["base"] = cast_match.group(3)
    result["offset"] = int(cast_match.group(4))
    result["alignment"] = ALIGNMENTS[result["type"]]

    return result

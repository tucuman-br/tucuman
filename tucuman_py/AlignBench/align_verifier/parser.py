import re


# =====================================================
# TIPOS SUPORTADOS
# =====================================================

ALIGNMENTS = {
    "uint16_t": 2,
    "uint32_t": 4,
    "uint64_t": 8
}


# =====================================================
# UTILITÁRIOS
# =====================================================

def detect_ptr_type(code):

    for t in [
        "uint16_t",
        "uint32_t",
        "uint64_t"
    ]:

        if t in code:
            return t

    raise Exception(
        "Tipo nao suportado"
    )


def detect_alignment(ptr_type):

    return ALIGNMENTS[ptr_type]


# =====================================================
# PARSER PRINCIPAL
# =====================================================

def parse_file(filename):

    with open(filename, "r") as f:
        code = f.read()

    result = {}

    result["filename"] = filename

    ptr_type = detect_ptr_type(code)

    result["ptr_type"] = ptr_type
    result["alignment"] = detect_alignment(ptr_type)

    # --------------------------------------------------
    # packed struct ?
    # --------------------------------------------------

    result["packed"] = (
        "__attribute__((packed))" in code
    )

    # ==================================================
    # E1 / E2
    # offset simbólico
    # ==================================================

    if "nondet_uint" in code:

        result["kind"] = "symbolic"

        m = re.search(
            r"i\s*<\s*(\d+)",
            code
        )

        if m:

            result["symbolic_bound"] = int(
                m.group(1)
            )

        else:

            result["symbolic_bound"] = 8

        return result

    # ==================================================
    # offsetof(...)
    # B2
    # ==================================================

    if "offsetof" in code:

        result["kind"] = "offsetof"

        result["offset"] = (
            result["alignment"]
        )

        return result

    # ==================================================
    # acesso a campo .b
    #
    # cobre:
    #
    # &s.b
    # &sp.b
    # &obj.b
    # &qualquer_variavel.b
    #
    # H1-H6
    # J1-J3
    # ==================================================

    m = re.search(
        r"&\s*\w+\.b",
        code
    )

    if m:

        if result["packed"]:

            result["kind"] = "packed_field"

            result["offset"] = 1

        else:

            result["kind"] = "field"

            result["offset"] = (
                result["alignment"]
            )

        return result

    # ==================================================
    # sizeof(char)
    # F1-F3
    # ==================================================

    if "sizeof(char)" in code:

        result["kind"] = "offset"

        result["offset"] = 1

        return result

    # ==================================================
    # buf + N
    #
    # A1-A3
    # G1-G3
    # I1-I3
    # ==================================================

    m = re.search(
        r"buf\s*\+\s*(\d+)",
        code
    )

    if m:

        result["kind"] = "offset"

        result["offset"] = int(
            m.group(1)
        )

        return result

    # ==================================================
    # base + N
    #
    # B1
    # ==================================================

    m = re.search(
        r"base\s*\+\s*(\d+)",
        code
    )

    if m:

        result["kind"] = "offset"

        result["offset"] = int(
            m.group(1)
        )

        return result

    # ==================================================
    # vec[N]
    #
    # D1
    # ==================================================

    m = re.search(
        r"vec\[(\d+)\]",
        code
    )

    if m:

        result["kind"] = "offset"

        result["offset"] = int(
            m.group(1)
        )

        return result

    # ==================================================
    # ((char *)&x + N)
    #
    # C1
    # ==================================================

    m = re.search(
        r"&x\s*\+\s*(\d+)",
        code
    )

    if m:

        result["kind"] = "offset"
  
        result["offset"] = int(
            m.group(1)
        )

      return result

    

    # ==================================================
    # (void*)buf + N
    #
    # I1-I3
    # ==================================================

    m = re.search(
        r"void\s*\*\)\s*buf\s*\+\s*(\d+)",
        code
    )

    if m:

        result["kind"] = "offset"

        result["offset"] = int(
            m.group(1)
        )

        return result

    # ==================================================
    # cast alinhado
    #
    # C2
    # ==================================================

    if "&x" in code:

        result["kind"] = "offset"

        result["offset"] = 0

        return result

    raise Exception(
        "Padrao nao reconhecido"
    )

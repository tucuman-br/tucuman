import re

from ast_nodes import (
    ByteArray,
    PointerCast,
    StructField,
    StructDecl,
    OffsetOf
)

# =====================================================
# PARSER
# =====================================================

def parse_file(filename):

    with open(filename, "r") as f:
        code = f.read()

    result = {
        "arrays": [],
        "casts": [],
        "structs": [],
        "offsetofs": []
    }

    # -------------------------------------------------
    # Arrays
    # -------------------------------------------------

    array_pattern = r'char\s+(\w+)\[(\d+)\]'

    for m in re.finditer(array_pattern, code):

        result["arrays"].append(
            ByteArray(
                m.group(1),
                int(m.group(2))
            )
        )

    # -------------------------------------------------
    # Casts
    # -------------------------------------------------

    cast_pattern = (
        r'(uint16_t|uint32_t|uint64_t)'
        r'\s*\*\s*(\w+)'
        r'\s*=\s*'
        r'\(\s*\1\s*\*\s*\)'
        r'\s*\(\s*(\w+)\s*\+\s*(\d+)\s*\)'
    )

    for m in re.finditer(cast_pattern, code):

        result["casts"].append(

            PointerCast(
                ptr_name=m.group(2),
                ptr_type=m.group(1),
                base_name=m.group(3),
                offset=int(m.group(4))
            )

        )

    # -------------------------------------------------
    # Structs
    # -------------------------------------------------

    struct_pattern = (
        r'struct\s+(\w+)\s*'
        r'\{(.*?)\};'
    )

    for sm in re.finditer(
        struct_pattern,
        code,
        re.DOTALL
    ):

        struct_name = sm.group(1)
        body = sm.group(2)

        fields = []

        field_pattern = (
            r'(char|uint16_t|uint32_t|uint64_t)'
            r'\s+(\w+)\s*;'
        )

        for fm in re.finditer(
            field_pattern,
            body
        ):

            fields.append(

                StructField(
                    field_type=fm.group(1),
                    field_name=fm.group(2)
                )

            )

        result["structs"].append(

            StructDecl(
                struct_name,
                fields
            )

        )

    # -------------------------------------------------
    # offsetof
    # -------------------------------------------------

    offsetof_pattern = (
        r'offsetof'
        r'\s*\('
        r'\s*struct\s+(\w+)'
        r'\s*,\s*(\w+)'
        r'\s*\)'
    )

    for m in re.finditer(
        offsetof_pattern,
        code
    ):

        result["offsetofs"].append(

            OffsetOf(
                struct_name=m.group(1),
                field_name=m.group(2)
            )

        )

    return result

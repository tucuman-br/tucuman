from alignment import alignment_of

def align_up(value, align):

    remainder = value % align

    if remainder == 0:
        return value

    return value + (align - remainder)

def compute_struct_layout(struct_decl):

    offsets = {}

    current = 0

    for field in struct_decl.fields:

        align = alignment_of(
            field.field_type
        )

        current = align_up(
            current,
            align
        )

        offsets[field.field_name] = current

        if field.field_type == "char":
            size = 1
        elif field.field_type == "uint16_t":
            size = 2
        elif field.field_type == "uint32_t":
            size = 4
        elif field.field_type == "uint64_t":
            size = 8
        else:
            raise Exception(
                f"Tipo desconhecido: {field.field_type}"
            )

        current += size

    return offsets

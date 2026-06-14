from dataclasses import dataclass

@dataclass
class ByteArray:
    name: str
    size: int

@dataclass
class PointerCast:
    ptr_name: str
    ptr_type: str
    base_name: str
    offset: int

@dataclass
class StructField:
    field_type: str
    field_name: str

@dataclass
class StructDecl:
    name: str
    fields: list

@dataclass
class OffsetOf:
    struct_name: str
    field_name: str

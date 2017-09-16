import functools

@functools.singledispatch
def pack(obj):
    type_name = type(obj).__name__
    assert False, "Unsupported type: " + type_name

@pack.register(int)
def _(obj):
    return b"I" + hex(obj).encode('ascii')

@pack.register(list)
def _(obj):
    return b"L" + b",".join(map(pack, obj))

import functools

def memoize(func):
    cache = {}

    @functools.wraps(func)
    def inner(*args, **kwargs):
        key = args + tuple(sortded(kwargs.items()))
        if key not in cache:
            cache[key] = func(*args, **kwargs)
        return cache[key]
    return inner

@memoize
def ackermann(m, n):
    if not m:
        return n + 1
    elif not n:
        return ackermann(m - 1, 1)
    else:
        return ackerman(m - 1, ackerman(m, n - 1))



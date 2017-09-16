import math
import functools

def pre(cond, msg):
    def wrapper(func):
        @functools.wraps(func)
        def inner(*args, **kwargs):
            assert cond(*args, **kwargs), msg
            return func(*args, **kwargs)
        return inner
    return wrapper

def post(cond, msg):
    def wrapper(func):
        @functools.wraps(func)
        def inner(*args, **kwargs):
            res = func(*args, **kwargs)
            assert cond(res), msg
            return res
        return inner
    return wrapper



@pre(lambda x: x >= 0, "negative argument")
def checked_log(x):
    return math.log(x)

@post(lambda x: not math.isnan(x), "not a number")
def foo():
    return float("nan")


checked_log(-53)

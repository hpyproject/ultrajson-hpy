import sys
import time
import json
import ujson

from tests.support import import_ujson_hpy

ujson_hpy_universal = import_ujson_hpy("universal")
ujson_hpy_universal.__name__ = 'ujson_hpy_universal'

ujson_hpy_debug = import_ujson_hpy("debug")
ujson_hpy_debug.__name__ = 'ujson_hpy_debug'

CPYTHON = (sys.implementation.name == "cpython")
if CPYTHON:
    ujson_hpy_cpython = import_ujson_hpy("cpython")
    ujson_hpy_cpython.__name__ = 'ujson_hpy_cpython'


def benchmark(mod, fname, N):
    a = time.time()
    for i in range(N):
        with open(fname, 'rb') as f:
            for line in f:
                mod.loads(line)
    b = time.time()
    t = (b-a) * 1000.0 / N
    print('%20s: %6.2f ms per iteration [%2d iterations]' % (mod.__name__, t, N))


def main():
    N = 100
    fname = 'benchmark/2015-01-01-15.json'
    benchmark(json, fname, N)
    benchmark(ujson_hpy_universal, fname, N)
    benchmark(ujson_hpy_debug, fname, N)
    benchmark(ujson, fname, N)
    if CPYTHON:
        benchmark(ujson_hpy_cpython, fname, N)


if __name__ == '__main__':
    main()

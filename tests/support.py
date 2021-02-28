""" Support functions for tests and benchmarking. """

import importlib.util
import glob
import os
import sys

import hpy.universal


def import_ujson_hpy(abi="default"):
    """ Either load the default ujson_hpy, or specifically the ujson_hpy
        universal module if the UJSON_UNIVERSAL environment variable is
        set to a non-empty value.
    """
    abi = os.environ.get("HPY_ABI", abi)
    if abi == "default":
        import ujson_hpy
        mod = ujson_hpy
    elif abi == "cpython":
        mod = load_cpython_module(
            "ujson_hpy",
            find_so_filename("ujson_hpy.cpython-*.so"))
    elif abi == "universal":
        mod = load_universal_module(
            "ujson_hpy",
            find_so_filename("ujson_hpy.hpy.so"),
            debug=False)
    elif abi == "debug":
        mod = load_universal_module(
            "ujson_hpy",
            find_so_filename("ujson_hpy.hpy.so"),
            debug=True)
    else:
        raise ValueError("Unknown HPY_ABI {!r}".format(abi))
    return mod


def find_so_filename(pattern):
    """ Search for an extension module .so file that matches the specified
        pattern.
    """
    for p in sys.path:
        paths = glob.glob(os.path.join(p, pattern))
        if not paths:
            continue
        if len(paths) > 1:
            raise RuntimeError(
                "Found multiple possible .so files for pattern {!r} in"
                " sys.path entry {!r}".format(pattern, p))
        return paths[0]
    raise RuntimeError(
        "Could not find .so file for pattern {!r} in sys.path".format(pattern))


def load_universal_module(name, so_filename, debug):
    """ Load a universal ABI module .so file.

        Copied from hpy/tests/support.py.
    """
    assert name not in sys.modules
    mod = hpy.universal.load(name, so_filename, debug=debug)
    mod.__file__ = so_filename
    return mod


def load_cpython_module(name, so_filename):
    """ Load a cpython ABI module .so file.

        Copied from hpy/tests/support.py.
    """
    # we've got a normal CPython module compiled with the CPython API/ABI,
    # let's load it normally. It is important to do the imports only here,
    # because this file will be imported also by PyPy tests which runs on
    # Python2
    assert name not in sys.modules
    spec = importlib.util.spec_from_file_location(name, so_filename)
    try:
        # module_from_spec adds the module to sys.modules
        module = importlib.util.module_from_spec(spec)
    finally:
        if name in sys.modules:
            del sys.modules[name]
    spec.loader.exec_module(module)
    return module

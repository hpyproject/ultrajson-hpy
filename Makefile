.PHONY: all test benchmark

all:
	python setup.py build
	python setup.py build_ext -if
	@echo
	@echo
	@echo UNIVERSAL
	python setup.py --hpy-abi=universal build_ext -if

test:
	HPY_ABI=cpython python -m pytest tests/tests.py
	HPY_ABI=universal python -m pytest tests/tests.py
	HPY_ABI=debug python -m pytest tests/tests.py

benchmark:
	python -m benchmark.main

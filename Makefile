.PHONY: all test benchmark

all:
	python setup.py build_ext -if
	@echo
	@echo
	@echo UNIVERSAL
	python setup.py --hpy-abi=universal build_ext -if

test:
	python -m pytest tests/tests.py
	#XXX we need a way to re-enable this test on CPython
	#HPY_UNIVERSAL=1 python -m pytest tests/tests.py

benchmark:
	python -m benchmark.main

all:
	cd gerador/cmake-build-debug && $(MAKE)
	cd motor/cmake-build-debug && $(MAKE)
	$(MAKE) run

run:
	cd gerador/cmake-build-debug && ./gerador plane 4 plane.3d
	cd gerador/cmake-build-debug && ./gerador box 2 2 2 3 box.3d
	cd gerador/cmake-build-debug && ./gerador sphere 2 50 50 sphere.3d
	cd gerador/cmake-build-debug && ./gerador cone 2 2 50 50 cone.3d
	cd motor/cmake-build-debug && ./motor configuracao.xml

all:
	@cd gerador && $(MAKE) -s
	@cd motor && $(MAKE) -s
	@$(MAKE) -s run

run:
	echo "./gerador plane 4 plane.3d"
	@cd gerador && ./gerador plane 4 plane.3d
	echo "./gerador box 2 2 2 3 box.3d"
	@cd gerador && ./gerador box 2 2 2 3 box.3d
	echo "./gerador sphere 2 50 50 sphere.3d"
	@cd gerador && ./gerador sphere 2 50 50 sphere.3d
	echo "./gerador cone 2 2 50 50 cone.3d"
	@cd gerador && ./gerador cone 2 2 50 50 cone.3d
	echo "./motor configuracao.xml"
	@cd motor && ./motor configuracao.xml &

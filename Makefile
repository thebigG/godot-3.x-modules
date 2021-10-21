CORES := 4

linux:
	 scons p=x11 target=debug -j$(CORES)
docs:
	./bin/godot.x11.tools.64 --doctool .

clean:
	rm -r bin

format:
	./misc/scripts/clang_format.sh

check_docs:
	doc/tools/makerst.py --dry-run doc/classes modules

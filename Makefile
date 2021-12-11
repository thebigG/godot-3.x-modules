CORES := 8

linux-debug:
	 scons p=x11 target=debug -j$(CORES)

linux-release:
	 scons p=x11 target=release_debug -j$(CORES)

linux-server:
	scons -j$(CORES) platform=server tools=no target=release

linux-server-tools:
	scons -j${CORES} platform=server tools=yes target=release_debug

docs:
	./bin/godot.x11.tools.64 --doctool .

clean:
	rm -r bin

clean-scons:
	scons -j${CORES} --clean
	scons -j${CORES} --no-cache

format:
	./misc/scripts/clang_format.sh

check_docs:
	doc/tools/makerst.py --dry-run doc/classes modules

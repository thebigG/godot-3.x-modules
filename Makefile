CORES := 8

linux-debug:
	 scons p=x11 target=debug -j$(CORES)

linux-release:
	 scons p=x11 target=release_debug -j$(CORES)

linux-server:
	scons -j$(CORES) platform=server tools=no target=release

linux-server-tools:
	scons -j${CORES} platform=server tools=yes target=release_debug


javascript-release-debug:
	scons platform=javascript tools=no target=release_debug

javascript-release:
	scons platform=javascript tools=no target=release


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
	doc/tools/make_rst.py --dry-run doc/classes modules

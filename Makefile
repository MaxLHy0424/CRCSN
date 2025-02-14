include msys2
compiler         = g++.exe
args_defines     = -D_CRT_SECURE_NO_WARNINGS -DANSI -D_ANSI
args_link        =
args_std         = gnu++26
args_warning     = -Wall -Wextra -Weffc++
args_opt_debug   = -Og
args_opt_release = -Ofast -flto=auto -fno-rtti
input_charset    = utf-8
output_charset   = gb18030
args_base        = -pipe -finput-charset=$(input_charset) -fexec-charset=$(output_charset) -std=$(args_std) $(args_link) $(args_warning) $(args_defines)
args_debug       = -g3 $(args_base) $(args_opt_debug)
args_release     = -DNDEBUG -static $(args_base) $(args_opt_release)
.PHONY: init build clean debug release
all: init build release
init:
	$(msys2_path)/usr/bin/pacman.exe -Sy --noconfirm --needed\
	 mingw-w64-i686-toolchain\
	 mingw-w64-ucrt-x86_64-toolchain\
	 make\
	 git\
	 base\
	 base-devel\
	 binutils
build: debug release
debug: bin/debug/__debug__.exe
release: bin/release/CRCSN-i686-msvcrt.exe\
         bin/release/CRCSN-x86_64-ucrt.exe
clean:
	$(msys2_path)/usr/bin/rm.exe -rf bin
	$(msys2_path)/usr/bin/mkdir.exe bin
	$(msys2_path)/usr/bin/touch.exe bin/.gitkeep
dependencies_debug = src/*
bin/debug/__debug__.exe: $(dependencies_debug) bin/debug/.gitkeep
	$(msys2_path)/ucrt64/bin/$(compiler) $(dependencies_debug).cpp $(args_debug) -o $@
dependencies_release_32bit = bin/info-i686.o src/*
bin/release/CRCSN-i686-msvcrt.exe: $(dependencies_release_32bit) bin/release/.gitkeep
	$(msys2_path)/mingw32/bin/$(compiler) $(dependencies_release_32bit).cpp $(args_release) -o $@
dependencies_release_64bit = bin/info-x86_64.o src/*
bin/release/CRCSN-x86_64-ucrt.exe: $(release_64bit_dependencies) bin/release/.gitkeep
	$(msys2_path)/ucrt64/bin/$(compiler) $(release_64bit_dependencies).cpp $(args_release) -o $@
dependencies_info = info.rc img/favicon.ico src/info.hpp
bin/info-i686.o: $(info_bin_dependencies) bin/.gitkeep
	$(msys2_path)/usr/bin/windres.exe -i $< -o $@ $(args_defines) -F pe-i386
bin/info-x86_64.o: $(info_bin_dependencies) bin/.gitkeep
	$(msys2_path)/usr/bin/windres.exe -i $< -o $@ $(args_defines) -F pe-x86-64
bin/.gitkeep:
	$(msys2_path)/usr/bin/mkdir.exe bin -p
	$(msys2_path)/usr/bin/touch.exe $@
bin/debug/.gitkeep: bin/.gitkeep
	$(msys2_path)/usr/bin/mkdir.exe bin/debug -p
	$(msys2_path)/usr/bin/touch.exe $@
bin/release/.gitkeep: bin/.gitkeep
	$(msys2_path)/usr/bin/mkdir.exe bin/release -p
	$(msys2_path)/usr/bin/touch.exe $@
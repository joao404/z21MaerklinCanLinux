# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.28

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/marcel/Dokumente/Entwicklung/Eisenbahn/Rocrail/MaerklinCan/z21MaerklinCanLinux

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/marcel/Dokumente/Entwicklung/Eisenbahn/Rocrail/MaerklinCan/z21MaerklinCanLinux/build

# Include any dependencies generated for this target.
include CMakeFiles/z21maerklincan.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/z21maerklincan.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/z21maerklincan.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/z21maerklincan.dir/flags.make

CMakeFiles/z21maerklincan.dir/src/main.cpp.o: CMakeFiles/z21maerklincan.dir/flags.make
CMakeFiles/z21maerklincan.dir/src/main.cpp.o: /home/marcel/Dokumente/Entwicklung/Eisenbahn/Rocrail/MaerklinCan/z21MaerklinCanLinux/src/main.cpp
CMakeFiles/z21maerklincan.dir/src/main.cpp.o: CMakeFiles/z21maerklincan.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/marcel/Dokumente/Entwicklung/Eisenbahn/Rocrail/MaerklinCan/z21MaerklinCanLinux/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/z21maerklincan.dir/src/main.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/z21maerklincan.dir/src/main.cpp.o -MF CMakeFiles/z21maerklincan.dir/src/main.cpp.o.d -o CMakeFiles/z21maerklincan.dir/src/main.cpp.o -c /home/marcel/Dokumente/Entwicklung/Eisenbahn/Rocrail/MaerklinCan/z21MaerklinCanLinux/src/main.cpp

CMakeFiles/z21maerklincan.dir/src/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/z21maerklincan.dir/src/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/marcel/Dokumente/Entwicklung/Eisenbahn/Rocrail/MaerklinCan/z21MaerklinCanLinux/src/main.cpp > CMakeFiles/z21maerklincan.dir/src/main.cpp.i

CMakeFiles/z21maerklincan.dir/src/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/z21maerklincan.dir/src/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/marcel/Dokumente/Entwicklung/Eisenbahn/Rocrail/MaerklinCan/z21MaerklinCanLinux/src/main.cpp -o CMakeFiles/z21maerklincan.dir/src/main.cpp.s

CMakeFiles/z21maerklincan.dir/src/z60.cpp.o: CMakeFiles/z21maerklincan.dir/flags.make
CMakeFiles/z21maerklincan.dir/src/z60.cpp.o: /home/marcel/Dokumente/Entwicklung/Eisenbahn/Rocrail/MaerklinCan/z21MaerklinCanLinux/src/z60.cpp
CMakeFiles/z21maerklincan.dir/src/z60.cpp.o: CMakeFiles/z21maerklincan.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/marcel/Dokumente/Entwicklung/Eisenbahn/Rocrail/MaerklinCan/z21MaerklinCanLinux/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/z21maerklincan.dir/src/z60.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/z21maerklincan.dir/src/z60.cpp.o -MF CMakeFiles/z21maerklincan.dir/src/z60.cpp.o.d -o CMakeFiles/z21maerklincan.dir/src/z60.cpp.o -c /home/marcel/Dokumente/Entwicklung/Eisenbahn/Rocrail/MaerklinCan/z21MaerklinCanLinux/src/z60.cpp

CMakeFiles/z21maerklincan.dir/src/z60.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/z21maerklincan.dir/src/z60.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/marcel/Dokumente/Entwicklung/Eisenbahn/Rocrail/MaerklinCan/z21MaerklinCanLinux/src/z60.cpp > CMakeFiles/z21maerklincan.dir/src/z60.cpp.i

CMakeFiles/z21maerklincan.dir/src/z60.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/z21maerklincan.dir/src/z60.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/marcel/Dokumente/Entwicklung/Eisenbahn/Rocrail/MaerklinCan/z21MaerklinCanLinux/src/z60.cpp -o CMakeFiles/z21maerklincan.dir/src/z60.cpp.s

CMakeFiles/z21maerklincan.dir/src/Can2Lan.cpp.o: CMakeFiles/z21maerklincan.dir/flags.make
CMakeFiles/z21maerklincan.dir/src/Can2Lan.cpp.o: /home/marcel/Dokumente/Entwicklung/Eisenbahn/Rocrail/MaerklinCan/z21MaerklinCanLinux/src/Can2Lan.cpp
CMakeFiles/z21maerklincan.dir/src/Can2Lan.cpp.o: CMakeFiles/z21maerklincan.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/marcel/Dokumente/Entwicklung/Eisenbahn/Rocrail/MaerklinCan/z21MaerklinCanLinux/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/z21maerklincan.dir/src/Can2Lan.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/z21maerklincan.dir/src/Can2Lan.cpp.o -MF CMakeFiles/z21maerklincan.dir/src/Can2Lan.cpp.o.d -o CMakeFiles/z21maerklincan.dir/src/Can2Lan.cpp.o -c /home/marcel/Dokumente/Entwicklung/Eisenbahn/Rocrail/MaerklinCan/z21MaerklinCanLinux/src/Can2Lan.cpp

CMakeFiles/z21maerklincan.dir/src/Can2Lan.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/z21maerklincan.dir/src/Can2Lan.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/marcel/Dokumente/Entwicklung/Eisenbahn/Rocrail/MaerklinCan/z21MaerklinCanLinux/src/Can2Lan.cpp > CMakeFiles/z21maerklincan.dir/src/Can2Lan.cpp.i

CMakeFiles/z21maerklincan.dir/src/Can2Lan.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/z21maerklincan.dir/src/Can2Lan.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/marcel/Dokumente/Entwicklung/Eisenbahn/Rocrail/MaerklinCan/z21MaerklinCanLinux/src/Can2Lan.cpp -o CMakeFiles/z21maerklincan.dir/src/Can2Lan.cpp.s

CMakeFiles/z21maerklincan.dir/src/Cs2DataParser.cpp.o: CMakeFiles/z21maerklincan.dir/flags.make
CMakeFiles/z21maerklincan.dir/src/Cs2DataParser.cpp.o: /home/marcel/Dokumente/Entwicklung/Eisenbahn/Rocrail/MaerklinCan/z21MaerklinCanLinux/src/Cs2DataParser.cpp
CMakeFiles/z21maerklincan.dir/src/Cs2DataParser.cpp.o: CMakeFiles/z21maerklincan.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/marcel/Dokumente/Entwicklung/Eisenbahn/Rocrail/MaerklinCan/z21MaerklinCanLinux/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/z21maerklincan.dir/src/Cs2DataParser.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/z21maerklincan.dir/src/Cs2DataParser.cpp.o -MF CMakeFiles/z21maerklincan.dir/src/Cs2DataParser.cpp.o.d -o CMakeFiles/z21maerklincan.dir/src/Cs2DataParser.cpp.o -c /home/marcel/Dokumente/Entwicklung/Eisenbahn/Rocrail/MaerklinCan/z21MaerklinCanLinux/src/Cs2DataParser.cpp

CMakeFiles/z21maerklincan.dir/src/Cs2DataParser.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/z21maerklincan.dir/src/Cs2DataParser.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/marcel/Dokumente/Entwicklung/Eisenbahn/Rocrail/MaerklinCan/z21MaerklinCanLinux/src/Cs2DataParser.cpp > CMakeFiles/z21maerklincan.dir/src/Cs2DataParser.cpp.i

CMakeFiles/z21maerklincan.dir/src/Cs2DataParser.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/z21maerklincan.dir/src/Cs2DataParser.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/marcel/Dokumente/Entwicklung/Eisenbahn/Rocrail/MaerklinCan/z21MaerklinCanLinux/src/Cs2DataParser.cpp -o CMakeFiles/z21maerklincan.dir/src/Cs2DataParser.cpp.s

CMakeFiles/z21maerklincan.dir/src/WebService.cpp.o: CMakeFiles/z21maerklincan.dir/flags.make
CMakeFiles/z21maerklincan.dir/src/WebService.cpp.o: /home/marcel/Dokumente/Entwicklung/Eisenbahn/Rocrail/MaerklinCan/z21MaerklinCanLinux/src/WebService.cpp
CMakeFiles/z21maerklincan.dir/src/WebService.cpp.o: CMakeFiles/z21maerklincan.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/marcel/Dokumente/Entwicklung/Eisenbahn/Rocrail/MaerklinCan/z21MaerklinCanLinux/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/z21maerklincan.dir/src/WebService.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/z21maerklincan.dir/src/WebService.cpp.o -MF CMakeFiles/z21maerklincan.dir/src/WebService.cpp.o.d -o CMakeFiles/z21maerklincan.dir/src/WebService.cpp.o -c /home/marcel/Dokumente/Entwicklung/Eisenbahn/Rocrail/MaerklinCan/z21MaerklinCanLinux/src/WebService.cpp

CMakeFiles/z21maerklincan.dir/src/WebService.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/z21maerklincan.dir/src/WebService.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/marcel/Dokumente/Entwicklung/Eisenbahn/Rocrail/MaerklinCan/z21MaerklinCanLinux/src/WebService.cpp > CMakeFiles/z21maerklincan.dir/src/WebService.cpp.i

CMakeFiles/z21maerklincan.dir/src/WebService.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/z21maerklincan.dir/src/WebService.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/marcel/Dokumente/Entwicklung/Eisenbahn/Rocrail/MaerklinCan/z21MaerklinCanLinux/src/WebService.cpp -o CMakeFiles/z21maerklincan.dir/src/WebService.cpp.s

CMakeFiles/z21maerklincan.dir/src/trainBoxMaerklin/CanInterfaceLinux.cpp.o: CMakeFiles/z21maerklincan.dir/flags.make
CMakeFiles/z21maerklincan.dir/src/trainBoxMaerklin/CanInterfaceLinux.cpp.o: /home/marcel/Dokumente/Entwicklung/Eisenbahn/Rocrail/MaerklinCan/z21MaerklinCanLinux/src/trainBoxMaerklin/CanInterfaceLinux.cpp
CMakeFiles/z21maerklincan.dir/src/trainBoxMaerklin/CanInterfaceLinux.cpp.o: CMakeFiles/z21maerklincan.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/marcel/Dokumente/Entwicklung/Eisenbahn/Rocrail/MaerklinCan/z21MaerklinCanLinux/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/z21maerklincan.dir/src/trainBoxMaerklin/CanInterfaceLinux.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/z21maerklincan.dir/src/trainBoxMaerklin/CanInterfaceLinux.cpp.o -MF CMakeFiles/z21maerklincan.dir/src/trainBoxMaerklin/CanInterfaceLinux.cpp.o.d -o CMakeFiles/z21maerklincan.dir/src/trainBoxMaerklin/CanInterfaceLinux.cpp.o -c /home/marcel/Dokumente/Entwicklung/Eisenbahn/Rocrail/MaerklinCan/z21MaerklinCanLinux/src/trainBoxMaerklin/CanInterfaceLinux.cpp

CMakeFiles/z21maerklincan.dir/src/trainBoxMaerklin/CanInterfaceLinux.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/z21maerklincan.dir/src/trainBoxMaerklin/CanInterfaceLinux.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/marcel/Dokumente/Entwicklung/Eisenbahn/Rocrail/MaerklinCan/z21MaerklinCanLinux/src/trainBoxMaerklin/CanInterfaceLinux.cpp > CMakeFiles/z21maerklincan.dir/src/trainBoxMaerklin/CanInterfaceLinux.cpp.i

CMakeFiles/z21maerklincan.dir/src/trainBoxMaerklin/CanInterfaceLinux.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/z21maerklincan.dir/src/trainBoxMaerklin/CanInterfaceLinux.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/marcel/Dokumente/Entwicklung/Eisenbahn/Rocrail/MaerklinCan/z21MaerklinCanLinux/src/trainBoxMaerklin/CanInterfaceLinux.cpp -o CMakeFiles/z21maerklincan.dir/src/trainBoxMaerklin/CanInterfaceLinux.cpp.s

CMakeFiles/z21maerklincan.dir/src/trainBoxMaerklin/MaerklinCanInterface.cpp.o: CMakeFiles/z21maerklincan.dir/flags.make
CMakeFiles/z21maerklincan.dir/src/trainBoxMaerklin/MaerklinCanInterface.cpp.o: /home/marcel/Dokumente/Entwicklung/Eisenbahn/Rocrail/MaerklinCan/z21MaerklinCanLinux/src/trainBoxMaerklin/MaerklinCanInterface.cpp
CMakeFiles/z21maerklincan.dir/src/trainBoxMaerklin/MaerklinCanInterface.cpp.o: CMakeFiles/z21maerklincan.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/marcel/Dokumente/Entwicklung/Eisenbahn/Rocrail/MaerklinCan/z21MaerklinCanLinux/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object CMakeFiles/z21maerklincan.dir/src/trainBoxMaerklin/MaerklinCanInterface.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/z21maerklincan.dir/src/trainBoxMaerklin/MaerklinCanInterface.cpp.o -MF CMakeFiles/z21maerklincan.dir/src/trainBoxMaerklin/MaerklinCanInterface.cpp.o.d -o CMakeFiles/z21maerklincan.dir/src/trainBoxMaerklin/MaerklinCanInterface.cpp.o -c /home/marcel/Dokumente/Entwicklung/Eisenbahn/Rocrail/MaerklinCan/z21MaerklinCanLinux/src/trainBoxMaerklin/MaerklinCanInterface.cpp

CMakeFiles/z21maerklincan.dir/src/trainBoxMaerklin/MaerklinCanInterface.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/z21maerklincan.dir/src/trainBoxMaerklin/MaerklinCanInterface.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/marcel/Dokumente/Entwicklung/Eisenbahn/Rocrail/MaerklinCan/z21MaerklinCanLinux/src/trainBoxMaerklin/MaerklinCanInterface.cpp > CMakeFiles/z21maerklincan.dir/src/trainBoxMaerklin/MaerklinCanInterface.cpp.i

CMakeFiles/z21maerklincan.dir/src/trainBoxMaerklin/MaerklinCanInterface.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/z21maerklincan.dir/src/trainBoxMaerklin/MaerklinCanInterface.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/marcel/Dokumente/Entwicklung/Eisenbahn/Rocrail/MaerklinCan/z21MaerklinCanLinux/src/trainBoxMaerklin/MaerklinCanInterface.cpp -o CMakeFiles/z21maerklincan.dir/src/trainBoxMaerklin/MaerklinCanInterface.cpp.s

CMakeFiles/z21maerklincan.dir/src/trainBoxMaerklin/MaerklinCanInterfaceObserver.cpp.o: CMakeFiles/z21maerklincan.dir/flags.make
CMakeFiles/z21maerklincan.dir/src/trainBoxMaerklin/MaerklinCanInterfaceObserver.cpp.o: /home/marcel/Dokumente/Entwicklung/Eisenbahn/Rocrail/MaerklinCan/z21MaerklinCanLinux/src/trainBoxMaerklin/MaerklinCanInterfaceObserver.cpp
CMakeFiles/z21maerklincan.dir/src/trainBoxMaerklin/MaerklinCanInterfaceObserver.cpp.o: CMakeFiles/z21maerklincan.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/marcel/Dokumente/Entwicklung/Eisenbahn/Rocrail/MaerklinCan/z21MaerklinCanLinux/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building CXX object CMakeFiles/z21maerklincan.dir/src/trainBoxMaerklin/MaerklinCanInterfaceObserver.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/z21maerklincan.dir/src/trainBoxMaerklin/MaerklinCanInterfaceObserver.cpp.o -MF CMakeFiles/z21maerklincan.dir/src/trainBoxMaerklin/MaerklinCanInterfaceObserver.cpp.o.d -o CMakeFiles/z21maerklincan.dir/src/trainBoxMaerklin/MaerklinCanInterfaceObserver.cpp.o -c /home/marcel/Dokumente/Entwicklung/Eisenbahn/Rocrail/MaerklinCan/z21MaerklinCanLinux/src/trainBoxMaerklin/MaerklinCanInterfaceObserver.cpp

CMakeFiles/z21maerklincan.dir/src/trainBoxMaerklin/MaerklinCanInterfaceObserver.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/z21maerklincan.dir/src/trainBoxMaerklin/MaerklinCanInterfaceObserver.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/marcel/Dokumente/Entwicklung/Eisenbahn/Rocrail/MaerklinCan/z21MaerklinCanLinux/src/trainBoxMaerklin/MaerklinCanInterfaceObserver.cpp > CMakeFiles/z21maerklincan.dir/src/trainBoxMaerklin/MaerklinCanInterfaceObserver.cpp.i

CMakeFiles/z21maerklincan.dir/src/trainBoxMaerklin/MaerklinCanInterfaceObserver.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/z21maerklincan.dir/src/trainBoxMaerklin/MaerklinCanInterfaceObserver.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/marcel/Dokumente/Entwicklung/Eisenbahn/Rocrail/MaerklinCan/z21MaerklinCanLinux/src/trainBoxMaerklin/MaerklinCanInterfaceObserver.cpp -o CMakeFiles/z21maerklincan.dir/src/trainBoxMaerklin/MaerklinCanInterfaceObserver.cpp.s

CMakeFiles/z21maerklincan.dir/src/trainBoxMaerklin/MaerklinConfigDataStream.cpp.o: CMakeFiles/z21maerklincan.dir/flags.make
CMakeFiles/z21maerklincan.dir/src/trainBoxMaerklin/MaerklinConfigDataStream.cpp.o: /home/marcel/Dokumente/Entwicklung/Eisenbahn/Rocrail/MaerklinCan/z21MaerklinCanLinux/src/trainBoxMaerklin/MaerklinConfigDataStream.cpp
CMakeFiles/z21maerklincan.dir/src/trainBoxMaerklin/MaerklinConfigDataStream.cpp.o: CMakeFiles/z21maerklincan.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/marcel/Dokumente/Entwicklung/Eisenbahn/Rocrail/MaerklinCan/z21MaerklinCanLinux/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Building CXX object CMakeFiles/z21maerklincan.dir/src/trainBoxMaerklin/MaerklinConfigDataStream.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/z21maerklincan.dir/src/trainBoxMaerklin/MaerklinConfigDataStream.cpp.o -MF CMakeFiles/z21maerklincan.dir/src/trainBoxMaerklin/MaerklinConfigDataStream.cpp.o.d -o CMakeFiles/z21maerklincan.dir/src/trainBoxMaerklin/MaerklinConfigDataStream.cpp.o -c /home/marcel/Dokumente/Entwicklung/Eisenbahn/Rocrail/MaerklinCan/z21MaerklinCanLinux/src/trainBoxMaerklin/MaerklinConfigDataStream.cpp

CMakeFiles/z21maerklincan.dir/src/trainBoxMaerklin/MaerklinConfigDataStream.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/z21maerklincan.dir/src/trainBoxMaerklin/MaerklinConfigDataStream.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/marcel/Dokumente/Entwicklung/Eisenbahn/Rocrail/MaerklinCan/z21MaerklinCanLinux/src/trainBoxMaerklin/MaerklinConfigDataStream.cpp > CMakeFiles/z21maerklincan.dir/src/trainBoxMaerklin/MaerklinConfigDataStream.cpp.i

CMakeFiles/z21maerklincan.dir/src/trainBoxMaerklin/MaerklinConfigDataStream.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/z21maerklincan.dir/src/trainBoxMaerklin/MaerklinConfigDataStream.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/marcel/Dokumente/Entwicklung/Eisenbahn/Rocrail/MaerklinCan/z21MaerklinCanLinux/src/trainBoxMaerklin/MaerklinConfigDataStream.cpp -o CMakeFiles/z21maerklincan.dir/src/trainBoxMaerklin/MaerklinConfigDataStream.cpp.s

CMakeFiles/z21maerklincan.dir/src/trainBoxMaerklin/MaerklinLocoManagment.cpp.o: CMakeFiles/z21maerklincan.dir/flags.make
CMakeFiles/z21maerklincan.dir/src/trainBoxMaerklin/MaerklinLocoManagment.cpp.o: /home/marcel/Dokumente/Entwicklung/Eisenbahn/Rocrail/MaerklinCan/z21MaerklinCanLinux/src/trainBoxMaerklin/MaerklinLocoManagment.cpp
CMakeFiles/z21maerklincan.dir/src/trainBoxMaerklin/MaerklinLocoManagment.cpp.o: CMakeFiles/z21maerklincan.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/marcel/Dokumente/Entwicklung/Eisenbahn/Rocrail/MaerklinCan/z21MaerklinCanLinux/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_10) "Building CXX object CMakeFiles/z21maerklincan.dir/src/trainBoxMaerklin/MaerklinLocoManagment.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/z21maerklincan.dir/src/trainBoxMaerklin/MaerklinLocoManagment.cpp.o -MF CMakeFiles/z21maerklincan.dir/src/trainBoxMaerklin/MaerklinLocoManagment.cpp.o.d -o CMakeFiles/z21maerklincan.dir/src/trainBoxMaerklin/MaerklinLocoManagment.cpp.o -c /home/marcel/Dokumente/Entwicklung/Eisenbahn/Rocrail/MaerklinCan/z21MaerklinCanLinux/src/trainBoxMaerklin/MaerklinLocoManagment.cpp

CMakeFiles/z21maerklincan.dir/src/trainBoxMaerklin/MaerklinLocoManagment.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/z21maerklincan.dir/src/trainBoxMaerklin/MaerklinLocoManagment.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/marcel/Dokumente/Entwicklung/Eisenbahn/Rocrail/MaerklinCan/z21MaerklinCanLinux/src/trainBoxMaerklin/MaerklinLocoManagment.cpp > CMakeFiles/z21maerklincan.dir/src/trainBoxMaerklin/MaerklinLocoManagment.cpp.i

CMakeFiles/z21maerklincan.dir/src/trainBoxMaerklin/MaerklinLocoManagment.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/z21maerklincan.dir/src/trainBoxMaerklin/MaerklinLocoManagment.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/marcel/Dokumente/Entwicklung/Eisenbahn/Rocrail/MaerklinCan/z21MaerklinCanLinux/src/trainBoxMaerklin/MaerklinLocoManagment.cpp -o CMakeFiles/z21maerklincan.dir/src/trainBoxMaerklin/MaerklinLocoManagment.cpp.s

CMakeFiles/z21maerklincan.dir/src/z21/UdpInterfaceLinux.cpp.o: CMakeFiles/z21maerklincan.dir/flags.make
CMakeFiles/z21maerklincan.dir/src/z21/UdpInterfaceLinux.cpp.o: /home/marcel/Dokumente/Entwicklung/Eisenbahn/Rocrail/MaerklinCan/z21MaerklinCanLinux/src/z21/UdpInterfaceLinux.cpp
CMakeFiles/z21maerklincan.dir/src/z21/UdpInterfaceLinux.cpp.o: CMakeFiles/z21maerklincan.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/marcel/Dokumente/Entwicklung/Eisenbahn/Rocrail/MaerklinCan/z21MaerklinCanLinux/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_11) "Building CXX object CMakeFiles/z21maerklincan.dir/src/z21/UdpInterfaceLinux.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/z21maerklincan.dir/src/z21/UdpInterfaceLinux.cpp.o -MF CMakeFiles/z21maerklincan.dir/src/z21/UdpInterfaceLinux.cpp.o.d -o CMakeFiles/z21maerklincan.dir/src/z21/UdpInterfaceLinux.cpp.o -c /home/marcel/Dokumente/Entwicklung/Eisenbahn/Rocrail/MaerklinCan/z21MaerklinCanLinux/src/z21/UdpInterfaceLinux.cpp

CMakeFiles/z21maerklincan.dir/src/z21/UdpInterfaceLinux.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/z21maerklincan.dir/src/z21/UdpInterfaceLinux.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/marcel/Dokumente/Entwicklung/Eisenbahn/Rocrail/MaerklinCan/z21MaerklinCanLinux/src/z21/UdpInterfaceLinux.cpp > CMakeFiles/z21maerklincan.dir/src/z21/UdpInterfaceLinux.cpp.i

CMakeFiles/z21maerklincan.dir/src/z21/UdpInterfaceLinux.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/z21maerklincan.dir/src/z21/UdpInterfaceLinux.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/marcel/Dokumente/Entwicklung/Eisenbahn/Rocrail/MaerklinCan/z21MaerklinCanLinux/src/z21/UdpInterfaceLinux.cpp -o CMakeFiles/z21maerklincan.dir/src/z21/UdpInterfaceLinux.cpp.s

CMakeFiles/z21maerklincan.dir/src/z21/z21Interface.cpp.o: CMakeFiles/z21maerklincan.dir/flags.make
CMakeFiles/z21maerklincan.dir/src/z21/z21Interface.cpp.o: /home/marcel/Dokumente/Entwicklung/Eisenbahn/Rocrail/MaerklinCan/z21MaerklinCanLinux/src/z21/z21Interface.cpp
CMakeFiles/z21maerklincan.dir/src/z21/z21Interface.cpp.o: CMakeFiles/z21maerklincan.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/marcel/Dokumente/Entwicklung/Eisenbahn/Rocrail/MaerklinCan/z21MaerklinCanLinux/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_12) "Building CXX object CMakeFiles/z21maerklincan.dir/src/z21/z21Interface.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/z21maerklincan.dir/src/z21/z21Interface.cpp.o -MF CMakeFiles/z21maerklincan.dir/src/z21/z21Interface.cpp.o.d -o CMakeFiles/z21maerklincan.dir/src/z21/z21Interface.cpp.o -c /home/marcel/Dokumente/Entwicklung/Eisenbahn/Rocrail/MaerklinCan/z21MaerklinCanLinux/src/z21/z21Interface.cpp

CMakeFiles/z21maerklincan.dir/src/z21/z21Interface.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/z21maerklincan.dir/src/z21/z21Interface.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/marcel/Dokumente/Entwicklung/Eisenbahn/Rocrail/MaerklinCan/z21MaerklinCanLinux/src/z21/z21Interface.cpp > CMakeFiles/z21maerklincan.dir/src/z21/z21Interface.cpp.i

CMakeFiles/z21maerklincan.dir/src/z21/z21Interface.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/z21maerklincan.dir/src/z21/z21Interface.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/marcel/Dokumente/Entwicklung/Eisenbahn/Rocrail/MaerklinCan/z21MaerklinCanLinux/src/z21/z21Interface.cpp -o CMakeFiles/z21maerklincan.dir/src/z21/z21Interface.cpp.s

CMakeFiles/z21maerklincan.dir/src/z21/z21InterfaceObserver.cpp.o: CMakeFiles/z21maerklincan.dir/flags.make
CMakeFiles/z21maerklincan.dir/src/z21/z21InterfaceObserver.cpp.o: /home/marcel/Dokumente/Entwicklung/Eisenbahn/Rocrail/MaerklinCan/z21MaerklinCanLinux/src/z21/z21InterfaceObserver.cpp
CMakeFiles/z21maerklincan.dir/src/z21/z21InterfaceObserver.cpp.o: CMakeFiles/z21maerklincan.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/marcel/Dokumente/Entwicklung/Eisenbahn/Rocrail/MaerklinCan/z21MaerklinCanLinux/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_13) "Building CXX object CMakeFiles/z21maerklincan.dir/src/z21/z21InterfaceObserver.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/z21maerklincan.dir/src/z21/z21InterfaceObserver.cpp.o -MF CMakeFiles/z21maerklincan.dir/src/z21/z21InterfaceObserver.cpp.o.d -o CMakeFiles/z21maerklincan.dir/src/z21/z21InterfaceObserver.cpp.o -c /home/marcel/Dokumente/Entwicklung/Eisenbahn/Rocrail/MaerklinCan/z21MaerklinCanLinux/src/z21/z21InterfaceObserver.cpp

CMakeFiles/z21maerklincan.dir/src/z21/z21InterfaceObserver.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/z21maerklincan.dir/src/z21/z21InterfaceObserver.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/marcel/Dokumente/Entwicklung/Eisenbahn/Rocrail/MaerklinCan/z21MaerklinCanLinux/src/z21/z21InterfaceObserver.cpp > CMakeFiles/z21maerklincan.dir/src/z21/z21InterfaceObserver.cpp.i

CMakeFiles/z21maerklincan.dir/src/z21/z21InterfaceObserver.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/z21maerklincan.dir/src/z21/z21InterfaceObserver.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/marcel/Dokumente/Entwicklung/Eisenbahn/Rocrail/MaerklinCan/z21MaerklinCanLinux/src/z21/z21InterfaceObserver.cpp -o CMakeFiles/z21maerklincan.dir/src/z21/z21InterfaceObserver.cpp.s

# Object files for target z21maerklincan
z21maerklincan_OBJECTS = \
"CMakeFiles/z21maerklincan.dir/src/main.cpp.o" \
"CMakeFiles/z21maerklincan.dir/src/z60.cpp.o" \
"CMakeFiles/z21maerklincan.dir/src/Can2Lan.cpp.o" \
"CMakeFiles/z21maerklincan.dir/src/Cs2DataParser.cpp.o" \
"CMakeFiles/z21maerklincan.dir/src/WebService.cpp.o" \
"CMakeFiles/z21maerklincan.dir/src/trainBoxMaerklin/CanInterfaceLinux.cpp.o" \
"CMakeFiles/z21maerklincan.dir/src/trainBoxMaerklin/MaerklinCanInterface.cpp.o" \
"CMakeFiles/z21maerklincan.dir/src/trainBoxMaerklin/MaerklinCanInterfaceObserver.cpp.o" \
"CMakeFiles/z21maerklincan.dir/src/trainBoxMaerklin/MaerklinConfigDataStream.cpp.o" \
"CMakeFiles/z21maerklincan.dir/src/trainBoxMaerklin/MaerklinLocoManagment.cpp.o" \
"CMakeFiles/z21maerklincan.dir/src/z21/UdpInterfaceLinux.cpp.o" \
"CMakeFiles/z21maerklincan.dir/src/z21/z21Interface.cpp.o" \
"CMakeFiles/z21maerklincan.dir/src/z21/z21InterfaceObserver.cpp.o"

# External object files for target z21maerklincan
z21maerklincan_EXTERNAL_OBJECTS =

z21maerklincan: CMakeFiles/z21maerklincan.dir/src/main.cpp.o
z21maerklincan: CMakeFiles/z21maerklincan.dir/src/z60.cpp.o
z21maerklincan: CMakeFiles/z21maerklincan.dir/src/Can2Lan.cpp.o
z21maerklincan: CMakeFiles/z21maerklincan.dir/src/Cs2DataParser.cpp.o
z21maerklincan: CMakeFiles/z21maerklincan.dir/src/WebService.cpp.o
z21maerklincan: CMakeFiles/z21maerklincan.dir/src/trainBoxMaerklin/CanInterfaceLinux.cpp.o
z21maerklincan: CMakeFiles/z21maerklincan.dir/src/trainBoxMaerklin/MaerklinCanInterface.cpp.o
z21maerklincan: CMakeFiles/z21maerklincan.dir/src/trainBoxMaerklin/MaerklinCanInterfaceObserver.cpp.o
z21maerklincan: CMakeFiles/z21maerklincan.dir/src/trainBoxMaerklin/MaerklinConfigDataStream.cpp.o
z21maerklincan: CMakeFiles/z21maerklincan.dir/src/trainBoxMaerklin/MaerklinLocoManagment.cpp.o
z21maerklincan: CMakeFiles/z21maerklincan.dir/src/z21/UdpInterfaceLinux.cpp.o
z21maerklincan: CMakeFiles/z21maerklincan.dir/src/z21/z21Interface.cpp.o
z21maerklincan: CMakeFiles/z21maerklincan.dir/src/z21/z21InterfaceObserver.cpp.o
z21maerklincan: CMakeFiles/z21maerklincan.dir/build.make
z21maerklincan: CMakeFiles/z21maerklincan.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/home/marcel/Dokumente/Entwicklung/Eisenbahn/Rocrail/MaerklinCan/z21MaerklinCanLinux/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_14) "Linking CXX executable z21maerklincan"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/z21maerklincan.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/z21maerklincan.dir/build: z21maerklincan
.PHONY : CMakeFiles/z21maerklincan.dir/build

CMakeFiles/z21maerklincan.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/z21maerklincan.dir/cmake_clean.cmake
.PHONY : CMakeFiles/z21maerklincan.dir/clean

CMakeFiles/z21maerklincan.dir/depend:
	cd /home/marcel/Dokumente/Entwicklung/Eisenbahn/Rocrail/MaerklinCan/z21MaerklinCanLinux/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/marcel/Dokumente/Entwicklung/Eisenbahn/Rocrail/MaerklinCan/z21MaerklinCanLinux /home/marcel/Dokumente/Entwicklung/Eisenbahn/Rocrail/MaerklinCan/z21MaerklinCanLinux /home/marcel/Dokumente/Entwicklung/Eisenbahn/Rocrail/MaerklinCan/z21MaerklinCanLinux/build /home/marcel/Dokumente/Entwicklung/Eisenbahn/Rocrail/MaerklinCan/z21MaerklinCanLinux/build /home/marcel/Dokumente/Entwicklung/Eisenbahn/Rocrail/MaerklinCan/z21MaerklinCanLinux/build/CMakeFiles/z21maerklincan.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/z21maerklincan.dir/depend


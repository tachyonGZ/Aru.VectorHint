cmake_minimum_required (VERSION 3.19)

project (
	"Aru.VectorHint"
	VERSION 1.0.0
	DESCRIPTION "Aru.VectorHint"
	LANGUAGES CXX
)

set(install_permissions
	OWNER_WRITE OWNER_READ OWNER_EXECUTE
	GROUP_WRITE GROUP_READ GROUP_EXECUTE
	WORLD_WRITE WORLD_READ WORLD_EXECUTE
)

### /path/to/ server sourcemod directory
cmake_path(SET install_path NORMALIZE "/path/to/.../addons/sourcemod")

MESSAGE(CHECK_START "Searching for SP compiler")
if(EXISTS ${install_path}/scripting/spcomp)
	set(SP_COMPILER "${install_path}/scripting/spcomp")
	MESSAGE(CHECK_PASS "found at: ${SP_COMPILER}")
elseif(EXISTS ${install_path}/scripting/spcomp64)
	set(SP_COMPILER "${install_path}/scripting/spcomp64")
	MESSAGE(CHECK_PASS "found at: ${SP_COMPILER}")
else()
	set(SP_COMPILER "")
	MESSAGE(CHECK_FAIL "couldn't find SourcePawn compiler at ${install_path}/scripting/. Not compiling plugins")
endif()

### Finding the SourceMod SDK and any game SDKs on the WSL
get_filename_component(build_root ".." ABSOLUTE)

# git clone -b 1.12-dev https://github.com/alliedmodders/sourcemod.git sourcemod-1.12-dev
# Can be a symlink to your Window's drive system but IntelliSense won't figure it out
if(IS_DIRECTORY ${build_root}/sourcemod-1.12-dev)
	set(SM "${build_root}/sourcemod-1.12-dev")
	MESSAGE(STATUS "Found SourceMod directory at ${SM}")
else()
	MESSAGE(FATAL_ERROR "Couldn't find SourceMod SDK at ")
endif()

if(IS_DIRECTORY ${build_root}/hl2sdk)
	set (HL2SDK "${build_root}/hl2sdk")
	MESSAGE(STATUS "Found HL2SDK directory at ${HL2SDK}")
elseif()
	MESSAGE(FATAL_ERROR "Couldn't find hl2sdk at ")
endif()

# git clone -b 1.12-dev https://github.com/alliedmodders/sourcepawn.git sourcepawn-1.12-dev
if(IS_DIRECTORY ${build_root}/sourcepawn-1.12-dev)
	set(SOURCEPAWN_SDK "${build_root}/sourcepawn-1.12-dev")
	MESSAGE(STATUS "Found sourcepawn directory at ${SOURCEPAWN_SDK}")
elseif()
	MESSAGE(FATAL_ERROR "Couldn't find sourcepawn at ")
endif()

if(IS_DIRECTORY ${build_root}/amtl-master)
	set(AMTL_SDK "${build_root}/amtl-master")
	MESSAGE(STATUS "Found amtl directory at ${SOURCEPAWN_SDK}")
elseif()
	MESSAGE(FATAL_ERROR "Couldn't find amtl at ")
endif()

##################################################################

### Include sub-projects.
add_subdirectory("extensions")
if(EXISTS ${SP_COMPILER})
	add_subdirectory("scripting")
endif()

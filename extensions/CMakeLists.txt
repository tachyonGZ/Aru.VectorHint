add_library(
	extension 
	SHARED
	"extension.cpp"
	"${SM}/public/smsdk_ext.cpp"
	"VectorHint.cpp"
)

set_target_properties(extension PROPERTIES LIBRARY_OUTPUT_NAME "${CMAKE_PROJECT_NAME}.ext")
set_target_properties(extension PROPERTIES CXX_STANDARD 20)

target_compile_options(extension PUBLIC $<$<PLATFORM_ID:Linux>:-m32>)
target_link_options(extension PUBLIC $<$<PLATFORM_ID:Linux>:-m32>)

if (UNIX)
	target_compile_definitions(extension
		PRIVATE $<$<COMPILE_LANGUAGE:CXX>: 
					GNUC
					-D_LINUX
					-DPOSIX
					-Dstricmp=strcasecmp 
					-D_stricmp=strcasecmp
					-D_snprintf=snprintf
					-D_vsnprintf=vsnprintf
					-DHAVE_STDINT_H
					$<$<CONFIG:Debug>: 
						-DDEBUG 
					>
					$<$<CONFIG:Release>: 
						-DNDEBUG 
					>
				>
	)
elseif (WIN32)
	target_compile_definitions(extension
	PRIVATE $<$<COMPILE_LANGUAGE:CXX>: 
				GNUC
				-D_LINUX
				-DPOSIX
				-DHAVE_STDINT_H
				-D_CRT_SECURE_NO_WARNINGS
				$<$<CONFIG:Debug>: 
					-DDEBUG 
				>
				$<$<CONFIG:Release>: 
					-DNDEBUG 
				>
			>
)
else()
	message(FATAL_ERROR "unknown")
endif()
#[[
target_compile_options(extension 
	PRIVATE $<$<COMPILE_LANGUAGE:CXX>: 
				-std=c++14 -fpic -m32 -fexceptions -fno-threadsafe-statics 
				-Wno-overloaded-virtual -fvisibility-inlines-hidden
				-Wno-non-virtual-dtor -Wno-delete-non-virtual-dtor
				$<$<CONFIG:Debug>: 
					-Wall -Wextra -pedantic -g -Og -ggdb 
				>
				$<$<CONFIG:Release>: 
					-s -O3 
				> 
			>
)
]]

target_link_libraries(
	extension 
	PRIVATE
	-static-libgcc
	-static-libstdc++
)

target_include_directories(
	extension 
	PUBLIC  
	"${SM}/public" 
	"${SM}/public/extensions"
	"${SOURCEPAWN_SDK}/include"
	"${AMTL_SDK}"
	"${AMTL_SDK}/amtl"
	"." 
	".."
)

### To install the extension, click "Build > Install {projectname}"
#[[
if(IS_DIRECTORY ${install_path}/extensions)
	install(TARGETS 
				extension
			LIBRARY
				DESTINATION ${install_path}/extensions
				PERMISSIONS ${install_permissions}
	)
	MESSAGE(STATUS "Using install dir ${install_path}/extensions")
else()
	MESSAGE(SEND_ERROR "Can't install extension in ${install_path}/extensions")
endif()
]]
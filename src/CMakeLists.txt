find_package(OpenMP REQUIRED)
set(CMAKE_CXX_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_CXX_FLAGS}")
#http://www.bineteri.com/qtwithcmake
# Don't forget to include output directory, otherwise
# the UI file won't be wrapped!
include_directories(${CMAKE_CURRENT_BINARY_DIR})

# Add current directory to the nvcc include line.
CONFIGURE_FILE(
	"${PROJECT_SOURCE_DIR}/src_path.h.in"
	"${PROJECT_SOURCE_DIR}/src/src_path.h"
)

CONFIGURE_FILE(
	"${PROJECT_SOURCE_DIR}/dataset_path.h.in"
	"${PROJECT_SOURCE_DIR}/src/dataset_path.h"
)


#for non-fermi cards
#set(CUDA_NVCC_FLAGS_DEBUG "-arch;sm_11")
#set(CUDA_NVCC_FLAGS "-arch;sm_13;-Xptxas;-O1")
#speed up with a better reg count
#set(CUDA_NVCC_FLAGS "-arch;sm_20;--ptxas-options=-v;--maxrregcount=32;-Xptxas;-O")
#http://forums.nvidia.com/index.php?showtopic=213695
#compiler might be too aggressive
set(CUDA_NVCC_FLAGS "-arch;sm_21")
#for kepler
#set(CUDA_NVCC_FLAGS "-arch;sm_35")
add_definitions(-DKEPLER=1)

INCLUDE_DIRECTORIES(
	"/usr/local/include"
	"/usr/include"
	"${PROJECT_SOURCE_DIR}/../tools/source"
	"${PROJECT_SOURCE_DIR}/../tools/math"
        "${PROJECT_SOURCE_DIR}/../tools/cudaTools/src"

	 ${QT_INCLUDE_DIR}
        ${CUDA_SDK_ROOT_DIR}/common/inc
        ${CUDA_TOOLKIT_ROOT_DIR}/include
)
if(WIN32)
                SET(CUTIL_LIB_DIRECTORY
                        "${CUDA_SDK_ROOT_DIR}/common/lib/"
                )
else(WIN32)
                SET(CUTIL_LIB_DIRECTORY
                        "${CUDA_SDK_ROOT_DIR}/C/lib/"
                )
endif(WIN32)

LINK_DIRECTORIES(
	"/usr/lib"
	"/usr/local/lib"
	"${PROJECT_SOURCE_DIR}/../lib"
        ${CUTIL_LIB_DIRECTORY}
)

##############################################################################
# Use one executable only.
ADD_LIBRARY(bh_viewer
DriverBH.cpp
BarnesHut.cpp
BHNode.cpp
BBox.cpp
  )
  
 #TARGET_LINK_LIBRARIES(bh_viewer)
 
 IF(WIN32)
		ADD_CUSTOM_COMMAND(
				TARGET particle_lattice
				POST_BUILD
				COMMAND ${CMAKE_COMMAND} -E copy $(ConfigurationName)/particle_lattice.lib ${PROJECT_SOURCE_DIR}/../lib/cudaimplicitsurface.lib
		)
ELSE(WIN32)
		ADD_CUSTOM_COMMAND(
				TARGET particle_lattice
				POST_BUILD
				#for some reason changes to "source" directory
				COMMAND ${CMAKE_COMMAND} -E copy libparticle_lattice.a ${PROJECT_SOURCE_DIR}/../lib/libparticle_lattice.a
		)
ENDIF(WIN32)

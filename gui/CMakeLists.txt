FIND_PACKAGE(Qt4 REQUIRED)
SET(QT_USE_QTOPENGL 1)
INCLUDE(${QT_USE_FILE})
add_definitions(-DGLEW_STATIC -DFREEGLUT_STATIC)

QT_WRAP_CPP(Sculptor
MOC_FILES
QtSculptorWidget.h
SculptorWindow.h
)

QT4_WRAP_UI(
UI_HEADERS
mainwindow.ui
)

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

FIND_PACKAGE(OpenGL)

IF(OPENGL_FOUND)
	SET(GL_LIB ${OPENGL_LIBRARIES})
ELSE(OPENGL_FOUND)
	MESSAGE("Couldn't find OpenGL")
ENDIF(OPENGL_FOUND)

find_package(Threads)
if (Threads_FOUND)
ELSE(Threads_FOUND)
	MESSAGE("Threads not found.")
ENDIF(Threads_FOUND)
FIND_PACKAGE(GLUT)
FIND_PACKAGE(GLU)

#for non-fermi cards
#set(CUDA_NVCC_FLAGS_DEBUG "-arch;sm_11")
#set(CUDA_NVCC_FLAGS "-arch;sm_13;-Xptxas;-O1")
#speed up with a better reg count
#set(CUDA_NVCC_FLAGS "-arch;sm_20;--ptxas-options=-v;--maxrregcount=32;-Xptxas;-O")
#http://forums.nvidia.com/index.php?showtopic=213695
#compiler might be too aggressive
set(CUDA_NVCC_FLAGS "-arch;sm_21;--ptxas-options=-v;-Xptxas;-O3")
#for kepler
#set(CUDA_NVCC_FLAGS "-arch;sm_35")
add_definitions(-DKEPLER=1)

INCLUDE_DIRECTORIES(
	"/usr/local/include"
	"/usr/include"
	"${PROJECT_SOURCE_DIR}/../tools/source"
	"${PROJECT_SOURCE_DIR}/../tools/math"
        "${PROJECT_SOURCE_DIR}/../tools/cudaTools/src"
	"${PROJECT_SOURCE_DIR}/../tools/camera"
	"${PROJECT_SOURCE_DIR}/../tools/renderer"
	"${PROJECT_SOURCE_DIR}/../marching_cubes/src/"
	"${PROJECT_SOURCE_DIR}/../tools/glew/include"
	"${PROJECT_SOURCE_DIR}/../tools/freeglut"
	"${PROJECT_SOURCE_DIR}/src/"
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
CUDA_ADD_EXECUTABLE(gui_pl
  main.cc
  QtSculptorWidget.cpp
	SculptorWidget.cpp
  SculptorWindow.cpp
drawbh.cpp
  ${MOC_FILES}
  ${UI_HEADERS}
)
  
 TARGET_LINK_LIBRARIES(gui_pl
 tools
camera
renderer
gomp
cudaError
bh_viewer

boost_thread
boost_system
freeglut_static
 ${QT_LIBRARIES}
 ${OPENGL_LIBRARIES} 
${GLUT_LIBRARIES}
glew
 ${CMAKE_THREAD_LIBS_INIT} 
boost_thread
)
 

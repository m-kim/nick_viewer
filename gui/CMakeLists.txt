FIND_PACKAGE(Qt4 REQUIRED)
SET(QT_USE_QTOPENGL 1)
INCLUDE(${QT_USE_FILE})

QT_WRAP_CPP(Sculptor
MOC_FILES
QtSculptorWidget.h
SculptorWindow.h
)

QT4_WRAP_UI(
UI_HEADERS
mainwindow.ui
)

#http://www.bineteri.com/qtwithcmake
# Don't forget to include output directory, otherwise
# the UI file won't be wrapped!
include_directories(${CMAKE_CURRENT_BINARY_DIR})

FIND_PACKAGE(OpenGL)

IF(OPENGL_FOUND)
	SET(GL_LIB ${OPENGL_LIBRARIES})
ELSE(OPENGL_FOUND)
	MESSAGE("Couldn't find OpenGL")
ENDIF(OPENGL_FOUND)


INCLUDE_DIRECTORIES(
	"/usr/local/include"
	"/usr/include"
     ${QT_INCLUDE_DIR}
)

LINK_DIRECTORIES(
	"/usr/lib"
	"/usr/local/lib"
	"${PROJECT_SOURCE_DIR}/../lib"
        ${CUTIL_LIB_DIRECTORY}
)

##############################################################################
# Use one executable only.
ADD_EXECUTABLE(gui_pl
  main.cc
  QtSculptorWidget.cpp
	SculptorWidget.cpp
  SculptorWindow.cpp
  ${MOC_FILES}
  ${UI_HEADERS}
)
  
 TARGET_LINK_LIBRARIES(gui_pl
 ${QT_LIBRARIES}
 ${OPENGL_LIBRARIES} 
 ${CMAKE_THREAD_LIBS_INIT} 
)
 

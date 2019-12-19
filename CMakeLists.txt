    CMAKE_MINIMUM_REQUIRED(VERSION 2.4)

PROJECT(BHViewer)
FIND_PACKAGE(CUDA REQUIRED)
if (CUDA_SDK_ROOT_DIR MATCHES "CUDA_SDK_ROOT_DIR-NOTFOUND")
        IF(WIN32)
                # Look for the SDK stuff
                find_path(CUDA_SDK_ROOT_DIR C/common/inc/cutil.h
                  "$ENV{NVSDKCUDA_ROOT}"
                  "[HKEY_LOCAL_MACHINE\\SOFTWARE\\NVIDIA Corporation\\Installed Products\\NVIDIA SDK 10\\Compute;InstallDir]"
                "/Developer/GPU\ Computing/C"
                )

                # Keep the CUDA_SDK_ROOT_DIR first in order to be able to override the
                # environment variables.
                set(CUDA_SDK_SEARCH_PATH
                  "${CUDA_SDK_ROOT_DIR}"
                  "${CUDA_TOOLKIT_ROOT_DIR}/local/NVSDK0.2"
                  "${CUDA_TOOLKIT_ROOT_DIR}/NVSDK0.2"
                  "${CUDA_TOOLKIT_ROOT_DIR}/NV_CUDA_SDK"
                  "$ENV{HOME}/NVIDIA_CUDA_SDK"
                  "$ENV{HOME}/NVIDIA_CUDA_SDK_MACOSX"
                  "/Developer/CUDA"
                )

        ELSE(WIN32)
                find_path(CUDA_SDK_ROOT_DIR C/common/inc/cutil.h
                                $ENV{NVSDKCUDA_ROOT}
                                ~/NVIDIA_GPU_Computing_SDK
                )
                SET(CUDA_SDK_SEARCH_PATH
                        "${CUDA_SDK_ROOT_DIR}"
                        "~/NVIDIA_GPU_Computing_SDK"
                )
        ENDIF(WIN32)

 endif (CUDA_SDK_ROOT_DIR MATCHES "CUDA_SDK_ROOT_DIR-NOTFOUND")
SUBDIRS(
	src
        #cli
	gui
  )

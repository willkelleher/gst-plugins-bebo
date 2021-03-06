
PROJECT(libgstbebo)

SET_PROPERTY(
  DIRECTORY
  APPEND PROPERTY COMPILE_DEFINITIONS
  HAVE_CONFIG_H
)

INCLUDE_DIRECTORIES(
  ${CMAKE_SOURCE_DIR}
  ${PROJECT_SOURCE_DIR}/../../win32/common
  ${GST_INSTALL_BASE}/include
  ${GST_INSTALL_BASE}/include/gstreamer-1.0
  ${GST_INSTALL_BASE}/include/glib-2.0
  ${GST_INSTALL_BASE}/lib/glib-2.0/include
  ${GST_INSTALL_BASE}/lib/gstreamer-1.0/include
  ${CMAKE_SOURCE_DIR}/gst-libs/gst/dxgi/
  ${CMAKE_SOURCE_DIR}/gst-libs/gst
  ${CMAKE_SOURCE_DIR}/gst
  ${CMAKE_SOURCE_DIR}/shared
  ${CMAKE_SOURCE_DIR}/third_party/speexdsp/include
  ${NVENC_SDK_BASE}/Video_Codec_SDK_7.1.9/Samples/Common/inc
  ${CUDA_PATH}
)

LINK_DIRECTORIES(
  "C:/Program Files (x86)/Windows Kits/10/Lib/10.0.15063.0/um/x64"
  ${GST_INSTALL_BASE}/lib
  ${GST_INSTALL_BASE}/lib/gstreamer-1.0
  ${CMAKE_SOURCE_DIR}/third_party/speexdsp/lib
)

set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MT /Zi")
set(CMAKE_SHARED_LINKER_FLAGS_RELEASE "${CMAKE_SHARED_LINKER_FLAGS_RELEASE} /DEBUG:FULL /OPT:REF /OPT:ICF")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /MTd")

SET(shared_SOURCES
  ${CMAKE_SOURCE_DIR}/gst-libs/gst/dxgi/gstdxgimemory.c
  ${CMAKE_SOURCE_DIR}/gst-libs/gst/dxgi/gstdxgidevice.c
)

SET(shared_HEADERS
  ${CMAKE_SOURCE_DIR}/shared/bebo_shmem.h
  ${CMAKE_SOURCE_DIR}/shared/config.h
  ${CMAKE_SOURCE_DIR}/gst-libs/gst/dxgi/gstdxgidevice.h
  ${CMAKE_SOURCE_DIR}/gst-libs/gst/dxgi/gstdxgimemory.h
)

SET(nvenc_SOURCES
  nvenc/gstnvbaseenc.c
  nvenc/gstnvenc.c
  nvenc/gstnvh264enc.c
)

SET(nvenc_HEADERS
  nvenc/gstnvbaseenc.h
  nvenc/gstnvenc.h
  nvenc/gstnvh264enc.h
)

SET(gstdshowsink_SOURCES
  dshowfiltersink/gstdshowsink.c
)

SET(gstdshowsink_HEADERS
  dshowfiltersink/gstdshowsink.h
)

SET(gl2dxgi_SOURCES
  gl2dxgi/gstgl2dxgi.c
)

SET(gl2dxgi_HEADERS
  gl2dxgi/gstgl2dxgi.h
)

SET(buffer_holder_FILES
  bufferholder/gstbufferholder.c
  bufferholder/gstbufferholder.h
)

SET(noisegate_FILES
  noisegate/gstaudionoisegate.c
  noisegate/gstaudionoisegate.h
)

SET(noisesuppression_FILES
  noisesuppression/gstaudionoisesuppression.c
  noisesuppression/gstaudionoisesuppression.h
)


source_group("nvenc" FILES ${nvenc_SOURCES} ${nvenc_HEADERS})
source_group("gstdshowsink" FILES ${gstdshowsink_SOURCES} ${gstdshowsink_HEADERS})
source_group("gl2dxgi" FILES ${gl2dxgi_SOURCES} ${gl2dxgi_HEADERS})
source_group("shared" FILES ${shared_SOURCES} ${shared_HEADERS})
source_group("plugin_init" FILES gstbeboplugin.c)
source_group("bufferholder" FILES ${buffer_holder_FILES})
source_group("noisegate" FILES ${noisegate_FILES})
source_group("noisesuppression" FILES ${noisesuppression_FILES})

ADD_LIBRARY(libgstbebo SHARED
  gstbeboplugin.c
  ${shared_SOURCES}
  ${shared_HEADERS}
  ${nvenc_SOURCES}
  ${nvenc_HEADERS}
  ${gstdshowsink_SOURCES}
  ${gstdshowsink_HEADERS}
  ${gl2dxgi_SOURCES}
  ${gl2dxgi_HEADERS}
  ${buffer_holder_FILES}
  ${noisegate_FILES}
  ${noisesuppression_FILES}
)

TARGET_LINK_LIBRARIES(libgstbebo
  gstreamer-1.0
  gstaudio-1.0
  gstvideo-1.0
  gstbase-1.0
  gstgl-1.0
  glib-2.0
  gobject-2.0
  rpcrt4
  uuid
  winmm
  D3D11
  opengl32
  gstallocators-1.0
  gstbadvideo-1.0
  gstpbutils-1.0
  gstcontroller-1.0
  libspeexdsp
)


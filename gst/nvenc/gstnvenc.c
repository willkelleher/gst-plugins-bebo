/* GStreamer NVENC plugin
 * Copyright (C) 2015 Centricular Ltd
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public
 * License along with this library; if not, write to the
 * Free Software Foundation, Inc., 51 Franklin St, Fifth Floor,
 * Boston, MA 02110-1301, USA.
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "gstnvenc.h"
#include "gstnvh264enc.h"
#include "dshowfiltersink/gstdshowsink.h"
GST_DEBUG_CATEGORY (gst_nvenc_debug);

static NV_ENCODE_API_FUNCTION_LIST nvenc_api;

NVENCSTATUS
NvEncOpenEncodeSessionEx (NV_ENC_OPEN_ENCODE_SESSION_EX_PARAMS * params,
    void **encoder)
{
  g_assert (nvenc_api.nvEncOpenEncodeSessionEx != NULL);
  return nvenc_api.nvEncOpenEncodeSessionEx (params, encoder);
}

NVENCSTATUS
NvEncDestroyEncoder (void *encoder)
{
  g_assert (nvenc_api.nvEncDestroyEncoder != NULL);
  return nvenc_api.nvEncDestroyEncoder (encoder);
}

NVENCSTATUS
NvEncGetEncodeGUIDs (void *encoder, GUID * array, uint32_t array_size,
    uint32_t * count)
{
  g_assert (nvenc_api.nvEncGetEncodeGUIDs != NULL);
  return nvenc_api.nvEncGetEncodeGUIDs (encoder, array, array_size, count);
}

NVENCSTATUS
NvEncGetEncodeProfileGUIDCount (void *encoder, GUID encodeGUID,
    uint32_t * encodeProfileGUIDCount)
{
  g_assert (nvenc_api.nvEncGetEncodeProfileGUIDCount != NULL);
  return nvenc_api.nvEncGetEncodeProfileGUIDCount (encoder, encodeGUID,
      encodeProfileGUIDCount);
}

NVENCSTATUS
NvEncGetEncodeProfileGUIDs (void *encoder, GUID encodeGUID,
    GUID * profileGUIDs, uint32_t guidArraySize, uint32_t * GUIDCount)
{
  g_assert (nvenc_api.nvEncGetEncodeProfileGUIDs != NULL);
  return nvenc_api.nvEncGetEncodeProfileGUIDs (encoder, encodeGUID,
      profileGUIDs, guidArraySize, GUIDCount);
}

NVENCSTATUS
NvEncGetInputFormats (void *encoder, GUID enc_guid,
    NV_ENC_BUFFER_FORMAT * array, uint32_t size, uint32_t * num)
{
  g_assert (nvenc_api.nvEncGetInputFormats != NULL);
  return nvenc_api.nvEncGetInputFormats (encoder, enc_guid, array, size, num);
}

NVENCSTATUS
NvEncGetEncodePresetCount (void *encoder, GUID encodeGUID,
    uint32_t * encodePresetGUIDCount)
{
  g_assert (nvenc_api.nvEncGetEncodeProfileGUIDCount != NULL);
  return nvenc_api.nvEncGetEncodePresetCount (encoder, encodeGUID,
      encodePresetGUIDCount);
}

NVENCSTATUS
NvEncGetEncodePresetGUIDs (void *encoder, GUID encodeGUID,
    GUID * presetGUIDs, uint32_t guidArraySize, uint32_t * GUIDCount)
{
  g_assert (nvenc_api.nvEncGetEncodeProfileGUIDs != NULL);
  return nvenc_api.nvEncGetEncodePresetGUIDs (encoder, encodeGUID,
      presetGUIDs, guidArraySize, GUIDCount);
}

NVENCSTATUS
NvEncGetEncodePresetConfig (void *encoder, GUID encodeGUID,
    GUID presetGUID, NV_ENC_PRESET_CONFIG * presetConfig)
{
  g_assert (nvenc_api.nvEncGetEncodePresetConfig != NULL);
  return nvenc_api.nvEncGetEncodePresetConfig (encoder, encodeGUID, presetGUID,
      presetConfig);
}

NVENCSTATUS
NvEncGetEncodeCaps (void *encoder, GUID encodeGUID,
    NV_ENC_CAPS_PARAM * capsParam, int *capsVal)
{
  g_assert (nvenc_api.nvEncGetEncodeCaps != NULL);
  return nvenc_api.nvEncGetEncodeCaps (encoder, encodeGUID, capsParam, capsVal);
}

NVENCSTATUS
NvEncGetSequenceParams (void *encoder,
    NV_ENC_SEQUENCE_PARAM_PAYLOAD * sequenceParamPayload)
{
  g_assert (nvenc_api.nvEncGetSequenceParams != NULL);
  return nvenc_api.nvEncGetSequenceParams (encoder, sequenceParamPayload);
}

NVENCSTATUS
NvEncInitializeEncoder (void *encoder, NV_ENC_INITIALIZE_PARAMS * params)
{
  g_assert (nvenc_api.nvEncInitializeEncoder != NULL);
  return nvenc_api.nvEncInitializeEncoder (encoder, params);
}

NVENCSTATUS
NvEncReconfigureEncoder (void *encoder, NV_ENC_RECONFIGURE_PARAMS * params)
{
  g_assert (nvenc_api.nvEncReconfigureEncoder != NULL);
  return nvenc_api.nvEncReconfigureEncoder (encoder, params);
}

NVENCSTATUS
NvEncRegisterResource (void *encoder, NV_ENC_REGISTER_RESOURCE * params)
{
  g_assert (nvenc_api.nvEncRegisterResource != NULL);
  return nvenc_api.nvEncRegisterResource (encoder, params);
}

NVENCSTATUS
NvEncUnregisterResource (void *encoder, NV_ENC_REGISTERED_PTR resource)
{
  g_assert (nvenc_api.nvEncUnregisterResource != NULL);
  return nvenc_api.nvEncUnregisterResource (encoder, resource);
}

NVENCSTATUS
NvEncMapInputResource (void *encoder, NV_ENC_MAP_INPUT_RESOURCE * params)
{
  g_assert (nvenc_api.nvEncMapInputResource != NULL);
  return nvenc_api.nvEncMapInputResource (encoder, params);
}

NVENCSTATUS
NvEncUnmapInputResource (void *encoder, NV_ENC_INPUT_PTR input_buffer)
{
  g_assert (nvenc_api.nvEncUnmapInputResource != NULL);
  return nvenc_api.nvEncUnmapInputResource (encoder, input_buffer);
}

NVENCSTATUS
NvEncCreateInputBuffer (void *encoder, NV_ENC_CREATE_INPUT_BUFFER * input_buf)
{
  g_assert (nvenc_api.nvEncCreateInputBuffer != NULL);
  return nvenc_api.nvEncCreateInputBuffer (encoder, input_buf);
}

NVENCSTATUS
NvEncLockInputBuffer (void *encoder, NV_ENC_LOCK_INPUT_BUFFER * input_buf)
{
  g_assert (nvenc_api.nvEncLockInputBuffer != NULL);
  return nvenc_api.nvEncLockInputBuffer (encoder, input_buf);
}

NVENCSTATUS
NvEncUnlockInputBuffer (void *encoder, NV_ENC_INPUT_PTR input_buf)
{
  g_assert (nvenc_api.nvEncUnlockInputBuffer != NULL);
  return nvenc_api.nvEncUnlockInputBuffer (encoder, input_buf);
}

NVENCSTATUS
NvEncDestroyInputBuffer (void *encoder, NV_ENC_INPUT_PTR input_buf)
{
  g_assert (nvenc_api.nvEncDestroyInputBuffer != NULL);
  return nvenc_api.nvEncDestroyInputBuffer (encoder, input_buf);
}

NVENCSTATUS
NvEncCreateBitstreamBuffer (void *encoder, NV_ENC_CREATE_BITSTREAM_BUFFER * bb)
{
  g_assert (nvenc_api.nvEncCreateBitstreamBuffer != NULL);
  return nvenc_api.nvEncCreateBitstreamBuffer (encoder, bb);
}

NVENCSTATUS
NvEncLockBitstream (void *encoder, NV_ENC_LOCK_BITSTREAM * lock_bs)
{
  g_assert (nvenc_api.nvEncLockBitstream != NULL);
  return nvenc_api.nvEncLockBitstream (encoder, lock_bs);
}

NVENCSTATUS
NvEncUnlockBitstream (void *encoder, NV_ENC_OUTPUT_PTR bb)
{
  g_assert (nvenc_api.nvEncUnlockBitstream != NULL);
  return nvenc_api.nvEncUnlockBitstream (encoder, bb);
}

NVENCSTATUS
NvEncDestroyBitstreamBuffer (void *encoder, NV_ENC_OUTPUT_PTR bit_buf)
{
  g_assert (nvenc_api.nvEncDestroyBitstreamBuffer != NULL);
  return nvenc_api.nvEncDestroyBitstreamBuffer (encoder, bit_buf);
}

NVENCSTATUS
NvEncEncodePicture (void *encoder, NV_ENC_PIC_PARAMS * pic_params)
{
  g_assert (nvenc_api.nvEncEncodePicture != NULL);
  return nvenc_api.nvEncEncodePicture (encoder, pic_params);
}

gboolean
gst_nvenc_cmp_guid (GUID g1, GUID g2)
{
  return (g1.Data1 == g2.Data1 && g1.Data2 == g2.Data2 && g1.Data3 == g2.Data3
      && g1.Data4[0] == g2.Data4[0] && g1.Data4[1] == g2.Data4[1]
      && g1.Data4[2] == g2.Data4[2] && g1.Data4[3] == g2.Data4[3]
      && g1.Data4[4] == g2.Data4[4] && g1.Data4[5] == g2.Data4[5]
      && g1.Data4[6] == g2.Data4[6] && g1.Data4[7] == g2.Data4[7]);
}

NV_ENC_BUFFER_FORMAT
gst_nvenc_get_nv_buffer_format (GstVideoFormat fmt)
{
  switch (fmt) {
    case GST_VIDEO_FORMAT_NV12:
      return NV_ENC_BUFFER_FORMAT_NV12_PL;
    case GST_VIDEO_FORMAT_YV12:
      return NV_ENC_BUFFER_FORMAT_YV12_PL;
    case GST_VIDEO_FORMAT_I420:
      return NV_ENC_BUFFER_FORMAT_IYUV_PL;
    case GST_VIDEO_FORMAT_Y444:
      return NV_ENC_BUFFER_FORMAT_YUV444_PL;
    case GST_VIDEO_FORMAT_RGBA:
      return NV_ENC_BUFFER_FORMAT_ABGR;
    default:
      break;
  }
  return NV_ENC_BUFFER_FORMAT_UNDEFINED;
}

typedef NVENCSTATUS(NVENCAPI* PNVENCODEAPICREATEINSTANCE)(NV_ENCODE_API_FUNCTION_LIST *functionList);

gboolean load_nvenc_dlls()
{
  GST_DEBUG_CATEGORY_INIT (gst_nvenc_debug, "nvenc", 0, "Nvidia NVENC encoder");

  // ROWAN LOAD DLL
  HINSTANCE hDLL = LoadLibraryA("nvEncodeAPI64.dll");
  #if HAVE_NVENC_GST_GL
  GST_INFO("GL memory is enabled although it migt not be used");
  #endif
  if (hDLL == NULL) {

      GST_ERROR("Failed to load nvEncodeAPI.dll");
      return FALSE;
  }
  PNVENCODEAPICREATEINSTANCE nvEncodeAPICreateInstance =
      (PNVENCODEAPICREATEINSTANCE)GetProcAddress(hDLL, "NvEncodeAPICreateInstance");
  if (nvEncodeAPICreateInstance == NULL) {
      GST_ERROR("Failed to load nvEncodeAPICreateInstance.");
      return FALSE;
  }
  nvenc_api.version = NV_ENCODE_API_FUNCTION_LIST_VER;
  if (nvEncodeAPICreateInstance(&nvenc_api) != NV_ENC_SUCCESS) {
    GST_ERROR("Failed to get NVEncodeAPI function table!");
    return FALSE;
  } else {
    GST_INFO("Created NVEncodeAPI instance, got function table");
    return TRUE;
  } 
}

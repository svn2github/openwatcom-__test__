/***************************************************************************
*
*                            Open Watcom Project
*
*  Copyright (c) 2004-2008 The Open Watcom Contributors. All Rights Reserved.
*
*  ========================================================================
*
*    This file contains Original Code and/or Modifications of Original
*    Code as defined in and that are subject to the Sybase Open Watcom
*    Public License version 1.0 (the 'License'). You may not use this file
*    except in compliance with the License. BY USING THIS FILE YOU AGREE TO
*    ALL TERMS AND CONDITIONS OF THE LICENSE. A copy of the License is
*    provided with the Original Code and Modifications, and is also
*    available at www.sybase.com/developer/opensource.
*
*    The Original Code and all software distributed under the License are
*    distributed on an 'AS IS' basis, WITHOUT WARRANTY OF ANY KIND, EITHER
*    EXPRESS OR IMPLIED, AND SYBASE AND ALL CONTRIBUTORS HEREBY DISCLAIM
*    ALL SUCH WARRANTIES, INCLUDING WITHOUT LIMITATION, ANY WARRANTIES OF
*    MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE, QUIET ENJOYMENT OR
*    NON-INFRINGEMENT. Please see the License for the specific language
*    governing rights and limitations under the License.
*
*  ========================================================================
*
*  Description: Implementation of the dxguid.lib library.
*
**************************************************************************/

#include <windows.h>

/* d3d.h */
EXTERN_C const IID  IID_IDirect3D =
    { 0x3BBA0080, 0x2421, 0x11CF, { 0xA3, 0x1A, 0x00, 0xAA, 0x00, 0xB9, 0x33, 0x56 } };
EXTERN_C const IID  IID_IDirect3DDevice =
    { 0x64108800, 0x957D, 0x11D0, { 0x89, 0xAB, 0x00, 0xA0, 0xC9, 0x05, 0x41, 0x29 } };
EXTERN_C const IID  IID_IDirect3DTexture =
    { 0x2CDCD9E0, 0x25A0, 0x11CF, { 0xA3, 0x1A, 0x00, 0xAA, 0x00, 0xB9, 0x33, 0x56 } };
EXTERN_C const IID  IID_IDirect3DLight =
    { 0x4417C142, 0x33AD, 0x11CF, { 0x81, 0x6F, 0x00, 0x00, 0xC0, 0x20, 0x15, 0x6E } };
EXTERN_C const IID  IID_IDirect3DMaterial =
    { 0x4417C144, 0x33AD, 0x11CF, { 0x81, 0x6F, 0x00, 0x00, 0xC0, 0x20, 0x15, 0x6E } };
EXTERN_C const IID  IID_IDirect3DExecuteBuffer =
    { 0x4417C145, 0x33AD, 0x11CF, { 0x81, 0x6F, 0x00, 0x00, 0xC0, 0x20, 0x15, 0x6E } };
EXTERN_C const IID  IID_IDirect3DViewport =
    { 0x4417C146, 0x33AD, 0x11CF, { 0x81, 0x6F, 0x00, 0x00, 0xC0, 0x20, 0x15, 0x6E } };
EXTERN_C const IID  IID_IDirect3D2 =
    { 0x6AAE1EC1, 0x622A, 0x11D0, { 0x88, 0x9D, 0x00, 0xAA, 0x00, 0xBB, 0xB7, 0x6A } };
EXTERN_C const IID  IID_IDirect3DDevice2 =
    { 0x93281501, 0x8CF8, 0x11D0, { 0x89, 0xAB, 0x00, 0xA0, 0xC9, 0x05, 0x41, 0x29 } };
EXTERN_C const IID  IID_IDirect3DTexture2 =
    { 0x93281502, 0x8CF8, 0x11D0, { 0x89, 0xAB, 0x00, 0xA0, 0xC9, 0x05, 0x41, 0x29 } };
EXTERN_C const IID  IID_IDirect3DMaterial2 =
    { 0x93281503, 0x8CF8, 0x11D0, { 0x89, 0xAB, 0x00, 0xA0, 0xC9, 0x05, 0x41, 0x29 } };
EXTERN_C const IID  IID_IDirect3DViewport2 =
    { 0x93281500, 0x8CF8, 0x11D0, { 0x89, 0xAB, 0x00, 0xA0, 0xC9, 0x05, 0x41, 0x29 } };
EXTERN_C const IID  IID_IDirect3D3 =
    { 0xBB223240, 0xE72B, 0x11D0, { 0xA9, 0xB4, 0x00, 0xAA, 0x00, 0xC0, 0x99, 0x3E } };
EXTERN_C const IID  IID_IDirect3DDevice3 =
    { 0xB0AB3B60, 0x33D7, 0x11D1, { 0xA9, 0x81, 0x00, 0xC0, 0x4F, 0xD7, 0xB1, 0x74 } };
EXTERN_C const IID  IID_IDirect3DMaterial3 =
    { 0xCA9C46F4, 0xD3C5, 0x11D1, { 0xB7, 0x5A, 0x00, 0x60, 0x08, 0x52, 0xB3, 0x12 } };
EXTERN_C const IID  IID_IDirect3DViewport3 =
    { 0xB0AB3B61, 0x33D7, 0x11D1, { 0xA9, 0x81, 0x00, 0xC0, 0x4F, 0xD7, 0xB1, 0x74 } };
EXTERN_C const IID  IID_IDirect3DVertexBuffer =
    { 0x7A503555, 0x4A83, 0x11D1, { 0xA5, 0xDB, 0x00, 0xA0, 0xC9, 0x03, 0x67, 0xF8 } };
EXTERN_C const IID  IID_IDirect3D7 =
    { 0xF5049E77, 0x4861, 0x11D2, { 0xA4, 0x07, 0x00, 0xA0, 0xC9, 0x06, 0x29, 0xA8 } };
EXTERN_C const IID  IID_IDirect3DDevice7 =
    { 0xF5049E79, 0x4861, 0x11D2, { 0xA4, 0x07, 0x00, 0xA0, 0xC9, 0x06, 0x29, 0xA8 } };
EXTERN_C const IID  IID_IDirect3DVertexBuffer7 =
    { 0xF5049E7D, 0x4861, 0x11D2, { 0xA4, 0x07, 0x00, 0xA0, 0xC9, 0x06, 0x29, 0xA8 } };

/* d3drmobj.h */
EXTERN_C const IID      IID_IDirect3DRMObject =
    { 0xEB16CB00, 0xD271, 0x11CE, { 0xAC, 0x48, 0x00, 0x00, 0xC0, 0x38, 0x25, 0xA1 } };
EXTERN_C const IID      IID_IDirect3DRMObject2 =
    { 0x4516EC7C, 0x8F20, 0x11D0, { 0x9B, 0x6D, 0x00, 0x00, 0xC0, 0x78, 0x1B, 0xC3 } };
EXTERN_C const IID      IID_IDirect3DRMVisual =
    { 0xEB16CB04, 0xD271, 0x11CE, { 0xAC, 0x48, 0x00, 0x00, 0xC0, 0x38, 0x25, 0xA1 } };
EXTERN_C const IID      IID_IDirect3DRMDevice =
    { 0xE9E19280, 0x6E05, 0x11CF, { 0xAC, 0x4A, 0x00, 0x00, 0xC0, 0x38, 0x25, 0xA1 } };
EXTERN_C const IID      IID_IDirect3DRMDevice2 =
    { 0x4516EC78, 0x8F20, 0x11D0, { 0x9B, 0x6D, 0x00, 0x00, 0xC0, 0x78, 0x1B, 0xC3 } };
EXTERN_C const IID      IID_IDirect3DRMDevice3 =
    { 0x549F498B, 0xBFEB, 0x11D1, { 0x8E, 0xD8, 0x00, 0xA0, 0xC9, 0x67, 0xA4, 0x82 } };
EXTERN_C const IID      IID_IDirect3DRMViewport =
    { 0xEB16CB02, 0xD271, 0x11CE, { 0xAC, 0x48, 0x00, 0x00, 0xC0, 0x38, 0x25, 0xA1 } };
EXTERN_C const IID      IID_IDirect3DRMViewport2 =
    { 0x4A1B1BE6, 0xBFED, 0x11D1, { 0x8E, 0xD8, 0x00, 0xA0, 0xC9, 0x67, 0xA4, 0x82 } };
EXTERN_C const IID      IID_IDirect3DRMFrame =
    { 0xEB16CB03, 0xD271, 0x11CE, { 0xAC, 0x48, 0x00, 0x00, 0xC0, 0x38, 0x25, 0xA1 } };
EXTERN_C const IID      IID_IDirect3DRMFrame2 =
    { 0xC3DFBD60, 0x3988, 0x11D0, { 0x9E, 0xC2, 0x00, 0x00, 0xC0, 0x29, 0x1A, 0xC3 } };
EXTERN_C const IID      IID_IDirect3DRMFrame3 =
    { 0xFF6B7F70, 0xA40E, 0x11D1, { 0x91, 0xF9, 0x00, 0x00, 0xF8, 0x75, 0x8E, 0x66 } };
EXTERN_C const IID      IID_IDirect3DRMMesh =
    { 0xA3A80D01, 0x6E12, 0x11CF, { 0xAC, 0x4A, 0x00, 0x00, 0xC0, 0x38, 0x25, 0xA1 } };
EXTERN_C const IID      IID_IDirect3DRMProgressiveMesh =
    { 0x4516EC79, 0x8F20, 0x11D0, { 0x9B, 0x6D, 0x00, 0x00, 0xC0, 0x78, 0x1B, 0xC3 } };
EXTERN_C const IID      IID_IDirect3DRMShadow =
    { 0xAF359780, 0x6BA3, 0x11CF, { 0xAC, 0x4A, 0x00, 0x00, 0xC0, 0x38, 0x25, 0xA1 } };
EXTERN_C const IID      IID_IDirect3DRMShadow2 =
    { 0x86B44E25, 0x9C82, 0x11D1, { 0xBB, 0x0B, 0x00, 0xA0, 0xC9, 0x81, 0xA0, 0xA6 } };
EXTERN_C const IID      IID_IDirect3DRMFace =
    { 0xEB16CB07, 0xD271, 0x11CE, { 0xAC, 0x48, 0x00, 0x00, 0xC0, 0x38, 0x25, 0xA1 } };
EXTERN_C const IID      IID_IDirect3DRMFace2 =
    { 0x4516EC81, 0x8F20, 0x11D0, { 0x9B, 0x6D, 0x00, 0x00, 0xC0, 0x78, 0x1B, 0xC3 } };
EXTERN_C const IID      IID_IDirect3DRMMeshBuilder =
    { 0xA3A80D02, 0x6E12, 0x11CF, { 0xAC, 0x4A, 0x00, 0x00, 0xC0, 0x38, 0x25, 0xA1 } };
EXTERN_C const IID      IID_IDirect3DRMMeshBuilder2 =
    { 0x4516EC77, 0x8F20, 0x11D0, { 0x9B, 0x6D, 0x00, 0x00, 0xC0, 0x78, 0x1B, 0xC3 } };
EXTERN_C const IID      IID_IDirect3DRMMeshBuilder3 =
    { 0x4516EC82, 0x8F20, 0x11D0, { 0x9B, 0x6D, 0x00, 0x00, 0xC0, 0x78, 0x1B, 0xC3 } };
EXTERN_C const IID      IID_IDirect3DRMLight =
    { 0xEB16CB08, 0xD271, 0x11CE, { 0xAC, 0x48, 0x00, 0x00, 0xC0, 0x38, 0x25, 0xA1 } };
EXTERN_C const IID      IID_IDirect3DRMTexture =
    { 0xEB16CB09, 0xD271, 0x11CE, { 0xAC, 0x48, 0x00, 0x00, 0xC0, 0x38, 0x25, 0xA1 } };
EXTERN_C const IID      IID_IDirect3DRMTexture2 =
    { 0x120F30C0, 0x1629, 0x11D0, { 0x94, 0x1C, 0x00, 0x80, 0xC8, 0x0C, 0xFA, 0x7B } };
EXTERN_C const IID      IID_IDirect3DRMTexture3 =
    { 0xFF6B7F73, 0xA40E, 0x11D1, { 0x91, 0xF9, 0x00, 0x00, 0xF8, 0x75, 0x8E, 0x66 } };
EXTERN_C const IID      IID_IDirect3DRMWrap =
    { 0xEB16CB0A, 0xD271, 0x11CE, { 0xAC, 0x48, 0x00, 0x00, 0xC0, 0x38, 0x25, 0xA1 } };
EXTERN_C const IID      IID_IDirect3DRMMaterial =
    { 0xEB16CB0B, 0xD271, 0x11CE, { 0xAC, 0x48, 0x00, 0x00, 0xC0, 0x38, 0x25, 0xA1 } };
EXTERN_C const IID      IID_IDirect3DRMMaterial2 =
    { 0xFF6B7F75, 0xA40E, 0x11D1, { 0x91, 0xF9, 0x00, 0x00, 0xF8, 0x75, 0x8E, 0x66 } };
EXTERN_C const IID      IID_IDirect3DRMAnimation =
    { 0xEB16CB0D, 0xD271, 0x11CE, { 0xAC, 0x48, 0x00, 0x00, 0xC0, 0x38, 0x25, 0xA1 } };
EXTERN_C const IID      IID_IDirect3DRMAnimation2 =
    { 0xFF6B7F77, 0xA40E, 0x11D1, { 0x91, 0xF9, 0x00, 0x00, 0xF8, 0x75, 0x8E, 0x66 } };
EXTERN_C const IID      IID_IDirect3DRMAnimationSet =
    { 0xEB16CB0E, 0xD271, 0x11CE, { 0xAC, 0x48, 0x00, 0x00, 0xC0, 0x38, 0x25, 0xA1 } };
EXTERN_C const IID      IID_IDirect3DRMAnimationSet2 =
    { 0xFF6B7F79, 0xA40E, 0x11D1, { 0x91, 0xF9, 0x00, 0x00, 0xF8, 0x75, 0x8E, 0x66 } };
EXTERN_C const IID      IID_IDirect3DRMUserVisual =
    { 0x59163DE0, 0x6D43, 0x11CF, { 0xAC, 0x4A, 0x00, 0x00, 0xC0, 0x38, 0x25, 0xA1 } };
EXTERN_C const IID      IID_IDirect3DRMObjectArray =
    { 0x242F6BC2, 0x3849, 0x11D0, { 0x9B, 0x6D, 0x00, 0x00, 0xC0, 0x78, 0x1B, 0xC3 } };
EXTERN_C const IID      IID_IDirect3DRMDeviceArray =
    { 0xEB16CB10, 0xD271, 0x11CE, { 0xAC, 0x48, 0x00, 0x00, 0xC0, 0x38, 0x25, 0xA1 } };
EXTERN_C const IID      IID_IDirect3DRMFrameArray =
    { 0xEB16CB12, 0xD271, 0x11CE, { 0xAC, 0x48, 0x00, 0x00, 0xC0, 0x38, 0x25, 0xA1 } };
EXTERN_C const IID      IID_IDirect3DRMViewportArray =
    { 0xEB16CB11, 0xD271, 0x11CE, { 0xAC, 0x48, 0x00, 0x00, 0xC0, 0x38, 0x25, 0xA1 } };
EXTERN_C const IID      IID_IDirect3DRMVisualArray =
    { 0xEB16CB13, 0xD271, 0x11CE, { 0xAC, 0x48, 0x00, 0x00, 0xC0, 0x38, 0x25, 0xA1 } };
EXTERN_C const IID      IID_IDirect3DRMAnimationArray =
    { 0xD5F1CAE0, 0x4BD7, 0x11D1, { 0xB9, 0x74, 0x00, 0x60, 0x08, 0x3E, 0x45, 0xF3 } };
EXTERN_C const IID      IID_IDirect3DRMPickedArray =
    { 0xEB16CB16, 0xD271, 0x11CE, { 0xAC, 0x48, 0x00, 0x00, 0xC0, 0x38, 0x25, 0xA1 } }; 
EXTERN_C const IID      IID_IDirect3DRMLightArray =
    { 0xEB16CB14, 0xD271, 0x11CE, { 0xAC, 0x48, 0x00, 0x00, 0xC0, 0x38, 0x25, 0xA1 } };
EXTERN_C const IID      IID_IDirect3DRMFaceArray =
    { 0xEB16CB17, 0xD271, 0x11CE, { 0xAC, 0x48, 0x00, 0x00, 0xC0, 0x38, 0x25, 0xA1 } };
EXTERN_C const IID      IID_IDirect3DRMPicked2Array =
    { 0x4516EC7B, 0x8F20, 0x11D0, { 0x9B, 0x6D, 0x00, 0x00, 0xC0, 0x78, 0x1B, 0xC3 } };
EXTERN_C const IID      IID_IDirect3DRMInterpolator =
    { 0x242F6BC1, 0x3849, 0x11D0, { 0x9B, 0x6D, 0x00, 0x00, 0xC0, 0x78, 0x1B, 0xC3 } };
EXTERN_C const IID      IID_IDirect3DRMClippedVisual =
    { 0x5434E733, 0x6D66, 0x11D1, { 0xBB, 0x0B, 0x00, 0x00, 0xF8, 0x75, 0x86, 0x5A } };
EXTERN_C const CLSID    CLSID_CDirect3DRMDevice =
    { 0x4FA3568E, 0x623F, 0x11CF, { 0xAC, 0x4A, 0x00, 0x00, 0xC0, 0x38, 0x25, 0xA1 } };
EXTERN_C const CLSID    CLSID_CDirect3DRMViewport =
    { 0x4FA3568F, 0x623F, 0x11CF, { 0xAC, 0x4A, 0x00, 0x00, 0xC0, 0x38, 0x25, 0xA1 } };
EXTERN_C const CLSID    CLSID_CDirect3DRMFrame =
    { 0x4FA35690, 0x623F, 0x11CF, { 0xAC, 0x4A, 0x00, 0x00, 0xC0, 0x38, 0x25, 0xA1 } };
EXTERN_C const CLSID    CLSID_CDirect3DRMMesh =
    { 0x4FA35691, 0x623F, 0x11CF, { 0xAC, 0x4A, 0x00, 0x00, 0xC0, 0x38, 0x25, 0xA1 } };
EXTERN_C const CLSID    CLSID_CDirect3DRMMeshBuilder =
    { 0x4FA35692, 0x623F, 0x11CF, { 0xAC, 0x4A, 0x00, 0x00, 0xC0, 0x38, 0x25, 0xA1 } };
EXTERN_C const CLSID    CLSID_CDirect3DRMFace =
    { 0x4FA35693, 0x623F, 0x11CF, { 0xAC, 0x4A, 0x00, 0x00, 0xC0, 0x38, 0x25, 0xA1 } };
EXTERN_C const CLSID    CLSID_CDirect3DRMLight =
    { 0x4FA35694, 0x623F, 0x11CF, { 0xAC, 0x4A, 0x00, 0x00, 0xC0, 0x38, 0x25, 0xA1 } };
EXTERN_C const CLSID    CLSID_CDirect3DRMTexture =
    { 0x4FA35695, 0x623F, 0x11CF, { 0xAC, 0x4A, 0x00, 0x00, 0xC0, 0x38, 0x25, 0xA1 } };
EXTERN_C const CLSID    CLSID_CDirect3DRMWrap =
    { 0x4FA35696, 0x623F, 0x11CF, { 0xAC, 0x4A, 0x00, 0x00, 0xC0, 0x38, 0x25, 0xA1 } };
EXTERN_C const CLSID    CLSID_CDirect3DRMMaterial =
    { 0x4FA35697, 0x623F, 0x11CF, { 0xAC, 0x4A, 0x00, 0x00, 0xC0, 0x38, 0x25, 0xA1 } };
EXTERN_C const CLSID    CLSID_CDirect3DRMAnimation =
    { 0x4FA35698, 0x623F, 0x11CF, { 0xAC, 0x4A, 0x00, 0x00, 0xC0, 0x38, 0x25, 0xA1 } };
EXTERN_C const CLSID    CLSID_CDirect3DRMAnimationSet =
    { 0x4FA35699, 0x623F, 0x11CF, { 0xAC, 0x4A, 0x00, 0x00, 0xC0, 0x38, 0x25, 0xA1 } };
EXTERN_C const CLSID    CLSID_CDirect3DRMUserVisual =
    { 0x4FA3669A, 0x623F, 0x11CF, { 0xAC, 0x4A, 0x00, 0x00, 0xC0, 0x38, 0x25, 0xA1 } };
EXTERN_C const CLSID    CLSID_CDirect3DRMShadow =
    { 0x4FA3669B, 0x623F, 0x11CF, { 0xAC, 0x4A, 0x00, 0x00, 0xC0, 0x38, 0x25, 0xA1 } };
EXTERN_C const CLSID    CLSID_CDirect3DRMViewportInterpolator =
    { 0x0DE9EAA1, 0x3B84, 0x11D0, { 0x9B, 0x6D, 0x00, 0x00, 0xC0, 0x78, 0x1B, 0xC3 } };
EXTERN_C const CLSID    CLSID_CDirect3DRMFrameInterpolator =
    { 0x0DE9EAA2, 0x3B84, 0x11D0, { 0x9B, 0x6D, 0x00, 0x00, 0xC0, 0x78, 0x1B, 0xC3 } };
EXTERN_C const CLSID    CLSID_CDirect3DRMMeshInterpolator =
    { 0x0DE9EAA3, 0x3B84, 0x11D0, { 0x9B, 0x6D, 0x00, 0x00, 0xC0, 0x78, 0x1B, 0xC3 } };
EXTERN_C const CLSID    CLSID_CDirect3DRMLightInterpolator =
    { 0x0DE9EAA6, 0x3B84, 0x11D0, { 0x9B, 0x6D, 0x00, 0x00, 0xC0, 0x78, 0x1B, 0xC3 } };
EXTERN_C const CLSID    CLSID_CDirect3DRMMaterialInterpolator =
    { 0x0DE9EAA7, 0x3B84, 0x11D0, { 0x9B, 0x6D, 0x00, 0x00, 0xC0, 0x78, 0x1B, 0xC3 } };
EXTERN_C const CLSID    CLSID_CDirect3DRMTextureInterpolator =
    { 0x0DE9EAA8, 0x3B84, 0x11D0, { 0x9B, 0x6D, 0x00, 0x00, 0xC0, 0x78, 0x1B, 0xC3 } };
EXTERN_C const CLSID    CLSID_CDirect3DRMProgressiveMesh =
    { 0x4516EC40, 0x8F20, 0x11D0, { 0x9B, 0x6D, 0x00, 0x00, 0xC0, 0x78, 0x1B, 0xC3 } };
EXTERN_C const CLSID    CLSID_CDirect3DRMClippedVisual =
    { 0x5434E72D, 0x6D66, 0x11D1, { 0xBB, 0x0B, 0x00, 0x00, 0xF8, 0x75, 0x86, 0x5A } };

/* d3drm.h */
EXTERN_C const IID      IID_IDirect3DRM =
    { 0x2BC49361, 0x8327, 0x11CF, { 0xAC, 0x4A, 0x00, 0x00, 0xC0, 0x38, 0x25, 0xA1 } };
EXTERN_C const IID      IID_IDirect3DRM2 =
    { 0x4516ECC8, 0x8F20, 0x11D0, { 0x9B, 0x6D, 0x00, 0x00, 0xC0, 0x78, 0x1B, 0xC3 } };
EXTERN_C const IID      IID_IDirect3DRM3 =
    { 0x4516EC83, 0x8F20, 0x11D0, { 0x9B, 0x6D, 0x00, 0x00, 0xC0, 0x78, 0x1B, 0xC3 } };
EXTERN_C const CLSID    CLSID_CDirect3DRM =
    { 0x4516EC41, 0x8F20, 0x11D0, { 0x9B, 0x6D, 0x00, 0x00, 0xC0, 0x78, 0x1B, 0xC3 } };

/* d3d9.h */
EXTERN_C const IID  IID_IDirect3D9 =
    { 0x81BDCBCA, 0x64D4, 0x426D, { 0xAE, 0x8D, 0xAD, 0x01, 0x47, 0xF4, 0x27, 0x5C } };
EXTERN_C const IID  IID_IDirect3D9Ex =
    { 0x02177241, 0x69FC, 0x400C, { 0x8F, 0xF1, 0x93, 0xA4, 0x4D, 0xF6, 0x86, 0x1D } };
EXTERN_C const IID  IID_IDirect3DDevice9 =
    { 0xD0223B96, 0xBF7A, 0x43FD, { 0x92, 0xBD, 0xA4, 0x3B, 0x0D, 0x82, 0xB9, 0xEB } };
EXTERN_C const IID  IID_IDirect3DDevice9Ex =
    { 0xB18B10CE, 0x2649, 0x405A, { 0x87, 0x0F, 0x95, 0xF7, 0x77, 0xD4, 0x31, 0x3A } };
EXTERN_C const IID  IID_IDirect3DStateBlock9 =
    { 0xB07C4FE5, 0x310D, 0x4BA8, { 0xA2, 0x3C, 0x4F, 0x0F, 0x20, 0x6F, 0x21, 0x8B } };
EXTERN_C const IID  IID_IDirect3DResource9 =
    { 0x05EEC05D, 0x8F7D, 0x4362, { 0xB9, 0x99, 0xD1, 0xBA, 0xF3, 0x57, 0xC7, 0x04 } };
EXTERN_C const IID  IID_IDirect3DVertexDeclaration9 =
    { 0xDD13C59C, 0x36FA, 0x4098, { 0xA8, 0xFB, 0xC7, 0xED, 0x39, 0xDC, 0x85, 0x46 } };
EXTERN_C const IID  IID_IDirect3DVertexShader9 =
    { 0xEFC5557E, 0x6265, 0x4613, { 0x8A, 0x94, 0x43, 0x85, 0x78, 0x89, 0xEB, 0x36 } };
EXTERN_C const IID  IID_IDirect3DPixelShader9 =
    { 0x6D3BDBDC, 0x5B02, 0x4415, { 0xB8, 0x52, 0xCE, 0x5E, 0x8B, 0xCC, 0xB2, 0x89 } };
EXTERN_C const IID  IID_IDirect3DBaseTexture9 =
    { 0x580CA87E, 0x1D3C, 0x4D54, { 0x99, 0x1D, 0xB7, 0xD3, 0xE3, 0xC2, 0x98, 0xCE } };
EXTERN_C const IID  IID_IDirect3DTexture9 =
    { 0x85C31227, 0x3DE5, 0x4F00, { 0x9B, 0x3A, 0xF1, 0x1A, 0xC3, 0x8C, 0x18, 0xB5 } };
EXTERN_C const IID  IID_IDirect3DVolumeTexture9 =
    { 0x2518526C, 0xE789, 0x4111, { 0xA7, 0xB9, 0x47, 0xEF, 0x32, 0x8D, 0x13, 0xE6 } };
EXTERN_C const IID  IID_IDirect3DCubeTexture9 =
    { 0xFFF32F81, 0xD953, 0x473A, { 0x92, 0x23, 0x93, 0xD6, 0x52, 0xAB, 0xA9, 0x3F } };
EXTERN_C const IID  IID_IDirect3DVertexBuffer9 =
    { 0xB64BB1B5, 0xFD70, 0x4DF6, { 0xBF, 0x91, 0x19, 0xD0, 0xA1, 0x24, 0x55, 0xE3 } };
EXTERN_C const IID  IID_IDirect3DIndexBuffer9 =
    { 0x7C9DD65E, 0xD3F7, 0x4529, { 0xAC, 0xEE, 0x78, 0x58, 0x30, 0xAC, 0xDE, 0x35 } };
EXTERN_C const IID  IID_IDirect3DSurface9 =
    { 0x0CFBAF3A, 0x9FF6, 0x429A, { 0x99, 0xB3, 0xA2, 0x79, 0x6A, 0xF8, 0xB8, 0x9B } };
EXTERN_C const IID  IID_IDirect3DVolume9 =
    { 0x24F416E6, 0x1F67, 0x4AA7, { 0xB8, 0x8E, 0xD3, 0x3F, 0x6F, 0x31, 0x28, 0xA1 } };
EXTERN_C const IID  IID_IDirect3DSwapChain9 =
    { 0x794950F2, 0xADFC, 0x458A, { 0x90, 0x5E, 0x10, 0xA1, 0x0B, 0x0B, 0x50, 0x3B } };
EXTERN_C const IID  IID_IDirect3DSwapChain9Ex =
    { 0x91886CAF, 0x1C3D, 0x4D2E, { 0xA0, 0xAB, 0x3E, 0x4C, 0x7D, 0x8D, 0x33, 0x03 } };
EXTERN_C const IID  IID_IDirect3DQuery9 =
    { 0xD9771460, 0xA695, 0x4F26, { 0xBB, 0xD3, 0x27, 0xB8, 0x40, 0xB5, 0x41, 0xCC } };

/* dvp.h */
EXTERN_C const IID  IID_IDDVideoPortContainer =
    { 0x6C142760, 0xA733, 0x11CE, { 0xA5, 0x21, 0x00, 0x20, 0xAF, 0x0B, 0xE5, 0x60 } };
EXTERN_C const IID  IID_IDirectDrawVideoPort =
    { 0xB36D93E0, 0x2B43, 0x11CF, { 0xA2, 0xDE, 0x00, 0xAA, 0x00, 0xB9, 0x33, 0x56 } };
EXTERN_C const IID  IID_IDirectDrawVideoPortNotify =
    { 0xA655FB94, 0x0589, 0x4E57, { 0xB3, 0x33, 0x56, 0x7A, 0x89, 0x46, 0x8C, 0x88 } };


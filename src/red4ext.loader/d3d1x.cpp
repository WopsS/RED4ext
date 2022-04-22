#include "stdafx.hpp"
#include "d3d1x.hpp"

using D3D11CreateDevice_t = decltype(&D3D11CreateDevice);
using D3D11CreateDeviceAndSwapChain_t = decltype(&D3D11CreateDeviceAndSwapChain);
using D3D11On12CreateDevice_t = decltype(&D3D11On12CreateDevice);
using D3DKMTCloseAdapter_t = decltype(&D3DKMTCloseAdapter);
using D3DKMTCreateAllocation_t = decltype(&D3DKMTCreateAllocation);
using D3DKMTCreateContext_t = decltype(&D3DKMTCreateContext);
using D3DKMTCreateDevice_t = decltype(&D3DKMTCreateDevice);
using D3DKMTCreateSynchronizationObject_t = decltype(&D3DKMTCreateSynchronizationObject);
using D3DKMTDestroyAllocation_t = decltype(&D3DKMTDestroyAllocation);
using D3DKMTDestroyContext_t = decltype(&D3DKMTDestroyContext);
using D3DKMTDestroyDevice_t = decltype(&D3DKMTDestroyDevice);
using D3DKMTDestroySynchronizationObject_t = decltype(&D3DKMTDestroySynchronizationObject);
using D3DKMTEscape_t = decltype(&D3DKMTEscape);
using D3DKMTGetContextSchedulingPriority_t = decltype(&D3DKMTGetContextSchedulingPriority);
using D3DKMTGetDeviceState_t = decltype(&D3DKMTGetDeviceState);
using D3DKMTGetDisplayModeList_t = decltype(&D3DKMTGetDisplayModeList);
using D3DKMTGetMultisampleMethodList_t = decltype(&D3DKMTGetMultisampleMethodList);
using D3DKMTGetRuntimeData_t = decltype(&D3DKMTGetRuntimeData);
using D3DKMTGetSharedPrimaryHandle_t = decltype(&D3DKMTGetSharedPrimaryHandle);
using D3DKMTLock_t = decltype(&D3DKMTLock);
using D3DKMTOpenAdapterFromHdc_t = decltype(&D3DKMTOpenAdapterFromHdc);
using D3DKMTOpenResource_t = decltype(&D3DKMTOpenResource);
using D3DKMTPresent_t = decltype(&D3DKMTPresent);
using D3DKMTQueryAdapterInfo_t = decltype(&D3DKMTQueryAdapterInfo);
using D3DKMTQueryAllocationResidency_t = decltype(&D3DKMTQueryAllocationResidency);
using D3DKMTQueryResourceInfo_t = decltype(&D3DKMTQueryResourceInfo);
using D3DKMTRender_t = decltype(&D3DKMTRender);
using D3DKMTSetAllocationPriority_t = decltype(&D3DKMTSetAllocationPriority);
using D3DKMTSetContextSchedulingPriority_t = decltype(&D3DKMTSetContextSchedulingPriority);
using D3DKMTSetDisplayMode_t = decltype(&D3DKMTSetDisplayMode);
using D3DKMTSetDisplayPrivateDriverFormat_t = decltype(&D3DKMTSetDisplayPrivateDriverFormat);
using D3DKMTSetGammaRamp_t = decltype(&D3DKMTSetGammaRamp);
using D3DKMTSetVidPnSourceOwner_t = decltype(&D3DKMTSetVidPnSourceOwner);
using D3DKMTSignalSynchronizationObject_t = decltype(&D3DKMTSignalSynchronizationObject);
using D3DKMTUnlock_t = decltype(&D3DKMTUnlock);
using D3DKMTWaitForSynchronizationObject_t = decltype(&D3DKMTWaitForSynchronizationObject);
using D3DKMTWaitForVerticalBlankEvent_t = decltype(&D3DKMTWaitForVerticalBlankEvent);

using CreateDirect3D11DeviceFromDXGIDevice_t = void (*)();
using CreateDirect3D11SurfaceFromDXGISurface_t = void (*)();
using D3D11CoreCreateDevice_t = void (*)();
using D3D11CoreCreateLayeredDevice_t = void (*)();
using D3D11CoreGetLayeredDeviceSize_t = void (*)();
using D3D11CoreRegisterLayers_t = void (*)();
using D3D11CreateDeviceForD3D12_t = void (*)();
using D3DPerformance_BeginEvent_t = void (*)();
using D3DPerformance_EndEvent_t = void (*)();
using D3DPerformance_GetStatus_t = void (*)();
using D3DPerformance_SetMarker_t = void (*)();
using EnableFeatureLevelUpgrade_t = void (*)();
using OpenAdapter10_t = void (*)();
using OpenAdapter10_2_t = void (*)();

namespace Functions
{
D3D11CreateDevice_t D3D11CreateDevice;
D3D11CreateDeviceAndSwapChain_t D3D11CreateDeviceAndSwapChain;
D3D11On12CreateDevice_t D3D11On12CreateDevice;
D3DKMTCloseAdapter_t D3DKMTCloseAdapter;
D3DKMTCreateAllocation_t D3DKMTCreateAllocation;
D3DKMTCreateContext_t D3DKMTCreateContext;
D3DKMTCreateDevice_t D3DKMTCreateDevice;
D3DKMTCreateSynchronizationObject_t D3DKMTCreateSynchronizationObject;
D3DKMTDestroyAllocation_t D3DKMTDestroyAllocation;
D3DKMTDestroyContext_t D3DKMTDestroyContext;
D3DKMTDestroyDevice_t D3DKMTDestroyDevice;
D3DKMTDestroySynchronizationObject_t D3DKMTDestroySynchronizationObject;
D3DKMTEscape_t D3DKMTEscape;
D3DKMTGetContextSchedulingPriority_t D3DKMTGetContextSchedulingPriority;
D3DKMTGetDeviceState_t D3DKMTGetDeviceState;
D3DKMTGetDisplayModeList_t D3DKMTGetDisplayModeList;
D3DKMTGetMultisampleMethodList_t D3DKMTGetMultisampleMethodList;
D3DKMTGetRuntimeData_t D3DKMTGetRuntimeData;
D3DKMTGetSharedPrimaryHandle_t D3DKMTGetSharedPrimaryHandle;
D3DKMTLock_t D3DKMTLock;
D3DKMTOpenAdapterFromHdc_t D3DKMTOpenAdapterFromHdc;
D3DKMTOpenResource_t D3DKMTOpenResource;
D3DKMTPresent_t D3DKMTPresent;
D3DKMTQueryAdapterInfo_t D3DKMTQueryAdapterInfo;
D3DKMTQueryAllocationResidency_t D3DKMTQueryAllocationResidency;
D3DKMTQueryResourceInfo_t D3DKMTQueryResourceInfo;
D3DKMTRender_t D3DKMTRender;
D3DKMTSetAllocationPriority_t D3DKMTSetAllocationPriority;
D3DKMTSetContextSchedulingPriority_t D3DKMTSetContextSchedulingPriority;
D3DKMTSetDisplayMode_t D3DKMTSetDisplayMode;
D3DKMTSetDisplayPrivateDriverFormat_t D3DKMTSetDisplayPrivateDriverFormat;
D3DKMTSetGammaRamp_t D3DKMTSetGammaRamp;
D3DKMTSetVidPnSourceOwner_t D3DKMTSetVidPnSourceOwner;
D3DKMTSignalSynchronizationObject_t D3DKMTSignalSynchronizationObject;
D3DKMTUnlock_t D3DKMTUnlock;
D3DKMTWaitForSynchronizationObject_t D3DKMTWaitForSynchronizationObject;
D3DKMTWaitForVerticalBlankEvent_t D3DKMTWaitForVerticalBlankEvent;

CreateDirect3D11DeviceFromDXGIDevice_t CreateDirect3D11DeviceFromDXGIDevice;
CreateDirect3D11SurfaceFromDXGISurface_t CreateDirect3D11SurfaceFromDXGISurface;
D3D11CoreCreateDevice_t D3D11CoreCreateDevice;
D3D11CoreCreateLayeredDevice_t D3D11CoreCreateLayeredDevice;
D3D11CoreGetLayeredDeviceSize_t D3D11CoreGetLayeredDeviceSize;
D3D11CoreRegisterLayers_t D3D11CoreRegisterLayers;
D3D11CreateDeviceForD3D12_t D3D11CreateDeviceForD3D12;
D3DPerformance_BeginEvent_t D3DPerformance_BeginEvent;
D3DPerformance_EndEvent_t D3DPerformance_EndEvent;
D3DPerformance_GetStatus_t D3DPerformance_GetStatus;
D3DPerformance_SetMarker_t D3DPerformance_SetMarker;
EnableFeatureLevelUpgrade_t EnableFeatureLevelUpgrade;
OpenAdapter10_t OpenAdapter10;
OpenAdapter10_2_t OpenAdapter10_2;
} // namespace Functions

HRESULT WINAPI _D3D11CreateDevice(IDXGIAdapter* pAdapter, D3D_DRIVER_TYPE DriverType, HMODULE Software, UINT Flags,
                                  CONST D3D_FEATURE_LEVEL* pFeatureLevels, UINT FeatureLevels, UINT SDKVersion,
                                  ID3D11Device** ppDevice, D3D_FEATURE_LEVEL* pFeatureLevel,
                                  ID3D11DeviceContext** ppImmediateContext)
{
    return Functions::D3D11CreateDevice(pAdapter, DriverType, Software, Flags, pFeatureLevels, FeatureLevels,
                                        SDKVersion, ppDevice, pFeatureLevel, ppImmediateContext);
}

HRESULT WINAPI _D3D11CreateDeviceAndSwapChain(IDXGIAdapter* pAdapter, D3D_DRIVER_TYPE DriverType, HMODULE Software,
                                              UINT Flags, CONST D3D_FEATURE_LEVEL* pFeatureLevels, UINT FeatureLevels,
                                              UINT SDKVersion, CONST DXGI_SWAP_CHAIN_DESC* pSwapChainDesc,
                                              IDXGISwapChain** ppSwapChain, ID3D11Device** ppDevice,
                                              D3D_FEATURE_LEVEL* pFeatureLevel,
                                              ID3D11DeviceContext** ppImmediateContext)
{
    return Functions::D3D11CreateDeviceAndSwapChain(pAdapter, DriverType, Software, Flags, pFeatureLevels,
                                                    FeatureLevels, SDKVersion, pSwapChainDesc, ppSwapChain, ppDevice,
                                                    pFeatureLevel, ppImmediateContext);
}

HRESULT WINAPI _D3D11On12CreateDevice(IUnknown* pDevice, UINT Flags, CONST D3D_FEATURE_LEVEL* pFeatureLevels,
                                      UINT FeatureLevels, IUnknown* CONST* ppCommandQueues, UINT NumQueues,
                                      UINT NodeMask, ID3D11Device** ppDevice, ID3D11DeviceContext** ppImmediateContext,
                                      D3D_FEATURE_LEVEL* pChosenFeatureLevel)
{
    return Functions::D3D11On12CreateDevice(pDevice, Flags, pFeatureLevels, FeatureLevels, ppCommandQueues, NumQueues,
                                            NodeMask, ppDevice, ppImmediateContext, pChosenFeatureLevel);
}

NTSTATUS APIENTRY _D3DKMTCloseAdapter(CONST D3DKMT_CLOSEADAPTER* a1)
{
    return Functions::D3DKMTCloseAdapter(a1);
}

NTSTATUS APIENTRY _D3DKMTCreateAllocation(D3DKMT_CREATEALLOCATION* a1)
{
    return Functions::D3DKMTCreateAllocation(a1);
}

NTSTATUS APIENTRY _D3DKMTCreateContext(D3DKMT_CREATECONTEXT* a1)
{
    return Functions::D3DKMTCreateContext(a1);
}

NTSTATUS APIENTRY _D3DKMTCreateDevice(D3DKMT_CREATEDEVICE* a1)
{
    return Functions::D3DKMTCreateDevice(a1);
}

NTSTATUS APIENTRY _D3DKMTCreateSynchronizationObject(D3DKMT_CREATESYNCHRONIZATIONOBJECT* a1)
{
    return Functions::D3DKMTCreateSynchronizationObject(a1);
}

NTSTATUS APIENTRY _D3DKMTDestroyAllocation(CONST D3DKMT_DESTROYALLOCATION* a1)
{
    return Functions::D3DKMTDestroyAllocation(a1);
}

NTSTATUS APIENTRY _D3DKMTDestroyContext(CONST D3DKMT_DESTROYCONTEXT* a1)
{
    return Functions::D3DKMTDestroyContext(a1);
}

NTSTATUS APIENTRY _D3DKMTDestroyDevice(CONST D3DKMT_DESTROYDEVICE* a1)
{
    return Functions::D3DKMTDestroyDevice(a1);
}

NTSTATUS APIENTRY _D3DKMTDestroySynchronizationObject(CONST D3DKMT_DESTROYSYNCHRONIZATIONOBJECT* a1)
{
    return Functions::D3DKMTDestroySynchronizationObject(a1);
}

NTSTATUS APIENTRY _D3DKMTEscape(CONST D3DKMT_ESCAPE* a1)
{
    return Functions::D3DKMTEscape(a1);
}

NTSTATUS APIENTRY _D3DKMTGetContextSchedulingPriority(D3DKMT_GETCONTEXTSCHEDULINGPRIORITY* a1)
{
    return Functions::D3DKMTGetContextSchedulingPriority(a1);
}

NTSTATUS APIENTRY _D3DKMTGetDeviceState(D3DKMT_GETDEVICESTATE* a1)
{
    return Functions::D3DKMTGetDeviceState(a1);
}

NTSTATUS APIENTRY _D3DKMTGetDisplayModeList(D3DKMT_GETDISPLAYMODELIST* a1)
{
    return Functions::D3DKMTGetDisplayModeList(a1);
}

NTSTATUS APIENTRY _D3DKMTGetMultisampleMethodList(D3DKMT_GETMULTISAMPLEMETHODLIST* a1)
{
    return Functions::D3DKMTGetMultisampleMethodList(a1);
}

NTSTATUS APIENTRY _D3DKMTGetRuntimeData(CONST D3DKMT_GETRUNTIMEDATA* a1)
{
    return Functions::D3DKMTGetRuntimeData(a1);
}

NTSTATUS APIENTRY _D3DKMTGetSharedPrimaryHandle(D3DKMT_GETSHAREDPRIMARYHANDLE* a1)
{
    return Functions::D3DKMTGetSharedPrimaryHandle(a1);
}

NTSTATUS APIENTRY _D3DKMTLock(D3DKMT_LOCK* a1)
{
    return Functions::D3DKMTLock(a1);
}

NTSTATUS APIENTRY _D3DKMTOpenAdapterFromHdc(D3DKMT_OPENADAPTERFROMHDC* a1)
{
    return Functions::D3DKMTOpenAdapterFromHdc(a1);
}

NTSTATUS APIENTRY _D3DKMTOpenResource(D3DKMT_OPENRESOURCE* a1)
{
    return Functions::D3DKMTOpenResource(a1);
}

NTSTATUS APIENTRY _D3DKMTPresent(D3DKMT_PRESENT* a1)
{
    return Functions::D3DKMTPresent(a1);
}

NTSTATUS APIENTRY _D3DKMTQueryAdapterInfo(CONST D3DKMT_QUERYADAPTERINFO* a1)
{
    return Functions::D3DKMTQueryAdapterInfo(a1);
}

NTSTATUS APIENTRY _D3DKMTQueryAllocationResidency(CONST D3DKMT_QUERYALLOCATIONRESIDENCY* a1)
{
    return Functions::D3DKMTQueryAllocationResidency(a1);
}

NTSTATUS APIENTRY _D3DKMTQueryResourceInfo(D3DKMT_QUERYRESOURCEINFO* a1)
{
    return Functions::D3DKMTQueryResourceInfo(a1);
}

NTSTATUS APIENTRY _D3DKMTRender(D3DKMT_RENDER* a1)
{
    return Functions::D3DKMTRender(a1);
}

NTSTATUS APIENTRY _D3DKMTSetAllocationPriority(CONST D3DKMT_SETALLOCATIONPRIORITY* a1)
{
    return Functions::D3DKMTSetAllocationPriority(a1);
}

NTSTATUS APIENTRY _D3DKMTSetContextSchedulingPriority(CONST D3DKMT_SETCONTEXTSCHEDULINGPRIORITY* a1)
{
    return Functions::D3DKMTSetContextSchedulingPriority(a1);
}

NTSTATUS APIENTRY _D3DKMTSetDisplayMode(CONST D3DKMT_SETDISPLAYMODE* a1)
{
    return Functions::D3DKMTSetDisplayMode(a1);
}

NTSTATUS APIENTRY _D3DKMTSetDisplayPrivateDriverFormat(CONST D3DKMT_SETDISPLAYPRIVATEDRIVERFORMAT* a1)
{
    return Functions::D3DKMTSetDisplayPrivateDriverFormat(a1);
}

NTSTATUS APIENTRY _D3DKMTSetGammaRamp(CONST D3DKMT_SETGAMMARAMP* a1)
{
    return Functions::D3DKMTSetGammaRamp(a1);
}

NTSTATUS APIENTRY _D3DKMTSetVidPnSourceOwner(CONST D3DKMT_SETVIDPNSOURCEOWNER* a1)
{
    return Functions::D3DKMTSetVidPnSourceOwner(a1);
}

NTSTATUS APIENTRY _D3DKMTSignalSynchronizationObject(CONST D3DKMT_SIGNALSYNCHRONIZATIONOBJECT* a1)
{
    return Functions::D3DKMTSignalSynchronizationObject(a1);
}

NTSTATUS APIENTRY _D3DKMTUnlock(CONST D3DKMT_UNLOCK* a1)
{
    return Functions::D3DKMTUnlock(a1);
}

NTSTATUS APIENTRY _D3DKMTWaitForSynchronizationObject(CONST D3DKMT_WAITFORSYNCHRONIZATIONOBJECT* a1)
{
    return Functions::D3DKMTWaitForSynchronizationObject(a1);
}

NTSTATUS APIENTRY _D3DKMTWaitForVerticalBlankEvent(CONST D3DKMT_WAITFORVERTICALBLANKEVENT* a1)
{
    return Functions::D3DKMTWaitForVerticalBlankEvent(a1);
}

void _CreateDirect3D11DeviceFromDXGIDevice()
{
    Functions::CreateDirect3D11DeviceFromDXGIDevice();
}

void _CreateDirect3D11SurfaceFromDXGISurface()
{
    Functions::CreateDirect3D11SurfaceFromDXGISurface();
}

void _D3D11CoreCreateDevice()
{
    Functions::D3D11CoreCreateDevice();
}

void _D3D11CoreCreateLayeredDevice()
{
    Functions::D3D11CoreCreateLayeredDevice();
}

void _D3D11CoreGetLayeredDeviceSize()
{
    Functions::D3D11CoreGetLayeredDeviceSize();
}

void _D3D11CoreRegisterLayers()
{
    Functions::D3D11CoreRegisterLayers();
}

void _D3D11CreateDeviceForD3D12()
{
    Functions::D3D11CreateDeviceForD3D12();
}

void _D3DPerformance_BeginEvent()
{
    Functions::D3DPerformance_BeginEvent();
}

void _D3DPerformance_EndEvent()
{
    Functions::D3DPerformance_EndEvent();
}

void _D3DPerformance_GetStatus()
{
    Functions::D3DPerformance_GetStatus();
}

void _D3DPerformance_SetMarker()
{
    Functions::D3DPerformance_SetMarker();
}

void _EnableFeatureLevelUpgrade()
{
    Functions::EnableFeatureLevelUpgrade();
}

void _OpenAdapter10()
{
    Functions::OpenAdapter10();
}

void _OpenAdapter10_2()
{
    Functions::OpenAdapter10_2();
}

bool LoadOriginal()
{
    wil::unique_cotaskmem_string rawPath;
    if (FAILED(SHGetKnownFolderPath(FOLDERID_System, KF_FLAG_DEFAULT, nullptr, &rawPath)))
    {
        return false;
    }

    constexpr auto dllName = "d3d11.dll";

    std::filesystem::path dll = rawPath.get();
    dll /= dllName;

    auto handle = LoadLibrary(dll.c_str());
    if (!handle)
    {
        return false;
    }

    Functions::CreateDirect3D11DeviceFromDXGIDevice = reinterpret_cast<CreateDirect3D11DeviceFromDXGIDevice_t>(
        GetProcAddress(handle, "CreateDirect3D11DeviceFromDXGIDevice"));
    Functions::CreateDirect3D11SurfaceFromDXGISurface = reinterpret_cast<CreateDirect3D11SurfaceFromDXGISurface_t>(
        GetProcAddress(handle, "CreateDirect3D11SurfaceFromDXGISurface"));
    Functions::D3D11CoreCreateDevice =
        reinterpret_cast<D3D11CoreCreateDevice_t>(GetProcAddress(handle, "D3D11CoreCreateDevice"));
    Functions::D3D11CoreCreateLayeredDevice =
        reinterpret_cast<D3D11CoreCreateLayeredDevice_t>(GetProcAddress(handle, "D3D11CoreCreateLayeredDevice"));
    Functions::D3D11CoreGetLayeredDeviceSize =
        reinterpret_cast<D3D11CoreGetLayeredDeviceSize_t>(GetProcAddress(handle, "D3D11CoreGetLayeredDeviceSize"));
    Functions::D3D11CoreRegisterLayers =
        reinterpret_cast<D3D11CoreRegisterLayers_t>(GetProcAddress(handle, "D3D11CoreRegisterLayers"));
    Functions::D3D11CreateDevice = reinterpret_cast<D3D11CreateDevice_t>(GetProcAddress(handle, "D3D11CreateDevice"));
    Functions::D3D11CreateDeviceAndSwapChain =
        reinterpret_cast<D3D11CreateDeviceAndSwapChain_t>(GetProcAddress(handle, "D3D11CreateDeviceAndSwapChain"));
    Functions::D3D11CreateDeviceForD3D12 =
        reinterpret_cast<D3D11CreateDeviceForD3D12_t>(GetProcAddress(handle, "D3D11CreateDeviceForD3D12"));
    Functions::D3D11On12CreateDevice =
        reinterpret_cast<D3D11On12CreateDevice_t>(GetProcAddress(handle, "D3D11On12CreateDevice"));
    Functions::D3DKMTCloseAdapter =
        reinterpret_cast<D3DKMTCloseAdapter_t>(GetProcAddress(handle, "D3DKMTCloseAdapter"));
    Functions::D3DKMTCreateAllocation =
        reinterpret_cast<D3DKMTCreateAllocation_t>(GetProcAddress(handle, "D3DKMTCreateAllocation"));
    Functions::D3DKMTCreateContext =
        reinterpret_cast<D3DKMTCreateContext_t>(GetProcAddress(handle, "D3DKMTCreateContext"));
    Functions::D3DKMTCreateDevice =
        reinterpret_cast<D3DKMTCreateDevice_t>(GetProcAddress(handle, "D3DKMTCreateDevice"));
    Functions::D3DKMTCreateSynchronizationObject = reinterpret_cast<D3DKMTCreateSynchronizationObject_t>(
        GetProcAddress(handle, "D3DKMTCreateSynchronizationObject"));
    Functions::D3DKMTDestroyAllocation =
        reinterpret_cast<D3DKMTDestroyAllocation_t>(GetProcAddress(handle, "D3DKMTDestroyAllocation"));
    Functions::D3DKMTDestroyContext =
        reinterpret_cast<D3DKMTDestroyContext_t>(GetProcAddress(handle, "D3DKMTDestroyContext"));
    Functions::D3DKMTDestroyDevice =
        reinterpret_cast<D3DKMTDestroyDevice_t>(GetProcAddress(handle, "D3DKMTDestroyDevice"));
    Functions::D3DKMTDestroySynchronizationObject = reinterpret_cast<D3DKMTDestroySynchronizationObject_t>(
        GetProcAddress(handle, "D3DKMTDestroySynchronizationObject"));
    Functions::D3DKMTEscape = reinterpret_cast<D3DKMTEscape_t>(GetProcAddress(handle, "D3DKMTEscape"));
    Functions::D3DKMTGetContextSchedulingPriority = reinterpret_cast<D3DKMTGetContextSchedulingPriority_t>(
        GetProcAddress(handle, "D3DKMTGetContextSchedulingPriority"));
    Functions::D3DKMTGetDeviceState =
        reinterpret_cast<D3DKMTGetDeviceState_t>(GetProcAddress(handle, "D3DKMTGetDeviceState"));
    Functions::D3DKMTGetDisplayModeList =
        reinterpret_cast<D3DKMTGetDisplayModeList_t>(GetProcAddress(handle, "D3DKMTGetDisplayModeList"));
    Functions::D3DKMTGetMultisampleMethodList =
        reinterpret_cast<D3DKMTGetMultisampleMethodList_t>(GetProcAddress(handle, "D3DKMTGetMultisampleMethodList"));
    Functions::D3DKMTGetRuntimeData =
        reinterpret_cast<D3DKMTGetRuntimeData_t>(GetProcAddress(handle, "D3DKMTGetRuntimeData"));
    Functions::D3DKMTGetSharedPrimaryHandle =
        reinterpret_cast<D3DKMTGetSharedPrimaryHandle_t>(GetProcAddress(handle, "D3DKMTGetSharedPrimaryHandle"));
    Functions::D3DKMTLock = reinterpret_cast<D3DKMTLock_t>(GetProcAddress(handle, "D3DKMTLock"));
    Functions::D3DKMTOpenAdapterFromHdc =
        reinterpret_cast<D3DKMTOpenAdapterFromHdc_t>(GetProcAddress(handle, "D3DKMTOpenAdapterFromHdc"));
    Functions::D3DKMTOpenResource =
        reinterpret_cast<D3DKMTOpenResource_t>(GetProcAddress(handle, "D3DKMTOpenResource"));
    Functions::D3DKMTPresent = reinterpret_cast<D3DKMTPresent_t>(GetProcAddress(handle, "D3DKMTPresent"));
    Functions::D3DKMTQueryAdapterInfo =
        reinterpret_cast<D3DKMTQueryAdapterInfo_t>(GetProcAddress(handle, "D3DKMTQueryAdapterInfo"));
    Functions::D3DKMTQueryAllocationResidency =
        reinterpret_cast<D3DKMTQueryAllocationResidency_t>(GetProcAddress(handle, "D3DKMTQueryAllocationResidency"));
    Functions::D3DKMTQueryResourceInfo =
        reinterpret_cast<D3DKMTQueryResourceInfo_t>(GetProcAddress(handle, "D3DKMTQueryResourceInfo"));
    Functions::D3DKMTRender = reinterpret_cast<D3DKMTRender_t>(GetProcAddress(handle, "D3DKMTRender"));
    Functions::D3DKMTSetAllocationPriority =
        reinterpret_cast<D3DKMTSetAllocationPriority_t>(GetProcAddress(handle, "D3DKMTSetAllocationPriority"));
    Functions::D3DKMTSetContextSchedulingPriority = reinterpret_cast<D3DKMTSetContextSchedulingPriority_t>(
        GetProcAddress(handle, "D3DKMTSetContextSchedulingPriority"));
    Functions::D3DKMTSetDisplayMode =
        reinterpret_cast<D3DKMTSetDisplayMode_t>(GetProcAddress(handle, "D3DKMTSetDisplayMode"));
    Functions::D3DKMTSetDisplayPrivateDriverFormat = reinterpret_cast<D3DKMTSetDisplayPrivateDriverFormat_t>(
        GetProcAddress(handle, "D3DKMTSetDisplayPrivateDriverFormat"));
    Functions::D3DKMTSetGammaRamp =
        reinterpret_cast<D3DKMTSetGammaRamp_t>(GetProcAddress(handle, "D3DKMTSetGammaRamp"));
    Functions::D3DKMTSetVidPnSourceOwner =
        reinterpret_cast<D3DKMTSetVidPnSourceOwner_t>(GetProcAddress(handle, "D3DKMTSetVidPnSourceOwner"));
    Functions::D3DKMTSignalSynchronizationObject = reinterpret_cast<D3DKMTSignalSynchronizationObject_t>(
        GetProcAddress(handle, "D3DKMTSignalSynchronizationObject"));
    Functions::D3DKMTUnlock = reinterpret_cast<D3DKMTUnlock_t>(GetProcAddress(handle, "D3DKMTUnlock"));
    Functions::D3DKMTWaitForSynchronizationObject = reinterpret_cast<D3DKMTWaitForSynchronizationObject_t>(
        GetProcAddress(handle, "D3DKMTWaitForSynchronizationObject"));
    Functions::D3DKMTWaitForVerticalBlankEvent =
        reinterpret_cast<D3DKMTWaitForVerticalBlankEvent_t>(GetProcAddress(handle, "D3DKMTWaitForVerticalBlankEvent"));
    Functions::D3DPerformance_BeginEvent =
        reinterpret_cast<D3DPerformance_BeginEvent_t>(GetProcAddress(handle, "D3DPerformance_BeginEvent"));
    Functions::D3DPerformance_EndEvent =
        reinterpret_cast<D3DPerformance_EndEvent_t>(GetProcAddress(handle, "D3DPerformance_EndEvent"));
    Functions::D3DPerformance_GetStatus =
        reinterpret_cast<D3DPerformance_GetStatus_t>(GetProcAddress(handle, "D3DPerformance_GetStatus"));
    Functions::D3DPerformance_SetMarker =
        reinterpret_cast<D3DPerformance_SetMarker_t>(GetProcAddress(handle, "D3DPerformance_SetMarker"));
    Functions::EnableFeatureLevelUpgrade =
        reinterpret_cast<EnableFeatureLevelUpgrade_t>(GetProcAddress(handle, "EnableFeatureLevelUpgrade"));
    Functions::OpenAdapter10 = reinterpret_cast<OpenAdapter10_t>(GetProcAddress(handle, "OpenAdapter10"));
    Functions::OpenAdapter10_2 = reinterpret_cast<OpenAdapter10_2_t>(GetProcAddress(handle, "OpenAdapter10_2"));

    return true;
}

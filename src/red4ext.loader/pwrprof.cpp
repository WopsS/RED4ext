#include "stdafx.hpp"
#include "pwrprof.hpp"

using CallNtPowerInformation_t = decltype(&CallNtPowerInformation);
using CanUserWritePwrScheme_t = decltype(&CanUserWritePwrScheme);
using DeletePwrScheme_t = decltype(&DeletePwrScheme);
using DevicePowerClose_t = decltype(&DevicePowerClose);
using DevicePowerEnumDevices_t = decltype(&DevicePowerEnumDevices);
using DevicePowerOpen_t = decltype(&DevicePowerOpen);
using DevicePowerSetDeviceState_t = decltype(&DevicePowerSetDeviceState);
using EnumPwrSchemes_t = decltype(&EnumPwrSchemes);
using GetActivePwrScheme_t = decltype(&GetActivePwrScheme);
using GetCurrentPowerPolicies_t = decltype(&GetCurrentPowerPolicies);
using GetPwrCapabilities_t = decltype(&GetPwrCapabilities);
using GetPwrDiskSpindownRange_t = decltype(&GetPwrDiskSpindownRange);
using IsAdminOverrideActive_t = decltype(&IsAdminOverrideActive);
using IsPwrHibernateAllowed_t = decltype(&IsPwrHibernateAllowed);
using IsPwrShutdownAllowed_t = decltype(&IsPwrShutdownAllowed);
using IsPwrSuspendAllowed_t = decltype(&IsPwrSuspendAllowed);
using PowerCanRestoreIndividualDefaultPowerScheme_t = decltype(&PowerCanRestoreIndividualDefaultPowerScheme);
using PowerCreatePossibleSetting_t = decltype(&PowerCreatePossibleSetting);
using PowerCreateSetting_t = decltype(&PowerCreateSetting);
using PowerDeleteScheme_t = decltype(&PowerDeleteScheme);
using PowerDeterminePlatformRole_t = decltype(&PowerDeterminePlatformRole);
using PowerDeterminePlatformRoleEx_t = decltype(&PowerDeterminePlatformRoleEx);
using PowerDuplicateScheme_t = decltype(&PowerDuplicateScheme);
using PowerEnumerate_t = decltype(&PowerEnumerate);
using PowerGetActiveScheme_t = decltype(&PowerGetActiveScheme);
using PowerImportPowerScheme_t = decltype(&PowerImportPowerScheme);
using PowerIsSettingRangeDefined_t = decltype(&PowerIsSettingRangeDefined);
using PowerOpenSystemPowerKey_t = decltype(&PowerOpenSystemPowerKey);
using PowerOpenUserPowerKey_t = decltype(&PowerOpenUserPowerKey);
using PowerReadACDefaultIndex_t = decltype(&PowerReadACDefaultIndex);
using PowerReadACValue_t = decltype(&PowerReadACValue);
using PowerReadACValueIndex_t = decltype(&PowerReadACValueIndex);
using PowerReadDCDefaultIndex_t = decltype(&PowerReadDCDefaultIndex);
using PowerReadDCValue_t = decltype(&PowerReadDCValue);
using PowerReadDCValueIndex_t = decltype(&PowerReadDCValueIndex);
using PowerReadDescription_t = decltype(&PowerReadDescription);
using PowerReadFriendlyName_t = decltype(&PowerReadFriendlyName);
using PowerReadIconResourceSpecifier_t = decltype(&PowerReadIconResourceSpecifier);
using PowerReadPossibleDescription_t = decltype(&PowerReadPossibleDescription);
using PowerReadPossibleFriendlyName_t = decltype(&PowerReadPossibleFriendlyName);
using PowerReadPossibleValue_t = decltype(&PowerReadPossibleValue);
using PowerReadSettingAttributes_t = decltype(&PowerReadSettingAttributes);
using PowerReadValueIncrement_t = decltype(&PowerReadValueIncrement);
using PowerReadValueMax_t = decltype(&PowerReadValueMax);
using PowerReadValueMin_t = decltype(&PowerReadValueMin);
using PowerReadValueUnitsSpecifier_t = decltype(&PowerReadValueUnitsSpecifier);
using PowerRegisterForEffectivePowerModeNotifications_t = decltype(&PowerRegisterForEffectivePowerModeNotifications);
using PowerRegisterSuspendResumeNotification_t = decltype(&PowerRegisterSuspendResumeNotification);
using PowerRemovePowerSetting_t = decltype(&PowerRemovePowerSetting);
using PowerReplaceDefaultPowerSchemes_t = decltype(&PowerReplaceDefaultPowerSchemes);
using PowerReportThermalEvent_t = decltype(&PowerReportThermalEvent);
using PowerRestoreDefaultPowerSchemes_t = decltype(&PowerRestoreDefaultPowerSchemes);
using PowerRestoreIndividualDefaultPowerScheme_t = decltype(&PowerRestoreIndividualDefaultPowerScheme);
using PowerSetActiveScheme_t = decltype(&PowerSetActiveScheme);
using PowerSettingAccessCheck_t = decltype(&PowerSettingAccessCheck);
using PowerSettingAccessCheckEx_t = decltype(&PowerSettingAccessCheckEx);
using PowerSettingRegisterNotification_t = decltype(&PowerSettingRegisterNotification);
using PowerSettingUnregisterNotification_t = decltype(&PowerSettingUnregisterNotification);
using PowerUnregisterFromEffectivePowerModeNotifications_t =
    decltype(&PowerUnregisterFromEffectivePowerModeNotifications);
using PowerUnregisterSuspendResumeNotification_t = decltype(&PowerUnregisterSuspendResumeNotification);
using PowerWriteACDefaultIndex_t = decltype(&PowerWriteACDefaultIndex);
using PowerWriteACValueIndex_t = decltype(&PowerWriteACValueIndex);
using PowerWriteDCDefaultIndex_t = decltype(&PowerWriteDCDefaultIndex);
using PowerWriteDCValueIndex_t = decltype(&PowerWriteDCValueIndex);
using PowerWriteDescription_t = decltype(&PowerWriteDescription);
using PowerWriteFriendlyName_t = decltype(&PowerWriteFriendlyName);
using PowerWriteIconResourceSpecifier_t = decltype(&PowerWriteIconResourceSpecifier);
using PowerWritePossibleDescription_t = decltype(&PowerWritePossibleDescription);
using PowerWritePossibleFriendlyName_t = decltype(&PowerWritePossibleFriendlyName);
using PowerWritePossibleValue_t = decltype(&PowerWritePossibleValue);
using PowerWriteSettingAttributes_t = decltype(&PowerWriteSettingAttributes);
using PowerWriteValueIncrement_t = decltype(&PowerWriteValueIncrement);
using PowerWriteValueMax_t = decltype(&PowerWriteValueMax);
using PowerWriteValueMin_t = decltype(&PowerWriteValueMin);
using PowerWriteValueUnitsSpecifier_t = decltype(&PowerWriteValueUnitsSpecifier);
using ReadGlobalPwrPolicy_t = decltype(&ReadGlobalPwrPolicy);
using ReadProcessorPwrScheme_t = decltype(&ReadProcessorPwrScheme);
using ReadPwrScheme_t = decltype(&ReadPwrScheme);
using SetActivePwrScheme_t = decltype(&SetActivePwrScheme);
using SetSuspendState_t = decltype(&SetSuspendState);
using ValidatePowerPolicies_t = decltype(&ValidatePowerPolicies);
using WriteGlobalPwrPolicy_t = decltype(&WriteGlobalPwrPolicy);
using WriteProcessorPwrScheme_t = decltype(&WriteProcessorPwrScheme);
using WritePwrScheme_t = decltype(&WritePwrScheme);

CallNtPowerInformation_t _CallNtPowerInformation;
CanUserWritePwrScheme_t _CanUserWritePwrScheme;
DeletePwrScheme_t _DeletePwrScheme;
DevicePowerClose_t _DevicePowerClose;
DevicePowerEnumDevices_t _DevicePowerEnumDevices;
DevicePowerOpen_t _DevicePowerOpen;
DevicePowerSetDeviceState_t _DevicePowerSetDeviceState;
EnumPwrSchemes_t _EnumPwrSchemes;
GetActivePwrScheme_t _GetActivePwrScheme;
GetCurrentPowerPolicies_t _GetCurrentPowerPolicies;
GetPwrCapabilities_t _GetPwrCapabilities;
GetPwrDiskSpindownRange_t _GetPwrDiskSpindownRange;
IsAdminOverrideActive_t _IsAdminOverrideActive;
IsPwrHibernateAllowed_t _IsPwrHibernateAllowed;
IsPwrShutdownAllowed_t _IsPwrShutdownAllowed;
IsPwrSuspendAllowed_t _IsPwrSuspendAllowed;
PowerCanRestoreIndividualDefaultPowerScheme_t _PowerCanRestoreIndividualDefaultPowerScheme;
PowerCreatePossibleSetting_t _PowerCreatePossibleSetting;
PowerCreateSetting_t _PowerCreateSetting;
PowerDeleteScheme_t _PowerDeleteScheme;
PowerDeterminePlatformRole_t _PowerDeterminePlatformRole;
PowerDeterminePlatformRoleEx_t _PowerDeterminePlatformRoleEx;
PowerDuplicateScheme_t _PowerDuplicateScheme;
PowerEnumerate_t _PowerEnumerate;
PowerGetActiveScheme_t _PowerGetActiveScheme;
PowerImportPowerScheme_t _PowerImportPowerScheme;
PowerIsSettingRangeDefined_t _PowerIsSettingRangeDefined;
PowerOpenSystemPowerKey_t _PowerOpenSystemPowerKey;
PowerOpenUserPowerKey_t _PowerOpenUserPowerKey;
PowerReadACDefaultIndex_t _PowerReadACDefaultIndex;
PowerReadACValue_t _PowerReadACValue;
PowerReadACValueIndex_t _PowerReadACValueIndex;
PowerReadDCDefaultIndex_t _PowerReadDCDefaultIndex;
PowerReadDCValue_t _PowerReadDCValue;
PowerReadDCValueIndex_t _PowerReadDCValueIndex;
PowerReadDescription_t _PowerReadDescription;
PowerReadFriendlyName_t _PowerReadFriendlyName;
PowerReadIconResourceSpecifier_t _PowerReadIconResourceSpecifier;
PowerReadPossibleDescription_t _PowerReadPossibleDescription;
PowerReadPossibleFriendlyName_t _PowerReadPossibleFriendlyName;
PowerReadPossibleValue_t _PowerReadPossibleValue;
PowerReadSettingAttributes_t _PowerReadSettingAttributes;
PowerReadValueIncrement_t _PowerReadValueIncrement;
PowerReadValueMax_t _PowerReadValueMax;
PowerReadValueMin_t _PowerReadValueMin;
PowerReadValueUnitsSpecifier_t _PowerReadValueUnitsSpecifier;
PowerRegisterForEffectivePowerModeNotifications_t _PowerRegisterForEffectivePowerModeNotifications;
PowerRegisterSuspendResumeNotification_t _PowerRegisterSuspendResumeNotification;
PowerRemovePowerSetting_t _PowerRemovePowerSetting;
PowerReplaceDefaultPowerSchemes_t _PowerReplaceDefaultPowerSchemes;
PowerReportThermalEvent_t _PowerReportThermalEvent;
PowerRestoreDefaultPowerSchemes_t _PowerRestoreDefaultPowerSchemes;
PowerRestoreIndividualDefaultPowerScheme_t _PowerRestoreIndividualDefaultPowerScheme;
PowerSetActiveScheme_t _PowerSetActiveScheme;
PowerSettingAccessCheck_t _PowerSettingAccessCheck;
PowerSettingAccessCheckEx_t _PowerSettingAccessCheckEx;
PowerSettingRegisterNotification_t _PowerSettingRegisterNotification;
PowerSettingUnregisterNotification_t _PowerSettingUnregisterNotification;
PowerUnregisterFromEffectivePowerModeNotifications_t _PowerUnregisterFromEffectivePowerModeNotifications;
PowerUnregisterSuspendResumeNotification_t _PowerUnregisterSuspendResumeNotification;
PowerWriteACDefaultIndex_t _PowerWriteACDefaultIndex;
PowerWriteACValueIndex_t _PowerWriteACValueIndex;
PowerWriteDCDefaultIndex_t _PowerWriteDCDefaultIndex;
PowerWriteDCValueIndex_t _PowerWriteDCValueIndex;
PowerWriteDescription_t _PowerWriteDescription;
PowerWriteFriendlyName_t _PowerWriteFriendlyName;
PowerWriteIconResourceSpecifier_t _PowerWriteIconResourceSpecifier;
PowerWritePossibleDescription_t _PowerWritePossibleDescription;
PowerWritePossibleFriendlyName_t _PowerWritePossibleFriendlyName;
PowerWritePossibleValue_t _PowerWritePossibleValue;
PowerWriteSettingAttributes_t _PowerWriteSettingAttributes;
PowerWriteValueIncrement_t _PowerWriteValueIncrement;
PowerWriteValueMax_t _PowerWriteValueMax;
PowerWriteValueMin_t _PowerWriteValueMin;
PowerWriteValueUnitsSpecifier_t _PowerWriteValueUnitsSpecifier;
ReadGlobalPwrPolicy_t _ReadGlobalPwrPolicy;
ReadProcessorPwrScheme_t _ReadProcessorPwrScheme;
ReadPwrScheme_t _ReadPwrScheme;
SetActivePwrScheme_t _SetActivePwrScheme;
SetSuspendState_t _SetSuspendState;
ValidatePowerPolicies_t _ValidatePowerPolicies;
WriteGlobalPwrPolicy_t _WriteGlobalPwrPolicy;
WriteProcessorPwrScheme_t _WriteProcessorPwrScheme;
WritePwrScheme_t _WritePwrScheme;

NTSTATUS WINAPI CallNtPowerInformation(_In_ POWER_INFORMATION_LEVEL InformationLevel,
                                       _In_reads_bytes_opt_(InputBufferLength) PVOID InputBuffer,
                                       _In_ ULONG InputBufferLength,
                                       _Out_writes_bytes_opt_(OutputBufferLength) PVOID OutputBuffer,
                                       _In_ ULONG OutputBufferLength)
{
    return _CallNtPowerInformation(InformationLevel, InputBuffer, InputBufferLength, OutputBuffer, OutputBufferLength);
}

STDAPI_(BOOLEAN) CanUserWritePwrScheme(VOID)
{
    return _CanUserWritePwrScheme();
}

STDAPI_(BOOLEAN) DeletePwrScheme(_In_ UINT uiID)
{
    return _DeletePwrScheme(uiID);
}

STDAPI_(BOOLEAN) DevicePowerClose(VOID)
{
    return _DevicePowerClose();
}

STDAPI_(BOOLEAN)
DevicePowerEnumDevices(_In_ ULONG QueryIndex, _In_ ULONG QueryInterpretationFlags, _In_ ULONG QueryFlags,
                       _Out_writes_bytes_opt_(*pBufferSize) PBYTE pReturnBuffer, _Inout_ PULONG pBufferSize)
{
    return _DevicePowerEnumDevices(QueryIndex, QueryInterpretationFlags, QueryFlags, pReturnBuffer, pBufferSize);
}

STDAPI_(BOOLEAN) DevicePowerOpen(_In_opt_ ULONG DebugMask)
{
    return _DevicePowerOpen(DebugMask);
}

STDAPI_(DWORD) DevicePowerSetDeviceState(_In_ LPCWSTR DeviceDescription, _In_ ULONG SetFlags, _In_opt_ PVOID SetData)
{
    return _DevicePowerSetDeviceState(DeviceDescription, SetFlags, SetData);
}

STDAPI_(BOOLEAN) EnumPwrSchemes(_In_ PWRSCHEMESENUMPROC lpfn, _In_ LPARAM lParam)
{
    return _EnumPwrSchemes(lpfn, lParam);
}

STDAPI_(BOOLEAN) GetActivePwrScheme(_Out_ PUINT puiID)
{
    return _GetActivePwrScheme(puiID);
}

STDAPI_(BOOLEAN)
GetCurrentPowerPolicies(_Out_ PGLOBAL_POWER_POLICY pGlobalPowerPolicy, _Out_ PPOWER_POLICY pPowerPolicy)
{
    return _GetCurrentPowerPolicies(pGlobalPowerPolicy, pPowerPolicy);
}

BOOLEAN WINAPI GetPwrCapabilities(_Out_ PSYSTEM_POWER_CAPABILITIES lpspc)
{
    return _GetPwrCapabilities(lpspc);
}

STDAPI_(BOOLEAN) GetPwrDiskSpindownRange(_Out_ PUINT puiMax, _Out_ PUINT puiMin)
{
    return _GetPwrDiskSpindownRange(puiMax, puiMin);
}

STDAPI_(BOOLEAN) IsAdminOverrideActive(_In_ PADMINISTRATOR_POWER_POLICY papp)
{
    return _IsAdminOverrideActive(papp);
}

STDAPI_(BOOLEAN) IsPwrHibernateAllowed(VOID)
{
    return _IsPwrHibernateAllowed();
}

STDAPI_(BOOLEAN) IsPwrShutdownAllowed(VOID)
{
    return _IsPwrShutdownAllowed();
}

STDAPI_(BOOLEAN) IsPwrSuspendAllowed(VOID)
{
    return _IsPwrSuspendAllowed();
}

STDAPI_(DWORD)
PowerCanRestoreIndividualDefaultPowerScheme(_In_ CONST GUID* SchemeGuid)
{
    return _PowerCanRestoreIndividualDefaultPowerScheme(SchemeGuid);
}

STDAPI_(DWORD)
PowerCreatePossibleSetting(_In_opt_ HKEY RootSystemPowerKey, _In_ CONST GUID* SubGroupOfPowerSettingsGuid,
                           _In_ CONST GUID* PowerSettingGuid, _In_ ULONG PossibleSettingIndex)
{
    return _PowerCreatePossibleSetting(RootSystemPowerKey, SubGroupOfPowerSettingsGuid, PowerSettingGuid,
                                       PossibleSettingIndex);
}

STDAPI_(DWORD)
PowerCreateSetting(_In_opt_ HKEY RootSystemPowerKey, _In_ CONST GUID* SubGroupOfPowerSettingsGuid,
                   _In_ CONST GUID* PowerSettingGuid)
{
    return _PowerCreateSetting(RootSystemPowerKey, SubGroupOfPowerSettingsGuid, PowerSettingGuid);
}

STDAPI_(DWORD)
PowerDeleteScheme(_In_opt_ HKEY RootPowerKey, _In_ CONST GUID* SchemeGuid)
{
    return _PowerDeleteScheme(RootPowerKey, SchemeGuid);
}

STDAPI_(POWER_PLATFORM_ROLE) PowerDeterminePlatformRole(VOID)
{
    return _PowerDeterminePlatformRole();
}

POWER_PLATFORM_ROLE WINAPI PowerDeterminePlatformRoleEx(_In_ ULONG Version)
{
    return _PowerDeterminePlatformRoleEx(Version);
}

STDAPI_(DWORD)
PowerDuplicateScheme(_In_opt_ HKEY RootPowerKey, _In_ const GUID* SourceSchemeGuid,
                     _Inout_ GUID** DestinationSchemeGuid)
{
    return _PowerDuplicateScheme(RootPowerKey, SourceSchemeGuid, DestinationSchemeGuid);
}

STDAPI_(DWORD)
PowerEnumerate(_In_opt_ HKEY RootPowerKey, _In_opt_ CONST GUID* SchemeGuid,
               _In_opt_ CONST GUID* SubGroupOfPowerSettingsGuid, _In_ POWER_DATA_ACCESSOR AccessFlags, _In_ ULONG Index,
               _Out_writes_bytes_opt_(*BufferSize) UCHAR* Buffer, _Inout_ DWORD* BufferSize)
{
    return _PowerEnumerate(RootPowerKey, SchemeGuid, SubGroupOfPowerSettingsGuid, AccessFlags, Index, Buffer,
                           BufferSize);
}

DWORD WINAPI PowerGetActiveScheme(_In_opt_ HKEY UserRootPowerKey, _Outptr_ GUID** ActivePolicyGuid)
{
    return _PowerGetActiveScheme(UserRootPowerKey, ActivePolicyGuid);
}

STDAPI_(DWORD)
PowerImportPowerScheme(_In_opt_ HKEY RootPowerKey, _In_ LPCWSTR ImportFileNamePath,
                       _Inout_ GUID** DestinationSchemeGuid)
{
    return _PowerImportPowerScheme(RootPowerKey, ImportFileNamePath, DestinationSchemeGuid);
}

STDAPI_(BOOLEAN)
PowerIsSettingRangeDefined(_In_opt_ CONST GUID* SubKeyGuid OPTIONAL, _In_opt_ CONST GUID* SettingGuid OPTIONAL)
{
    return _PowerIsSettingRangeDefined(SubKeyGuid, SettingGuid);
}

STDAPI_(DWORD)
PowerOpenSystemPowerKey(_Out_ HKEY* phSystemPowerKey, _In_ REGSAM Access, _In_ BOOL OpenExisting)
{
    return _PowerOpenSystemPowerKey(phSystemPowerKey, Access, OpenExisting);
}

STDAPI_(DWORD)
PowerOpenUserPowerKey(_Out_ HKEY* phUserPowerKey, _In_ REGSAM Access, _In_ BOOL OpenExisting)
{
    return _PowerOpenUserPowerKey(phUserPowerKey, Access, OpenExisting);
}

STDAPI_(DWORD)
PowerReadACDefaultIndex(_In_opt_ HKEY RootPowerKey, _In_ CONST GUID* SchemePersonalityGuid,
                        _In_opt_ CONST GUID* SubGroupOfPowerSettingsGuid OPTIONAL, _In_ CONST GUID* PowerSettingGuid,
                        _Out_ LPDWORD AcDefaultIndex)
{
    return _PowerReadACDefaultIndex(RootPowerKey, SchemePersonalityGuid, SubGroupOfPowerSettingsGuid, PowerSettingGuid,
                                    AcDefaultIndex);
}

DWORD WINAPI PowerReadACValue(_In_opt_ HKEY RootPowerKey, _In_opt_ CONST GUID* SchemeGuid,
                              _In_opt_ CONST GUID* SubGroupOfPowerSettingsGuid, _In_opt_ CONST GUID* PowerSettingGuid,
                              _Out_opt_ PULONG Type, _Out_writes_bytes_opt_(*BufferSize) LPBYTE Buffer,
                              _Inout_opt_ LPDWORD BufferSize)
{
    return _PowerReadACValue(RootPowerKey, SchemeGuid, SubGroupOfPowerSettingsGuid, PowerSettingGuid, Type, Buffer,
                             BufferSize);
}

STDAPI_(DWORD)
PowerReadACValueIndex(_In_opt_ HKEY RootPowerKey, _In_opt_ CONST GUID* SchemeGuid,
                      _In_opt_ CONST GUID* SubGroupOfPowerSettingsGuid, _In_opt_ CONST GUID* PowerSettingGuid,
                      _Out_ LPDWORD AcValueIndex)
{
    return _PowerReadACValueIndex(RootPowerKey, SchemeGuid, SubGroupOfPowerSettingsGuid, PowerSettingGuid,
                                  AcValueIndex);
}

STDAPI_(DWORD)
PowerReadDCDefaultIndex(_In_opt_ HKEY RootPowerKey, _In_ CONST GUID* SchemePersonalityGuid,
                        _In_opt_ CONST GUID* SubGroupOfPowerSettingsGuid, _In_ CONST GUID* PowerSettingGuid,
                        _Out_ LPDWORD DcDefaultIndex)
{
    return _PowerReadDCDefaultIndex(RootPowerKey, SchemePersonalityGuid, SubGroupOfPowerSettingsGuid, PowerSettingGuid,
                                    DcDefaultIndex);
}

DWORD WINAPI PowerReadDCValue(_In_opt_ HKEY RootPowerKey, _In_opt_ CONST GUID* SchemeGuid,
                              _In_opt_ CONST GUID* SubGroupOfPowerSettingsGuid, _In_opt_ CONST GUID* PowerSettingGuid,
                              _Out_opt_ PULONG Type, _Out_writes_bytes_opt_(*BufferSize) PUCHAR Buffer,
                              _Inout_ LPDWORD BufferSize)
{
    return _PowerReadDCValue(RootPowerKey, SchemeGuid, SubGroupOfPowerSettingsGuid, PowerSettingGuid, Type, Buffer,
                             BufferSize);
}

STDAPI_(DWORD)
PowerReadDCValueIndex(_In_opt_ HKEY RootPowerKey, _In_opt_ CONST GUID* SchemeGuid,
                      _In_opt_ CONST GUID* SubGroupOfPowerSettingsGuid, _In_opt_ CONST GUID* PowerSettingGuid,
                      _Out_ LPDWORD DcValueIndex)
{
    return _PowerReadDCValueIndex(RootPowerKey, SchemeGuid, SubGroupOfPowerSettingsGuid, PowerSettingGuid,
                                  DcValueIndex);
}

STDAPI_(DWORD)
PowerReadDescription(_In_opt_ HKEY RootPowerKey, _In_opt_ CONST GUID* SchemeGuid,
                     _In_opt_ CONST GUID* SubGroupOfPowerSettingsGuid, _In_opt_ CONST GUID* PowerSettingGuid,
                     _Out_writes_bytes_opt_(*BufferSize) PUCHAR Buffer, _Inout_ LPDWORD BufferSize)
{
    return _PowerReadDescription(RootPowerKey, SchemeGuid, SubGroupOfPowerSettingsGuid, PowerSettingGuid, Buffer,
                                 BufferSize);
}

STDAPI_(DWORD)
PowerReadFriendlyName(_In_opt_ HKEY RootPowerKey, _In_opt_ CONST GUID* SchemeGuid,
                      _In_opt_ CONST GUID* SubGroupOfPowerSettingsGuid, _In_opt_ CONST GUID* PowerSettingGuid,
                      _Out_writes_bytes_opt_(*BufferSize) PUCHAR Buffer, _Inout_ LPDWORD BufferSize)
{
    return _PowerReadFriendlyName(RootPowerKey, SchemeGuid, SubGroupOfPowerSettingsGuid, PowerSettingGuid, Buffer,
                                  BufferSize);
}

STDAPI_(DWORD)
PowerReadIconResourceSpecifier(_In_opt_ HKEY RootPowerKey, _In_opt_ CONST GUID* SchemeGuid,
                               _In_opt_ CONST GUID* SubGroupOfPowerSettingsGuid, _In_opt_ CONST GUID* PowerSettingGuid,
                               _Out_writes_bytes_opt_(*BufferSize) PUCHAR Buffer, _Inout_ LPDWORD BufferSize)
{
    return _PowerReadIconResourceSpecifier(RootPowerKey, SchemeGuid, SubGroupOfPowerSettingsGuid, PowerSettingGuid,
                                           Buffer, BufferSize);
}

STDAPI_(DWORD)
PowerReadPossibleDescription(_In_opt_ HKEY RootPowerKey, _In_opt_ CONST GUID* SubGroupOfPowerSettingsGuid,
                             _In_opt_ CONST GUID* PowerSettingGuid, _In_ ULONG PossibleSettingIndex,
                             _Out_writes_bytes_opt_(*BufferSize) PUCHAR Buffer, _Inout_ LPDWORD BufferSize)
{
    return _PowerReadPossibleDescription(RootPowerKey, SubGroupOfPowerSettingsGuid, PowerSettingGuid,
                                         PossibleSettingIndex, Buffer, BufferSize);
}

STDAPI_(DWORD)
PowerReadPossibleFriendlyName(_In_opt_ HKEY RootPowerKey, _In_opt_ CONST GUID* SubGroupOfPowerSettingsGuid,
                              _In_opt_ CONST GUID* PowerSettingGuid, _In_ ULONG PossibleSettingIndex,
                              _Out_writes_bytes_opt_(*BufferSize) PUCHAR Buffer, _Inout_ LPDWORD BufferSize)
{
    return _PowerReadPossibleFriendlyName(RootPowerKey, SubGroupOfPowerSettingsGuid, PowerSettingGuid,
                                          PossibleSettingIndex, Buffer, BufferSize);
}

STDAPI_(DWORD)
PowerReadPossibleValue(_In_opt_ HKEY RootPowerKey, _In_opt_ CONST GUID* SubGroupOfPowerSettingsGuid,
                       _In_opt_ CONST GUID* PowerSettingGuid, _Out_opt_ PULONG Type, _In_ ULONG PossibleSettingIndex,
                       _Out_writes_bytes_opt_(*BufferSize) PUCHAR Buffer, _Inout_ LPDWORD BufferSize)
{
    return _PowerReadPossibleValue(RootPowerKey, SubGroupOfPowerSettingsGuid, PowerSettingGuid, Type,
                                   PossibleSettingIndex, Buffer, BufferSize);
}

STDAPI_(DWORD) PowerReadSettingAttributes(_In_opt_ CONST GUID* SubGroupGuid, _In_opt_ CONST GUID* PowerSettingGuid)
{
    return _PowerReadSettingAttributes(SubGroupGuid, PowerSettingGuid);
}

STDAPI_(DWORD)
PowerReadValueIncrement(_In_opt_ HKEY RootPowerKey, _In_opt_ CONST GUID* SubGroupOfPowerSettingsGuid,
                        _In_opt_ CONST GUID* PowerSettingGuid, _Out_ LPDWORD ValueIncrement)
{
    return _PowerReadValueIncrement(RootPowerKey, SubGroupOfPowerSettingsGuid, PowerSettingGuid, ValueIncrement);
}

STDAPI_(DWORD)
PowerReadValueMax(_In_opt_ HKEY RootPowerKey, _In_opt_ CONST GUID* SubGroupOfPowerSettingsGuid,
                  _In_opt_ CONST GUID* PowerSettingGuid, _Out_ LPDWORD ValueMaximum)
{
    return _PowerReadValueMax(RootPowerKey, SubGroupOfPowerSettingsGuid, PowerSettingGuid, ValueMaximum);
}

STDAPI_(DWORD)
PowerReadValueMin(_In_opt_ HKEY RootPowerKey, _In_opt_ CONST GUID* SubGroupOfPowerSettingsGuid,
                  _In_opt_ CONST GUID* PowerSettingGuid, _Out_ LPDWORD ValueMinimum)
{
    return _PowerReadValueMin(RootPowerKey, SubGroupOfPowerSettingsGuid, PowerSettingGuid, ValueMinimum);
}

STDAPI_(DWORD)
PowerReadValueUnitsSpecifier(_In_opt_ HKEY RootPowerKey, _In_opt_ CONST GUID* SubGroupOfPowerSettingsGuid,
                             _In_opt_ CONST GUID* PowerSettingGuid, _Out_writes_bytes_opt_(*BufferSize) UCHAR* Buffer,
                             _Inout_ LPDWORD BufferSize)
{
    return _PowerReadValueUnitsSpecifier(RootPowerKey, SubGroupOfPowerSettingsGuid, PowerSettingGuid, Buffer,
                                         BufferSize);
}

_Must_inspect_result_ HRESULT WINAPI
PowerRegisterForEffectivePowerModeNotifications(_In_ ULONG Version, _In_ EFFECTIVE_POWER_MODE_CALLBACK* Callback,
                                                _In_opt_ VOID* Context, _Outptr_ VOID** RegistrationHandle)
{
    return _PowerRegisterForEffectivePowerModeNotifications(Version, Callback, Context, RegistrationHandle);
}

DWORD WINAPI PowerRegisterSuspendResumeNotification(_In_ DWORD Flags, _In_ HANDLE Recipient,
                                                    _Out_ PHPOWERNOTIFY RegistrationHandle)
{
    return _PowerRegisterSuspendResumeNotification(Flags, Recipient, RegistrationHandle);
}

STDAPI_(DWORD) PowerRemovePowerSetting(_In_ CONST GUID* PowerSettingSubKeyGuid, _In_ CONST GUID* PowerSettingGuid)
{
    return _PowerRemovePowerSetting(PowerSettingSubKeyGuid, PowerSettingGuid);
}

STDAPI_(DWORD) PowerReplaceDefaultPowerSchemes(VOID)
{
    return _PowerReplaceDefaultPowerSchemes();
}

STDAPI_(DWORD) PowerReportThermalEvent(_In_ PTHERMAL_EVENT Event)
{
    return _PowerReportThermalEvent(Event);
}

STDAPI_(DWORD) PowerRestoreDefaultPowerSchemes(VOID)
{
    return _PowerRestoreDefaultPowerSchemes();
}

STDAPI_(DWORD) PowerRestoreIndividualDefaultPowerScheme(_In_ CONST GUID* SchemeGuid)
{
    return _PowerRestoreIndividualDefaultPowerScheme(SchemeGuid);
}

DWORD WINAPI PowerSetActiveScheme(_In_opt_ HKEY UserRootPowerKey, _In_opt_ CONST GUID* SchemeGuid)
{
    return _PowerSetActiveScheme(UserRootPowerKey, SchemeGuid);
}

STDAPI_(DWORD) PowerSettingAccessCheck(_In_ POWER_DATA_ACCESSOR AccessFlags, _In_opt_ CONST GUID* PowerGuid)
{
    return _PowerSettingAccessCheck(AccessFlags, PowerGuid);
}

STDAPI_(DWORD)
PowerSettingAccessCheckEx(_In_ POWER_DATA_ACCESSOR AccessFlags, _In_opt_ CONST GUID* PowerGuid, _In_ REGSAM AccessType)
{
    return _PowerSettingAccessCheckEx(AccessFlags, PowerGuid, AccessType);
}

DWORD WINAPI PowerSettingRegisterNotification(_In_ LPCGUID SettingGuid, _In_ DWORD Flags, _In_ HANDLE Recipient,
                                              _Out_ PHPOWERNOTIFY RegistrationHandle)
{
    return _PowerSettingRegisterNotification(SettingGuid, Flags, Recipient, RegistrationHandle);
}

DWORD WINAPI PowerSettingUnregisterNotification(_Inout_ HPOWERNOTIFY RegistrationHandle)
{
    return _PowerSettingUnregisterNotification(RegistrationHandle);
}

HRESULT WINAPI PowerUnregisterFromEffectivePowerModeNotifications(_In_ VOID* RegistrationHandle)
{
    return _PowerUnregisterFromEffectivePowerModeNotifications(RegistrationHandle);
}

DWORD WINAPI PowerUnregisterSuspendResumeNotification(_Inout_ HPOWERNOTIFY RegistrationHandle)
{
    return _PowerUnregisterSuspendResumeNotification(RegistrationHandle);
}

STDAPI_(DWORD)
PowerWriteACDefaultIndex(_In_opt_ HKEY RootSystemPowerKey, _In_ CONST GUID* SchemePersonalityGuid,
                         _In_opt_ CONST GUID* SubGroupOfPowerSettingsGuid, _In_ CONST GUID* PowerSettingGuid,
                         _In_ DWORD DefaultAcIndex)
{
    return _PowerWriteACDefaultIndex(RootSystemPowerKey, SchemePersonalityGuid, SubGroupOfPowerSettingsGuid,
                                     PowerSettingGuid, DefaultAcIndex);
}

DWORD WINAPI PowerWriteACValueIndex(_In_opt_ HKEY RootPowerKey, _In_ CONST GUID* SchemeGuid,
                                    _In_opt_ CONST GUID* SubGroupOfPowerSettingsGuid,
                                    _In_opt_ CONST GUID* PowerSettingGuid, _In_ DWORD AcValueIndex)
{
    return _PowerWriteACValueIndex(RootPowerKey, SchemeGuid, SubGroupOfPowerSettingsGuid, PowerSettingGuid,
                                   AcValueIndex);
}

STDAPI_(DWORD)
PowerWriteDCDefaultIndex(_In_opt_ HKEY RootSystemPowerKey, _In_ CONST GUID* SchemePersonalityGuid,
                         _In_opt_ CONST GUID* SubGroupOfPowerSettingsGuid, _In_ CONST GUID* PowerSettingGuid,
                         _In_ DWORD DefaultDcIndex)
{
    return _PowerWriteDCDefaultIndex(RootSystemPowerKey, SchemePersonalityGuid, SubGroupOfPowerSettingsGuid,
                                     PowerSettingGuid, DefaultDcIndex);
}

DWORD WINAPI PowerWriteDCValueIndex(_In_opt_ HKEY RootPowerKey, _In_ CONST GUID* SchemeGuid,
                                    _In_opt_ CONST GUID* SubGroupOfPowerSettingsGuid,
                                    _In_opt_ CONST GUID* PowerSettingGuid, _In_ DWORD DcValueIndex)
{
    return _PowerWriteDCValueIndex(RootPowerKey, SchemeGuid, SubGroupOfPowerSettingsGuid, PowerSettingGuid,
                                   DcValueIndex);
}

STDAPI_(DWORD)
PowerWriteDescription(_In_opt_ HKEY RootPowerKey, _In_ CONST GUID* SchemeGuid,
                      _In_opt_ CONST GUID* SubGroupOfPowerSettingsGuid, _In_opt_ CONST GUID* PowerSettingGuid,
                      _In_reads_bytes_(BufferSize) UCHAR* Buffer, _In_ DWORD BufferSize)
{
    return _PowerWriteDescription(RootPowerKey, SchemeGuid, SubGroupOfPowerSettingsGuid, PowerSettingGuid, Buffer,
                                  BufferSize);
}

STDAPI_(DWORD)
PowerWriteFriendlyName(_In_opt_ HKEY RootPowerKey, _In_ CONST GUID* SchemeGuid,
                       _In_opt_ CONST GUID* SubGroupOfPowerSettingsGuid, _In_opt_ CONST GUID* PowerSettingGuid,
                       _In_reads_bytes_(BufferSize) UCHAR* Buffer, _In_ DWORD BufferSize)
{
    return _PowerWriteFriendlyName(RootPowerKey, SchemeGuid, SubGroupOfPowerSettingsGuid, PowerSettingGuid, Buffer,
                                   BufferSize);
}

STDAPI_(DWORD)
PowerWriteIconResourceSpecifier(_In_opt_ HKEY RootPowerKey, _In_ CONST GUID* SchemeGuid,
                                _In_opt_ CONST GUID* SubGroupOfPowerSettingsGuid, _In_opt_ CONST GUID* PowerSettingGuid,
                                _In_reads_bytes_(BufferSize) UCHAR* Buffer, _In_ DWORD BufferSize)
{
    return _PowerWriteIconResourceSpecifier(RootPowerKey, SchemeGuid, SubGroupOfPowerSettingsGuid, PowerSettingGuid,
                                            Buffer, BufferSize);
}

STDAPI_(DWORD)
PowerWritePossibleDescription(_In_opt_ HKEY RootPowerKey, _In_opt_ CONST GUID* SubGroupOfPowerSettingsGuid,
                              _In_opt_ CONST GUID* PowerSettingGuid, _In_ ULONG PossibleSettingIndex,
                              _In_reads_bytes_(BufferSize) UCHAR* Buffer, _In_ DWORD BufferSize)
{
    return _PowerWritePossibleDescription(RootPowerKey, SubGroupOfPowerSettingsGuid, PowerSettingGuid,
                                          PossibleSettingIndex, Buffer, BufferSize);
}

STDAPI_(DWORD)
PowerWritePossibleFriendlyName(_In_opt_ HKEY RootPowerKey, _In_opt_ CONST GUID* SubGroupOfPowerSettingsGuid,
                               _In_opt_ CONST GUID* PowerSettingGuid, _In_ ULONG PossibleSettingIndex,
                               _In_reads_bytes_(BufferSize) UCHAR* Buffer, _In_ DWORD BufferSize)
{
    return _PowerWritePossibleFriendlyName(RootPowerKey, SubGroupOfPowerSettingsGuid, PowerSettingGuid,
                                           PossibleSettingIndex, Buffer, BufferSize);
}

STDAPI_(DWORD)
PowerWritePossibleValue(_In_opt_ HKEY RootPowerKey, _In_opt_ CONST GUID* SubGroupOfPowerSettingsGuid,
                        _In_opt_ CONST GUID* PowerSettingGuid, _In_ ULONG Type, _In_ ULONG PossibleSettingIndex,
                        _In_reads_bytes_(BufferSize) UCHAR* Buffer, _In_ DWORD BufferSize)
{
    return _PowerWritePossibleValue(RootPowerKey, SubGroupOfPowerSettingsGuid, PowerSettingGuid, Type,
                                    PossibleSettingIndex, Buffer, BufferSize);
}

STDAPI_(DWORD)
PowerWriteSettingAttributes(_In_opt_ CONST GUID* SubGroupGuid, _In_opt_ CONST GUID* PowerSettingGuid,
                            _In_ DWORD Attributes)
{
    return _PowerWriteSettingAttributes(SubGroupGuid, PowerSettingGuid, Attributes);
}

STDAPI_(DWORD)
PowerWriteValueIncrement(_In_opt_ HKEY RootPowerKey, _In_opt_ CONST GUID* SubGroupOfPowerSettingsGuid,
                         _In_opt_ CONST GUID* PowerSettingGuid, _In_ DWORD ValueIncrement)
{
    return _PowerWriteValueIncrement(RootPowerKey, SubGroupOfPowerSettingsGuid, PowerSettingGuid, ValueIncrement);
}

STDAPI_(DWORD)
PowerWriteValueMax(_In_opt_ HKEY RootPowerKey, _In_opt_ CONST GUID* SubGroupOfPowerSettingsGuid,
                   _In_opt_ CONST GUID* PowerSettingGuid, _In_ DWORD ValueMaximum)
{
    return _PowerWriteValueMax(RootPowerKey, SubGroupOfPowerSettingsGuid, PowerSettingGuid, ValueMaximum);
}

STDAPI_(DWORD)
PowerWriteValueMin(_In_opt_ HKEY RootPowerKey, _In_opt_ CONST GUID* SubGroupOfPowerSettingsGuid,
                   _In_opt_ CONST GUID* PowerSettingGuid, _In_ DWORD ValueMinimum)
{
    return _PowerWriteValueMin(RootPowerKey, SubGroupOfPowerSettingsGuid, PowerSettingGuid, ValueMinimum);
}

STDAPI_(DWORD)
PowerWriteValueUnitsSpecifier(_In_opt_ HKEY RootPowerKey, _In_opt_ CONST GUID* SubGroupOfPowerSettingsGuid,
                              _In_opt_ CONST GUID* PowerSettingGuid, _In_reads_bytes_(BufferSize) UCHAR* Buffer,
                              _In_ DWORD BufferSize)
{
    return _PowerWriteValueUnitsSpecifier(RootPowerKey, SubGroupOfPowerSettingsGuid, PowerSettingGuid, Buffer,
                                          BufferSize);
}

STDAPI_(BOOLEAN) ReadGlobalPwrPolicy(_In_ PGLOBAL_POWER_POLICY pGlobalPowerPolicy)
{
    return _ReadGlobalPwrPolicy(pGlobalPowerPolicy);
}

STDAPI_(BOOLEAN)
ReadProcessorPwrScheme(_In_ UINT uiID, _Out_ PMACHINE_PROCESSOR_POWER_POLICY pMachineProcessorPowerPolicy)
{
    return _ReadProcessorPwrScheme(uiID, pMachineProcessorPowerPolicy);
}

STDAPI_(BOOLEAN) ReadPwrScheme(_In_ UINT uiID, _Out_ PPOWER_POLICY pPowerPolicy)
{
    return _ReadPwrScheme(uiID, pPowerPolicy);
}

STDAPI_(BOOLEAN)
SetActivePwrScheme(_In_ UINT uiID, _In_opt_ PGLOBAL_POWER_POLICY pGlobalPowerPolicy,
                   _In_opt_ PPOWER_POLICY pPowerPolicy)
{
    return _SetActivePwrScheme(uiID, pGlobalPowerPolicy, pPowerPolicy);
}

STDAPI_(BOOLEAN) SetSuspendState(_In_ BOOLEAN bHibernate, _In_ BOOLEAN bForce, _In_ BOOLEAN bWakeupEventsDisabled)
{
    return _SetSuspendState(bHibernate, bForce, bWakeupEventsDisabled);
}

STDAPI_(BOOLEAN)
ValidatePowerPolicies(_Inout_opt_ PGLOBAL_POWER_POLICY pGlobalPowerPolicy, _Inout_opt_ PPOWER_POLICY pPowerPolicy)
{
    return _ValidatePowerPolicies(pGlobalPowerPolicy, pPowerPolicy);
}

STDAPI_(BOOLEAN) WriteGlobalPwrPolicy(_In_ PGLOBAL_POWER_POLICY pGlobalPowerPolicy)
{
    return _WriteGlobalPwrPolicy(pGlobalPowerPolicy);
}

STDAPI_(BOOLEAN)
WriteProcessorPwrScheme(_In_ UINT uiID, _In_ PMACHINE_PROCESSOR_POWER_POLICY pMachineProcessorPowerPolicy)
{
    return _WriteProcessorPwrScheme(uiID, pMachineProcessorPowerPolicy);
}

STDAPI_(BOOLEAN)
WritePwrScheme(_In_ PUINT puiID, _In_ LPCWSTR lpszSchemeName, _In_opt_ LPCWSTR lpszDescription,
               _In_ PPOWER_POLICY lpScheme)
{
    return _WritePwrScheme(puiID, lpszSchemeName, lpszDescription, lpScheme);
}

/*
 * These functions are undocumented, hopefully the compiler will generate a jmp instruction for them.
 */

using GUIDFormatToGlobalPowerPolicy_t = void (*)();
using GUIDFormatToPowerPolicy_t = void (*)();
using LoadCurrentPwrScheme_t = void (*)();
using MergeLegacyPwrScheme_t = void (*)();
using PowerApplyPowerRequestOverride_t = void (*)();
using PowerApplySettingChanges_t = void (*)();
using PowerClearUserAwayPrediction_t = void (*)();
using PowerCloseEnvironmentalMonitor_t = void (*)();
using PowerCloseLimitsMitigation_t = void (*)();
using PowerCloseLimitsPolicy_t = void (*)();
using PowerDebugDifPowerPolicies_t = void (*)();
using PowerDebugDifSystemPowerPolicies_t = void (*)();
using PowerDebugDumpPowerPolicy_t = void (*)();
using PowerDebugDumpPowerScheme_t = void (*)();
using PowerDebugDumpSystemPowerCapabilities_t = void (*)();
using PowerDebugDumpSystemPowerPolicy_t = void (*)();
using PowerGetActualOverlayScheme_t = void (*)();
using PowerGetAdaptiveStandbyDiagnostics_t = void (*)();
using PowerGetEffectiveOverlayScheme_t = void (*)();
using PowerGetOverlaySchemes_t = void (*)();
using PowerGetUserAwayMinPredictionConfidence_t = void (*)();
using PowerInformationWithPrivileges_t = void (*)();
using PowerPolicyToGUIDFormat_t = void (*)();
using PowerReadACValueIndexEx_t = void (*)();
using PowerReadDCValueIndexEx_t = void (*)();
using PowerReadSecurityDescriptor_t = void (*)();
using PowerReapplyActiveScheme_t = void (*)();
using PowerRegisterEnvironmentalMonitor_t = void (*)();
using PowerRegisterLimitsMitigation_t = void (*)();
using PowerRegisterLimitsPolicy_t = void (*)();
using PowerReportLimitsEvent_t = void (*)();
using PowerRestoreACDefaultIndex_t = void (*)();
using PowerRestoreDCDefaultIndex_t = void (*)();
using PowerSetActiveOverlayScheme_t = void (*)();
using PowerSetAlsBrightnessOffset_t = void (*)();
using PowerSetBrightnessAndTransitionTimes_t = void (*)();
using PowerSetUserAwayPrediction_t = void (*)();
using PowerSettingRegisterNotificationEx_t = void (*)();
using PowerUpdateEnvironmentalMonitorState_t = void (*)();
using PowerUpdateEnvironmentalMonitorThresholds_t = void (*)();
using PowerUpdateLimitsMitigation_t = void (*)();
using PowerWriteSecurityDescriptor_t = void (*)();

GUIDFormatToGlobalPowerPolicy_t _GUIDFormatToGlobalPowerPolicy;
GUIDFormatToPowerPolicy_t _GUIDFormatToPowerPolicy;
LoadCurrentPwrScheme_t _LoadCurrentPwrScheme;
MergeLegacyPwrScheme_t _MergeLegacyPwrScheme;
PowerApplyPowerRequestOverride_t _PowerApplyPowerRequestOverride;
PowerApplySettingChanges_t _PowerApplySettingChanges;
PowerClearUserAwayPrediction_t _PowerClearUserAwayPrediction;
PowerCloseEnvironmentalMonitor_t _PowerCloseEnvironmentalMonitor;
PowerCloseLimitsMitigation_t _PowerCloseLimitsMitigation;
PowerCloseLimitsPolicy_t _PowerCloseLimitsPolicy;
PowerDebugDifPowerPolicies_t _PowerDebugDifPowerPolicies;
PowerDebugDifSystemPowerPolicies_t _PowerDebugDifSystemPowerPolicies;
PowerDebugDumpPowerPolicy_t _PowerDebugDumpPowerPolicy;
PowerDebugDumpPowerScheme_t _PowerDebugDumpPowerScheme;
PowerDebugDumpSystemPowerCapabilities_t _PowerDebugDumpSystemPowerCapabilities;
PowerDebugDumpSystemPowerPolicy_t _PowerDebugDumpSystemPowerPolicy;
PowerGetActualOverlayScheme_t _PowerGetActualOverlayScheme;
PowerGetAdaptiveStandbyDiagnostics_t _PowerGetAdaptiveStandbyDiagnostics;
PowerGetEffectiveOverlayScheme_t _PowerGetEffectiveOverlayScheme;
PowerGetOverlaySchemes_t _PowerGetOverlaySchemes;
PowerGetUserAwayMinPredictionConfidence_t _PowerGetUserAwayMinPredictionConfidence;
PowerInformationWithPrivileges_t _PowerInformationWithPrivileges;
PowerPolicyToGUIDFormat_t _PowerPolicyToGUIDFormat;
PowerReadACValueIndexEx_t _PowerReadACValueIndexEx;
PowerReadDCValueIndexEx_t _PowerReadDCValueIndexEx;
PowerReadSecurityDescriptor_t _PowerReadSecurityDescriptor;
PowerReapplyActiveScheme_t _PowerReapplyActiveScheme;
PowerRegisterEnvironmentalMonitor_t _PowerRegisterEnvironmentalMonitor;
PowerRegisterLimitsMitigation_t _PowerRegisterLimitsMitigation;
PowerRegisterLimitsPolicy_t _PowerRegisterLimitsPolicy;
PowerReportLimitsEvent_t _PowerReportLimitsEvent;
PowerRestoreACDefaultIndex_t _PowerRestoreACDefaultIndex;
PowerRestoreDCDefaultIndex_t _PowerRestoreDCDefaultIndex;
PowerSetActiveOverlayScheme_t _PowerSetActiveOverlayScheme;
PowerSetAlsBrightnessOffset_t _PowerSetAlsBrightnessOffset;
PowerSetBrightnessAndTransitionTimes_t _PowerSetBrightnessAndTransitionTimes;
PowerSetUserAwayPrediction_t _PowerSetUserAwayPrediction;
PowerSettingRegisterNotificationEx_t _PowerSettingRegisterNotificationEx;
PowerUpdateEnvironmentalMonitorState_t _PowerUpdateEnvironmentalMonitorState;
PowerUpdateEnvironmentalMonitorThresholds_t _PowerUpdateEnvironmentalMonitorThresholds;
PowerUpdateLimitsMitigation_t _PowerUpdateLimitsMitigation;
PowerWriteSecurityDescriptor_t _PowerWriteSecurityDescriptor;

void GUIDFormatToGlobalPowerPolicy()
{
    _GUIDFormatToGlobalPowerPolicy();
}

void GUIDFormatToPowerPolicy()
{
    _GUIDFormatToPowerPolicy();
}

void LoadCurrentPwrScheme()
{
    _LoadCurrentPwrScheme();
}

void MergeLegacyPwrScheme()
{
    _MergeLegacyPwrScheme();
}

void PowerApplyPowerRequestOverride()
{
    _PowerApplyPowerRequestOverride();
}

void PowerApplySettingChanges()
{
    _PowerApplySettingChanges();
}

void PowerClearUserAwayPrediction()
{
    _PowerClearUserAwayPrediction();
}

void PowerCloseEnvironmentalMonitor()
{
    _PowerCloseEnvironmentalMonitor();
}

void PowerCloseLimitsMitigation()
{
    _PowerCloseLimitsMitigation();
}

void PowerCloseLimitsPolicy()
{
    _PowerCloseLimitsPolicy();
}

void PowerDebugDifPowerPolicies()
{
    _PowerDebugDifPowerPolicies();
}

void PowerDebugDifSystemPowerPolicies()
{
    _PowerDebugDifSystemPowerPolicies();
}

void PowerDebugDumpPowerPolicy()
{
    _PowerDebugDumpPowerPolicy();
}

void PowerDebugDumpPowerScheme()
{
    _PowerDebugDumpPowerScheme();
}

void PowerDebugDumpSystemPowerCapabilities()
{
    _PowerDebugDumpSystemPowerCapabilities();
}

void PowerDebugDumpSystemPowerPolicy()
{
    _PowerDebugDumpSystemPowerPolicy();
}

void PowerGetActualOverlayScheme()
{
    _PowerGetActualOverlayScheme();
}

void PowerGetAdaptiveStandbyDiagnostics()
{
    _PowerGetAdaptiveStandbyDiagnostics();
}

void PowerGetEffectiveOverlayScheme()
{
    _PowerGetEffectiveOverlayScheme();
}

void PowerGetOverlaySchemes()
{
    _PowerGetOverlaySchemes();
}

void PowerGetUserAwayMinPredictionConfidence()
{
    _PowerGetUserAwayMinPredictionConfidence();
}

void PowerInformationWithPrivileges()
{
    _PowerInformationWithPrivileges();
}

void PowerPolicyToGUIDFormat()
{
    _PowerPolicyToGUIDFormat();
}

void PowerReadACValueIndexEx()
{
    _PowerReadACValueIndexEx();
}

void PowerReadDCValueIndexEx()
{
    _PowerReadDCValueIndexEx();
}

void PowerReadSecurityDescriptor()
{
    _PowerReadSecurityDescriptor();
}

void PowerReapplyActiveScheme()
{
    _PowerReapplyActiveScheme();
}

void PowerRegisterEnvironmentalMonitor()
{
    _PowerRegisterEnvironmentalMonitor();
}

void PowerRegisterLimitsMitigation()
{
    _PowerRegisterLimitsMitigation();
}

void PowerRegisterLimitsPolicy()
{
    _PowerRegisterLimitsPolicy();
}

void PowerReportLimitsEvent()
{
    _PowerReportLimitsEvent();
}

void PowerRestoreACDefaultIndex()
{
    _PowerRestoreACDefaultIndex();
}

void PowerRestoreDCDefaultIndex()
{
    _PowerRestoreDCDefaultIndex();
}

void PowerSetActiveOverlayScheme()
{
    _PowerSetActiveOverlayScheme();
}

void PowerSetAlsBrightnessOffset()
{
    _PowerSetAlsBrightnessOffset();
}

void PowerSetBrightnessAndTransitionTimes()
{
    _PowerSetBrightnessAndTransitionTimes();
}

void PowerSetUserAwayPrediction()
{
    _PowerSetUserAwayPrediction();
}

void PowerSettingRegisterNotificationEx()
{
    _PowerSettingRegisterNotificationEx();
}

void PowerUpdateEnvironmentalMonitorState()
{
    _PowerUpdateEnvironmentalMonitorState();
}

void PowerUpdateEnvironmentalMonitorThresholds()
{
    _PowerUpdateEnvironmentalMonitorThresholds();
}

void PowerUpdateLimitsMitigation()
{
    _PowerUpdateLimitsMitigation();
}

void PowerWriteSecurityDescriptor()
{
    _PowerWriteSecurityDescriptor();
}

bool LoadOriginal()
{
    wil::unique_cotaskmem_string rawPath;
    if (FAILED(SHGetKnownFolderPath(FOLDERID_System, KF_FLAG_DEFAULT, nullptr, &rawPath)))
    {
        return false;
    }

    constexpr auto dllName = "powrprof.dll";

    std::filesystem::path dll = rawPath.get();
    dll /= dllName;

    auto handle = LoadLibrary(dll.c_str());
    if (!handle)
    {
        return false;
    }

    _CallNtPowerInformation =
        reinterpret_cast<CallNtPowerInformation_t>(GetProcAddress(handle, "CallNtPowerInformation"));
    _CanUserWritePwrScheme = reinterpret_cast<CanUserWritePwrScheme_t>(GetProcAddress(handle, "CanUserWritePwrScheme"));
    _DeletePwrScheme = reinterpret_cast<DeletePwrScheme_t>(GetProcAddress(handle, "DeletePwrScheme"));
    _DevicePowerClose = reinterpret_cast<DevicePowerClose_t>(GetProcAddress(handle, "DevicePowerClose"));
    _DevicePowerEnumDevices =
        reinterpret_cast<DevicePowerEnumDevices_t>(GetProcAddress(handle, "DevicePowerEnumDevices"));
    _DevicePowerOpen = reinterpret_cast<DevicePowerOpen_t>(GetProcAddress(handle, "DevicePowerOpen"));
    _DevicePowerSetDeviceState =
        reinterpret_cast<DevicePowerSetDeviceState_t>(GetProcAddress(handle, "DevicePowerSetDeviceState"));
    _EnumPwrSchemes = reinterpret_cast<EnumPwrSchemes_t>(GetProcAddress(handle, "EnumPwrSchemes"));
    _GetActivePwrScheme = reinterpret_cast<GetActivePwrScheme_t>(GetProcAddress(handle, "GetActivePwrScheme"));
    _GetCurrentPowerPolicies =
        reinterpret_cast<GetCurrentPowerPolicies_t>(GetProcAddress(handle, "GetCurrentPowerPolicies"));
    _GetPwrCapabilities = reinterpret_cast<GetPwrCapabilities_t>(GetProcAddress(handle, "GetPwrCapabilities"));
    _GetPwrDiskSpindownRange =
        reinterpret_cast<GetPwrDiskSpindownRange_t>(GetProcAddress(handle, "GetPwrDiskSpindownRange"));
    _IsAdminOverrideActive = reinterpret_cast<IsAdminOverrideActive_t>(GetProcAddress(handle, "IsAdminOverrideActive"));
    _IsPwrHibernateAllowed = reinterpret_cast<IsPwrHibernateAllowed_t>(GetProcAddress(handle, "IsPwrHibernateAllowed"));
    _IsPwrShutdownAllowed = reinterpret_cast<IsPwrShutdownAllowed_t>(GetProcAddress(handle, "IsPwrShutdownAllowed"));
    _IsPwrSuspendAllowed = reinterpret_cast<IsPwrSuspendAllowed_t>(GetProcAddress(handle, "IsPwrSuspendAllowed"));
    _PowerCanRestoreIndividualDefaultPowerScheme = reinterpret_cast<PowerCanRestoreIndividualDefaultPowerScheme_t>(
        GetProcAddress(handle, "PowerCanRestoreIndividualDefaultPowerScheme"));
    _PowerCreatePossibleSetting =
        reinterpret_cast<PowerCreatePossibleSetting_t>(GetProcAddress(handle, "PowerCreatePossibleSetting"));
    _PowerCreateSetting = reinterpret_cast<PowerCreateSetting_t>(GetProcAddress(handle, "PowerCreateSetting"));
    _PowerDeleteScheme = reinterpret_cast<PowerDeleteScheme_t>(GetProcAddress(handle, "PowerDeleteScheme"));
    _PowerDeterminePlatformRole =
        reinterpret_cast<PowerDeterminePlatformRole_t>(GetProcAddress(handle, "PowerDeterminePlatformRole"));
    _PowerDeterminePlatformRoleEx =
        reinterpret_cast<PowerDeterminePlatformRoleEx_t>(GetProcAddress(handle, "PowerDeterminePlatformRoleEx"));
    _PowerDuplicateScheme = reinterpret_cast<PowerDuplicateScheme_t>(GetProcAddress(handle, "PowerDuplicateScheme"));
    _PowerEnumerate = reinterpret_cast<PowerEnumerate_t>(GetProcAddress(handle, "PowerEnumerate"));
    _PowerGetActiveScheme = reinterpret_cast<PowerGetActiveScheme_t>(GetProcAddress(handle, "PowerGetActiveScheme"));
    _PowerImportPowerScheme =
        reinterpret_cast<PowerImportPowerScheme_t>(GetProcAddress(handle, "PowerImportPowerScheme"));
    _PowerIsSettingRangeDefined =
        reinterpret_cast<PowerIsSettingRangeDefined_t>(GetProcAddress(handle, "PowerIsSettingRangeDefined"));
    _PowerOpenSystemPowerKey =
        reinterpret_cast<PowerOpenSystemPowerKey_t>(GetProcAddress(handle, "PowerOpenSystemPowerKey"));
    _PowerOpenUserPowerKey = reinterpret_cast<PowerOpenUserPowerKey_t>(GetProcAddress(handle, "PowerOpenUserPowerKey"));
    _PowerReadACDefaultIndex =
        reinterpret_cast<PowerReadACDefaultIndex_t>(GetProcAddress(handle, "PowerReadACDefaultIndex"));
    _PowerReadACValue = reinterpret_cast<PowerReadACValue_t>(GetProcAddress(handle, "PowerReadACValue"));
    _PowerReadACValueIndex = reinterpret_cast<PowerReadACValueIndex_t>(GetProcAddress(handle, "PowerReadACValueIndex"));
    _PowerReadDCDefaultIndex =
        reinterpret_cast<PowerReadDCDefaultIndex_t>(GetProcAddress(handle, "PowerReadDCDefaultIndex"));
    _PowerReadDCValue = reinterpret_cast<PowerReadDCValue_t>(GetProcAddress(handle, "PowerReadDCValue"));
    _PowerReadDCValueIndex = reinterpret_cast<PowerReadDCValueIndex_t>(GetProcAddress(handle, "PowerReadDCValueIndex"));
    _PowerReadDescription = reinterpret_cast<PowerReadDescription_t>(GetProcAddress(handle, "PowerReadDescription"));
    _PowerReadFriendlyName = reinterpret_cast<PowerReadFriendlyName_t>(GetProcAddress(handle, "PowerReadFriendlyName"));
    _PowerReadIconResourceSpecifier =
        reinterpret_cast<PowerReadIconResourceSpecifier_t>(GetProcAddress(handle, "PowerReadIconResourceSpecifier"));
    _PowerReadPossibleDescription =
        reinterpret_cast<PowerReadPossibleDescription_t>(GetProcAddress(handle, "PowerReadPossibleDescription"));
    _PowerReadPossibleFriendlyName =
        reinterpret_cast<PowerReadPossibleFriendlyName_t>(GetProcAddress(handle, "PowerReadPossibleFriendlyName"));
    _PowerReadPossibleValue =
        reinterpret_cast<PowerReadPossibleValue_t>(GetProcAddress(handle, "PowerReadPossibleValue"));
    _PowerReadSettingAttributes =
        reinterpret_cast<PowerReadSettingAttributes_t>(GetProcAddress(handle, "PowerReadSettingAttributes"));
    _PowerReadValueIncrement =
        reinterpret_cast<PowerReadValueIncrement_t>(GetProcAddress(handle, "PowerReadValueIncrement"));
    _PowerReadValueMax = reinterpret_cast<PowerReadValueMax_t>(GetProcAddress(handle, "PowerReadValueMax"));
    _PowerReadValueMin = reinterpret_cast<PowerReadValueMin_t>(GetProcAddress(handle, "PowerReadValueMin"));
    _PowerReadValueUnitsSpecifier =
        reinterpret_cast<PowerReadValueUnitsSpecifier_t>(GetProcAddress(handle, "PowerReadValueUnitsSpecifier"));
    _PowerRegisterForEffectivePowerModeNotifications =
        reinterpret_cast<PowerRegisterForEffectivePowerModeNotifications_t>(
            GetProcAddress(handle, "PowerRegisterForEffectivePowerModeNotifications"));
    _PowerRegisterSuspendResumeNotification = reinterpret_cast<PowerRegisterSuspendResumeNotification_t>(
        GetProcAddress(handle, "PowerRegisterSuspendResumeNotification"));
    _PowerRemovePowerSetting =
        reinterpret_cast<PowerRemovePowerSetting_t>(GetProcAddress(handle, "PowerRemovePowerSetting"));
    _PowerReplaceDefaultPowerSchemes =
        reinterpret_cast<PowerReplaceDefaultPowerSchemes_t>(GetProcAddress(handle, "PowerReplaceDefaultPowerSchemes"));
    _PowerReportThermalEvent =
        reinterpret_cast<PowerReportThermalEvent_t>(GetProcAddress(handle, "PowerReportThermalEvent"));
    _PowerRestoreDefaultPowerSchemes =
        reinterpret_cast<PowerRestoreDefaultPowerSchemes_t>(GetProcAddress(handle, "PowerRestoreDefaultPowerSchemes"));
    _PowerRestoreIndividualDefaultPowerScheme = reinterpret_cast<PowerRestoreIndividualDefaultPowerScheme_t>(
        GetProcAddress(handle, "PowerRestoreIndividualDefaultPowerScheme"));
    _PowerSetActiveScheme = reinterpret_cast<PowerSetActiveScheme_t>(GetProcAddress(handle, "PowerSetActiveScheme"));
    _PowerSettingAccessCheck =
        reinterpret_cast<PowerSettingAccessCheck_t>(GetProcAddress(handle, "PowerSettingAccessCheck"));
    _PowerSettingAccessCheckEx =
        reinterpret_cast<PowerSettingAccessCheckEx_t>(GetProcAddress(handle, "PowerSettingAccessCheckEx"));
    _PowerSettingRegisterNotification = reinterpret_cast<PowerSettingRegisterNotification_t>(
        GetProcAddress(handle, "PowerSettingRegisterNotification"));
    _PowerSettingUnregisterNotification = reinterpret_cast<PowerSettingUnregisterNotification_t>(
        GetProcAddress(handle, "PowerSettingUnregisterNotification"));
    using PowerUnregisterFromEffectivePowerModeNotifications_t =
        decltype(&PowerUnregisterFromEffectivePowerModeNotifications);
    _PowerUnregisterSuspendResumeNotification = reinterpret_cast<PowerUnregisterSuspendResumeNotification_t>(
        GetProcAddress(handle, "PowerUnregisterSuspendResumeNotification"));
    _PowerWriteACDefaultIndex =
        reinterpret_cast<PowerWriteACDefaultIndex_t>(GetProcAddress(handle, "PowerWriteACDefaultIndex"));
    _PowerWriteACValueIndex =
        reinterpret_cast<PowerWriteACValueIndex_t>(GetProcAddress(handle, "PowerWriteACValueIndex"));
    _PowerWriteDCDefaultIndex =
        reinterpret_cast<PowerWriteDCDefaultIndex_t>(GetProcAddress(handle, "PowerWriteDCDefaultIndex"));
    _PowerWriteDCValueIndex =
        reinterpret_cast<PowerWriteDCValueIndex_t>(GetProcAddress(handle, "PowerWriteDCValueIndex"));
    _PowerWriteDescription = reinterpret_cast<PowerWriteDescription_t>(GetProcAddress(handle, "PowerWriteDescription"));
    _PowerWriteFriendlyName =
        reinterpret_cast<PowerWriteFriendlyName_t>(GetProcAddress(handle, "PowerWriteFriendlyName"));
    _PowerWriteIconResourceSpecifier =
        reinterpret_cast<PowerWriteIconResourceSpecifier_t>(GetProcAddress(handle, "PowerWriteIconResourceSpecifier"));
    _PowerWritePossibleDescription =
        reinterpret_cast<PowerWritePossibleDescription_t>(GetProcAddress(handle, "PowerWritePossibleDescription"));
    _PowerWritePossibleFriendlyName =
        reinterpret_cast<PowerWritePossibleFriendlyName_t>(GetProcAddress(handle, "PowerWritePossibleFriendlyName"));
    _PowerWritePossibleValue =
        reinterpret_cast<PowerWritePossibleValue_t>(GetProcAddress(handle, "PowerWritePossibleValue"));
    _PowerWriteSettingAttributes =
        reinterpret_cast<PowerWriteSettingAttributes_t>(GetProcAddress(handle, "PowerWriteSettingAttributes"));
    _PowerWriteValueIncrement =
        reinterpret_cast<PowerWriteValueIncrement_t>(GetProcAddress(handle, "PowerWriteValueIncrement"));
    _PowerWriteValueMax = reinterpret_cast<PowerWriteValueMax_t>(GetProcAddress(handle, "PowerWriteValueMax"));
    _PowerWriteValueMin = reinterpret_cast<PowerWriteValueMin_t>(GetProcAddress(handle, "PowerWriteValueMin"));
    _PowerWriteValueUnitsSpecifier =
        reinterpret_cast<PowerWriteValueUnitsSpecifier_t>(GetProcAddress(handle, "PowerWriteValueUnitsSpecifier"));
    _ReadGlobalPwrPolicy = reinterpret_cast<ReadGlobalPwrPolicy_t>(GetProcAddress(handle, "ReadGlobalPwrPolicy"));
    _ReadProcessorPwrScheme =
        reinterpret_cast<ReadProcessorPwrScheme_t>(GetProcAddress(handle, "ReadProcessorPwrScheme"));
    _ReadPwrScheme = reinterpret_cast<ReadPwrScheme_t>(GetProcAddress(handle, "ReadPwrScheme"));
    _SetActivePwrScheme = reinterpret_cast<SetActivePwrScheme_t>(GetProcAddress(handle, "SetActivePwrScheme"));
    _SetSuspendState = reinterpret_cast<SetSuspendState_t>(GetProcAddress(handle, "SetSuspendState"));
    _ValidatePowerPolicies = reinterpret_cast<ValidatePowerPolicies_t>(GetProcAddress(handle, "ValidatePowerPolicies"));
    _WriteGlobalPwrPolicy = reinterpret_cast<WriteGlobalPwrPolicy_t>(GetProcAddress(handle, "WriteGlobalPwrPolicy"));
    _WriteProcessorPwrScheme =
        reinterpret_cast<WriteProcessorPwrScheme_t>(GetProcAddress(handle, "WriteProcessorPwrScheme"));
    _WritePwrScheme = reinterpret_cast<WritePwrScheme_t>(GetProcAddress(handle, "WritePwrScheme"));

    // Undocumented functions.
    _GUIDFormatToGlobalPowerPolicy =
        reinterpret_cast<GUIDFormatToGlobalPowerPolicy_t>(GetProcAddress(handle, "GUIDFormatToGlobalPowerPolicy"));
    _GUIDFormatToPowerPolicy =
        reinterpret_cast<GUIDFormatToPowerPolicy_t>(GetProcAddress(handle, "GUIDFormatToPowerPolicy"));
    _LoadCurrentPwrScheme = reinterpret_cast<LoadCurrentPwrScheme_t>(GetProcAddress(handle, "LoadCurrentPwrScheme"));
    _MergeLegacyPwrScheme = reinterpret_cast<MergeLegacyPwrScheme_t>(GetProcAddress(handle, "MergeLegacyPwrScheme"));
    _PowerApplyPowerRequestOverride =
        reinterpret_cast<PowerApplyPowerRequestOverride_t>(GetProcAddress(handle, "PowerApplyPowerRequestOverride"));
    _PowerApplySettingChanges =
        reinterpret_cast<PowerApplySettingChanges_t>(GetProcAddress(handle, "PowerApplySettingChanges"));
    _PowerClearUserAwayPrediction =
        reinterpret_cast<PowerClearUserAwayPrediction_t>(GetProcAddress(handle, "PowerClearUserAwayPrediction"));
    _PowerCloseEnvironmentalMonitor =
        reinterpret_cast<PowerCloseEnvironmentalMonitor_t>(GetProcAddress(handle, "PowerCloseEnvironmentalMonitor"));
    _PowerCloseLimitsMitigation =
        reinterpret_cast<PowerCloseLimitsMitigation_t>(GetProcAddress(handle, "PowerCloseLimitsMitigation"));
    _PowerCloseLimitsPolicy =
        reinterpret_cast<PowerCloseLimitsPolicy_t>(GetProcAddress(handle, "PowerCloseLimitsPolicy"));
    _PowerDebugDifPowerPolicies =
        reinterpret_cast<PowerDebugDifPowerPolicies_t>(GetProcAddress(handle, "PowerDebugDifPowerPolicies"));
    _PowerDebugDifSystemPowerPolicies = reinterpret_cast<PowerDebugDifSystemPowerPolicies_t>(
        GetProcAddress(handle, "PowerDebugDifSystemPowerPolicies"));
    _PowerDebugDumpPowerPolicy =
        reinterpret_cast<PowerDebugDumpPowerPolicy_t>(GetProcAddress(handle, "PowerDebugDumpPowerPolicy"));
    _PowerDebugDumpPowerScheme =
        reinterpret_cast<PowerDebugDumpPowerScheme_t>(GetProcAddress(handle, "PowerDebugDumpPowerScheme"));
    _PowerDebugDumpSystemPowerCapabilities = reinterpret_cast<PowerDebugDumpSystemPowerCapabilities_t>(
        GetProcAddress(handle, "PowerDebugDumpSystemPowerCapabilities"));
    _PowerDebugDumpSystemPowerPolicy =
        reinterpret_cast<PowerDebugDumpSystemPowerPolicy_t>(GetProcAddress(handle, "PowerDebugDumpSystemPowerPolicy"));
    _PowerGetActualOverlayScheme =
        reinterpret_cast<PowerGetActualOverlayScheme_t>(GetProcAddress(handle, "PowerGetActualOverlayScheme"));
    _PowerGetAdaptiveStandbyDiagnostics = reinterpret_cast<PowerGetAdaptiveStandbyDiagnostics_t>(
        GetProcAddress(handle, "PowerGetAdaptiveStandbyDiagnostics"));
    _PowerGetEffectiveOverlayScheme =
        reinterpret_cast<PowerGetEffectiveOverlayScheme_t>(GetProcAddress(handle, "PowerGetEffectiveOverlayScheme"));
    _PowerGetOverlaySchemes =
        reinterpret_cast<PowerGetOverlaySchemes_t>(GetProcAddress(handle, "PowerGetOverlaySchemes"));
    _PowerGetUserAwayMinPredictionConfidence = reinterpret_cast<PowerGetUserAwayMinPredictionConfidence_t>(
        GetProcAddress(handle, "PowerGetUserAwayMinPredictionConfidence"));
    _PowerInformationWithPrivileges =
        reinterpret_cast<PowerInformationWithPrivileges_t>(GetProcAddress(handle, "PowerInformationWithPrivileges"));
    _PowerPolicyToGUIDFormat =
        reinterpret_cast<PowerPolicyToGUIDFormat_t>(GetProcAddress(handle, "PowerPolicyToGUIDFormat"));
    _PowerReadACValueIndexEx =
        reinterpret_cast<PowerReadACValueIndexEx_t>(GetProcAddress(handle, "PowerReadACValueIndexEx"));
    _PowerReadDCValueIndexEx =
        reinterpret_cast<PowerReadDCValueIndexEx_t>(GetProcAddress(handle, "PowerReadDCValueIndexEx"));
    _PowerReadSecurityDescriptor =
        reinterpret_cast<PowerReadSecurityDescriptor_t>(GetProcAddress(handle, "PowerReadSecurityDescriptor"));
    _PowerReapplyActiveScheme =
        reinterpret_cast<PowerReapplyActiveScheme_t>(GetProcAddress(handle, "PowerReapplyActiveScheme"));
    _PowerRegisterEnvironmentalMonitor = reinterpret_cast<PowerRegisterEnvironmentalMonitor_t>(
        GetProcAddress(handle, "PowerRegisterEnvironmentalMonitor"));
    _PowerRegisterLimitsMitigation =
        reinterpret_cast<PowerRegisterLimitsMitigation_t>(GetProcAddress(handle, "PowerRegisterLimitsMitigation"));
    _PowerRegisterLimitsPolicy =
        reinterpret_cast<PowerRegisterLimitsPolicy_t>(GetProcAddress(handle, "PowerRegisterLimitsPolicy"));
    _PowerReportLimitsEvent =
        reinterpret_cast<PowerReportLimitsEvent_t>(GetProcAddress(handle, "PowerReportLimitsEvent"));
    _PowerRestoreACDefaultIndex =
        reinterpret_cast<PowerRestoreACDefaultIndex_t>(GetProcAddress(handle, "PowerRestoreACDefaultIndex"));
    _PowerRestoreDCDefaultIndex =
        reinterpret_cast<PowerRestoreDCDefaultIndex_t>(GetProcAddress(handle, "PowerRestoreDCDefaultIndex"));
    _PowerSetActiveOverlayScheme =
        reinterpret_cast<PowerSetActiveOverlayScheme_t>(GetProcAddress(handle, "PowerSetActiveOverlayScheme"));
    _PowerSetAlsBrightnessOffset =
        reinterpret_cast<PowerSetAlsBrightnessOffset_t>(GetProcAddress(handle, "PowerSetAlsBrightnessOffset"));
    _PowerSetBrightnessAndTransitionTimes = reinterpret_cast<PowerSetBrightnessAndTransitionTimes_t>(
        GetProcAddress(handle, "PowerSetBrightnessAndTransitionTimes"));
    _PowerSetUserAwayPrediction =
        reinterpret_cast<PowerSetUserAwayPrediction_t>(GetProcAddress(handle, "PowerSetUserAwayPrediction"));
    _PowerSettingRegisterNotificationEx = reinterpret_cast<PowerSettingRegisterNotificationEx_t>(
        GetProcAddress(handle, "PowerSettingRegisterNotificationEx"));
    _PowerUpdateEnvironmentalMonitorState = reinterpret_cast<PowerUpdateEnvironmentalMonitorState_t>(
        GetProcAddress(handle, "PowerUpdateEnvironmentalMonitorState"));
    _PowerUpdateEnvironmentalMonitorThresholds = reinterpret_cast<PowerUpdateEnvironmentalMonitorThresholds_t>(
        GetProcAddress(handle, "PowerUpdateEnvironmentalMonitorThresholds"));
    _PowerUpdateLimitsMitigation =
        reinterpret_cast<PowerUpdateLimitsMitigation_t>(GetProcAddress(handle, "PowerUpdateLimitsMitigation"));
    _PowerWriteSecurityDescriptor =
        reinterpret_cast<PowerWriteSecurityDescriptor_t>(GetProcAddress(handle, "PowerWriteSecurityDescriptor"));

    return true;
}

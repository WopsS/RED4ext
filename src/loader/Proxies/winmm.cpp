#include "winmm.hpp"

using CloseDriver_t = decltype(&CloseDriver);
using OpenDriver_t = decltype(&OpenDriver);
using SendDriverMessage_t = decltype(&SendDriverMessage);
using DrvGetModuleHandle_t = decltype(&DrvGetModuleHandle);
using GetDriverModuleHandle_t = decltype(&GetDriverModuleHandle);
using DefDriverProc_t = decltype(&DefDriverProc);
using DriverCallback_t = decltype(&DriverCallback);
using PlaySound_t = decltype(&PlaySoundA);
using PlaySoundA_t = decltype(&PlaySoundA);
using PlaySoundW_t = decltype(&PlaySoundW);
using auxGetNumDevs_t = decltype(&auxGetNumDevs);
using auxGetDevCapsA_t = decltype(&auxGetDevCapsA);
using auxGetDevCapsW_t = decltype(&auxGetDevCapsW);
using auxSetVolume_t = decltype(&auxSetVolume);
using auxGetVolume_t = decltype(&auxGetVolume);
using auxOutMessage_t = decltype(&auxOutMessage);
using joyGetPos_t = decltype(&joyGetPos);
using joyGetThreshold_t = decltype(&joyGetThreshold);
using joyReleaseCapture_t = decltype(&joyReleaseCapture);
using joySetCapture_t = decltype(&joySetCapture);
using joySetThreshold_t = decltype(&joySetThreshold);
using joyConfigChanged_t = decltype(&joyConfigChanged);
using joyGetPosEx_t = decltype(&joyGetPosEx);
using joyGetNumDevs_t = decltype(&joyGetNumDevs);
using joyGetDevCapsA_t = decltype(&joyGetDevCapsA);
using joyGetDevCapsW_t = decltype(&joyGetDevCapsW);
using mciSendCommandA_t = decltype(&mciSendCommandA);
using mciSendCommandW_t = decltype(&mciSendCommandW);
using mciSendStringA_t = decltype(&mciSendStringA);
using mciSendStringW_t = decltype(&mciSendStringW);
using mciGetDeviceIDA_t = decltype(&mciGetDeviceIDA);
using mciGetDeviceIDW_t = decltype(&mciGetDeviceIDW);
using mciGetDeviceIDFromElementIDA_t = decltype(&mciGetDeviceIDFromElementIDA);
using mciGetDeviceIDFromElementIDW_t = decltype(&mciGetDeviceIDFromElementIDW);
using mciGetErrorStringA_t = decltype(&mciGetErrorStringA);
using mciGetErrorStringW_t = decltype(&mciGetErrorStringW);
using mciSetYieldProc_t = decltype(&mciSetYieldProc);
using mciGetCreatorTask_t = decltype(&mciGetCreatorTask);
using mciGetYieldProc_t = decltype(&mciGetYieldProc);
using mciGetDriverData_t = decltype(&mciGetDriverData);
using mciLoadCommandResource_t = decltype(&mciLoadCommandResource);
using mciSetDriverData_t = decltype(&mciSetDriverData);
using mciDriverYield_t = decltype(&mciDriverYield);
using mciDriverNotify_t = decltype(&mciDriverNotify);
using mciFreeCommandResource_t = decltype(&mciFreeCommandResource);
using midiOutGetNumDevs_t = decltype(&midiOutGetNumDevs);
using midiStreamOpen_t = decltype(&midiStreamOpen);
using midiStreamClose_t = decltype(&midiStreamClose);
using midiStreamProperty_t = decltype(&midiStreamProperty);
using midiStreamPosition_t = decltype(&midiStreamPosition);
using midiStreamOut_t = decltype(&midiStreamOut);
using midiStreamPause_t = decltype(&midiStreamPause);
using midiStreamRestart_t = decltype(&midiStreamRestart);
using midiStreamStop_t = decltype(&midiStreamStop);
using midiConnect_t = decltype(&midiConnect);
using midiDisconnect_t = decltype(&midiDisconnect);
using midiOutGetDevCapsA_t = decltype(&midiOutGetDevCapsA);
using midiOutGetDevCapsW_t = decltype(&midiOutGetDevCapsW);
using midiOutGetVolume_t = decltype(&midiOutGetVolume);
using midiOutSetVolume_t = decltype(&midiOutSetVolume);
using midiOutGetErrorTextA_t = decltype(&midiOutGetErrorTextA);
using midiOutGetErrorTextW_t = decltype(&midiOutGetErrorTextW);
using midiOutOpen_t = decltype(&midiOutOpen);
using midiOutClose_t = decltype(&midiOutClose);
using midiOutPrepareHeader_t = decltype(&midiOutPrepareHeader);
using midiOutUnprepareHeader_t = decltype(&midiOutUnprepareHeader);
using midiOutShortMsg_t = decltype(&midiOutShortMsg);
using midiOutLongMsg_t = decltype(&midiOutLongMsg);
using midiOutReset_t = decltype(&midiOutReset);
using midiOutCachePatches_t = decltype(&midiOutCachePatches);
using midiOutCacheDrumPatches_t = decltype(&midiOutCacheDrumPatches);
using midiOutGetID_t = decltype(&midiOutGetID);
using midiOutMessage_t = decltype(&midiOutMessage);
using midiInGetNumDevs_t = decltype(&midiInGetNumDevs);
using midiInGetDevCapsA_t = decltype(&midiInGetDevCapsA);
using midiInGetDevCapsW_t = decltype(&midiInGetDevCapsW);
using midiInGetErrorTextA_t = decltype(&midiInGetErrorTextA);
using midiInGetErrorTextW_t = decltype(&midiInGetErrorTextW);
using midiInOpen_t = decltype(&midiInOpen);
using midiInClose_t = decltype(&midiInClose);
using midiInPrepareHeader_t = decltype(&midiInPrepareHeader);
using midiInUnprepareHeader_t = decltype(&midiInUnprepareHeader);
using midiInAddBuffer_t = decltype(&midiInAddBuffer);
using midiInStart_t = decltype(&midiInStart);
using midiInStop_t = decltype(&midiInStop);
using midiInReset_t = decltype(&midiInReset);
using midiInGetID_t = decltype(&midiInGetID);
using midiInMessage_t = decltype(&midiInMessage);
using mixerGetNumDevs_t = decltype(&mixerGetNumDevs);
using mixerGetDevCapsA_t = decltype(&mixerGetDevCapsA);
using mixerGetDevCapsW_t = decltype(&mixerGetDevCapsW);
using mixerOpen_t = decltype(&mixerOpen);
using mixerClose_t = decltype(&mixerClose);
using mixerMessage_t = decltype(&mixerMessage);
using mixerGetLineInfoA_t = decltype(&mixerGetLineInfoA);
using mixerGetLineInfoW_t = decltype(&mixerGetLineInfoW);
using mixerGetID_t = decltype(&mixerGetID);
using mixerGetLineControlsA_t = decltype(&mixerGetLineControlsA);
using mixerGetLineControlsW_t = decltype(&mixerGetLineControlsW);
using mixerGetControlDetailsA_t = decltype(&mixerGetControlDetailsA);
using mixerGetControlDetailsW_t = decltype(&mixerGetControlDetailsW);
using mixerSetControlDetails_t = decltype(&mixerSetControlDetails);
using mmDrvInstall_t = decltype(&mmDrvInstall);
using mmTaskCreate_t = decltype(&mmTaskCreate);
using mmTaskBlock_t = decltype(&mmTaskBlock);
using mmTaskSignal_t = decltype(&mmTaskSignal);
using mmTaskYield_t = decltype(&mmTaskYield);
using mmGetCurrentTask_t = decltype(&mmGetCurrentTask);
using mmioStringToFOURCCA_t = decltype(&mmioStringToFOURCCA);
using mmioStringToFOURCCW_t = decltype(&mmioStringToFOURCCW);
using mmioInstallIOProcA_t = decltype(&mmioInstallIOProcA);
using mmioInstallIOProcW_t = decltype(&mmioInstallIOProcW);
using mmioOpenA_t = decltype(&mmioOpenA);
using mmioOpenW_t = decltype(&mmioOpenW);
using mmioRenameA_t = decltype(&mmioRenameA);
using mmioRenameW_t = decltype(&mmioRenameW);
using mmioClose_t = decltype(&mmioClose);
using mmioRead_t = decltype(&mmioRead);
using mmioWrite_t = decltype(&mmioWrite);
using mmioSeek_t = decltype(&mmioSeek);
using mmioGetInfo_t = decltype(&mmioGetInfo);
using mmioSetInfo_t = decltype(&mmioSetInfo);
using mmioSetBuffer_t = decltype(&mmioSetBuffer);
using mmioFlush_t = decltype(&mmioFlush);
using mmioAdvance_t = decltype(&mmioAdvance);
using mmioSendMessage_t = decltype(&mmioSendMessage);
using mmioAscend_t = decltype(&mmioAscend);
using mmioDescend_t = decltype(&mmioDescend);
using mmioCreateChunk_t = decltype(&mmioCreateChunk);
using sndPlaySoundA_t = decltype(&sndPlaySoundA);
using sndPlaySoundW_t = decltype(&sndPlaySoundW);
using timeGetSystemTime_t = decltype(&timeGetSystemTime);
using timeGetTime_t = decltype(&timeGetTime);
using timeGetDevCaps_t = decltype(&timeGetDevCaps);
using timeBeginPeriod_t = decltype(&timeBeginPeriod);
using timeEndPeriod_t = decltype(&timeEndPeriod);
using timeKillEvent_t = decltype(&timeKillEvent);
using timeSetEvent_t = decltype(&timeSetEvent);
using waveOutGetNumDevs_t = decltype(&waveOutGetNumDevs);
using waveOutGetDevCapsA_t = decltype(&waveOutGetDevCapsA);
using waveOutGetDevCapsW_t = decltype(&waveOutGetDevCapsW);
using waveOutGetVolume_t = decltype(&waveOutGetVolume);
using waveOutSetVolume_t = decltype(&waveOutSetVolume);
using waveOutGetErrorTextA_t = decltype(&waveOutGetErrorTextA);
using waveOutGetErrorTextW_t = decltype(&waveOutGetErrorTextW);
using waveOutOpen_t = decltype(&waveOutOpen);
using waveOutClose_t = decltype(&waveOutClose);
using waveOutPrepareHeader_t = decltype(&waveOutPrepareHeader);
using waveOutUnprepareHeader_t = decltype(&waveOutUnprepareHeader);
using waveOutWrite_t = decltype(&waveOutWrite);
using waveOutPause_t = decltype(&waveOutPause);
using waveOutRestart_t = decltype(&waveOutRestart);
using waveOutReset_t = decltype(&waveOutReset);
using waveOutBreakLoop_t = decltype(&waveOutBreakLoop);
using waveOutGetPosition_t = decltype(&waveOutGetPosition);
using waveOutGetPitch_t = decltype(&waveOutGetPitch);
using waveOutSetPitch_t = decltype(&waveOutSetPitch);
using waveOutGetPlaybackRate_t = decltype(&waveOutGetPlaybackRate);
using waveOutSetPlaybackRate_t = decltype(&waveOutSetPlaybackRate);
using waveOutGetID_t = decltype(&waveOutGetID);
using waveOutMessage_t = decltype(&waveOutMessage);
using waveInGetNumDevs_t = decltype(&waveInGetNumDevs);
using waveInGetDevCapsA_t = decltype(&waveInGetDevCapsA);
using waveInGetDevCapsW_t = decltype(&waveInGetDevCapsW);
using waveInGetErrorTextA_t = decltype(&waveInGetErrorTextA);
using waveInGetErrorTextW_t = decltype(&waveInGetErrorTextW);
using waveInOpen_t = decltype(&waveInOpen);
using waveInClose_t = decltype(&waveInClose);
using waveInPrepareHeader_t = decltype(&waveInPrepareHeader);
using waveInUnprepareHeader_t = decltype(&waveInUnprepareHeader);
using waveInAddBuffer_t = decltype(&waveInAddBuffer);
using waveInStart_t = decltype(&waveInStart);
using waveInStop_t = decltype(&waveInStop);
using waveInReset_t = decltype(&waveInReset);
using waveInGetPosition_t = decltype(&waveInGetPosition);
using waveInGetID_t = decltype(&waveInGetID);
using waveInMessage_t = decltype(&waveInMessage);

using WOWAppExit_t = VOID(WINAPI*)();
using mciExecute_t = BOOL(WINAPI*)(LPCSTR);
using mmsystemGetVersion_t = UINT(WINAPI*)();
using PlaySoundStub_t = decltype(&PlaySoundA);

#undef PlaySound

namespace Functions
{
CloseDriver_t CloseDriver;
OpenDriver_t OpenDriver;
SendDriverMessage_t SendDriverMessage;
DrvGetModuleHandle_t DrvGetModuleHandle;
GetDriverModuleHandle_t GetDriverModuleHandle;
DefDriverProc_t DefDriverProc;
DriverCallback_t DriverCallback;
PlaySound_t PlaySound;
PlaySoundA_t PlaySoundA;
PlaySoundW_t PlaySoundW;
auxGetNumDevs_t auxGetNumDevs;
auxGetDevCapsA_t auxGetDevCapsA;
auxGetDevCapsW_t auxGetDevCapsW;
auxSetVolume_t auxSetVolume;
auxGetVolume_t auxGetVolume;
auxOutMessage_t auxOutMessage;
joyGetPos_t joyGetPos;
joyGetThreshold_t joyGetThreshold;
joyReleaseCapture_t joyReleaseCapture;
joySetCapture_t joySetCapture;
joySetThreshold_t joySetThreshold;
joyConfigChanged_t joyConfigChanged;
joyGetPosEx_t joyGetPosEx;
joyGetNumDevs_t joyGetNumDevs;
joyGetDevCapsA_t joyGetDevCapsA;
joyGetDevCapsW_t joyGetDevCapsW;
mciSendCommandA_t mciSendCommandA;
mciSendCommandW_t mciSendCommandW;
mciSendStringA_t mciSendStringA;
mciSendStringW_t mciSendStringW;
mciGetDeviceIDA_t mciGetDeviceIDA;
mciGetDeviceIDW_t mciGetDeviceIDW;
mciGetDeviceIDFromElementIDA_t mciGetDeviceIDFromElementIDA;
mciGetDeviceIDFromElementIDW_t mciGetDeviceIDFromElementIDW;
mciGetErrorStringA_t mciGetErrorStringA;
mciGetErrorStringW_t mciGetErrorStringW;
mciSetYieldProc_t mciSetYieldProc;
mciGetCreatorTask_t mciGetCreatorTask;
mciGetYieldProc_t mciGetYieldProc;
mciGetDriverData_t mciGetDriverData;
mciLoadCommandResource_t mciLoadCommandResource;
mciSetDriverData_t mciSetDriverData;
mciDriverYield_t mciDriverYield;
mciDriverNotify_t mciDriverNotify;
mciFreeCommandResource_t mciFreeCommandResource;
midiOutGetNumDevs_t midiOutGetNumDevs;
midiStreamOpen_t midiStreamOpen;
midiStreamClose_t midiStreamClose;
midiStreamProperty_t midiStreamProperty;
midiStreamPosition_t midiStreamPosition;
midiStreamOut_t midiStreamOut;
midiStreamPause_t midiStreamPause;
midiStreamRestart_t midiStreamRestart;
midiStreamStop_t midiStreamStop;
midiConnect_t midiConnect;
midiDisconnect_t midiDisconnect;
midiOutGetDevCapsA_t midiOutGetDevCapsA;
midiOutGetDevCapsW_t midiOutGetDevCapsW;
midiOutGetVolume_t midiOutGetVolume;
midiOutSetVolume_t midiOutSetVolume;
midiOutGetErrorTextA_t midiOutGetErrorTextA;
midiOutGetErrorTextW_t midiOutGetErrorTextW;
midiOutOpen_t midiOutOpen;
midiOutClose_t midiOutClose;
midiOutPrepareHeader_t midiOutPrepareHeader;
midiOutUnprepareHeader_t midiOutUnprepareHeader;
midiOutShortMsg_t midiOutShortMsg;
midiOutLongMsg_t midiOutLongMsg;
midiOutReset_t midiOutReset;
midiOutCachePatches_t midiOutCachePatches;
midiOutCacheDrumPatches_t midiOutCacheDrumPatches;
midiOutGetID_t midiOutGetID;
midiOutMessage_t midiOutMessage;
midiInGetNumDevs_t midiInGetNumDevs;
midiInGetDevCapsA_t midiInGetDevCapsA;
midiInGetDevCapsW_t midiInGetDevCapsW;
midiInGetErrorTextA_t midiInGetErrorTextA;
midiInGetErrorTextW_t midiInGetErrorTextW;
midiInOpen_t midiInOpen;
midiInClose_t midiInClose;
midiInPrepareHeader_t midiInPrepareHeader;
midiInUnprepareHeader_t midiInUnprepareHeader;
midiInAddBuffer_t midiInAddBuffer;
midiInStart_t midiInStart;
midiInStop_t midiInStop;
midiInReset_t midiInReset;
midiInGetID_t midiInGetID;
midiInMessage_t midiInMessage;
mixerGetNumDevs_t mixerGetNumDevs;
mixerGetDevCapsA_t mixerGetDevCapsA;
mixerGetDevCapsW_t mixerGetDevCapsW;
mixerOpen_t mixerOpen;
mixerClose_t mixerClose;
mixerMessage_t mixerMessage;
mixerGetLineInfoA_t mixerGetLineInfoA;
mixerGetLineInfoW_t mixerGetLineInfoW;
mixerGetID_t mixerGetID;
mixerGetLineControlsA_t mixerGetLineControlsA;
mixerGetLineControlsW_t mixerGetLineControlsW;
mixerGetControlDetailsA_t mixerGetControlDetailsA;
mixerGetControlDetailsW_t mixerGetControlDetailsW;
mixerSetControlDetails_t mixerSetControlDetails;
mmDrvInstall_t mmDrvInstall;
mmTaskCreate_t mmTaskCreate;
mmTaskBlock_t mmTaskBlock;
mmTaskSignal_t mmTaskSignal;
mmTaskYield_t mmTaskYield;
mmGetCurrentTask_t mmGetCurrentTask;
mmioStringToFOURCCA_t mmioStringToFOURCCA;
mmioStringToFOURCCW_t mmioStringToFOURCCW;
mmioInstallIOProcA_t mmioInstallIOProcA;
mmioInstallIOProcW_t mmioInstallIOProcW;
mmioOpenA_t mmioOpenA;
mmioOpenW_t mmioOpenW;
mmioRenameA_t mmioRenameA;
mmioRenameW_t mmioRenameW;
mmioClose_t mmioClose;
mmioRead_t mmioRead;
mmioWrite_t mmioWrite;
mmioSeek_t mmioSeek;
mmioGetInfo_t mmioGetInfo;
mmioSetInfo_t mmioSetInfo;
mmioSetBuffer_t mmioSetBuffer;
mmioFlush_t mmioFlush;
mmioAdvance_t mmioAdvance;
mmioSendMessage_t mmioSendMessage;
mmioAscend_t mmioAscend;
mmioDescend_t mmioDescend;
mmioCreateChunk_t mmioCreateChunk;
sndPlaySoundA_t sndPlaySoundA;
sndPlaySoundW_t sndPlaySoundW;
timeGetSystemTime_t timeGetSystemTime;
timeGetTime_t timeGetTime;
timeGetDevCaps_t timeGetDevCaps;
timeBeginPeriod_t timeBeginPeriod;
timeEndPeriod_t timeEndPeriod;
timeKillEvent_t timeKillEvent;
timeSetEvent_t timeSetEvent;
waveOutGetNumDevs_t waveOutGetNumDevs;
waveOutGetDevCapsA_t waveOutGetDevCapsA;
waveOutGetDevCapsW_t waveOutGetDevCapsW;
waveOutGetVolume_t waveOutGetVolume;
waveOutSetVolume_t waveOutSetVolume;
waveOutGetErrorTextA_t waveOutGetErrorTextA;
waveOutGetErrorTextW_t waveOutGetErrorTextW;
waveOutOpen_t waveOutOpen;
waveOutClose_t waveOutClose;
waveOutPrepareHeader_t waveOutPrepareHeader;
waveOutUnprepareHeader_t waveOutUnprepareHeader;
waveOutWrite_t waveOutWrite;
waveOutPause_t waveOutPause;
waveOutRestart_t waveOutRestart;
waveOutReset_t waveOutReset;
waveOutBreakLoop_t waveOutBreakLoop;
waveOutGetPosition_t waveOutGetPosition;
waveOutGetPitch_t waveOutGetPitch;
waveOutSetPitch_t waveOutSetPitch;
waveOutGetPlaybackRate_t waveOutGetPlaybackRate;
waveOutSetPlaybackRate_t waveOutSetPlaybackRate;
waveOutGetID_t waveOutGetID;
waveOutMessage_t waveOutMessage;
waveInGetNumDevs_t waveInGetNumDevs;
waveInGetDevCapsA_t waveInGetDevCapsA;
waveInGetDevCapsW_t waveInGetDevCapsW;
waveInGetErrorTextA_t waveInGetErrorTextA;
waveInGetErrorTextW_t waveInGetErrorTextW;
waveInOpen_t waveInOpen;
waveInClose_t waveInClose;
waveInPrepareHeader_t waveInPrepareHeader;
waveInUnprepareHeader_t waveInUnprepareHeader;
waveInAddBuffer_t waveInAddBuffer;
waveInStart_t waveInStart;
waveInStop_t waveInStop;
waveInReset_t waveInReset;
waveInGetPosition_t waveInGetPosition;
waveInGetID_t waveInGetID;
waveInMessage_t waveInMessage;

WOWAppExit_t WOWAppExit;
mciExecute_t mciExecute;
mmsystemGetVersion_t mmsystemGetVersion;
PlaySoundStub_t PlaySoundStub;
} // namespace Functions

LRESULT WINAPI _CloseDriver(HDRVR hDriver, LPARAM lParam1, LPARAM lParam2)
{
    return Functions::CloseDriver(hDriver, lParam1, lParam2);
}

HDRVR WINAPI _OpenDriver(LPCWSTR szDriverName, LPCWSTR szSectionName, LPARAM lParam2)
{
    return Functions::OpenDriver(szDriverName, szSectionName, lParam2);
}

LRESULT WINAPI _SendDriverMessage(HDRVR hDriver, UINT message, LPARAM lParam1, LPARAM lParam2)
{
    return Functions::SendDriverMessage(hDriver, message, lParam1, lParam2);
}

HMODULE WINAPI _DrvGetModuleHandle(HDRVR hDriver)
{
    return Functions::DrvGetModuleHandle(hDriver);
}

HMODULE WINAPI _GetDriverModuleHandle(HDRVR hDriver)
{
    return Functions::GetDriverModuleHandle(hDriver);
}

LRESULT WINAPI _DefDriverProc(DWORD_PTR dwDriverIdentifier, HDRVR hdrvr, UINT uMsg, LPARAM lParam1, LPARAM lParam2)
{
    return Functions::DefDriverProc(dwDriverIdentifier, hdrvr, uMsg, lParam1, lParam2);
}

BOOL APIENTRY _DriverCallback(DWORD_PTR dwCallback, DWORD dwFlags, HDRVR hDevice, DWORD dwMsg, DWORD_PTR dwUser,
                              DWORD_PTR dwParam1, DWORD_PTR dwParam2)
{
    return Functions::DriverCallback(dwCallback, dwFlags, hDevice, dwMsg, dwUser, dwParam1, dwParam2);
}

BOOL WINAPI _PlaySound(LPCSTR pszSound, HMODULE hmod, DWORD fdwSound)
{
    return Functions::PlaySound(pszSound, hmod, fdwSound);
}

BOOL WINAPI _PlaySoundA(LPCSTR pszSound, HMODULE hmod, DWORD fdwSound)
{
    return Functions::PlaySoundA(pszSound, hmod, fdwSound);
}

BOOL WINAPI _PlaySoundW(LPCWSTR pszSound, HMODULE hmod, DWORD fdwSound)
{
    return Functions::PlaySoundW(pszSound, hmod, fdwSound);
}

UINT WINAPI _auxGetNumDevs(void)
{
    return Functions::auxGetNumDevs();
}

MMRESULT WINAPI _auxGetDevCapsA(UINT_PTR uDeviceID, LPAUXCAPSA pac, UINT cbac)
{
    return Functions::auxGetDevCapsA(uDeviceID, pac, cbac);
}

MMRESULT WINAPI _auxGetDevCapsW(UINT_PTR uDeviceID, LPAUXCAPSW pac, UINT cbac)
{
    return Functions::auxGetDevCapsW(uDeviceID, pac, cbac);
}

MMRESULT WINAPI _auxSetVolume(UINT uDeviceID, DWORD dwVolume)
{
    return Functions::auxSetVolume(uDeviceID, dwVolume);
}

MMRESULT WINAPI _auxGetVolume(UINT uDeviceID, LPDWORD pdwVolume)
{
    return Functions::auxGetVolume(uDeviceID, pdwVolume);
}

MMRESULT WINAPI _auxOutMessage(UINT uDeviceID, UINT uMsg, DWORD_PTR dw1, DWORD_PTR dw2)
{
    return Functions::auxOutMessage(uDeviceID, uMsg, dw1, dw2);
}

MMRESULT WINAPI _joyGetPos(UINT uJoyID, LPJOYINFO pji)
{
    return Functions::joyGetPos(uJoyID, pji);
}

MMRESULT WINAPI _joyGetThreshold(UINT uJoyID, LPUINT puThreshold)
{
    return Functions::joyGetThreshold(uJoyID, puThreshold);
}

MMRESULT WINAPI _joyReleaseCapture(UINT uJoyID)
{
    return Functions::joyReleaseCapture(uJoyID);
}

MMRESULT WINAPI _joySetCapture(HWND hwnd, UINT uJoyID, UINT uPeriod, BOOL fChanged)
{
    return Functions::joySetCapture(hwnd, uJoyID, uPeriod, fChanged);
}

MMRESULT WINAPI _joySetThreshold(UINT uJoyID, UINT uThreshold)
{
    return Functions::joySetThreshold(uJoyID, uThreshold);
}

MMRESULT WINAPI _joyConfigChanged(DWORD dwFlags)
{
    return Functions::joyConfigChanged(dwFlags);
}

MMRESULT WINAPI _joyGetPosEx(UINT uJoyID, LPJOYINFOEX pji)
{
    return Functions::joyGetPosEx(uJoyID, pji);
}

UINT WINAPI _joyGetNumDevs(void)
{
    return Functions::joyGetNumDevs();
}

MMRESULT WINAPI _joyGetDevCapsA(UINT_PTR uJoyID, LPJOYCAPSA pjc, UINT cbjc)
{
    return Functions::joyGetDevCapsA(uJoyID, pjc, cbjc);
}

MMRESULT WINAPI _joyGetDevCapsW(UINT_PTR uJoyID, LPJOYCAPSW pjc, UINT cbjc)
{
    return Functions::joyGetDevCapsW(uJoyID, pjc, cbjc);
}

MCIERROR WINAPI _mciSendCommandA(MCIDEVICEID mciId, UINT uMsg, DWORD_PTR dwParam1, DWORD_PTR dwParam2)
{
    return Functions::mciSendCommandA(mciId, uMsg, dwParam1, dwParam2);
}

MCIERROR WINAPI _mciSendCommandW(MCIDEVICEID mciId, UINT uMsg, DWORD_PTR dwParam1, DWORD_PTR dwParam2)
{
    return Functions::mciSendCommandW(mciId, uMsg, dwParam1, dwParam2);
}

MCIERROR WINAPI _mciSendStringA(LPCSTR lpstrCommand, LPSTR lpstrReturnString, UINT uReturnLength, HWND hwndCallback)
{
    return Functions::mciSendStringA(lpstrCommand, lpstrReturnString, uReturnLength, hwndCallback);
}

MCIERROR WINAPI _mciSendStringW(LPCWSTR lpstrCommand, LPWSTR lpstrReturnString, UINT uReturnLength, HWND hwndCallback)
{
    return Functions::mciSendStringW(lpstrCommand, lpstrReturnString, uReturnLength, hwndCallback);
}

MCIDEVICEID WINAPI _mciGetDeviceIDA(LPCSTR pszDevice)
{
    return Functions::mciGetDeviceIDA(pszDevice);
}

MCIDEVICEID WINAPI _mciGetDeviceIDW(LPCWSTR pszDevice)
{
    return Functions::mciGetDeviceIDW(pszDevice);
}

MCIDEVICEID WINAPI _mciGetDeviceIDFromElementIDA(DWORD dwElementID, LPCSTR lpstrType)
{
    return Functions::mciGetDeviceIDFromElementIDA(dwElementID, lpstrType);
}

MCIDEVICEID WINAPI _mciGetDeviceIDFromElementIDW(DWORD dwElementID, LPCWSTR lpstrType)
{
    return Functions::mciGetDeviceIDFromElementIDW(dwElementID, lpstrType);
}

BOOL WINAPI _mciGetErrorStringA(MCIERROR mcierr, LPSTR pszText, UINT cchText)
{
    return Functions::mciGetErrorStringA(mcierr, pszText, cchText);
}

BOOL WINAPI _mciGetErrorStringW(MCIERROR mcierr, LPWSTR pszText, UINT cchText)
{
    return Functions::mciGetErrorStringW(mcierr, pszText, cchText);
}

BOOL WINAPI _mciSetYieldProc(MCIDEVICEID mciId, YIELDPROC fpYieldProc, DWORD dwYieldData)
{
    return Functions::mciSetYieldProc(mciId, fpYieldProc, dwYieldData);
}

HTASK WINAPI _mciGetCreatorTask(MCIDEVICEID mciId)
{
    return Functions::mciGetCreatorTask(mciId);
}

YIELDPROC WINAPI _mciGetYieldProc(MCIDEVICEID mciId, LPDWORD pdwYieldData)
{
    return Functions::mciGetYieldProc(mciId, pdwYieldData);
}

DWORD_PTR APIENTRY _mciGetDriverData(MCIDEVICEID wDeviceID)
{
    return Functions::mciGetDriverData(wDeviceID);
}

UINT APIENTRY _mciLoadCommandResource(HANDLE hInstance, LPCWSTR lpResName, UINT wType)
{
    return Functions::mciLoadCommandResource(hInstance, lpResName, wType);
}

BOOL APIENTRY _mciSetDriverData(MCIDEVICEID wDeviceID, DWORD_PTR dwData)
{
    return Functions::mciSetDriverData(wDeviceID, dwData);
}

UINT APIENTRY _mciDriverYield(MCIDEVICEID wDeviceID)
{
    return Functions::mciDriverYield(wDeviceID);
}

BOOL APIENTRY _mciDriverNotify(HANDLE hwndCallback, MCIDEVICEID wDeviceID, UINT uStatus)
{
    return Functions::mciDriverNotify(hwndCallback, wDeviceID, uStatus);
}

BOOL APIENTRY _mciFreeCommandResource(UINT wTable)
{
    return Functions::mciFreeCommandResource(wTable);
}

UINT WINAPI _midiOutGetNumDevs(void)
{
    return Functions::midiOutGetNumDevs();
}

MMRESULT WINAPI _midiStreamOpen(LPHMIDISTRM phms, LPUINT puDeviceID, DWORD cMidi, DWORD_PTR dwCallback,
                                DWORD_PTR dwInstance, DWORD fdwOpen)
{
    return Functions::midiStreamOpen(phms, puDeviceID, cMidi, dwCallback, dwInstance, fdwOpen);
}

MMRESULT WINAPI _midiStreamClose(HMIDISTRM hms)
{
    return Functions::midiStreamClose(hms);
}

MMRESULT WINAPI _midiStreamProperty(HMIDISTRM hms, LPBYTE lppropdata, DWORD dwProperty)
{
    return Functions::midiStreamProperty(hms, lppropdata, dwProperty);
}

MMRESULT WINAPI _midiStreamPosition(HMIDISTRM hms, LPMMTIME lpmmt, UINT cbmmt)
{
    return Functions::midiStreamPosition(hms, lpmmt, cbmmt);
}

MMRESULT WINAPI _midiStreamOut(HMIDISTRM hms, LPMIDIHDR pmh, UINT cbmh)
{
    return Functions::midiStreamOut(hms, pmh, cbmh);
}

MMRESULT WINAPI _midiStreamPause(HMIDISTRM hms)
{
    return Functions::midiStreamPause(hms);
}

MMRESULT WINAPI _midiStreamRestart(HMIDISTRM hms)
{
    return Functions::midiStreamRestart(hms);
}

MMRESULT WINAPI _midiStreamStop(HMIDISTRM hms)
{
    return Functions::midiStreamStop(hms);
}

MMRESULT WINAPI _midiConnect(HMIDI hmi, HMIDIOUT hmo, LPVOID pReserved)
{
    return Functions::midiConnect(hmi, hmo, pReserved);
}

MMRESULT WINAPI _midiDisconnect(HMIDI hmi, HMIDIOUT hmo, LPVOID pReserved)
{
    return Functions::midiDisconnect(hmi, hmo, pReserved);
}

MMRESULT WINAPI _midiOutGetDevCapsA(UINT_PTR uDeviceID, LPMIDIOUTCAPSA pmoc, UINT cbmoc)
{
    return Functions::midiOutGetDevCapsA(uDeviceID, pmoc, cbmoc);
}

MMRESULT WINAPI _midiOutGetDevCapsW(UINT_PTR uDeviceID, LPMIDIOUTCAPSW pmoc, UINT cbmoc)
{
    return Functions::midiOutGetDevCapsW(uDeviceID, pmoc, cbmoc);
}

MMRESULT WINAPI _midiOutGetVolume(HMIDIOUT hmo, LPDWORD pdwVolume)
{
    return Functions::midiOutGetVolume(hmo, pdwVolume);
}

MMRESULT WINAPI _midiOutSetVolume(HMIDIOUT hmo, DWORD dwVolume)
{
    return Functions::midiOutSetVolume(hmo, dwVolume);
}

MMRESULT WINAPI _midiOutGetErrorTextA(MMRESULT mmrError, LPSTR pszText, UINT cchText)
{
    return Functions::midiOutGetErrorTextA(mmrError, pszText, cchText);
}

MMRESULT WINAPI _midiOutGetErrorTextW(MMRESULT mmrError, LPWSTR pszText, UINT cchText)
{
    return Functions::midiOutGetErrorTextW(mmrError, pszText, cchText);
}

MMRESULT WINAPI _midiOutOpen(LPHMIDIOUT phmo, UINT uDeviceID, DWORD_PTR dwCallback, DWORD_PTR dwInstance, DWORD fdwOpen)
{
    return Functions::midiOutOpen(phmo, uDeviceID, dwCallback, dwInstance, fdwOpen);
}

MMRESULT WINAPI _midiOutClose(HMIDIOUT hmo)
{
    return Functions::midiOutClose(hmo);
}

MMRESULT WINAPI _midiOutPrepareHeader(HMIDIOUT hmo, LPMIDIHDR pmh, UINT cbmh)
{
    return Functions::midiOutPrepareHeader(hmo, pmh, cbmh);
}

MMRESULT WINAPI _midiOutUnprepareHeader(HMIDIOUT hmo, LPMIDIHDR pmh, UINT cbmh)
{
    return Functions::midiOutUnprepareHeader(hmo, pmh, cbmh);
}

MMRESULT WINAPI _midiOutShortMsg(HMIDIOUT hmo, DWORD dwMsg)
{
    return Functions::midiOutShortMsg(hmo, dwMsg);
}

MMRESULT WINAPI _midiOutLongMsg(HMIDIOUT hmo, LPMIDIHDR pmh, UINT cbmh)
{
    return Functions::midiOutLongMsg(hmo, pmh, cbmh);
}

MMRESULT WINAPI _midiOutReset(HMIDIOUT hmo)
{
    return Functions::midiOutReset(hmo);
}

MMRESULT WINAPI _midiOutCachePatches(HMIDIOUT hmo, UINT uBank, LPWORD pwpa, UINT fuCache)
{
    return Functions::midiOutCachePatches(hmo, uBank, pwpa, fuCache);
}

MMRESULT WINAPI _midiOutCacheDrumPatches(HMIDIOUT hmo, UINT uPatch, LPWORD pwkya, UINT fuCache)
{
    return Functions::midiOutCacheDrumPatches(hmo, uPatch, pwkya, fuCache);
}

MMRESULT WINAPI _midiOutGetID(HMIDIOUT hmo, LPUINT puDeviceID)
{
    return Functions::midiOutGetID(hmo, puDeviceID);
}

MMRESULT WINAPI _midiOutMessage(HMIDIOUT hmo, UINT uMsg, DWORD_PTR dw1, DWORD_PTR dw2)
{
    return Functions::midiOutMessage(hmo, uMsg, dw1, dw2);
}

UINT WINAPI _midiInGetNumDevs(void)
{
    return Functions::midiInGetNumDevs();
}

MMRESULT WINAPI _midiInGetDevCapsA(UINT_PTR uDeviceID, LPMIDIINCAPSA pmic, UINT cbmic)
{
    return Functions::midiInGetDevCapsA(uDeviceID, pmic, cbmic);
}

MMRESULT WINAPI _midiInGetDevCapsW(UINT_PTR uDeviceID, LPMIDIINCAPSW pmic, UINT cbmic)
{
    return Functions::midiInGetDevCapsW(uDeviceID, pmic, cbmic);
}

MMRESULT WINAPI _midiInGetErrorTextA(MMRESULT mmrError, LPSTR pszText, UINT cchText)
{
    return Functions::midiInGetErrorTextA(mmrError, pszText, cchText);
}

MMRESULT WINAPI _midiInGetErrorTextW(MMRESULT mmrError, LPWSTR pszText, UINT cchText)
{
    return Functions::midiInGetErrorTextW(mmrError, pszText, cchText);
}

MMRESULT WINAPI _midiInOpen(LPHMIDIIN phmi, UINT uDeviceID, DWORD_PTR dwCallback, DWORD_PTR dwInstance, DWORD fdwOpen)
{
    return Functions::midiInOpen(phmi, uDeviceID, dwCallback, dwInstance, fdwOpen);
}

MMRESULT WINAPI _midiInClose(HMIDIIN hmi)
{
    return Functions::midiInClose(hmi);
}

MMRESULT WINAPI _midiInPrepareHeader(HMIDIIN hmi, LPMIDIHDR pmh, UINT cbmh)
{
    return Functions::midiInPrepareHeader(hmi, pmh, cbmh);
}

MMRESULT WINAPI _midiInUnprepareHeader(HMIDIIN hmi, LPMIDIHDR pmh, UINT cbmh)
{
    return Functions::midiInUnprepareHeader(hmi, pmh, cbmh);
}

MMRESULT WINAPI _midiInAddBuffer(HMIDIIN hmi, LPMIDIHDR pmh, UINT cbmh)
{
    return Functions::midiInAddBuffer(hmi, pmh, cbmh);
}

MMRESULT WINAPI _midiInStart(HMIDIIN hmi)
{
    return Functions::midiInStart(hmi);
}

MMRESULT WINAPI _midiInStop(HMIDIIN hmi)
{
    return Functions::midiInStop(hmi);
}

MMRESULT WINAPI _midiInReset(HMIDIIN hmi)
{
    return Functions::midiInReset(hmi);
}

MMRESULT WINAPI _midiInGetID(HMIDIIN hmi, LPUINT puDeviceID)
{
    return Functions::midiInGetID(hmi, puDeviceID);
}

MMRESULT WINAPI _midiInMessage(HMIDIIN hmi, UINT uMsg, DWORD_PTR dw1, DWORD_PTR dw2)
{
    return Functions::midiInMessage(hmi, uMsg, dw1, dw2);
}

UINT WINAPI _mixerGetNumDevs(void)
{
    return Functions::mixerGetNumDevs();
}

MMRESULT WINAPI _mixerGetDevCapsA(UINT_PTR uMxId, LPMIXERCAPSA pmxcaps, UINT cbmxcaps)
{
    return Functions::mixerGetDevCapsA(uMxId, pmxcaps, cbmxcaps);
}

MMRESULT WINAPI _mixerGetDevCapsW(UINT_PTR uMxId, LPMIXERCAPSW pmxcaps, UINT cbmxcaps)
{
    return Functions::mixerGetDevCapsW(uMxId, pmxcaps, cbmxcaps);
}

MMRESULT WINAPI _mixerOpen(LPHMIXER phmx, UINT uMxId, DWORD_PTR dwCallback, DWORD_PTR dwInstance, DWORD fdwOpen)
{
    return Functions::mixerOpen(phmx, uMxId, dwCallback, dwInstance, fdwOpen);
}

MMRESULT WINAPI _mixerClose(HMIXER hmx)
{
    return Functions::mixerClose(hmx);
}

DWORD WINAPI _mixerMessage(HMIXER hmx, UINT uMsg, DWORD_PTR dwParam1, DWORD_PTR dwParam2)
{
    return Functions::mixerMessage(hmx, uMsg, dwParam1, dwParam2);
}

MMRESULT WINAPI _mixerGetLineInfoA(HMIXEROBJ hmxobj, LPMIXERLINEA pmxl, DWORD fdwInfo)
{
    return Functions::mixerGetLineInfoA(hmxobj, pmxl, fdwInfo);
}

MMRESULT WINAPI _mixerGetLineInfoW(HMIXEROBJ hmxobj, LPMIXERLINEW pmxl, DWORD fdwInfo)
{
    return Functions::mixerGetLineInfoW(hmxobj, pmxl, fdwInfo);
}

MMRESULT WINAPI _mixerGetID(HMIXEROBJ hmxobj, UINT FAR* puMxId, DWORD fdwId)
{
    return Functions::mixerGetID(hmxobj, puMxId, fdwId);
}

MMRESULT WINAPI _mixerGetLineControlsA(HMIXEROBJ hmxobj, LPMIXERLINECONTROLSA pmxlc, DWORD fdwControls)
{
    return Functions::mixerGetLineControlsA(hmxobj, pmxlc, fdwControls);
}

MMRESULT WINAPI _mixerGetLineControlsW(HMIXEROBJ hmxobj, LPMIXERLINECONTROLSW pmxlc, DWORD fdwControls)
{
    return Functions::mixerGetLineControlsW(hmxobj, pmxlc, fdwControls);
}

MMRESULT WINAPI _mixerGetControlDetailsA(HMIXEROBJ hmxobj, LPMIXERCONTROLDETAILS pmxcd, DWORD fdwDetails)
{
    return Functions::mixerGetControlDetailsA(hmxobj, pmxcd, fdwDetails);
}

MMRESULT WINAPI _mixerGetControlDetailsW(HMIXEROBJ hmxobj, LPMIXERCONTROLDETAILS pmxcd, DWORD fdwDetails)
{
    return Functions::mixerGetControlDetailsW(hmxobj, pmxcd, fdwDetails);
}

MMRESULT WINAPI _mixerSetControlDetails(HMIXEROBJ hmxobj, LPMIXERCONTROLDETAILS pmxcd, DWORD fdwDetails)
{
    return Functions::mixerSetControlDetails(hmxobj, pmxcd, fdwDetails);
}

UINT APIENTRY _mmDrvInstall(HDRVR hDriver, LPCWSTR wszDrvEntry, DRIVERMSGPROC drvMessage, UINT wFlags)
{
    return Functions::mmDrvInstall(hDriver, wszDrvEntry, drvMessage, wFlags);
}

UINT APIENTRY _mmTaskCreate(LPTASKCALLBACK lpfn, HANDLE FAR* lph, DWORD_PTR dwInst)
{
    return Functions::mmTaskCreate(lpfn, lph, dwInst);
}

VOID APIENTRY _mmTaskBlock(DWORD h)
{
    return Functions::mmTaskBlock(h);
}

BOOL APIENTRY _mmTaskSignal(DWORD h)
{
    return Functions::mmTaskSignal(h);
}

VOID APIENTRY _mmTaskYield(VOID)
{
    return Functions::mmTaskYield();
}

DWORD APIENTRY _mmGetCurrentTask(VOID)
{
    return Functions::mmGetCurrentTask();
}

FOURCC WINAPI _mmioStringToFOURCCA(LPCSTR sz, UINT uFlags)
{
    return Functions::mmioStringToFOURCCA(sz, uFlags);
}

FOURCC WINAPI _mmioStringToFOURCCW(LPCWSTR sz, UINT uFlags)
{
    return Functions::mmioStringToFOURCCW(sz, uFlags);
}

LPMMIOPROC WINAPI _mmioInstallIOProcA(FOURCC fccIOProc, LPMMIOPROC pIOProc, DWORD dwFlags)
{
    return Functions::mmioInstallIOProcA(fccIOProc, pIOProc, dwFlags);
}

LPMMIOPROC WINAPI _mmioInstallIOProcW(FOURCC fccIOProc, LPMMIOPROC pIOProc, DWORD dwFlags)
{
    return Functions::mmioInstallIOProcW(fccIOProc, pIOProc, dwFlags);
}

HMMIO WINAPI _mmioOpenA(LPSTR pszFileName, LPMMIOINFO pmmioinfo, DWORD fdwOpen)
{
    return Functions::mmioOpenA(pszFileName, pmmioinfo, fdwOpen);
}

HMMIO WINAPI _mmioOpenW(LPWSTR pszFileName, LPMMIOINFO pmmioinfo, DWORD fdwOpen)
{
    return Functions::mmioOpenW(pszFileName, pmmioinfo, fdwOpen);
}

MMRESULT WINAPI _mmioRenameA(LPCSTR pszFileName, LPCSTR pszNewFileName, LPCMMIOINFO pmmioinfo, DWORD fdwRename)
{
    return Functions::mmioRenameA(pszFileName, pszNewFileName, pmmioinfo, fdwRename);
}

MMRESULT WINAPI _mmioRenameW(LPCWSTR pszFileName, LPCWSTR pszNewFileName, LPCMMIOINFO pmmioinfo, DWORD fdwRename)
{
    return Functions::mmioRenameW(pszFileName, pszNewFileName, pmmioinfo, fdwRename);
}

MMRESULT WINAPI _mmioClose(HMMIO hmmio, UINT fuClose)
{
    return Functions::mmioClose(hmmio, fuClose);
}

LONG WINAPI _mmioRead(HMMIO hmmio, HPSTR pch, LONG cch)
{
    return Functions::mmioRead(hmmio, pch, cch);
}

LONG WINAPI _mmioWrite(HMMIO hmmio, const char _huge* pch, LONG cch)
{
    return Functions::mmioWrite(hmmio, pch, cch);
}

LONG WINAPI _mmioSeek(HMMIO hmmio, LONG lOffset, int iOrigin)
{
    return Functions::mmioSeek(hmmio, lOffset, iOrigin);
}

MMRESULT WINAPI _mmioGetInfo(HMMIO hmmio, LPMMIOINFO pmmioinfo, UINT fuInfo)
{
    return Functions::mmioGetInfo(hmmio, pmmioinfo, fuInfo);
}

MMRESULT WINAPI _mmioSetInfo(HMMIO hmmio, LPCMMIOINFO pmmioinfo, UINT fuInfo)
{
    return Functions::mmioSetInfo(hmmio, pmmioinfo, fuInfo);
}

MMRESULT WINAPI _mmioSetBuffer(HMMIO hmmio, LPSTR pchBuffer, LONG cchBuffer, UINT fuBuffer)
{
    return Functions::mmioSetBuffer(hmmio, pchBuffer, cchBuffer, fuBuffer);
}

MMRESULT WINAPI _mmioFlush(HMMIO hmmio, UINT fuFlush)
{
    return Functions::mmioFlush(hmmio, fuFlush);
}

MMRESULT WINAPI _mmioAdvance(HMMIO hmmio, LPMMIOINFO pmmioinfo, UINT fuAdvance)
{
    return Functions::mmioAdvance(hmmio, pmmioinfo, fuAdvance);
}

LRESULT WINAPI _mmioSendMessage(HMMIO hmmio, UINT uMsg, LPARAM lParam1, LPARAM lParam2)
{
    return Functions::mmioSendMessage(hmmio, uMsg, lParam1, lParam2);
}

MMRESULT WINAPI _mmioDescend(HMMIO hmmio, LPMMCKINFO pmmcki, const MMCKINFO FAR* pmmckiParent, UINT fuDescend)
{
    return Functions::mmioDescend(hmmio, pmmcki, pmmckiParent, fuDescend);
}

MMRESULT WINAPI _mmioAscend(HMMIO hmmio, LPMMCKINFO pmmcki, UINT fuAscend)
{
    return Functions::mmioAscend(hmmio, pmmcki, fuAscend);
}

MMRESULT WINAPI _mmioCreateChunk(HMMIO hmmio, LPMMCKINFO pmmcki, UINT fuCreate)
{
    return Functions::mmioCreateChunk(hmmio, pmmcki, fuCreate);
}

BOOL WINAPI _sndPlaySoundA(LPCSTR pszSound, UINT fuSound)
{
    return Functions::sndPlaySoundA(pszSound, fuSound);
}

BOOL WINAPI _sndPlaySoundW(LPCWSTR pszSound, UINT fuSound)
{
    return Functions::sndPlaySoundW(pszSound, fuSound);
}

MMRESULT WINAPI _timeGetSystemTime(LPMMTIME pmmt, UINT cbmmt)
{
    return Functions::timeGetSystemTime(pmmt, cbmmt);
}

DWORD WINAPI _timeGetTime(void)
{
    return Functions::timeGetTime();
}

MMRESULT WINAPI _timeGetDevCaps(LPTIMECAPS ptc, UINT cbtc)
{
    return Functions::timeGetDevCaps(ptc, cbtc);
}

MMRESULT WINAPI _timeBeginPeriod(UINT uPeriod)
{
    return Functions::timeBeginPeriod(uPeriod);
}

MMRESULT WINAPI _timeEndPeriod(UINT uPeriod)
{
    return Functions::timeEndPeriod(uPeriod);
}

MMRESULT WINAPI _timeSetEvent(UINT uDelay, UINT uResolution, LPTIMECALLBACK fptc, DWORD_PTR dwUser, UINT fuEvent)
{
    return Functions::timeSetEvent(uDelay, uResolution, fptc, dwUser, fuEvent);
}

MMRESULT WINAPI _timeKillEvent(UINT uTimerID)
{
    return Functions::timeKillEvent(uTimerID);
}

UINT WINAPI _waveOutGetNumDevs(void)
{
    return Functions::waveOutGetNumDevs();
}

MMRESULT WINAPI _waveOutGetDevCapsA(UINT_PTR uDeviceID, LPWAVEOUTCAPSA pwoc, UINT cbwoc)
{
    return Functions::waveOutGetDevCapsA(uDeviceID, pwoc, cbwoc);
}

MMRESULT WINAPI _waveOutGetDevCapsW(UINT_PTR uDeviceID, LPWAVEOUTCAPSW pwoc, UINT cbwoc)
{
    return Functions::waveOutGetDevCapsW(uDeviceID, pwoc, cbwoc);
}

MMRESULT WINAPI _waveOutGetVolume(HWAVEOUT hwo, LPDWORD pdwVolume)
{
    return Functions::waveOutGetVolume(hwo, pdwVolume);
}

MMRESULT WINAPI _waveOutSetVolume(HWAVEOUT hwo, DWORD dwVolume)
{
    return Functions::waveOutSetVolume(hwo, dwVolume);
}

MMRESULT WINAPI _waveOutGetErrorTextA(MMRESULT mmrError, LPSTR pszText, UINT cchText)
{
    return Functions::waveOutGetErrorTextA(mmrError, pszText, cchText);
}

MMRESULT WINAPI _waveOutGetErrorTextW(MMRESULT mmrError, LPWSTR pszText, UINT cchText)
{
    return Functions::waveOutGetErrorTextW(mmrError, pszText, cchText);
}

MMRESULT WINAPI _waveOutOpen(LPHWAVEOUT phwo, UINT uDeviceID, LPCWAVEFORMATEX pwfx, DWORD_PTR dwCallback,
                             DWORD_PTR dwInstance, DWORD fdwOpen)
{
    return Functions::waveOutOpen(phwo, uDeviceID, pwfx, dwCallback, dwInstance, fdwOpen);
}

MMRESULT WINAPI _waveOutClose(HWAVEOUT hwo)
{
    return Functions::waveOutClose(hwo);
}

MMRESULT WINAPI _waveOutPrepareHeader(HWAVEOUT hwo, LPWAVEHDR pwh, UINT cbwh)
{
    return Functions::waveOutPrepareHeader(hwo, pwh, cbwh);
}

MMRESULT WINAPI _waveOutUnprepareHeader(HWAVEOUT hwo, LPWAVEHDR pwh, UINT cbwh)
{
    return Functions::waveOutUnprepareHeader(hwo, pwh, cbwh);
}

MMRESULT WINAPI _waveOutWrite(HWAVEOUT hwo, LPWAVEHDR pwh, UINT cbwh)
{
    return Functions::waveOutWrite(hwo, pwh, cbwh);
}

MMRESULT WINAPI _waveOutPause(HWAVEOUT hwo)
{
    return Functions::waveOutPause(hwo);
}

MMRESULT WINAPI _waveOutRestart(HWAVEOUT hwo)
{
    return Functions::waveOutRestart(hwo);
}

MMRESULT WINAPI _waveOutReset(HWAVEOUT hwo)
{
    return Functions::waveOutReset(hwo);
}

MMRESULT WINAPI _waveOutBreakLoop(HWAVEOUT hwo)
{
    return Functions::waveOutBreakLoop(hwo);
}

MMRESULT WINAPI _waveOutGetPosition(HWAVEOUT hwo, LPMMTIME pmmt, UINT cbmmt)
{
    return Functions::waveOutGetPosition(hwo, pmmt, cbmmt);
}

MMRESULT WINAPI _waveOutGetPitch(HWAVEOUT hwo, LPDWORD pdwPitch)
{
    return Functions::waveOutGetPitch(hwo, pdwPitch);
}

MMRESULT WINAPI _waveOutSetPitch(HWAVEOUT hwo, DWORD dwPitch)
{
    return Functions::waveOutSetPitch(hwo, dwPitch);
}

MMRESULT WINAPI _waveOutGetPlaybackRate(HWAVEOUT hwo, LPDWORD pdwRate)
{
    return Functions::waveOutGetPlaybackRate(hwo, pdwRate);
}

MMRESULT WINAPI _waveOutSetPlaybackRate(HWAVEOUT hwo, DWORD dwRate)
{
    return Functions::waveOutSetPlaybackRate(hwo, dwRate);
}

MMRESULT WINAPI _waveOutGetID(HWAVEOUT hwo, LPUINT puDeviceID)
{
    return Functions::waveOutGetID(hwo, puDeviceID);
}

MMRESULT WINAPI _waveOutMessage(HWAVEOUT hwo, UINT uMsg, DWORD_PTR dw1, DWORD_PTR dw2)
{
    return Functions::waveOutMessage(hwo, uMsg, dw1, dw2);
}

UINT WINAPI _waveInGetNumDevs(void)
{
    return Functions::waveInGetNumDevs();
}

MMRESULT WINAPI _waveInGetDevCapsA(UINT_PTR uDeviceID, LPWAVEINCAPSA pwic, UINT cbwic)
{
    return Functions::waveInGetDevCapsA(uDeviceID, pwic, cbwic);
}

MMRESULT WINAPI _waveInGetDevCapsW(UINT_PTR uDeviceID, LPWAVEINCAPSW pwic, UINT cbwic)
{
    return Functions::waveInGetDevCapsW(uDeviceID, pwic, cbwic);
}

MMRESULT WINAPI _waveInGetErrorTextA(MMRESULT mmrError, LPSTR pszText, UINT cchText)
{
    return Functions::waveInGetErrorTextA(mmrError, pszText, cchText);
}

MMRESULT WINAPI _waveInGetErrorTextW(MMRESULT mmrError, LPWSTR pszText, UINT cchText)
{
    return Functions::waveInGetErrorTextW(mmrError, pszText, cchText);
}

MMRESULT WINAPI _waveInOpen(LPHWAVEIN phwi, UINT uDeviceID, LPCWAVEFORMATEX pwfx, DWORD_PTR dwCallback,
                            DWORD_PTR dwInstance, DWORD fdwOpen)
{
    return Functions::waveInOpen(phwi, uDeviceID, pwfx, dwCallback, dwInstance, fdwOpen);
}

MMRESULT WINAPI _waveInClose(HWAVEIN hwi)
{
    return Functions::waveInClose(hwi);
}

MMRESULT WINAPI _waveInPrepareHeader(HWAVEIN hwi, LPWAVEHDR pwh, UINT cbwh)
{
    return Functions::waveInPrepareHeader(hwi, pwh, cbwh);
}

MMRESULT WINAPI _waveInUnprepareHeader(HWAVEIN hwi, LPWAVEHDR pwh, UINT cbwh)
{
    return Functions::waveInUnprepareHeader(hwi, pwh, cbwh);
}

MMRESULT WINAPI _waveInAddBuffer(HWAVEIN hwi, LPWAVEHDR pwh, UINT cbwh)
{
    return Functions::waveInAddBuffer(hwi, pwh, cbwh);
}

MMRESULT WINAPI _waveInStart(HWAVEIN hwi)
{
    return Functions::waveInStart(hwi);
}

MMRESULT WINAPI _waveInStop(HWAVEIN hwi)
{
    return Functions::waveInStop(hwi);
}

MMRESULT WINAPI _waveInReset(HWAVEIN hwi)
{
    return Functions::waveInReset(hwi);
}

MMRESULT WINAPI _waveInGetPosition(HWAVEIN hwi, LPMMTIME pmmt, UINT cbmmt)
{
    return Functions::waveInGetPosition(hwi, pmmt, cbmmt);
}

MMRESULT WINAPI _waveInGetID(HWAVEIN hwi, LPUINT puDeviceID)
{
    return Functions::waveInGetID(hwi, puDeviceID);
}

MMRESULT WINAPI _waveInMessage(HWAVEIN hwi, UINT uMsg, DWORD_PTR dw1, DWORD_PTR dw2)
{
    return Functions::waveInMessage(hwi, uMsg, dw1, dw2);
}

VOID WINAPI _WOWAppExit()
{
    return Functions::WOWAppExit();
}

BOOL WINAPI _mciExecute(LPCSTR pszCommand)
{
    return Functions::mciExecute(pszCommand);
}

UINT WINAPI _mmsystemGetVersion()
{
    return Functions::mmsystemGetVersion();
}

BOOL WINAPI _PlaySoundStub(LPCSTR pszSound, HMODULE hmod, DWORD fdwSound)
{
    return Functions::PlaySoundStub(pszSound, hmod, fdwSound);
}

bool winmm::LoadOriginal()
{
    wil::unique_cotaskmem_string rawPath;
    if (FAILED(SHGetKnownFolderPath(FOLDERID_System, KF_FLAG_DEFAULT, nullptr, &rawPath)))
    {
        return false;
    }

    constexpr auto dllName = "winmm.dll";

    std::filesystem::path dll = rawPath.get();
    dll /= dllName;

    auto handle = LoadLibrary(dll.c_str());
    if (!handle)
    {
        return false;
    }

    Functions::CloseDriver = reinterpret_cast<CloseDriver_t>(GetProcAddress(handle, "CloseDriver"));
    Functions::OpenDriver = reinterpret_cast<OpenDriver_t>(GetProcAddress(handle, "OpenDriver"));
    Functions::SendDriverMessage = reinterpret_cast<SendDriverMessage_t>(GetProcAddress(handle, "SendDriverMessage"));
    Functions::DrvGetModuleHandle =
        reinterpret_cast<DrvGetModuleHandle_t>(GetProcAddress(handle, "DrvGetModuleHandle"));
    Functions::GetDriverModuleHandle =
        reinterpret_cast<GetDriverModuleHandle_t>(GetProcAddress(handle, "GetDriverModuleHandle"));
    Functions::DefDriverProc = reinterpret_cast<DefDriverProc_t>(GetProcAddress(handle, "DefDriverProc"));
    Functions::DriverCallback = reinterpret_cast<DriverCallback_t>(GetProcAddress(handle, "DriverCallback"));
    Functions::PlaySound = reinterpret_cast<PlaySound_t>(GetProcAddress(handle, "PlaySound"));
    Functions::PlaySoundA = reinterpret_cast<PlaySoundA_t>(GetProcAddress(handle, "PlaySoundA"));
    Functions::PlaySoundW = reinterpret_cast<PlaySoundW_t>(GetProcAddress(handle, "PlaySoundW"));
    Functions::auxGetNumDevs = reinterpret_cast<auxGetNumDevs_t>(GetProcAddress(handle, "auxGetNumDevs"));
    Functions::auxGetDevCapsA = reinterpret_cast<auxGetDevCapsA_t>(GetProcAddress(handle, "auxGetDevCapsA"));
    Functions::auxGetDevCapsW = reinterpret_cast<auxGetDevCapsW_t>(GetProcAddress(handle, "auxGetDevCapsW"));
    Functions::auxSetVolume = reinterpret_cast<auxSetVolume_t>(GetProcAddress(handle, "auxSetVolume"));
    Functions::auxGetVolume = reinterpret_cast<auxGetVolume_t>(GetProcAddress(handle, "auxGetVolume"));
    Functions::auxOutMessage = reinterpret_cast<auxOutMessage_t>(GetProcAddress(handle, "auxOutMessage"));
    Functions::joyGetPos = reinterpret_cast<joyGetPos_t>(GetProcAddress(handle, "joyGetPos"));
    Functions::joyGetThreshold = reinterpret_cast<joyGetThreshold_t>(GetProcAddress(handle, "joyGetThreshold"));
    Functions::joyReleaseCapture = reinterpret_cast<joyReleaseCapture_t>(GetProcAddress(handle, "joyReleaseCapture"));
    Functions::joySetCapture = reinterpret_cast<joySetCapture_t>(GetProcAddress(handle, "joySetCapture"));
    Functions::joySetThreshold = reinterpret_cast<joySetThreshold_t>(GetProcAddress(handle, "joySetThreshold"));
    Functions::joyConfigChanged = reinterpret_cast<joyConfigChanged_t>(GetProcAddress(handle, "joyConfigChanged"));
    Functions::joyGetPosEx = reinterpret_cast<joyGetPosEx_t>(GetProcAddress(handle, "joyGetPosEx"));
    Functions::joyGetNumDevs = reinterpret_cast<joyGetNumDevs_t>(GetProcAddress(handle, "joyGetNumDevs"));
    Functions::joyGetDevCapsA = reinterpret_cast<joyGetDevCapsA_t>(GetProcAddress(handle, "joyGetDevCapsA"));
    Functions::joyGetDevCapsW = reinterpret_cast<joyGetDevCapsW_t>(GetProcAddress(handle, "joyGetDevCapsW"));
    Functions::mciSendCommandA = reinterpret_cast<mciSendCommandA_t>(GetProcAddress(handle, "mciSendCommandA"));
    Functions::mciSendCommandW = reinterpret_cast<mciSendCommandW_t>(GetProcAddress(handle, "mciSendCommandW"));
    Functions::mciSendStringA = reinterpret_cast<mciSendStringA_t>(GetProcAddress(handle, "mciSendStringA"));
    Functions::mciSendStringW = reinterpret_cast<mciSendStringW_t>(GetProcAddress(handle, "mciSendStringW"));
    Functions::mciGetDeviceIDA = reinterpret_cast<mciGetDeviceIDA_t>(GetProcAddress(handle, "mciGetDeviceIDA"));
    Functions::mciGetDeviceIDW = reinterpret_cast<mciGetDeviceIDW_t>(GetProcAddress(handle, "mciGetDeviceIDW"));
    Functions::mciGetDeviceIDFromElementIDA =
        reinterpret_cast<mciGetDeviceIDFromElementIDA_t>(GetProcAddress(handle, "mciGetDeviceIDFromElementIDA"));
    Functions::mciGetDeviceIDFromElementIDW =
        reinterpret_cast<mciGetDeviceIDFromElementIDW_t>(GetProcAddress(handle, "mciGetDeviceIDFromElementIDW"));
    Functions::mciGetErrorStringA =
        reinterpret_cast<mciGetErrorStringA_t>(GetProcAddress(handle, "mciGetErrorStringA"));
    Functions::mciGetErrorStringW =
        reinterpret_cast<mciGetErrorStringW_t>(GetProcAddress(handle, "mciGetErrorStringW"));
    Functions::mciSetYieldProc = reinterpret_cast<mciSetYieldProc_t>(GetProcAddress(handle, "mciSetYieldProc"));
    Functions::mciGetCreatorTask = reinterpret_cast<mciGetCreatorTask_t>(GetProcAddress(handle, "mciGetCreatorTask"));
    Functions::mciGetYieldProc = reinterpret_cast<mciGetYieldProc_t>(GetProcAddress(handle, "mciGetYieldProc"));
    Functions::mciGetDriverData = reinterpret_cast<mciGetDriverData_t>(GetProcAddress(handle, "mciGetDriverData"));
    Functions::mciLoadCommandResource =
        reinterpret_cast<mciLoadCommandResource_t>(GetProcAddress(handle, "mciLoadCommandResource"));
    Functions::mciSetDriverData = reinterpret_cast<mciSetDriverData_t>(GetProcAddress(handle, "mciSetDriverData"));
    Functions::mciDriverYield = reinterpret_cast<mciDriverYield_t>(GetProcAddress(handle, "mciDriverYield"));
    Functions::mciDriverNotify = reinterpret_cast<mciDriverNotify_t>(GetProcAddress(handle, "mciDriverNotify"));
    Functions::mciFreeCommandResource =
        reinterpret_cast<mciFreeCommandResource_t>(GetProcAddress(handle, "mciFreeCommandResource"));
    Functions::midiOutGetNumDevs = reinterpret_cast<midiOutGetNumDevs_t>(GetProcAddress(handle, "midiOutGetNumDevs"));
    Functions::midiStreamOpen = reinterpret_cast<midiStreamOpen_t>(GetProcAddress(handle, "midiStreamOpen"));
    Functions::midiStreamClose = reinterpret_cast<midiStreamClose_t>(GetProcAddress(handle, "midiStreamClose"));
    Functions::midiStreamProperty =
        reinterpret_cast<midiStreamProperty_t>(GetProcAddress(handle, "midiStreamProperty"));
    Functions::midiStreamPosition =
        reinterpret_cast<midiStreamPosition_t>(GetProcAddress(handle, "midiStreamPosition"));
    Functions::midiStreamOut = reinterpret_cast<midiStreamOut_t>(GetProcAddress(handle, "midiStreamOut"));
    Functions::midiStreamPause = reinterpret_cast<midiStreamPause_t>(GetProcAddress(handle, "midiStreamPause"));
    Functions::midiStreamRestart = reinterpret_cast<midiStreamRestart_t>(GetProcAddress(handle, "midiStreamRestart"));
    Functions::midiStreamStop = reinterpret_cast<midiStreamStop_t>(GetProcAddress(handle, "midiStreamStop"));
    Functions::midiConnect = reinterpret_cast<midiConnect_t>(GetProcAddress(handle, "midiConnect"));
    Functions::midiDisconnect = reinterpret_cast<midiDisconnect_t>(GetProcAddress(handle, "midiDisconnect"));
    Functions::midiOutGetDevCapsA =
        reinterpret_cast<midiOutGetDevCapsA_t>(GetProcAddress(handle, "midiOutGetDevCapsA"));
    Functions::midiOutGetDevCapsW =
        reinterpret_cast<midiOutGetDevCapsW_t>(GetProcAddress(handle, "midiOutGetDevCapsW"));
    Functions::midiOutGetVolume = reinterpret_cast<midiOutGetVolume_t>(GetProcAddress(handle, "midiOutGetVolume"));
    Functions::midiOutSetVolume = reinterpret_cast<midiOutSetVolume_t>(GetProcAddress(handle, "midiOutSetVolume"));
    Functions::midiOutGetErrorTextA =
        reinterpret_cast<midiOutGetErrorTextA_t>(GetProcAddress(handle, "midiOutGetErrorTextA"));
    Functions::midiOutGetErrorTextW =
        reinterpret_cast<midiOutGetErrorTextW_t>(GetProcAddress(handle, "midiOutGetErrorTextW"));
    Functions::midiOutOpen = reinterpret_cast<midiOutOpen_t>(GetProcAddress(handle, "midiOutOpen"));
    Functions::midiOutClose = reinterpret_cast<midiOutClose_t>(GetProcAddress(handle, "midiOutClose"));
    Functions::midiOutPrepareHeader =
        reinterpret_cast<midiOutPrepareHeader_t>(GetProcAddress(handle, "midiOutPrepareHeader"));
    Functions::midiOutUnprepareHeader =
        reinterpret_cast<midiOutUnprepareHeader_t>(GetProcAddress(handle, "midiOutUnprepareHeader"));
    Functions::midiOutShortMsg = reinterpret_cast<midiOutShortMsg_t>(GetProcAddress(handle, "midiOutShortMsg"));
    Functions::midiOutLongMsg = reinterpret_cast<midiOutLongMsg_t>(GetProcAddress(handle, "midiOutLongMsg"));
    Functions::midiOutReset = reinterpret_cast<midiOutReset_t>(GetProcAddress(handle, "midiOutReset"));
    Functions::midiOutCachePatches =
        reinterpret_cast<midiOutCachePatches_t>(GetProcAddress(handle, "midiOutCachePatches"));
    Functions::midiOutCacheDrumPatches =
        reinterpret_cast<midiOutCacheDrumPatches_t>(GetProcAddress(handle, "midiOutCacheDrumPatches"));
    Functions::midiOutGetID = reinterpret_cast<midiOutGetID_t>(GetProcAddress(handle, "midiOutGetID"));
    Functions::midiOutMessage = reinterpret_cast<midiOutMessage_t>(GetProcAddress(handle, "midiOutMessage"));
    Functions::midiInGetNumDevs = reinterpret_cast<midiInGetNumDevs_t>(GetProcAddress(handle, "midiInGetNumDevs"));
    Functions::midiInGetDevCapsA = reinterpret_cast<midiInGetDevCapsA_t>(GetProcAddress(handle, "midiInGetDevCapsA"));
    Functions::midiInGetDevCapsW = reinterpret_cast<midiInGetDevCapsW_t>(GetProcAddress(handle, "midiInGetDevCapsW"));
    Functions::midiInGetErrorTextA =
        reinterpret_cast<midiInGetErrorTextA_t>(GetProcAddress(handle, "midiInGetErrorTextA"));
    Functions::midiInGetErrorTextW =
        reinterpret_cast<midiInGetErrorTextW_t>(GetProcAddress(handle, "midiInGetErrorTextW"));
    Functions::midiInOpen = reinterpret_cast<midiInOpen_t>(GetProcAddress(handle, "midiInOpen"));
    Functions::midiInClose = reinterpret_cast<midiInClose_t>(GetProcAddress(handle, "midiInClose"));
    Functions::midiInPrepareHeader =
        reinterpret_cast<midiInPrepareHeader_t>(GetProcAddress(handle, "midiInPrepareHeader"));
    Functions::midiInUnprepareHeader =
        reinterpret_cast<midiInUnprepareHeader_t>(GetProcAddress(handle, "midiInUnprepareHeader"));
    Functions::midiInAddBuffer = reinterpret_cast<midiInAddBuffer_t>(GetProcAddress(handle, "midiInAddBuffer"));
    Functions::midiInStart = reinterpret_cast<midiInStart_t>(GetProcAddress(handle, "midiInStart"));
    Functions::midiInStop = reinterpret_cast<midiInStop_t>(GetProcAddress(handle, "midiInStop"));
    Functions::midiInReset = reinterpret_cast<midiInReset_t>(GetProcAddress(handle, "midiInReset"));
    Functions::midiInGetID = reinterpret_cast<midiInGetID_t>(GetProcAddress(handle, "midiInGetID"));
    Functions::midiInMessage = reinterpret_cast<midiInMessage_t>(GetProcAddress(handle, "midiInMessage"));
    Functions::mixerGetNumDevs = reinterpret_cast<mixerGetNumDevs_t>(GetProcAddress(handle, "mixerGetNumDevs"));
    Functions::mixerGetDevCapsA = reinterpret_cast<mixerGetDevCapsA_t>(GetProcAddress(handle, "mixerGetDevCapsA"));
    Functions::mixerGetDevCapsW = reinterpret_cast<mixerGetDevCapsW_t>(GetProcAddress(handle, "mixerGetDevCapsW"));
    Functions::mixerOpen = reinterpret_cast<mixerOpen_t>(GetProcAddress(handle, "mixerOpen"));
    Functions::mixerClose = reinterpret_cast<mixerClose_t>(GetProcAddress(handle, "mixerClose"));
    Functions::mixerMessage = reinterpret_cast<mixerMessage_t>(GetProcAddress(handle, "mixerMessage"));
    Functions::mixerGetLineInfoA = reinterpret_cast<mixerGetLineInfoA_t>(GetProcAddress(handle, "mixerGetLineInfoA"));
    Functions::mixerGetLineInfoW = reinterpret_cast<mixerGetLineInfoW_t>(GetProcAddress(handle, "mixerGetLineInfoW"));
    Functions::mixerGetID = reinterpret_cast<mixerGetID_t>(GetProcAddress(handle, "mixerGetID"));
    Functions::mixerGetLineControlsA =
        reinterpret_cast<mixerGetLineControlsA_t>(GetProcAddress(handle, "mixerGetLineControlsA"));
    Functions::mixerGetLineControlsW =
        reinterpret_cast<mixerGetLineControlsW_t>(GetProcAddress(handle, "mixerGetLineControlsW"));
    Functions::mixerGetControlDetailsA =
        reinterpret_cast<mixerGetControlDetailsA_t>(GetProcAddress(handle, "mixerGetControlDetailsA"));
    Functions::mixerGetControlDetailsW =
        reinterpret_cast<mixerGetControlDetailsW_t>(GetProcAddress(handle, "mixerGetControlDetailsW"));
    Functions::mixerSetControlDetails =
        reinterpret_cast<mixerSetControlDetails_t>(GetProcAddress(handle, "mixerSetControlDetails"));
    Functions::mmDrvInstall = reinterpret_cast<mmDrvInstall_t>(GetProcAddress(handle, "mmDrvInstall"));
    Functions::mmTaskCreate = reinterpret_cast<mmTaskCreate_t>(GetProcAddress(handle, "mmTaskCreate"));
    Functions::mmTaskBlock = reinterpret_cast<mmTaskBlock_t>(GetProcAddress(handle, "mmTaskBlock"));
    Functions::mmTaskSignal = reinterpret_cast<mmTaskSignal_t>(GetProcAddress(handle, "mmTaskSignal"));
    Functions::mmTaskYield = reinterpret_cast<mmTaskYield_t>(GetProcAddress(handle, "mmTaskYield"));
    Functions::mmGetCurrentTask = reinterpret_cast<mmGetCurrentTask_t>(GetProcAddress(handle, "mmGetCurrentTask"));
    Functions::mmioStringToFOURCCA =
        reinterpret_cast<mmioStringToFOURCCA_t>(GetProcAddress(handle, "mmioStringToFOURCCA"));
    Functions::mmioStringToFOURCCW =
        reinterpret_cast<mmioStringToFOURCCW_t>(GetProcAddress(handle, "mmioStringToFOURCCW"));
    Functions::mmioInstallIOProcA =
        reinterpret_cast<mmioInstallIOProcA_t>(GetProcAddress(handle, "mmioInstallIOProcA"));
    Functions::mmioInstallIOProcW =
        reinterpret_cast<mmioInstallIOProcW_t>(GetProcAddress(handle, "mmioInstallIOProcW"));
    Functions::mmioOpenA = reinterpret_cast<mmioOpenA_t>(GetProcAddress(handle, "mmioOpenA"));
    Functions::mmioOpenW = reinterpret_cast<mmioOpenW_t>(GetProcAddress(handle, "mmioOpenW"));
    Functions::mmioRenameA = reinterpret_cast<mmioRenameA_t>(GetProcAddress(handle, "mmioRenameA"));
    Functions::mmioRenameW = reinterpret_cast<mmioRenameW_t>(GetProcAddress(handle, "mmioRenameW"));
    Functions::mmioClose = reinterpret_cast<mmioClose_t>(GetProcAddress(handle, "mmioClose"));
    Functions::mmioRead = reinterpret_cast<mmioRead_t>(GetProcAddress(handle, "mmioRead"));
    Functions::mmioWrite = reinterpret_cast<mmioWrite_t>(GetProcAddress(handle, "mmioWrite"));
    Functions::mmioSeek = reinterpret_cast<mmioSeek_t>(GetProcAddress(handle, "mmioSeek"));
    Functions::mmioGetInfo = reinterpret_cast<mmioGetInfo_t>(GetProcAddress(handle, "mmioGetInfo"));
    Functions::mmioSetInfo = reinterpret_cast<mmioSetInfo_t>(GetProcAddress(handle, "mmioSetInfo"));
    Functions::mmioSetBuffer = reinterpret_cast<mmioSetBuffer_t>(GetProcAddress(handle, "mmioSetBuffer"));
    Functions::mmioFlush = reinterpret_cast<mmioFlush_t>(GetProcAddress(handle, "mmioFlush"));
    Functions::mmioAdvance = reinterpret_cast<mmioAdvance_t>(GetProcAddress(handle, "mmioAdvance"));
    Functions::mmioSendMessage = reinterpret_cast<mmioSendMessage_t>(GetProcAddress(handle, "mmioSendMessage"));
    Functions::mmioAscend = reinterpret_cast<mmioAscend_t>(GetProcAddress(handle, "mmioAscend"));
    Functions::mmioDescend = reinterpret_cast<mmioDescend_t>(GetProcAddress(handle, "mmioDescend"));
    Functions::mmioCreateChunk = reinterpret_cast<mmioCreateChunk_t>(GetProcAddress(handle, "mmioCreateChunk"));
    Functions::sndPlaySoundA = reinterpret_cast<sndPlaySoundA_t>(GetProcAddress(handle, "sndPlaySoundA"));
    Functions::sndPlaySoundW = reinterpret_cast<sndPlaySoundW_t>(GetProcAddress(handle, "sndPlaySoundW"));
    Functions::timeGetSystemTime = reinterpret_cast<timeGetSystemTime_t>(GetProcAddress(handle, "timeGetSystemTime"));
    Functions::timeGetTime = reinterpret_cast<timeGetTime_t>(GetProcAddress(handle, "timeGetTime"));
    Functions::timeGetDevCaps = reinterpret_cast<timeGetDevCaps_t>(GetProcAddress(handle, "timeGetDevCaps"));
    Functions::timeBeginPeriod = reinterpret_cast<timeBeginPeriod_t>(GetProcAddress(handle, "timeBeginPeriod"));
    Functions::timeEndPeriod = reinterpret_cast<timeEndPeriod_t>(GetProcAddress(handle, "timeEndPeriod"));
    Functions::timeKillEvent = reinterpret_cast<timeKillEvent_t>(GetProcAddress(handle, "timeKillEvent"));
    Functions::timeSetEvent = reinterpret_cast<timeSetEvent_t>(GetProcAddress(handle, "timeSetEvent"));
    Functions::waveOutGetNumDevs = reinterpret_cast<waveOutGetNumDevs_t>(GetProcAddress(handle, "waveOutGetNumDevs"));
    Functions::waveOutGetDevCapsA =
        reinterpret_cast<waveOutGetDevCapsA_t>(GetProcAddress(handle, "waveOutGetDevCapsA"));
    Functions::waveOutGetDevCapsW =
        reinterpret_cast<waveOutGetDevCapsW_t>(GetProcAddress(handle, "waveOutGetDevCapsW"));
    Functions::waveOutGetVolume = reinterpret_cast<waveOutGetVolume_t>(GetProcAddress(handle, "waveOutGetVolume"));
    Functions::waveOutSetVolume = reinterpret_cast<waveOutSetVolume_t>(GetProcAddress(handle, "waveOutSetVolume"));
    Functions::waveOutGetErrorTextA =
        reinterpret_cast<waveOutGetErrorTextA_t>(GetProcAddress(handle, "waveOutGetErrorTextA"));
    Functions::waveOutGetErrorTextW =
        reinterpret_cast<waveOutGetErrorTextW_t>(GetProcAddress(handle, "waveOutGetErrorTextW"));
    Functions::waveOutOpen = reinterpret_cast<waveOutOpen_t>(GetProcAddress(handle, "waveOutOpen"));
    Functions::waveOutClose = reinterpret_cast<waveOutClose_t>(GetProcAddress(handle, "waveOutClose"));
    Functions::waveOutPrepareHeader =
        reinterpret_cast<waveOutPrepareHeader_t>(GetProcAddress(handle, "waveOutPrepareHeader"));
    Functions::waveOutUnprepareHeader =
        reinterpret_cast<waveOutUnprepareHeader_t>(GetProcAddress(handle, "waveOutUnprepareHeader"));
    Functions::waveOutWrite = reinterpret_cast<waveOutWrite_t>(GetProcAddress(handle, "waveOutWrite"));
    Functions::waveOutPause = reinterpret_cast<waveOutPause_t>(GetProcAddress(handle, "waveOutPause"));
    Functions::waveOutRestart = reinterpret_cast<waveOutRestart_t>(GetProcAddress(handle, "waveOutRestart"));
    Functions::waveOutReset = reinterpret_cast<waveOutReset_t>(GetProcAddress(handle, "waveOutReset"));
    Functions::waveOutBreakLoop = reinterpret_cast<waveOutBreakLoop_t>(GetProcAddress(handle, "waveOutBreakLoop"));
    Functions::waveOutGetPosition =
        reinterpret_cast<waveOutGetPosition_t>(GetProcAddress(handle, "waveOutGetPosition"));
    Functions::waveOutGetPitch = reinterpret_cast<waveOutGetPitch_t>(GetProcAddress(handle, "waveOutGetPitch"));
    Functions::waveOutSetPitch = reinterpret_cast<waveOutSetPitch_t>(GetProcAddress(handle, "waveOutSetPitch"));
    Functions::waveOutGetPlaybackRate =
        reinterpret_cast<waveOutGetPlaybackRate_t>(GetProcAddress(handle, "waveOutGetPlaybackRate"));
    Functions::waveOutSetPlaybackRate =
        reinterpret_cast<waveOutSetPlaybackRate_t>(GetProcAddress(handle, "waveOutSetPlaybackRate"));
    Functions::waveOutGetID = reinterpret_cast<waveOutGetID_t>(GetProcAddress(handle, "waveOutGetID"));
    Functions::waveOutMessage = reinterpret_cast<waveOutMessage_t>(GetProcAddress(handle, "waveOutMessage"));
    Functions::waveInGetNumDevs = reinterpret_cast<waveInGetNumDevs_t>(GetProcAddress(handle, "waveInGetNumDevs"));
    Functions::waveInGetDevCapsA = reinterpret_cast<waveInGetDevCapsA_t>(GetProcAddress(handle, "waveInGetDevCapsA"));
    Functions::waveInGetDevCapsW = reinterpret_cast<waveInGetDevCapsW_t>(GetProcAddress(handle, "waveInGetDevCapsW"));
    Functions::waveInGetErrorTextA =
        reinterpret_cast<waveInGetErrorTextA_t>(GetProcAddress(handle, "waveInGetErrorTextA"));
    Functions::waveInGetErrorTextW =
        reinterpret_cast<waveInGetErrorTextW_t>(GetProcAddress(handle, "waveInGetErrorTextW"));
    Functions::waveInOpen = reinterpret_cast<waveInOpen_t>(GetProcAddress(handle, "waveInOpen"));
    Functions::waveInClose = reinterpret_cast<waveInClose_t>(GetProcAddress(handle, "waveInClose"));
    Functions::waveInPrepareHeader =
        reinterpret_cast<waveInPrepareHeader_t>(GetProcAddress(handle, "waveInPrepareHeader"));
    Functions::waveInUnprepareHeader =
        reinterpret_cast<waveInUnprepareHeader_t>(GetProcAddress(handle, "waveInUnprepareHeader"));
    Functions::waveInAddBuffer = reinterpret_cast<waveInAddBuffer_t>(GetProcAddress(handle, "waveInAddBuffer"));
    Functions::waveInStart = reinterpret_cast<waveInStart_t>(GetProcAddress(handle, "waveInStart"));
    Functions::waveInStop = reinterpret_cast<waveInStop_t>(GetProcAddress(handle, "waveInStop"));
    Functions::waveInReset = reinterpret_cast<waveInReset_t>(GetProcAddress(handle, "waveInReset"));
    Functions::waveInGetPosition = reinterpret_cast<waveInGetPosition_t>(GetProcAddress(handle, "waveInGetPosition"));
    Functions::waveInGetID = reinterpret_cast<waveInGetID_t>(GetProcAddress(handle, "waveInGetID"));
    Functions::waveInMessage = reinterpret_cast<waveInMessage_t>(GetProcAddress(handle, "waveInMessage"));
    Functions::WOWAppExit = reinterpret_cast<WOWAppExit_t>(GetProcAddress(handle, "WOWAppExit"));
    Functions::mciExecute = reinterpret_cast<mciExecute_t>(GetProcAddress(handle, "mciExecute"));
    Functions::mmsystemGetVersion =
        reinterpret_cast<mmsystemGetVersion_t>(GetProcAddress(handle, "mmsystemGetVersion"));
    Functions::PlaySoundStub = reinterpret_cast<PlaySoundStub_t>(GetProcAddress(handle, "PlaySoundStub"));

    return true;
}

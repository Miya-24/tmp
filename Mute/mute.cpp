
#include <windows.h>
#include <mmdeviceapi.h>
#include <endpointvolume.h>
#include <cstdio>
#include <locale.h>

#define MUTE_ON  1
#define MUTE_OFF 0

int main(int argc,char *argv[])
{
    HRESULT hr = 0;
    IMMDeviceEnumerator *pEnum = NULL;
    IMMDevice *pEndpoint = NULL;
    IAudioEndpointVolume *pAudioEndVol = NULL;

    hr = CoInitializeEx(0, COINIT_MULTITHREADED);
    hr = CoCreateInstance(__uuidof(MMDeviceEnumerator), NULL, CLSCTX_ALL,IID_PPV_ARGS(&pEnum));
    if (FAILED(hr)) {
		CoUninitialize();
		return 1;
	}
    hr = pEnum->GetDefaultAudioEndpoint(eRender, eConsole, &pEndpoint);
	if (FAILED(hr)) {
		if (pEnum)
			pEnum->Release();
		CoUninitialize();
		return 2;
	}
    hr = pEndpoint->Activate(__uuidof(IAudioEndpointVolume),CLSCTX_ALL, NULL, (void **)&pAudioEndVol);
	if (FAILED(hr)) {
		if (pEndpoint)
			pEndpoint->Release();
		if (pEnum)
			pEnum->Release();
		CoUninitialize();
		return 3;
	}
    BOOL pbGetMute = MUTE_OFF;
	hr = pAudioEndVol->GetMute(&pbGetMute);
	if (FAILED(hr)) {
		if (pAudioEndVol)
			pAudioEndVol->Release();
		if (pEndpoint)
			pEndpoint->Release();
		if (pEnum)
			pEnum->Release();
		CoUninitialize();
		return 4;
	}

    BOOL bSetMute = MUTE_OFF;
    if (argc == 2) {
        bSetMute = (strcmp(argv[1], "on") == 0) ? MUTE_ON : MUTE_OFF;
    } else {
        bSetMute = pbGetMute ? MUTE_OFF : MUTE_ON;
    }
    hr = pAudioEndVol->SetMute(bSetMute, NULL);
    bSetMute ? printf("mute on\n") : printf("mute off\n");

    if (pAudioEndVol) {
		pAudioEndVol->Release();
    }
	if (pEndpoint){
		pEndpoint->Release();
    }
	if (pEnum){
		pEnum->Release();
    }
	CoUninitialize();
	return 0;
}
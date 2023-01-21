#pragma once

#include <Windows.h>
#include <process.h>
#include <string>

class PlayAudio
{
public:
    PlayAudio(HWND, LPCSTR);
    ~PlayAudio();
    void Play();
    void Repeat();
    void Stop();
    static UINT WINAPI SubThread(void*);

protected:



private:
    void Open();
    void Close();

    HWND hWnd;
    std::string szFileName;
    HANDLE hThread = NULL;
    UINT uThreadID = 0;

    static BOOL bLoop;
    static MCI_OPEN_PARMS open;

    const static UINT AUDIO_PLAY = WM_APP + 1;
    const static UINT AUDIO_REPEAT = WM_APP + 2;
    const static UINT AUDIO_STOP = WM_APP + 3;
};
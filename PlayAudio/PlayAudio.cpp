#include"PlayAudio.h"


MCI_OPEN_PARMS PlayAudio::open;
BOOL PlayAudio::bLoop = FALSE;

PlayAudio::PlayAudio(HWND w, LPCSTR f) : hWnd(w), szFileName(f)
{
    Open();
}

PlayAudio::~PlayAudio()
{
    Close();
}

void PlayAudio::Open()
{
    open.dwCallback = MAKELONG(hWnd, 0);
    open.lpstrDeviceType = (LPCSTR)MCI_DEVTYPE_WAVEFORM_AUDIO;
    open.lpstrElementName = szFileName.c_str();

    hThread = (HANDLE)_beginthreadex(
        NULL,
        0,
        SubThread,
        (void*)hWnd,
        0,
        &uThreadID);

    Sleep(500);
}

void PlayAudio::Close()
{
    bLoop = FALSE;
    DWORD dwRet = WaitForSingleObject(hThread, 100000);
    CloseHandle(hThread);
    hThread = NULL;
}

void PlayAudio::Play()
{
    PostThreadMessage(uThreadID, AUDIO_PLAY, 0, 0);
}

void PlayAudio::Repeat()
{
    PostThreadMessage(uThreadID, AUDIO_REPEAT, 0, 0);
}

void PlayAudio::Stop()
{
    PostThreadMessage(uThreadID, AUDIO_STOP, 0, 0);
}


UINT WINAPI PlayAudio::SubThread(void* pParam)
{
    int nErr = mciSendCommand(
        0,
        MCI_OPEN, MCI_OPEN_TYPE | MCI_OPEN_TYPE_ID | MCI_OPEN_ELEMENT,
        reinterpret_cast<DWORD_PTR>(&open)
    );

    if (nErr) {
        return 0;
    }

    bLoop = TRUE;
    const WORD wDeviceID = open.wDeviceID;
    const DWORD dwCallback = open.dwCallback;

    while (bLoop) {
        MSG msg = {};
        while (GetMessage(&msg, NULL, WM_APP, 0)) {
            switch (msg.message) {
            case 0:
            case -1:
                bLoop = FALSE;
                break;
            case AUDIO_PLAY:
            {
                MCI_PLAY_PARMS play = {};
                play.dwCallback = dwCallback;
                mciSendCommand(wDeviceID, MCI_PLAY, MCI_NOTIFY, reinterpret_cast<DWORD_PTR>(&play));
                break;
            }
            case AUDIO_REPEAT:
            {
                mciSendCommand(wDeviceID, MCI_SEEK, MCI_SEEK_TO_START, 0);

                MCI_PLAY_PARMS play = {};
                play.dwCallback = dwCallback;
                mciSendCommand(wDeviceID, MCI_PLAY, MCI_NOTIFY, reinterpret_cast<DWORD_PTR>(&play));

                break;
            }
            case AUDIO_STOP:
            {
                bLoop = FALSE;
                mciSendCommand(wDeviceID, MCI_STOP, 0, 0);
                mciSendCommand(wDeviceID, MCI_SEEK, MCI_SEEK_TO_START, 0);
                break;
            }
            default:
                break;
            }

            if (!bLoop) {
                break;
            }
        }
    }
    mciSendCommand(wDeviceID, MCI_CLOSE, 0, 0);

    return 0;
}
// ConsoleApplication1.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <Windows.h>

int main()
{
    //Get number of input devices.
    UINT uInputDevices = 0;
    UINT uRtn = GetRawInputDeviceList(NULL, &uInputDevices, sizeof(RAWINPUTDEVICELIST));
    if (uRtn != 0 || uInputDevices == 0)
    {
        return 0;
    }

    //Get input devices list.
    PRAWINPUTDEVICELIST pArrayInputDevices = new RAWINPUTDEVICELIST[uInputDevices]();
    UINT uNumOfImputDevice = uInputDevices;
    if (GetRawInputDeviceList(pArrayInputDevices , &uInputDevices, sizeof(RAWINPUTDEVICELIST)) != uNumOfImputDevice)
    {
        delete[] pArrayInputDevices;
        return 0;
    }
    
    for (UINT i = 0; i < uNumOfImputDevice; i++)
    {
        UINT nsz = 0;
        if (GetRawInputDeviceInfo(pArrayInputDevices[i].hDevice, RIDI_DEVICENAME, NULL, &nsz) != 0)
        {
            continue;
        }
        char* pName = new char[nsz]();
        if (GetRawInputDeviceInfo(pArrayInputDevices[i].hDevice, RIDI_DEVICENAME, pName, &nsz) < 0)
        {
            delete[] pName;
            continue;
        }

        char log[255] = {};
        sprintf_s(log, sizeof(log), "[%02d] hDevice=0x%08p %s", i, pArrayInputDevices[i].hDevice, pName);
        std::cout << log << std::endl;
        delete[] pName;

        UINT sz = sizeof(RID_DEVICE_INFO);
        RID_DEVICE_INFO devinfo = {sz, };
        
        //Get input device information.
        if (GetRawInputDeviceInfo(pArrayInputDevices[i].hDevice, RIDI_DEVICEINFO, &devinfo, &sz) < 0)
        {
            
            delete[] pArrayInputDevices;
            return 0;
        }
        //Input device is touchscreen.
        if ((devinfo.hid.usUsagePage == 0x000D) && (devinfo.hid.usUsage == 0x0004))
        {
            //Test
            //Can get monitor info?
            std::cout << "TouchScreen" << std::endl;
            MONITORINFO info = {sizeof(MONITORINFO), };
            if (GetMonitorInfo((HMONITOR)pArrayInputDevices[i].hDevice, &info))
            {
                if (info.dwFlags == MONITORINFOF_PRIMARY)
                {
                    std::cout << "Primary" << std::endl;
                }
                else
                {
                    std::cout << "Not primary" << std::endl;
                }
            }
            else
            {
                std::cout << "Failed" << std::endl;
            }
        }
    }

    delete[] pArrayInputDevices;
    return 0;
}

#include <windows.h>
#include <stdlib.h>
#include <stdio.h>
#include <winuser.h>
#include <iostream>

BOOL CALLBACK MyMonitorEnumProc( HMONITOR hMonitor, HDC hdcMonitor, LPRECT lprcMonitor, LPARAM dwData )
{
    MONITORINFOEX monitorInfo;
    monitorInfo.cbSize = sizeof( monitorInfo );
    GetMonitorInfo( hMonitor, &monitorInfo );

     std::cout << monitorInfo.szDevice << std::endl;
    return TRUE;
}

int main()
{
    /*
    int value = 10;
    char cmd[1024] = {};
    sprintf(cmd, "powercfg /setacvalueindex SCHEME_BALANCED SUB_VIDEO aded5e82-b909-4619-9949-f5d71dac0bcb %d", value);    
    system(cmd);
    system("powercfg /setactive SCHEME_BALANCED");
    return 0;
    */
    //EnumDisplayMonitors( NULL, NULL, MyMonitorEnumProc, 0 );
    char cmd[1024]  = {};
    sprintf(cmd, "C:/Users/TOSHIKI/WorkSpace/CSharp/test %d", 100);
    system(cmd);

    return 0;
}
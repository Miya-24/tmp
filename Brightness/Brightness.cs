using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Management;

namespace DeviceManager.Brightness
{
    class BrightnessController
    {
        ManagementClass WmiMonitorBrightnessMethods = new ManagementClass("root/wmi", "WmiMonitorBrightnessMethods", null);

        // via http://home.a00.itscom.net/hatada/csharp/lcd01.html
        // https://stackoverflow.com/questions/18083982/how-to-query-getmonitorbrightness-from-c-sharp
        // https://stackoverflow.com/questions/8194006/c-sharp-setting-screen-brightness-windows-7
        // https://msdn.microsoft.com/ja-jp/library/system.management.managementscope(v=vs.110).aspx
        public void SetBrightness(int level)
        {
            foreach (ManagementObject mo in WmiMonitorBrightnessMethods.GetInstances())
            {
                ManagementBaseObject inParams = mo.GetMethodParameters("WmiSetBrightness");
                inParams["Brightness"] = level; // 輝度を level % に
                inParams["Timeout"] = 5;       // 操作のタイムアウトを 5 秒にセット
                Console.Write(level);
                mo.InvokeMethod("WmiSetBrightness", inParams, null);
            }
        }   
    }
    class Program {
        static void Main(string[] args) {
            int i = int.Parse(args[0]);
            BrightnessController bc = new BrightnessController();
            bc.SetBrightness(i);
        }
    }
}
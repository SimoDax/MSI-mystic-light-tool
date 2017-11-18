/*
MSI-Mystic-light-tool
Copyright(C) 2017 Simone Dassi

This program is free software : you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program. If not, see <http://www.gnu.org/licenses/>.
*/

//reference for the Mystic Light lib: https://www.msi.com/files/pdf/Mystic_Light_Software_Development_Kit.pdf


#include "stdafx.h"
#include <atlsafe.h>
#include "MysticLight_SDK.h"

HINSTANCE MLinstance;
LPMLAPI_Initialize ml_init;
LPMLAPI_GetErrorMessage ml_errorMsg;
LPMLAPI_GetDeviceInfo ml_getDevInfo;
LPMLAPI_GetLedInfo ml_getLedInfo;
LPMLAPI_GetLedColor ml_getColor;		//coloUr is better tbh..
LPMLAPI_GetLedStyle	ml_getStyle;
LPMLAPI_GetLedMaxBright ml_getMaxBright;
LPMLAPI_GetLedBright ml_getBright;
LPMLAPI_GetLedMaxSpeed ml_getMaxSpeed;
LPMLAPI_GetLedSpeed ml_getSpeed;
LPMLAPI_SetLedColor ml_setColor;
LPMLAPI_SetLedStyle ml_setStyle;
LPMLAPI_SetLedBright ml_setBright;
LPMLAPI_SetLedSpeed ml_setSpeed;

int loadLib() {

	MLinstance = LoadLibrary(TEXT("MysticLight_SDK.dll"));
	if (!MLinstance)
		return 0;

	ml_init = (LPMLAPI_Initialize)GetProcAddress(MLinstance, "MLAPI_Initialize");
	ml_errorMsg = (LPMLAPI_GetErrorMessage)GetProcAddress(MLinstance, "MLAPI_GetErrorMessage");
	ml_getDevInfo = (LPMLAPI_GetDeviceInfo)GetProcAddress(MLinstance, "MLAPI_GetDeviceInfo");  

	//add all the other ML functions you need to use here..
	return 1;
}

void printStatus(int status) {
	BSTR errStr;

	ml_errorMsg(status, &errStr);
	printf("Function returned status code: %S\n", errStr);
}



int main(){

	int status;
	CComSafeArray<BSTR> devices;	//Wrapper class to use safearrays in C++ (https://msdn.microsoft.com/en-us/magazine/mt795188.aspx)
									//according to MSI docs GetDeviceInfo should return a safearray of BSTR for the devices..
	CComSafeArray<DWORD> ledCount;	//.. and a safearray of DWORD for the led count in each device

	SAFEARRAY* devArrayDescriptor = devices.m_psa;			//the actual pointer to the safearray descriptor is .m_psa
	SAFEARRAY* ledCountArrayDescriptor = ledCount.m_psa;

	if (loadLib()) {

		status = ml_init();		//initialise the sdk
		printStatus(status);	//helper function to print a verbose description of the status code

		status = ml_getDevInfo(&devArrayDescriptor, &ledCountArrayDescriptor); //I have yet to understand why it wants a double pointer as parameter..
		printStatus(status);

		//sample loop to iterate elements in a safearray
		for (LONG i = devices.GetLowerBound(); i <= devices.GetUpperBound(); i++){
			printf("Device #%d: %S, Led count: %d\n", i, devices.GetAt(i), ledCount.GetAt(i));		//item count of both safearrays is the same, safe to access ledCount too
		}

		// ... put your code to control leds here
	}
	else
		printf("MysticLight_SDK.dll not found.\n");

	system("PAUSE");
    return 0;
}


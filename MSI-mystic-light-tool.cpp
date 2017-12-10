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

struct MysticLight {		//struct grouping all the function pointers under one pseudo-object, ml, for better clarity
	LPMLAPI_Initialize init;
	LPMLAPI_GetErrorMessage errorMsg;
	LPMLAPI_GetDeviceInfo getDevInfo;
	LPMLAPI_GetLedInfo getLedInfo;
	LPMLAPI_GetLedColor getColor;		//coloUr is better tbh..
	LPMLAPI_GetLedStyle	getStyle;
	LPMLAPI_GetLedMaxBright getMaxBright;
	LPMLAPI_GetLedBright getBright;
	LPMLAPI_GetLedMaxSpeed getMaxSpeed;
	LPMLAPI_GetLedSpeed getSpeed;
	LPMLAPI_SetLedColor setColor;
	LPMLAPI_SetLedStyle setStyle;
	LPMLAPI_SetLedBright setBright;
	LPMLAPI_SetLedSpeed setSpeed;
} ml;

int loadLib() {

	MLinstance = LoadLibrary(TEXT("MysticLight_SDK.dll"));
	if (!MLinstance)
		return 0;

	//initialise the struct fields
	ml.init = (LPMLAPI_Initialize)GetProcAddress(MLinstance, "MLAPI_Initialize");
	ml.errorMsg = (LPMLAPI_GetErrorMessage)GetProcAddress(MLinstance, "MLAPI_GetErrorMessage");
	ml.getDevInfo = (LPMLAPI_GetDeviceInfo)GetProcAddress(MLinstance, "MLAPI_GetDeviceInfo");  

	//add all the other ML functions you need to use here..
	return 1;
}

void printStatus(int status) {
	BSTR errStr;

	ml.errorMsg(status, &errStr);
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

		status = ml.init();		//initialise the sdk
		printStatus(status);	//helper function to print a verbose description of the status code

		if (status == 0) {		//initialisation successful

			status = ml.getDevInfo(&devArrayDescriptor, &ledCountArrayDescriptor); //I have yet to understand why it wants a double pointer as parameter..
			printStatus(status);

			//sample loop to iterate through elements in a safearray
			for (LONG i = devices.GetLowerBound(); i <= devices.GetUpperBound(); i++) {
				printf("Device #%d: %S, Led count: %d\n", i, devices.GetAt(i), ledCount.GetAt(i));		//item count of both safearrays is the same, safe to access ledCount too
			}

			// ... put your code to control leds here
		}
	}
	else
		printf("MysticLight_SDK.dll not found.\n");

	system("PAUSE");
    return 0;
}


// Fill out your copyright notice in the Description page of Project Settings.

#include "ATLASrift.h"
#include "My3DMouse.h"

AMy3DMouse::AMy3DMouse(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
//	PrimaryActorTick.bCanEverTick = true;
//	PrimaryActorTick.bStartWithTickEnabled = true;
}

void AMy3DMouse::BeginPlay()
{
	Super::BeginPlay();
	init();
	//DispatchLoopNT();
}

int AMy3DMouse::init()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, TEXT("Hello MOUSE!"));

	hWndMain = GetActiveWindow();
	int  res = 0;            /* SbInits result..if>0 it worked, if=0 it didnt work   */

	res = SbInit();

	/* if 3D mouse was not detected then print error, close win., exit prog. */
	if (res < 1)
	{
		printf("Sorry - No supported 3Dconnexion device available.\n");
		ExitProcess(1);                /* exit program */
	}

	return(res);
}

int AMy3DMouse::SbInit()
{
	_tcscpy(devicename, _T(""));
	int res;                             /* result of SiOpen, to be returned  */
	SiOpenData oData;                    /* OS Independent data to open ball  */

	/*init the SpaceWare input library */
	if (SiInitialize() == SPW_DLL_LOAD_ERROR)
	{
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Error: Could not load SiAppDll dll files"));
		}
	}

	SiOpenWinInit(&oData, hWndMain);    /* init Win. platform specific data  */
	SiSetUiMode(devHdl, SI_UI_ALL_CONTROLS); /* Config SoftButton Win Display */

	/* open data, which will check for device type and return the device handle
	to be used by this function */
	if ((devHdl = SiOpen("3DxTest32", SI_ANY_DEVICE, SI_NO_MASK, SI_EVENT, &oData)) == NULL)
	{
#if 0
		SPWchar err[100];
		extern enum SpwRetVal SpwErrorVal;
		_stprintf(err, _T("SiOpen error: %d\n"), SpwErrorVal);
		MessageBox(NULL, err, _T("3DxTest: SiOpen Error"), MB_ICONERROR);
#endif

		SiTerminate();  /* called to shut down the SpaceWare input library */
		res = 0;        /* could not open device */

		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, "could not open device");
		return res;
	}
	else
	{
		//SiGrabDevice(devHdl, SPW_TRUE);
		SiDeviceName devName;
		SiGetDeviceName(devHdl, &devName);
		_stprintf(devicename, _T("%S"), devName.name);
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, devicename);
		res = 1;        /* opened device succesfully */
		return res;
	}
	return(0);
}

//void AMy3DMouse::Tick(float DeltaTime)
//{
//	Super::Tick(DeltaTime);
//	//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("Tick"));
//	CheckMessages();
//}

bool AMy3DMouse::CheckMessages()
{
	if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
	{

		/* init Window platform specific data for a call to SiGetEvent */
		SiGetEventWinInit(&EData, msg.message, msg.wParam, msg.lParam);

		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, "Something Happened!");

		/* check whether msg was a 3D mouse event and process it */
		if (SiGetEvent(devHdl, SI_AVERAGE_EVENTS, &EData, &Event) == SI_IS_EVENT)
		{
			if (Event.type == SI_MOTION_EVENT)
			{
				tra = FVector(Event.u.spwData.mData[SI_TX], Event.u.spwData.mData[SI_TY], Event.u.spwData.mData[SI_TZ]);
				//rot = FVector(pEvent->u.spwData.mData[SI_RX], pEvent->u.spwData.mData[SI_RY], pEvent->u.spwData.mData[SI_RZ]);
				GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, tra.ToString() + "  Rot " + rot.ToString());
				return true;
			}
			else if (Event.type == SI_BUTTON_PRESS_EVENT)
			{
				//	SbButtonPressEvent(Event.u.hwButtonEvent.buttonNumber);  /* process button press event */
				GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, "3D Mouse BUTTON PRESS Event!");
			}
			else if (Event.type == SI_BUTTON_RELEASE_EVENT)
			{
				//	SbButtonReleaseEvent(Event.u.hwButtonEvent.buttonNumber); /* process button release event */
				GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, "3D Mouse BUTTON RELEASE Event!");
			}
			else if (Event.type == SI_DEVICE_CHANGE_EVENT)
			{
				//	HandleDeviceChangeEvent(&Event); /* process 3D mouse device change event */
				GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, "3D Mouse CHANGE Event!");
			}

			return false;  
		}

		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return false;
}


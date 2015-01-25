// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"

#include "spwmacro.h"
#include "AllowWindowsPlatformTypes.h"
#include "si.h"        /* Required for any SpaceWare support within an app.*/
#include "siapp.h"     /* Required for siapp.lib symbols */
#include "HideWindowsPlatformTypes.h"

#include "virtualkeys.hpp"

#include "My3DMouse.generated.h"

UCLASS()
class ATLASRIFT_API AMy3DMouse : public AActor
{
	GENERATED_BODY()
		AMy3DMouse(const FObjectInitializer& ObjectInitializer);

	//virtual void Tick(float DeltaTime) override;

	virtual void BeginPlay() override;

public:

	SiHdl        devHdl;      /* Handle to 3D Mouse Device */
	HWND         hWndMain;    /* Handle to Main Window */
	TCHAR devicename[100];

	SiSpwEvent     Event;    /* SpaceWare Event */
	SiGetEventData EData;    /* SpaceWare Event Data */


	int init();
	int SbInit();

	UFUNCTION(BlueprintCallable, Category = "3D Mouse Functions")
	bool CheckMessages();


	void  SbButtonPressEvent(int buttonnumber);
	void  SbButtonReleaseEvent(int buttonnumber);
	void  HandleDeviceChangeEvent(SiSpwEvent *pEvent);

	UPROPERTY(BlueprintReadWrite, Category = "3DMouseCoordinates")
		FVector tra;
	UPROPERTY(BlueprintReadWrite, Category = "3DMouseCoordinates")
		FVector rot;

private:
	MSG            msg;      /* incoming message to be evaluated */
	BOOL           handled;  /* is message handled yet */



};

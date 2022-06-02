#pragma once

#include "Engine/EngineTypes.h"
#include "CoreMinimal.h"
#include "UI/Elements/ReloadProgressBarElement.h"

class UProgressBar;

class ReloadProgressBarElement 
{
private:
	UProgressBar* ReloadProgressBar;

	bool InReloadProgress = false;
	float ReloadDuration;
	float PastSeconds;

public:
	ReloadProgressBarElement(UProgressBar* ReloadProgressBar);

	void OnStartReload(float Duration);
	void Tick(float DeltaTime);

private:
	void Update(float Current, float Max);
	void SetProgressState(bool InProgress);
};
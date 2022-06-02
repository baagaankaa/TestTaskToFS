
#include "UI/Elements/ReloadProgressBarElement.h"
#include "Blueprint/UserWidget.h"
#include "Components/ProgressBar.h"
#include "Engine/World.h"

DEFINE_LOG_CATEGORY_STATIC(LogReloadProgressBar, All, All);

ReloadProgressBarElement::ReloadProgressBarElement(UProgressBar* ProgressBar) : ReloadProgressBar(ProgressBar)
{
	SetProgressState(false);
}

void ReloadProgressBarElement::OnStartReload(float Duration)
{
	ReloadDuration = Duration;
	PastSeconds = 0.0f;
	SetProgressState(true);
}

void ReloadProgressBarElement::Update(float Current, float Max)
{
	ReloadProgressBar->SetPercent(Current / Max);
}

void ReloadProgressBarElement::SetProgressState(bool InProgress)
{
	InReloadProgress = InProgress;
	ReloadProgressBar->SetVisibility(InProgress 
		? ESlateVisibility::Visible
		: ESlateVisibility::Hidden);
}

void ReloadProgressBarElement::Tick(float DeltaTime)
{
	if (InReloadProgress == false)
	{
		return;
	}

	PastSeconds += DeltaTime;

	Update(PastSeconds, ReloadDuration);

	UE_LOG(LogReloadProgressBar, Display, TEXT("PastSeconds: %f, Duration %f"), PastSeconds, ReloadDuration);
	UE_LOG(LogReloadProgressBar, Display, TEXT("Percent: %f"), ReloadProgressBar->Percent);
	UE_LOG(LogReloadProgressBar, Display, TEXT("equal is : %i"), PastSeconds >= ReloadDuration);

	if (PastSeconds < ReloadDuration)
	{
		return;
	}

	UE_LOG(LogReloadProgressBar, Display, TEXT("State: false"));
	SetProgressState(false);
}

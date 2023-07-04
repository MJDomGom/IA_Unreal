#include "IA_PlayMontageBehavior.h"
#include "GameFramework/Character.h"

bool UIA_PlayMontageBehavior::Trigger(AActor& Avatar, const UGameplayBehaviorConfig* Config, AActor* SmartObjectOwner)
{
	ACharacter* Char = Cast<ACharacter>(&Avatar);
	if (!Char) {
		return false;
	}
	CurrentAvatar = &Avatar;
	const float AnimTime = Char->PlayAnimMontage(MontageToPlay);
	Char->GetWorldTimerManager().SetTimer(AnimTimer,this,&UIA_PlayMontageBehavior::OnAnimTimer, AnimTime);
	return true;
}

void UIA_PlayMontageBehavior::OnAnimTimer()
{
	if (!CurrentAvatar) {
		return;
	}
	EndBehavior(*CurrentAvatar);
}

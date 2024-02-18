// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/WorriorAnimInstance.h"
#include "Character/Worrior.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "D:\UE_5.3\Engine\Source\Runtime\AnimGraphRuntime\Public\KismetAnimationLibrary.h"
#include "Animation/AnimInstance.h"

void UWorriorAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	WorriorRef = Cast<AWorrior>(TryGetPawnOwner());
	if (WorriorRef)
	{
		WorriorMoveComponent = WorriorRef->GetCharacterMovement();
		
	}
}

void UWorriorAnimInstance::NativeUpdateAnimation(float DeltaTime)
{
	Super::NativeUpdateAnimation(DeltaTime);

	if (WorriorMoveComponent)
	{
		Speed = UKismetMathLibrary::VSizeXY(WorriorMoveComponent->Velocity);
		Direction = UKismetAnimationLibrary::CalculateDirection(WorriorRef->GetVelocity(), WorriorRef->GetActorRotation());
		IsFalling = WorriorMoveComponent->IsFalling();
		CharacterState = WorriorRef->GetCharacterState();
	}
}

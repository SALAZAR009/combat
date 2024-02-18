// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "Character/CharacterEnum.h"
#include "WorriorAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class COMBAT_PRACTICE_API UWorriorAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
public:

	//Create Function for For Initializing animation
	virtual void NativeInitializeAnimation() override;

	//Create Function for Updating Animation
	virtual void NativeUpdateAnimation(float DeltaTime) override;



	//Variables
	UPROPERTY(BlueprintReadOnly, Category = "Movement")
	class AWorrior* WorriorRef;

	UPROPERTY(BlueprintReadOnly, Category = "Movement")
	class UCharacterMovementComponent* WorriorMoveComponent;

	UPROPERTY(BlueprintReadOnly, Category = "Movement")
	float Speed;

	UPROPERTY(BlueprintReadOnly, Category = "Movement")
	float Direction;

	UPROPERTY(BlueprintReadOnly, Category = "Movement")
	class UAnimInstance* Anim_Instance;

	UPROPERTY(BlueprintReadOnly, Category = "Movement")
	bool IsFalling;

	UPROPERTY(BlueprintReadOnly, Category = "Movement|CharacterState")
	ECharacterState CharacterState;

};

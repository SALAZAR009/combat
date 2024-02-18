// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "CharacterEnum.h"
#include "Worrior.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UInputMappingContext;
class UInputAction;
class UAnimMontage;
class USphereComponent;



UCLASS()
class COMBAT_PRACTICE_API AWorrior : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AWorrior();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	 
	
	

protected:

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);
	void Mode();
	void Attacks();

	/*
	* Function to Montages;
	*/
	void PlayAttackMontage();

	UFUNCTION(BlueprintCallable)
	void PlayEndNotify();

	bool CanAttack();

	// For Collision test
	UPROPERTY(VisibleAnywhere, Category = "Sphere Collision")
	TObjectPtr<USphereComponent>Sphere_RH;

	UPROPERTY(VisibleAnywhere, Category = "Sphere Collision")
	TObjectPtr<USphereComponent>Sphere_LH;

	UFUNCTION()
	void SphereCollisionBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent*OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

private:

	ECharacterState CharacterState = ECharacterState::ECS_NormalMode;

	UPROPERTY(BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	EAttackingState AttackingState = EAttackingState::EAS_Unoccupied;
	
	
	
	UPROPERTY(VisibleAnywhere, Category = "Camera")
	TObjectPtr<USpringArmComponent>CameraBoom;

	UPROPERTY(VisibleAnywhere, Category = "Camera")
	TObjectPtr<UCameraComponent>Camera;

	UPROPERTY(EditAnyWhere, Category = "Enhanced Input")
	TObjectPtr<UInputMappingContext>BaseMappingContext;

	UPROPERTY(EditAnyWhere, Category = "Enhanced Input")
	TObjectPtr<UInputAction>MoveAction;

	UPROPERTY(EditAnyWhere, Category = "Enhanced Input")
	TObjectPtr<UInputAction>LookAction;

	UPROPERTY(EditAnyWhere, Category = "Enhanced Input")
	TObjectPtr<UInputAction>JumpAction;

	UPROPERTY(EditAnyWhere, Category = "Enhanced Input")
	TObjectPtr<UInputAction>ModeChange;

	UPROPERTY(EditDefaultsOnly, Category = "Enhanced Input")
	TObjectPtr<UInputAction>Attack;

	/*
	* Montages
	*/

	UPROPERTY(EditDefaultsOnly, Category = "Attack Montages")
	TObjectPtr<UAnimMontage>Attack_Montage;


public:
	FORCEINLINE ECharacterState GetCharacterState() const { return CharacterState; }
};

// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Worrior.h"
#include "GameFramework/SpringArmComponent.h"//Header for SpringArm
#include "Camera/CameraComponent.h"//Header for CameraComponent
#include "InputMappingContext.h" //Header for inputmapping
#include "EnhancedInputSubsystems.h"//Header for EnhancedInput
#include "EnhancedInputComponent.h"//Header file fore Enhanced Component
#include "Animation/AnimMontage.h"
#include "Components/SphereComponent.h"


// Sets default values
AWorrior::AWorrior()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(GetRootComponent());
	CameraBoom->TargetArmLength = 200.0f;
	CameraBoom->SocketOffset = FVector(0.0f, 0.0f, 75.0f);

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(CameraBoom);
	
	Sphere_RH = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere_0"));
	Sphere_RH->SetupAttachment(GetMesh(),"hand_r");

	Sphere_LH = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere_1"));
	Sphere_LH->SetupAttachment(GetMesh(),"hand_l");
	
}

// Called when the game starts or when spawned
void AWorrior::BeginPlay()
{
	Super::BeginPlay();

	//Get Controller
	if(APlayerController * Control= Cast<APlayerController>(GetController()))
	{ //Adding Subsystem
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(Control->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(BaseMappingContext, 0);
		}

	}
	
}

void AWorrior::Move(const FInputActionValue& Value)
{
	if (AttackingState == EAttackingState::EAS_Attacking) return;
	if (Controller != NULL)
	{
		const FVector2D DirectionalValue = Value.Get<FVector2D>();
		const FRotator RotationValue = Controller->GetControlRotation();
		const FRotator Yaw_Rotation(0.0f, RotationValue.Yaw, 0.0f);
		if (DirectionalValue.Y != 0.f)
		{
			FVector Forward = FRotationMatrix(Yaw_Rotation).GetUnitAxis(EAxis::X); 
			AddMovementInput(Forward, DirectionalValue.Y);
		}
		if (DirectionalValue.X != 0.f)
		{
			FVector Right = FRotationMatrix(Yaw_Rotation).GetUnitAxis(EAxis::Y);
			AddMovementInput(Right, DirectionalValue.X);
		}
	}
}

void AWorrior::Look(const FInputActionValue& Value)
{
	const FVector2D LookValue = Value.Get<FVector2D>();
	if (GetController())
	{
				
		AddControllerYawInput(LookValue.X);
		
		AddControllerPitchInput(LookValue.Y);
		
	}
}

void AWorrior::Mode()
{
	bool ModeA = true;
	
		if (ModeA)
		{
			CharacterState = ECharacterState::ECS_FightMode;
			ModeA = false;
		}
		else
		{
			CharacterState = ECharacterState::ECS_NormalMode;
			ModeA = true;
		}
		
	
}

void AWorrior::Attacks()
{
	
	if (CanAttack() )
	{
		PlayAttackMontage();
		AttackingState = EAttackingState::EAS_Attacking;
	}
}

bool AWorrior::CanAttack()
{
	return AttackingState == EAttackingState::EAS_Unoccupied && CharacterState != ECharacterState::ECS_NormalMode;
}

void AWorrior::SphereCollisionBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{

}

void AWorrior::PlayAttackMontage()
{
	UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
	if (AnimInstance && Attack_Montage)
	{
		AnimInstance->Montage_Play(Attack_Montage, 1.5f);
		INT32 Section = FMath::RandRange(0,3);
		FName SectionName = FName();
		switch (Section)
		{
		case 0:
			SectionName = FName("Attack1");
			break;
		case 1:
			SectionName = FName("Attack2");
			break;
		case 2:
			SectionName = FName("Attack3");
			break;
		case 3:
			SectionName = FName("Attack4");
			break;
		default:
			break;
		}
		AnimInstance->Montage_JumpToSection(SectionName, Attack_Montage);
	}
}

void AWorrior::PlayEndNotify()
{
	AttackingState = EAttackingState::EAS_Unoccupied;
}




// Called every frame
void AWorrior::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AWorrior::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		//For MoveCommand
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AWorrior::Move);
		//For LookCommand
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AWorrior::Look);

		//For jump
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &ACharacter::Jump);
		
		//For Enter enter fight mode
		EnhancedInputComponent->BindAction(ModeChange, ETriggerEvent::Triggered, this, &AWorrior::Mode);

		//for Play Attack Montages
		EnhancedInputComponent->BindAction(Attack, ETriggerEvent::Triggered, this, &AWorrior::Attacks);

	}
}




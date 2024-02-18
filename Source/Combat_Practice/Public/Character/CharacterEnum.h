#pragma once
UENUM(BlueprintType)
enum class ECharacterState : uint8
{
	ECS_NormalMode UMETA(DisplayName = "Normal Mode"),
	ECS_FightMode UMETA(DisplayName = "Fight Mode")
};

UENUM(BlueprintType)
enum class EAttackingState : uint8
{
	EAS_Unoccupied UMETA(DisplayName = "Unoccupied"),
	EAS_Attacking UMETA(DisplayName = "Attacking")
};
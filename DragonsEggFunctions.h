// Copyright ScaleSculptor / Spyrm.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "GameplayTagContainer.h"
#include "AbilitySystem/LyraAbilitySystemComponent.h"
#include "GameplayAbilitySpec.h"
#include "DragonsEggFunctions.generated.h"


class ULyraGameplayAbility;


/**
 * Various blueprint nodes created for Dragon's Egg
 */
UCLASS()
class DRAGONSEGGRUNTIME_API UDragonsEggFunctions : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, BlueprintAuthorityOnly, Category = "GameplayAbilities")
		static FGameplayAbilitySpecHandle GiveAbilityWithInputTag(UAbilitySystemComponent* AbilitySystemComponent,
			TSubclassOf<ULyraGameplayAbility> Ability, int32 AbilityLevel, FGameplayTag InputTag);
	

	UFUNCTION(BlueprintCallable, BlueprintAuthorityOnly, Category = "Gameplay Abilities")
		static void ClearAllAbilitiesWithInputTag(UAbilitySystemComponent* AbilitySystemComponent, FGameplayTag InputTag);

};

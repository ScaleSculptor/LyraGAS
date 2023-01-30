// Copyright ScaleSculptor / Spyrm.


#include "DragonsEggFunctions.h"
#include "AbilitySystemLog.h"

FGameplayAbilitySpecHandle UDragonsEggFunctions::GiveAbilityWithInputTag(UAbilitySystemComponent* AbilitySystemComponent,
	TSubclassOf<ULyraGameplayAbility> AbilityClass, int32 AbilityLevel /*= 0*/, FGameplayTag InputTag)
{
	check(AbilitySystemComponent);

	if (!AbilitySystemComponent->IsOwnerActorAuthoritative())
	{
		return FGameplayAbilitySpecHandle();
	}

	// validate the class
	if (!ensure(AbilityClass))
	{
		ABILITY_LOG(Error, TEXT("BuildAbilitySpecFromClass called with an invalid Ability Class."));

		return FGameplayAbilitySpecHandle();
	}

	//create the ability spec and add the input tag to it before giving it to the player's ASC
	ULyraGameplayAbility* AbilityCDO = AbilityClass->GetDefaultObject<ULyraGameplayAbility>();

	FGameplayAbilitySpec AbilitySpec(AbilityCDO, AbilityLevel);
	AbilitySpec.DynamicAbilityTags.AddTag(InputTag);

	return AbilitySystemComponent->GiveAbility(AbilitySpec);

}

void UDragonsEggFunctions::ClearAllAbilitiesWithInputTag(UAbilitySystemComponent* AbilitySystemComponent, FGameplayTag InputTag)
{
	// find all matching abilities
	TArray<const FGameplayAbilitySpec*> SpecsToClear;
	
	// ignore invalid inputs
	if (InputTag.IsValid())
	{
		// iterate through all abilities
		for (const FGameplayAbilitySpec& Spec : AbilitySystemComponent->GetActivatableAbilities())
		{
			// add maching abilities to the list
			if (Spec.DynamicAbilityTags.HasTag(InputTag))
			{
				SpecsToClear.Add(&Spec);
			}
		}
	}

	// iterate through the bound abilities
	for (const FGameplayAbilitySpec* CurrentSpec : SpecsToClear)
	{
		// clear the ability
		AbilitySystemComponent->ClearAbility(CurrentSpec->Handle);
	}
}
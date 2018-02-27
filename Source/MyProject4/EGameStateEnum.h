
#pragma once

#include "Engine/UserDefinedEnum.h"

UENUM()
enum class EGameStateEnum : uint8
{
	GE_NotStarted	UMETA(DisplayName = "NOT STARTED"),
	GE_Started		UMETA(DisplayName = "STARTED"),
	GE_Ended		UMETA(DisplayName = "ENDED"),
	GE_Unblocked	UMETA(DisplayName = "UNBLOCKED"),
	GE_Blocked		UMETA(DisplayName = "BLOCKED")
};

#include "Character.h"
#include "Engine.h"
#include "World.h"
#include "CollisionComponent.h"

ACharacter::ACharacter()
{
}

ACharacter::~ACharacter()
{
}

bool ACharacter::PredictMove(int InX, int InY)
{
	for (auto Other : GEngine->GetWorld()->GetActors()) {
		for (auto OtherComponent : Other->Components)
		{
			if (Other == this)
			{
				continue;
			}

			UCollisionComponent* OtherCollision = dynamic_cast<UCollisionComponent*>(OtherComponent);
			if (OtherCollision)
			{
				if (OtherCollision->bIsGenerateHit && InX == Other->GetX() && InY == Other->GetY())
				{
					ReceiveHit(Other);
					return false;
				}

				//if (OtherCollision->bIsGenerateOverlap && InX == Other->GetX() && InY == Other->GetY())
				//{
				//	OnActorBeginOverlap(Other);
				//	return false;
				//}
			}
		}
	}

	return true;
}

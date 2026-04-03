#include "CollisionComponent.h"
#include "Engine.h"
#include "World.h"
#include "Actor.h"

//생성할 때 초기화 되는 메모리에 들어갈 때 초기화 (이게 나음)
//함수 안에 넣으면 이게 다 만들어 지고 나서 진행 되는 것.
UCollisionComponent::UCollisionComponent() : bIsGenerateHit(false), bIsGenerateOverlap(false)
{
}

UCollisionComponent::~UCollisionComponent()
{
}

void UCollisionComponent::BeginPlay()
{
}

void UCollisionComponent::Tick()
{
	for (auto Other : GEngine->GetWorld()->GetActors()) {
		for (auto OtherComponent : Other->Components)
		{
			if (Other == this->Owner)
			{
				continue;
			}

			UCollisionComponent* OtherCollision = dynamic_cast<UCollisionComponent*>(OtherComponent);
			if (OtherCollision)
			{
				if (OtherCollision->bIsGenerateOverlap && Owner->GetX() == Other->GetX() && Owner->GetY() == Other->GetY())
				{
					if (Owner->OnActorBeginOverlap)
					{
						Owner->OnActorBeginOverlap(Other);
					}
					if (Other->OnActorBeginOverlap)
					{
						Other->OnActorBeginOverlap(Owner);
					}
				}
				if (OtherCollision->bIsGenerateHit && Owner->GetX() == Other->GetX() && Owner->GetY() == Other->GetY())
				{
					Other->ReceiveHit(Owner);
					Owner->ReceiveHit(Other);
				}
			}
		}
	}
}

#include "PickupBase.h"
#include "../PlayerCharacter.h"
#include "Components/BoxComponent.h"

APickupBase::APickupBase()
{
	PrimaryActorTick.bCanEverTick = true;

	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Component"));
	RootComponent = BoxComponent;

	AbilityMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Ability Mesh"));
	AbilityMesh->SetupAttachment(BoxComponent);
}

void APickupBase::BeginPlay()
{
	Super::BeginPlay();
	
	if(BoxComponent)
	{
		BoxComponent->OnComponentBeginOverlap.AddDynamic(this, &APickupBase::OnSphereBeginOverlap);
	}
}

void APickupBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APickupBase::OnSphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG(LogTemp, Warning, TEXT("we collided with an actor with name %s"), *OtherActor->GetActorNameOrLabel());
	APlayerCharacter* Player = Cast<APlayerCharacter>(OtherActor);
	if(Player){
		AddPickupToPlayer(*Player);
		BoxComponent->OnComponentBeginOverlap.RemoveAll(this);
	}
}

void APickupBase::HandleDestruction() {
	Destroy();
}

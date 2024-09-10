#include "GunBase.h"
#include "DrawDebugHelpers.h"
#include "Camera/CameraComponent.h"
#include "Animation/AnimInstance.h"
#include "../HealthComponent.h"

AGunBase::AGunBase()
{
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);

	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(Root);

	ADSCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("ADSCamera"));
	ADSCameraComponent->bUsePawnControlRotation = true;

	FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, true);
	ADSCameraComponent->AttachToComponent(Mesh, AttachmentRules, TEXT("ADS"));
}

void AGunBase::BeginPlay()
{
	Super::BeginPlay();
	
}

void AGunBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// TODO: only do this if we are ADSing
    APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
    if (PlayerController)
    {
        FRotator NewRotation = PlayerController->GetControlRotation();
		GetOwner()->SetActorRotation(NewRotation);
    }

}

void AGunBase::PullTrigger() {
	// TODO: muzzle flash particles
	// TODO: gun sound

	FHitResult Hit;
	FVector ShotDirection; 

	bool bSuccess = GunTrace(Hit, ShotDirection);

	if(bSuccess){
		DrawDebugPoint(GetWorld(), Hit.Location, 5, FColor::Blue, true);
		AActor* HitActor = Hit.GetActor();
		
		if(HitActor){
			UE_LOG(LogTemp, Warning, TEXT("hit actor with name: %s"), *HitActor->GetActorNameOrLabel());

			UHealthComponent* HC = HitActor->FindComponentByClass<UHealthComponent>();
			if(HC){
				HC->TakeDamage(Damage);
			}
		}
	}
}

bool AGunBase::GunTrace(FHitResult& OutHit, FVector& OutShotDirection) {
	AController* OwnerController = Cast<APawn>(GetOwner())->GetController();

	if(OwnerController == nullptr) return false;

	FVector Location;
	FRotator Rotation;
	OwnerController->GetPlayerViewPoint(Location, Rotation);
	OutShotDirection = -Rotation.Vector();

	FVector End = Location + Rotation.Vector() * FireRange;

	DrawDebugLine(GetWorld(), Location, End, FColor::Green, true, 5.f);

	// ignore the gun and the owner of the gun
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this);
	Params.AddIgnoredActor(GetOwner());

	return GetWorld()->LineTraceSingleByChannel(OutHit, Location, End, ECollisionChannel::ECC_GameTraceChannel2, Params);
}

USkeletalMeshComponent* AGunBase::GetMesh() const {
	return Mesh;
}
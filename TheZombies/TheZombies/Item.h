// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ItemTable.h"
#include "GameFramework/Actor.h"
#include "Item.generated.h"

UCLASS()
class THEZOMBIES_API AItem : public AActor
{
	GENERATED_BODY()
		//CurrentCount(현재수량), MaxCount(최대수량), Durability(내구도), FlavorText(플레이터 텍스트)

public:	
	// Sets default values for this actor's properties
	AItem();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Data)
		int32 ItemRow;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Data)
		class UDataTable* DataTable;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Infomation)
		FText Name;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Infomation)
		FText FlavorText;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Count)
		int32 CurrentCount;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Count)
		int32 MaxCount;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Icon)
		class UTexture* Icon;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Mesh)
		class USceneComponent* Root;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Mesh)
		class USkeletalMeshComponent* Body;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Mesh)
		class UBoxComponent* Interaction;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Owner)
		class ATheZombiesCharacter* MyOwner;

	UFUNCTION()
		void BindInteractionCharacter(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
		void UnBindInteractionCharacter(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	virtual void BeginPlay() override;

public:
	FORCEINLINE class USkeletalMeshComponent* GetBody() const { return Body; }
	FORCEINLINE class UTexture* GetIcon() const { return Icon; }

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void SetInteractionCollision(bool bUseCollision);
	virtual void SetOwner(class AActor* NewOwner) override;
	virtual FItemData MakeItemData();
};

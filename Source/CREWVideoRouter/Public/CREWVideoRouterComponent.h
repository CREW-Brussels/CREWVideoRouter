#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Sockets.h"
#include "SocketSubsystem.h"
#include "CREWVideoRouterComponent.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class CREWVIDEOROUTER_API UCREWVideoRouterComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UCREWVideoRouterComponent();

protected:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

public:
	/** The IP address to connect to (e.g., "127.0.0.1") */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TCP")
	FString ServerIP = TEXT("127.0.0.1");

	/** The port number to connect to */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TCP")
	int32 ServerPort = 9990;

	/** Send a string over the TCP socket */
	UFUNCTION(BlueprintCallable, Category = "TCP")
	void Route(int input, int output);

private:
	FSocket* Socket = nullptr;

	bool ConnectToServer();
	void DisconnectFromServer();
};
#include "CREWVideoRouterComponent.h"
#include "Networking.h"
#include "Sockets.h"
#include "SocketSubsystem.h"

UCREWVideoRouterComponent::UCREWVideoRouterComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UCREWVideoRouterComponent::BeginPlay()
{
	Super::BeginPlay();
	ConnectToServer();
}

void UCREWVideoRouterComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	DisconnectFromServer();
	Super::EndPlay(EndPlayReason);
}

bool UCREWVideoRouterComponent::ConnectToServer()
{
	if (Socket)
	{
		return true; // Already connected
	}

	ISocketSubsystem* SocketSubsystem = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM);
	if (!SocketSubsystem)
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to get SocketSubsystem"));
		return false;
	}

	Socket = SocketSubsystem->CreateSocket(NAME_Stream, TEXT("TCPSocket"), false);
	if (!Socket)
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to create socket"));
		return false;
	}

	FIPv4Address IP;
	FIPv4Address::Parse(ServerIP, IP);
	TSharedRef<FInternetAddr> Addr = SocketSubsystem->CreateInternetAddr();
	Addr->SetIp(IP.Value);
	Addr->SetPort(ServerPort);

	bool bConnected = Socket->Connect(*Addr);
	if (!bConnected)
	{
		UE_LOG(LogTemp, Error, TEXT("Could not connect to TCP server at %s:%d"), *ServerIP, ServerPort);
		SocketSubsystem->DestroySocket(Socket);
		Socket = nullptr;
		return false;
	}

	// Set to non-blocking
	Socket->SetNonBlocking(true);
	Socket->SetNoDelay(true);

	UE_LOG(LogTemp, Log, TEXT("TCP Connected to %s:%d"), *ServerIP, ServerPort);
	return true;
}

void UCREWVideoRouterComponent::DisconnectFromServer()
{
	if (Socket)
	{
		Socket->Close();
		ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->DestroySocket(Socket);
		Socket = nullptr;

		UE_LOG(LogTemp, Log, TEXT("TCP Socket closed"));
	}
}

void UCREWVideoRouterComponent::Route(int input, int output)
{
	if (!Socket || !Socket->GetConnectionState() == SCS_Connected)
	{
		UE_LOG(LogTemp, Warning, TEXT("Not connected. Attempting to reconnect..."));
		if (!ConnectToServer())
		{
			UE_LOG(LogTemp, Error, TEXT("Reconnect failed. Cannot send message."));
			return;
		}
	}
	if (input > 0 && output > 0) {
		FString Message = FString::Format(TEXT("VIDEO OUTPUT ROUTING:\n{0} {1}\n\n"), { output - 1, input - 1 });
		FTCHARToUTF8 Convert(*Message);
		int32 BytesSent = 0;
		bool bSuccess = Socket->Send((uint8*)Convert.Get(), Convert.Length(), BytesSent);

		if (!bSuccess)
		{
			UE_LOG(LogTemp, Error, TEXT("Failed to send TCP message"));
		}
	}
	else {
		UE_LOG(LogTemp, Error, TEXT("Invalid Video Routing range"));
	}
}

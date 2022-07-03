# MP_PuzzlePlatform
First multiplayer game made in Unreal

## Commands to run the server:
url of UnrealEditor.exe  + url uproject + flags

#### Cliente
```
"C:\Program Files\Epic Games\UE_5.0\Engine\Binaries\Win64\UnrealEditor.exe" "C:\Users\frans\Documents\Unreal Projects\MP_PuzzlePlatform\MP_PuzzlePlatform.uproject" 192.168.1.50 -game -log
```

#### Servidor
```
"C:\Program Files\Epic Games\UE_5.0\Engine\Binaries\Win64\UnrealEditor.exe" "C:\Users\frans\Documents\Unreal Projects\MP_PuzzlePlatform\MP_PuzzlePlatform.uproject" /Game/Maps/Lobby -game -log
```

<br>

### flags: 
* -game: start the game
* -log: print the logs of the server to the cmd

## Unreal Networking

### Check is the server
```C++
// Check is the server
if (HasAuthority()){
  // Server only stuff
}

// Check is the client
if (!HasAuthority()){
  // Client only stuff
}
```

### Replication ( _In the BeginPlay() method_ )
```C++
// Replicate Actor
if (HasAuthority()){
  SetReplicates(true); // Set Actor to replicate
  SetReplicateMovement(true); // Set the Actor movement to replicate
}

```

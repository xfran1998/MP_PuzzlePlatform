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
"C:\Program Files\Epic Games\UE_5.0\Engine\Binaries\Win64\UnrealEditor.exe" "C:\Users\frans\Documents\Unreal Projects\MP_PuzzlePlatform\MP_PuzzlePlatform.uproject" 192.168.1.50 -server -log
```

<br>

### flags: 
* -game: start the game
* -log: print the logs of the server to the cmd


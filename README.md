# Mario Party N64 Combo Mod

> Combine Mario Party 3, 2, (and optionally 1) into a single ROM for console or emulator.<br/>
> Most flashcarts for console have a 64MB ROM limit so the patcher outputs 2 files: mp3-mp2 combined and mp3-mp2-mp1 combined

## Table of Contents

- [Playing](#playing)
- [FAQ](#faq)
- [Building from Source](#building-from-source)

## Playing

1. **Download and extract**  
   - Download `patcher.zip` from the [Releases](https://github.com/Rainchus/Mp3-Combination/releases) tab.  
   - Extract the contents into a folder.
2. **Prepare your ROMs**  
   - Obtain US ROMs for **Mario Party 3**, **Mario Party 2**, and **Mario Party 1**.  
   - Place them in the `roms/` directory.
3. **Patch on Windows**  
   ```bash
   ./patcher.exe
   ```  
   - Outputs:
     - `mp3-mp2-combo.z64`  
     - `mp3-mp2-mp1-combo.z64` (if MP1 included)
4. **Patch on macOS**  
   ```bash
   python patcher_macOS.py
   ```  
   - Outputs unmodded base ROMs:
     - `mp3-mp2-base.z64`  
     - `mp3-mp2-mp1-base.z64`
   - Apply BPS patches using [Hack64 Patcher](https://hack64.net/tools/patcher.php):  
     | Patch File                | Target ROM                    |
     | ------------------------- | ----------------------------- |
     | `mp3-mp2-combo.bps`       | `mp3-mp2-base.z64`            |
     | `mp3-mp2-mp1-combo.bps`   | `mp3-mp2-mp1-base.z64`        |
5. **Emulator Settings**  
   - **Expansion Pak**: Enabled (8MB RAM)  
   - **Project64**:  
     - Save Type: `16kbit EEPROM`  
     - (Options > Configuration > Config: MarioPartyN64Combo)
6. **Troubleshooting**  
   See [FAQ](#faq) for common issues.

## FAQ

<details>
<summary><strong>When I start the game, it says I need to set the save type to 16KBit?</strong></summary>
  
This means your emulator did not set the save type correctly.  
**Project64**:  
1. Run the game.  
2. Go to **Options > Configuration > Config: MarioPartyN64Combo**.  
3. Set **Default save type** to `16-kbit EEPROM`.  
</details>

<details>
<summary><strong>The game crashes when loading minigames from other Mario Parties</strong></summary>
  
Some emulators lack perfect N64 accuracy.  
**Project64**:  
1. Use Project64 4.0 (development build).  
2. Go to **Options > Configuration > Config: MarioPartyN64Combo > Recompiler**.  
3. Set **CPU core style** to **Interpreter**.  

If issues persist, try the [Ares Emulator](https://ares-emulator.github.io/).  
</details>

<details>
<summary><strong>The game froze when the minigame wheel should have appeared</strong></summary>
  
You may not have selected enough minigames for that category.  
- Restart the ROM.  
- Press `Z` to open **Minigame Settings**.  
- Add more minigames to the desired category.  
</details>

<details>
<summary><strong>Will Daisy and Waluigi ever be playable?</strong></summary>
  
Probably not until decompilations progress further.  
</details>

## Building from Source

> **Note:** Only follow if you want to build the mod from source.

1. **Install armips**  
   Follow instructions: https://hack64.net/Thread-Importing-C-Code-Into-SM64-Using-n64chain-and-armips
2. **Clone this repository**  
   ```bash
   git clone https://github.com/Rainchus/Mp3-Combination.git
   cd Mp3-Combination
   ```
3. **Add ROMs**  
   - `rom/mp1.z64` (Big-endian MP1)  
   - `rom/mp2.z64` (Big-endian MP2)  
   - `rom/mp3.z64` (Big-endian MP3)
4. **Pack custom assets**  
   ```bash
   python ./initial_pack_mainfs.py
   ```  
   - Run whenever new images are added.
5. **Configure build**  
   ```bash
   python ./configure.py [-mp1]
   ```
6. **Build**  
   ```bash
   ninja
   ```  
   - Outputs:  
     - `rom/mp3-mp2.mod.z64`  
     - `rom/mp3-mp2-mp1.mod.z64`


# Yakuza 0 Legend Style Fix

Allows you to change to legend style and normal style back and forth without going to pause menu for both Majima and Kiryu.

<h3>
  <p align="center">
    <a href="https://youtu.be/Hz94Aow_Z8s">
      <b>SHOWCASE</b>
    </a>
  </p>
</h3>

# Changelog

`1.0`:

- Code cleanup
- Fixed an issue where if your controller gets disconnected the mod won't respond to your R3/RS keypress after reconnecting
- Apache 2.0 -> MIT

# Usage

When in fight press R3/RS on controller or TAB on keyboard to change to legend style,
press your regular key to change from legend style.

## Example

- Regular Style -> Legend Style (R3/RS or TAB)
- Legend -> Brawler (DPAD UP / 1)
- Legend -> Rush (DPAD LEFT / 2)
- Legend -> Beast (DPAD RIGHT / 3)

# Installation

1. Download the "dxgi.dll" file from the [latest release](https://github.com/ibldzn/yakuza-0-legend-style-fix/releases/latest).
2. Navigate to your game directory (where Yakuza0.exe is located).
3. Copy and paste the file you just downloaded to game directory.
4. Your game directory now should look something like this
   ![Screenshot](https://i.imgur.com/Yi3XAIP.png)
5. Done!

## I'm having issue with your mod, what should I do?

Download `Y0LSF.asi` file in the [release tab](https://github.com/ibldzn/yakuza-0-legend-style-fix/releases/latest),
get an ASI Loader ([like this one](https://github.com/ThirteenAG/Ultimate-ASI-Loader/releases) for example),
place both the ASI Loader and `Y0LSF.asi` in the game root directory.

If you already have an ASI Loader (usually named as `dinput8.dll`), you just have to move `Y0LSF.asi` to your game directory.

<h3><p align="center">If it still doesn't work, please <a href="https://github.com/ibldzn/yakuza-0-legend-style-fix/issues/new">create an issue</a>.</p></h3>

# Known Issue

- ~~Change style animation sometimes [won't play correctly](https://youtu.be/Hz94Aow_Z8s?t=20) when changing to or from legend style.~~ As of 1.0, I haven't encountered any after 2 hours of gameplay. (The issue might still be there, but who knows..)
- If you find any more issue please make sure to [create an issue](https://github.com/ibldzn/yakuza-0-legend-style-fix/issues/new)
  or contact me on discord `ibldzn#1649`.

# Build

Make sure you have [CMake](https://cmake.org/) installed and a shell which supports bash command, run `./build.sh Release` or
`./build.sh Release -DASI_VER=OFF` to build the non-asi version. The binary should be inside the `_out/` directory after you run the build command.

# Credit

- [TsudaKageyu](https://github.com/TsudaKageyu) for [minhook](https://github.com/TsudaKageyu/minhook) library used in this project.

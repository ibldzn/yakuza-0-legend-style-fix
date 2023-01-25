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

`1.1`:

- Added support for custom keybinding

`1.0`:

- Code cleanup
- Fixed an issue where if your controller gets disconnected the mod won't respond to your R3/RS keypress after reconnecting
- Apache 2.0 -> MIT

# Usage

When in fight press R3/RS on controller or your custom keybinding on keyboard to change to legend style,
press your regular key to change from legend style.

## Example

- Regular Style -> Legend Style (R3/RS or your custom keybinding, default to TAB)
- Legend -> Brawler (DPAD UP / 1)
- Legend -> Rush (DPAD LEFT / 2)
- Legend -> Beast (DPAD RIGHT / 3)

## Changing the keybinding

- Create a file called `Y0LSF_keybind.txt` in the same directory as the mod
- Write any of these [Virtual Key Codes](https://learn.microsoft.com/en-us/windows/win32/inputdev/virtual-key-codes) inside the file you just created

### Example

If you want to use 0-9 OR A-Z as the trigger key, you can write just the letter inside the file, e.g.

```
4
```

will use 4 as the trigger key

Otherwise, you can write `VK_*` inside the file, e.g.

```
VK_SHIFT
```

will use the SHIFT key as the trigger key

Also, you CANNOT use any of the key that says `Undefined`, `Reserved`, `OEM specific`, or `Unassigned` inside the link above.

# Installation

## DLL Version

1. Download the "dxgi.dll" file from the [latest release](https://github.com/ibldzn/yakuza-0-legend-style-fix/releases/latest).
2. Navigate to your game directory (where Yakuza0.exe is located).
3. Copy and paste the file you just downloaded to game directory.
4. Your game directory now should look something like this
   ![Screenshot](https://i.imgur.com/Yi3XAIP.png)
5. Done!

## ASI Version

1. Follow the same step as above, except you should download the "Y0LSF.asi" file
2. Get an ASI loader then put it inside the same directory as the game
3. Done!

If you already have an ASI Loader (usually named as `dinput8.dll`), you just have to move `Y0LSF.asi` to your game directory.

<h3><p align="center">If it still doesn't work, please <a href="https://github.com/ibldzn/yakuza-0-legend-style-fix/issues/new">create an issue</a>.</p></h3>

# Known Issue

- Change style animation sometimes [won't play correctly](https://youtu.be/Hz94Aow_Z8s?t=20) when changing to or from legend style.
- If you find any more issue please make sure to [create an issue](https://github.com/ibldzn/yakuza-0-legend-style-fix/issues/new)
  or contact me on discord `ibldzn#7036`.

# Build

Make sure you run this with bash shell and have [CMake](https://cmake.org/) installed, then run `./build.sh --rel` or
`./build.sh --rel -DASI_VER=OFF` to build the non-asi version. The binary should be inside the `_out/` directory after you run the build command.

# Credit

- [TsudaKageyu](https://github.com/TsudaKageyu) for [minhook](https://github.com/TsudaKageyu/minhook) library used in this project.

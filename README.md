# Yakuza 0 Legend Style Fix

Allows you to change to legend style and normal style back and forth without going to pause menu for both Majima and Kiryu.

<h3>
  <p align="center">
    <a href="https://youtu.be/Hz94Aow_Z8s">
      <b>SHOWCASE</b>
    </a>
  </p>
</h3>

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
2. Navigate to your Y0 directory (where Yakuza0.exe is located).
3. Copy and paste the file you just downloaded to Y0 directory.
4. Your Y0 directory now should look something like this
   ![Screenshot](https://i.imgur.com/Yi3XAIP.png)
5. Done!

## I'm having issue with your mod, what should I do?

<h3>
  <p align="center">
    <b>[RECOMMENDED WAY]</b>
  </p>
</h3>

Download "Y0LSF.asi" file in the [release tab](https://github.com/ibldzn/yakuza-0-legend-style-fix/releases/latest),
get an ASI Loader ([like this one](https://github.com/ThirteenAG/Ultimate-ASI-Loader/releases) for example),
place the ASI Loader in the game root directory, where to put the "Y0LSF.asi" file depends on what ASI Loader you're using,
if you use the one I linked, you can read the [usage](https://github.com/ThirteenAG/Ultimate-ASI-Loader#usage) segment in their README.

<h3>
  <p align="center">
    <b>[WORKS BUT NOT ADVISED WAY]</b>
  </p>
</h3>

Get any DLL injector, then inject the "Y0LSF.asi" file into the game. Keep in mind that you'll have to do this everytime you start the game.

<h3><p align="center">If neither of those works, please <a href="https://github.com/ibldzn/yakuza-0-legend-style-fix/issues/new">create an issue</a>.</p></h3>

# Improvement

Pull requests are more than welcome!

# Known Issue

- Change style animation sometimes [won't play correctly](https://youtu.be/Hz94Aow_Z8s?t=20) when changing to or from legend style.
- If you find any more issues please make sure to [create an issue](https://github.com/ibldzn/yakuza-0-legend-style-fix/issues/new).

# Credit

- [TsudaKageyu](https://github.com/TsudaKageyu) for [minhook](https://github.com/TsudaKageyu/minhook) library used in this project.

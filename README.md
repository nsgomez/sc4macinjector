# SC4MacInjector :electric_plug:
A plugin for enabling Macs to run plugins for SimCity 4.

## Requirements
A digital release of SimCity 4 Deluxe/Rush Hour for Intel Macs (e.g. GOG, Steam, Origin).
The Mac App Store release **will not work** as it is not Aspyr's port but a Wineskin wrapper.
The PowerPC port is also incompatible, and since it is an unsupported platform it will not be
implemented in the future.

## Installation
Either obtain a prebuilt .dylib file from the Releases tab or compile yourself, then copy to
`~/Documents/SimCity 4/Plugins/`.

## Usage
Packaging is currently a work in progress. To use this plugin,

1. Open a terminal.
2. Run the following commands:

```
cd "~/Library/Application Support/Steam/steamapps/common/SimCity 4 Deluxe/SimCity 4 Deluxe Edition.app/Contents/MacOS"
DYLD_INSERT_LIBRARIES=~/Documents/SimCity 4/Plugins/libinjector.dylib "./Sim City 4 Deluxe Editionsub"
```

On platforms other than Steam the path to `cd` into may differ, as may the name of the executable.
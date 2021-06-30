# OpenHaystack - (ultra low power) alternative firmware

This is an alternative OpenHaystack firmware based on https://github.com/seemoo-lab/openhaystack/tree/main/Firmware/Microbit_v1/offline-finding but using the Softdevice from Nordic Semi. This way it will use a lot less power than the original one. It seems that a CR2032 may last almost 3 years! https://github.com/seemoo-lab/openhaystack/issues/57#issuecomment-841642356

## Setting up

### Get submodules
```
git submodule init
git submodule update
```

### Install required dependencies
 - nRF command line tools
 `brew tap homebrew/cask-drivers; brew install --cask nordic-nrf-command-line-tools`

 - binutils
 `brew install binutils`

 - gcc-arm-none-eabi
 `brew install --cask gcc-arm-embedded`

### Compile the firmware
Follow instructions on the `apps` folder

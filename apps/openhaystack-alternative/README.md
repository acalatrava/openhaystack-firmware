# OpenHaystack alternative firmware

This is an alternative firmware to [the OpenHaystack Microbit firmware](https://github.com/seemoo-lab/openhaystack/tree/main/Firmware/Microbit_v1/offline-finding), but using the Softdevice from Nordic Semiconductors, which has greatly better power efficiency.

It is using SDK 11 which uses the Softdevice S130/S132 v2.0.0 that is compatible with both nRF51 and nRF52 platforms. It has been tested with the following modules:

- E104-BT5032A board from EBYTE which can be purchased [here](https://www.aliexpress.com/item/4000538644215.html).
- "AliExpress beacon" which can be purchased [here](https://www.aliexpress.com/item/32826502025.html).

By default it will compile for nRF52 platform. If you want to make a firmware for nRF51822 you can add the `NRF_MODEL` environment variable like this

```shell
NRF_MODEL=nrf51 make
```

Please keep in mind that, by default, the resulting binaries on `_build` will not include the Softdevice. You can generate a full binary by issuing

```shell
make build
```

or

```shell
NRF_MODEL=nrf51 BOARD=BOARD_ALIEXPRESS make build
```

This command will create a full binary to be flashed on the `compiled` directory with the given parameters.

A compiled binary for both platforms is already included for convenience.

This compiled binary then has to be patched with your advertisement key from OpenHaystack app:

```shell
NRF_MODEL=nrf51 ADV_KEY_BASE64=YOUR_ADVERTISEMENT_KEY make patch
```

This command will create the new patched binary (`nrf51_firmware_patched.bin`) with provided key in the `compiled` directory.

Note that you can't patch the board type (`BOARD`), you have to compile the firmware for yourself if you want to change the board type.

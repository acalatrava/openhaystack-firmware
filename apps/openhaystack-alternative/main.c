#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include "ble_stack.h"
#include "openhaystack.h"

/** 
 * advertising interval in milliseconds 
 */
#define ADVERTISING_INTERVAL 5000

static char public_key[28] = "OFFLINEFINDINGPUBLICKEYHERE!";

/**
 * main function
 */
int main(void) {
    // Variable to hold the data to advertise
    uint8_t *ble_address;
    uint8_t *raw_data;
    uint8_t data_len;

    // Set key to be advertised
    data_len = setAdvertisementKey(public_key, &ble_address, &raw_data);

    // Init BLE stack
    init_ble();

    // Set bluetooth address
    setMacAddress(ble_address);

    // Set advertisement data
    setAdvertisementData(raw_data, data_len);

    // Start advertising
    startAdvertisement(ADVERTISING_INTERVAL);

    // Go to low power mode
    while (1) {
        power_manage();
    }
}

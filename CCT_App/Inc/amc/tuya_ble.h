#ifndef TYPE_BLE_H
#define TYPE_BLE_H

#include "stm32f1xx_hal.h"

#define FRAME_DATA_SIZE 32

typedef enum {
	BEAT_HEART,
	GET_PRODUCT_INFO,
	INFO_DEVICE_LINK_STATE,
	RESET_BLE_FROM_MCU,
	MCU_MESH_STATE_UP,
	MESH_TRANSPARENT_DOWN,
	MCU_NOTIFY_UP,
	MCU_ALL_UP,
	FUNCTION_TEST,
	MESH_TRANSPARENT_UP,
} CMD_Type;

typedef enum {
	BLE_PKG_EMPTY,
	BLE_PKG_HEAD_FILLED,
	BLE_PKG_DATA_FILLED,
	BLE_PKG_ALL_FILLED
} BLE_box_flag;

typedef struct {
	uint16_t head;
	uint8_t ext;
	CMD_Type type;
	uint16_t length;
	uint8_t data[FRAME_DATA_SIZE];
	uint8_t checkSum;
} BLE_Package;

typedef struct {
	BLE_Package pac;
	BLE_box_flag flag;
	uint8_t received_size;
	uint8_t request_size;
}BLE_Data_Struct;

typedef struct {
	uint8_t send_flag;
	CMD_Type type;
}ble_send_state;

void ble_package_receive_cpl_cb(void);
void ble_package_error_process(void);
void ble_process(void);

#endif
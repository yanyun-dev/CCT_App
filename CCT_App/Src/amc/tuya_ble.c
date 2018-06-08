#include "tuya_ble.h"

#include "usart.h"
#include "assert.h"


#define DATA_ENDIAN 1 //大端
#define FRAME_HEAD (0x55aa)
#define FRAME_HEAD_SIZE 2
#define FRAME_EXT_SIZE 1
#define FRAME_TYPE_SIZE 1
#define FRAME_LENGTH_SIZE 2
#define FRAME_CHECKSUM_SIZE 1

#define BLE_RECEIVE_PACKAGE_SIZE 3
#define BLE_SEND_PACKAGE_SIZE 3

#define RCV_BUF_SIZE 32
#define SEND_BUF_SIZE 32

ble_send_state gBleUploadStruct;

static BLE_Data_Struct ble_receive_package;
static BLE_Data_Struct ble_send_package;
static uint8_t rcv_buffer[RCV_BUF_SIZE];
static uint8_t send_buffer[SEND_BUF_SIZE];
static uint8_t ble_receive_error_count;

static void ble_package_receive(uint8_t *rcv_buffer , uint8_t rcv_size);
static void ble_receive_package_clear(void);
static void ble_send_package_clear(void);
static void ble_start_package_receive(void);
static void ble_start_package_send(void);


#define BLE_RECEIVE_START(size) ble_package_receive(rcv_buffer, size);

#define BLE_Checksum(package, checksum) do { \
	uint16_t _i; \
	checksum = 0; \
	checksum += package.head & 0x00FF; \
	checksum += package.head >> 8; \
	checksum += package.ext; \
	checksum += package.type; \
	checksum += package.length & 0x00FF; \
	checksum += package.length >> 8; \
	for (_i = 0; _i < package.length; ++_i) \
	{ \
		checksum += package.data[_i]; \
	} \
}while(0)

#define ble_package_receive(rcv_buffer ,rcv_size) HAL_UART_Receive_IT(MAIN_COMM_SERIAL, rcv_buffer, rcv_size)
#define ble_package_send(send_buffer ,rcv_size) HAL_UART_Transmit_IT(MAIN_COMM_SERIAL, send_buffer, rcv_size)


void ble_package_receive_cpl_cb(void)
{
	uint8_t i;
	uint8_t checksum = 0;
	if(ble_receive_package.flag == BLE_PKG_EMPTY)
	{
		if(ble_receive_package.received_size == 0)
		{
			if(rcv_buffer[0] != (FRAME_HEAD >> 8) || rcv_buffer[1] != (FRAME_HEAD & 0x00FF))
			{
			return;
			}
		#if DATA_ENDIAN
			ble_receive_package.pac.head = ((((uint16_t)rcv_buffer[0])<<8) + rcv_buffer[1]);
			ble_receive_package.pac.ext = rcv_buffer[FRAME_HEAD_SIZE];
			ble_receive_package.pac.type = rcv_buffer[FRAME_HEAD_SIZE+FRAME_EXT_SIZE];
			ble_receive_package.pac.length = ((((uint16_t)rcv_buffer[FRAME_HEAD_SIZE+FRAME_EXT_SIZE + FRAME_TYPE_SIZE])<<8) + rcv_buffer[FRAME_HEAD_SIZE+FRAME_EXT_SIZE + FRAME_TYPE_SIZE + 1]);
		#else
			ble_receive_package.pac.head = ((((uint16_t)rcv_buffer[1])<<8) + rcv_buffer[0]);
			ble_receive_package.pac.ext = rcv_buffer[FRAME_HEAD_SIZE];
			ble_receive_package.pac.type = rcv_buffer[FRAME_HEAD_SIZE+FRAME_EXT_SIZE];
			ble_receive_package.pac.length = ((((uint16_t)rcv_buffer[FRAME_HEAD_SIZE+FRAME_EXT_SIZE + FRAME_TYPE_SIZE + 1])<<8) + rcv_buffer[FRAME_HEAD_SIZE+FRAME_EXT_SIZE + FRAME_TYPE_SIZE]);
		#endif
			ble_receive_package.received_size += ble_receive_package.request_size;
			ble_receive_package.request_size = ble_receive_package.pac.length + FRAME_CHECKSUM_SIZE;
			ble_receive_package.flag = BLE_PKG_HEAD_FILLED;
			BLE_RECEIVE_START(ble_receive_package.request_size);
		}
		else if(ble_receive_package.flag == BLE_PKG_HEAD_FILLED)
		{
			for(i = 0; i < ble_receive_package.pac.length; ++i)
			{
				ble_receive_package.pac.data[i] = rcv_buffer[i];
			}
			ble_receive_package.pac.checkSum = rcv_buffer[i];
			BLE_Checksum(ble_receive_package.pac, checksum);
			if(checksum == ble_receive_package.pac.checkSum)
			{
				ble_receive_package.flag = BLE_PKG_ALL_FILLED;
				ble_receive_error_count = 0;
			}
			else
			{
				iprintf("File: %s, Line: %d - ble receive error!!!", __FILE__, __LINE__);
				ble_receive_package.flag = BLE_PKG_EMPTY;
			}
		}
	}
}


void ble_process(void)
{
	uint8_t checksum;
	DebugComm_SendData(ble_receive_package.pac.data, ble_receive_package.pac.length);
	if(ble_receive_package.flag == BLE_PKG_ALL_FILLED)
	{
		switch(ble_receive_package.pac.type)
		{
		case BEAT_HEART:
			if(ble_send_package.flag == BLE_PKG_EMPTY)
			{
				static uint8_t beat_heart_response;
				ble_send_package.pac.head = FRAME_HEAD;
				ble_send_package.pac.ext = 0x01;
				ble_send_package.pac.type = BEAT_HEART;
				ble_send_package.pac.length = 1;
				ble_send_package.pac.data[ble_send_package.pac.length-1] = (beat_heart_response ? beat_heart_response++ : 1);
				BLE_Checksum(ble_send_package.pac, checksum);
				ble_send_package.pac.checkSum = checksum;
				ble_send_package.flag = BLE_PKG_ALL_FILLED;
			}
			break;
		case GET_PRODUCT_INFO:
			if(ble_send_package.flag == BLE_PKG_EMPTY)
			{
				
			}
			break;
		case INFO_DEVICE_LINK_STATE:
			break;
//		case NOTIFY_UP:
//			break;
//		case FUNCTION_TEST:
//			break;
//		case TRANSPARENT_UP:
//			break;
//		case TRANSPARENT_DOWN:
//			break;
		default:
			break;
		}
		ble_receive_package_clear();
	}
	else if(ble_receive_package.flag == BLE_PKG_EMPTY)
	{
		ble_start_package_receive();
	}
	if(ble_send_package.flag == BLE_PKG_EMPTY)
	{
		// 检测是否有数据要发送
		if(gBleUploadStruct.send_flag)
		{
			switch(gBleUploadStruct.type)
			{
				case RESET_BLE_FROM_MCU:
					break;
				case MCU_MESH_STATE_UP:
					break;
				case	MESH_TRANSPARENT_DOWN: 
					break;
				case	MCU_NOTIFY_UP: 
					break;
				case	MCU_ALL_UP: 
					break;
				case	FUNCTION_TEST: 
					break;
				case	MESH_TRANSPARENT_UP: 
					break;
				default:
					break;
			}
			gBleUploadStruct.send_flag = 0;
		}
	}
	else if(ble_send_package.flag == BLE_PKG_ALL_FILLED)
	{
		assert((sizeof(ble_send_package.pac) + ble_send_package.pac.length - 1) <= 32);
		ble_package_send((uint8_t *)&ble_send_package.pac, sizeof(ble_send_package.pac) + ble_send_package.pac.length - 1);
		ble_send_package_clear();
	}
}

static void ble_receive_package_clear(void)
{
	ble_receive_package.flag = BLE_PKG_EMPTY;
	ble_receive_package.received_size = 0;
	ble_receive_package.request_size = 0;
}

static void ble_send_package_clear(void)
{
	ble_send_package.flag = BLE_PKG_EMPTY;
}

void ble_package_error_process(void)
{
	if(ble_receive_error_count++)
	{
		//通信错误上报
	}
	ble_receive_package_clear();
}


static void ble_start_package_receive()
{
	uint8_t i;
	if(ble_receive_package.flag == BLE_PKG_EMPTY)
	{
		ble_receive_package.received_size = 0;
		ble_receive_package.request_size = FRAME_HEAD_SIZE + FRAME_EXT_SIZE + FRAME_TYPE_SIZE + FRAME_LENGTH_SIZE;
		BLE_RECEIVE_START(ble_receive_package.request_size);
	}
}
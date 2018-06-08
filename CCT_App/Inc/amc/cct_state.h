#ifndef CCT_STATE_H
#define CCT_STATE_H

#include "stm32f1xx_hal.h"

typedef enum {
	CCT_STATE_UPPER_LIMIT,
	CCT_STATE_LOWER_LIMIT,
	CCT_STATE_SETTING,
	CCT_STATE_DIMING_SETTING
}CCT_STATE_TYPE;

typedef enum {
	U_1800K,
	U_2000K,
	U_2200K,
	U_2450K,
	U_2700K,
	U_3000K,
	U_3500K,
	U_4000K
}CCT_UpperLimit;

typedef enum {
	L_1800K,
	L_2000K,
	L_2200K,
	L_2450K,
	L_2700K,
	L_3000K,
	L_3500K,
	L_4000K
}CCT_LowerLimit;

typedef enum {
	DIP,
	MOBILE
} CCT_SETTING;

typedef enum {
	ELV_TRAIC_BRIGHTNESS,
	_0_to_10_BRIGHTNESS,
	_0_to_10_CCTTUNABLE,
	MOBILE_APPS
}CCT_DIMING_SETTING;

uint8_t CCT_StateGet(CCT_STATE_TYPE type);
void CCT_StateSet(CCT_STATE_TYPE type, uint8_t level);

#endif
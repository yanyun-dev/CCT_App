#include "cct_state.h"
#include "gpio.h"

#define CCT_STATE_UPPER_LIMIT_POS_MASK (6)
#define CCT_STATE_LOWER_LIMIT_POS_MASK (3)
#define CCT_STATE_SETTING_POS_MASK	(2)
#define CCT_STATE_DIMING_SETTING_POS_MASK  (0)

#define CCT_STATE_UPPER_LIMIT_MASK (7 << CCT_STATE_UPPER_LIMIT_POS_MASK)
#define CCT_STATE_LOWER_LIMIT_MASK (7 << CCT_STATE_LOWER_LIMIT_POS_MASK)
#define CCT_STATE_SETTING_MASK	(1 << CCT_STATE_SETTING_POS_MASK)
#define CCT_STATE_DIMING_SETTING_MASK  (3 << CCT_STATE_DIMING_SETTING_POS_MASK)


static uint32_t cct_state;

uint8_t CCT_StateGet(CCT_STATE_TYPE type)
{
	switch(type) {
		case CCT_STATE_UPPER_LIMIT:
			return (cct_state | CCT_STATE_UPPER_LIMIT_MASK) >> CCT_STATE_UPPER_LIMIT_POS_MASK;
			break;
		case CCT_STATE_LOWER_LIMIT:
			return (cct_state | CCT_STATE_LOWER_LIMIT_MASK) >> CCT_STATE_LOWER_LIMIT_POS_MASK;
			break;
		case CCT_STATE_SETTING:
			return (cct_state | CCT_STATE_SETTING_MASK) >> CCT_STATE_SETTING_POS_MASK;
			break;
		case CCT_STATE_DIMING_SETTING:
			return (cct_state | CCT_STATE_DIMING_SETTING_MASK) >> CCT_STATE_DIMING_SETTING_POS_MASK;
			break;
		default:
			return 0xFF;
	}
	return 0xFF;
}


void CCT_StateSet(CCT_STATE_TYPE type, uint8_t level)
{
	switch(type) {
		case CCT_STATE_UPPER_LIMIT:
			cct_state = (cct_state & (~CCT_STATE_UPPER_LIMIT_MASK)) | (CCT_STATE_UPPER_LIMIT << CCT_STATE_UPPER_LIMIT_POS_MASK);
			break;
		case CCT_STATE_LOWER_LIMIT:
			cct_state = (cct_state & (~CCT_STATE_LOWER_LIMIT_MASK)) | (CCT_STATE_LOWER_LIMIT << CCT_STATE_LOWER_LIMIT_POS_MASK);
			break;
		case CCT_STATE_SETTING:			
			cct_state = (cct_state & (~CCT_STATE_SETTING_MASK)) | (CCT_STATE_SETTING << CCT_STATE_SETTING_POS_MASK);
			break;
		case CCT_STATE_DIMING_SETTING:
			cct_state = (cct_state & (~CCT_STATE_DIMING_SETTING_MASK)) | (CCT_STATE_DIMING_SETTING << CCT_STATE_DIMING_SETTING_POS_MASK);
			break;
	}
}

void CCT_StateUpdate(void)
{
	if(CCT_StateGet(CCT_STATE_SETTING) == DIP)
	{
		cct_state = GPIO_Poll();
	}
	else {
//		cct_state = 
	}
}
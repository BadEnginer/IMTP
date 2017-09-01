#include "L6470.h"

void	SetParam(ServoReg in_servo_reg, uint32_t value)
{
	SPI_WriteByte((uint8_t) in_servo_reg);
	switch (in_servo_reg)
	{
		case ADR_ABS_POS: ;
		case ADR_MARK: ;
			SPI_WriteByte((uint8_t)(value >> 16));
		case ADR_EL_POS: ;
		case ADR_ACC: ;
		case ADR_DEC: ;
		case ADR_MAX_SPEED: ;
		case ADR_MIN_SPEED: ;
		case ADR_FS_SPD: ;
		case ADR_CONFIG: ;
		case ADR_STATUS: ;
			SPI_WriteByte((uint8_t)(value >> 8));
		default:
			SPI_WriteByte((uint8_t)(value));
	}
}

uint32_t GetParam(ServoReg out_servo_reg)
{
	uint32_t temp = 0;
	uint32_t rx = 0;

	/* Send GetParam operation code to dSPIN */
	temp = SPI_ReadByte((uint8_t)GET_PARAM | (uint8_t)out_servo_reg);
	/* MSB which should be 0 */
	temp = temp << 24;
	rx |= temp;
	switch (out_servo_reg)
	{
		case ADR_ABS_POS: ;
		case ADR_MARK: ;
		case ADR_SPEED:
		temp = SPI_ReadByte((uint8_t)(0x00));
		temp = temp << 16;
		rx |= temp;
		case ADR_EL_POS: ;
		case ADR_ACC: ;
		case ADR_DEC: ;
		case ADR_MAX_SPEED: ;
		case ADR_MIN_SPEED: ;
		case ADR_FS_SPD: ;
		case ADR_CONFIG: ;
		case ADR_STATUS:
			temp = SPI_ReadByte((uint8_t)(0x00));
			temp = temp << 8;
			rx |= temp;
		default:
			temp = SPI_ReadByte((uint8_t)(0x00));
		rx |= temp;
	}
	return rx;
}
void	Run(ServoDirect direct, uint32_t speed)
{
		/* Send RUN operation code to dSPIN */
		SPI_ReadByte((uint8_t)RUN | (uint8_t)direct);
		/* Send speed - byte 2 data dSPIN */
		SPI_ReadByte((uint8_t)(speed >> 16));
		/* Send speed - byte 1 data dSPIN */
		SPI_ReadByte((uint8_t)(speed >> 8));
		/* Send speed - byte 0 data dSPIN */
		SPI_ReadByte((uint8_t)(speed));
}
void	StepClock(ServoDirect direct) // Запустить от  другово такта хз
{
		/* Send StepClock operation code to dSPIN */
		SPI_ReadByte((uint8_t) STEP_CLOCK | (uint8_t)direct);
}
void	Move(ServoDirect direct, uint32_t n_step)
{
		/* Send Move operation code to dSPIN */
		SPI_ReadByte((uint8_t)MOVE | (uint8_t)direct);
		/* Send n_step - byte 2 data dSPIN */
		SPI_ReadByte((uint8_t)(n_step >> 16));
		/* Send n_step - byte 1 data dSPIN */
		SPI_ReadByte((uint8_t)(n_step >> 8));
		/* Send n_step - byte 0 data dSPIN */
		SPI_ReadByte((uint8_t)(n_step));
}
void	GoTo(uint32_t abs_pos)
{
		/* Send GoTo operation code to dSPIN */
		SPI_ReadByte(GO_TO);
		/* Send absolute position parameter - byte 2 data to dSPIN */
		SPI_ReadByte((uint8_t)(abs_pos >> 16));
		/* Send absolute position parameter - byte 1 data to dSPIN */
		SPI_ReadByte((uint8_t)(abs_pos >> 8));
		/* Send absolute position parameter - byte 0 data to dSPIN */
		SPI_ReadByte((uint8_t)(abs_pos));
}
void	GoTo_DIR(ServoDirect direct, uint32_t abs_pos)
{
		/* Send GoTo_DIR operation code to dSPIN */
		SPI_ReadByte((uint8_t)GO_TO_DIR | (uint8_t)direct);
		/* Send absolute position parameter - byte 2 data to dSPIN */
		SPI_ReadByte((uint8_t)(abs_pos >> 16));
		/* Send absolute position parameter - byte 1 data to dSPIN */
		SPI_ReadByte((uint8_t)(abs_pos >> 8));
		/* Send absolute position parameter - byte 0 data to dSPIN */
		SPI_ReadByte((uint8_t)(abs_pos));
}
//	bool	GoUntil(ACT, DIR, SPD); почитать ...
//	bool	ReleseSW(ACT, DIR); тоже ересь какая то
void	GoHome(void)
{
	SPI_ReadByte(GO_HOME);
}
void	GoMark(void)
{
	SPI_ReadByte(GO_MARK);
}
void	ResetPos(void)
{
	SPI_ReadByte(RESET_POS);
}
void	ResetDevice(void)
{
	SPI_ReadByte(RESET_DEVICE);
}
void	SoftStop(void)
{
	SPI_ReadByte(SOFT_STOP);
}
void	HardStop(void)
{
	SPI_ReadByte(HARD_STOP);
}
void	SoftHiZ(void)
{
	SPI_ReadByte(SOFT_HIZ);
}
void	HardHiZ(void)
{
	SPI_ReadByte(HARD_HIZ);
}
uint16_t	GetStatus(void)
{
	uint16_t temp = 0;
	uint16_t rx = 0;

	/* Send GetStatus operation code to dSPIN */
	SPI_ReadByte(GET_STATUS);
	/* Send zero byte / receive MSByte from dSPIN */
	temp = SPI_ReadByte((uint8_t)(0x00));
	temp = temp << 8;
	rx |= temp;
	/* Send zero byte / receive LSByte from dSPIN */
	temp = SPI_ReadByte((uint8_t)(0x00));
	rx |= temp;
	return rx;
}

void ReadStatusL6470(StatusServo * status)
{
	status->abs_pos			=	GetParam(ADR_ABS_POS);
	status->el_pos			=	GetParam(ADR_EL_POS);
	status->mark			=	GetParam(ADR_MARK);
	status->speed			=	GetParam(ADR_SPEED);
	status->acc				=	GetParam(ADR_ACC);
	status->dec				=	GetParam(ADR_DEC);
	status->max_speed		=	GetParam(ADR_MAX_SPEED);
	status->min_speed		=	GetParam(ADR_MIN_SPEED);
	status->fs_spd			=	GetParam(ADR_FS_SPD);
	status->kval_hold		=	GetParam(ADR_KVAL_HOLD);
	status->kval_run		=	GetParam(ADR_KVAL_RUN);
	status->kval_acc		=	GetParam(ADR_KVAL_ACC);
	status->kval_dec		=	GetParam(ADR_KVAL_DEC);
	status->int_spd			=	GetParam(ADR_INT_SPD);
	status->st_slp			=	GetParam(ADR_ST_SLP);
	status->fn_slp_acc		=	GetParam(ADR_FN_SLP_ACC);
	status->fn_slp_dec		=	GetParam(ADR_FN_SLP_DEC);
	status->k_therm			=	GetParam(ADR_K_THERM);
	status->adc_out			=	GetParam(ADR_ABS_POS);
	status->ocd_th			=	GetParam(ADR_OCD_TH);
	status->stall_th		=	GetParam(ADR_STALL_TH);
	status->step_mode		=	GetParam(ADR_STEP_MODE);
	status->alarm_en.alarm	=	GetParam(ADR_ALARM_EN);
	status->config.config	=	GetParam(ADR_CONFIG);
	status->status.status	=	GetParam(ADR_STATUS);
}
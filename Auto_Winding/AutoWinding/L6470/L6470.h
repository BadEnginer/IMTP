#ifndef L6470_H

#define L6470_H
#include "../spi/spi.h"
#include <stdbool.h>
#include "../bits_macros.h"

typedef enum {
	ADR_ABS_POS			=((uint8_t)0x01),
	ADR_EL_POS			=((uint8_t)0x02),
	ADR_MARK			=((uint8_t)0x03),
	ADR_SPEED			=((uint8_t)0x04),
	ADR_ACC				=((uint8_t)0x05),
	ADR_DEC				=((uint8_t)0x06),
	ADR_MAX_SPEED		=((uint8_t)0x07),
	ADR_MIN_SPEED		=((uint8_t)0x08),
	ADR_FS_SPD			=((uint8_t)0x15),
	ADR_KVAL_HOLD		=((uint8_t)0x09),
	ADR_KVAL_RUN		=((uint8_t)0x0A),
	ADR_KVAL_ACC		=((uint8_t)0x0B),
	ADR_KVAL_DEC		=((uint8_t)0x0C),
	ADR_INT_SPD			=((uint8_t)0x0D),
	ADR_ST_SLP			=((uint8_t)0x0E),
	ADR_FN_SLP_ACC		=((uint8_t)0x0F),
	ADR_FN_SLP_DEC		=((uint8_t)0x10),
	ADR_K_THERM			=((uint8_t)0x11),
	ADR_ADC_OUT			=((uint8_t)0x12),
	ADR_OCD_TH			=((uint8_t)0x13),
	ADR_STALL_TH		=((uint8_t)0x14),
	ADR_STEP_MODE		=((uint8_t)0x16),
	ADR_ALARM_EN		=((uint8_t)0x17),
	ADR_CONFIG			=((uint8_t)0x18),
	ADR_STATUS			=((uint8_t)0x19),
	ADR_RESERVED_REG2	=((uint8_t)0x1A),
	ADR_RESERVED_REG1	=((uint8_t)0x1B)
	} ServoReg;
	
typedef enum {
	NOP					= ((uint8_t)0x00),
	SET_PARAM			= ((uint8_t)0x00),
	GET_PARAM			= ((uint8_t)0x20),
	RUN					= ((uint8_t)0x50),
	STEP_CLOCK			= ((uint8_t)0x58),
	MOVE				= ((uint8_t)0x40),
	GO_TO				= ((uint8_t)0x60),
	GO_TO_DIR			= ((uint8_t)0x68),
	GO_UNTIL			= ((uint8_t)0x82),
	GO_UNTIL_ACT_CPY	= ((uint8_t)0x8A),
	RELEASE_SW			= ((uint8_t)0x92),
	GO_HOME				= ((uint8_t)0x70),
	GO_MARK				= ((uint8_t)0x78),
	RESET_POS			= ((uint8_t)0xD8),
	RESET_DEVICE		= ((uint8_t)0xC0),
	SOFT_STOP			= ((uint8_t)0xB0),
	HARD_STOP			= ((uint8_t)0xB8),
	SOFT_HIZ			= ((uint8_t)0xA0),
	HARD_HIZ			= ((uint8_t)0xA8),
	GET_STATUS			= ((uint8_t)0xD0),
	RESERVED_CMD2		= ((uint8_t)0xEB),
	RESERVED_CMD1		= ((uint8_t)0xF8)
} ServoCommand;	

typedef enum {
		FWD		=((uint8_t)0x01),	// Направления вращения прямое
		BWD		=((uint8_t)0x00)	// Направления вращения обратное
	} ServoDirect;
	
typedef struct
{
	uint16_t HiZ:1;
	uint16_t BUSY:1;
	uint16_t SW_F:1;
	uint16_t SW_EVN:1;
	uint16_t DIR:1;
	uint16_t MOT_STATUS:2;
	uint16_t NOTPERF_CMD:1;
	uint16_t WRONG_CMD:1;
	uint16_t UVLO:1;
	uint16_t TH_WRN:1;
	uint16_t TH_SD:1;
	uint16_t OCD:1;
	uint16_t STEP_LOSS_A:1;
	uint16_t STEP_LOSS_B:1;
	uint16_t SCK_MOD:1;
} StatusReg;

typedef union
{
	uint16_t  status;
	StatusReg statusReg;
} uStatus;

typedef struct
{
	uint16_t OSC_SEL:3;
	uint16_t EXT_CLK:1;
	uint16_t SW_MODE:1;
	uint16_t EN_VSCOMP:1;
	uint16_t RESERVED:1;
	uint16_t OC_SD:1;
	uint16_t POW_SR:2;
	uint16_t F_PWM_DEC:3; // N	//f_pwm = (f_osc/512 * N) * M
	uint16_t F_PWM_INT:3; // M
} ConfigReg;

typedef union
{
	uint16_t  config;
	ConfigReg configReg;
} uConfig;

typedef struct
{
	uint8_t Overcurrent:1;
	uint8_t Thermal_shutdown:1;
	uint8_t Thermal_warning:1;
	uint8_t Undervoltage:1;
	uint8_t Stall_detection_Bridge_A:1;
	uint8_t Stall_detection_Bridge_B:1;
	uint8_t Switch_turn_on_event:1;
	uint8_t Wrong_or_non_performable_command:1;
} AlarmReg;

typedef union
{
	uint16_t  alarm;
	AlarmReg alarmReg;
} uAlarm;

typedef struct
{
	uint32_t abs_pos;
	uint16_t el_pos;
	uint32_t mark;
	uint32_t speed;
	uint16_t acc;
	uint16_t dec;
	uint16_t max_speed;
	uint16_t min_speed;
	uint16_t fs_spd;
	uint8_t  kval_hold; // Амплитуда напряжения при остоновке 
	uint8_t  kval_run;	// Амплитуда напряжения при вращении 
	uint8_t  kval_acc;	// Амплитуда напряжения при ускорениие 
	uint8_t  kval_dec;	// Амплитуда напряжения при замедлении 
	uint16_t int_spd;
	uint8_t  st_slp;
	uint8_t  fn_slp_acc;
	uint8_t  fn_slp_dec;
	uint8_t  k_therm;
	uint8_t  adc_out;
	uint8_t  ocd_th;
	uint8_t  stall_th;
	uint8_t  step_mode;
	uAlarm	 alarm_en;
	uConfig	 config;
	uStatus  status;
}	StatusServo;


void		SetParam(ServoReg in_servo_reg, uint32_t value);
uint32_t	GetParam(ServoReg out_servo_reg);
void		Run(ServoDirect direct, uint32_t speed);
void		StepClock(ServoDirect direct); // Запустить от  другово такта хз
void		Move(ServoDirect direct, uint32_t n_step);
void		GoTo(uint32_t abs_pos);
void		GoTo_DIR(ServoDirect direct, uint32_t abs_pos);
//	bool	GoUntil(ACT, DIR, SPD); почитать ... 
//	bool	ReleseSW(ACT, DIR); тоже ересь какая то 
void		GoHome(void);
void		GoMark(void);
void		ResetPos(void);
void		ResetDevice(void);
void		SoftStop(void);
void		HardStop(void);
void		SoftHiZ(void);
void		HardHiZ(void);
uint16_t	GetStatus(void);
uint8_t		Busy_HW(void);
void		ReadStatusL6470(StatusServo *);
	
#endif /* L6470_H_ */
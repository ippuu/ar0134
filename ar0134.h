//
//THIS File Area /include/media/ar0134.h
//

#ifndef _AR0134_H_
#define _AR0134_H_


#define AR0134_NAME "ar0134_i2c"
#define I2C_MAJOR   89
#define AR0134_MAGIC 'A'


typedef struct
{
        unsigned short startx;
        unsigned short starty;
        unsigned short endx;
        unsigned short endy;
}__attribute__((packed)) image_area;

typedef struct 
{
	unsigned short address;
	unsigned short data;
    unsigned int command;
    unsigned int flag;
    image_area active_area;            
    
}__attribute__((packed)) ar0134_add_data;

#define READ_DATA  _IOWR(AR0134_MAGIC,0,ar0134_add_data)
#define WRITE_DATA _IOWR(AR0134_MAGIC,1,ar0134_add_data)
#define CMD_MODE _IOWR(AR0134_MAGIC,2,ar0134_add_data)



#define AR0134_COMMAND_CNT  3


//Nomal Register Area
#define WRITE_ADDRESS 0x20
#define READ_ADDRESS 0x21

//Alterna Register Area
#define AL_WRITE_ADDRESS 0x30
#define AL_READ_ADDRESS 0x31

#define CHIP_VERSION 0x3000

#define REG_MOD_DEFAULT 0 // Nomal Register Area Access 
#define REG_MOD_AL 		1 // Alternate Registar Access Mode select
//command

enum func{
    ROW_NOISE_ROW=1,
    ROW_NOISE_COL,
    TEST_PATTERN_SOLID, 
    TEST_PATTERN_COL_BAR,
    TEST_PATTERN_FADE,
    TEST_PATTERN_CANCLE,
    GLOBAL_GAIN_UP,
    GLOBAL_GAIN_DOWN,
    ROW_MIRROR,
    COLUMN_MIRROR,
    
    
};
    


#define EXTENAL_CLK     24000000UL

// AR0134 Register 
//*****RegisterName*******Register Address****defald Value
#define CHIP_VER		    	0x3000 //0x2406
#define Y_ADDR_START	    	0x3002 //0x0000
#define X_ADDR_START	    	0x3004 //0x0000
#define Y_ADDR_END			0x3006 //0x03BF
#define X_ADDR_END			0x3008 //
#define FRAME_LEN_LINES		0x300A
#define LINE_LEN_PCK		    0x300C
#define REVISION_NMB		    0x300E //1byte
#define COARSE_INTG_TIME 	0x3012
#define FINE_INTG_TIME		0x3014
#define COARSE_INTG_TME_CB	0x3016
#define FINE_INTG_TIME_CB	0x3018
#define RESET_REGISTER		0x301A
#define DATA_PEDESTAL		0x301E
#define GPI_STATUS			0x3026
#define ROW_SPEED			0x3028
#define VT_PIX_CLK_DIV		0x302A
#define VT_SYS_CLK_DIV		0x302C
#define PRE_PLL_CLK_DIV		0x302E
#define PLL_MULTILIER		0x3030
#define DIGITAL_BINNING		0x3032
#define FRAME_COUNT			0x303A
#define FRAME_STATUS		    0x303C
#define READ_MODE			0x3040
#define DARK_CONTROL		    0x3044
#define FLASH				    0x3046
#define GREEN1_GAIN			0x3056
#define BLUE_GAIN			0x3058
#define RED_GAIN			    0x305A
#define GREEN2_GAIN			0x305C
#define GLOBAL_GAIN			0x305E
#define EMBEDDED_DATA_CTRL	0x3064
#define DATAPATH_SELECT		0x306E
#define TEST_PATTERN_MODE	0x3070
#define TEST_DATA_RED		0x3072
#define TEST_DATA_GREEN		0x3074
#define TEST_DATA_BLUE		0x3076
#define TEST_DATA_GREENB	0x3078
#define TEST_RAW_MODE		0x307A
#define SEQ_DATA_PORT		0x3086
#define SEQ_CTRL_PORT		0x3088
#define X_ADDR_START_CB		0x308A
#define Y_ADDR_START_CB		0x308C
#define X_ADDR_END_CB		0x308E
#define Y_ADDR_END_CB		0x3090
#define X_EVEN_INC			0x30A0
#define X_ODD_INC			0x30A2
#define Y_EVEN_INC			0x30A4
#define Y_ODD_INC			0x30A6
#define Y_ODD_INC_CB		    0x30A8
#define FRAME_LEN_LINE_CB	0x30AA
#define FRAME_EXPOSURE		0x30AC
#define DIGITAL_TEST		    0x30B0
#define TEMPSENS_DATA		0x30B2
#define TEMPSENS_CTRL		0x30B4
#define GREEN1_GAIN_CB		0x30BC
#define BLUE_GAIN_CB		    0x30BE
#define RED_GAIN_CB			0x30C0
#define GREEN2_GAIN_CB		0x30C2
#define GLOBAL_GAIN_CB		0x30C4
#define TEMPSENS_CALIB1		0x30C6
#define TEMPSENS_CALIB2		0x30C8
#define TEMPSENS_CALIB3     0x30CA
#define TEMPSENS_CALIB4		0x30CC
#define COLUMN_CORRECTION	0x30D4
#define AE_CTRL_REG			0x3100
#define AE_LUMA_TARGET_REG	0x3102
#define AE_MIN_EV_STEP_REG	0x3108
#define AE_MAX_EV_STEP_REG	0x310A
#define AE_DAMP_OFFSET_REG	0x310C
#define AE_DAMP_GAIN_REG    0x310E
#define AE_DAMP_MAX_REG		0x3110
#define AE_MAX_EXPOSURE_REG	0x311C
#define AE_MIN_EXPOSURE_REG	0x311E
#define AE_DARK_CUR_THRESH_REG	0x3124
#define AE_CURRENT_GAINS	    0x312A
#define AE_ROI_X_START_OFFSET	0x3140
#define AE_ROI_Y_START_OFFSET	0x3142
#define AE_ROI_X_SIZE		0x3144
#define AE_ROI_Y_SIZE		0x3146
#define AE_COARSE_INTEGRAION_TIME	0x3164
#define AE_AG_EXPOSURE_HI	0x3166
#define AE_AG_EXPOSURE_LO	0x3168	
#define DELTA_DK_LEVEL		0x3188
#define HISPI_TIMING		    0x31C0
#define HISPI_CRC_0			0x31C8
#define HISPI_CRC_1			0x31CA
#define HISPI_CRC_2			0x31CC
#define HISPI_CRC_3			0x31CE
#define STAT_FRAME_ID		0x31D2
#define I2C_WRT_CHKSUM		0x31D6
#define HORIZONTAL_CUR_POS	0x31E8
#define VERTICAL_CUR_POS	    0x31EA
#define HORIZONTAL_CUR_WIDTH	0x31EC
#define VERTICAL_CUR_WIDTH	0x31EE
#define I2C_IDS				0x31FC



unsigned short res640x480_init[]={
//regseter address , Data
 0x301A, 0x00D9, 	// RESET_REGISTER
 0x3088, 0x8000, 	// SEQ_CTRL_PORT
 
 //SEQ_DATA_PORT Start
 0x3086, 0x3227, 0x3086, 0x0101, 0x3086, 0x0F25, 0x3086, 0x0808,
 0x3086, 0x0227, 0x3086, 0x0101, 0x3086, 0x0837, 0x3086, 0x2700,
 0x3086, 0x0138, 0x3086, 0x2701, 0x3086, 0x013A, 0x3086, 0x2700,
 0x3086, 0x0125, 0x3086, 0x0020, 0x3086, 0x3C25, 0x3086, 0x0040,
 0x3086, 0x3427, 0x3086, 0x003F, 0x3086, 0x2500, 0x3086, 0x2037,
 0x3086, 0x2540, 0x3086, 0x4036, 0x3086, 0x2500, 0x3086, 0x4031,
 0x3086, 0x2540, 0x3086, 0x403D, 0x3086, 0x6425, 0x3086, 0x2020,
 0x3086, 0x3D64, 0x3086, 0x2510, 0x3086, 0x1037, 0x3086, 0x2520,
 0x3086, 0x2010, 0x3086, 0x2510, 0x3086, 0x100F, 0x3086, 0x2708,
 0x3086, 0x0802, 0x3086, 0x2540, 0x3086, 0x402D, 0x3086, 0x2608,
 0x3086, 0x280D, 0x3086, 0x1709, 0x3086, 0x2600, 0x3086, 0x2805,
 0x3086, 0x26A7, 0x3086, 0x2807, 0x3086, 0x2580, 0x3086, 0x8029,
 0x3086, 0x1705, 0x3086, 0x2500, 0x3086, 0x4027, 0x3086, 0x2222,
 0x3086, 0x1616, 0x3086, 0x2726, 0x3086, 0x2617, 0x3086, 0x3626,
 0x3086, 0xA617, 0x3086, 0x0326, 0x3086, 0xA417, 0x3086, 0x1F28,
 0x3086, 0x0526, 0x3086, 0x2028, 0x3086, 0x0425, 0x3086, 0x2020,
 0x3086, 0x2700, 0x3086, 0x2625, 0x3086, 0x0000, 0x3086, 0x171E,
 0x3086, 0x2500, 0x3086, 0x0425, 0x3086, 0x0020, 0x3086, 0x2117,
 0x3086, 0x121B, 0x3086, 0x1703, 0x3086, 0x2726, 0x3086, 0x2617,
 0x3086, 0x2828, 0x3086, 0x0517, 0x3086, 0x1A26, 0x3086, 0x6017,
 0x3086, 0xAE25, 0x3086, 0x0080, 0x3086, 0x2700, 0x3086, 0x2626,
 0x3086, 0x1828, 0x3086, 0x002E, 0x3086, 0x2A28, 0x3086, 0x081E,
 0x3086, 0x4127, 0x3086, 0x1010, 0x3086, 0x0214, 0x3086, 0x6060,
 0x3086, 0x0A14, 0x3086, 0x6060, 0x3086, 0x0B14, 0x3086, 0x6060,
 0x3086, 0x0C14, 0x3086, 0x6060, 0x3086, 0x0D14, 0x3086, 0x6060,
 0x3086, 0x0217, 0x3086, 0x3C14, 0x3086, 0x0060, 0x3086, 0x0A14,
 0x3086, 0x0060, 0x3086, 0x0B14, 0x3086, 0x0060, 0x3086, 0x0C14,
 0x3086, 0x0060, 0x3086, 0x0D14, 0x3086, 0x0060, 0x3086, 0x0811,
 0x3086, 0x2500, 0x3086, 0x1027, 0x3086, 0x0010, 0x3086, 0x2F6F,
 0x3086, 0x0F3E, 0x3086, 0x2500, 0x3086, 0x0827, 0x3086, 0x0008,
 0x3086, 0x3066, 0x3086, 0x3225, 0x3086, 0x0008, 0x3086, 0x2700,
 0x3086, 0x0830, 0x3086, 0x6631, 0x3086, 0x3D64, 0x3086, 0x2508,
 0x3086, 0x083D, 0x3086, 0xFF3D, 0x3086, 0x2A27, 0x3086, 0x083F,
 0x3086, 0x2C00,  //SEQ_DATA_PORT END
 
 
 0x301A, 0x10D8, 	// RESET_REGISTER
 0x30D4, 0x6007, 	// COLUMN_CORRECTION
 0x301A, 0x10DC, 	// RESET_REGISTER
 0x301A, 0x10D8, 	// RESET_REGISTER
 0x30D4, 0xE007, 	// COLUMN_CORRECTION
 0x301A, 0x10DC, 	// RESET_REGISTER
//PLL
 0x3028, 0x0010,		//ROW_SPEED = 16
 0x302A, 0x0008,		//VT_PIX_CLK_DIV = 8
 0x302C, 0x0001,		//VT_SYS_CLK_DIV = 1
 0x302E, 0x0008,		//PRE_PLL_CLK_DIV = 8
 0x3030, 0x00C6,		//PLL_MULTIPLIER = 198
 0x3032, 0x0000,		//DIGITAL_BINNING = 0
 0x30B0, 0x0080,		//DIGITAL_TEST = 128
//Timing
 0x301A, 0x00D8,		//RESET_REGISTER = 216
 0x301A, 0x10DC,		//RESET_REGISTER = 4316
 0x3002, 0x00F4,		//Y_ADDR_START = 244
 0x3004, 0x0142,		//X_ADDR_START = 322
 0x3006, 0x02D3,		//Y_ADDR_END = 723
 0x3008, 0x03C1,		//X_ADDR_END = 961
 0x300A, 0x03DB,		//FRAME_LENGTH_LINES = 987
 0x300C, 0x056C,		//LINE_LENGTH_PCK = 1388
 0x3012, 0x0216,		//COARSE_INTEGRATION_TIME = 534
 0x3014, 0x0000,		//FINE_INTEGRATION_TIME = 900
 0x3040, 0x0000,		//READ_MODE = 0
 0x3064, 0x1802,		//EMBEDDED_DATA_CTRL = 6146
 0x31C6, 0x8008,		//HISPI_CONTROL_STATUS = 32776
 0x30A2, 0x0001, 	// X_ODD_INC
 0x30A6, 0x0001, 	// Y_ODD_INC
 0x301A, 0x10DC 	// RESET_REGISTER
},

res1280x960_init[]={
 0x301A, 0x00D9, 	// RESET_REGISTER
 0x3088, 0x8000,	// SEQ_CTRL_PORT
 
 //SEQ_DATA_PORT start
 0x3086, 0x3227, 0x3086, 0x0101, 0x3086, 0x0F25, 0x3086, 0x0808,
 0x3086, 0x0227, 0x3086, 0x0101, 0x3086, 0x0837, 0x3086, 0x2700,
 0x3086, 0x0138, 0x3086, 0x2701, 0x3086, 0x013A, 0x3086, 0x2700,
 0x3086, 0x0125, 0x3086, 0x0020, 0x3086, 0x3C25, 0x3086, 0x0040,
 0x3086, 0x3427, 0x3086, 0x003F, 0x3086, 0x2500, 0x3086, 0x2037,
 0x3086, 0x2540, 0x3086, 0x4036, 0x3086, 0x2500, 0x3086, 0x4031,
 0x3086, 0x2540, 0x3086, 0x403D, 0x3086, 0x6425, 0x3086, 0x2020,
 0x3086, 0x3D64, 0x3086, 0x2510, 0x3086, 0x1037, 0x3086, 0x2520,
 0x3086, 0x2010, 0x3086, 0x2510, 0x3086, 0x100F, 0x3086, 0x2708,
 0x3086, 0x0802, 0x3086, 0x2540, 0x3086, 0x402D, 0x3086, 0x2608,
 0x3086, 0x280D, 0x3086, 0x1709, 0x3086, 0x2600, 0x3086, 0x2805,
 0x3086, 0x26A7, 0x3086, 0x2807, 0x3086, 0x2580, 0x3086, 0x8029,
 0x3086, 0x1705, 0x3086, 0x2500, 0x3086, 0x4027, 0x3086, 0x2222,
 0x3086, 0x1616, 0x3086, 0x2726, 0x3086, 0x2617, 0x3086, 0x3626,
 0x3086, 0xA617, 0x3086, 0x0326, 0x3086, 0xA417, 0x3086, 0x1F28,
 0x3086, 0x0526, 0x3086, 0x2028, 0x3086, 0x0425, 0x3086, 0x2020,
 0x3086, 0x2700, 0x3086, 0x2625, 0x3086, 0x0000, 0x3086, 0x171E,
 0x3086, 0x2500, 0x3086, 0x0425, 0x3086, 0x0020, 0x3086, 0x2117,
 0x3086, 0x121B, 0x3086, 0x1703, 0x3086, 0x2726, 0x3086, 0x2617,
 0x3086, 0x2828, 0x3086, 0x0517, 0x3086, 0x1A26, 0x3086, 0x6017,
 0x3086, 0xAE25, 0x3086, 0x0080, 0x3086, 0x2700, 0x3086, 0x2626,
 0x3086, 0x1828, 0x3086, 0x002E, 0x3086, 0x2A28, 0x3086, 0x081E,
 0x3086, 0x4127, 0x3086, 0x1010, 0x3086, 0x0214, 0x3086, 0x6060,
 0x3086, 0x0A14, 0x3086, 0x6060, 0x3086, 0x0B14, 0x3086, 0x6060,
 0x3086, 0x0C14, 0x3086, 0x6060, 0x3086, 0x0D14, 0x3086, 0x6060,
 0x3086, 0x0217, 0x3086, 0x3C14, 0x3086, 0x0060, 0x3086, 0x0A14,
 0x3086, 0x0060, 0x3086, 0x0B14, 0x3086, 0x0060, 0x3086, 0x0C14,
 0x3086, 0x0060, 0x3086, 0x0D14, 0x3086, 0x0060, 0x3086, 0x0811,
 0x3086, 0x2500, 0x3086, 0x1027, 0x3086, 0x0010, 0x3086, 0x2F6F,
 0x3086, 0x0F3E, 0x3086, 0x2500, 0x3086, 0x0827, 0x3086, 0x0008,
 0x3086, 0x3066, 0x3086, 0x3225, 0x3086, 0x0008, 0x3086, 0x2700,
 0x3086, 0x0830, 0x3086, 0x6631, 0x3086, 0x3D64, 0x3086, 0x2508,
 0x3086, 0x083D, 0x3086, 0xFF3D, 0x3086, 0x2A27, 0x3086, 0x083F,
 0x3086, 0x2C00, //EAN SEQ_DATA_PORT
 0x301A, 0x10D8, 	// RESET_REGISTER
 0x30D4, 0x6007, 	// COLUMN_CORRECTION
 0x301A, 0x10DC, 	// RESET_REGISTER
 0x301A, 0x10D8, 	// RESET_REGISTER
 0x30D4, 0xE007, 	// COLUMN_CORRECTION
 0x301A, 0x10DC, 	// RESET_REGISTER
//PLL
 0x3028, 0x0010,		//ROW_SPEED = 16
 0x302A, 0x0008,		//VT_PIX_CLK_DIV = 8
 0x302C, 0x0001,		//VT_SYS_CLK_DIV = 1
 0x302E, 0x0008,		//PRE_PLL_CLK_DIV = 8
 0x3030, 0x00C6,		//PLL_MULTIPLIER = 198
 0x3032, 0x0000,		//DIGITAL_BINNING = 0
 0x30B0, 0x0080,		//DIGITAL_TEST = 128
//Timing
 0x301A, 0x00D8,		//RESET_REGISTER = 216
 0x301A, 0x10DC,		//RESET_REGISTER = 4316
 0x3002, 0x0004,		//Y_ADDR_START = 4
 0x3004, 0x0002,		//X_ADDR_START = 2
 0x3006, 0x03C3,		//Y_ADDR_END = 963
 0x3008, 0x0501,		//X_ADDR_END = 1281
 0x300A, 0x03DB,		//FRAME_LENGTH_LINES = 987
 0x300C, 0x056C,		//LINE_LENGTH_PCK = 1388
 0x3012, 0x0216,		//COARSE_INTEGRATION_TIME = 534
 0x3014, 0x0000,	    //FINE_INTEGRATION_TIME = 900
 0x3040, 0x0000,		//READ_MODE = 0
 0x3064, 0x1802,		//EMBEDDED_DATA_CTRL = 6146
 0x31C6, 0x8008,		//HISPI_CONTROL_STATUS = 32776
 0x30A2, 0x0001,      // X_ODD_INC
 0x30A6, 0x0001,      // Y_ODD_INC
 0x301A, 0x10DC,      // RESET_REGISTER       
    
};



#endif

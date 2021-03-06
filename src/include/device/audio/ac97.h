#ifndef C_OS_DEVICE_AUDIO_AC97_H
#define C_OS_DEVICE_AUDIO_AC97_H
#define AC97_REG_RESET 				0x00
#define AC97_REG_MASTER_VOL			0x02
#define AC97_REG_HPPHONE_VOL		0x04
#define AC97_REG_MASTER_MONO_MUTE	0x06
#define AC97_REG_MASTER_TONE		0x08
#define AC97_REG_PC_BEEP_MUTE		0x0A
#define AC97_REG_PHONE_MUTE			0x0C
#define AC97_REG_MIC_MUTE			0x0E
#define AC97_REG_LINEIN_MUTE		0x10
#define AC97_REG_CD_MUTE			0x12
#define AC97_REG_VIDEO_MUTE			0x14
#define AC97_REG_AUX_MUTE			0x16
#define AC97_REG_PCMOUT_MUTE		0x18
#define AC97_REG_RECORD_SELECT		0x1A
#define AC97_REG_RECORD_MUTE		0x1C
#define AC97_REG_RECORDMIC_MUTE		0x1E
#define AC97_REG_GENPURPOSE			0x20
#define AC97_REG_3DCONTROL			0x22
#define AC97_REG_AC97RESERVED		0x24
#define AC97_REG_POWERDOWN_CTRLSTAT	0x26
#define AC97_REG_EXTENDED_AUDIO		0x28
#define AC97_REG_EXT_AUDIO_CTRLSTAT	0x2A
#define AC97_REG_PCM_FRONT_DAC_RATE	0x2C
#define AC97_REG_PCM_SRND_DAC_RATE	0x2E
#define AC97_REG_PCM_LFE_DAC_RATE	0x30
#define AC97_REG_PCM_LR_DAC_RATE	0x32
#define AC97_REG_PCM_MIN_DAC_RATE	0x34
#define AC97_REG_LFE_MUTE			0x36
#define AC97_REG_LR_MUTE			0x38
//0x38-0x56 reserved by Intel
#define AC97_REG_VENDOR_RESERVED1	0x58
#define AC97_REG_VENDOR_RESERVED2	0x7A
#define AC97_REG_VENDOR_ID1			0x7C
#define AC97_REG_VENDOR_ID2			0x7E


#endif

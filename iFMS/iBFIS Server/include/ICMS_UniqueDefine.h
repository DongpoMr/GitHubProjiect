#pragma once

#ifndef _ICMS_UNIQUEDEFINE_H
#define _ICMS_UNIQUEDEFINE_H

/************************�Զ�����뼯����********************************/
//��Դ���ʹ���
//����
#define ICMS_RESOUCE_SOBEY_MILICMS			0x00100001

//Sobey
#define ICMS_RESOUCE_SOBEY_NVR2000			0x00100002
#define ICMS_RESOUCE_SOBEY_NVR3000			0x00100003
#define ICMS_RESOUCE_SOBEY_OEMNVS			0x00100004
#define ICMS_RESOUCE_SOBEY_DVS0100BHD	    0x00110005

//sony 0x00010000
#define ICMS_RESOUCE_SONY_DF40P				0x00010001
#define ICMS_RESOUCE_SONY_CS1011			0x00010002
#define ICMS_RESOUCE_SONY_RZ25P				0x00010003
#define ICMS_RESOUCE_SONY_RX570P			0x00010004
#define ICMS_RESOUCE_SONY_RZ50P				0x00010005
#define ICMS_RESOUCE_SONY_CM120				0x00010006
#define ICMS_RESOUCE_SONY_DF70P				0x00010007
#define ICMS_RESOUCE_SONY_DS60				0x00010008
#define ICMS_RESOUCE_SONY_CS20				0x00010009
#define ICMS_RESOUCE_SONY_RX550P			0x0001000A
#define ICMS_RESOUCE_SONY_DM110				0x0001000B
#define ICMS_RESOUCE_SONY_DS10				0x0001000C
#define ICMS_RESOUCE_SONY_V704				0x0001000D

//���� 0x00020000
//IPC DS-ZCD712PF
#define ICMS_RESOUCE_DS_ZCD712PF			0x00020001
//DVS DS-6102HF
#define ICMS_RESOUCE_DS_6102HF			    0x00020002
//DVR DS-8004HF-S
#define ICMS_RESOUCE_DS_8004HFS			    0x00020003
//DS-2DF1-401E    10���������������
#define ICMS_RESOUCE_DS_2DF1401E		   0x00020004
//DS-2CD852MF-E   �������������
#define ICMS_RESOUCE_DS_2CD852MFE		   0x00020005
//DS-2CD892PF     ����ǹ�������
#define ICMS_RESOUCE_DS_2CD892PF		   0x00020006
//DS-2CD892P-IR3  ������⸨����Դ�����
#define ICMS_RESOUCE_DS_2CD892PIR3		   0x00020007

//DS-6104HC       ��Ƶ������
#define ICMS_RESOUCE_DS_6104HC			   0x00020008
//DS-6101HF-IP-A  ��Ƶ������
#define ICMS_RESOUCE_DS_6101HFIPA		   0x00020009
//DS-2CD6001HF/B  ������Ƶ������
#define ICMS_RESOUCE_DS_2CD6001HFB		   0x0002000a
//DS-2CD6001HF/P  ������Ƶ������
#define ICMS_RESOUCE_DS_2CD6001HFP		   0x0002000b

//ӯ��
#define ICMS_RESOUCE_HC_ENMA		       0x00020201
//��Ȼ
#define ICMS_RESOUCE_HC_JTDM		       0x00020202
//����
#define ICMS_RESOUCE_HC_SUPERB		       0x00020203


//�� 0x00030000
//DH-DVR0404LN-S
#define ICMS_RESOUCE_DH_DVR0404LN			0x00030001
//DH-NVS04EB
#define ICMS_RESOUCE_DH_NVS04EB			    0x00030002
//DH-IPC-FDB465P
#define ICMS_RESOUCE_DH_IPCFDB465P			0x00030003

//Vista ��������
#define  ICMS_RESOUCE_VISTA120              0x00040001

//Axis  0x00050000
#define  ICMS_RESOUCE_AXIS_Q1755            0x00050001


//����ҫ��  0x00060000
#define  ICMS_RESOUCE_SZYD_81L            0x00060001

//DDS�Ž�  0x00070000
#define  ICMS_RESOUCE_DDS_TWODOOR         0x00070001


//����ʿ  0x00080000
#define  ICMS_RESOUCE_EGISE_6208L         0x00080001

//Զ�̲��  0x00090000
#define  ICMS_RESOUCE_REMOTE_PLUG         0x00090001

//������Դ���ʹ�����

//ipgs�豸GUID
#define ICMS_EQUMODEGUID_IPGS (_T("{FBB0C875-BE9B-11E2-8492-FB031872F268}"))

//�豸����
#define ICMS_EQU_DVR					0x0101		//DVR
#define ICMS_EQU_NVR					0x0102		//NVR
#define ICMS_EQU_IPVIDICON				0x0103		//IPC
#define ICMS_EQU_DVS					0x0104		//DVS
#define ICMS_EQU_HOSTALARM              0x0105      //��������
#define ICMS_EQU_CASCADE				0x0106		//����
#define ICMS_EQU_INDPC			        0x0107		//���ػ�
#define ICMS_EQU_DVS5th					0x0108
#define ICMS_EQU_IPC5th					0x0109
#define ICMS_EQU_CTRLBOARD              0x010a      //����
#define ICMS_EQU_ENTRANCEGUARD			0x010b      //�Ž���267��
#define ICMS_EQU_PATROL					0x010c      //Ѳ�� ��268��
#define ICMS_EQU_MATRIX					0x010d     //����269��
#define ICMS_EQU_GRAPHJOINTER			0x010e     //ƴ������270��
#define ICMS_EQU_SCREEN					0x010f     //��Ļ�豸��271��
#define ICMS_EQU_DECORDER				0x0110		//��������272��


//̽ͷ��������
#define ICMS_SPYINPUTTYPE_OPEN			0x2001		//������8193��
#define ICMS_SPYINPUTTYPE_CLOSE			0x2002		//���գ�8194��

//�����������
#define ICMS_OUTPUTTYPE_OPEN		    0x3001	  //������12289��
#define ICMS_OUTPUTTYPE_CLOSE		    0x3002	 //���գ�12290��

//�豸װ��ǽǶ�
#define ICMS_DEVICE_ANGLE_0				0x0001
#define	ICMS_DEVICE_ANGLE_90			0x0002
#define	ICMS_DEVICE_ANGLE_180			0x0003
#define	ICMS_DEVICE_ANGLE_270			0x0004


//����ͷ���ʹ���
#define ICMS_VID_HIGHBALL				0x0301		//����
#define ICMS_VID_GUNNBALL				0x0302		//ǹ��
#define ICMS_VID_HALFBALL				0x0303		//����

//����
#define ICMS_VIDEO_LOWRATE				0x0801		//������
#define ICMS_VIDEO_HIGHRATE				0x0802		//������

//̽ͷ��������
#define ICMS_SPYALARM_BAGINBREAAK		0x0401		//�Ƿ�����

////�����������
#define ICMS_OUTPUT_EMAL				0xE301  //�ʼ����
#define ICMS_OUTPUT_SMS					0xE302  //�������
#define ICMS_OUTPUT_TEL					0xE303  //�绰���
#define ICMS_OUTPUT_LED					0xE304  //LED���
#define ICMS_OUTPUT_LIGHT				0xE305  //���������


//ϵͳȨ��
#define ICMS_SYS_AUT_BASE				0x0601		//��������
#define ICMS_SYS_AUT_LOCALKINPLAN		0x0602		//����¼��ƻ�������
#define ICMS_SYS_AUT_GROUPSURVEY		0x0603		//������Ѳ

//���豸Ȩ��
#define ICMS_SUBEQU_AUT_NETPARUPD		0x0701		//Զ�̲����޸�
#define ICMS_SUBEQU_AUT_NETRESTART		0x0702		//Զ������
#define ICMS_SUBEQU_AUT_STATESEARCH		0x0703		//״̬��ѯ
#define ICMS_SUBEQU_AUT_VOICELISTEN		0x0704		//��������
#define ICMS_SUBEQU_AUT_VOICETALK		0x0705		//�����Խ�


//��־����
#define ICMS_LOG_SYSTEM					0x0A01		//ϵͳ��־
#define ICMS_LOG_ALARM					0x0A02		//������־
#define ICMS_LOG_OPERATION				0x0A03		//������־
#define ICMS_LOG_PATROL					0x0A04		//Ѳ����־

//�ļ�����
#define ICMS_FILE_MANUALREC				0x0B01		//�ֶ�¼��
#define ICMS_FILE_ALARMREC				0x0B02		//����¼��
#define ICMS_FILE_SCHEMEREC				0x0B03		//�ƻ�¼��
#define ICMS_FILE_HISTORY				0x0B04		//��ʷ����
#define ICMS_FILE_ALARMSNAP				0x0B05		//����ץ֡
#define ICMS_FILE_MANUALSNAP			0x0B06		//�ֶ�ץ֡

//״̬����
#define ICMS_STATE_ORDERPROG			0x0C01		//�㲥
#define ICMS_STATE_DIRECTSEED			0x0C02		//ֱ��
#define ICMS_STATE_PLAN					0x0C03		//�ƻ�

//�ƻ�����
#define ICMS_PLAN_KINESCOPE				0x0D01		//¼��
#define ICMS_PLAN_GUARDAGAINST			0x0D02		//��������
#define ICMS_PLAN_PATROL				0x0D03		//Ѳ��

/*�˴��������޸�
#define ICMS_PLAN_PATROL				0x0D04		//����
*/

//����������//ʹ�ú����Դ���Ͷ���
//#define ICMS_SERVER_CONTROL				0x1001		//���Ʒ�����
//#define ICMS_SERVER_ALARM				    0x1002		//����������
//#define ICMS_SERVER_MAP					0x1303		//MAP������
//#define ICMS_SERVER_GIS					0x1004		//GIS������

//Ѳ������
#define ICMS_PATROL_MANUAL				0x1101		//�ֶ�
#define ICMS_PATROL_AUTO				0x1102		//�Զ�

//Matrix�忨���ʹ���
#define ICMS_MATRIX_VGA					0x1201		//VGA
#define ICMS_MATRIX_MD					0x1202		//MD

//Matrix�忨�ͺŴ���
#define ICMS_MATRIXNUM_USUAL			0x1301		//ͨ��
#define ICMS_MATRIXNUM_HKDS4004MD		0x1302		//����_DS4004MD

//����ǽ�������忨�������	
#define  ICMS_MATRIX_OUTTYPE_ONE   0x8001	//�����
#define  ICMS_MATRIX_OUTTYPE_TWO   0x8002	 //˫���
#define  ICMS_MATRIX_OUTTYPE_FOUR  0x8003	 //�����
#define  ICMS_MATRIX_OUTTYPE_EIGHT 0x8004	 //�����

//������־����
#define  ICMS_OPERLOG_SYS         0x1901	//ϵͳ����(��/�ػ�)��6401��
#define  ICMS_OPERLOG_TALK        0x1902	//�������ƣ�6402��
#define  ICMS_OPERLOG_SNAP        0x1903	//ץ֡��6403��
#define  ICMS_OPERLOG_MANREC      0x1904    //¼��6404��
#define  ICMS_OPERLOG_VOD         0x1905	//�طţ�6405��
#define  ICMS_OPERLOG_LIVE        0x1906    //ʵʱ����6406��
#define  ICMS_OPERLOG_MANUAL      0x1907	//��̨���ƣ�6407��
#define  ICMS_OPERLOG_MANCIRCLE   0x1908    //Ѳ�����ƣ�6408��
#define  ICMS_OPERLOG_SETMAN      0x1909	//���ù���6409��
#define  ICMS_OPERLOG_STORE       0x190a    //�洢����6410��
#define  ICMS_OPERLOG_TASK        0x190b    //�������6411��
#define  ICMS_OPERLOG_MANTEST     0x190c    //�豸Ѳ�죨6412��
#define  ICMS_OPERLOG_TRANSFILE   0x190d    //�ļ�Ǩ�� (6413)
#define  ICMS_OPERLOG_UPLOADFILE   0x190e    //�ļ����� (6414)

/***************************Ӧ�ó������********************************/
//���ݿ��������
#define ICMS_DBT_NON					0xF001		//������
#define ICMS_DBT_INSERT					0xF002		//��Ӳ���
#define ICMS_DBT_UPDATE					0xF003		//�޸Ĳ���
#define ICMS_DBT_DELETE					0xF004		//ɾ������
#define ICMS_DBT_SELETE					0xF005		//ѡ�����

/*************************** Enum�궨�� ********************************/
//��������¼�� -- ��������
#define ICMS_DATARATE_LOW				0x0801		//������
#define ICMS_DATARATE_HIGH				0x0802		//������

//����������� -- ����ָ���ʽ
#define ICMS_OUTRENEW_DELAY				0x0901		//�ӳٻָ�
#define ICMS_OUTRENEW_ALARMOVER			0x0902		//����������ָ�
#define ICMS_OUTRENEW_MANUAL			0x0903		//�ֶ��ָ�

//����Դ����
#define ICMS_OPERSRC_EMAP				0x5001		//��ͼ
#define ICMS_OPERSRC_USER				0x5002		//�û���Ϣ
#define ICMS_OPERSRC_SUBEQU				0x5003		//���豸



//����Դ����
#define ICMS_ALARMSOURCE_SUBEQU			0x4001	//���豸����
#define ICMS_ALARMSOURCE_SERVER			0x4002	//����������
#define ICMS_ALARMSOURCE_TASK			0x4003	//δ������񱨾�

//����������
#define ICMS_MAINSOURCE_CHANNEL			    0xE100		//ͨ��
#define ICMS_MAINSOURCE_PROBE				0xE200		//̽ͷ
#define ICMS_MAINSOURCE_OUTPUT		   		0xE300		//���
#define ICMS_MAINSOURCE_SYSTEM				0xE400		//ϵͳ
#define ICMS_MAINSOURCE_MANUAL				0xE500		//�ֶ�
#define ICMS_MAINSOURCE_OTHER				0xE600		//����
#define ICMS_MAINSOURCE_PATROL				0xE700		//Ѳ��
#define ICMS_MAINSOURCE_EGUARD				0xE800		//�Ž�


//�����¼����ʹ���
//�豸
#define ICMS_ALARMEVENT_DEVOPENFAILED			0xE001	/* ���豸ʧ�� */
#define	ICMS_ALARMEVENT_CHANNELGETSTREAMFAILED	0xE002	/* ��ȡʵʱ��ʧ�� */
#define ICMS_ALARMEVENT_CHANNELGETSTREAMSUCCESS	0xE003	/* ʵʱ���ָ� */

#define ICMS_ALARM_EQUIPMENT_STATE_REQ			0xE004		//��ȡ�豸����״̬
#define ICMS_ALARM_EQUIPMENT_STATE_ACK			0xE005

//ͨ��
#define	ICMS_ALARMEVENT_MOTIONPROBE           0xE101    //�ƶ����
#define ICMS_ALARMEVENT_VIDEOLOST             0xE102	//��Ƶ��ʧ
#define	ICMS_ALARMEVENT_SHIELDALARM           0xE103	//��ͷ�ڵ�
#define ICMS_ALARMEVENT_DEPA_VMF              0xE110    //�߼����ܱ���(Խ�硢���򡭡�) 
#define	ICMS_ALARMEVENT_FIELD_CROSS           0xE111	//�ܽ籣����Խ��
#define	ICMS_ALARMEVENT_FIELD_OVERLINE        0xE112	//�ܽ籣��������
#define	ICMS_ALARMEVENT_FIELD_WANDER          0xE113	//�ܽ籣�����ǻ�
#define	ICMS_ALARMEVENT_FIELD_DISAPEAR        0xE114	//�ܽ籣������ʧ
#define	ICMS_ALARMEVENT_MANACTION_CONVERSE    0xE115	//����Ϊ��⣺����
#define	ICMS_ALARMEVENT_FIELD_LEAVEBEHIND     0xE121	//�ܽ籣��������
#define	ICMS_ALARMEVENT_MANACTION_RATEABN     0xE122	//����Ϊ��⣺�ٶ��쳣
#define	ICMS_ALARMEVENT_VAHICLE_CONVERSE      0xE131	//������Ϊ��⣺����
#define	ICMS_ALARMEVENT_VAHICLE_SCRAM         0xE132    //������Ϊ��⣺��ͣ
#define	ICMS_ALARMEVENT_VAHICLE_ILLSTOP       0xE133	//������Ϊ��⣺�Ƿ�ͣ��
#define	ICMS_ALARMEVENT_VAHICLE_CROSSLINE     0xE134	//������Ϊ��⣺����Խ��
#define	ICMS_ALARMEVENT_OBJECT_COUNTNUM       0xE141    //���壯����ͳ�Ʊ���
#define	ICMS_ALARMEVENT_OBJECT_DUBOVERLINE    0xE142 //˫��Խ��   ԭ:�ܽ籣�������� ˫��
#define	ICMS_ALARMEVENT_OBJECT_HOLD           0xE143 //��Ա����
#define	ICMS_ALARMEVENT_OBJECT_TAMPERING      0xE144 //���ƻ���⣨�ڵ��� ��Ϳ���齹����λ��
#define	ICMS_ALARMEVENT_OBJECT_AUDIO          0xE145//������Ƶ��⣨����̽�⡢����̽�⣩
#define	ICMS_ALARMEVENT_FRAMERATE_ERROR       0xE146//֡���쳣
#define	ICMS_ALARMEVENT_VIDEOSTREAM_ERROR     0xE147//¼��ʧ��
#define	ICMS_ALARMEVENT_REALSTREAM_INTERRUPT  0xE148//ʵʱ���ж�
#define	ICMS_ALARMEVENT_DEVICE_OPEN_FAIL      0xE149//���豸ʧ��(������)


//̽ͷ//����
#define	ICMS_ALARMEVENT_INFRARED 			  0xE201    //����̽����
#define	ICMS_ALARMEVENT_MACROWAVE  	 		  0xE202    //΢��̽����
#define	ICMS_ALARMEVENT_ULTRASONIC  	 	  0xE203    //������̽����
#define	ICMS_ALARMEVENT_DOORPROTECT  		  0xE204    //�Ŵ�
#define	ICMS_ALARMEVENT_PERIMETER    		  0xE205    //�ܽ籨��̽����
#define	ICMS_ALARMEVENT_BURNGAS      		  0xE206    //ȼ��̽����
#define	ICMS_ALARMEVENT_FROGPROBE    		  0xE207    //����̽����
#define	ICMS_ALARMEVENT_SHAKEPROBE   		  0xE208    //��̽����
#define	ICMS_ALARMEVENT_GLASSBROKE   		  0xE209    //��������̽����
#define	ICMS_ALARMEVENT_TEMPERATURE   		  0xE20A    //�¶�̽����
#define	ICMS_ALARMEVENT_EXIBUTTON    		  0xE20B    //������ť
#define	ICMS_ALARMEVENT_FINGERPRINT    		  0xE20C    //ָ�Ƽ�ⱨ��

#define	ICMS_ALARMEVENT_OPENTOCLOSE    		  0xE211    //������
#define	ICMS_ALARMEVENT_CLOSETOOPEN    		  0xE212    //�ص���

//���
#define	ICMS_ALARMEVENT_SOUNDLIGHT 			  0xE301    //���ⱨ��

//ϵͳ
#define ICMS_ALARMEVENT_EQUERR				  0xE401	//ǰ���豸���ϱ���
#define ICMS_ALARMEVENT_SERVER				  0xE402	//���������ϱ���
#define ICMS_ALARMEVENT_NOCOMPLETE			  0xE403	//δ������񱨾�
#define ICMS_ALARMEVENT_NETERROR			  0xE404	//������ϱ���
#define ICMS_ALARMEVENT_FULLDISK			  0xE405	//Ӳ��������
#define ICMS_ALARMEVENT_DISKBREAK			  0xE406	//Ӳ�̹��ϱ���
#define ICMS_ALARMEVENT_DECORDERROR			  0xE407	//���뿨���󱨾�
#define ICMS_ALARMEVENT_CPUOVER			      0xE408	//CPU�����ɱ���
#define ICMS_ALARMEVENT_WRITEFAILED			  0xE409	//д�ļ�ʧ�ܱ���
#define ICMS_ALARMEVENT_ENCRYPTDOGERR		  0xE40A	//�����ܹ�����
#define ICMS_ALARMEVENT_NETRECONNECT		  0xE40B	//�����������ӳɹ�
#define ICMS_ALARMEVENT_ALARMDEFENSE	  	  0xE903	  //��������
#define ICMS_ALARMEVENT_TROUBLEDEFENSE	   	  0xE904	  //��������

//�ֶ�
#define ICMS_ALARMEVENT_MANUAL				  0xE501	//�ֶ�����
//����
#define ICMS_ALARMEVENT_OTHER				  0xE601	//��������
#define ICMS_ALARMEVENT_TEL				      0xE602	//�绰����
#define ICMS_ALARMEVENT_SMS				      0xE603	//���ű���

//Ѳ��
#define ICMS_ALARMEVENT_NOTARRIVE 		      0xE701    //δ��Ѳ����

//�Ž�
#define	ICMS_ALARMEVENT_MGMLOCK 		   0xE801    //����������
#define	ICMS_ALARMEVENT_DOORMGM 	       0xE802    //�Ŵ�
#define	ICMS_ALARMEVENT_CARDREADER	       0xE803    //����������
#define	ICMS_ALARMEVENT_DOORRELEASE        0xE804    //��������
#define	ICMS_ALARMEVENT_DOORBUTTON	       0xE805    //���Ű�ť
#define	ICMS_ALARMEVENT_FINGERMARK		      0xE806    //ָ��ʶ��
#define ICMS_ALARMEVENT_DOORACCESS	          0xE807    //������Ȩ����
#define ICMS_ALARMEVENT_DOORDENIED	          0xE808    //�Ƿ�������
#define ICMS_ALARMEVENT_DOORILLEGAL	          0xE809    //�������
#define ICMS_ALARMEVENT_DOORCLOSED	          0xE80A    //�Źر�
#define ICMS_ALARMEVENT_DOORFORCED	          0xE80B    //��ǿ�Ƚ���
#define ICMS_ALARMEVENT_DOORHELD	          0xE80C    //����ʱ�����
#define ICMS_ALARMEVENT_DOORBELL              0xE80D    //��������    
#define ICMS_ALARMEVENT_DOORINTIMIDATION	  0xE81E	//в�ȿ���
#define ICMS_ALARMEVENT_DOORLINKAGEOPEN	      0xE81F	//��������
#define ICMS_ALARMEVENT_DOORALWAYSOPEN	      0xE810	//�ų���
#define ICMS_ALARMEVENT_DOORALWAYSCLOSE		  0xE811	//�ų���
#define ICMS_ALARMEVENT_DOOROVERLOAD          0xE812	//����������Ա������
#define ICMS_ALARMEVENT_DOORATTENDANCE        0xE813    //�����¼�

//��Ƶ����������
#define ICMS_AUDIOCODEC_G711_64			0x7001		// G7.11��64kbps��
#define ICMS_AUDIOCODEC_G726_40			0x7002		// G7.26��40kbps��
#define ICMS_AUDIOCODEC_G726_32			0x7003		// G7.26��32kbps��
#define ICMS_AUDIOCODEC_G726_24			0x7004		// G7.26��24Kbps��
#define ICMS_AUDIOCODEC_G726_16			0x7005		// G7.26��16bps��


//���豸����
#define ICMS_SUBEQU_CHANNEL				0x0201		//ͨ��
#define ICMS_SUBEQU_SPY					0x0202		//̽ͷ
#define ICMS_SUBEQU_OUTPUT				0x0203		//���
#define ICMS_SUBEQU_EGUARD				0x0204		//�Ž�(516)
#define ICMS_SUBEQU_PATROL				0x0205		//Ѳ��(517)
#define ICMS_SUBEQU_DEARAE				0x0206		//����(518)


//������������
#define	ICMS_ACTION_RECORD  0x1601 //����¼��
#define	ICMS_ACTION_SNAP    0x1602 //����ץ֡
#define	ICMS_ACTION_PTZ     0x1603	//��̨����
#define	ICMS_ACTION_OUTPUT  0x1604	//�������
#define	ICMS_ACTION_TVWALL  0x1605	//����ǽ
#define	ICMS_ACTION_MONITOR 0x1606 //��ض˹���
#define	ICMS_ACTION_EMAIL   0x1607	//�ʼ�֪ͨ
#define	ICMS_ACTION_SMS     0x1608	//����֪ͨ

#define ICMS_
//��������״̬
typedef enum tag_enumAlarmStatus
{
	ICMS_ALARM_DISPOSE_NO    = 0x0F01,		//δ���� 
	ICMS_ALARM_DISPOSE_DOING = 0x0F02,		//������
	ICMS_ALARM_DISPOSE_OK    = 0x0F03       //�Ѵ���
}EN_ICMS_AlarmStatus;


//�����¼��ȼ�
typedef enum tag_ICMS_AlarmDegree
{
	ICMS_EMERGENCY  = 1,  //������Emergency��
	ICMS_ALERT      = 2,  //������Alert��
	ICMS_CRITICAL   = 3,  //�ؼ���Critical��
	ICMS_ERROR      = 4,  //����Error��
	ICMS_WARNING    = 5   //���棨Warning��
}EN_ICMS_AlarmDegree;

//ʵʱ����������
typedef enum {STOPPED,PLAY,PAUSE,SEEK_2_TIME,FORWARD_FRAME,BACKWARD_FRAME,FAST_FORWARD,FAST_BACKWARD}PLAY_CTRL;

//�޸�Ԥ�õ�
typedef enum {INSERT_POINT,UPDATE_POINT,DELETE_POINT,GOTO_POINT,STOP_POINT} SET_OPERATION;

//��̨����
typedef enum {PTZ_LEFT,PTZ_LEFT_UP,PTZ_UP,PTZ_UP_RIGHT,PTZ_RIGHT,PTZ_DOWN_RIGHT,PTZ_DOWN,PTZ_DOWN_LEFT,PTZ_ABSOLUTE_POS,PTZ_STOP_MOVE,\
PTZ_RESET, PTZ_PUSH_FAR, PTZ_PULL_NEAR }PTZ_DIRECTION;

//��̨�������ܿ���
typedef enum {CTRL_LIGHT,CTRL_FOG,CTRL_RAIN_BRUSH,PROTOCOL_TRANS}AUXILIARY_METHOD;

//��־���Ͷ���
typedef enum {SYSTEM_LOG,WARNING_LOG,OPER_LOG}LOG_KIND;

//��½��֤���ܷ�ʽ
typedef enum 
{
	NO_ENCRYPT = 0,//���Ĵ�������
	MD5 = 1,      //ʹ�ù�ϣֵ��������
	DES =2        //ʹ��des��������
}ENCRYPTTYPE;

//¼���ѯ����
#define  DEVICE_RECORDTYPE_ALL 0xFF //ȫ��¼������
#define  DEVICE_RECORDTYPE_TIMINGRECORD 0x0000 //��ʱ¼��
#define  DEVICE_RECORDTYPE_MOTIONDETECTION 0x0001 //�ƶ����
#define  DEVICE_RECORDTYPE_ALARMSPRING 0x0002 //��������
#define  DEVICE_RECORDTYPE_ALARMORMOTIONDETECTION 0x0003 //����|�ƶ����
#define  DEVICE_RECORDTYPE_ALARMANDMOTIONDETECTION 0x0004 //����&�ƶ����
//#define  DEVICE_RECORDTYPE_APPROACHALARM 0x0002 //�ӽ�����
//#define  DEVICE_RECORDTYPE_CASHOUTALARM 0x0003 //��������
//#define  DEVICE_RECORDTYPE_CASHINALARM 0x0004 //��������
#define  DEVICE_RECORDTYPE_COMMANDSPRING 0x0005 //�����
#define  DEVICE_RECORDTYPE_MANUALRECORD 0x0006 //�ֶ�¼��
#define  DEVICE_RECORDTYPE_SHAKEALARM 0x0007 //�𶯱���
#define  DEVICE_RECORDTYPE_EXTERIORALARM 0x0008 //�ⲿ����
#define  DEVICE_RECORDTYPE_CARDIDQUERY 0x0009 //���Ų�ѯ
#define  DEVICE_RECORDTYPE_COMBINATIONQUERY 0x000a //���������ѯ
#define  DEVICE_RECORDTYPE_PICQUERYBYCARDID 0x000b//�����Ų�ѯͼƬ
#define  DEVICE_RECORDTYPE_PICQUERY 0x000c//��ѯͼƬ
#define  DEVICE_RECORDTYPE_ALLALARM 0x000d //ȫ������

//¼��ط�״̬����
#define DEVICE_PLAYBACK_PAUSE 0x0003 //��ͣ����

#define DEVICE_PLAYBACK_START 0x0004//�ָ�����

#define DEVICE_PLAYBACK_FAST 0x0005//���

#define DEVICE_PLAYBACK_SLOW 0x0006//����

#define DEVICE_PLAYBACK_NORMAL 0x0007//�����ٶ�

#define DEVICE_PLAYBACK_FRAMETO 0x0008//��֡ǰ��

#define DEVICE_PLAYBACK_FRAMEBACK 0x0001//��֡����

#define DEVICE_PLAYBACK_STARTAUDIO 0x0009//������

#define DEVICE_PLAYBACK_STOPAUDIO 0x000a//�ر�����

#define DEVICE_PLAYBACK_AUDIOVOLUME 0x000b//��������

#define DEVICE_PLAYBACK_SETPOS 0x000c//�ı��ļ��طŵĽ���

#define DEVICE_PLAYBACK_GETPOS 0x000d//��ȡ�ļ��طŵĽ���

#define DEVICE_PLAYBACK_GETTIME 0x000e//��ȡ��ǰ�Ѿ����ŵ�ʱ��

#define DEVICE_PLAYBACK_GETFRAME 0x000f//��ȡ��ǰ�Ѿ����ŵ�֡��

#define DEVICE_PLAYBACK_GETTOTALFRAMES 0x0010//��ȡ��ǰ�����ļ��ܵ�֡��

#define DEVICE_PLAYBACK_GETTOTALTIME 0x0011//��ȡ��ǰ�����ļ��ܵ�ʱ��

#define DEVICE_PLAYBACK_SLOWFORWARD	    0x00012//����
#define DEVICE_PLAYBACK_SLOWBACKWARD	0x00013//����

/*************************** ͨѶ����궨�� ********************************/
#pragma pack(push,1)
typedef struct tag_structiCMSCommand
{
	WORD  wSrcType;		    //Դ������
	WORD  wCmdMainType;     //�����������
	DWORD dwCmdSubType;     //�����������

	DWORD dwSeqID;          //�������
	WORD wExtendType;       //��չ��������
	DWORD dwExndSize;       //��չ���ݴ�С

	tag_structiCMSCommand()
	{
		wSrcType = 0;
		wCmdMainType = 0;
		dwCmdSubType = 0;     
		dwSeqID = 0;        
		wExtendType = 0;       
		dwExndSize = 0;
	}
}ST_ICMS_Command;
#pragma pack(pop)

#define		ICMS_SERVER_SWITCH				0x1001  //ת����ý�������
#define		ICMS_SERVER_ALARM				0x1002  //����������	
#define		ICMS_SERVER_ACQUISVER			0x1102  //�����ɼ�������	
#define		ICMS_SERVER_EMAP			    0x1003  //���ӵ�ͼ������
#define		ICMS_SERVER_GISSYS				0x1004  //��ͼ��Ϣ������
#define		ICMS_SERVER_INSERV				0x1006  //���ܷ���������
#define		ICMS_SERVER_MEETING				0x1007  //���������
#define  	ICMS_SERVER_MATRIX			    0x1008  //����ǽ������	
#define		ICMS_SERVER_MCENTER				0x1009  //���������	
#define		ICMS_SERVER_STORE				0x100A  //�洢��ý�������	
#define		ICMS_SERVER_SOFTDOG			    0x100B  //���������
#define		ICMS_SERVER_TRANSFER			0x100C  //Ǩ�Ʒ�����
#define     ICMS_SERVER_TRANSWITCH			0x100D  //Ǩ����ý�������
#define		ICMS_SERVER_DBSERVER			0x100F	//���ݿ��ŷ�
#define		ICMS_SERVER_DCS					0x1011	//�������Ʒ�����
#define		ICMS_SERVER_NETGATE				0x1012	//���������ط�����
#define		ICMS_SERVER_IPGS				0x1013	//�������ط�����
#define		ICMS_SERVER_SSWITCH				0x1014	//ת��ý�������
#define		ICMS_SERVER_DOMAIN				0x1015	//�ֲ�ʽ�������
#define		ICMS_SERVER_NMS					0x1016	//�ۺ���ά���������

#define		ICMS_CLIENT_MONITOR				0xff01  //��ؿͻ���
#define  	ICMS_CLIENT_MANAGE				0xff02  //���ù���ͻ���	
#define		ICMS_CLIENT_MATRIX				0xff03  //����ǽ�ͻ���	
#define		ICMS_ISWITCH_AGENT				0xff04  //���ڼ���ʱ��iSwitch
#define		ICMS_SERVER_SMPNVR			    0x10f1	//����SMP��NVR������
#define		ICMS_SERVER_SMPMAT			    0x10f2	//����SMP��MAT������
#define		ICMS_SERVER_SMPSPS			    0x10f3	//����SMP��SPS������

// ��ϵͳ����
#define ISMS_DSYSTEM_ISMS			0X0001		// SMSϵͳ
#define ISMS_DSYSTEM_ISMS_AGENCY	0X0002		// ������SMSϵͳ
#define ISMS_DSYSTEM_IPGS			0X0003		// IPGSϵͳ
#define ISMS_DSYSTEM_SMP			0X0004		// SMPϵͳ
#define ISMS_DSYSTEM_ICMS8000		0X0005		// ICMS8000ϵͳ
#define ISMS_DSYSTEM_ICMS6000		0X0006		// ICMS6000ϵͳ
#define ISMS_DSYSTEM_ILNVR			0X0007		// NVRϵͳ

//���������Ͷ���
#define		ICMS_TYPE_CMDTYPE_CTRL									0x0001   //��������
#define		ICMS_TYPE_CMDTYPE_ALARM									0x0002   //��������

#define		ICMS_TYPE_CMDTYPE_ISWITCH_INTERNAL						0xffff
#define     ICMS_TYPE_CMDTYPE_IWEB_INTERNAL                         0xfffe

#define	    ISMS_SOCIMONITOR_2_IPGS_GET_SERVERPORT_REQ         		0XB001	// IPGS��ȡIPGS��¼�˿�
#define	    ISMS_SOCIMONITOR_2_IPGS_GET_SERVERPORT_ACK         		0XB002
//�������������Ͷ���
//#define	ICMS_TYPE_CTRLTYPE_LOGIN_IN								0x0001   //��½����
//#define	ICMS_TYPE_CTRLTYPE_LOGIN_IN_ACK							0x0002   //��½��Ӧ

//��չ�������Ͷ���
#define		ICMD_TYPE_EXDTYPE_XML									0x0001	//XML��չ����
#define		ICMD_TYPE_EXDTYPE_BINARY								0x0002	//������������չ����
#define		ICMD_TYPE_EXDTYPE_MIX									0x0003	//XML+���������ݻ����չ����, 

#define		ICMS_TYPE_CMDTYPE_STREAMDATA							0x0003   //������
#define		ICMS_DEFINE_DATA_TYPE_GPS                               0x30	 //��ʾ�����ݰ�ΪGPS��������

//��Ϊ������ʱ����չ���ݵ�ͷ4���ֽ�ΪXML����
//Ȩ����Ϣ�������
//�û�ϵͳȨ��	iMonitor	iMC	
#define		ICMS_IMONITOR_2_IMC_GET_SYSTEM_POWER_REQ				0x0101
#define		ICMS_IMONITOR_2_IMC_GET_SYSTEM_POWER_ACK				0x0102

//ϵͳ���汾��Ϣ	iMonitor	iMC	
#define		ICMS_IMONITOR_2_IMC_GET_SYSTEM_INFO_REQ					0x801a
#define		ICMS_IMONITOR_2_IMC_GET_SYSTEM_INFO_ACK					0x801b

//��ȡ�豸��Ȩ��	iMonitor	iMC	
#define		ICMS_IMONITOR_2_IMC_GET_DEVICE_POWER_REQ				0x0103
#define		ICMS_IMONITOR_2_IMC_GET_DEVICE_POWER_ACK				0x0104

//�û����豸��Ȩ�޸���
#define     ICMS_TYPE_IMANTYPE_USER_PRIVILEGE_UPDATE				0x0b40
#define     ICMS_TYPE_IMANTYPE_USER_PRIVILEGE_UPDATE_ACK            0x0b41

//��֯�ṹ���������
//��ȡ���ݰ汾��Ϣ
#define		ICMS_IMONITOR_2_IMC_GET_VERSION_REQ						0x0205
#define		ICMS_IMONITOR_2_IMC_GET_VERSION_ACK						0x0206
//��ȡ���豸�����Ϣ	iMonitor	iMC	
#define		ICMS_IMONITOR_2_IMC_GET_SUBDEVICE_INFO_REQ				0x0201
#define		ICMS_IMONITOR_2_IMC_GET_SUBDEVICE_INFO_ACK				0x0202
//��ȡ��֯�ṹ��	iMonitor	iMC	
#define		ICMS_IMONITOR_2_IMC_GET_ORGANIZE_INFO_REQ				0x0203
#define		ICMS_IMONITOR_2_IMC_GET_ORGANIZE_INFO_ACK				0x0204
//��֯�ṹ������֪ͨ
#define		ICMS_UPDATE_ORGANIZE_NOTIFY								0x0207
// ���豸����֪ͨ
#define		ICMS_UPDATE_MAIN_DEVICE_NOTIFY							0x0208
//�洢��Դ�������֪ͨ
#define		ICMS_UPDATE_STORAGE_RESOURCE_NOTIFY						0x0209
//����Ԥ������
#define		ICMS_ALARM_PLAN_UPDATE_NOTIFY							0x020A
//����������Ϣ����
#define		ICMS_ALARM_ASS_UPDATE_NOTIFY							0x020B
//�ƻ��������
#define		ICMS_PLAN_UPDATE_NOTIFY									0x020C
//��ͼ����
#define		ISMS_MAP_LIST_UPDATE_NOTIFY								0x020D
#define		ISMS_MAP_LEAF_UPDATE_NOTIFY								0x020E
#define		ISMS_MAP_ASS_UPDATE_NOTIFY								0x020F
#define		ISMS_MAP_EQU_ASS_UPDATE_NOTIFY							0x0210
#define		ISMS_MAPPICTURE_UPDATE_NOTIFY							0x0211

//ʵʱ�࿴�������
//����ʵʱ��Ƶ,��Ƶ����	iMonitor	iSwitch	
#define		ICMS_IMONITOR_2_ISWITCH_GET_REAL_STREAM_REQ				0x0301
#define		ICMS_IMONITOR_2_ISWITCH_GET_REAL_STREAM_ACK				0x0302

//����ʵʱ������rtp�˿�	iMonitor	iSwitch	
#define		ICMS_IMONITOR_2_ISWITCH_SET_REAL_STREAM_REQ				0x0303
#define		ICMS_IMONITOR_2_ISWITCH_SET_REAL_STREAM_ACK				0x0304

//ʵʱ����������	iMonitor	iSwitch	
#define		ICMS_IMONITOR_2_ISWITCH_PLAY_CTRL_STREAM_REQ			0x0305
#define		ICMS_IMONITOR_2_ISWITCH_PLAY_CTRL_STREAM_ACK			0x0306

//ʵʱ�����ӱ�ǩ	iMonitor	iSwitch	
#define		ICMS_IMONITOR_2_ISWITCH_ADD_REAL_STREAM_TAG_REQ			0x0307
#define		ICMS_IMONITOR_2_ISWITCH_ADD_REAL_STREAM_TAG_ACK			0x0308

//����ʵʱ���Ƿ����¼��	iMonitor	iSwitch	
#define		ICMS_IMONITOR_2_ISWITCH_CTRL_REAL_STREAM_RECORD_REQ		0x0309
#define		ICMS_IMONITOR_2_ISWITCH_CTRL_REAL_STREAM_RECORD_ACK		0x030a

//ʵʱ��ץ֡	iMonitor	iSwitch	
#define		ICMS_IMONITOR_2_ISWITCH_GRASP_REAL_STREAM_FRAME_REQ		0x030b
#define		ICMS_IMONITOR_2_ISWITCH_GRASP_REAL_STREAM_FRAME_ACK		0x030c

//����ʵʱ��ͼ�����
//���ݷ��� : iMonitor ----> iSwitch
#define		ICMS_IMONITOR_2_ISWITCH_SET_PHOTO_INFO_REQ				0x030d
#define		ICMS_IMONITOR_2_ISWITCH_SET_PHOTO_INFO_ACK				0x030e

//���������Խ�����	iMonitor	iSwitch	
#define		ICMS_IMONITOR_2_ISWITCH_GET_AUDIOCHAT_REQ				0x030f
#define		ICMS_IMONITOR_2_ISWITCH_GET_AUDIOCHAT_ACK				0x0310

//�ֶ��������
//���ݷ��� : iMonitor ----> iSwitch
#define		ICMS_IMONITOR_2_ISWITCH_MANUAL_OUTPUT_REQ					0x0311
#define		ICMS_IMONITOR_2_ISWITCH_MANUAL_OUTPUT_ACK					0x0312

// iSwitch -> iMonitor
#define	    ICMS_ISWITCH_2_IMONITOR_RESSTATUS_NOTIFY		         0x0313
#define	    ICMS_ISWITCH_2_IMONITOR_RESSTATUS_NOTIFY_ACK		     0x0314

//ֹͣ�����Խ�
//���ݷ��� : iMonitor ----> iSwitch
#define		ICMS_IMONITOR_2_ISWITCH_STOP_AUDIOCHAT_REQ					0x0315
#define		ICMS_IMONITOR_2_ISWITCH_STOP_AUDIOCHAT_ACK					0x0316

#define		ICMS_TYPE_CTRLTYPE_DEVICE_CONTROL_REQ						0x0317
#define		ICMS_TYPE_CTRLTYPE_DEVICE_CONTROL_ACK						0x0318

#define		ICMS_TYPE_CTRLTYPE_DEVICE_CONNECT_REQ						0x0319
#define		ICMS_TYPE_CTRLTYPE_DEVICE_CONNECT_ACK						0x031a

//����GPS����������
//���ݷ���iMonitor---->iSwitch
#define		ICMS_IMONITOR_2_GPSSVR_GETGPSDATA_STREAM_REQ				0x031b
#define		ICMS_IMONITOR_2_GPSSVR_GETGPSDATA_STREAM_ACK				0x031c

//���ݷ��� : iAlarm ----> iSwitch Alarm��iSwitch��ȡԤ¼��Ϣ
#define		ICMS_TYPE_CTRLTYPE_PREREC_STATUS_REQ					0x0d3d
#define		ICMS_TYPE_CTRLTYPE_PREREC_STATUS_ACK					0x0d3e

//����Ԥ¼ʱ����ý�彻�����Ʒ�������ַ	iAlarm --->	iMC	
#define		ICMS_IALARM_2_IMC_GET_ISWTICH_ADDR_REQ					0x0d3f
#define		ICMS_IALARM_2_IMC_GET_ISWTICH_ADDR_ACK					0x0d40

//�豸��/����״̬֪ͨ
//���ݷ��� : iSwitch ---->iAlarm  iAlarm  ---->iMonitor
#define		ICMS_TYPE_CTRLTYPE_DEVICE_STATUS_NOTIFY		            0x0d41
#define	    ICMS_TYPE_CTRLTYPE_DEVICE_STATUS_NOTIFY_ACK		        0x0d42

//������־����
//���ݷ��� : iMonitor ---->iAlarm  
 #define	ICMS_TYPE_CTRLTYPE_GET_ALARMLOG_REQ		                0x0d43
#define	    ICMS_TYPE_CTRLTYPE_GET_ALARMLOG_ACK		                0x0d44

//ʵʱ��ת����������
//���ݷ��� : iMC <------> iSwitch
#define		ICMS_MC_2_ISWITCH_STREAM_TRANSFER_REQ					0x0d45
#define		ICMS_MC_2_ISWITCH_STREAM_TRANSFER_ACK					0x0d46

//�豸״̬��ѯ
//���ݷ���  iMonitor <--------> iMC <--------> iSwitch
#define     ICMS_2_SWITCH_DEVICE_STATUS_QUERY_REQ                    0x0df7
#define     ICMS_2_SWITCH_DEVICE_STATUS_QUERY_ACK                    0x0df8

#define     ICMS_2_SWITCH_DEVICE_INFO_QUERY_REQ						 0x0df9	
#define     ICMS_2_SWITCH_DEVICE_INFO_QUERY_ACK						 0x0dfa

#define		ICMS_ALARM_EQUIPSTATE_NOTIFY							0x0a1b

//�豸����״̬
#define ISMS_GET_SUBEQUIPMENT_ONLINESTATE_REQ		0x8254
#define ISMS_GET_SUBEQUIPMENT_ONLINESTATE_ACK		0x8255

// �豸����״̬���֪ͨ
#define ISMS_SUBEQUIPMENT_ONLINESTATE_CHANGED_NOTIFY	0x824f

/*************************** VOD�㲥������� ********************************/
//��ȡ vod��ѯ�б�	iMonitor	iSwitch	
#define		ICMS_IMONITOR_2_IMC_GET_VOD_LIST_REQ	                0x0401
#define		ICMS_IMONITOR_2_IMC_GET_VOD_LIST_ACK					0x0402

//SIP��ȡ vod��ѯ�б�	iMonitor	iSwitch	
#define     ICMS_IMONITOR_2_IMC_SIP_GET_VOD_LIST_REQ                0x1409
#define     ICMS_IMONITOR_2_IMC_SIP_GET_VOD_LIST_ACK                0x1410

//��ȡ¼��ץ֡ͼƬ�б�	iMonitor	iSwitch	
#define		ICMS_IMONITOR_2_IMC_GET_VIDEO_GRAB_PIC_REQ				0x0403
#define		ICMS_IMONITOR_2_IMC_GET_VIDEO_GRAB_PIC_ACK				0x0404

//�����ȡ¼��ץ֡	iMonitor	iSwitch	
#define		ICMS_IMONITOR_2_ISWITCH_GET_VIDEO_RECORD_REQ		    0x0405
#define		ICMS_IMONITOR_2_ISWITCH_GET_VIDEO_RECORD_ACK			0x0406

//��ȡץ֡ͼƬ	iMonitor	iSwitch	
#define		ICMS_IMONITOR_2_ISWITCH_GET_VIDEO_GRAB_PIC_REQ			0x0407
#define		ICMS_IMONITOR_2_ISWITCH_GET_VIDEO_GRAB_PIC_ACK			0x0408

//����vod�ļ��㲥��Ƶ,��Ƶ����	iMonitor	iSwitch	
#define		ICMS_IMONITOR_2_ISWITCH_GET_VOD_STREAM_REQ				0x0409
#define		ICMS_IMONITOR_2_ISWITCH_GET_VOD_STREAM_ACK				0x040a

//����vod�ļ��㲥��Ƶ,��Ƶ����	iMonitor	iSwitch	
#define		ICMS_IMONITOR_2_ISWITCH_SIP_GET_VOD_STREAM_REQ			0x140a
#define		ICMS_IMONITOR_2_ISWITCH_SIP_GET_VOD_STREAM_ACK			0x140b

//����vod����rtp�˿�	iMonitor	iSwitch	
#define		ICMS_IMONITOR_2_ISWITCH_SET_VOD_STREAM_REQ				0x040b
#define		ICMS_IMONITOR_2_ISWITCH_SET_VOD_STREAM_ACK				0x040c

//vod����������iMonitor	iSwitch	
#define		ICMS_IMONITOR_2_ISWITCH_CTRL_VOD_STREAM_REQ				0x040d
#define		ICMS_IMONITOR_2_ISWITCH_CTRL_VOD_STREAM_ACK				0x040e

//vod��sip��������iMonitor	iSwitch	
#define		ICMS_IMONITOR_2_ISWITCH_SIP_CTRL_VOD_STREAM_REQ			0x140c
#define		ICMS_IMONITOR_2_ISWITCH_SIP_CTRL_VOD_STREAM_ACK			0x140d

//vod���ӱ�ǩ	iMonitor	iSwitch	
#define		ICMS_IMONITOR_2_ISWITCH_ADD_VOD_STREAM_TAG_REQ			0x040f
#define		ICMS_IMONITOR_2_ISWITCH_ADD_VOD_STREAM_TAG_ACK			0x0410

//vodץ֡	iMonitor	iSwitch	
#define		ICMS_IMONITOR_2_ISWITCH_GRASP_VOD_STREAM_FRAME_REQ		0x0411
#define		ICMS_IMONITOR_2_ISWITCH_GRASP_VOD_STREAM_FRAME_ACK		0x0412

//����vod�ļ�tag��Ϣ	iMonitor	iMC	
#define		ICMS_IMONITOR_2_IMC_GET_VOD_TAG_INFO_REQ			    0x0413
#define		ICMS_IMONITOR_2_IMC_GET_VOD_TAG_INFO_ACK			    0x0414

//iMonitor����iSwitch�ƶ�vod�ļ������ʱ��
#define     ICMS_IMONITOR_2_ISWITCH_SEEK_2_RELATIVE_TIME_REQ		0x0415
#define     ICMS_IMONITOR_2_ISWITCH_SEEK_2_RELATIVE_TIME_ACK		0x0416

//vod��sip seek����iMonitor	iSwitch	
#define     ICMS_IMONITOR_2_ISWITCH_SIP_SEEK_2_RELATIVE_TIME_REQ	0x1415
#define     ICMS_IMONITOR_2_ISWITCH_SIP_SEEK_2_RELATIVE_TIME_ACK	0x1416

//iMonitor����iSwitch��ȡ��һ���������е�gop
#define     ICMS_IMONITOR_2_ISWITCH_GET_NEXT_GOP_REQ				0x0417
#define     ICMS_IMONITOR_2_ISWITCH_GET_NEXT_GOP_ACK				0x0418

//iMonitor����iSwitch��ȡ��һ���������е�gop
#define     ICMS_IMONITOR_2_ISWITCH_GET_PREV_GOP_REQ				0x0419
#define     ICMS_IMONITOR_2_ISWITCH_GET_PREV_GOP_ACK				0x041A

//iMonitor����iSwitch��ȡ��ȡ��һ���������
#define     ICMS_IMONITOR_2_ISWITCH_GET_FAST_FORWARD_REQ		    0x041B
#define     ICMS_IMONITOR_2_ISWITCH_GET_FAST_FORWARD_ACK		    0x041C

//iMonitor����iSwitch��ȡ��һ���������
#define     ICMS_IMONITOR_2_ISWITCH_GET_FAST_BACKWARD_REQ			0x041D
#define     ICMS_IMONITOR_2_ISWITCH_GET_FAST_BACKWARD_ACK			0x041E

//iMonitor����iSwitch�˳���ǰvod�㲥
#define		ICMS_IMONITOR_2_ISWITCH_VOD_STOP_REQ			        0x041f
#define		ICMS_IMONITOR_2_ISWITCH_VOD_STOP_ACK			        0x0420

//�ļ����ݴ���ͷ
#define		ICMS_ISWITCH_2_IMONITOR_DATA_TRAN			            0x0421

//iMonitor����iSwitch��ʼ��ǰvod�㲥
//���ݷ��� : iMonitor ----> iSwitch 
#define		ICMS_IMONITOR_2_ISWITCH_VOD_START_REQ			        0x0423
#define		ICMS_IMONITOR_2_ISWITCH_VOD_START_ACK				    0x0424

//iMonitor����iSwitch��ͣ��ǰvod�㲥
//���ݷ��� : iMonitor ----> iSwitch
#define		ICMS_IMONITOR_2_ISWITCH_VOD_PAUSE_REQ			        0x0425
#define		ICMS_IMONITOR_2_ISWITCH_VOD_PAUSE_ACK			        0x0426

//iSwitch֪ͨiMonitor����״̬
#define		ICMS_ISWITCH_2_IMONITOR_VOD_NOTIFY_REQ			        0x0427
#define		ICMS_ISWITCH_2_IMONITOR_VOD_NOTIFY_ACK			        0x0428

//¼��Ǩ��
//���ݷ��� : iMonitor ----> iSwitch
#define   	ICMS_CLIENT_TRANSFER_RECFILE_REQ					    0x0429
#define 	ICMS_CLIENT_TRANSFER_RECFILE_ACK					    0x042a

//ͼƬǨ��
//���ݷ��� : iMonitor ----> iSwitch
#define		ICMS_CLIENT_TRANSFER_PICFILE_REQ					   0x042b
#define		ICMS_CLIENT_TRANSFER_PICFILE_ACK				       0x042c

//¼��Ǩ�ƽ���
//���ݷ��� : iSwitch ----> iMonitor
#define	ICMS_CLIENT_TRANSFER_PROGRESS_NOTIFY					   0x042d
#define	ICMS_CLIENT_TRANSFER_PROGRESS_NOTIFY_ACK				   0x042e

//�ļ�Ǩ�ƿ���
#define		ICMS_CLIENT_TRANSFER_CONTROL_REQ					   0x042f
#define		ICMS_CLIENT_TRANSFER_CONTROL_ACK					   0x0430

// SMQ:2013-12-16 Add
// ���ñ�ǩ��Ϣ
#define		ISMS_CLIENT_2_MC_SET_TAGINFO_REQ					0x0431
#define		ISMS_CLIENT_2_MC_SET_TAGINFO_ACK					0x0432

// SMQ:2013-12-16 Add
// ��ѯ��ǩ��Ϣ
#define		ISMS_CLIENT_2_MC_GET_TAGINFO_REQ					0x0433
#define		ISMS_CLIENT_2_MC_GET_TAGINFO_ACK					0x0434


//ɾ��Ǩ���ļ�
#define		ICMS_IMONITOR_2_ISWTCHI_DEL_TRANSFER_FILE_REQ					0x0d47
#define		ICMS_IMONITOR_2_ISWTCHI_DEL_TRANSFER_FILE_ACK					0x0d48

//monitor��MC��ȡ�ض��û���Ǩ����Ϣ
#define		ICMS_IMONITOR_2_MC_QUERY_TRANSFER_TASK_INFO_REQ					0x0d49
#define		ICMS_IMONITOR_2_MC_QUERY_TRANSFER_TASK_INFO_ACK					0x0d4a

//monitor��Ǩ�Ʒ�������ȡ�ض�����Ľ��Ⱥ�״̬��Ϣ
#define		ICMS_IMONITOR_2_ISWITCH_QUERY_TRANSFER_TASK_INFO_REQ				0x0d4b
#define		ICMS_IMONITOR_2_ISWITCH_QUERY_TRANSFER_TASK_INFO_ACK				0x0d4c

//Ǩ�Ʒ������ϱ�Ǩ������״̬��Ϣ
#define		ICMS_ISWITCH_2_MONITOR_TRANSFER_TASK_STATUS_CHANGE_NOTIFY_REQ		0x0d4d
#define		ICMS_ISWITCH_2_MONITOR_TRANSFER_TASK_STATUS_CHANGE_NOTIFY_ACK		0x0d4e

//�����ļ�����֪ͨ����
#define     ICMS_MONITOR_2_ISWITCH_UPLOAD_FILE_FINISH_NOTIFY_REQ                0x0d4f
#define     ICMS_ISWITCH_2_MONITOR_UPLOAD_FILE_FINISH_NOTIFY_ACK                0x0d50

/*************************** ��ѯ����������� ********************************/
//��ȡ�豸������Ѳ������	iMonitor	iMC	
#define		ICMS_IMONITOR_2_IMC_GET_GROUP_SURVEY_SCHEME_REQ			0x0501
#define		ICMS_IMONITOR_2_IMC_GET_GROUP_SURVEY_SCHEME_ACK			0x0502

//�����豸������Ѳ������	iMonitor	iMC	
#define		ICMS_IMONITOR_2_IMC_SET_GROUP_SURVEY_SCHEME_REQ			0x0503
#define		ICMS_IMONITOR_2_IMC_SET_GROUP_SURVEY_SCHEME_ACK			0x0504

//ɾ���豸������Ѳ���ñ�	iMonitor	iMC	
#define		ICMS_IMONITOR_2_IMC_DEL_GROUP_SURVEY_SCHEME_REQ			0x0505
#define		ICMS_IMONITOR_2_IMC_DEL_GROUP_SURVEY_SCHEME_ACK			0x0506

//��ȡ������Ѳ�ƻ���
//���ݷ��� : iMonitor ----> iMC
#define		ICMS_IMONITOR_2_IMC_GET_GROUP_SURVEY_PLAN_REQ		    0x0507
#define		ICMS_IMONITOR_2_IMC_GET_GROUP_SURVEY_PLAN_ACK			0x0508

//���ݷ��� : iMonitor ----> iMC
#define		ICMS_IMONITOR_2_IMC_SET_GROUP_SURVEY_PLAN_REQ			0x0509
#define		ICMS_IMONITOR_2_IMC_SET_GROUP_SURVEY_PLAN_ACK			0x050a

//������Ѳ�ƻ�����֪ͨ
//���ݷ��� : iMC ----> iMonitor    
#define	 ICMS_IMC_TO_IMONITOR_GROUP_SURVEY_PLAN_UPDATE			0x050b
//���ݷ��� : iMonitor ----> Imc
#define	 ICMS_IMC_TO_IMONITOR_GROUP_SURVEY_PLAN_UPDATE_ACK		0x050c


//�豸��������
#define	 ICMS_IMANAGER_TYPE_EQUIPMENT_BATCH_UPDATE			    0x050D
#define	 ICMS_IMANAGER_TYPE_EQUIPMENT_BATCH_UPDATE_ACK			0x050E

//�����������֪ͨ
#define	 ICMS_IMANAGER_TYPE_SERVERINFO_BATCH_UPDATE			    0x050F
#define	 ICMS_IMANAGER_TYPE_SERVERINFO_BATCH_UPDATE_ACK			0x0510

//���豸������������
#define	 ICMS_IMANAGER_TYPE_SUBADVSET_BATCH_UPDATE			    0x0511
#define	 ICMS_IMANAGER_TYPE_SUBADVSET_BATCH_UPDATE_ACK			0x0512

//��ȡ����������
#define	 ISOC_GET_SETVER_TYPE_AND_VERSION_REQ					0x5051
#define	 ISOC_GET_SETVER_TYPE_AND_VERSION_ACK                   0x5052


/*************************** ��̨����������� ********************************/
//��ȡ�豸Ԥ�õ�	iMonitor	iSwitch	
#define		ICMS_IMONITOR_2_IMC_GET_SUB_PREDEFINE_POS_REQ			0x0601
#define		ICMS_IMONITOR_2_IMC_GET_SUB_PREDEFINE_POS_ACK			0x0602

//�޸��豸Ԥ�õ�	iMonitor	iSwitch	
#define		ICMS_IMONITOR_2_IMC_SET_SUB_PREDEFINE_POS_REQ			0x0603
#define		ICMS_IMONITOR_2_IMC_SET_SUB_PREDEFINE_POS_ACK			0x0604

//��ȡ�豸Ѳ��Ԥ�õ�	iMonitor	iSwitch	
#define		ICMS_IMONITOR_2_IMC_GET_SUB_PREDEFINE_CRUISE_REQ		0x0605
#define		ICMS_IMONITOR_2_IMC_GET_SUB_PREDEFINE_CRUISE_ACK		0x0606

//�豸Ѳ��Ԥ�õ�	iMonitor	iSwitch	
#define		ICMS_IMONITOR_2_IMC_SET_SUB_PREDEFINE_CRUISE_REQ		0x0607
#define		ICMS_IMONITOR_2_IMC_SET_SUB_PREDEFINE_CRUISE_ACK		0x0608

//ptz�˸������ƶ�����	iMonitor	iSwitch	
#define		ICMS_IMONITOR_2_ISWITCH_PTZ_MOVE_REQ					0x0609
#define		ICMS_IMONITOR_2_ISWITCH_PTZ_MOVE_ACK					0x060a

//ptz��zoom����	iMonitor	iSwitch	
#define		ICMS_IMONITOR_2_ISWITCH_PTZ_ZOOM_REQ					0x060b
#define		ICMS_IMONITOR_2_ISWITCH_PTZ_ZOOM_ACK					0x060c

//ptz��focus����	iMonitor	iSwitch	
#define		ICMS_IMONITOR_2_ISWITCH_PTZ_FOCUS_REQ				   0x060d
#define		ICMS_IMONITOR_2_ISWITCH_PTZ_FOCUS_ACK				   0x060e

// 
//ptz�ĸ������ܿ��� 	iMonitor	iSwitch	
#define		ICMS_IMONITOR_2_ISWITCH_PTZ_AUXILIARY_REQ				0x060f
#define		ICMS_IMONITOR_2_ISWITCH_PTZ_AUXILIARY_ACK				0x0610

//iMonitor��iSwitch�����豸Ԥ�õ�
#define		ICMS_IMONITOR_2_ISWITCH_PREDEFINE_POSITION_REQ			0x0611
#define		ICMS_IMONITOR_2_ISWITCH_PREDEFINE_POSITION_ACK			0x0612

//iMonitor��iSwitch�豸Ѳ��
#define		ICMS_IMONITOR_2_ISWITCH_PREDEFINE_CRUISE_REQ			0x0613
#define		ICMS_IMONITOR_2_ISWITCH_PREDEFINE_CRUISE_ACK			0x0614

//iMonitor��iSwitch��ѯptz��ǰλ��
//���ݷ��� : iMonitor ----> iSwitch
#define		ICMS_IMONITOR_2_ISWITCH_GET_PTZ_POSITION_REQ			0x0615
#define		ICMS_IMONITOR_2_ISWITCH_GET_PTZ_POSITION_ACK			0x0616

//iMonitor��iSwitch��ʵʱ���ӿ�ͼ����ͨ��������PTZ
#define		ICMS_IMONITOR_2_ISWITCH_CTRL_PTZ_VIEW_REQ				0x0617
#define		ICMS_IMONITOR_2_ISWITCH_CTRL_PTZ_VIEW_ACK				0x0618

//iMonitor��iSwitch�ڻ�ȡPTZ��ǰλ��
#define		ICMS_IMONITOR_2_ISWITCH_GET_PTZ_CURPOS_REQ				0x0619
#define		ICMS_IMONITOR_2_ISWITCH_GET_PTZ_CURPOS_ACK				0x061a

//Ptz����λ���ƶ�
//���ݷ��� : iMonitor ----> iSwitch 
#define	 ICMS_IMONITOR_2_ISWITCH_PTZ_ABSSOLUTEMOVE_REQ				0x061b
#define	 ICMS_IMONITOR_2_ISWITCH_PTZ_ABSSOLUTEMOVE_ACK				0x061c

//Ptz��̨��ռ
//���ݷ��� : iMonitor ----> iSwitch 
#define  ICMS_IMONITOR_2_ISWITCH_PTZ_EXCLUSIVE_REQ                  0x061d
#define  ICMS_IMONITOR_2_ISWITCH_PTZ_EXCLUSIVE_ACK                  0x061e

//Ptz��Ȧ����
//���ݷ��� : iMonitor ----> iSwitch 
#define   ICMS_IMONITOR_2_ISWITCH_PTZ_APERTURE_REQ                  0x0620
#define   ICMS_IMONITOR_2_ISWITCH_PTZ_APERTURE_ACK                  0x0621

//���ݷ��� : iMonitor ----> iSwitch 
#define	 ICMS_IMONITOR_2_ISWITCH_IO_CONTROL_REQ						0x0622
#define	 ICMS_IMONITOR_2_ISWITCH_IO_CONTROL_ACK						0x0623

/*************************** ��־��ѯ���������� ********************************/
//��ȡ��־��	iMonitor	iMC	
#define		ICMS_IMONITOR_2_IMC_GET_LOG_REQ							0x0701
#define		ICMS_IMONITOR_2_IMC_GET_LOG_ACK							0x0702

//ȡ������ɫ	iMonitor	iMC	
#define		ICMS_IMONITOR_2_IMC_GET_WARNING_COLOR_REQ				0x0801
#define		ICMS_IMONITOR_2_IMC_GET_WARNING_COLOR_ACK				0x0802

//ȡϵͳʹ���ʵȲ���	iMonitor	iMC	
#define		ICMS_IMONITOR_2_IMC_GET_SYSTEM_USEAGE_REQ				0x0803
#define		ICMS_IMONITOR_2_IMC_GET_SYSTEM_USEAGE_ACK				0x0804

//ȡ���Ͷ�����Ϣ����	iMonitor	iMC	
#define		ICMS_IMONITOR_2_IMC_GET_TYPE_INFO_REQ					0x0805
#define		ICMS_IMONITOR_2_IMC_GET_TYPE_INFO_ACK					0x0806

//��ȡ����Monitor��ַ
//���ݷ��� : iMonitor ----> iMC
#define		ICMS_IMONITOR_2_IMC_GET_MONITORADDR_REQ					0x0807
#define		ICMS_IMONITOR_2_IMC_GET_MONITORADDR_ACK					0x0808

//��ȡ�û�����ı����¼�����
//���ݷ��� : iMonitor ----> iMC
#define		ICMS_IMONITOR_2_IMC_GET_USER_ALARMCODE_REQ		    	0x0809
#define		ICMS_IMONITOR_2_IMC_GET_USER_ALARMCODE_ACK				0x080a

//��ȡ���������ñ�ǩ��Ϣ
//���ݷ��� : iMonitor ----> iMC
#define		ICMS_IMONITOR_2_IMC_GET_ALARM_TAG_REQ					0x080b
#define		ICMS_IMONITOR_2_IMC_GET_ALARM_TAG_ACK					0x080c

//��ȡ����������ע����Ϣ
//���ݷ��� : iMonitor ----> iMC
#define		ICMS_IMONITOR_2_IMC_GET_ALARM_DESC_REQ					0x080d
#define		ICMS_IMONITOR_2_IMC_GET_ALARM_DESC_ACK					0x080e

//��ӱ��������ñ�ǩ��Ϣ
//���ݷ��� : iMonitor ----> iMC
#define		ICMS_IMONITOR_2_IMC_ADD_ALARM_TAG_REQ					0x080f
#define		ICMS_IMONITOR_2_IMC_ADD_ALARM_TAG_ACK					0x0810

#define ISMS_GET_SYSTEM_INFO_REQ									0x801a
#define ISMS_GET_SYSTEM_INFO_ACK									0x801b

#define ISMS_GET_SERVER_REQ											0x8010
#define ISMS_GET_SERVER_ACK											0x8011


/*************************** ��½��֤������� ********************************/
//Monitor���ߵǼ�	iMonitor	ISwitch, iMap, iAlarm	
#define		ICMS_IMONITOR_2_LOGIN_IN_REQ							0x0a01
#define		ICMS_IMONITOR_2_LOGIN_IN_ACK							0x0a02

//Monitor����ע��	iMonitor	ISwitch, iMap, iAlarm	
#define		ICMS_IMONITOR_2_LOGIN_OUT_REQ							0x0a03
#define		ICMS_IMONITOR_2_LOGIN_OUT_ACK							0x0a04

//���������	iMonitor	ISwitch, iMap, iAlarm	
#define		ICMS_IMONITOR_2_HEART_BEAT_REQ							0x0a05
#define		ICMS_IMONITOR_2_HEART_BEAT_ACK							0x0a06

//iSwitch,iAlarm,iMap,iMonitor,iManager��������Ĺ�������-> MC
#define		ICMS_TYPE_TOMC_LOGIN_REQ								0x0a07
#define		ICMS_TYPE_TOMC_LOGIN_ACK								0x0a08

//iSwitch,iAlarm,iMap,iMonitor,iManager��������Ĺ�������-> MC
#define		ICMS_TYPE_TOMC_LOGOUT_REQ								0x0a09
#define		ICMS_TYPE_TOMC_LOGOUT_ACK								0x0a0a

//�ϼ����������¼���������֤	�ϼ�iMC/iAlarm	iMC/iAlarm	
#define		ICMS_TYPE_CONNECT_SUBSERVER_REQ							0x0a0b
#define		ICMS_TYPE_CONNECT_SUBSERVER_ACK							0x0a0c

//�¼����������������	iMC/iAlarm	�ϼ�iMC/iAlarm	
#define		ICMS_TYPE_SUBSERVER_HEART_BEAT_REQ						0x0a0d
#define		ICMS_TYPE_SUBSERVER_HEART_BEAT_ACK						0x0a0e

//�¼��������˳�֪ͨ	iMC/iAlarm	�ϼ�iMC/iAlarm	
#define		ICMS_TYPE_SUBSERVER_LOGOUT_REQ							0x0a0f
#define		ICMS_TYPE_SUBSERVER_LOGOUT_ACK							0x0a10

//�ӷ�����������������֤	��iMC/iAlarm	��iMC/iAlarm	
#define		ICMS_TYPE_CONNECT_TOMAINSERV_REQ						0x0a11
#define		ICMS_TYPE_CONNECT_TOMAINSERV_ACK						0x0a12

//���ӷ��������������	��iMC/iAlarm	��iMC/iAlarm	
#define		ICMS_TYPE_SERVER_HEART_BEAT_REQ							0x0a13
#define		ICMS_TYPE_SERVER_HEART_BEAT_ACK							0x0a14

//�¼����������ϼ�������ע��
#define	ICMS_TYPE_CONNECT_SUPERSERVER_REQ							0x0a15
#define	ICMS_TYPE_CONNECT_SUPERSERVER_ACK							0x0a16

//������������������
#define ICMS_TYPE_PINGALIVE_REQ										0x0a17
#define ICMS_TYPE_PINGALIVE_ACK										0x0a18

//ISWITCH��¼���������ӿ�����
#define ICMS_ISWITCH_2_UID_LOGIN_REQ                                0x0a19
#define	ICMS_ISWITCH_2_UID_LOGIN_ACK							    0x0a1a



/*************************** ���ù������� ********************************/
//¼��ƻ�����֪ͨ	iManager	iMC	
#define		ICMS_TYPE_IMANTYPE_RECSCHEDULE_UPDATE					0x0b01
#define		ICMS_TYPE_IMANTYPE_RECSCHEDULE_UPDATE_ACK				0x0b02

//¼�����ؼƻ�����֪ͨ	iManager	iMC	
#define		ICMS_TYPE_IMANTYPE_RECUPLOADSCHEDULE_UPDATE				0x0b03
#define		ICMS_TYPE_IMANTYPE_RECUPLOADSCHEDULE_UPDATE_ACK			0x0b04

//�����ƻ�����֪ͨ	iManager	iMC	
#define		ICMS_TYPE_IMANTYPE_DEFENCESCHEDULE_UPDATE				0x0b05
#define		ICMS_TYPE_IMANTYPE_DEFENCESCHEDULE_UPDATE_ACK			0x0b06

//�Զ�Ѳ�����֪ͨ	iManager	iMC	
#define		ICMS_TYPE_IMANTYPE_AUTOPATROLSCHEDULE_UPDATE			0x0b07
#define		ICMS_TYPE_IMANTYPE_AUTOPATROLSCHEDULE_UPDATE_ACK		0x0b08

//�ֶ�Ѳ�쿪ʼ֪ͨ	iManager	iMC	
#define		ICMS_TYPE_IMANTYPE_MANUALPATROLSCHEDULE_START			0x0b09
#define		ICMS_TYPE_IMANTYPE_MANUALPATROLSCHEDULE_START_ACK		0x0b0a
#define		ICMS_TYPE_IMANTYPE_MANUALPATROLSCHEDULE_RESULT_ACK		0x0b0b

//�ֶ�Ѳ��ȡ��	iManager	iMC	
#define		ICMS_TYPE_IMANTYPE_AUTOPATROLSCHEDULE_CANCEL			0x0b0f
#define		ICMS_TYPE_IMANTYPE_AUTOPATROLSCHEDULE_CANCEL_ACK		0x0b10

//�������ø���֪ͨ	iManager	iMC	
#define		ICMS_TYPE_IMANTYPE_ALARM_UPDATE							0x0b11
#define		ICMS_TYPE_IMANTYPE_ALARM_UPDATE_ACK						0x0b12

//�豸����֪ͨ	iManager		
#define		ICMS_TYPE_IMANTYPE_EQUIPMENT_CONNECT					0x0b13
#define		ICMS_TYPE_IMANTYPE_EQUIPMENT_CONNECT_ACK				0x0b14

//�豸����֪ͨ	iManager	iMC	
#define		ICMS_TYPE_IMANTYPE_EQUIPMENT_UPDATE						0x0b15
#define		ICMS_TYPE_IMANTYPE_EQUIPMENT_UPDATE_ACK					0x0b16

//��֯�������	iManager	iMC	
#define		ICMS_TYPE_IMANTYPE_ORGANIZE_UPDATE  					0x0b17
#define		ICMS_TYPE_IMANTYPE_ORGANIZE_UPDATE_ACK					0x0b18

//�û�����֪ͨ	iManager	iMC	
#define		ICMS_TYPE_IMANTYPE_USER_UPDATE							0x0b19
#define		ICMS_TYPE_IMANTYPE_USER_UPDATE_ACK						0x0b1a

//��ͼ����֪ͨ	iManager	iMC	
#define		ICMS_TYPE_IMANTYPE_MAP_UPDATE							0x0b1b
#define		ICMS_TYPE_IMANTYPE_MAP_UPDATE_ACK						0x0b1c

//�������ø���֪ͨ	iManager	iMC	
#define		ICMS_TYPE_IMANTYPE_SERVER_UPDATE						0x0b1d
#define		ICMS_TYPE_IMANTYPE_SERVER_UPDATE_ACK					0x0b1e

//ϵͳ���ø���	iManager	iMC	
#define		ICMS_TYPE_IMANTYPE_SYSTEM_UPDATE						0x0b21
#define		ICMS_TYPE_IMANTYPE_SYSTEM_UPDATE_ACK					0x0b22

//ͬ������֪ͨ//��Ҫ������������
#define		ICMS_TYPE_IMANTYPE_SYNALLDATA_UPDATE				    0x0b1f
#define		ICMS_TYPE_IMANTYPE_SYNALLDATA_UPDATE_ACK				0x0b20

//NVR/�¼�ICMS����֪ͨ
#define  ICMS_TYPE_IMANTYPE_NVRORSERV_UPDATE                        0x0b23
#define  ICMS_TYPE_IMANTYPE_NVRORSERV_UPDATE_ACK                    0x0b24

//�ƻ����ñ��֪ͨ
#define    ICMS_TYPE_IMANTYPE_PLANSET_UPDATE                        0x0b25
#define    ICMS_TYPE_IMANTYPE_PLANSET_UPDATE_ACK                    0x0b26

//���豸�߼��������ø���֪ͨ
#define    ICMS_TYPE_IMANTYPE_SUBEQU_ADVSET_UPDATE  	            0x0b27
#define    ICMS_TYPE_IMANTYPE_SUBEQU_ADVSET_UPDATE_ACK  	        0x0b28

//��ȡ�߼���������
#define     ICMS_TYPE_IMANTYPE_SUBEQU_GET_ADVSET_REQ  	            0x0b29
#define     ICMS_TYPE_IMANTYPE_SUBEQU_GET_ADVSET_ACK  	            0x0b2a

//ǰ���豸��������
//���ݷ��� : iManage ---->iMC  iMC  ---->iSwitch
#define	    ICMS_TYPE_CTRLTYPE_DEVICE_POWER_NOTIFY		            0x0b2b
#define	    ICMS_TYPE_CTRLTYPE_DEVICE_POWER_NOTIFY_ACK		        0x0b2c

//�����������ø���֪ͨ
//���ݷ��� : iManage ---->iMC     iMC  ---->iAlarm
#define		ICMS_TYPE_IMANTYPE_AUDIOSET_UPDATE  	               0x0b2d
#define		ICMS_TYPE_IMANTYPE_AUDIOSET_UPDATE_ACK  			   0x0b2e

//�����¼��������֪ͨ
//���ݷ��� : iManage ---->iMC          iMC  ---->iAlarm  iMC  ---->iMonitor
#define		ICMS_TYPE_IMANTYPE_AEVENTSET_UPDATE  	               0x0b2f
#define		ICMS_TYPE_IMANTYPE_AEVENTSET_UPDATE_ACK  			   0x0b30

//�ļ��洢�ֶ����ø���֪ͨ
//���ݷ��� : iManage ---->iMC  iMC  ---->iSwitch
#define		ICMS_TYPE_IMANTYPE_FILECUT_UPDATE  						0x0b31
#define		ICMS_TYPE_IMANTYPE_FILECUT_UPDATE_ACK  					0x0b32

//����������ø���֪ͨ
//���ݷ��� : iManage ---->iMC  iMC  ---->iSwitch
#define ICMS_TYPE_IMANTYPE_INOUTSET_UPDATE  						0x0b33
#define ICMS_TYPE_IMANTYPE_INOUTSET_UPDATE_ACK  					0x0b34

//�洢ͨ���������֪ͨ
//���ݷ��� : iManage---->iMC  iMC -----> iManage
#define ICMS_TYPE_IMANTYPE_STORAGE_CHANNELS_UPDATE					0x0b35
#define ICMS_TYPE_IMANTYPE_STORAGE_CHANNELS_UPDATE_ACK				0x0b36

//�洢��Ԫ����֪ͨ
//���ݷ��� : iManage---->iMC  iMC -----> iManage
#define ICMS_TYPE_IMANTYPE_STORAGE_UNIT_UPDATE						0x0b37
#define ICMS_TYPE_IMANTYPE_STORAGE_UNIT_UPDATE_ACK					0x0b38

//�洢���̸���֪ͨ
//���ݷ��� : iManage---->iMC  iMC -----> iManage
#define ICMS_TYPE_IMANTYPE_STORAGE_UPDATE							0x0b39
#define ICMS_TYPE_IMANTYPE_STORAGE_UPDATE_ACK						0x0b3A

//������Ⱥ����
#define ICMS_TYPE_IMANTYPE_GROUP_UPDATE								0x0b3b
#define ICMS_TYPE_IMANTYPE_GROUP_UPDATE_ACK							0x0b3c

//Զ����Ӽ�Ⱥ��Ϣ
#define ICMS_TYPE_IMANTYPE_ADDGROUP_REQ								0x0b3d
#define ICMS_TYPE_IMANTYPE_ADDGROUP_ACK								0x0b3e

//�洢�豸������������
//���ݷ��� : iManage---->iMC  iMC -----> iManage
#define ICMS_TYPE_IMANTYPE_STORAGE_REQ								0x0b3f
#define ICMS_TYPE_IMANTYPE_STORAGE_ACK								0x0b42

//ͼ���������ģʽ��������
#define ICMS_TYPE_IMANTYPE_IMAGEMODE_REQ							0x0b44
#define ICMS_TYPE_IMANTYPE_IMAGEMODE_ACK							0x0b45

//����ͼ�����ģʽ����
#define ICMS_TYPE_IMANTYPE_IMAGEMODE_SET_REQ						0x0b46
#define ICMS_TYPE_IMANTYPE_IMAGEMODE_SET_ACK						0x0b47

// ȡ֤��Ԫ�����������
//���ݷ��� : iManage---->iMC--->iSwitch  iSwitch -----> iMC -----> iManage
#define ICMS_TYPE_IMANTYPE_STORAGE_EVIDENCEUNIT_UPDATE				0x0b43
#define ICMS_TYPE_IMANTYPE_STORAGE_EVIDENCEUNIT_UPDATE_ACK			0x0b44

#define ICMS_TYPE_IMANTYPE_RELATION_EVIDENCEUNIT_UPDAT				0x0b45
#define ICMS_TYPE_IMANTYPE_RELATION_EVIDENCEUNIT_UPDATE_ACK			0x0b46

#define ICMS_TYPE_TRANTASK_UPDATE_REQ								0x0b47
#define ICMS_TYPE_TRANTASK_UPDATE_ACK								0x0b48

#define  ICMS_IMONITOR_2_MC_QUERYROUTE_INFO_REQ						0x1301
#define  ICMS_IMONITOR_2_MC_QUERYROUTE_INFO_ACK						0x1302

#define  ICMS_IMONITOR_2_MC_GETVODFILE_INFO_REQ						0x1303
#define  ICMS_IMONITOR_2_MC_GETVODFILE_INFO_ACK						0x1304

#define  ICMS_TYPE_IMANTYPE_GETDISKFREESPACE_REQ                    0x3420
#define  ICMS_TYPE_IMANTYPE_GETDISKFREESPACE_ACK                    0x3421

/*************************** �������ĵ���������� ********************************/
#define     ICMS_TO_IMC_GET_RECSWITCH_ADDR_REQ						0x0dd5			//MC����¼���ַ
#define     ICMS_TO_IMC_GET_RECSWITCH_ADDR_ACK						0x0dd6			//MC����¼���ַ

//¼���������	iMC	ISwitch	
#define		ICMS_TYPE_CTRLTYPE_IMC_RECORD_REQ						0x0c01
#define		ICMS_TYPE_CTRLTYPE_IMC_RECORD_ACK						0x0c02

//IPC&DVSѲ���������	iMC	ISwitch	
#define		ICMS_TYPE_CTRLTYPE_IMC_DETECT_REQ						0x0c03
#define		ICMS_TYPE_CTRLTYPE_IMC_DETECT_ACK						0x0c04

//IPC&DVSѲ��״̬֪ͨ	iSwitch	iMC	
#define		ICMS_TYPE_CTRLTYPE_ISWITCH_DETECTNOTIFY					0x0c05
#define		ICMS_TYPE_CTRLTYPE_ISWITCH_DETECTNOTIFY_ACK				0x0c06

//�豸Ѳ����֪ͨ	iSwitch	iMC	
#define		ICMS_TYPE_CTRLTYPE_SELFTEST_REQ							0x0c07
#define		ICMS_TYPE_CTRLTYPE_SELFTEST_ACK							0x0c08

//IPC&DVSѲ�����	iSwitch	iMC	
#define		ICMS_TYPE_CTRLTYPE_ISWITCH_DETECTFIN					0x0c09
#define		ICMS_TYPE_CTRLTYPE_ISWITCH_DETECTFIN_ACK				0x0c0a

//ϵͳѲ������	iMC	iSwitch��iMatrix��iMap��iAlarm��iManager��iMonitor	
#define		ICMS_TYPE_CTRLTYPE_IMC_ALIVENOTIFY_REQ					0x0c0b
#define		ICMS_TYPE_CTRLTYPE_IMC_ALIVENOTIFY_ACK					0x0c0c

//�����������	iMC	iAlarm	
#define		ICMS_TYPE_CTRLTYPE_IMC_SETDEFENCE_REQ					0x0c0d
#define		ICMS_TYPE_CTRLTYPE_IMC_SETDEFENCE_ACK					0x0c0e

//�����������	iMC	iAlarm	
#define		ICMS_TYPE_CTRLTYPE_IMC_CANCELDEFENCE_REQ				0x0c0f
#define		ICMS_TYPE_CTRLTYPE_IMC_CANCELDEFENCE_ACK				0x0c10

//���ݸ���֪ͨ	iMC	�ϼ�iMC	
#define		ICMS_TYPE_CTRLTYPE_IMC_UPDATE_REQ						0x0c11
#define		ICMS_TYPE_CTRLTYPE_IMC_UPDATE_ACK						0x0c12

//����ͬ������	�ϼ�iMC	iMC	
#define		ICMS_TYPE_CTRLTYPE_IMC_DATASYN_REQ						0x0c13
#define		ICMS_TYPE_CTRLTYPE_IMC_DATASYN_ACK						0x0c14

//ͬ�����ݴ���	iMC	�ϼ�iMC	
#define		ICMS_TYPE_CTRLTYPE_IMC_DATASYNTRAN						0x0c15
#define		ICMS_TYPE_CTRLTYPE_IMC_DATASYNTRAN_ACK					0x0c16

//����ͬ�����	�ϼ�iMC	iMC	
#define		ICMS_TYPE_CTRLTYPE_IMC_DATASYNEND						0x0c17
#define		ICMS_TYPE_CTRLTYPE_IMC_DATASYNEND_ACK					0x0c18

//���󱨾���������ַ	iMonitor	iMC	
#define		ICMS_TO_IMC_GET_ALARM_ADDR_REQ							0x0c19
#define		ICMS_TO_IMC_GET_ALARM_ADDR_ACK							0x0c1a

//������ӵ�ͼ��������ַ	iMonitor	iMC	
#define		ICMS_IMONITOR_2_IMC_GET_EMAP_ADDR_REQ					0x0c1b
#define		ICMS_IMONITOR_2_IMC_GET_EMAP_ADDR_ACK					0x0c1c

//����ý�彻�����Ʒ�������ַ	iMonitor	iMC	
#define		ICMS_IMONITOR_2_IMC_GET_ISWTICH_ADDR_REQ				0x0c1d
#define		ICMS_IMONITOR_2_IMC_GET_ISWTICH_ADDR_ACK				0x0c1e

//�������ݿ��ַ��Ϣ
//���ݷ���: iAlarm,iMap,iSwitch ----> iMC
#define		ICMS_TYPE_CTRLTYPE_GETDBADDR_REQ						0x0c1f
#define		ICMS_TYPE_CTRLTYPE_GETDBADDR_ACK						0x0c20

//����vod�㲥ý�彻�����Ʒ�������ַ	iMonitor	iMC	
#define		ICMS_IMONITOR_2_IMC_GET_VODISWTICH_ADDR_REQ				0x0c21
#define		ICMS_IMONITOR_2_IMC_GET_VODISWTICH_ADDR_ACK				0x0c22

//ISwitch֪ͨMCԤ�õ����	ISwitch	iMC	
#define		ICMS_TYPE_CTRLTYPE_PRESET_UPDATE_REQ					0x0c23
#define		ICMS_TYPE_CTRLTYPE_PRESET_UPDATE_ACK					0x0c24

//ISwitch֪ͨMCѲ������	ISwitch	iMC	
#define		ICMS_TYPE_CTRLTYPE_CRIOSE_UPDATE_REQ					0x0c25
#define		ICMS_TYPE_CTRLTYPE_CRIOSE_UPDATE_ACK					0x0c26

//������Ѳ��������֪ͨ	iMC	iMonitor	
#define		ICMS_IMC_2_IMONITOR_GROUP_SURVEY_SCHEME_UPDATE			0x0c29
#define		ICMS_IMC_2_IMONITOR_GROUP_SURVEY_SCHEME_UPDATE_ACK		0x0c2a

//����iSwitch����״̬	iMC	ISwitch	
#define		ICMS_IMC_ISWITCH_DEVOPEN_STATUS_REQ						0x0c2b
#define		ICMS_IMC_ISWITCH_DEVOPEN_STATUS_ACK						0x0c2c

//��ѯ������־����¼��	iMonitor	iMC	
#define		ICMS_TYPE_CTRLTYPE_QUERY_ALARMREC_REQ					0x0c2d
#define		ICMS_TYPE_CTRLTYPE_QUERY_ALARMREC_ACK					0x0c2e

//iMC���¼�����������ͬ��
#define		ICMS_TYPE_CTRLTYPE_UPSERV_DATASYN						0x0c2f
#define		ICMS_TYPE_CTRLTYPE_UPSERV_DATASYN_ACK					0x0c30

//�豸�����������
#define	     ICMS_TYPE_CTRLTYPE_DEVRECORD_UP		                0x0c31
#define	     ICMS_TYPE_CTRLTYPE_DEVRECORD_UP_ACK		            0x0c32


//���������豸��iSwitch��ַ
//���ݷ���: iMonitor/iAlarm/iManage ----> iMC
#define		ICMS_TO_IMC_GET_MULTISWTICH_ADDR_REQ					0x0c33
#define		ICMS_TO_IMC_GET_MULTISWTICH_ADDR_ACK					0x0c34

//iMonitor��iMC����Ǩ�Ʒ�������ַ
//���ݷ���: iMonitor ----> iMC
#define		ICMS_TO_IMC_GET_TRANSFER_ADDR_REQ			            0x0c35
#define		ICMS_TO_IMC_GET_TRANSFER_ADDR__ACK			            0x0c36

//��ȡǨ���ļ���Ϣ
#define		ICMS_TYPE_CTRLTYPE_TRANSFILEINFO_REQ					0x0e07
#define		ICMS_TYPE_CTRLTYPE_TRANSFILEINFO_ACK					0x0e08

//���浱ǰ¼������״̬
//���ݷ���: iSwitch ----> iMC
#define	    ICMS_TYPE_CTRLTYPE_RECTASK_STATUS_NOTIFY		        0x0c37
#define	    ICMS_TYPE_CTRLTYPE_RECTASK_STATUS_NOTIFY_ACK			0x0c38

//��ȡiSwitch��ַ
//���ݷ���: iMonitor ----> iMC
#define	    ICMS_TYPE_CTRLTYPE_GET_ISWITCH_ADDR_REQ		            0x0c39
#define	    ICMS_TYPE_CTRLTYPE_GET_ISWITCH_ADDR_ACK			        0x0c3a

#define		ICMS_ISWITCH_IMC_GET_ISWTICH_ADDR_REQ					0x0c41
#define		ICMS_ISWITCH_IMC_GET_ISWTICH_ADDR_ACK					0x0c42

#define		ICMS_TO_IMC_GET_DISKSTORAGE_REQ							0x0c43
#define		ICMS_TO_IMC_GET_DISKSTORAGE_ACK							0x0c44

//�ͻ�����MC�����豸��Ƶ������ǽ����
#define		ICMS_TO_IMC_VIDEO_TO_MATRIX_REQ							0x0c45
#define		ICMS_TO_IMC_VIDEO_TO_MATRIX_ACK							0x0c46

#define		ICMS_TO_IMC_GET_SYSTEMRUNSTATUS_REQ						0x0c47			
#define		ICMS_TO_IMC_GET_SYSTEMRUNSTATUS_ACK						0x0c48

#define	ICMS_ISWITCH_IMC_NOTIFY_RECORDRUN_REQ					    0x0c49
#define		ICMS_ISWITCH_IMC_NOTIFY_RECORDRUN_ACK					0x0c4a

#define    ICMS_TYPE_IMATYPE_SERVER_CHECK_REQ						0x0c4b
#define    ICMS_TYPE_IMATYPE_SERVER_CHECK_ACK						0x0c4c

#define    ICMS_TYPE_IMC_GET_TRNFILENOTE_REQ						0x0c4d
#define    ICMS_TYPE_IMC_GET_TRANFILENOTE_ACK						0x0c4e

#define    ICMS_IMONITOR_2_ISWITCH_AVAILABLE_TALKBACK_ENCODEPRAMS_REQ  0x0c4f
#define    ICMS_IMONITOR_2_ISWITCH_AVAILABLE_TALKBACK_ENCODEPRAMS_ACK  0x0c50

//����GPS��������ַ
#define		ICMS_IMONITOR_2_IMC_GET_GPSSVR_ADDR_REQ                  0x0c51
#define		ICMS_IMONITOR_2_IMC_GET_GPSSVR_ADDR_ACK                  0x0c52

/*************************** ��������������� ********************************/
//̽ͷ��ͨ����������	ISwitch	 iAlarm	
#define		ICMS_TYPE_CTRLTYPE_ALARMEVENT_NOTIFY					0x0d01
#define		ICMS_TYPE_CTRLTYPE_ALARMEVENT_NOTIFY_ACK				0x0d02

//ϵͳ��������	iSwitch, iMap, iMC	iAlarm	
#define		ICMS_TYPE_CTRLTYPE_SYSALARM_NOTIFY						0x0d03
#define		ICMS_TYPE_CTRLTYPE_SYSALARM_NOTIFY_ACK					0x0d04

//�ֶ���������	iMonitor	 iAlarm	
#define		ICMS_TYPE_CTRLTYPE_MANUALALARM_NOTIFY					0x0d05
#define		ICMS_TYPE_CTRLTYPE_MANUALALARM_NOTIF_ACK				0x0d06

//����¼��	iAlarm	iSwitch	
#define		ICMS_TYPE_CTRLTYPE_ALARMACTION_STARTRECORD				0x0d07
#define		ICMS_TYPE_CTRLTYPE_ALARMACTION_STARTRECORD_ACK			0x0d08

//��Ƶץ֡	iAlarm	iSwitch	
#define		ICMS_TYPE_CTRLTYPE_ALARMACTION_VIDEOSNAP				0x0d09
#define		ICMS_TYPE_CTRLTYPE_ALARMACTION_VIDEOSNAP_ACK			0x0d00a

//PTZ����	iAlarm	iSwitch
#define		ICMS_TYPE_CTRLTYPE_ALARMACTION_PTZ						0x0d0b
#define		ICMS_TYPE_CTRLTYPE_ALARMACTION_PTZ_ACK					0x0d0c

//�������	IAlarm/iMonitor	ISwitch/iAlarm	
#define		ICMS_TYPE_CTRLTYPE_ALARMACTION_OUTPUT					0x0d0d
#define		ICMS_TYPE_CTRLTYPE_ALARMACTION_OUTPUT_ACK				0x0d0e

//����ǽ����	iAlarm	imatrix	
#define		ICMS_TYPE_CTRLTYPE_ALARMACTION_TVWALL					0x0d0f
#define		ICMS_TYPE_CTRLTYPE_ALARMACTION_TVWALL_ACK				0x0d10

//����֪ͨ	iAlarm	���Ż�	
#define		ICMS_TYPE_CTRLTYPE_ALARMACTION_SMS						0x0d11
#define		ICMS_TYPE_CTRLTYPE_ALARMACTION_SMS_ACK					0x0d12

//�ʼ�֪ͨ	iAlarm	�ʼ�������	
#define		ICMS_TYPE_CTRLTYPE_ALARMACTION_EMAIL					0x0d13
#define		ICMS_TYPE_CTRLTYPE_ALARMACTION_EMAIL_ACK				0x0d14

//������ͼ, ��ƵԤ��, ������ʾ	iAlarm	iMonitor	
#define		ICMS_TYPE_CTRLTYPE_ALARM_DESCRIPTION					0x0d15
#define		ICMS_TYPE_CTRLTYPE_ALARM_DESCRIPTION_ACK				0x0d16

//ֹͣ¼��	iAlarm	iSwitch	
#define		ICMS_TYPE_CTRLTYPE_ALARMACTION_STOPRECORD				0x0d17
#define		ICMS_TYPE_CTRLTYPE_ALARMACTION_STOPRECORD_ACK			0x0d18

//�ָ���̨	iAlarm	iSwitch	
#define		ICMS_TYPE_CTRLTYPE_ALARMACTION_RESUMEPTZ				0x0d19
#define		ICMS_TYPE_CTRLTYPE_ALARMACTION_RESUMEPTZ_ACK			0x0d1a

//��������ָ�	iAlarm	iSwitch
#define		ICMS_TYPE_CTRLTYPE_ALARMACTION_OUTPUTRESUME				0x0d1b
#define		ICMS_TYPE_CTRLTYPE_ALARMACTION_OUTPUTRESUME_ACK			0x0d1c

//����֪ͨ	IAlarm/iMonitor	ISwitch/iAlarm	
#define		ICMS_TYPE_CTRLTYPE_ALARM_SETDEFENCE						0x0d1d
#define		ICMS_TYPE_CTRLTYPE_ALARM_SETDEFENCE_ACK					0x0d1e

//����֪ͨ	IAlarm/iMonitor	ISwitch/iAlarm	
#define		ICMS_TYPE_CTRLTYPE_ALARM_CANCELDEFENCE					0x0d1f
#define		ICMS_TYPE_CTRLTYPE_ALARM_CANCELDEFENCE_ACK				0x0d20

//Ԥ¼֪ͨ	iAlarm	iSwitch	
#define		ICMS_TYPE_CTRLTYPE_PRERECORD							0x0d21
#define		ICMS_TYPE_CTRLTYPE_PRERECORD_ACK						0x0d22

//����������֪ͨ	iAlarm	IMonitor/�ϼ�iAlarm	
#define		ICMS_TYPE_CTRLTYPE_ALARMDEAL_RESULT						0x0d23
#define		ICMS_TYPE_CTRLTYPE_ALARMDEAL_RESULT_ACK					0x0d24

//�ֶ�����ָ�������û�	iAlarm	iMonitor	
#define		ICMS_TYPE_CTRLTYPE_ALARMMANNUL_NOTIFY					0x0d25
#define		ICMS_TYPE_CTRLTYPE_ALARMMANNUL_NOTIFY_ACK				0x0d26

//Monitor��������״̬�ϱ�	iMonitor	IAlarm/�ϼ�iAlarm	
#define		ICMS_TYPE_CTRLTYPE_MONITOR_ALARMSTATUS					0x0d27
#define		ICMS_TYPE_CTRLTYPE_MONITOR_ALARMSTATUS_ACK				0x0d28

//Monitor�����������ϱ�	iMonitor	iAlarm	
#define		ICMS_TYPE_CTRLTYPE_MONITOR_RESULTUP						0x0d29
#define		ICMS_TYPE_CTRLTYPE_MONITOR_RESULTUP_ACK					0x0d2a

//Monitorȡ������	iMonitor	iAlarm	
#define		ICMS_TYPE_CTRLTYPE_MONITOR_CANCELALARM					0x0d2b
#define		ICMS_TYPE_CTRLTYPE_MONITOR_CANCELALARM_ACK				0x0d2c

//�����¼���Ϣ��ѯ	�ϼ�iAlarm	iAlarm	
#define		ICMS_TYPE_CTRLTYPE_ALARMINFO_QUERY						0x0d2d
#define		ICMS_TYPE_CTRLTYPE_ALARMINFO_QUERY_ACK					0x0d2e

//ͨ��������Ϣ��ѯ	�ϼ�iAlarm	iAlarm	
#define		ICMS_TYPE_CTRLTYPE_ALARMRELATION_QUERY					0x0d2f
#define		ICMS_TYPE_CTRLTYPE_ALARMRELATION_QUERY_ACK				0x0d30

//Iswitch���������	iSwitch	iAlarm	
#define		ICMS_ISWITCH_HEART_BEAT_REQ								0x0d31
#define		ICMS_ISWITCH_HEART_BEAT_ACK								0x0d32

//���ӷ���������ͬ��	��iAlarm	��iAlarm
#define		ICMS_TYPE_CTRLTYPE_ALARM_DATASYN						0x0d33
#define		ICMS_TYPE_CTRLTYPE_ALARM_DATASYN_ACK					0x0d34

//�رն��Ԥ¼	iAlarm	iSwitch0	
#define		ICMS_TYPE_CTRLTYPE_ISWITCH_STOP_PREREC_REQ				0x0d35
#define		ICMS_TYPE_CTRLTYPE_ISWITCH_STOP_PREREC_ACK				0x0d36

//�ر�ָ�����豸��Ԥ¼	iAlarm	iSwitch	
#define		ICMS_TYPE_CTRLTYPE_ISWITCH_STOP_SOMEPRE_REQ				0x0d37
#define		ICMS_TYPE_CTRLTYPE_ISWITCH_STOP_SOMEPRE_ACK				0x0d38

//���ݷ��� : iAlarm ----> iSwitch ��ѯ�����豸��״̬
#define		ICMS_TYPE_CTRLTYPE_ALARMEQU_STATUS_REQ					0x0d39
#define		ICMS_TYPE_CTRLTYPE_ALARMEQU_STATUS_ACK					0x0d3a

//���ݷ��� : iAlarm ----> iSwitch  ���䱨���豸
#define		ICMS_TYPE_CTRLTYPE_ALLOT_ALARMEQU_REQ					0x0d3b
#define		ICMS_TYPE_CTRLTYPE_ALLOT_ALARMEQU_ACK					0x0d3c

//���ݷ��� : iAlarm ----> iSwitch Alarm��iSwitch��ȡԤ¼��Ϣ
#define		ICMS_TYPE_CTRLTYPE_PREREC_STATUS_REQ					0x0d3d
#define		ICMS_TYPE_CTRLTYPE_PREREC_STATUS_ACK					0x0d3e

//��ȡδ������
#define		ICMS_TYPE_CTRLTYPE_UNTREATED_ALARM_REQ					0x0d4f
#define		ICMS_TYPE_CTRLTYPE_UNTREATED_ALARM_ACK					0x0d50

/*************************** ��ͼ����������� ********************************/
//��ͼ�ṹͬ��	iMonitor	iAlarm	
#define		ICMS_TYPE_CTRLTYPE_EMAPSTRUCTURE_TRAN					0x0e03
#define		ICMS_TYPE_CTRLTYPE_EMAPSTRUCTURE_TRAN_ACK				0x0e04

//��ͼ����ͬ��	iMonitor	iAlarm	
#define		ICMS_TYPE_CTRLTYPE_EMAPDATA_TRAN						0x0e05
#define		ICMS_TYPE_CTRLTYPE_EMAPDATA_TRAN_ACK					0x0e06


// ���õ�ͼ�ṹ��Ϣ
#define		ICMS_TYPE_CTRLTYPE_SET_EMAPSTRUCTURE_TRAN					0x0e09
#define		ICMS_TYPE_CTRLTYPE_SET_EMAPSTRUCTURE_TRAN_ACK				0x0e0a

//��ͼ�������� iMonitor iEmap
#define    ISMS_TYPE_CTRLTYPE_GET_MAPPICTURE_REQ					0x8075
#define    ISMS_TYPE_CTRLTYPE_GET_MAPPICTURE_ACK					0x8076



/*************************** ������������ ********************************/
//�������	�����	iMC/iAlarm/iMap/iSwitch	
#define		ICMS_SERVER_ACTIVE_REQ									0x0f01
#define		ICMS_SERVER_ACTIVE_ACK									0x0f02

//�����˳�֪ͨ	iMC/iAlarm/iMap/iSwitch	�����	
#define		ICMS_SOFTDOG_STOP_REQ									0x0f03
#define		ICMS_SOFTDOG_STOP_ACK									0x0f04


/*************************** MATRIX����������� ********************************/
//��ȡMatrix�����������Ϣ	iMatrix	iMC	
#define ICMS_GET_MATRIX_SERVER_INFO_REQ			   					0x1001	
#define ICMS_GET_MATRIX_SERVER_INFO_ACK			   					0x1002		   

//����Matrix�����������Ϣ	iMatrix	iMC	
#define ICMS_SET_MATRIX_SERVER_INFO_REQ			   					0x1003		    
#define ICMS_SET_MATRIX_SERVER_INFO_ACK			   					0x1004	

//��������ǽ������Ѳ iMatrix	iMaxtrixServer
#define ICMS_START_MATRIX_GROUP_SURVEY_REQ			   				0x1005		    
#define  ICMS_START_MATRIX_GROUP_SURVEY_ACK				   			0x1006

//��������ǽ������Ѳ 	iMatrix	iMaxtrixServer	
#define ICMS_START_MATRIX_WINDOW_SURVEY_REQ			   				0x1007		    
#define  ICMS_START_MATRIX_WINDOW_SURVEY_ACK				   		0x1008		   	    

//��Ƶ��ָ������ͨ��  iMatrix	iMaxtrixServer
#define ICMS_MATRIX_SPECIAL_SUBEQUIPMENT_PLAY_REQ			   		0x1009		        
#define  ICMS_MATRIX_SPECIAL_SUBEQUIPMENT_PLAY_ACK			   		0x100a		

//ֹͣ����ͣ����ǽ������Ѳ    iMatrix	iMaxtrixServer 
#define ICMS_STOP_MATRIX_GROUP_SURVEY_REQ			   				0x100b		
#define  ICMS_STOP_MATRIX_GROUP_SURVEY_ACK			   				0x100c	

       	   
//ֹͣ����ǽ������Ѳ 	iMatrix	iMaxtrixServer	
#define ICMS_STOP_MATRIX_WINDOW_SURVEY_REQ			   				0x100d		    
#define  ICMS_STOP_MATRIX_WINDOW_SURVEY_ACK				   			0x100e

//��Ϣ����
#define ICMS_SET_MATRIX_INFO_OVERLAY_REQ							0x100f
#define  ICMS_SET_MATRIX_INFO_OVERLAY_ACK							0x1010	   

//������Ƶ���Ŵ�������
#define ICMS_SET_MATRIX_EXCHANGE_PLAYWND_REQ						0x1011
#define ICMS_SET_MATRIX_EXCHANGE_PLAYWND_ACK						0x1012   	  
   	  
//��Ƶ����ȫ����ʾ
#define ICMS_SET_MATRIX_FULLSCREEN_PLAYWND_REQ						0x1013		    
#define ICMS_SET_MATRIX_FULLSCREEN_PLAYWND_ACK						0x1014		   

//��Ƶ���涳��
#define ICMS_SET_MATRIX_FROZEN_SCREEN_PLAYWND_REQ					0x1015		    
#define ICMS_SET_MATRIX_FROZEN_SCREEN_PLAYWND_ACK					0x1016		    

//���������
#define ICMS_SET_MATRIX_CAMERA_LOCK_PLAYWND_REQ						0x1017		    
#define ICMS_SET_MATRIX_CAMERA_LOCK_PLAYWND_ACK						0x1018

//ͼ��180��ת
#define ICMS_SET_MATRIX_VIDEO_ROVERSAL_PLAYWND_REQ					0x1019		    
#define ICMS_SET_MATRIX_VIDEO_ROVERSAL_PLAYWND_ACK					0x101a		    

//ͼ����ǿ
#define ICMS_SET_MATRIX_IMAGE_ENHANCE_PLAYWND_REQ					0x101b		    
#define ICMS_SET_MATRIX_IMAGE_ENHANCE_PLAYWND_ACK				    0x101c

//�������ܷ���
#define ICMS_SET_MATRIX_INTELLIGENCE_ANALYSIS_PLAYWND_REQ		    0x101d	
#define ICMS_SET_MATRIX_INTELLIGENCE_ANALYSIS_PLAYWND_ACK		    0x101e	

//Vodָ�����ڲ�����Ƶ��
#define ICMS_MATRIX_SPECIAL_VOD_PLAY_REQ						    0x1021
#define ICMS_MATRIX_SPECIAL_VOD_PLAY_ACK						    0x1022

//Vod����ָ��ץ֡ͼƬ
#define ICMS_MATRIX_SPECIAL_VOD_DOWNLOAD_IMAGE_REQ				    0x1023
#define ICMS_MATRIX_SPECIAL_VOD_DOWNLOAD_IMAGE_ACK				    0x1024

//Vodָ������ͼƬ��ʾ
#define ICMS_MATRIX_SPECIAL_VOD_LISTIMAGE_REQ					    0x1025
#define ICMS_MATRIX_SPECIAL_VOD_LISTIMAGE_ACK					    0x1026

//Vod���ſ���
#define ICMS_MATRIX_SPECIAL_VOD_PLAYCTRL_REQ				  	    0x1027
#define ICMS_MATRIX_SPECIAL_VOD_PLAYCTRL_ACK				  	    0x1028

//Vod���ſ��ƣ��޼����٣�
#define ICMS_MATRIX_SPECIAL_VOD_VAR_SPEED_REQ				  	     0x1029
#define ICMS_MATRIX_SPECIAL_VOD_VAR_SPEED_ACK				  	     0x102a

//Vod���ſ��ƣ��Ŵ� ��С)
#define ICMS_MATRIX_SPECIAL_VOD_VAR_AREA_REQ				  	     0x102b
#define ICMS_MATRIX_SPECIAL_VOD_VAR_AREA_ACK				  	     0x102c

//Vod��Ϣ������ʾ
#define ICMS_SET_MATRIX_INFO_VOD_LIST_REQ			  		     	 0x102d
#define ICMS_SET_MATRIX_INFO_VOD_LIST_ACK			  		     	 0x102e

//Get Matrix Server Group_Survey Status
#define ICMS_GET_MATRIX_SURVEY_REQ									 0x102f
#define ICMS_GET_MATRIX_SURVEY_ACK									 0x1030

//Do Maxtrix Server Group Survey Play
#define	ICMS_MAXTRIX_SCHE_SURVEY_REQ								 0x1200
#define ICMS_MAXTRIX_SCHE_SURVEY_ACK								 0x1201

//����Matrix����Ѳ�ƻ�
#define ICMS_MATRIX_WEEK_SCHE_SURVEY_REQ							 0x1202
#define ICMS_MATRIX_WEEK_SCHE_SURVEY_ACK							 0x1203

#define ICMS_SET_MATRIX_CAMERA_BITRATECHANG_REQ						 0x1204	
#define ICMS_SET_MATRIX_CAMERA_BITRATECHANG_ACK						 0x1205	
#define	ICMS_ISWITCH_ISWITCH_TRANSMIT_DATA_REQ					     0x1208
#define	ICMS_ISWITCH_ISWITCH_TRANSMIT_DATA_ACK					     0x1209

//����Ǩ������
#define	ICMS_ISWITCH_ISWITCH_TRANSMIT_DATA_RATE_REQ					 0x1210
#define	ICMS_ISWITCH_ISWITCH_TRANSMIT_DATA_RATE_ACK					 0x1211

//Ǩ��ת��֪ͨ��Ϣ
//��Ϣ����:Ǩ��ת��������-------->Ǩ�Ʒ�����
#define	ICMS_ISWITCH_ISWITCH_TRANSMIT_DATA_NOTIFY					 0x1212

//��ʼת��Ǩ������
//��Ϣ����:Ǩ�Ʒ�����-------->Ǩ��ת��������
#define	ICMS_ISWITCH_ISWITCH_TRANSMIT_DATA_START					 0x1213
#define	ICMS_ISWITCH_ISWITCH_TRANSMIT_DATA_PAUSE					 0x1217
#define	ICMS_ISWITCH_ISWITCH_TRANSMIT_DATA_STOP					 0x1222

//ֹͣת��Ǩ������
#define ICMS_ISWITCH_ISWITCH_STOP_TRANSMIT_DATA_REQ                  0x1214

//Ǩ�Ʒ�������Ǩ��ת��������֮�������
#define ICMS_ISWITCH_ISWITCH_HEART_BEART_REQ                         0x1215
#define ICMS_ISWITCH_ISWITCH_HEART_BEART_ACK                         0x1216
//����Ǩ���ļ�����
#define ICMS_ISWITCH_IMC_LOCK_TRANS_FILE_REQ                         0x1218
//����Ǩ���ļ�Ӧ��
#define ICMS_ISWITCH_IMC_LOCK_TRANS_FILE_ACK                         0x1219

#define ICMS_ISWITCH_IMC_UNLOCK_TRANS_FILE_REQ                        0x1220
//����Ǩ���ļ�Ӧ��
#define ICMS_ISWITCH_IMC_UNLOCK_TRANS_FILE_ACK                        0x1221

//Ǩ�Ʊ����ļ�����
#define		ICMS_CLIENT_TRANSFER_FILE_REQ					         0x1227
//Ǩ�Ʊ����ļ�ACK
#define		ICMS_CLIENT_TRANSFER_FILE_ACK					         0x1223
//Ǩ�Ʊ����ļ���ɺ��֪ͨ
#define		ICMS_CLIENT_TRANSFER_DATA_NOTIFY					     0x1224
//Ǩ�Ʊ����ļ���������
#define		ICMS_CLIENT_TRANSFER_DATA_CTRL                           0x1225
#define		ICMS_CLIENT_TRANSFER_DATA_CTRL_ACK                       0x1226


//ICMS����ϵͳ�л�����/Ӧ�� //manage-->mc
#define		ICMS_IMANAGER_TO_IMC_SYSSWITCH_REQ						0x3201
#define		ICMS_IMANAGER_TO_IMC_SYSSWITCH_ACK						0x3202

//ICMS����ϵͳ�л�ȡ������/Ӧ�� //manage-->mc
#define		ICMS_IMANAGER_TO_IMC_CANCEL_SYSSWITCH_REQ				0x3203
#define		ICMS_IMANAGER_TO_IMC_CANCEL_SYSSWITCH_ACK				0x3204

#define		ICMS_TYPE_CTRLTYPE_ISWITCH_REBOOT_REQ					0x0dd2
#define		ICMS_TYPE_CTRLTYPE_ISWITCH_REBOOT_ACK					0x0dd3

#define		ICMS_TYPE_CTRLTYPE_ISWITCH_TAKEOVER_REQ					0x0dd6
#define		ICMS_TYPE_CTRLTYPE_ISWITCH_TAKEOVER_ACK					0x0dd7

#define		ICMS_CTRL_SWITCH_TYPE_CHANGE_NOTIY						0x0dd8
#define		ICMS_CTRL_SWITCH_TYPE_CHANGE_NOTIY_ACK					0x0dd9
/********************** Iswitch�ڲ��������(0x1031 - 0x103f) ****************************/
//��������״̬
#define ICMS_ISWITCH_NOTIFY_PARAM_UPDATE							0x1031
#define ICMS_ISWITCH_NOTIFY_RTPSTATUS								0x1032
#define ICMS_ISWITCH_NOTIFY_DELETEDEVICE							0x1033
#define	ICMS_ISWITCH_NOTIFY_DEVOPEN_STATUS							0x1034
#define ICMS_ISWTICH_NOTIFY_DEV_IDLE								0x1035
#define ICMS_ISWITCH_NOTIFY_OPEN_STREAM								0x1036
#define ICMS_ISWITCH_NOTIFY_CHANGERECDIR							0x1037
#define ICMS_ISWTICH_NOTIFY_RECTASKSTATUS							0x1038
#define ICMS_ISWTICH_HEART											0x1039
#define ICMS_ISWTICH_NOTIFY_REALSTREAMTAGRESPONSE                   0x103a

#define ICMS_ISWTICH_PING_REQ										0x10A0
#define	ICMS_ISWTICH_PING_ACK										0x10A1

/*************************** ������������� ********************************/
//��������£�������ӣ�ɾ�����޸ģ�	iManager	MC
#define ICMS_IMANAGER_PUBLICDOMAIN_UPD_REQ							0x1100
#define ICMS_IMANAGER_PUBLICDOMAIN_UPD_ACK							0x1101

//�������Աϵͳ���£�������ӣ�ɾ�����޸ģ�	iManager	MC
#define ICMS_IMANAGER_PUBLICDOMAIN_MCSYS_UPD_REQ					0x1102
#define ICMS_IMANAGER_PUBLICDOMAIN_MCSYS_UPD_ACK					0x1103

//��֤MC����	MC		MC
#define ICMS_IMANAGER_PUBLICDOMAIN_VERIFY_MCPSW_REQ					0x1104
#define ICMS_IMANAGER_PUBLICDOMAIN_VERIFY_MCPSW_ACK					0x1105

//�ֶ�ͬ��ָ���������ڵ����г�Ա	iManager	MC
#define ICMS_IMANAGER_PUBLICDOMAIN_MANUAL_SYNC_REQ					0x1106
#define ICMS_IMANAGER_PUBLICDOMAIN_MANUAL_SYNC_ACK					0x1107

//��MC����豸	iManager	MC
#define ICMS_IMANAGER_ACROSS_MC_ADDEQU_REQ							0x1108
#define ICMS_IMANAGER_ACROSS_MC_ADDEQU_ACK							0x1109

//��MC�����֯����	iManager	MC
#define ICMS_IMANAGER_ACROSS_MC_ADDORG_REQ							0x110A
#define ICMS_IMANAGER_ACROSS_MC_ADDORG_ACK							0x110B

//��MC����û�	iManager	MC
#define ICMS_IMANAGER_ACROSS_MC_ADDUSER_REQ							0x110C
#define ICMS_IMANAGER_ACROSS_MC_ADDUSER_ACK							0x110D

//��MC����û���	iManager	MC
#define ICMS_IMANAGER_ACROSS_MC_ADDUSERGROUP_REQ					0x110E
#define ICMS_IMANAGER_ACROSS_MC_ADDUSERGROUP_ACK					0x110F

//��MC��ӷ�����	iManager	MC
#define ICMS_IMANAGER_ACROSS_MC_ADDSERVER_REQ						0x1110
#define ICMS_IMANAGER_ACROSS_MC_ADDSERVER_ACK						0x1111

//��MC����豸(�ڴ�)	iMC		MC
#define ICMS_IMC_ACROSS_MC_ADDEQU_REQ								0x1112
#define ICMS_IMC_ACROSS_MC_ADDEQU_ACK								0x1113

//��MC�����֯����(�ڴ�)	iMC		MC
#define ICMS_IMC_ACROSS_MC_ADDORG_REQ								0x1114
#define ICMS_IMC_ACROSS_MC_ADDORG_ACK								0x1115

//��MC����û�(�ڴ�)	iMC		MC
#define ICMS_IMC_ACROSS_MC_ADDUSER_REQ								0x1116
#define ICMS_IMC_ACROSS_MC_ADDUSER_ACK								0x1117

//��MC����û���(�ڴ�)	iMC		MC	
#define ICMS_IMC_ACROSS_MC_ADDUSERGROUP_REQ							0x1118
#define ICMS_IMC_ACROSS_MC_ADDUSERGROUP_ACK							0x1119

//��MC��ӷ�����(�ڴ�)	iMC		MC
#define ICMS_IMC_ACROSS_MC_ADDSERVER_REQ							0x111A
#define ICMS_IMC_ACROSS_MC_ADDSERVER_ACK							0x111B

//MC��SWITCH����ָ���豸ͼ��������ǽ����
#define ICMS_TO_ISWITCH_VIDEO_TO_MATRIX_REQ							0x1201
#define ICMS_TO_ISWITCH_VIDEO_TO_MATRIX_ACK							0x1202

//ISWITCH��ȡ��������״̬����
#define ICMS_ISWITCH_2_UID_GET_FILTER_STATUS_REQ					0x6001
#define ICMS_ISWITCH_2_UID_GET_FILTER_STATUS_ACK					0x6002

//ISWITCH���ù�������״̬����
#define ICMS_ISWITCH_2_UID_SET_FILTER_STATUS_REQ					0x6003
#define ICMS_ISWITCH_2_UID_SET_FILTER_STATUS_ACK					0x6004

/*************************** �����ݶ��� ********************************/
#define ICMS_DEFINE_TYPE_NONE									0x00

//data main type
#define ICMS_DEFINE_DATA_TYPE_VIDEO								0x10
#define ICMS_DEFINE_DATA_TYPE_AUDIO								0x20
#define ICMS_DEFINE_DATA_TYPE_STREAM							0x40
#define ICMS_DEFINE_DATA_TYPE_INDUSTRY							0x60
#define ICMS_DEFINE_DATA_TYPE_METADATA							0x80
#define ICMS_DEFINE_DATA_TYPE_SELFDEFINE						0xff


//ext type
//Audio Codec Type
#define ICMS_DEFINE_AUDIO_UNKNOW								0x0001
#define ICMS_DEFINE_AUDIO_G711									0x0002
#define ICMS_DEFINE_AUDIO_G711U                                 0x0002
#define ICMS_DEFINE_AUDIO_AAC									0x0003
#define ICMS_DEFINE_AUDIO_G726									0x0004
#define ICMS_DEFINE_AUDIO_MP3									0x0005
#define ICMS_DEFINE_HIK_G722                                    0x0006
#define ICMS_DEFINE_HIK_G711                                    0x0007
#define ICMS_DEFINE_DAHUA_G711A                                 0x0008
#define ICMS_DEFINE_AUDIO_PCM                                   0x000a
#define ISOC_DEFINE_AUDIO_G722									0x000b
#define ISOC_DEFINE_AUDIO_G729                                  0x000c
#define ISOC_DEFINE_AUDIO_G723_1                                0x000d
#define ICMS_DEFINE_AUDIO_G722									0x000b
#define ICMS_DEFINE_AUDIO_G729                                  0x000c
#define ICMS_DEFINE_AUDIO_G723_1                                0x000d
#define ICMS_DEFINE_AUDIO_AMR                                   0x000e
#define ICMS_DEFINE_AUDIO_ADPCM                                 0x000f
#define ICMS_DEFINE_AUDIO_G711A                                 0x0010
#define ICMS_DEFINE_AUDIO_AMR_NB								0x0011 //AMR-NB��Ƶ��ʽ
#define ICMS_DEFINE_AUDIO_AMR_MB								0x0012 //AMR-MB��Ƶ��ʽ
#define ICMS_DEFINE_MPON_G711A									0x0013
#define ICMS_DEFINE_CREARO_ADPCM                                0x0014
#define ICMS_DEFINE_AUDIO_G723                                  0x0015

//Video Codec Type
#define ICMS_DEFINE_VIDEO_UNKNOW								0x0008
#define ICMS_DEFINE_VIDEO_JPEG									0x0010
#define ICMS_DEFINE_HIK_JPEG									0x0011
#define ICMS_DEFINE_DAHUA_JPEG									0x0012
#define ICMS_DEFINE_YAAN_JPEG									0x0013
#define ICMS_DEFINE_HANBANG_JPEG								0x0014
#define ICMS_DEFINE_VIDEO_MJPEGB								0x0015
#define ICMS_DEFINE_HUAMAI_JPEG                                 0x0016

#define ICMS_DEFINE_VIDEO_MPEG4									0x0020
#define ICMS_DEFINE_HIK_MPEG4									0x0021
#define ICMS_DEFINE_DAHUA_MPEG4									0x0022
#define ICMS_DEFINE_YAAN_MPEG4									0x0023

#define ICMS_DEFINE_VIDEO_MPEG2									0x0040
#define ICMS_DEFINE_HIK_MPEG2									0x0041

#define ICMS_DEFINE_VIDEO_H264									0x0080
#define ICMS_DEFINE_HIK_H264									0x0081
#define ICMS_DEFINE_DAHUA_H264									0x0082
#define ICMS_DEFINE_YAAN_H264									0x0083
#define ICMS_DEFINE_HUAMAI_H264                                 0x0084
#define ICMS_DEFINE_CREARO_H264                                 0x0085

#define ICMS_DEFINE_VIDEO_MSMPEG4V1								0x0090
#define ICMS_DEFINE_VIDEO_MSMPEG4V2								0x0091
#define ICMS_DEFINE_VIDEO_MSMPEG4V3								0x0092
#define ICMS_DEFINE_VIDEO_WMV1									0x0093
#define ICMS_DEFINE_VIDEO_WMV2									0x0094
#define ICMS_DEFINE_VIDEO_MEGAEYES								0x0095
#define ICMS_DEFINE_AUDIO_MEGAEYES								0x0096

#define ICMS_DEFINE_VIDEO_EASY7      							0x009b


#define ICMS_DEFINE_STREAM_DEC									0x0100 /* ��ʾΪ���������� */
#define ICMS_DEFINE_STREAM_RAW									0x0200 

#define ICMS_DEFINE_METADATE_DEPA								0x0300 /* DepaԪ���� */

#define ICMS_DEFINE_DATA_EXTTYPE_ALTERRECDIR					0xf001 /* ¼������洢·���л� */

//sub type
#define ICMS_DEFINE_SUBTYPE_FRAME_I								0x01
#define ICMS_DEFINE_SUBTYPE_FRAME_P								0x02
#define ICMS_DEFINE_SUBTYPE_FRAME_B								0x03
#define ICMS_DEFINE_SUBTYPE_NOKEYFRAME							0x04   

//audio bitrate
#define ICMS_DEFINE_AUDIO_BITRATE_16K							0x01
#define ICMS_DEFINE_AUDIO_BITRATE_24K							0x02
#define ICMS_DEFINE_AUDIO_BITRATE_32K							0x03
#define ICMS_DEFINE_AUDIO_BITRATE_40K							0x04
#define ICMS_DEFINE_AUDIO_BITRATE_64K							0x05

#pragma region ����Ϣ
#define GET_DOMAIN_SYSTEMINFO_REQ					0x3000
#define GET_DOMAIN_SYSTEMINFO_ACK					0x3001

#define GET_DOMAINCLIENT_INFO_REQ					0x3002
#define GET_DOMAINCLIENT_INFO_ACK					0x3003

#define UPDATE_DOMAINCLIENT_INFO_REQ				0x3004
#define UPDATE_DOMAINCLIENT_INFO_ACK				0x3005

#define GET_ROUTE_INFO_REQ							0x3006
#define GET_ROUTE_INFO_ACK							0x3007

#define UPDATE_ROUTE_INFO_REQ						0x3008
#define UPDATE_ROUTE_INFO_ACK						0x3009

// �������Ա
#define IDOMAIN_ADD_DOMAINCLIENT_REQ				0x301A
#define IDOMAIN_ADD_DOMAINCLIENT_ACK				0x301B

// �������Ա(�������ڲ�,��������)
#define IDOMAIN_ADD_DOMAINROUTE_REQ					0x301C
#define IDOMAIN_ADD_DOMAINROUTE_ACK					0x301D

// ɾ�����Ա(�������ڲ�,��������)
#define IDOMAIN_DEL_DOMAINCLIENT_REQ				0x301E
#define IDOMAIN_DEL_DOMAINCLIENT_ACK				0x301F

// ɾ����·��(�������ڲ�,��������)
#define IDOMAIN_DEL_DOMAINROUTE_REQ					0x3020
#define IDOMAIN_DEL_DOMAINROUTE_ACK					0x3021

// �ֶ�ͬ��
#define IDOMAIN_MANUAL_SYNC_REQ						0x3022
#define IDOMAIN_MANUAL_SYNC_ACK						0x3023

// ���Ա�汾��֤
#define IDOMAIN_DCVERSION_VERIFY_REQ				0x3024
#define IDOMAIN_DCVERSION_VERIFY_ACK				0x3025

// ���Ա��ϵ�汾��֤
#define IDOMAIN_DRVERSION_VERIFY_REQ				0x3026
#define IDOMAIN_DRVERSION_VERIFY_ACK				0x3027

// �����ݰ汾��֤
#define IDOMAIN_DDVERSION_VERIFY_REQ				0x3028
#define IDOMAIN_DDVERSION_VERIFY_ACK				0x3029

// �Զ�ͬ������
#define IDOMAIN_AUTO_SYNC_REQ						0x302A
#define IDOMAIN_AUTO_SYNC_ACK						0x302B

// ��ȡ���Ա
#define IDOMAIN_GET_DOMAINCLENT_REQ					0x302C
#define IDOMAIN_GET_DOMAINCLENT_ACK					0x302D

// ��ȡ��·��
#define IDOMAIN_GET_DOMAINROUTE_REQ					0x302E
#define IDOMAIN_GET_DOMAINROUTE_ACK					0x302F

// ��ȡ����������
#define IDOMAIN_GET_DOMAINDATA_REQ					0x3030
#define IDOMAIN_GET_DOMAINDATA_ACK					0x3031

// ���Ա����
#define IDOMAIN_UPDATE_DOMAINCLENT_REQ				0x3032
#define IDOMAIN_UPDATE_DOMAINCLENT_ACK				0x3033

// ��·�ɸ���
#define IDOMAIN_UPDATE_DOMAINROUTE_REQ				0x3034
#define IDOMAIN_UPDATE_DOMAINROUTE_ACK				0x3035

// �����ݸ���
#define IDOMAIN_UPDATE_DOMAINDATA_REQ				0x3036
#define IDOMAIN_UPDATE_DOMAINDATA_ACK				0x3037

// �û���֤����
#define IDOMAIN_USER_AUTHENTICATION_REQ				0x3038
#define IDOMAIN_USER_AUTHENTICATION_ACK				0x3039

// ����IP�Ͷ˿ڻ�ȡĿ������Ϣ manager -> mc -> ds
#define IDOMAIN_MANAGER_2_DSERVER_GET_DOMIANINFO_REQ	0X303A
#define IDOMAIN_MANAGER_2_DSERVER_GET_DOMIANINFO_ACK	0X303B

// ������Ա manager -> mc -> ds
#define IDOMAIN_MANAGER_2_DSERVER_ADD_DOMAINCLIENT_REQ	0X303C
#define IDOMAIN_MANAGER_2_DSERVER_ADD_DOMAINCLIENT_ACK	0X303D

// ������·�� manager -> mc -> ds
#define IDOMAIN_MANAGER_2_DSERVER_SET_DOMAINROUTE_REQ	0X303E
#define IDOMAIN_MANAGER_2_DSERVER_SET_DOMAINROUTE_ACK	0X303F

// ɾ�����Ա manager -> mc -> ds
#define IDOMAIN_MANAGER_2_DSERVER_DEL_DOMAINCLIENT_REQ	0X3040
#define IDOMAIN_MANAGER_2_DSERVER_DEL_DOMAINCLIENT_ACK	0X3041

// �������� manager -> mc ->ds
#define  IDOMAIN_MANAGER_2_DSERVER_DOMAIN_SET_REQ 		0x3042
#define  IDOMAIN_MANAGER_2_DSERVER_DOMAIN_SET_ACK 		0x3043

// ��ȡĿ����ϵͳ���ݰ汾
#define IDOMAIN_GET_DOMAIN_DATA_VERSION_REQ				0x3044
#define IDOMAIN_GET_DOMAIN_DATA_VERSION_ACK				0x3045

#pragma endregion

#define ISMS_GET_SUBEQUIPMENT_REQ					0x8000
#define ISMS_GET_SUBEQUIPMENT_ACK					0x8001

#define ISMS_GET_EQUIPMENT_REQ						0x8002
#define ISMS_GET_EQUIPMENT_ACK						0x8003

#define ISMS_GET_EQUIPMENT_TYPE_REQ					0x8004
#define ISMS_GET_EQUIPMENT_TYPE_ACK					0x8005

#define ISMS_SET_EQUIPMENT_REQ						0x8006
#define ISMS_SET_EQUIPMENT_ACK						0x8007

#define ISMS_SET_SUBEQUIPMENT_REQ					0x8008
#define ISMS_SET_SUBEQUIPMENT_ACK					0x8009

#define ISMS_SET_ORGANIZE_REQ						0x800a
#define ISMS_SET_ORGANIZE_ACK						0x800b

#define ISMS_SET_EQUORG_LINK_REQ					0x800c
#define ISMS_SET_EQUORG_LINK_ACK					0x800d

#define ISMS_GET_EQUSUB_LINK_REQ					0x800e
#define ISMS_GET_EQUSUB_LINK_ACK					0x800f

#define ISMS_GET_SERVER_REQ							0x8010
#define ISMS_GET_SERVER_ACK							0x8011

#define ISMS_SET_SERVER_REQ							0x8012
#define ISMS_SET_SERVER_ACK							0x8013

#define ISMS_GET_USERGROUP_LINK_REQ					0x8014
#define ISMS_GET_USERGROUP_LINK_ACK					0x8015

#define ISMS_SET_USERGROUP_REQ						0x8016
#define ISMS_SET_USERGROUP_ACK						0x8017

#define ISMS_SET_USER_REQ							0x8018
#define ISMS_SET_USER_ACK							0x8019

#define ISMS_GET_SYSTEM_INFO_REQ					0x801a
#define ISMS_GET_SYSTEM_INFO_ACK					0x801b

#define ISMS_LOGIN_AUTHENTICATION_REQ				0x801c
#define ISMS_LOGIN_AUTHENTICATION_ACK				0x801d

#define ISMS_LOGOUT_REQ								0x801e
#define ISMS_LOGOUT_ACK								0x801f

#define ISMS_SWITCH_RELAYSYSTEM_REQ					0x8020
#define ISMS_SWITCH_RELAYSYSTEM_ACK					0x8021

#define ISMS_CANCEL_SWITCH_RELAYSYSTEM_REQ			0x8022
#define ISMS_CANCEL_SWITCH_RELAYSYSTEM_ACK			0x8023

// ���·��������ӹ�ϵ
#define ISMS_UPDATE_SERVERLEVEL_REQ					0x8026
#define ISMS_UPDATE_SERVERLEVEL_ACK					0x8027


//��ȡ�߼�����
#define ISMS_GET_SYSSTORAGE_BASIC_REQ				0x802a
#define ISMS_GET_SYSSTORAGE_BASIC_ACK				0x802b

#define ISMS_GET_USER_BASIC_REQ						0x802e
#define ISMS_GET_USER_BASIC_ACK						0x802f

#define ISMS_GET_STORAGEDISK_INFO_REQ				0x8031
#define ISMS_GET_STORAGEDISK_INFO_ACK				0x8032

// ��������л�����
#define ISMS_EXCHANGLE_DISKINFO_REQ					0x8035
#define ISMS_EXCHANGLE_DISKINFO_ACK					0x8036

#define ISMS_EXCHANGLE_SERVER_REQ					0x8037
#define	ISMS_EXCHANGLE_SERVER_ACK					0x8038

//��ȡʱ������
#define ISMS_GET_SYSTEMTIME_REQ						0x8039
#define ISMS_GET_SYSTEMTIME_ACK						0x803a

//��ȡ����������Ϣ
#define ISMS_GET_ALARM_RELATION_REQ					0x803b
#define ISMS_GET_ALARM_RELATION_ACK					0x803c

//��ȡ����Ԥ��
#define ISMS_GET_ALARM_PREPLAN_REQ					0x803d
#define ISMS_GET_ALARM_PREPLAN_ACK					0x803e

//��ȡ����¼��������Ϣ
#define ISMS_GET_ALARM_RECORDE_REQ					0x8040
#define ISMS_GET_ALARM_RECORDE_ACK					0x8041

//��ȡץ֡������Ϣ
#define ISMS_GET_ALARM_CATCH_REQ					0x8042
#define ISMS_GET_ALARM_CATCH_ACK					0x8043

//��ȡ��̨������Ϣ
#define ISMS_GET_ALARM_PTZ_REQ						0x8044
#define ISMS_GET_ALARM_PTZ_ACK						0x8045

//��ȡ����ǽ������Ϣ
#define ISMS_GET_ALARM_TVWALL_REQ					0x8046
#define ISMS_GET_ALARM_TVWALL_ACK					0x8047

//��ȡ���������Ϣ
#define ISMS_GET_ALARM_OUTPUT_REQ					0x8048
#define ISMS_GET_ALARM_OUTPUT_ACK					0x8049

//��ȡ��ض�������Ϣ
#define ISMS_GET_ALARM_MONITOR_REQ					0x804a
#define ISMS_GET_ALARM_MONITOR_ACK					0x804b

//��ȡEmail������Ϣ
#define ISMS_GET_ALARM_EMAIL_REQ					0x804c
#define ISMS_GET_ALARM_EMAIL_ACK					0x804d

//��ȡ����������Ϣ
#define ISMS_GET_ALARM_SMS_REQ						0x804e
#define ISMS_GET_ALARM_SMS_AKC						0x8050

//����Ѳ��ƻ�
#define ISMS_SET_INSPECTION_PLAN_INFO_REQ			0x8051
#define ISMS_SET_INSPECTION_PLAN_INFO_ACK			0x8052

//��ѯѲ��ƻ�	
#define ISMS_LST_INSPECTION_PLAN_INFO_REQ			0x8053
#define ISMS_LST_INSPECTION_PLAN_INFO_ACK			0x8054

//���÷�����ѯ�ƻ�
#define ISMS_SET_GROUP_PLAN_REQ						0x8055
#define ISMS_SET_GROUP_PLAN_ACK						0x8056

//����¼������
#define ISMS_SET_PLAN_WEEK_RECORD_REQ 				0x8057
#define ISMS_SET_PLAN_WEEK_RECORD_ACK				0x8058

//��ȡ¼������
#define ISMS_LST_PLAN_WEEK_RECORD_REQ				0x8059
#define ISMS_LST_PLAN_WEEK_RECORD_ACK				0x805A

#define ISMS_GET_DEFENCE_STATE_REQ					0x805b
#define ISMS_GET_DEFENCE_STATE_ACK					0x805c

//��ȡ��������
#define ISMS_GET_PLAN_DEFENCE_REQ					0x805D
#define ISMS_GET_PLAN_DEFENCE_ACK					0x805E

//���ò�������
#define ISMS_SET_PLAN_DEFENCE_REQ					0x805F
#define ISMS_SET_PLAN_DEFENCE_ACK					0x8060

#define ISMS_SET_ALARM_LOG_REQ						0x8961
#define ISMS_SET_ALARM_LOG_ACK						0x8962

#define ISMS_UPT_ALARM_LOG_REQ						0x8061
#define ISMS_UPT_ALARM_LOG_ACK						0x8062

#define ISMS_SET_SYSTEM_LOG_REQ						0x8063
#define ISMS_SET_SYSTEM_LOG_ACK						0x8064

#define ISMS_SET_ALARM_LEVEL_REQ                    0x8065
#define ISMS_SET_ALARM_LEVEL_ACK                    0x8066

#define ISMS_SET_USER_LOGIN_REQ                     0x8067
#define ISMS_SET_USER_LOGIN_ACK                     0x8068

//��ѯѲ����
#define ISMS_GET_INSPECTION_RESULT_REQ				0x8069
#define ISMS_GET_INSPECTION_RESULT_ACK				0x806A

//��ȡ�豸�����豸��ϵ
#define ISMS_LST_EQUIPMENT_REQ						0x806B
#define ISMS_LST_EQUIPMENT_ACK						0x806C

//��ȡ�ļ���չ��Ϣ
#define ISMS_GET_FILEEXTENSION_REQ                  0x806D 
#define ISMS_GET_FILEEXTENSION_ACK                  0x806E

//�����ļ���չ��Ϣ
#define ISMS_SET_FILEEXTENSION_REQ                  0x806F
#define ISMS_SET_FILEEXTENSION_ACK                  0x8070

//���ô洢������Ϣ
#define ISMS_SET_DISKSTORGEINFO_REQ                 0x8071
#define ISMS_SET_DISKSTORGEINFO_ACK                 0x8072

//���õ�ͼ��Ϣ
#define ISMS_SET_MAPPICTURE_REQ                     0x8073
#define ISMS_SET_MAPPICTURE_ACK						0x8074

//��ȡ��ͼ����
#define ISMS_GET_MAPPICTURE_REQ						0x8075
#define ISMS_GET_MAPPICTURE_ACK						0x8076

//��ȡ�汾��Ϣ
#define ISMS_GET_VERSION_REQ						0x8077
#define ISMS_GET_VERSION_ACK						0x8078

//���ð汾��Ϣ
#define ISMS_SET_VERSION_REQ						0x8079
#define ISMS_SET_VERSION_ACK						0x8080

//��ȡMSCS��Ϣ
#define ISMS_GET_MSCS_REQ                           0x8081
#define ISMS_GET_MSCS_ACK                           0x8082

//����MSCS��Ϣ
#define ISMS_SET_MSCS_REQ                           0x8083
#define ISMS_SET_MSCS_ACK                           0x8084

//���ñ���������Ϣ
#define ISMS_SET_ALARM_RELATION_REQ					0x8085
#define ISMS_SET_ALARM_RELATION_ACK					0x8086

//���ñ���Ԥ��
#define ISMS_SET_ALARM_PREPLAN_REQ					0x8087
#define ISMS_SET_ALARM_PREPLAN_ACK					0x8088

//���ñ���¼��������Ϣ
#define ISMS_SET_ALARM_RECORDE_REQ					0x8089
#define ISMS_SET_ALARM_RECORDE_ACK					0x808A

//����ץ֡������Ϣ
#define ISMS_SET_ALARM_CATCH_REQ					0x808B
#define ISMS_SET_ALARM_CATCH_ACK					0x808C

//������̨������Ϣ
#define ISMS_SET_ALARM_PTZ_REQ						0x808D
#define ISMS_SET_ALARM_PTZ_ACK						0x808E

//���õ���ǽ������Ϣ
#define ISMS_SET_ALARM_TVWALL_REQ					0x8090
#define ISMS_SET_ALARM_TVWALL_ACK					0x8091

//�������������Ϣ
#define ISMS_SET_ALARM_OUTPUT_REQ					0x8092
#define ISMS_SET_ALARM_OUTPUT_ACK					0x8093

//���ü�ض�������Ϣ
#define ISMS_SET_ALARM_MONITOR_REQ					0x8094
#define ISMS_SET_ALARM_MONITOR_ACK					0x8095

//����Email������Ϣ
#define ISMS_SET_ALARM_EMAIL_REQ					0x8096
#define ISMS_SET_ALARM_EMAIL_ACK					0x8097

//���ö���������Ϣ
#define ISMS_SET_ALARM_SMS_REQ						0x8098
#define ISMS_SET_ALARM_SMS_AKC						0x8099

//���ñ����ȼ�
#define ISMS_SET_ALARM_LEVER_REQ					0x809A
#define ISMS_SET_ALARM_LEVER_AKC					0x809B

//��ȡ�����ȼ�
#define ISMS_GET_ALARM_LEVER_REQ					0x809C
#define ISMS_GET_ALARM_LEVER_AKC					0x809D

//�����߼�����
#define ISMS_SET_SYSSTORAGE_BASIC_REQ				0x809E
#define ISMS_SET_SYSSTORAGE_BASIC_ACK				0x80AF

//��ȡȡ֤��Դ�������
#define ISMS_GET_EVIDENCEALLOCATEINFO_REQ           0x80A5
#define ISMS_GET_EVIDENCEALLOCATEINFO_ACK           0x80A6

//��ȡȡ֤��Դ�������
#define ISMS_SET_EVIDENCEALLOCATEINFO_REQ           0x80A7
#define ISMS_SET_EVIDENCEALLOCATEINFO_ACK           0x80A8

//��ȡ�洢��Դ������
#define ISMS_GET_STORAGERESOURCEDISK_REQ			0x80A9
#define ISMS_GET_STORAGERESOURCEDISK_ACK			0x80AA

//���ô洢��Դ������
#define ISMS_SET_STORAGERESOURCEDISK_REQ			0x80AB
#define ISMS_SET_STORAGERESOURCEDISK_ACK			0x80AC

//��ȡ�洢��Դ���� 
#define ISMS_GET_STORAGERESOURCE_REQ				0x80AD
#define ISMS_GET_STORAGERESOURCE_ACK				0x80AE

//���ô洢��Դ���� 
#define ISMS_SET_STORAGERESOURCE_REQ				0x80AF
#define ISMS_SET_STORAGERESOURCE_ACK				0x80b0

//��ȡ����ǽ��Ϣ
#define ISMS_GET_MATRIXSERVERINFO_REQ				0x80B1
#define ISMS_GET_MATRIXSERVERINFO_ACK				0x80B2

//���õ���ǽ��Ϣ
#define ISMS_SET_MATRIXSERVERINFO_REQ				0x80B3
#define ISMS_SET_MATRIXSERVERINFO_ACK				0x80B4

//ɾ��������
#define ISMS_DELETE_DOMAINDATA_REQ					0x80B5
#define ISMS_DELETE_DOMAINDATA_ACK					0x80B6

//��ȡ��������
#define ISMS_GET_ALARMTYPE_REQ						0x80B7
#define ISMS_GET_ALARMTYPE_ACK						0x80B8

//����͸������
#define ISMS_SET_TRANSPARENTDATA_REQ				0x80B9
#define ISMS_SET_TRANSPARENTDATA_ACK				0x80BA

//��ȡ͸������
#define ISMS_GET_TRANSPARENTDATA_REQ				0x80BB
#define ISMS_GET_TRANSPARENTDATA_ACK				0x80BC

//�����û�������Ϣ
#define ISMS_MOD_USER_BASIC_INFO_REQ				0x80BD
#define ISMS_MOD_USER_BASIC_INFO_ACK				0x80BE

//�����û�����
#define ISMS_MOD_USER_PASSWORD_REQ					0x80BF
#define ISMS_MOD_USER_PASSWORD_ACK					0x80C0

//�����û�����Ȩ��
#define ISMS_MOD_USER_OPERATE_AUTHORITY_REQ			0x80C1
#define ISMS_MOD_USER_OPERATE_AUTHORITY_ACK			0x80C2

//�����û��豸Ȩ��
#define ISMS_MOD_USER_DEVICE_AUTHORITY_REQ			0x80C3
#define ISMS_MOD_USER_DEVICE_AUTHORITY_ACK			0x80C4

//�����û����豸Ȩ��
#define ISMS_MOD_USERGROUP_DEVICE_AUTHORITY_REQ		0x80C5
#define ISMS_MOD_USERGROUP_DEVICE_AUTHORITY_ACK		0x80C6

//��ȡ�û����豸Ȩ��
#define	ISMS_GET_USERGROUP_DEVICE_AUTHORITY_REQ		0x80C7
#define	ISMS_GET_USERGROUP_DEVICE_AUTHORITY_ACK		0x80C8

//��ȡ���û���Ϣ
#define IDOMAIN_GET_DUSERINFO_REQ	0x303a
#define IDOMAIN_GET_DUSERINFO_ACK	0x303b

//�������û���Ϣ
#define IDOMAIN_UPDATE_DUSERINFO_REQ	0x303c
#define IDOMAIN_UPDATE_DUSERINFO_ACK	0x303d

//��ȡ������¼���ץ֡�ļ���Ϣ
#define ISMS_GET_LOCKEDFILEINFO_REQ 	0x80C9
#define ISMS_GET_LOCKEDFILEINFO_ACK 	0x80CA

//��ȡ������̺��ļ��Ĺ�ϵ
#define ISMS_GET_PHYSICSDISKANDFILERELATION_REQ 0x80CB
#define ISMS_GET_PHYSICSDISKANDFILERELATION_ACK 0x80CC

//��ȡǨ���ļ���Ϣ(ȡ֤)
#define ISMS_GET_MIGRATEFILEINFO_REQ	0x80CD
#define ISMS_GET_MIGRATEFILEINFO_ACK	0x80CE 

//��ȡǨ��ץ֡��Ϣ(ȡ֤)
#define  ISMS_GET_MIGRATEPICFILEINFO_REQ		0x80CF
#define  ISMS_GET_MIGRATEPICFILEINFO_ACK		0x80D0


//��ȡǨ�������Ϣ(����δ��ɵ�Ǩ��������Ϣ, ���������δ��������Ǩ������)
#define  ISMS_GET_MIGRATETASKINFO_REQ		0x80D1
#define  ISMS_GET_MIGRATETASKINFO_ACK		0x80D2

//��ȡǨ�ƴ洢������Ϣ
#define  ISMS_GETMIGRATESTORECONFIGINFO_REQ		0x80D2
#define  ISMS_GETMIGRATESTORECONFIGINFO_ACK		0x80D3

//����Ǩ������
#define  ISMS_SET_MIGRATETASK_REQ	0x80D4
#define  ISMS_SET_MIGRATETASK_ACK	0x80D5

//���õ�ͼĿ¼
#define	 ISMS_SET_MAPLIST_REQ	0x80D6
#define	 ISMS_SET_MAPLIST_ACK	0x80D7

//����¼���ļ�
#define ISMS_SET_FILESINFO_REQ		0x80D8
#define ISMS_SET_FILESINFO_ACK		0x80D9

//����ץ֡�ļ�
#define ISMS_SET_PICFILESINFO_REQ		0x80DA
#define ISMS_SET_PICFILESINFO_ACK		0x80DB

//�����ļ���ǩ��Ϣ
#define ISMS_SET_TAGINFO_REQ 0x80DC
#define ISMS_SET_TAGINFO_ACK 0x80DD

//��ȡ�ļ���ǩ��Ϣ
#define ISMS_GET_TAGINFO_REQ 0x80DE
#define ISMS_GET_TAGINFO_ACK 0x80DF

//��ȡ�ָ�¼���С
#define ISMS_GET_RECORD_SIZE_REQ 0x80E0
#define ISMS_GET_RECORD_SIZE_ACK 0x80E1

//���õ�ͼ�ڵ�
#define	 ISMS_SET_MAPLEAF_REQ	0x80E2
#define	 ISMS_SET_MAPLEAF_ACK	0x80E3

//���õ�ͼ�ڵ��ϵ
#define	 ISMS_SET_MAPLEAFASS_REQ	0x80E4
#define	 ISMS_SET_MAPLEAFASS_ACK	0x80E5

//���õ�ͼ���豸��ϵ
#define	 ISMS_SET_MAPSUBEQUASS_REQ	0x80E6
#define	 ISMS_SET_MAPSUBEQUASS_ACK	0x80E7

//����ָ���ļ�
#define ISMS_LOCKFILES_REQ         0x80E8
#define ISMS_LOCKFILES_ACK		   0x80E9

//��������ļ�
#define ISMS_UNLOCKFILES_REQ		0x80EA
#define ISMS_UNLOCKFILES_ACK		0x80EB

//�����豸����
#define ISMS_SET_DEVICE_TYPE_REQ	0x80EC
#define ISMS_SET_DEVICE_TYPE_ACK	0x80ED

//��ѯϵͳ��־
#define ISMS_GET_SYSTEMLOG_REQ		0x80EE
#define ISMS_GET_SYSTEMLOG_ACK		0x80EF

//��ѯ������־
#define ISMS_GET_ALARMLOG_REQ		0x80F0
#define ISMS_GET_ALARMLOG_ACK		0x80F1

//��ȡδ����ı�����Ϣ
#define ICMS_TYPE_CTRLTYPE_UNTREATED_ALARM_REQ  0x0d4f
#define ICMS_TYPE_CTRLTYPE_UNTREATED_ALARM_ACK  0x0d50

//����Ǩ������
#define  ISMS_DEL_MIGRATETASK_REQ	0x80F2
#define  ISMS_DEL_MIGRATETASK_ACK	0x80F3

//����Ԥ�õ�
#define ISMS_SET_SUBPREDEFINEPOS_REQ	0x80F4
#define ISMS_SET_SUBPREDEFINEPOS_ACK	0x80F5

//����Ԥ�õ�
#define ISMS_SET_SUBPREDEFINECRUISE_REQ	0x80F6
#define ISMS_SET_SUBPREDEFINECRUISE_ACK	0x80F7

//��ȡ�����ռ��С
#define ISMS_GET_LOCKED_SPACE_LIMIT_REQ 0x80F8
#define ISMS_GET_LOCKED_SPACE_LIMIT_ACK 0x80F9

//���������ռ��С
#define ISMS_SET_LOCKED_SPACE_SIZE_REQ 0x80FA
#define ISMS_SET_LOCKED_SPACE_SIZE_ACK 0x80FB

// ��������
#define ISMS_SMS_2_SPS_GET_LOADSTATUS_INFO_REQ		0x80FC
#define	ISMS_SMS_2_SPS_GET_LOADSTATUS_INFO_ACK		0x80FD
// ����֪ͨ
#define ISMS_SPS_2_SMS_LOADSTATUS_INFO_NOTIFY_REQ	0x80FE

//�����û���ϵͳȨ��
#define ISMS_MOD_USERGROUP_AUTHORITY_REQ 0x80FF
#define ISMS_MOD_USERGROUP_AUTHORITY_ACK 0x8100

//��ȡ�û���ϵͳȨ��
#define ISMS_GET_USERGROUP_AUTHORITY_REQ 0x8101
#define ISMS_GET_USERGROUP_AUTHORITY_ACK 0x8102

//����¼��Ǩ���������
#define  ISMS_SET_MIGRATE_CURRENT_POS_TIME_REQ	0x8103
#define  ISMS_SET_MIGRATE_CURRENT_POS_TIME_ACK	0x8104	

//����Ǩ�Ʊ�Ŀ
#define ISOC_SET_MIGRATE_FILE_CATALOGUE_INFO_REQ 0x8105
#define ISOC_SET_MIGRATE_FILE_CATALOGUE_INFO_ACK 0x8106

//��ȡǨ�Ʊ�Ŀ��Ϣ
#define ISOC_GET_MIGRATE_FILE_CATALOGUE_INFO_REQ 0x8107
#define ISOC_GET_MIGRATE_FILE_CATALOGUE_INFO_ACK 0x8108

//����ϵͳ��Ϣ
#define ISMS_SET_SYSTEM_INFO_REQ				0x8109
#define ISMS_SET_SYSTEM_INFO_ACK				0x810A

//ɾ��ץ֡�ļ�
#define ISMS_DELETE_PICFILE_REQ					0x810B
#define ISMS_DELETE_PICFILE_ACK					0x810C

//ISMS���ݿⱸ�ݣ�
//�ֶ��������ݿ�
#define ISMS_MANUAL_BACKUP_REQ					0x810D
#define ISMS_MANUAL_BACKUP_ACK					0x810E

//��ȡ�Զ���������
#define ISMS_GET_AUTO_BACKUP_CONFIG_REQ			0x810F
#define ISMS_GET_AUTO_BACKUP_CONFIG_ACK			0x8110

//�����Զ�����
#define ISMS_SET_AUTO_BACKUP_REQ				0x8111
#define ISMS_SET_AUTO_BACKUP_ACK				0x8112

//��ȡ���еı���
#define ISMS_GET_BACKUP_DATA_REQ				0x8113
#define ISMS_GET_BACKUP_DATA_ACK				0x8114

//�ָ����ݿ�
#define ISMS_RESTORE_DATABASE_REQ				0x8115
#define ISMS_RESTORE_DATABASE_ACK				0x8116

//ɾ����������
#define ISMS_DELETE_BACKUP_DATA_REQ 			0x8117
#define ISMS_DELETE_BACKUP_DATA_ACK 			0x8118

//����ϵͳʱ��
#define ISMS_SET_SYSTEMTIME_REQ					0x8119
#define ISMS_SET_SYSTEMTIME_ACK					0x811A

//��ȡ��ͼ�ڵ���Ϣ
#define ISMS_GET_MAPLEAF_REQ					0x811B
#define ISMS_GET_MAPLEAF_ACK					0x811C

#define ISMS_UPT_TALK_LOG_REQ						0x8121
#define ISMS_UPT_TALK_LOG_ACK						0x8122

#define ISMS_GET_TALK_LOG_REQ						0x8123
#define ISMS_GET_TALK_LOG_ACK						0x8124


#pragma region IPGS��������
//���ݷ��� : ����ͻ���----> SMS---->�����ŷ�
#define IPGS_SERVO_LOGIN_REQ						0x9001
#define IPGS_SERVO_LOGIN_ACK						0x9002

// ����������
//���ݷ��� : ����ͻ���----> SMS---->�����ŷ�
#define IPGS_SERVO_GET_SERVER_REQ					0x9003
#define IPGS_SERVO_GET_SERVER_ACK					0x9004

//���ݷ��� : ����ͻ���----> SMS---->�����ŷ�
#define IPGS_SERVO_SET_SERVER_REQ					0x9005
#define IPGS_SERVO_SET_SERVER_ACK					0x9006

// ��������
//���ݷ��� : �����ŷ�----> SMS---->����ͻ���
#define IPGS_SERVO_GET_SERVICE_REQ					0x9007
#define IPGS_SERVO_GET_SERVICE_ACK					0x9008

//���ݷ��� : �����ŷ�----> SMS---->����ͻ���
#define IPGS_SERVO_SET_SERVICE_REQ					0x9009
#define IPGS_SERVO_SET_SERVICE_ACK					0x900a

// ϵͳ����
//���ݷ��� : ����ͻ���----> SMS---->�����ŷ�
#define IPGS_SERVO_GET_SYSTEM_REQ					0x900b
#define IPGS_SERVO_GET_SYSTEM_ACK					0x900c

//���ݷ��� : ����ͻ���----> SMS---->�����ŷ�
#define IPGS_SERVO_SET_SYSTEM_REQ					0x900d
#define IPGS_SERVO_SET_SYSTEM_ACK					0x900e

// �û�����
//���ݷ��� : ����ͻ���----> SMS---->�����ŷ�
#define IPGS_SERVO_GET_USER_REQ						0x900f
#define IPGS_SERVO_GET_USER_ACK						0x9010

//���ݷ��� : ����ͻ���----> SMS---->�����ŷ�
#define IPGS_SERVO_SET_USER_REQ						0x9011
#define IPGS_SERVO_SET_USER_ACK						0x9012

// �û�ӳ������
//���ݷ��� : ����ͻ���----> SMS---->�����ŷ�
#define IPGS_SERVO_GET_USERMAP_REQ					0x9013
#define IPGS_SERVO_GET_USERMAP_ACK 					0x9014

//���ݷ��� : ����ͻ���----> SMS---->�����ŷ�
#define IPGS_SERVO_SET_USERMAP_REQ					0x9015
#define IPGS_SERVO_SET_USERMAP_ACK					0x9016

// ������������
//���ݷ��� : ����ͻ���----> SMS---->�����ŷ�
#define IPGS_SERVO_GET_OPTYPE_REQ					0x9017
#define IPGS_SERVO_GET_OPTYPE_ACK 					0x9018
#pragma endregion

// ǰ���豸Уʱ
#define	ISMS_CLIENT_2_SMS_ADJUST_DEV_TIME_REQ		0x9019
#define	ISMS_CLIENT_2_SMS_ADJUST_DEV_TIME_ACK		0x901A

// ��ȡ�豸¼��״̬
#define	ISMS_CLIENT_2_SMS_GET_DEV_RECORD_STATE_INFO_REQ		0x901B
#define	ISMS_CLIENT_2_SMS_GET_DEV_RECORD_STATE_INFO_ACK		0x901C


// ����ϵͳ����֪ͨ
#define ISMS_DOMAIN_MEMBER_UPDATE_NOTIFY			0X901F

// ��ȡ������Ǩ�����Ա��Ϣ
#define ISMS_GET_TRANSFER_DOMAIN_MEMBER_REQ			0X9020
#define ISMS_GET_TRANSFER_DOMAIN_MEMBER_ACK			0X9021

#pragma region �ൺ������Ŀ����궨��

// ���Ӱ�����
#define ISMS_CLIENT_2_SMS_RELIEVEVALIDATE_REQ		0X9022
#define ISMS_CLIENT_2_SMS_RELIEVEVALIDATE_ACK		0X9023

// ͨ����Ϣ֪ͨ
#define ISMS_NOTICE_INFO_NOTIFY						0x901e

// ���ü����Ϣ
#define ISMS_SET_SUPERVISE_INFO_REQ					0x9024
#define ISMS_SET_SUPERVISE_INFO_ACK					0x9025

// ��ѯ�����Ϣ
#define ISMS_GET_SUPERVISE_INFO_REQ             0x9026
#define ISMS_GET_SUPERVISE_INFO_ACK             0x9027

// ͨ����Ϣ֪ͨ
#define ISMS_NOTICE_INFO_NOTIFY						0x901e

// ���ü����Ϣ
#define ISMS_SET_SUPERVISE_INFO_REQ					0x9024
#define ISMS_SET_SUPERVISE_INFO_ACK					0x9025

// ��ѯ�����Ϣ
#define ISMS_GET_SUPERVISE_INFO_REQ					0x9026
#define ISMS_GET_SUPERVISE_INFO_ACK					0x9027

#pragma endregion
/*************************** ��������������� ********************************/
//��ѯ���д�����Ϣ 	���ݷ��� : ����ͻ���----> LNVRLServer
#define ILNVRL_QUERY_All_DISK_INFO_REQ							0x9028
#define ILNVRL_QUERY_All_DISK_INFO_ACK 							0x9029
//������������ 	���ݷ��� : ����ͻ���----> LNVRLServer
#define ILNVRL_CREATE_DISK_ARRAY_REQ							0x902a
#define ILNVRL_CREATE_DISK_ARRAY_ACK							0x902b
//��ѯ������Ϣ 	���ݷ��� : ����ͻ���----> LNVRLServer
#define ILNVRL_QUERY_DISK_ARRAY_STATUS_REQ						0x902c
#define ILNVRL_QUERY_DISK_ARRAY_STATUS_ACK 						0x902d

//ֹͣһ������ 	���ݷ��� : ����ͻ���----> LNVRLServer
#define ILNVRL_STOP_DISK_ARRAY_REQ							    0x902e
#define ILNVRL_STOP_DISK_ARRAY_ACK							    0x902f

//ʧЧ������һ������ 	���ݷ��� : ����ͻ���----> LNVRLServer
#define ILNVRL_FAIL_DISK_IN_ARRAY_REQ							0x9030
#define ILNVRL_FAIL_DISK_IN_ARRAY_ACK							0x9031
//�Ƴ�������һ������ 	���ݷ��� : ����ͻ���----> LNVRLServer
#define ILNVRL_REMOVE_DISK_FROM_ARRAY_REQ						0x9032
#define ILNVRL_REMOVE_DISK_FROM_ARRAY_ACK 						0x9033
//��Ӵ��̵����У���ӱ����̣� 	���ݷ��� : ����ͻ���----> LNVRLServer
#define ILNVRL_ADD_DISK_TO_ARRAY_REQ							0x9034
#define ILNVRL_ADD_DISK_TO_ARRAY_ACK 							0x9035

//��������е�ԭ������Ϣ  ���ݷ���: ����ͻ���----> LNVRLServer
#define ILNVRL_CLEAR_ARRAY_INFO_IN_DISK_REQ						0x9036
#define ILNVRL_CLEAR_ARRAY_INFO_IN_DISK_ACK 					0x9037

//��������״̬���֪ͨ ���ݷ��� : LNVRLServer ---->  ����ͻ���
#define ILNVRL_EXTERNAL_MDADM_NOTFIY							0x9038


//�����̹�ע��Ϣ 	���ݷ��� : ����ͻ���----> LNVRLServer
#define ILNVRL_SET_CHEST_MARK_INFO_REQ							0x9040
#define ILNVRL_SET_CHEST_MARK_INFO_ACK 							0x9041

#define ISMS_CLIENT_2_SPS_GETRECTASK_STATUS_REQ     0x9044
#define ISMS_CLIENT_2_SPS_GETRECTASK_STATUS_ACK     0x9045
//����Ƶ
/*#pragma pack(push,1)*/
typedef struct tag_STBasicData
{
	//����Ƶ����������
	DWORD  wMainType;
	//����Ƶ������չ����
	DWORD  wExtType;
	//����Ƶ����������
	DWORD  wSubType;
	//iCMS ID
	GUID guid_ICMS;

	GUID guidStreamFlag;

	//�豸ID
	DWORD dwDeviceID;
	//���豸ID��ͨ������etc��
	DWORD dwSubDeviceID;
	//������ʼʱ��.   100ns
	ULONGLONG llBeginTime;          
	//�������ʱ��. 100ns
	ULONGLONG llRelativeTimeTick;

	union 
	{
		struct
		{
			int nWidth;
			int nHeight;
			double dFps;     
			DWORD dwBitrate; //bitrate,  bps
		}Basic_VideoInfo;

		struct 
		{
			int nFrequency;
			BYTE cChannel;
			BYTE cBitcount;
			DWORD dwBitrate;//bitrate,  bps
		}Basic_AudioIfno;

	}Basic_MediaInfo;

	//���ݰ���С
	DWORD dwTotalDataSize;
	//����ָ��
	BYTE* pData;

	WORD wPrivateType;           //˽����������
	DWORD dwPrivateDataSize;     //˽�����ݴ�С
	BYTE* pPrivateData;			 //˽������ָ��

	DWORD dwPanPosition;		//�����ˮƽλ��
	DWORD dwTiltPosition;		//�������ֱλ��
	DWORD dwZoomScale;			//��ͷ����


	DWORD dwReserved0;
	DWORD dwReserved1;

	tag_STBasicData()
	{
		wMainType		= ICMS_DEFINE_TYPE_NONE;
		wExtType		= ICMS_DEFINE_TYPE_NONE;
		wSubType		= ICMS_DEFINE_TYPE_NONE;
		guid_ICMS		= GUID_NULL;
		guidStreamFlag	= GUID_NULL;
		dwDeviceID		= 0;
		dwSubDeviceID	= 0;
		llBeginTime		= 0;          
		llRelativeTimeTick = 0;

		memset(&Basic_MediaInfo, 0, sizeof(Basic_MediaInfo));

		
		pData				= NULL;
		dwTotalDataSize		= 0;
		pPrivateData		= NULL;
		dwPrivateDataSize	= 0;  
		wPrivateType		= 0;
		

		dwPanPosition	= 0;	
		dwTiltPosition	= 0;	
		dwZoomScale		= 0;

		dwReserved0 = 0;
		dwReserved1 = 0;
	}

	~tag_STBasicData()
	{
		if (pData)
			delete[] pData;
		pData = NULL;

		if (pPrivateData)
			delete[] pPrivateData;
		pPrivateData = NULL;

		dwPrivateDataSize = 0;
		dwTotalDataSize = 0;
	}
	tag_STBasicData(const tag_STBasicData& src)
	{
		wMainType = src.wMainType;
		wExtType = src.wExtType;
		wSubType = src.wSubType;
		memcpy(&guid_ICMS, &src.guid_ICMS,sizeof(guid_ICMS));
		memcpy(&guidStreamFlag, &src.guidStreamFlag,sizeof(guidStreamFlag));
		dwDeviceID = src.dwDeviceID;
		dwSubDeviceID = src.dwSubDeviceID;
		llBeginTime = src.llBeginTime;
		llRelativeTimeTick = src.llRelativeTimeTick;
		memcpy(&Basic_MediaInfo, &src.Basic_MediaInfo, sizeof(Basic_MediaInfo));
		pData			= NULL;
		dwTotalDataSize	= 0;
		pPrivateData	= NULL;
		dwPrivateDataSize=0;
// 		if(pData)
// 		{
// 			delete []pData;
// 			pData = NULL;
// 		}
		if(src.dwTotalDataSize > 0)
		{
			pData = new BYTE[src.dwTotalDataSize];
			dwTotalDataSize = src.dwTotalDataSize;
			memcpy(pData, src.pData, dwTotalDataSize);
		}
		
		wPrivateType = src.wPrivateType;
// 		if(pPrivateData)
// 		{
// 			delete []pPrivateData;
// 			pPrivateData = NULL;
// 		}
		if(src.dwPrivateDataSize > 0)
		{
			pPrivateData = new BYTE[src.dwPrivateDataSize];
			dwPrivateDataSize = src.dwPrivateDataSize;
			memcpy(pPrivateData, src.pPrivateData, dwPrivateDataSize);	
		}
		
		dwPanPosition = src.dwPanPosition;	
		dwTiltPosition = src.dwTiltPosition;	
		dwZoomScale = src.dwZoomScale;

		dwReserved0 = src.dwReserved0;
		dwReserved1 = src.dwReserved1;
	}

	tag_STBasicData& tag_STBasicData::operator =(const tag_STBasicData& src)
	{
		wMainType = src.wMainType;
		wExtType = src.wExtType;
		wSubType = src.wSubType;
		memcpy(&guid_ICMS, &src.guid_ICMS,sizeof(guid_ICMS));
		memcpy(&guidStreamFlag, &src.guidStreamFlag,sizeof(guidStreamFlag));
		dwDeviceID = src.dwDeviceID;
		dwSubDeviceID = src.dwSubDeviceID;
		llBeginTime = src.llBeginTime;
		llRelativeTimeTick = src.llRelativeTimeTick;
		memcpy(&Basic_MediaInfo, &src.Basic_MediaInfo, sizeof(Basic_MediaInfo));

		if(pData)
		{
			delete []pData;
			pData = NULL;
		}
		
		if(src.dwTotalDataSize > 0)
		{
			pData = new BYTE[src.dwTotalDataSize];
			dwTotalDataSize = src.dwTotalDataSize;
			memcpy(pData, src.pData, dwTotalDataSize);	
		}
		

		wPrivateType = src.wPrivateType;
		if(pPrivateData)
		{
			delete []pPrivateData;
			pPrivateData = NULL;
		}
		if(src.dwPrivateDataSize)
		{
			pPrivateData = new BYTE[src.dwPrivateDataSize];
			dwPrivateDataSize = src.dwPrivateDataSize;
			memcpy(pPrivateData, src.pPrivateData, dwPrivateDataSize);	
		}		

		dwPanPosition = src.dwPanPosition;	
		dwTiltPosition = src.dwTiltPosition;	
		dwZoomScale = src.dwZoomScale;

		dwReserved0 = src.dwReserved0;
		dwReserved1 = src.dwReserved1;

		return *this;
	}

	int tag_STBasicData::Serialize(CArchive& ar)
	{
		try
		{
			if(ar.IsStoring())
			{
				ar << wMainType;
				ar << wExtType;
				ar << wSubType;
				ar.Write(&guid_ICMS,sizeof(guid_ICMS));
				ar.Write(&guidStreamFlag,sizeof(guidStreamFlag));
				ar << dwDeviceID;
				ar << dwSubDeviceID;
				ar.Write(&llBeginTime, sizeof(llBeginTime));
				ar.Write(&llRelativeTimeTick, sizeof(llRelativeTimeTick));

				ar.Write(&Basic_MediaInfo, sizeof(Basic_MediaInfo));

				ar << dwTotalDataSize;
				if (dwTotalDataSize > 0)
				{
					ar.Write(pData, dwTotalDataSize);
				}

				ar << wPrivateType;
				ar << dwPrivateDataSize;
				if (dwPrivateDataSize > 0)
				{
					ar.Write(pPrivateData, dwPrivateDataSize);
				}
	
				ar << dwPanPosition;
				ar << dwTiltPosition;
				ar << dwZoomScale;

				ar << dwReserved0;
				ar << dwReserved1;
			}
			else if(ar.IsLoading())
			{
				ar >> wMainType;
				ar >> wExtType;
				ar >> wSubType;
				ar.Read(&guid_ICMS, sizeof(guid_ICMS));
				ar.Read(&guidStreamFlag, sizeof(guidStreamFlag));
				ar >> dwDeviceID;
				ar >> dwSubDeviceID;
				ar.Read(&llBeginTime, sizeof(llBeginTime));
				ar.Read(&llRelativeTimeTick, sizeof(llRelativeTimeTick));

				ar.Read(&Basic_MediaInfo, sizeof(Basic_MediaInfo));

				ar >> dwTotalDataSize;
				if(pData)
				{
					delete []pData;
					pData = NULL;
				}
				if (dwTotalDataSize > 0)
				{
					pData = new BYTE[dwTotalDataSize];
					ar.Read(pData, dwTotalDataSize);
				}
				ar >> wPrivateType;
				ar >> dwPrivateDataSize;
				if(pPrivateData)
				{
					delete []pPrivateData;
					pPrivateData = NULL;
				}
				if (dwPrivateDataSize > 0)
				{
					pPrivateData = new BYTE[dwPrivateDataSize];
					ar.Read(pPrivateData, dwPrivateDataSize);
				}
				ar >> dwPanPosition;
				ar >> dwTiltPosition;
				ar >> dwZoomScale;

				ar >> dwReserved0;
				ar >> dwReserved1;
			}
		}
		catch(...)
		{
			//OutputDebugString(_T("STBasicData::Serialize Exception!"));
		}
		return TRUE;
	}

}ST_ICMSBASIC_DATA;
/*#pragma pack(pop)*/
///end of struct

//Ԫ����Ŀ����Ϣ����
typedef struct tag_STMetaObjectInfo
{
	//��ǰĿ�����ݿ�ʼ
	LONG lBeginFlag;
	//�˶�Ŀ��ID
	LONG lObjectID;
	//�˶�Ŀ������
	LONG lObjectType;
	//Ŀ��ͼ����������
	CArray<BYTE,BYTE> arObjectInfo;
	//Ŀ��ͼ���������Ϣ
	CString strObjectInfo;
	//Ŀ��X����
	LONG lXPosition;
	//Ŀ��Y����
	LONG lYPosition;
	//Ŀ��Z����
	LONG lZPosition;
	//Ŀ����
	LONG lWidth;
	//Ŀ��߶�
	LONG lHeight;
	//Ŀ����
	LONG lZLength;
	//�˶�Ŀ��X���ٶ�
	LONG lXSpeed;
	//�˶�Ŀ��Y���ٶ�
	LONG lYSpeed;
	//�˶�Ŀ��Z���ٶ�
	LONG lZSpeed;
	//Ŀ�����ݽ������
	LONG lEndFlag;

	tag_STMetaObjectInfo()
	{
		lBeginFlag = 0;
		lObjectID = 0;
		lObjectType = 0;
		lXPosition = 0;
		lYPosition = 0;
		lZPosition = 0;
		lWidth = 0;
		lHeight = 0;
		lZLength = 0;
		lXSpeed = 0;
		lYSpeed = 0;
		lZSpeed = 0;
		lEndFlag = 0;
	}
	~tag_STMetaObjectInfo()
	{

	}
	tag_STMetaObjectInfo(tag_STMetaObjectInfo &src)
	{
		lBeginFlag = src.lBeginFlag;
		lObjectID = src.lObjectID;
		lObjectType = src.lObjectType;

		DWORD dwObjectInfoCount = src.arObjectInfo.GetCount();
		for (DWORD i =0; i<dwObjectInfoCount; i++)
		{
			BYTE byElem = src.arObjectInfo[i];
			arObjectInfo.Add(byElem);
		}

		strObjectInfo = src.strObjectInfo;
		lXPosition = src.lXPosition;
		lYPosition = src.lYPosition;
		lZPosition = src.lZPosition;
		lWidth = src.lWidth;
		lHeight = src.lHeight;
		lZLength = src.lZLength;
		lXSpeed = src.lXSpeed;
		lYSpeed = src.lYSpeed;
		lZSpeed = src.lZSpeed;
		lEndFlag = src.lEndFlag;

	}

	tag_STMetaObjectInfo& tag_STMetaObjectInfo::operator = (tag_STMetaObjectInfo &src)
	{
		lBeginFlag = src.lBeginFlag;
		lObjectID = src.lObjectID;
		lObjectType = src.lObjectType;

		DWORD dwObjectInfoCount = src.arObjectInfo.GetCount();
		for (DWORD i =0; i<dwObjectInfoCount; i++)
		{
			BYTE byElem = src.arObjectInfo[i];
			arObjectInfo.Add(byElem);
		}

		strObjectInfo = src.strObjectInfo;
		lXPosition = src.lXPosition;
		lYPosition = src.lYPosition;
		lZPosition = src.lZPosition;
		lWidth = src.lWidth;
		lHeight = src.lHeight;
		lZLength = src.lZLength;
		lXSpeed = src.lXSpeed;
		lYSpeed = src.lYSpeed;
		lZSpeed = src.lZSpeed;
		lEndFlag = src.lEndFlag;
		return *this;

	}


	int tag_STMetaObjectInfo::Serialize(CArchive& ar)
	{
		try
		{
			if (ar.IsStoring())
			{
				ar<<lBeginFlag;
				ar<<lObjectID;
				ar<<lObjectType;
				DWORD dwObjectInfoCount = arObjectInfo.GetCount();
				ar<<dwObjectInfoCount;
				for (DWORD i =0; i<dwObjectInfoCount; i++)
				{
					ar<<arObjectInfo[i];
				}
				ar<<strObjectInfo;
				ar<<lXPosition;
				ar<<lYPosition;
				ar<<lZPosition;
				ar<<lWidth;
				ar<<lHeight;
				ar<<lZLength;
				ar<<lXSpeed;
				ar<<lYSpeed;
				ar<<lZSpeed;
				ar<<lEndFlag;
			} 
			else
			{
				ar>>lBeginFlag;
				ar>>lObjectID;
				ar>>lObjectType;
				DWORD dwObjectInfoCount = 0;
				ar>>dwObjectInfoCount;
				for (DWORD i =0; i<dwObjectInfoCount; i++)
				{
					BYTE byElem = 0;
					ar>>byElem;
					arObjectInfo.Add(byElem);
				}
				ar>>strObjectInfo;
				ar>>lXPosition;
				ar>>lYPosition;
				ar>>lZPosition;
				ar>>lWidth;
				ar>>lHeight;
				ar>>lZLength;
				ar>>lXSpeed;
				ar>>lYSpeed;
				ar>>lZSpeed;
				ar>>lEndFlag;
			}
		}
		catch (...)
		{
			AfxMessageBox(_T("ST_ICMSMETA_OBJECTINFO::Serialize Exception!"));
		}
		return 1;
	}
}ST_ICMSMETA_OBJECTINFO;

//Ԫ�����¼���Ϣ����
typedef struct tag_STMetaEventInfo
{
	//��ʼ���
	LONG lBeginFlag;
	//����ID
	LONG lEventID;
	//��������
	LONG lEventType;
	//�����¼���������
	CArray<BYTE,BYTE> arEventInfo;
	//��ǰ�¼������趨����
	CArray<BYTE,BYTE> arEventRuleInfo;
	//��������
	CString strEventInfo;
	//������ʱ�����
	LONGLONG llMarkInTime;
	//��������ʱ��
	LONGLONG llEventTime;
	//������ʱ�����
	LONGLONG llMarkOutTime;
	//����׼ȷ��
	float fReliability;
	//Ŀ��ID�б�
	CArray<LONG,LONG> arObjcetID;
	//�������
	LONG lEndFlag;

	tag_STMetaEventInfo()
	{
		lBeginFlag = 0;
		lEventID = 0;
		lEventType = 0;
		llMarkInTime = 0;
		llEventTime = 0;
		llMarkOutTime = 0;
		fReliability = 0;
		lEndFlag = 0;
	}
	~tag_STMetaEventInfo()
	{

	}
	tag_STMetaEventInfo(tag_STMetaEventInfo &src)
	{
		lBeginFlag = src.lBeginFlag;
		lEventID = src.lEventID;
		lEventType = src.lEventType;

		DWORD dwEventInfoCount = src.arEventInfo.GetCount();
		for (DWORD i =0; i < dwEventInfoCount; i++)
		{
			BYTE byElem = src.arEventInfo[i];
			arEventInfo.Add(byElem);
		}

		DWORD dwEventRuleInfoCount = src.arEventRuleInfo.GetCount();
		for (DWORD i =0; i < dwEventRuleInfoCount; i++)
		{
			BYTE byElem = src.arEventRuleInfo[i];
			arEventRuleInfo.Add(byElem);
		}

		strEventInfo = src.strEventInfo;
		llMarkInTime = src.llMarkInTime;
		llEventTime = src.llEventTime;
		llMarkOutTime = src.llMarkOutTime;
		fReliability = src.fReliability;
		
		DWORD dwObjcetIDCount = src.arObjcetID.GetCount();
		for (DWORD i =0; i < dwObjcetIDCount; i++)
		{
			LONG lElem = src.arObjcetID[i];
			arObjcetID.Add(lElem);
		}
		lEndFlag = src.lEndFlag;
	}

	tag_STMetaEventInfo& tag_STMetaEventInfo::operator = (tag_STMetaEventInfo &src)
	{
		lBeginFlag = src.lBeginFlag;
		lEventID = src.lEventID;
		lEventType = src.lEventType;

		DWORD dwEventInfoCount = src.arEventInfo.GetCount();
		for (DWORD i =0; i < dwEventInfoCount; i++)
		{
			BYTE byElem = src.arEventInfo[i];
			arEventInfo.Add(byElem);
		}

		DWORD dwEventRuleInfoCount = src.arEventRuleInfo.GetCount();
		for (DWORD i =0; i < dwEventRuleInfoCount; i++)
		{
			BYTE byElem = src.arEventRuleInfo[i];
			arEventRuleInfo.Add(byElem);
		}

		strEventInfo = src.strEventInfo;
		llMarkInTime = src.llMarkInTime;
		llEventTime = src.llEventTime;
		llMarkOutTime = src.llMarkOutTime;
		fReliability = src.fReliability;

		DWORD dwObjcetIDCount = src.arObjcetID.GetCount();
		for (DWORD i =0; i < dwObjcetIDCount; i++)
		{
			LONG lElem = src.arObjcetID[i];
			arObjcetID.Add(lElem);
		}
		lEndFlag = src.lEndFlag;
		return *this;

	}

	int tag_STMetaEventInfo::Serialize(CArchive& ar)
	{
		try
		{
			if (ar.IsStoring())
			{
				ar<<lBeginFlag;
				ar<<lEventID;
				ar<<lEventType;

				DWORD dwEventInfoCount = arEventInfo.GetCount();
				ar<<dwEventInfoCount;
				for (DWORD i =0; i < dwEventInfoCount; i++)
				{
					BYTE byElem = arEventInfo[i];
					ar<<byElem;
				}

				DWORD dwEventRuleInfoCount = arEventRuleInfo.GetCount();
				ar<<dwEventRuleInfoCount;
				for (DWORD i =0; i < dwEventRuleInfoCount; i++)
				{
					BYTE byElem = arEventRuleInfo[i];
					ar<<byElem;
				}
				ar<<strEventInfo;
				ar<<llMarkInTime;
				ar<<llEventTime;
				ar<<llMarkOutTime;
				ar<<fReliability;

				DWORD dwObjcetIDCount = arObjcetID.GetCount();
				ar<<dwObjcetIDCount;
				for (DWORD i =0; i < dwObjcetIDCount; i++)
				{
					LONG lElem = arObjcetID[i];
					ar<<lElem;
				}

				ar<<lEndFlag;
			} 
			else
			{
				ar>>lBeginFlag;
				ar>>lEventID;
				ar>>lEventType;

				DWORD dwEventInfoCount = 0;
				ar>>dwEventInfoCount;
				for (DWORD i =0; i < dwEventInfoCount; i++)
				{
					BYTE byElem = 0;
					ar>>byElem;
					arEventInfo.Add(byElem);
				}

				DWORD dwEventRuleInfoCount = 0;
				ar>>dwEventRuleInfoCount;
				for (DWORD i =0; i < dwEventRuleInfoCount; i++)
				{
					BYTE byElem = 0;
					ar>>byElem;
					arEventRuleInfo.Add(byElem);
				}
				ar>>strEventInfo;
				ar>>llMarkInTime;
				ar>>llEventTime;
				ar>>llMarkOutTime;
				ar>>fReliability;

				DWORD dwObjcetIDCount = 0;
				ar>>dwObjcetIDCount;
				for (DWORD i =0; i < dwObjcetIDCount; i++)
				{
					LONG lElem = 0;
					ar>>lElem;
					arObjcetID.Add(lElem);
				}
				ar>>lEndFlag;
			}
		}
		catch (...)
		{
			AfxMessageBox(_T("ST_ICMSMETA_EVENTINFO::Serialize Exception!"));
		}
		return 1;
	}
}ST_ICMSMETA_EVENTINFO;

//Ԫ���ݶ���
typedef struct tag_STMetaData
{ 
	//��ǰԪ���ݵĿ�ʼ���
	LONG lBeginFlag;
	//ͨ����
	LONG lChannel;
	//��ǰԪ���ݵĲ���ʱ��
	LONGLONG llBeginTime;
	//�Ŀ�����
	LONG lObjectNum;
	//�Ŀ�����Ϣ
	CArray<ST_ICMSMETA_OBJECTINFO*, ST_ICMSMETA_OBJECTINFO*> arObjectInfo;
	//��������
	LONG lEventNum;
	//������Ϣ
	CArray<ST_ICMSMETA_EVENTINFO*, ST_ICMSMETA_EVENTINFO*> arEventInfo;
	//Ԫ���ݰ��������
	LONG lEndFlag;

	tag_STMetaData()
	{
		lBeginFlag = 0;
		lChannel = 0;
		llBeginTime = 0;
		lObjectNum = 0;
		lEventNum = 0;
		lEndFlag = 0;
	}
	~tag_STMetaData()
	{
		ReleaseResource();
	}

	tag_STMetaData(tag_STMetaData &src)
	{
		lBeginFlag = src.lBeginFlag;
		lChannel = src.lChannel;
		llBeginTime = src.llBeginTime;
		lObjectNum =src.lObjectNum;

		ASSERT(src.lObjectNum == src.arObjectInfo.GetCount());
		for (WORD nCount = 0; nCount < lObjectNum; nCount++)
		{
			ST_ICMSMETA_OBJECTINFO *pSrcObjectInfo = src.arObjectInfo[nCount];
			ST_ICMSMETA_OBJECTINFO *pObjectInfo = new ST_ICMSMETA_OBJECTINFO;
			memcpy(pObjectInfo, pSrcObjectInfo, sizeof(ST_ICMSMETA_OBJECTINFO));
			arObjectInfo.Add(pObjectInfo);
		}
		lEventNum = src.lEventNum;

		ASSERT(src.lEventNum == src.arEventInfo.GetCount());
		for (WORD nCount = 0; nCount < lEventNum; nCount++)
		{
			ST_ICMSMETA_EVENTINFO *pSrcEventInfo = src.arEventInfo[nCount];
			ST_ICMSMETA_EVENTINFO *pEventInfo = new ST_ICMSMETA_EVENTINFO;
			memcpy(pEventInfo, pSrcEventInfo, sizeof(ST_ICMSMETA_EVENTINFO));
			arEventInfo.Add(pEventInfo);
		}

		lEndFlag = src.lEndFlag;
	}
	
	tag_STMetaData& tag_STMetaData::operator = (tag_STMetaData &src)
	{
		lBeginFlag = src.lBeginFlag;
		lChannel = src.lChannel;
		llBeginTime = src.llBeginTime;
		lObjectNum =src.lObjectNum;

		ReleaseResource();

		ASSERT(src.lObjectNum == src.arObjectInfo.GetCount());
		for (WORD nCount = 0; nCount < lObjectNum; nCount++)
		{
			ST_ICMSMETA_OBJECTINFO *pSrcObjectInfo = src.arObjectInfo[nCount];
			ST_ICMSMETA_OBJECTINFO *pObjectInfo = new ST_ICMSMETA_OBJECTINFO;
			memcpy(pObjectInfo, pSrcObjectInfo, sizeof(ST_ICMSMETA_OBJECTINFO));
			arObjectInfo.Add(pObjectInfo);
		}
		lEventNum = src.lEventNum;

		ASSERT(src.lEventNum == src.arEventInfo.GetCount());
		for (WORD nCount = 0; nCount < lEventNum; nCount++)
		{
			ST_ICMSMETA_EVENTINFO *pSrcEventInfo = src.arEventInfo[nCount];
			ST_ICMSMETA_EVENTINFO *pEventInfo = new ST_ICMSMETA_EVENTINFO;
			memcpy(pEventInfo, pSrcEventInfo, sizeof(ST_ICMSMETA_EVENTINFO));
			arEventInfo.Add(pEventInfo);
		}

		lEndFlag = src.lEndFlag;

		return *this;
	}

	int tag_STMetaData::Serialize(CArchive& ar)
	{
		try
		{
			if (ar.IsStoring())
			{
				ar<<lBeginFlag;
				ar<<lChannel;
				ar<<llBeginTime;
				ar<<lObjectNum;

				ASSERT(lObjectNum == arObjectInfo.GetCount());
				for (WORD nCount = 0; nCount < lObjectNum; nCount++)
				{
					ST_ICMSMETA_OBJECTINFO *pObjectInfo = arObjectInfo[nCount];
					pObjectInfo->Serialize(ar);
				}

				ar<<lEventNum;

				ASSERT(lEventNum == arEventInfo.GetCount());
				for (WORD nCount = 0; nCount < lEventNum; nCount++)
				{
					ST_ICMSMETA_EVENTINFO *pEventInfo = arEventInfo[nCount];
					pEventInfo->Serialize(ar);
				}
				ar<<lEndFlag;
			} 
			else
			{
				ReleaseResource();

				ar>>lBeginFlag;
				ar>>lChannel;
				ar>>llBeginTime;
				ar>>lObjectNum;
				//ASSERT(lObjectNum == arObjectInfo.GetCount());

				for (WORD nCount = 0; nCount < lObjectNum; nCount++)
				{
					ST_ICMSMETA_OBJECTINFO *pObjectInfo = new ST_ICMSMETA_OBJECTINFO;
					pObjectInfo->Serialize(ar);
					arObjectInfo.Add(pObjectInfo);
				}

				ar>>lEventNum;
				//ASSERT(lEventNum == arEventInfo.GetCount());

				for (WORD nCount = 0; nCount < lEventNum; nCount++)
				{
					ST_ICMSMETA_EVENTINFO *pEventInfo = new ST_ICMSMETA_EVENTINFO;
					pEventInfo->Serialize(ar);
					arEventInfo.Add(pEventInfo);
				}

				ar>>lEndFlag;
			}
		}
		catch (...)
		{
			AfxMessageBox(_T("ST_ICMSMETA_DATA::Serialize Exception!"));
		}
		return 1;
	}

	void tag_STMetaData::ReleaseResource()
	{
		ASSERT(lObjectNum == arObjectInfo.GetCount());
		for (WORD nCount = 0; nCount < lObjectNum; nCount++)
		{
			ST_ICMSMETA_OBJECTINFO *pObjectInfo = arObjectInfo[nCount];
			delete pObjectInfo;
			delete arObjectInfo[nCount];
		}
		arObjectInfo.RemoveAll();

		ASSERT(lEventNum == arEventInfo.GetCount());
		for (WORD nCount = 0; nCount < lEventNum; nCount++)
		{
			ST_ICMSMETA_EVENTINFO *pEventInfo = arEventInfo[nCount];
			delete pEventInfo;
			delete arEventInfo[nCount];
		}
		arEventInfo.RemoveAll();
	}
}ST_ICMSMETA_DATA;

#endif

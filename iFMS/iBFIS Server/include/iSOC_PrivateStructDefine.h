#pragma once
#include "iSOC_Datatype_Define.h"

//////////////////////////////////////
//�������Ͷ���
//////////////////////////////////////

////////////////////////////��ؿͻ���////////////////////////////////////////////////

#define OBJECT_TYPE_FACTORY				(1)		//��������
#define OBJECT_TYPE_ORGAN_SET			(5)		//��֯��������
#define OBJECT_TYPE_MCSERVERPEER		(6)		//��������Դ����
#define	OBJECT_TYPE_RIGHT_JUDGE			(7)		//Ȩ���ж϶���
#define OBJECT_TYPE_CALLBACK_MANAGER	(8)		//�ص��������
#define OBJECT_TYPE_NORMAL_STRUCT		(9)		//һ��ṹ�����
#define OBJECT_TYPE_THREAD				(10)	//�̶߳���
#define	OBJECT_TYPE_THREADPOOL			(11)	//�̳߳ض���
#define OBJECT_TYPE_ALARMSERVERPEER		(12)	//����������Դ����
#define OBJECT_TYPE_VODFILEMANAGEMENT	(13)	//VOD�ļ��������
#define	OBJECT_TYPE_VIDEORENDER			(14)    //��Ƶ��Ⱦ����
#define OBJECT_TYPE_AUDIORENDER			(15)    //��Ƶ��Ⱦ����
#define OBJECT_TYPE_VIDEOCODEC			(16)    //��Ƶ�����������
#define OBJECT_TYPE_VIDEODECODE			(17)    //��Ƶ����������
#define OBJECT_TYPE_VIDEOENCODE			(18)	//��Ƶ����������
#define OBJECT_TYPE_AUDIOCODEC			(19)	//��Ƶ�����������
#define OBJECT_TYPE_AUDIODECODE			(20)	//��Ƶ����������
#define OBJECT_TYPE_AUDIOENCODE			(21)	//��Ƶ����������
#define OBJECT_TYPE_TIMER				(22)	//��ʱ������
#define OBJECT_TYPE_REALSTREAMSOURCE	(23)	//ʵʱ��Դ����
#define OBJECT_TYPE_VODSTREAMSOURCE		(24)	//VOD��Դ����
#define OBJECT_TYPE_MAPSOURCE			(25)	//��ͼ����Դ����
#define OBJECT_TYPE_EMAPSOURCE			(26)	//���ӵ�ͼ����Դ���� 
#define OBJECT_TYPE_GISSOURCE			(27)	//gis����Դ����
#define OBJECT_TYPE_REALSTATION			(28)	//ʵʱStation����
#define OBJECT_TYPE_VODSTATION			(29)	//VOD station����
#define OBJECT_TYPE_FILEEXPORT			(30)	//�ļ���������
#define OBJECT_TYPE_FILEMIGRATESOURCE	(31)	//�ļ�Ǩ��Դ����
#define OBJECT_TYPE_DATALIST			(32)	//��������������
#define OBJECT_TYPE_DEVICEAUDIOTALK		(33)	//�豸�����Խ�����
#define OBJECT_TYPE_MONITORAUDIOTALK	(34)	//�ͻ��������Խ�����
#define OBJECT_TYPE_DBOPERATOR			(35)	//�־û�����
#define OBJECT_TYPE_FILEUPLOAD			(36)	//�ļ��ϴ�����
#define	OBJECT_TYPE_FILEDOWNLOAD		(37)	//�ļ����ض���
#define OBJECT_TYPE_M2DTALKSOURCE		(38)	//�豸�Խ�Դ����
#define OBJECT_TYPE_M2MTALKSOURCE		(39)	//�ͻ��˶Խ�Դ����
#define OBJECT_TYPE_VODFILEQUERYSOURCE	(40)	//VOD��ѯԴ����
#define OBJECT_TYPE_HSFILEMANAGEMENT	(41)	//�����ļ��������
#define OBJECT_TYPE_PTZCONTROL			(42)	//PTZ���ƶ���
#define	OBJECT_TYPE_FILEDELETE			(43)	//�ļ�ɾ������
#define OBJECT_TYPE_FILEMIGRATESTATION  (44)	//�ļ�Ǩ��ҵ�����
#define OBJECT_TYPE_SYSTEMVOLUMECONTROL (45)	//ϵͳ�������ƶ��󣬰��������������������
#define OBJECT_TYPE_PRESETCREISESOURCE	(46)	//Ѳ��Ԥ�õ����Դ����
#define OBJECT_TYPE_MEDIADATAPROCESSOR	(47)	//ý�����ݴ�����
#define OBJECT_TYPE_GROUPLOOPMANAGER	(48)	//������Ѳ�������
#define OBJECT_TYPE_GLOBALLASTERROR		(49)	//ȫ�ִ�����������
#define OBJECT_TYPE_MATRIXCONTROLSTATION (50)	//����ǽ����ҵ�����
#define OBJECT_TYPE_MATRIXCONTROLSOURCE	(51)	//����ǽ����Դ����
#define OBJECT_TYPE_FILEEXPORTSOURCE	(55)	//�ļ�����Դ����
#define OBJECT_TYPE_SERVERTYPE_AUTO_IDENTIFIER	(100)	//�����������Զ�ʶ�����
#define OBJECT_TYPE_LINEAR				(101)	//���������
#define OBJECT_TYPE_D3DMANAGER			(102)	//D3D��������������Ӧ�ó���ֻ����һ��D3D��������Ҫʹ�ô˶�����������ط��ã�
#define OBJECT_TYPE_CODEINFOSTATION		(103)//��ȡ�����ʽ����
#define OBJECT_TYPE_CODEINFOSOURCE		(104)//��ȡ�����ʽԴ����
#define OBJECT_TYPE_FILEMIGRATESTATIONV2 (108) //��������Ǩ�Ƶ��µ�Ǩ�ƽӿڶ���
#define OBJECT_TYPE_FILEMIGRATESOURCEV2	 (109) //��������Ǩ�Ƶ��µ�Ǩ��Դ�ӿڶ���
#define OBJECT_TYPE_FILELOCKMANAGER		(110) //�ļ������������
#define OBJECT_TYPE_FILEMIGRATEMANSOURCE (111) //�ļ�Ǩ�ƹ���Դ����
#define OBJECT_TYPE_IMAGE_TRANSFORM     (112)   //ͼ���������
#define OBJECT_TYPE_FFMPEGCODECMAN		(113) //FFMPEG Codec�������
#define OBJECT_TYPE_NETWORKMONITOR		(114) //�����ض���
#define OBJECT_TYPE_TTSSTATION			(115) //������ҵ�����
#define OBJECT_TYPE_SUPERVISESTATION	(116)	//������station����
#define OBJECT_TYPE_DEVICECONTAINER		(117)   //�豸��������
#define OBJECT_TYPE_TALKBACKSTATION		(118)	//�Խ�����station����
#define OBJECT_TYPE_SUPERVISESOURCE		(119)	//������Դ����

////////////////////////////////////����ͻ���///////////////////////////////////

#define OBJECT_TYPE_MANMCSOURCE			(10001)    //��������Դ
#define OBJECT_TYPE_MANSYSSETSOURCE		(10002)	//ϵͳ����Դ
#define OBJECT_TYPE_MANSYSSETSTATION	(10003)	//ϵͳ����ҵ�����


////////////////////////////////////����ǽ���////////////////////////////////////

#define OBJECT_TYPE_MATRIXINFOMAN				(20088) //����ǽ��������Ϣ�������
#define OBJECT_TYPE_MATRIXINFOMAN_V2			(20089) //�µ���ǽ��������Ϣ������󣬲��ټ�����ǰ�ĵ���ǽ����ģʽ����Ҫ������ʹ����ǰ�ĵ���ǽ�������

////////////////////////////////////����ǽ������/////////////////////////////////
#define OBJECT_TYPE_TVWALL_LIVECTRLSTATION		(20001) //����ǽ������ʵʱ�ؼ�ҵ�����
#define OBJECT_TYPE_TVWALL_MAPCTRLSTATION		(20002) //����ǽ��������ͼ�ؼ�ҵ�����
#define OBJECT_TYPE_TVWALL_DATARECVSTATION		(20003) //����ǽ���������ݽ���ҵ�����
#define OBJECT_TYPE_TVWALL_MATRIXCTRLSOURCE		(20004)	//����ǽ���������ݲٿ�ҵ�����
#define OBJECT_TYPE_TVWALL_WINDOWMANAGERSOURCE	(20005) //����ǽ���������ڿؼ�ҵ�����
#define OBJECT_TYPE_TVWALL_WINDOWSFRAMESTATION  (20006) //����ǽ���������ڿ��ҵ�����
#define OBJECT_TYPE_TVWALL_MONITOROUTPUTMANAGER (20007) //����ǽ����������������������

///////////////////////////////////�������Ʒ��������////////////////////////////////
#define OBJECT_TYPE_DCSSERVER_TASK_MANAGER		               (40002) //�������Ʒ������������ҵ�����
#define OBJECT_TYPE_DCSSERVER_STATIONMANAGER		           (40005) //ҵ��������

///////////////////////////////////��������SDK���////////////////////////////////////

#define OBJECT_TYPE_DCS_DATA_SOURCE				(30000) //��������Դ����
#define OBJECT_TYPE_DCS_SOURCE					(30001) //��������Դ����
#define OBJECT_TYPE_DCS_CONTROL_STATION			(30002) //��������ҵ�����
#define OBJECT_DES_DCS_DATA_TYPE				"MySQL" //����ʵʱ��ʱ�طŵ��ļ�����

///////////////////////////////////�豸���SDK���////////////////////////////////////
#define OBJECT_TYPE_DEVICEPLUGIN_TALKBACK			(400001) //IP�Խ��豸�������
///////////////////////////////////BFIS Sync���////////////////////////////////////
#define OBJECT_TYPE_BFIS_DISPLAY_LOG_STATION			(600001)	//��־��ʾ����
#define OBJECT_TYPE_BFISSYNC_SERVER						(600002)	//ͬ������������
#define OBJECT_TYPE_BFISSYNC_CLIENT						(600003)	//ͬ���ͻ���
#define OBJECT_TYPE_BFISSYNC_DBOPERATORSOURCE			(600004)	//ͬ��ϵͳ���ݿ����
#define OBJECT_TYPE_BFISSYNC_LISTENSERVER               (600005)    //����˼�������
//////////////////////////////////BFIS Server���/////////////////////////////////////
#define OBJECT_TYPE_BFISSERVER_DBOPERATORSOURCE			(700001)	//����˶����ݿ��������
#define OBJECT_TYPE_BFISSERVER_CLIENTSOURCE				(700002)	//����˶Կͻ��˲�������	
#define OBJECT_TYPE_BFISSERVER_CACHESOURCE				(700003)	//����˶Ի����������
#define OBJECT_TYPE_BFIS_CLIENTCOMMUNICATION			(700004)	//�������ͻ���ͨ�Ŷ���
#define OBJECT_TYPE_BFIS_COMMUNICATESYNCSERVER			(700005)	//������ͬ�������������ͨ�ŵĶ���
#define OBJECT_TYPE_BFIS_TASKMANAGER					(700006)	//��������������� 
#define OBJECT_TYPE_BFIS_NOTIFYSOURCE					(700007)	//֪ͨ����
#define OBJECT_TYPE_BFISSERVER_MIGRATETASKSTATION       (700008)    //Ǩ�ƹ������
#define OBJECT_TYPE_BFISSERVER_NOTIFICATIONSTATION      (700009)    //֪ͨ�������
#define OBJECT_TYPE_BFISSERVER_MCOPERATESTATION         (700010)    //MC��������
#define OBJECT_TYPE_BFISSERVER_SERIALIZEDATAMEMORY      (700011)    //���������л����ݹ���(�ڴ淽ʽ)
//////////////////////////////////BFIS SDK���/////////////////////////////////////
#define OBJECT_TYPE_BFIS_BASE_STATION					(800001)	//����ҵ��Station
#define OBJECT_TYPE_BFIS_BASE_SOURCE					(800002)	//����ҵ��Source
#define OBJECT_TYPE_BFIS_BASE_PLUGIN					(800003)	//�������


//////////////////////////////////////����������������//////////////////////////////////////
#define OBJECT_DES_DEVICEPLUGIN_TALKBACK_SPON		"SPON"	//����Խ��豸�������


//////////////////////////////////////��ؿͻ���///////////////////////////////////////////////////////

#define OBJECT_DES_RENDER_D3D			"D3D_RENDER"    //d3d��Ⱦ����
#define OBJECT_DES_RENDER_GDI			"GDI_RENDER"	//GDI��Ⱦ����
#define OBJECT_DES_RENDER_DDRAW			"DDRAW_RENDER"	//ddraw��Ⱦ����

#define OBJECT_DES_DECODE_SH264			"SH264_DECODE"	//��׼h264��������
#define OBJECT_DES_DECODE_SMJPEG		"SMJPEG_DECODE"	//��׼MJPEG��������
#define OBJECT_DES_DECODE_SMPEG4		"SMPEG4_DECODE"	//��׼MPEG4��������
#define OBJECT_DES_DECODE_HKVISSION		"HKVISSION_DEOCDE"	//����˽�и�ʽ��������
#define OBJECT_DES_DECODE_DAHUA			"DAHUA_DECODE"	//��˽�и�ʽ��������
#define OBJECT_DES_DECODE_G711			"G711_DECODE"	//G711��Ƶ���ݽ�������
#define OBJECT_DES_DECODE_G726			"G726_DECODE"	//G726��Ƶ���ݽ�������

#define OBJECT_DES_ENCODE_SH264			"SH264_ENCODE"	//��׼h264��������
#define OBJECT_DES_ENCODE_SMJPEG		"SMJPEG_ENCODE"	//��׼MJPEG��������
#define OBJECT_DES_ENCODE_SMPEG4		"SMPEG4_ENCODE"	//��׼MPEG4��������
#define OBJECT_DES_ENCODE_HKVISSION		"HKVISSION_ENCODE"	//����˽�и�ʽ��������"
#define OBJECT_DES_ENCODE_DAHUA			"DAHUA_ENCODE"	//��˽�и�ʽ��������
#define OBJECT_DES_ENCODE_G711			"G711_ENCODE"	//G711��Ƶ���ݱ�������
#define OBJECT_DES_ENCODE_G726			"G726_ENCODE"	//G726��Ƶ���ݱ�������

#define OBJECT_DES_VODSOURCE_SBFILE		"SBFile_SOURCE" //VOD����SB�ļ�����
#define OBJECT_DES_VODSOURCE_RPBFILE	"RPBFile_SOURCE" //����ʵʱ��ʱ�طŵ��ļ�����
#define OBJECT_DES_VODSOURCE_GENERAL	"GENERAL_SOURCE" //һ��ý���ļ�Source����

#define OBJECT_DES_HSFILEMANAGEMENT_MEMFILEMAPPING "MEMFILEMAPPING"  //�����ļ������е��ڴ�ӳ���ļ�����
#define OBJECT_DES_HSFILEMANAGEMENT_REALCACHEFILE  "REALCACHEFILE"  //ʵʱ�����ļ�������֧�ּ�ʱ�ط�

#define OBJECT_DES_SYSTEMVOLUME_IN		"SYSTEM_VOLUME_IN"			//ϵͳ����������ʶ
#define OBJECT_DES_SYSTEMVOLUME_OUT		"SYSTEM_VOLUME_OUT"			//ϵͳ���������ʶ


////////////////////////////////////////����ͻ���//////////////////////////////////////////////////////////


struct ST_CallbackCacheInfo
{
	ISOC_VOID* pCallback;
	ISOC_DWORDPTR dwCookie;
	ISOC_DWORDPTR dwReserved1;
	ISOC_DWORDPTR dwReserved2;
	ST_CallbackCacheInfo() : pCallback(ISOC_NULL),dwCookie(0),dwReserved1(0),dwReserved2(0)
	{
	}

	ST_CallbackCacheInfo(const ST_CallbackCacheInfo& info)
	{
		pCallback = info.pCallback;
		dwCookie = info.dwCookie;
		dwReserved1 = info.dwReserved1;
		dwReserved2 = info.dwReserved2;
	}

	bool operator == (const ST_CallbackCacheInfo& info)const
	{
		if(this->pCallback == info.pCallback && this->dwCookie == info.dwCookie && this->dwReserved1 == info.dwReserved1 && this->dwReserved2 == info.dwReserved2)
			return true;
		else
			return false;
	}
};


#define  MAX_PIXELFMT_COUNT		(3)

////////////////////////////////////�����///////////////////////////////////////////////////

#define ISOC_GET_SETVER_TYPE_AND_VERSION_REQ 0x5051
#define ISOC_GET_SETVER_TYPE_AND_VERSION_ACK 0x5052

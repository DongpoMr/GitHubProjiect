#ifndef __ISOC_AVCODECMODULE_API_HEADER__
#define __ISOC_AVCODECMODULE_API_HEADER__

#include "iSOC_UnitDefine.h"
#include "iSOC_Datatype_Define.h"
#include "iSOC_PublicStructDefine.h"

#ifdef __cplusplus
extern "C"
{
#endif

/******************************************************************************************************************************
*��������iSOC_CreateAVCodec
*��  �ܣ������������
*��  ����
		[OUT]	lAVCodecSession �����ı�������Ự��ʶ
		[IN]	nCodecType		����������ͣ�0����Ƶ��������1����Ƶ��������2����Ƶ��������3����Ƶ������
		[IN]	strCodecDes		�������������������ֵΪ��ӦcodecID��ֵת�����ַ���
		[IN]	dwReserved		������
*����ֵ���ɹ���ʼ���򷵻ش���0��ֵ����ʼ�����ɹ��򷵻�С��0��ֵ
*��  ע��
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT	iSOC_CreateAVCodec(OUT ISOC_LONGPTR	*lAVCodecSession,IN ISOC_INT nCodecType,IN ISOC_STR strCodecDes,IN ISOC_DWORDPTR dwReserved=0);


/******************************************************************************************************************************
*��������iSOC_SetAVCodecParameters
*��  �ܣ����ý�����ѡ��
*��  ����
		[IN]	lAVCodecSession	��������Ự��ʶ
		[IN]	nCtrlCmd		���������������
				�μ���
				FLUSH_CODEC_BUFFER = 1,	// flush the codec(decode,encode)'s buffer
				GET_PICTURE_DIRECTION,	// flip the output picture's direction
				SET_PICTURE_DIRECTION,	// flip the output picture's direction
				GET_BRIGHTNESS,			// adjust brightness
				SET_BRIGHTNESS,			// adjust brightness
				GET_PRIVATE_DATA,		// the private information
				SET_PRIVATE_DATA,		
				SET_DECODE_OUT_PIXEL_FMT,
				SET_IN_REAL_OR_VOD_STUATION,
		[IN]	pCtrlParam		����ֵ
		[IN]	nParamLen		����ֵ����
*����ֵ���ɹ���ʼ���򷵻ش���0��ֵ����ʼ�����ɹ��򷵻�С��0��ֵ
*��  ע��
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT	iSOC_SetAVCodecParameters(IN ISOC_LONGPTR lAVCodecSession,IN ISOC_INT nCtrlCmd,IN OUT ISOC_BYTE* pCtrlParam,IN ISOC_INT nParamLen);


/******************************************************************************************************************************
*��������iSOC_InitAVCodec
*��  �ܣ���ʼ���������
*��  ����
		[IN]	lAVCodecSession	��������Ự��ʶ
		[IN]	pInitParam		��ʼ������ֵ
				������Ƶ�ò�������ֵΪST_VideoInitParam���ͣ�����ֵΪST_VideoEncodeInitParam����
				������Ƶ����ST_AudioInitParam����
		[IN]	nParamLen		��������
		[IN]	dwReserved		������
*����ֵ���ɹ���ʼ���򷵻ش���0��ֵ����ʼ�����ɹ��򷵻�С��0��ֵ
*��  ע��
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT	iSOC_InitAVCodec(IN ISOC_LONGPTR lAVCodecSession,IN ISOC_BYTE* pInitParam,IN ISOC_INT nParamLen,IN ISOC_DWORDPTR dwReserved=0);


/******************************************************************************************************************************
*��������iSOC_AVEncode
*��  �ܣ����ݱ���
*��  ����
		[IN]	lAVCodecSession	��������Ự��ʶ
		[IN]	pSrcData		ԭʼ����
		[IN]	nSrcLen			ԭʼ���ݳ���
		[OUT]	pDstData		���������
		[OUT]	nDstLen			��������ݳ���
		[IN]	pPrivteParam	���Ӳ�����Ĭ��ΪNULL
*����ֵ���ɹ���ʼ���򷵻ش���0��ֵ����ʼ�����ɹ��򷵻�С��0��ֵ
*��  ע��
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT	iSOC_AVEncode(IN ISOC_LONGPTR lAVCodecSession,IN ISOC_BYTE* pSrcData,IN ISOC_INT nSrcLen,OUT ISOC_BYTE** pDstData,OUT ISOC_INT* nDstLen,IN ISOC_BYTE* pPrivteParam=NULL);



/******************************************************************************************************************************
*��������iSOC_AVDecode
*��  �ܣ����ݽ���
*��  ����
		[IN]	lAVCodecSession	��������Ự��ʶ
		[IN]	pSrcData		ԭʼ����
		[IN]	nSrcLen			ԭʼ���ݳ���
		[IN OUT] pDstData		���������֡,���Ϊ��Ƶ������Ҫ��ST_VideoFrame�Ľṹ��ָ�룬���Ϊ��Ƶ������ΪST_AudioFrameָ��
		[IN]	nDstDataLen		sizeof(ST_VideoFrame)��sizeof(ST_AudioFrame)
		[IN]	pPrivteParam	���Ӳ�����Ĭ��ΪNULL����Ƶ�����ʱ��Ϊ��ST_VideoParamָ��
*����ֵ���ɹ���ʼ���򷵻ش���0��ֵ����ʼ�����ɹ��򷵻�С��0��ֵ
*��  ע��
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT	iSOC_AVDecode(IN ISOC_LONGPTR lAVCodecSession,IN ISOC_BYTE* pSrcData,IN ISOC_INT nSrcLen,IN OUT BYTE *pDstData,IN ISOC_INT nDstDataLen,IN ISOC_BYTE* pPrivteParam=NULL);


/******************************************************************************************************************************
*��������iSOC_ReleaseAVCodec
*��  �ܣ�ע���������
*��  ����
		[IN]	lAVCodecSession	��������Ự��ʶ
		[IN]	dwReserved ��������
*����ֵ���ɹ���ʼ���򷵻ش���0��ֵ����ʼ�����ɹ��򷵻�С��0��ֵ
*��  ע��
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT	iSOC_ReleaseAVCodec(IN ISOC_LONGPTR lAVCodecSession,IN ISOC_DWORDPTR dwReserved=0);



/******************************************************************************************************************************
*��������iSOC_FillVideoFrame
*��  �ܣ���Ƶ�������
*��  ����
		[IN OUT]	pFrame			Դ��Ƶ֡��Ϣ
		[IN]		pFrameData		Դ��Ƶ֡����
		[IN]		type			ý���ʽ
		[IN]		width			���
		[IN]		height			�߶�
*����ֵ���ɹ��򷵻�ת�������ݳ���ֵ����ʼ���򷵻�С�ڵ���0��ֵ
*��  ע��
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT	iSOC_FillVideoFrame(IN OUT ST_VideoFrame *pFrame, IN ISOC_BYTE *pFrameData,IN MediaDataType type, IN ISOC_INT width, IN ISOC_INT height);

/******************************************************************************************************************************
*��������iSOC_ConvertColorSpace
*��  �ܣ���ɫ�ռ�ת��
*��  ����
		[IN]		pSrc		Դ����
		[IN]		mdtSrc		Դ���ݵ���ɫ�ռ�ֵ
		[IN OUT]	pDes		Ŀ������
		[IN]		mdtDes		Ŀ�����ݵ���ɫ�ռ�ֵ
		[IN]		nWidth		ͼ����
		[IN]		nHeight		ͼ��߶�
*����ֵ���ɹ��򷵻�ת�������ݳ���ֵ����ʼ���򷵻�С�ڵ���0��ֵ
*��  ע��
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT	iSOC_ConvertColorSpace(IN ST_VideoFrame *pSrc,IN MediaDataType mdtSrc,IN OUT ST_VideoFrame* pDes,IN MediaDataType mdtDes,IN ISOC_INT nWidth,IN ISOC_INT nHeight);


#ifdef __cplusplus
}
#endif

#endif
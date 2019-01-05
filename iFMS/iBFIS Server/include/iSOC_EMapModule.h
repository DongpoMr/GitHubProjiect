#ifndef __ISOC_EMAPMODULE_API_HEADER__
#define __ISOC_EMAPMODULE_API_HEADER__

#include "iSOC_UnitDefine.h"

#ifdef __cplusplus
extern "C"
{
#endif

/******************************************************************************************************************************
*��������iSOC_GetEMapSession
*��  �ܣ���ȡ���ӵ�ͼ�Ự
*��  ����
		[IN OUT]	lEMapSession	�����ĵ��ӵ�ͼ�Ự
		[IN]		lMCSession		�������ĻỰ
*����ֵ���ɹ���ʼ���򷵻ش���0��ֵ����ʼ�����ɹ��򷵻�С��0��ֵ
*��  ע��
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_GetEMapSession(IN OUT ISOC_LONGPTR *lEMapSession,IN ISOC_LONGPTR lMCSession);

/******************************************************************************************************************************
*��������iSOC_GetMapNodeInfo
*��  �ܣ���ȡ���ӵ�ͼ�Ĳ㼶��ϵ����Ϣ
*��  ����
		[IN]		lEMapSession	���ӵ�ͼ�Ự
		[IN OUT]	lDataListHead	�������ݶ��У���������ST_MapNode
*����ֵ���ɹ���ʼ���򷵻ش���0��ֵ����ʼ�����ɹ��򷵻�С��0��ֵ
*��  ע���μ�iSOC_UnitDefine.h��ʹ�����ݶ��еķ���
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_GetMapNodeInfo(IN ISOC_LONGPTR lEMapSession,IN OUT ISOC_LONGPTR * lDataListHead);

/******************************************************************************************************************************
*��������iSOC_GetMapLeafInfo
*��  �ܣ���ȡ���ӵ�ͼ����Ϣ
*��  ����
		[IN]		lEMapSession	���ӵ�ͼ�Ự
		[IN OUT]	lDataListHead	�������ݶ��У���������ST_MapLeaf
*����ֵ���ɹ���ʼ���򷵻ش���0��ֵ����ʼ�����ɹ��򷵻�С��0��ֵ
*��  ע���μ�iSOC_UnitDefine.h��ʹ�����ݶ��еķ���
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_GetMapLeafInfo(IN ISOC_LONGPTR lEMapSession,IN OUT ISOC_LONGPTR * lDataListHead);

/******************************************************************************************************************************
*��������iSOC_GetMapLeafMapAssInfo
*��  �ܣ���ȡ���ӵ�ͼ����ͼ�Ĺ�����ϵ��Ϣ
*��  ����
		[IN]		lEMapSession	���ӵ�ͼ�Ự
		[IN OUT]	lDataListHead	�������ݶ��У���������ST_MapLeafMapAss
*����ֵ���ɹ���ʼ���򷵻ش���0��ֵ����ʼ�����ɹ��򷵻�С��0��ֵ
*��  ע���μ�iSOC_UnitDefine.h��ʹ�����ݶ��еķ���
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_GetMapLeafMapAssInfo(IN ISOC_LONGPTR lEMapSession,IN OUT ISOC_LONGPTR * lDataListHead);

/******************************************************************************************************************************
*��������iSOC_GetMapLeafEquAssInfo
*��  �ܣ���ȡ���ӵ�ͼ���豸�Ĺ�����ϵ��Ϣ
*��  ����
		[IN]		lEMapSession	���ӵ�ͼ�Ự
		[IN OUT]	lDataListHead	�������ݶ��У���������ST_MapLeafEquAss
*����ֵ���ɹ���ʼ���򷵻ش���0��ֵ����ʼ�����ɹ��򷵻�С��0��ֵ
*��  ע���μ�iSOC_UnitDefine.h��ʹ�����ݶ��еķ���
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_GetMapLeafEquAssInfo(IN ISOC_LONGPTR lEMapSession,IN OUT ISOC_LONGPTR * lDataListHead);

/******************************************************************************************************************************
*��������iSOC_GetMapLeafOrgAssInfo
*��  �ܣ���ȡ���ӵ�ͼ����֯�ṹ�Ĺ�����ϵ��Ϣ
*��  ����
		[IN]		lEMapSession	���ӵ�ͼ�Ự
		[IN OUT]	lDataListHead	�������ݶ��У���������ST_MapLeafOrgAss
*����ֵ���ɹ���ʼ���򷵻ش���0��ֵ����ʼ�����ɹ��򷵻�С��0��ֵ
*��  ע���μ�iSOC_UnitDefine.h��ʹ�����ݶ��еķ���
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_GetMapLeafOrgAssInfo(IN ISOC_LONGPTR lEMapSession,IN OUT ISOC_LONGPTR * lDataListHead);

/******************************************************************************************************************************
*��������iSOC_DownLoadEmapFile
*��  �ܣ����ص��ӵ�ͼ��ָ����Ŀ¼
*��  ����
		[IN]	lEMapSession	���ӵ�ͼ�Ự
		[IN]	stMapInfo		Ҫ���صĵ�ͼ��Ϣ
		[IN]	strDesFilePath	���صĵ��ӵ�ͼ����·��
		[IN]	dwReserved		������
*����ֵ���ɹ���ʼ���򷵻ش���0��ֵ����ʼ�����ɹ��򷵻�С��0��ֵ
*��  ע��
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_DownLoadEmapFile(IN ISOC_LONGPTR lEMapSession,IN ST_MapLeaf stMapInfo,IN const ISOC_STR strDesFilePath,IN ISOC_DWORDPTR dwReserved = 0);

/******************************************************************************************************************************
*��������iSOC_SetEmapNotifyCallback
*��  �ܣ������첽�¼�֪ͨ�ص�����
*��  ����
		[IN]	lEMapSession	���ӵ�ͼ�Ự
		[IN]	pCallback		�첽�¼��ص�����ָ��
		[IN]	dwCookie		�û�COOKIE
*����ֵ���ɹ���ʼ���򷵻ش���0��ֵ����ʼ�����ɹ��򷵻�С��0��ֵ
*��  ע��
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_SetEmapNotifyCallback(IN ISOC_LONGPTR lEMapSession,IN iSOC_OperatorStateCallback pCallback,IN ISOC_DWORDPTR dwCookie);

/******************************************************************************************************************************
*��������iSOC_RegisterRecvMsgFromMapServerCallback
*��  �ܣ�ע���map���������ص�����ص�
*��  ����
		[IN]	lEMapSession	���ӵ�ͼ�Ự
        [IN]	dwCmdID		    �����ʶ
        [IN]	pCallback	    �ص�����ָ��
        [IN]	dwUserCookie    �û��Զ���Cookie
        [IN]	dwReserved	    ��������
*����ֵ�����óɹ����ش���0��ֵ������ʧ�ܷ���С��0��ֵ��������ʧ�ܣ���ʹ��iSOC_GetLastErrorDes��ȡ��������������-4˵���Ѿ�����
        һ��һ���Ļص���Ϣ
*��  ע�����Զ��ע��ͬһ�������ʶ�����ע���ʱ��pCallback,dwUserCookie����������������һ��Ҫ��ͬ������ע��ģ�
        ����ᷢ������
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_RegisterRecvMsgFromMapServerCallback(IN ISOC_LONGPTR lEMapSession,
                                                                    IN const ISOC_DWORD dwCmdID,
                                                                    IN iSOC_OnGotDataCallback pCallback,
                                                                    IN ISOC_DWORDPTR dwUserCookie,
                                                                    IN ISOC_DWORDPTR dwReserved = 0);

/******************************************************************************************************************************
*��������iSOC_RemoveRecvMsgFromMapServerCallback
*��  �ܣ��Ƴ���map���������ص�����ص�
*��  ����
		 [IN]	lEMapSession	MC�Ự��ʶ
		 [IN]	dwCmdID		    �����ʶ
		 [IN]	pCallback	    �ص�����ָ��
		 [IN]	dwReserved	    ��������
*����ֵ�����óɹ����ش���0��ֵ������ʧ�ܷ���С��0��ֵ��������ʧ�ܣ���ʹ��iSOC_GetLastErrorDes��ȡ��������������-4˵��û���ҵ�
		 ��Ӧ�Ļص���Ϣ
*��  ע������ϵͳʵ���˿��Զ��ע��һ�������ʶ�Ĺ��ܣ���pCallbackΪ��ʱ���Ƴ������������dwCmdID��ػص�
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_RemoveRecvMsgFromMapServerCallback(IN ISOC_LONGPTR lEMapSession,
                                                                  IN const ISOC_DWORD dwCmdID,
                                                                  IN iSOC_OnGotDataCallback pCallback,
                                                                  IN ISOC_DWORDPTR dwReserved = 0);
#ifdef __cplusplus
}
#endif

#endif
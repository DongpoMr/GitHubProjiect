#pragma once

/******************************************************************************
 *    ������뼯�ϣ����д������Ϊ���������д��ڵ���ISOC_ERR_SUCCESS���ǳɹ�      *
 ******************************************************************************/

#define iSOCErrorCode

#define ISOC_ERR_SUCCESS                    1       //û�д��󣬳ɹ�
#define ISOC_ERR_FAILED                     0       //����ʧ��
//����ģ��ͨ��--------(-200 ******��***** -299)
#define ISOC_ERR_UNKNOW_ERROR               -200    //δ֪�Ĵ���
#define ISOC_ERR_INVALID_PTR                -201    //��Ч��ָ��ʹ��֮ǰ�Ƿ��ʼ��ָ�룿
#define ISOC_ERR_INVALID_PARAMETER          -202    //��Ч�Ĳ���
#define ISOC_ERR_INVALID_CALL               -203    //��Ч����
#define ISOC_ERR_INVALID_SESSION            -204    //��Ч�Ĳ����Ự
#define ISOC_ERR_FACTORY_MANAGER_UNINIT     -205    //û�г�ʼ�������������
#define ISOC_ERR_MEM_ALLOCATE_FAILED        -206    //�����ڴ�ʧ��
#define ISOC_ERR_NULL_DATA_LIST             -207    //��������Ϊ��
#define ISOC_ERR_END_DATA_LIST              -208    //������������ĩ��
#define ISOC_ERR_BEGIN_DATA_LIST            -209    //������������Ŀ�ʼ��
#define ISOC_ERR_OUTOF_DATA_LIST            -210    //������������û���ҵ���Ӧ����
#define ISOC_ERR_CONNECT_SERVER             -211    //���ӷ�����ʧ��
#define ISOC_ERR_DISCONNECT_SERVER          -212    //�Ͽ�������ʧ��
#define ISOC_ERR_CREATE_FILE_FAILED         -213    //�����ļ�ʧ��
#define ISOC_ERR_INVALID_TIMESTAMP          -214    //��Ч��ʱ���
#define ISOC_ERR_CREATE_THREAD_FAILED       -215    //�����߳�ʧ��
#define ISOC_ERR_NEED_I_FRAME               -216    //����I֡����ҪI֡
#define ISOC_ERR_UNREGISTER_MEM             -217    //û�����ڴ��������ע��ĵ�ַ
#define ISOC_ERR_FILE_EXISTED               -218    //�ļ��Ѿ�����
#define ISOC_ERR_INVAILID_HWND              -219    //��Ч�Ĵ��ھ��
#define ISOC_ERR_INVAILID_WND_STYLE         -220    //��Ч�Ĵ��ڷ�񣬲�֧�����ִ��ڷ��
#define ISOC_ERR_NULL_FILE_SIZE             -221    //�ļ���СΪ��
#define ISOC_ERR_NULL_FILE                  -222    //�ļ�Ϊ�գ������ļ�ͷ����
#define ISOC_ERR_FCACHE_INIT                -223    //��ʼ�����ٻ����ļ�ʧ��
#define ISOC_ERR_FCACHE_UNSUPPORT_FORMAT    -224    //���ٻ����ļ���֧�ֵ��ļ���ʽ
#define ISOC_ERR_FCACHE_WRTIE               -225    //�����ļ�д��ʧ��
#define ISOC_ERR_FCACHE_READ                -226    //�����ļ���ȡʧ��
#define ISOC_ERR_FCACHE_NULL_HEAD           -227    //���ٻ����ļ�ͷ��ϢΪ��
#define ISOC_ERR_FCACHE_FIND_BLOCK          -228    //û���ҵ��ʺϵĸ��ٻ����ļ���
#define ISOC_ERR_INVAILID_PATH              -229    //��Ч���ļ�·���������ļ�·��Ϊ��
#define ISOC_ERR_SEND_MESSAGE               -230    //���緢����Ϣʧ��
#define ISOC_ERR_FIND_XML_NODE              -231    //û���ҵ���Ӧ��xml�ڵ�
#define ISOC_ERR_UNNEED_RECONNECT           -232    //����Ҫ����
#define ISOC_ERR_CREATE_CALLBACK_MAN        -233    //�޷������ص�����������
#define ISOC_ERR_SAVE_PICTURE               -234    //����ͼƬʧ��
#define ISOC_ERR_XML_RETURE_CODE            -235    //����������ɹ�
#define ISOC_ERR_TASK_TIMEOUT               -236    //����ʱ�����ɹ�
#define ISOC_ERR_NO_RELATIVE_MC_SESSION     -237    //�����Ự��û�п��ù���MC�Ự
#define ISOC_ERR_SERVER_ADDRESS             -238    //����ķ�������ַ
#define ISOC_ERR_RTP_INIT                   -239    //RTP��ʼ��ʧ��
#define ISOC_ERR_RTP_STATUS_CALLBACK        -240    //����RTP״̬�ص�ʧ��
#define ISOC_ERR_RTP_START_SEND             -241    //RTP��ʼ����ʧ��
#define ISOC_ERR_RTP_ADD_DES                -242    //RTP���Ŀ�ĵ�ַʧ��
#define ISOC_ERR_RTP_PUSH_DATA              -243    //RTP�������ʧ��
#define ISOC_ERR_NO_ACTIVE_TCP              -244    //û�п��õ�TCP���ӻỰ
#define ISOC_ERR_NO_SWITCH_OBJECT           -245    //û�п��õ�switch����
#define ISOC_ERR_XML_UNKNOW_ERROR           -246    //����Ԥ֪��xml�ڲ�����
#define ISOC_ERR_REPEAT_OPERATE             -247    //�ظ��Ĳ���
#define ISOC_ERR_UNMATCH_VERSION            -248    //�汾��ƥ�䣬��֧�ָ��ֹ���
#define ISOC_ERR_PROCESS_GET_PORT           -249    //��ȡ�������̶˿���Ϣʧ��
#define ISOC_ERR_UNINITIALIZE_BEFORE_USE    -250    //�ڶ���ʹ��֮ǰû�г�ʼ��
#define ISOC_ERR_CREATE_VOICE_FAILED		-251	//���������ֶ���ʧ��
#define ISOC_ERR_CREATE_TTSSESSION_FAILED	-252	//����TextToSpeak�Ựʧ��
#define ISOC_ERR_NO_ITEM					-253	//û���ҵ���Ӧ��
#define ISOC_ERR_CREATE_DBOPERATOR_FALIED   -254	//�������ݿ��������ʧ��
#define ISOC_ERR_EXISTED_ITEM				-255	//�����Ѿ�����
#define ISOC_ERR_NO_MORE_FRAME				-256	//û�и����֡
#define ISOC_ERR_CREATE_MEDIA_FILE_FAILED   -257	//����ý���ļ�ʧ��
#define ISOC_ERR_CREATE_TRACK_FAILED		-258	//����Trackʧ��
#define ISOC_ERR_READ_TO_EOF				-259	//�����ļ���ĩβ
#define ISOC_ERR_BUFFER_FULL				-260	//��������
#define ISOC_ERR_PARSE_STREAM_FAILED		-261	//������ʧ��
#define ISOC_ERR_NEED_SEEKNEWPTS			-262	//ʱ����쳣����Ҫ����seek�µ�pts

//�澯ģ������--------(-300 ******��***** -349)
#define ISOC_ERR_ALARM_GET_FAILED           -300    //��ȡ�����Ựʧ��

//�Խ�ģ������--------(-350 ******��***** -399)
#define ISOC_ERR_DEV_TALK_CREATE_FAILED     -350    //�豸�Խ��Ự����ʧ��
#define ISOC_ERR_M2M_TALK_CREATE_FAILED     -351    //�ͻ��˶Խ��豸�Ự����ʧ��
#define ISOC_ERR_CAPTURE_AUDIO_INIT         -352    //��ʼ����Ƶ�ɼ�ʧ��
#define ISOC_ERR_TALK_TYPE                  -353    //��֧�ֵĶԽ�����
#define ISOC_ERR_TALK_PROCESS_END           -354    //�Խ�����û�п�ʼ�����Ѿ�������������Ч���ò��������ڶԽ�������

//���������--------(-400 ******��***** -449)
#define ISOC_ERR_AVCODEC_CREATE_FAILED      -400    //������������Ựʧ��
#define ISOC_ERR_MEDIA_PROC_CREATE_FAILED   -401    //����ý�����ݴ���Ựʧ��
#define ISOC_ERR_CODEC_INIT_FAILED          -402    //��ʼ���������ʧ��
#define ISOC_ERR_NO_CODEC                   -403    //û�п��õı������
#define ISOC_ERR_INVALID_SAMPLE_RATE        -404    //�����õ���Ƶ����Ƶ��
#define ISOC_ERR_ONLY_MONO_SUPPORT          -405    //��֧�ֵ�ͨ��
#define ISOC_ERR_INVALID_BITS               -406    //��֧�ֵĲ���λ��
#define ISOC_ERR_INVALID_SAMPLE_BITS        -407    //��Ч�Ĳ���Ƶ�ʺͲ���λ�������
#define ISOC_ERR_UNSUPPORT_CODE             -408    //��֧�ֵı�����ʽ
#define ISOC_ERR_UNINIT_CODEC               -409    //û�г�ʼ���������  
#define ISOC_ERR_CODE_FAILED                -410    //����ʧ��
#define ISOC_ERR_DECODE_FAILED              -411    //����ʧ��
#define ISOC_ERR_NO_STREAM_INFO             -412    //û���ҵ��������Ϣ
#define ISOC_ERR_EQU_COLOR_SPACE            -413    //��ȵ�ɫ�ʿռ䣬����ת��
#define ISOC_ERR_CONVER_COLOR_FAILED        -414    //ɫ�ʿռ�ת��ʧ��
#define ISOC_ERR_FILL_FRAME                 -415    //���֡����ʧ��

//����Ƶ��Ⱦ���--------(-450 ******��***** -499)
#define ISOC_ERR_VOUT_CREATE_FAILED         -450    //������Ƶ��Ⱦ���Ựʧ��
#define ISOC_ERR_AOUT_CREATE_FAILED         -451    //������Ƶ��Ⱦ���Ựʧ��
#define ISOC_ERR_AINIT_FAILED               -452    //��ʼ����Ƶ��Ⱦ��ʧ��
#define ISOC_ERR_VINIT_FAILED               -453    //��ʼ����Ƶ��Ⱦ��ʧ��
#define ISOC_ERR_DSOUND_NO_BUFFER           -454    //DSoundû�п��õĻ�����
#define ISOC_ERR_SET_VOLUME                 -455    //��������ʧ��
#define ISOC_ERR_GET_VOLUME                 -456    //��ȡ����ʧ��
#define ISOC_ERR_ARENDER_FAILED             -457    //��Ⱦ��Ƶʧ��
#define ISOC_ERR_VRENDER_FAILED             -458    //��Ⱦ��Ƶʧ��
#define ISOC_ERR_ROTATION_FAILED            -459    //ͼƬ��תʧ��
#define ISOC_ERR_FILP_FAILED                -460    //ͼƬ��תʧ��
#define ISOC_ERR_NO_VOUT_SOURCE             -461    //û�п��õ���Ƶ��Ⱦģ�飬�ǲ���û�д���
#define ISOC_ERR_NO_AOUT_SOURCE             -462    //û�п��õ���Ƶ��Ⱦģ�飬�ǲ���û�д���
#define ISOC_ERR_D3D_INSIDE                 -463    //D3D�ڲ�����
#define ISOC_ERR_UNSPPORT_IMAGE_TYPE        -464    //��֧�ֵ�ͼ��Դ��ʽ����Ⱦʧ��
#define ISOC_ERR_DDRAW_INSIDE               -465    //DDraw�ڲ�����

//�����������--------(-500 ******��***** -549)
#define ISOC_ERR_CODEC_INFO_CREATE_FAILED   -500    //������������Ựʧ��
#define ISOC_ERR_CREATE_CODE_INFO_SOURCE    -501    //������ȡ�����ʽԴ����ʧ�ܣ���ȷ�϶�Ӧ����Ƿ��Ѿ���������Ŀ¼

//���ӵ�ͼ����--------(-550 ******��***** -599)
#define ISOC_ERR_EMAP_GET_FAILED            -550    //��ȡ���ӵ�ͼ�Ựʧ��

//�ļ���������--------(-600 ******��***** -649)
#define ISOC_ERR_FLOCK_CREATE_FAILED        -600    //�����ļ������Ựʧ��

//�ļ�Ǩ������--------(-650 ******��***** -699)
#define ISOC_ERR_MIGRATE2_CREATE_FAILED     -650    //����2.0�汾�ļ�Ǩ�ƻỰʧ��
#define ISOC_ERR_MMIGRATE_CREATE_FAILED     -651    //�����ļ�Ǩ�ƹ���Ựʧ��
#define ISOC_ERR_MIGRATE_CREATE_FAILED      -652    //����1.5.8�汾�ļ�Ǩ�ƻỰʧ��
#define ISOC_ERR_NO_MIGRATE_SOURCE          -653    //û�п��õ�Ǩ��Դ����

//�ļ�ģ������--------(-700 ******��***** -749)
#define ISOC_ERR_FEXPORT_CREATE_FAILED      -700    //�����ļ������Ựʧ��
#define ISOC_ERR_FUPLOAD_CREATE_FAILED      -701    //�����ļ����ػỰʧ��
#define ISOC_ERR_FDOWNLOAD_CREATE_FAILED    -702    //�����ļ����ػỰʧ��
#define ISOC_ERR_FDELETE_CREATE_FAILED      -703    //�����ļ�ɾ���Ựʧ��
#define ISOC_ERR_NO_QUERY_VODFILE_INTERFACE -704    //û�п��õ�VOD�ļ���ѯ�ӿ�
#define ISOC_ERR_FEXPORT_NO_SOURCE          -705    //�����ļ�����Դʧ�ܣ��˷�������֧���ļ�����
#define ISOC_ERR_FILE_PROCESS_STOP          -706    //�ļ������Ѿ�������
#define ISOC_ERR_FEXPORT_REPEATE_THREAD     -707    //�ļ������Ѿ������̣߳���Ҫ�ظ�����
#define ISOC_ERR_FILE_PROCESS_FAILED        -708    //�ļ�����ʧ����
#define ISOC_ERR_FCACHE_CREATE_FAILED       -709    //�����ļ����ٻ���������ʧ��
#define ISOC_ERR_NO_VOD_SOURCE              -710    //û�п��õ�VOD����Դ
#define ISOC_ERR_NULL_DATA_SKIN             -711    //û�п��õ����ݽ�����
#define ISOC_ERR_INVALID_TIMESPAN			-712	//��Ч�ĵ���ʱ��,��ʼʱ�������ʱ�����

//GISģ������--------(-750 ******��***** -799)
#define ISOC_ERR_GIS_CREATE_FAILED          -750    //����GIS�Ựʧ��
#define ISOC_ERR_GIS_SEARCH_FAILED          -751    //��GIS��û���ҵ���Ӧ��·
#define ISOC_ERR_GIS_PROCESS_FAILED         -752    //GIS���д���
#define ISOC_ERR_GIS_NO_SERVER              -753    //û�����ӵ�Զ�̵��÷����������ܽ����������

//ʵʱģ������--------(-800 ******��***** -849)
#define ISOC_ERR_LIVE_CREATE_FAILED         -800    //����ʵʱ�Ựʧ��
#define ISOC_ERR_LIVE_ADD_TAG               -801    //ʵʱ��ӱ�ǩʧ��
#define ISOC_ERR_LIVE_SOURCE_CREATE         -802    //����ʵʱ��Դ����Դ����ʧ�ܣ���ȷ�϶�Ӧ����Ƿ��Ѿ���������Ŀ¼
#define ISOC_ERR_NO_LIVE_SOURCE             -803    //û�п��õ�ʵʱ�������ǲ���û�д���
#define ISOC_ERR_NO_MEDIA_PROCESS           -804    //û�п��õ���ý�崦����
#define ISOC_ERR_LIVE_PROCESS_STOP          -805    //ʵʱ�����Ѿ��������ò�����������ʵʱû�н���֮ǰ

//��¼ģ������--------(-850 ******��***** -899)
#define ISOC_ERR_MC_CREATE_FAILED           -850    //��������������Ựʧ��
#define ISOC_ERR_NO_ORGAN_INTERFACE         -851    //û�п��õ���֯�ṹ����ӿ�
#define ISOC_ERR_NO_INDEX_DEV               -852    //ͨ������û���ҵ�ָ���豸
#define ISOC_ERR_NO_UNITCODE_DEV            -853    //ͨ���豸ͳһ����û���ҵ�ָ���豸
#define ISOC_ERR_NO_ID_DEV                  -854    //ͨ��IDû���ҵ�ָ���豸
#define ISOC_ERR_NO_ICMS_DEV                -855    //ͨ��ICMSSign��ICMSSignIDû���ҵ�ָ���豸
#define ISOC_ERR_MC_EXIST_MSG               -856    //�Ѿ�������ͬ����Ϣ���ӹ���������յ������ص���
#define ISOC_ERR_MC_NONEXISTENT_MSG         -857    //������ָ������Ϣ���ӹ���������յ������ص���
#define ISOC_ERR_NO_PERMISSION_INTERFACE    -858    //û�п��õ�Ȩ�޹���ӿ�
#define ISOC_ERR_MC_GET_USER_INFO           -859    //��ȡ�û���Ϣʧ��
#define ISOC_ERR_MC_GET_LOCAL_INFO          -860    //��ȡ������Ϣʧ��
#define ISOC_ERR_MC_GET_VERSION             -861    //��ȡϵͳ�汾��Ϣʧ��
#define ISOC_ERR_MC_LOGIN                   -862    //��¼ʧ�ܣ��û����������

//PTZ����ģ������--------(-900 ******��***** -949)
#define ISOC_ERR_PTZ_CTRL_CREATE_FAILED     -900    //����PTZ���ƻỰʧ��
#define ISOC_ERR_CP_GET_FAILED              -901    //��ȡѲ��Ԥ�õ�Ѳ������Ựʧ��
#define ISOC_ERR_NO_INDEX_CRUISE            -902    //ͨ������û���ҵ���Ӧ���豸Ѳ����Ϣ
#define ISOC_ERR_NO_ID_CRUISE               -903    //ͨ��Ѳ��IDû���ҵ���Ӧ���豸Ѳ����Ϣ
#define ISOC_ERR_NO_INDEX_PREPOINT          -904    //ͨ������û���ҵ���Ӧ���豸Ԥ�õ���Ϣ
#define ISOC_ERR_NO_ID_PREPOINT             -905    //ͨ��Ԥ�õ�IDû���ҵ���Ӧ���豸Ԥ�õ���Ϣ
#define ISOC_ERR_INDEX_DELETE_PREPOINT      -906    //ͨ��Ԥ�õ�����ɾ��Ԥ�õ���Ϣʧ��
#define ISOC_ERR_ID_DELETE_PREPOINT         -907    //ͨ��Ԥ�õ�IDɾ��Ԥ�õ���Ϣʧ��
#define ISOC_ERR_INDEX_DELETE_CRUISE        -908    //ͨ��Ѳ������ɾ��Ѳ����Ϣʧ��
#define ISOC_ERR_ID_DELETE_CRUISE           -909    //ͨ��Ѳ��IDɾ��Ѳ����Ϣʧ��

//��ʷ�ط�ģ������--------(-950 ******��***** -999)
#define ISOC_ERR_VOD_CREATE_FAILED          -950    //������ʷ�طŻỰʧ��
#define ISOC_ERR_INVALID_VODFILE_INFO       -951    //�����VOD�ļ���Ϣ����
#define ISOC_ERR_NO_VOD_PARSER              -952    //û�п��õ�VOD��������
#define ISOC_ERR_VOD_PROCESS_STOP           -953    //��ʷ�طŲ����Ѿ��������ò�����������ʵʱû�н���֮ǰ

//��������ģ������--------(-1000 ******��***** -1049)
#define ISOC_ERR_DCS_CREATE_FAILED          -1000   //�����������ƻỰʧ��
#define ISOC_ERR_DCS_NO_SOURCE              -1001   //û�п��õ�DCS����Դ
#define ISOC_ERR_DSC_DB_CRETER              -1002   //��������DB����Դʧ��
#define ISOC_ERR_DCS_DB_SOURCE              -1003   //û�п��ô���DB����Դ��δ�������ݿ⣩
#define ISOC_ERR_DCS_DB_WRITE               -1004   //д��������ݿ�ʧ��
#define ISOC_ERR_DCS_DB_UPDATE              -1005   //�������ݿ����ʧ��
#define ISOC_ERR_DCS_DB_DELETE              -1006   //�������ݿ�ɾ��ʧ��
#define ISOC_ERR_DCS_DEFENCE_LIST           -1007   //û���ҵ���Ӧ�Ĳ�������
#define ISOC_ERR_DCS_CONNECT_SERVER         -1008   //���Ӵ���������ʧ��


//����ǽģ������--------(-1050 ******��***** -1099)
#define ISOC_ERR_MATRIX_CREATE_FAILED       -1050   //��������ǽ���������ƻỰʧ��
#define ISOC_ERR_NO_MATRIX_SERVER_INTERFACE -1051   //û�п��õĵ���ǽ��������Ϣ����ӿ�
#define ISOC_ERR_NO_INDEX_MATRIX_SERVER     -1052   //ͨ������û���ҵ���Ӧ�ĵ���ǽ��������Ϣ
#define ISOC_ERR_NO_INDEX_MATRIX_OUTPUT     -1053   //ͨ������û���ҵ���Ӧ�ĵ���ǽ�����������Ϣ
#define ISOC_ERR_NO_ID_MATRIX_OUTPUT        -1054   //ͨ������ǽ������IDû���ҵ���Ӧ�ĵ���ǽ�����������Ϣ
#define ISOC_ERR_GET_MATRIX_LAYOUT_FAILED   -1055   //��ȡ����ǽ�ķ�����ʧ��
#define ISOC_ERR_INVALID_MONTAGE_COUNT      -1056   //��Ч��ƴ�Ӳ�������������(���ڵ���1)
#define ISOC_ERR_NO_MATRIX_SCREEN_INFO      -1057   //����ǽ������û���ҵ�ָ������Ļ��Ϣ
#define ISOC_ERR_GET_MATRIX_OUTPUT_STATUS   -1058   //��ȡ����ǽ���������״̬��Ϣʧ��
#define ISOC_ERR_GET_MATRIX_LIVE_STATUS     -1059   //��ȡ����ǽ������ʵʱ״̬��Ϣʧ��
#define ISOC_ERR_GET_MATRIX_VOD_STATUS      -1060   //��ȡ����ǽ��������ʷ�ط�ʱ��״̬��Ϣʧ��
#define ISOC_ERR_GET_MATRIX_GROUP_STATUS    -1061   //��ȡ����ǽ������������ѵ״̬��Ϣʧ��
#define ISOC_ERR_GET_MATRIX_ALARM_STATUS    -1062   //��ȡ����ǽ����������״̬��Ϣʧ��
#define ISOC_ERR_MATRIX_NO_SOURCE           -1063   //û�п��õĵ���ǽ����Դ

//VPUģ������---------(-1100 ******��***** -1149)
#define ISOC_ERR_CANNOT_CREATE_FILE_PARSER     -1100 //�޷������ļ���������
#define ISOC_ERR_CANNOT_CREATE_FILE_PARSER_MANAGER -1101 //�޷������ļ������������
#define ISOC_ERR_CANNOT_CREATE_SOURCE			-1102 //�޷�����Դ�ӿ�
#define ISOC_ERR_CANNOT_CREATE_PROCESSOR_STATION -1103 //�޷���������ҵ�����
#define ISOC_ERR_CANNOT_CREATE_DECODE_PROCESSOR -1104 //�޷��������봦�����
#define ISOC_ERR_CANNOT_CREATE_SOURCE_MANAGER   -1105 //�޷�����Դ�������
#define ISOC_ERR_CANNOT_CREATE_PROCESSOR_ITEM_STATION -1106 //�޷�������������ҵ�����
#define ISOC_ERR_CANNOT_CREATE_ANALYZE_PROCESSOR -1107 //�޷��������ܷ���ҵ�����
#define ISOC_ERR_CANNOT_CREATE_PROCESSOR		-1108 //�޷�����VPU����



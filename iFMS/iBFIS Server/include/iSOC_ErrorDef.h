#pragma once

/******************************************************************************
 *    错误代码集合，所有错误码均为负数，所有大于等于ISOC_ERR_SUCCESS都是成功      *
 ******************************************************************************/

#define iSOCErrorCode

#define ISOC_ERR_SUCCESS                    1       //没有错误，成功
#define ISOC_ERR_FAILED                     0       //操作失败
//所有模块通用--------(-200 ******到***** -299)
#define ISOC_ERR_UNKNOW_ERROR               -200    //未知的错误
#define ISOC_ERR_INVALID_PTR                -201    //无效的指针使用之前是否初始化指针？
#define ISOC_ERR_INVALID_PARAMETER          -202    //无效的参数
#define ISOC_ERR_INVALID_CALL               -203    //无效调用
#define ISOC_ERR_INVALID_SESSION            -204    //无效的操作会话
#define ISOC_ERR_FACTORY_MANAGER_UNINIT     -205    //没有初始化工厂管理对象
#define ISOC_ERR_MEM_ALLOCATE_FAILED        -206    //开辟内存失败
#define ISOC_ERR_NULL_DATA_LIST             -207    //数据链表为空
#define ISOC_ERR_END_DATA_LIST              -208    //超出数据链表末端
#define ISOC_ERR_BEGIN_DATA_LIST            -209    //超出数据链表的开始端
#define ISOC_ERR_OUTOF_DATA_LIST            -210    //超出数据链表，没有找到对应数据
#define ISOC_ERR_CONNECT_SERVER             -211    //连接服务器失败
#define ISOC_ERR_DISCONNECT_SERVER          -212    //断开服务器失败
#define ISOC_ERR_CREATE_FILE_FAILED         -213    //创建文件失败
#define ISOC_ERR_INVALID_TIMESTAMP          -214    //无效的时间戳
#define ISOC_ERR_CREATE_THREAD_FAILED       -215    //创建线程失败
#define ISOC_ERR_NEED_I_FRAME               -216    //不是I帧，需要I帧
#define ISOC_ERR_UNREGISTER_MEM             -217    //没有在内存管理里面注册的地址
#define ISOC_ERR_FILE_EXISTED               -218    //文件已经存在
#define ISOC_ERR_INVAILID_HWND              -219    //无效的窗口句柄
#define ISOC_ERR_INVAILID_WND_STYLE         -220    //无效的窗口风格，不支持这种窗口风格
#define ISOC_ERR_NULL_FILE_SIZE             -221    //文件大小为空
#define ISOC_ERR_NULL_FILE                  -222    //文件为空，或者文件头被损坏
#define ISOC_ERR_FCACHE_INIT                -223    //初始化高速缓冲文件失败
#define ISOC_ERR_FCACHE_UNSUPPORT_FORMAT    -224    //高速缓冲文件不支持的文件格式
#define ISOC_ERR_FCACHE_WRTIE               -225    //高速文件写入失败
#define ISOC_ERR_FCACHE_READ                -226    //高速文件读取失败
#define ISOC_ERR_FCACHE_NULL_HEAD           -227    //高速缓冲文件头信息为空
#define ISOC_ERR_FCACHE_FIND_BLOCK          -228    //没有找到适合的高速缓冲文件块
#define ISOC_ERR_INVAILID_PATH              -229    //无效的文件路径，或者文件路劲为空
#define ISOC_ERR_SEND_MESSAGE               -230    //网络发送消息失败
#define ISOC_ERR_FIND_XML_NODE              -231    //没有找到对应的xml节点
#define ISOC_ERR_UNNEED_RECONNECT           -232    //不需要重连
#define ISOC_ERR_CREATE_CALLBACK_MAN        -233    //无法创建回调函数管理器
#define ISOC_ERR_SAVE_PICTURE               -234    //保存图片失败
#define ISOC_ERR_XML_RETURE_CODE            -235    //信令操作不成功
#define ISOC_ERR_TASK_TIMEOUT               -236    //任务超时，不成功
#define ISOC_ERR_NO_RELATIVE_MC_SESSION     -237    //操作会话里没有可用关联MC会话
#define ISOC_ERR_SERVER_ADDRESS             -238    //错误的服务器地址
#define ISOC_ERR_RTP_INIT                   -239    //RTP初始化失败
#define ISOC_ERR_RTP_STATUS_CALLBACK        -240    //设置RTP状态回调失败
#define ISOC_ERR_RTP_START_SEND             -241    //RTP开始发送失败
#define ISOC_ERR_RTP_ADD_DES                -242    //RTP添加目的地址失败
#define ISOC_ERR_RTP_PUSH_DATA              -243    //RTP添加数据失败
#define ISOC_ERR_NO_ACTIVE_TCP              -244    //没有可用的TCP连接会话
#define ISOC_ERR_NO_SWITCH_OBJECT           -245    //没有可用的switch对象
#define ISOC_ERR_XML_UNKNOW_ERROR           -246    //不可预知的xml内部错误
#define ISOC_ERR_REPEAT_OPERATE             -247    //重复的操作
#define ISOC_ERR_UNMATCH_VERSION            -248    //版本不匹配，不支持该种功能
#define ISOC_ERR_PROCESS_GET_PORT           -249    //获取给定进程端口信息失败
#define ISOC_ERR_UNINITIALIZE_BEFORE_USE    -250    //在对象使用之前没有初始化
#define ISOC_ERR_CREATE_VOICE_FAILED		-251	//创建读文字对象失败
#define ISOC_ERR_CREATE_TTSSESSION_FAILED	-252	//创建TextToSpeak会话失败
#define ISOC_ERR_NO_ITEM					-253	//没有找到对应项
#define ISOC_ERR_CREATE_DBOPERATOR_FALIED   -254	//创建数据库操作对象失败
#define ISOC_ERR_EXISTED_ITEM				-255	//该项已经存在
#define ISOC_ERR_NO_MORE_FRAME				-256	//没有更多的帧
#define ISOC_ERR_CREATE_MEDIA_FILE_FAILED   -257	//创建媒体文件失败
#define ISOC_ERR_CREATE_TRACK_FAILED		-258	//创建Track失败
#define ISOC_ERR_READ_TO_EOF				-259	//读到文件的末尾
#define ISOC_ERR_BUFFER_FULL				-260	//缓冲区满
#define ISOC_ERR_PARSE_STREAM_FAILED		-261	//解析流失败
#define ISOC_ERR_NEED_SEEKNEWPTS			-262	//时间戳异常，需要重新seek新的pts

//告警模块特有--------(-300 ******到***** -349)
#define ISOC_ERR_ALARM_GET_FAILED           -300    //获取报警会话失败

//对讲模块特有--------(-350 ******到***** -399)
#define ISOC_ERR_DEV_TALK_CREATE_FAILED     -350    //设备对讲会话创建失败
#define ISOC_ERR_M2M_TALK_CREATE_FAILED     -351    //客户端对讲设备会话创建失败
#define ISOC_ERR_CAPTURE_AUDIO_INIT         -352    //初始化音频采集失败
#define ISOC_ERR_TALK_TYPE                  -353    //不支持的对讲类型
#define ISOC_ERR_TALK_PROCESS_END           -354    //对讲操作没有开始或者已经结束，操作无效，该操作必须在对讲运行在

//编解码特有--------(-400 ******到***** -449)
#define ISOC_ERR_AVCODEC_CREATE_FAILED      -400    //创建编解码器会话失败
#define ISOC_ERR_MEDIA_PROC_CREATE_FAILED   -401    //创建媒体数据处理会话失败
#define ISOC_ERR_CODEC_INIT_FAILED          -402    //初始化编解码器失败
#define ISOC_ERR_NO_CODEC                   -403    //没有可用的编解码器
#define ISOC_ERR_INVALID_SAMPLE_RATE        -404    //不可用的音频采样频率
#define ISOC_ERR_ONLY_MONO_SUPPORT          -405    //仅支持单通道
#define ISOC_ERR_INVALID_BITS               -406    //不支持的采样位数
#define ISOC_ERR_INVALID_SAMPLE_BITS        -407    //无效的采样频率和采用位数的组合
#define ISOC_ERR_UNSUPPORT_CODE             -408    //不支持的编解码格式
#define ISOC_ERR_UNINIT_CODEC               -409    //没有初始化编解码器  
#define ISOC_ERR_CODE_FAILED                -410    //编码失败
#define ISOC_ERR_DECODE_FAILED              -411    //解码失败
#define ISOC_ERR_NO_STREAM_INFO             -412    //没有找到流相关信息
#define ISOC_ERR_EQU_COLOR_SPACE            -413    //相等的色彩空间，不用转化
#define ISOC_ERR_CONVER_COLOR_FAILED        -414    //色彩空间转化失败
#define ISOC_ERR_FILL_FRAME                 -415    //填充帧数据失败

//视音频渲染相关--------(-450 ******到***** -499)
#define ISOC_ERR_VOUT_CREATE_FAILED         -450    //创建视频渲染器会话失败
#define ISOC_ERR_AOUT_CREATE_FAILED         -451    //创建音频渲染器会话失败
#define ISOC_ERR_AINIT_FAILED               -452    //初始化音频渲染器失败
#define ISOC_ERR_VINIT_FAILED               -453    //初始化视频渲染器失败
#define ISOC_ERR_DSOUND_NO_BUFFER           -454    //DSound没有可用的缓冲区
#define ISOC_ERR_SET_VOLUME                 -455    //设置音量失败
#define ISOC_ERR_GET_VOLUME                 -456    //获取音量失败
#define ISOC_ERR_ARENDER_FAILED             -457    //渲染音频失败
#define ISOC_ERR_VRENDER_FAILED             -458    //渲染视频失败
#define ISOC_ERR_ROTATION_FAILED            -459    //图片旋转失败
#define ISOC_ERR_FILP_FAILED                -460    //图片翻转失败
#define ISOC_ERR_NO_VOUT_SOURCE             -461    //没有可用的视频渲染模块，是不是没有创建
#define ISOC_ERR_NO_AOUT_SOURCE             -462    //没有可用的音频渲染模块，是不是没有创建
#define ISOC_ERR_D3D_INSIDE                 -463    //D3D内部错误
#define ISOC_ERR_UNSPPORT_IMAGE_TYPE        -464    //不支持的图像源格式，渲染失败
#define ISOC_ERR_DDRAW_INSIDE               -465    //DDraw内部错误

//编码参数特有--------(-500 ******到***** -549)
#define ISOC_ERR_CODEC_INFO_CREATE_FAILED   -500    //创建编码参数会话失败
#define ISOC_ERR_CREATE_CODE_INFO_SOURCE    -501    //创建获取编码格式源对象失败，请确认对应插件是否已经加入运行目录

//电子地图特有--------(-550 ******到***** -599)
#define ISOC_ERR_EMAP_GET_FAILED            -550    //获取电子地图会话失败

//文件锁定特有--------(-600 ******到***** -649)
#define ISOC_ERR_FLOCK_CREATE_FAILED        -600    //创建文件锁定会话失败

//文件迁移特有--------(-650 ******到***** -699)
#define ISOC_ERR_MIGRATE2_CREATE_FAILED     -650    //创建2.0版本文件迁移会话失败
#define ISOC_ERR_MMIGRATE_CREATE_FAILED     -651    //创建文件迁移管理会话失败
#define ISOC_ERR_MIGRATE_CREATE_FAILED      -652    //创建1.5.8版本文件迁移会话失败
#define ISOC_ERR_NO_MIGRATE_SOURCE          -653    //没有可用的迁移源对象

//文件模块特有--------(-700 ******到***** -749)
#define ISOC_ERR_FEXPORT_CREATE_FAILED      -700    //创建文件导出会话失败
#define ISOC_ERR_FUPLOAD_CREATE_FAILED      -701    //创建文件上载会话失败
#define ISOC_ERR_FDOWNLOAD_CREATE_FAILED    -702    //创建文件下载会话失败
#define ISOC_ERR_FDELETE_CREATE_FAILED      -703    //创建文件删除会话失败
#define ISOC_ERR_NO_QUERY_VODFILE_INTERFACE -704    //没有可用的VOD文件查询接口
#define ISOC_ERR_FEXPORT_NO_SOURCE          -705    //创建文件导出源失败，此服务器不支持文件导出
#define ISOC_ERR_FILE_PROCESS_STOP          -706    //文件操作已经结束了
#define ISOC_ERR_FEXPORT_REPEATE_THREAD     -707    //文件导出已经创建线程，不要重复创建
#define ISOC_ERR_FILE_PROCESS_FAILED        -708    //文件操作失败了
#define ISOC_ERR_FCACHE_CREATE_FAILED       -709    //创建文件高速缓冲管理对象失败
#define ISOC_ERR_NO_VOD_SOURCE              -710    //没有可用的VOD数据源
#define ISOC_ERR_NULL_DATA_SKIN             -711    //没有可用的数据接收器
#define ISOC_ERR_INVALID_TIMESPAN			-712	//无效的导出时间,开始时间与结束时间相等

//GIS模块特有--------(-750 ******到***** -799)
#define ISOC_ERR_GIS_CREATE_FAILED          -750    //创建GIS会话失败
#define ISOC_ERR_GIS_SEARCH_FAILED          -751    //在GIS中没有找到对应道路
#define ISOC_ERR_GIS_PROCESS_FAILED         -752    //GIS运行错误
#define ISOC_ERR_GIS_NO_SERVER              -753    //没有连接到远程调用服务器，不能进行相关设置

//实时模块特有--------(-800 ******到***** -849)
#define ISOC_ERR_LIVE_CREATE_FAILED         -800    //创建实时会话失败
#define ISOC_ERR_LIVE_ADD_TAG               -801    //实时添加标签失败
#define ISOC_ERR_LIVE_SOURCE_CREATE         -802    //创建实时流源对象源对象失败，请确认对应插件是否已经加入运行目录
#define ISOC_ERR_NO_LIVE_SOURCE             -803    //没有可用的实时流对象，是不是没有创建
#define ISOC_ERR_NO_MEDIA_PROCESS           -804    //没有可用的流媒体处理器
#define ISOC_ERR_LIVE_PROCESS_STOP          -805    //实时操作已经结束，该操作必须是在实时没有结束之前

//登录模块特有--------(-850 ******到***** -899)
#define ISOC_ERR_MC_CREATE_FAILED           -850    //创建管理服务器会话失败
#define ISOC_ERR_NO_ORGAN_INTERFACE         -851    //没有可用的组织结构管理接口
#define ISOC_ERR_NO_INDEX_DEV               -852    //通过索引没有找到指定设备
#define ISOC_ERR_NO_UNITCODE_DEV            -853    //通过设备统一编码没有找到指定设备
#define ISOC_ERR_NO_ID_DEV                  -854    //通过ID没有找到指定设备
#define ISOC_ERR_NO_ICMS_DEV                -855    //通过ICMSSign和ICMSSignID没有找到指定设备
#define ISOC_ERR_MC_EXIST_MSG               -856    //已经存在相同的消息（从管理服务器收到信令后回调）
#define ISOC_ERR_MC_NONEXISTENT_MSG         -857    //不存在指定的消息（从管理服务器收到信令后回调）
#define ISOC_ERR_NO_PERMISSION_INTERFACE    -858    //没有可用的权限管理接口
#define ISOC_ERR_MC_GET_USER_INFO           -859    //获取用户信息失败
#define ISOC_ERR_MC_GET_LOCAL_INFO          -860    //获取本地信息失败
#define ISOC_ERR_MC_GET_VERSION             -861    //获取系统版本信息失败
#define ISOC_ERR_MC_LOGIN                   -862    //登录失败，用户名密码错误

//PTZ控制模块特有--------(-900 ******到***** -949)
#define ISOC_ERR_PTZ_CTRL_CREATE_FAILED     -900    //创建PTZ控制会话失败
#define ISOC_ERR_CP_GET_FAILED              -901    //获取巡航预置点巡航管理会话失败
#define ISOC_ERR_NO_INDEX_CRUISE            -902    //通过索引没有找到对应的设备巡航信息
#define ISOC_ERR_NO_ID_CRUISE               -903    //通过巡航ID没有找到对应的设备巡航信息
#define ISOC_ERR_NO_INDEX_PREPOINT          -904    //通过索引没有找到对应的设备预置点信息
#define ISOC_ERR_NO_ID_PREPOINT             -905    //通过预置点ID没有找到对应的设备预置点信息
#define ISOC_ERR_INDEX_DELETE_PREPOINT      -906    //通过预置点索引删除预置点信息失败
#define ISOC_ERR_ID_DELETE_PREPOINT         -907    //通过预置点ID删除预置点信息失败
#define ISOC_ERR_INDEX_DELETE_CRUISE        -908    //通过巡航索引删除巡航信息失败
#define ISOC_ERR_ID_DELETE_CRUISE           -909    //通过巡航ID删除巡航信息失败

//历史回放模块特有--------(-950 ******到***** -999)
#define ISOC_ERR_VOD_CREATE_FAILED          -950    //创建历史回放会话失败
#define ISOC_ERR_INVALID_VODFILE_INFO       -951    //传入的VOD文件信息有误
#define ISOC_ERR_NO_VOD_PARSER              -952    //没有可用的VOD解析对象
#define ISOC_ERR_VOD_PROCESS_STOP           -953    //历史回放操作已经结束，该操作必须是在实时没有结束之前

//大屏控制模块特有--------(-1000 ******到***** -1049)
#define ISOC_ERR_DCS_CREATE_FAILED          -1000   //创建大屏控制会话失败
#define ISOC_ERR_DCS_NO_SOURCE              -1001   //没有可用的DCS控制源
#define ISOC_ERR_DSC_DB_CRETER              -1002   //创建大屏DB操作源失败
#define ISOC_ERR_DCS_DB_SOURCE              -1003   //没有可用大屏DB操作源（未连接数据库）
#define ISOC_ERR_DCS_DB_WRITE               -1004   //写入大屏数据库失败
#define ISOC_ERR_DCS_DB_UPDATE              -1005   //大屏数据库更新失败
#define ISOC_ERR_DCS_DB_DELETE              -1006   //大屏数据库删除失败
#define ISOC_ERR_DCS_DEFENCE_LIST           -1007   //没有找到对应的布防链表
#define ISOC_ERR_DCS_CONNECT_SERVER         -1008   //连接大屏服务器失败


//电视墙模块特有--------(-1050 ******到***** -1099)
#define ISOC_ERR_MATRIX_CREATE_FAILED       -1050   //创建电视墙服务器控制会话失败
#define ISOC_ERR_NO_MATRIX_SERVER_INTERFACE -1051   //没有可用的电视墙服务器信息管理接口
#define ISOC_ERR_NO_INDEX_MATRIX_SERVER     -1052   //通过索引没有找到对应的电视墙服务器信息
#define ISOC_ERR_NO_INDEX_MATRIX_OUTPUT     -1053   //通过索引没有找到对应的电视墙服务器输出信息
#define ISOC_ERR_NO_ID_MATRIX_OUTPUT        -1054   //通过电视墙服务器ID没有找到对应的电视墙服务器输出信息
#define ISOC_ERR_GET_MATRIX_LAYOUT_FAILED   -1055   //获取电视墙的分屏数失败
#define ISOC_ERR_INVALID_MONTAGE_COUNT      -1056   //无效的拼接操作行数或列数(大于等于1)
#define ISOC_ERR_NO_MATRIX_SCREEN_INFO      -1057   //电视墙服务器没有找到指定的屏幕信息
#define ISOC_ERR_GET_MATRIX_OUTPUT_STATUS   -1058   //获取电视墙服务器输出状态信息失败
#define ISOC_ERR_GET_MATRIX_LIVE_STATUS     -1059   //获取电视墙服务器实时状态信息失败
#define ISOC_ERR_GET_MATRIX_VOD_STATUS      -1060   //获取电视墙服务器历史回放时的状态信息失败
#define ISOC_ERR_GET_MATRIX_GROUP_STATUS    -1061   //获取电视墙服务器分组轮训状态信息失败
#define ISOC_ERR_GET_MATRIX_ALARM_STATUS    -1062   //获取电视墙服务器报警状态信息失败
#define ISOC_ERR_MATRIX_NO_SOURCE           -1063   //没有可用的电视墙控制源

//VPU模块特有---------(-1100 ******到***** -1149)
#define ISOC_ERR_CANNOT_CREATE_FILE_PARSER     -1100 //无法创建文件解析对象
#define ISOC_ERR_CANNOT_CREATE_FILE_PARSER_MANAGER -1101 //无法创建文件解析管理对象
#define ISOC_ERR_CANNOT_CREATE_SOURCE			-1102 //无法创建源接口
#define ISOC_ERR_CANNOT_CREATE_PROCESSOR_STATION -1103 //无法创建处理业务对象
#define ISOC_ERR_CANNOT_CREATE_DECODE_PROCESSOR -1104 //无法创建解码处理对象
#define ISOC_ERR_CANNOT_CREATE_SOURCE_MANAGER   -1105 //无法创建源管理对象
#define ISOC_ERR_CANNOT_CREATE_PROCESSOR_ITEM_STATION -1106 //无法创建子任务处理业务对象
#define ISOC_ERR_CANNOT_CREATE_ANALYZE_PROCESSOR -1107 //无法创建智能分析业务对象
#define ISOC_ERR_CANNOT_CREATE_PROCESSOR		-1108 //无法创建VPU对象



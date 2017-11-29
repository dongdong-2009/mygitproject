#ifndef algo_ivs_config_H__
#define algo_ivs_config_H__

#define Boon_ALG_IVS_MAX_TRAJECT_LEN	40

#define Boon_ALG_MAX_TGT_CNT			64//20						/*������Ŀ����*/
#define Boon_TRACK_MAX_TGT_CNT		Boon_ALG_MAX_TGT_CNT * 5		/*���ٹ�������������*/

#ifndef IVS_STATUS_E
#define IVS_STATUS_E			BoonInt32			/*���������������תһ��*/
#endif

#define Boon_ALG_MODULE_DATLEN				256		/* ģ�����ݳ��ȶ��� */	
#define Boon_ALG_MAX_RULE_NUM					16		/* ��������Ŀ		*/
#define Boon_ALG_MAX_OSC_NUM					4		//��Ʒ����-begin
#define Boon_ALG_MAX_OBJ_NUMBER				24		//�����Ŀ����(Ŀ�������㷨����)
#define Boon_ALG_MAX_GETUP_BOUNDARY_NUM_S		2		//����  bhz 20130415
#define Boon_ALG_MAX_REGION_NUM				6		//�������������(ֵ�ڡ���ͥ��ϯ����ͥ���淶��װ����)

/* �㷨������ */
typedef enum
{
	Boon_ALG_IVS_FUNC_NONE		= 0,		/* ��Ч */
	Boon_ALG_IVS_FUNC_HALT		= 1,		//ͣʻ
	Boon_ALG_IVS_FUNC_PERI_I		= 1<<1,		/* �ܽ��� 2*/
	Boon_ALG_IVS_FUNC_PERI_O		= 1<<2,		/* �ܽ��� 4*/
	Boon_ALG_IVS_FUNC_TRIPWIRE	= 1<<3,		/* �����߼�� 8*/
	Boon_ALG_IVS_FUNC_MTRIPWIRE	= 1<<4,		/* ����߼�� 16*/
	Boon_ALG_IVS_FUNC_LOITER		= 1<<5,		/* �ǻ���� 32*/
	Boon_ALG_IVS_FUNC_ABNMLVEL	= 1<<6,		/* ���ܼ�� 64*/
	Boon_ALG_IVS_FUNC_SLIPUP		= 1<<7,		/* ������� 128*/
	Boon_ALG_IVS_FUNC_GETUP		= 1<<8,		/* ������ 256*/
	Boon_ALG_IVS_FUNC_OSC			= 1<<9,		/* ��Ʒ������� 512*/
	Boon_ALG_IVS_FUNC_OSR			= 1<<10,	/* ��Ʒ��ʧ��� 1024*/
	Boon_ALG_IVS_FUNC_FIGHT		= 1<<11,	/* ��ܼ�� 2048*/
	Boon_ALG_IVS_FUNC_HIGLIMIT	= 1<<12,	/* �޸߼�� 4096*/
	Boon_ALG_IVS_FUNC_DUTY		= 1<<13,	/* ֵ�ڼ�� 8192*/	
	Boon_ALG_IVS_FUNC_VFD			= 1<<14,	/* ������� 16384*/
	Boon_ALG_IVS_FUNC_CDE			= 1<<15,	/* ��Ⱥ�ܶ� 32768*/
	Boon_ALG_IVS_FUNC_TPC			= 1<<16,	/* ��б����ͳ�� 65536*/
	Boon_ALG_IVS_FUNC_VPC			= 1<<17,	/* ��ֱ����ͳ�� 131072*/
	Boon_ALG_IVS_FUNC_AVD			= 1<<18,	/* ��Ƶ����㷨 */
	Boon_ALG_IVS_FUNC_CONVERSE	= 1<<19,	/* IVS���� */
	Boon_ALG_IVS_FUNC_STRANDED	= 1<<20,	/* IVS���� */
	Boon_ALG_IVS_FUNC_COURTSDC	= 1<<22,	/* ��ͥ���淶��װ��� */
	Boon_ALG_IVS_FUNC_COURBOONUTY	= 1<<23,	/* ��ͥ��ϯ��� */
	Boon_ALG_IVS_FUNC_COURTNPL	= 1<<24,	/* ��ͥ����ʶ�� */
	/*1<<21 �ѱ�ʹ�ã��뱣�� add mhm by*/

}Boon_ALG_IVS_FUNC_E;

/** �¼�״̬ */
typedef enum
{
	Boon_ALG_EVT_STATUS_NOSTA         = 0,	/**< ��״̬ */
	Boon_ALG_EVT_STATUS_START         = 1,	/**< ��ʼ */
	Boon_ALG_EVT_STATUS_END           = 2,	/**< ���� */
	Boon_ALG_EVT_STATUS_PROCEDURE     = 3		/**< ������ */
} Boon_ALG_EVT_STATUS_E;

#endif // _td_algo_ivs_config_H__


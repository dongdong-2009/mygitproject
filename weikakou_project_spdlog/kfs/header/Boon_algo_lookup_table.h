#ifndef _Boon_ALGO_LOOKUP_TABLE_H_
#define _Boon_ALGO_LOOKUP_TABLE_H_


#include	"Boon_algo_type.h"

#ifdef __cplusplus
extern "C" {
#endif

/**********************************Example*****************************
//��ѯ 201�ĵ�����
//�ڳ�ʼ�������е��� _gstLookUpTable.pf32Rcp_512_Init(iSeg); �������ɡ�
//
//BoonFloat32  f32Temp = _gstLookUpTable.pf32Rcp_512[201]; �õ�����ֵ
//˵�������˿��Զ�����ұ����̶���ʽ���ڽṹ���У��ȿ�
**********************************************************************/
typedef struct
{
	///////////////////// ������
	// ���뷶Χ	[0, 512),
	BoonFloat32* 	pf32Rcp_512;
	BoonInt32 (*pf32Rcp_512_Init)(BoonInt32);

	BoonFloat32 	*pf32etable;						//С����ָ�����ֵ�����
	BoonInt32 	(*pf32etable_Init)(BoonInt32);  
	BoonFloat32 	*pf32decltable;						//С����С�����ֵĵ�������С�����6λ
	BoonInt32 	(*pf32decltable_Init)(BoonInt32);
	
	BoonFloat32 	*pf32NexpHtable;					//��ָ�������������ֱ�
	BoonInt32  	(*pf32NexpHtable_Init)(BoonInt32);  
	BoonFloat32 	*pf32NexpLtable;					//��ָ������С�����ֱ�
	BoonInt32  	(*pf32NexpLtable_Init)(BoonInt32);  
	BoonUint8  	**pucAngleScale;
	BoonInt32 	(*pucAngleScaleTable_Init)(BoonInt32);

	BoonFloat32 ** pf32npd_kernel;
	BoonInt32 (*pf32npd_kernel_Init)(BoonInt32);//(x-y)/(x+y+0.0001)

//	BoonFloat32 * pf32NexpInt;
//	BoonInt32 (*pf32NexpInt_Init)(BoonInt32);//Z - 0-262144

	BoonInt32 * pf32NexpInt;
	BoonInt32 (*pf32NexpInt_Init)(BoonInt32);//Z - 0-262144

	//���㹫ʽ (x-y)/((x+y)+0.0001f);
	//x y ��Χ 0 -255 
	//BoonFloat32 pf32Rcp_255XY[256][256];
//	BoonInt32 (*pf32Rcp_255XY_Init)(BoonInt32);

}Boon_ALG_LOOKUPTABLET_S;

Boon_EXPORTS
Boon_ALG_LOOKUPTABLET_S  _gstLookUpTable;
#ifdef __cplusplus
}
#endif

#endif

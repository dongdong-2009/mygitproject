
#include "Boon_algo_type.h"

#ifndef _Boon_ALGO_LUT_H_
#define _Boon_ALGO_LUT_H_

#ifdef __cplusplus
extern "C" {
#endif

typedef struct
{
	BoonInt32 i32Size;

	///////////////////// ������
	// �ָ�
	BoonInt32* pi32Rcp_360_SQ16;
	// �ָ�
	// ���뷶Χ	[0, 255), �󵹺���19λС��
	BoonInt32* pi32Rcp_256_SQ19;
	// �ָ�
	// ���뷶Χ	[0, 64),
	BoonFloat32* pf32Rcp_64;

	///////////////////// sin ��
	// �ָ�
	//���Ǻ������������ķ�֮һ�ȵ�������������1024����
	BoonInt32* pi32Sin_360_SQ10;
	// �ָ�
	//���Ǻ������������ķ�֮һ�ȵ�������������65536����
	BoonInt32* pi32Sin_360_SQ16;

	///////////////////// cos ��
	// �ָ�
	//���Ǻ������������ķ�֮һ�ȵ�������������1024����
	BoonInt32* pi32Cos_360_SQ10;
	// �ָ�
	//���Ǻ������������ķ�֮һ�ȵ�������������65536����
	BoonInt32* pi32Cos_360_SQ16;

	///////////////////// tan ��
	// �ָ�
	//���Ǻ������������ķ�֮һ�ȵ�������������1024����
	BoonInt32* pi32Tan_360_SQ10;
	// �ָ�
	//���Ǻ������������ķ�֮һ�ȵ�������������1024����
	BoonInt32* pi32Tan_360_SQ16;

	///////////////////// atan ��
	// �ָ�
	BoonInt32* pi32ATan_360_SQ10;
	
	///////////////////// ��
	// �ָ�
	BoonFloat32* pf32ExpDivision;

	///////////////////// ����ת����
	// ����
	// opencv����ת�����[-128, 255]
	BoonFloat32* pf32Int2F32_OpenCV; // int->float 

}Boon_ALG_LOOKUPTABLE_S;

Boon_EXPORTS Boon_ALG_LOOKUPTABLE_S 	g_stLookUpTable;

#ifdef __cplusplus
}
#endif

#endif

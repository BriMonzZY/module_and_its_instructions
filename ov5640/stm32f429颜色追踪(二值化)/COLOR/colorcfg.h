#ifndef colorcfg_h
#define colorcfg_h

#include "color.h"


/*����ɫ���ѯ�ķ�Χ  ͼ����LCD������*/
#define IMG_X 120			      		//ͼƬx����120
#define IMG_Y 240               //ͼƬy����240 
#define IMG_W 240             	//ͼƬ���240
#define IMG_H 320            	 	//ͼƬ�߶�320

#define ALLOW_FAIL_PER       2     //�ݴ���Խ�� ��ɫƥ��Խ�ߣ�ҲԽ��ʶ�� ȡֵ>1

#define COLOR_RANG           30    //�趨��ɫ��ƫ�Ʒ�Χ Խ��Խ����ʶ�� ̫��������ʶ��
#define COLOR_NUM            7     //�趨׷����ɫ����Ŀ
#define OBJECT_NUM          4     //�趨׷����������
extern u8 global_page;									//��ǰ��ɫ��
extern u8 color_list[COLOR_NUM][7+7];		//��ɫ�ַ�
extern SEARCH_AREA_t area[OBJECT_NUM+1];							//������������
extern RESULT_t result[OBJECT_NUM];			//�����������
extern TARGET_CONDITION_t condition[COLOR_NUM];//����Ŀ�����
extern Quadrant		Quadrant_control;


#define LCD_READPOINT( usX, usY )  LCD_ReadPoint(usX,usY)//������㺯��

#endif


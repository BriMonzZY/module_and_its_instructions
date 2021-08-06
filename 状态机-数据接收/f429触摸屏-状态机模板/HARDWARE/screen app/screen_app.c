/**
 *    ��������Ӧ����
 *		״̬��״ִ̬�к���
 *		��Ļ���ƺ���
 */


#include "screen_app.h"

/* �������� */
u8 t=0;
u8 i=0;
u16 lastpos[5][2];		/* ���һ�ε����� */


////////////////////////////////////////////////////////////////////////////////
//���ݴ�����ר�в���
//��ˮƽ��
//x0,y0:����
//len:�߳���
//color:��ɫ
void gui_draw_hline(u16 x0,u16 y0,u16 len,u16 color)
{
	if(len==0)return;
    if((x0+len-1)>=lcddev.width)x0=lcddev.width-len-1;	//�������귶Χ
    if(y0>=lcddev.height)y0=lcddev.height-1;			//�������귶Χ
	LCD_Fill(x0,y0,x0+len-1,y0,color);	
}


/**
 * @brief    	��ʵ��Բ
 * @param    	x0,y0:����
							r:�뾶
							color:��ɫ
 * @retval   	��
 */
void gui_fill_circle(u16 x0,u16 y0,u16 r,u16 color)
{											  
	u32 i;
	u32 imax = ((u32)r*707)/1000+1;
	u32 sqmax = (u32)r*(u32)r+(u32)r/2;
	u32 x=r;
	gui_draw_hline(x0-r,y0,2*r,color);
	for (i=1;i<=imax;i++) 
	{
		if ((i*i+x*x)>sqmax)// draw lines from outside  
		{
 			if (x>imax) 
			{
				gui_draw_hline (x0-i+1,y0+x,2*(i-1),color);
				gui_draw_hline (x0-i+1,y0-x,2*(i-1),color);
			}
			x--;
		}
		// draw lines from inside (center)  
		gui_draw_hline(x0-x,y0+i,2*x,color);
		gui_draw_hline(x0-x,y0-i,2*x,color);
	}
}  


/**
 * @brief   ������֮��ľ���ֵ 
 * @param   x1,x2����ȡ��ֵ��������
 * @retval  ����ֵ��|x1-x2|
 */
u16 my_abs(u16 x1,u16 x2)
{			 
	if(x1>x2)return x1-x2;
	else return x2-x1;
}  


/**
 * @brief    ��һ������
 * @param    (x1,y1),(x2,y2):��������ʼ����
						  size�������Ĵ�ϸ�̶�
						  color����������ɫ
 * @retval   ��
 */
void lcd_draw_bline(u16 x1, u16 y1, u16 x2, u16 y2,u8 size,u16 color)
{
	u16 t; 
	int xerr=0,yerr=0,delta_x,delta_y,distance; 
	int incx,incy,uRow,uCol; 
	if(x1<size|| x2<size||y1<size|| y2<size)return; 
	delta_x=x2-x1; //������������ 
	delta_y=y2-y1; 
	uRow=x1; 
	uCol=y1; 
	if(delta_x>0)incx=1; //���õ������� 
	else if(delta_x==0)incx=0;//��ֱ�� 
	else {incx=-1;delta_x=-delta_x;} 
	if(delta_y>0)incy=1; 
	else if(delta_y==0)incy=0;//ˮƽ�� 
	else{incy=-1;delta_y=-delta_y;} 
	if( delta_x>delta_y)distance=delta_x; //ѡȡ�������������� 
	else distance=delta_y; 
	for(t=0;t<=distance+1;t++ )//������� 
	{  
		gui_fill_circle(uRow,uCol,size,color);//���� 
		xerr+=delta_x ; 
		yerr+=delta_y ; 
		if(xerr>distance) 
		{ 
			xerr-=distance; 
			uRow+=incx; 
		} 
		if(yerr>distance) 
		{ 
			yerr-=distance; 
			uCol+=incy; 
		} 
	}  
}   

/* ****************************��Ļ����************************************* */

/**
 * @brief:		INIT��Ļ���ƺ���
 * @param:		none
 * @retval:		none
 */
void Draw_INIT_Screen(void)
{
	/* init������������ */
	
	LCD_Clear(WHITE);
	
	POINT_COLOR=BLUE;
	LCD_DrawRectangle(75, 220, 195, 270);	 	/* MANUAL */
	LCD_DrawRectangle(75, 270,195, 320);		/* AUTO1 */
	LCD_DrawRectangle(75, 320, 195, 370); 	/* AUTO2 */
	LCD_DrawRectangle(75, 370, 195, 420); 	/* FOLLOW */
	POINT_COLOR=CYAN;
	LCD_ShowString(100,20,120,120,24,"WELCOM");
  LCD_ShowString(90,230,100,100,32,"MANUAL");
	LCD_ShowString(95,280,100,100,32,"AUTO1");
  LCD_ShowString(95,330,100,100,32,"AUTO2");	
	LCD_ShowString(95,380,100,100,32,"FOLLOW");	
}

void Draw_MAUAL_Screen(void)
{
	
}

void Draw_AUTO1_Screen(void)
{
	
}

void Draw_AUTO2_Screen(void)
{
	
}

void Draw_FOLLOW_Screen(void)
{
	
}


/* ***************************************״̬��������(��while(1)��ִ��)***************************** */


/**
 * @brief:		INIT��������
 * @param:		none
 * @retval:		none
 */
void INIT_Action(void)
{
	/* �������� */
	if(screen_cnt == 1){
		/* ״̬�л� */
		/**************MANUAL****************/
		if(tp_dev.x[t] >= 75 && tp_dev.x[t] <= 195 && tp_dev.y[t] >= 220 && tp_dev.y[t] <= 270){
			BEEP_ONCE();
			Init_To_Manual();  /* ����״̬ת�ƺ��� */
		}
		/**************AUTO1****************/
		if(tp_dev.x[t] >= 75 && tp_dev.x[t] <= 195 && tp_dev.y[t] >= 270 && tp_dev.y[t] <= 320){
			BEEP_ONCE();
			Init_To_Auto1();
		}
		/**************AUTO2****************/
		if(tp_dev.x[t] >= 75 && tp_dev.x[t] <= 195 && tp_dev.y[t] >= 320 && tp_dev.y[t] <= 370){
			BEEP_ONCE();
			Init_To_Auto2();
		}
		/**************FOLLOW****************/
		if(tp_dev.x[t] >= 75 && tp_dev.x[t] <= 195 && tp_dev.y[t] >= 370 && tp_dev.y[t] <= 420){
			BEEP_ONCE();
			Init_To_Follow();
		}
	}
}






void Button_App(void)
{
	printf("%d %d \n", tp_dev.x[t], tp_dev.y[t]);  // �������
}

# 激光测距


​	深圳维特公司的激光测距模块，使用normal模式，模块会不停的回传距离数据，通过固定的规律，寻找数据流中的距离信息，解算代码：

```C
/* 处理激光测距的距离数据   直接将距离值赋值给distance  阻塞式接收 */
void Distance_Process(void)
{
	unsigned int zero[100] = {0};
	uint16_t distance_tmp = 0, i;
	unsigned int distance_tmp_cnt = 0;
    HAL_UART_Receive(&huart6, temp_uart6, 64, 1000);  /* 接受数据 */

    /*
    for(i = 0; i < 64; i++) {
        printf("%d ", temp_uart6[i]);
    }
    printf("\n");
    */

    distance_tmp = 0;
    for(i = 0; i < 64; i++) {
        /* d: 1405 mm
             100 58 32 49 52 48 53 32 109 109
        */
        if(temp_uart6[i] == 100 && temp_uart6[i+1] == 58 && temp_uart6[i+2] == 32) {
            stack_push(&distance_stack, temp_uart6[i]);
            stack_push(&distance_stack, temp_uart6[i+1]);
            stack_push(&distance_stack, temp_uart6[i+2]);
        }
        /* 接收距离信息 */
        if(distance_stack.stack[0] == 100 && distance_stack.stack[1] == 58 && temp_uart6[i] != 109 && temp_uart6[i+1] != 109) {
            stack_push(&distance_stack, temp_uart6[i]);
        }
        /* 数据完整 */
        if(distance_stack.stack[0] == 100 && distance_stack.stack[1] == 58 && temp_uart6[i] == 109 && temp_uart6[i+1] == 109) {
            stack_push(&distance_stack, temp_uart6[i]);
            stack_push(&distance_stack, temp_uart6[i+1]);

            stack_pop(&distance_stack);
            stack_pop(&distance_stack);
            stack_pop(&distance_stack);

            while(distance_stack.stack[distance_stack.stack_top] != 32) {  /* 数据计算 */
                //printf("%d ", distance_stack.stack[distance_stack.stack_top]-48);
                distance_tmp = distance_tmp + (distance_stack.stack[distance_stack.stack_top]-48)*pow(10, distance_tmp_cnt++);
                stack_pop(&distance_stack);
            }
            if(distance_stack.stack[distance_stack.stack_top] == 32) {  /* 数据完整等待接收下一次 */
                memcpy(distance_stack.stack, zero, 100);
                distance_stack.stack_top = 0;
                distance_tmp_cnt = 0;
                distance = distance_tmp;
                //printf("distance: %d\n\n", distance);
                distance_tmp = 0;
            }
            if(distance_stack.stack[0] == 100 && distance_stack.stack[1] == 58 && i == 63) {  /* 没有结尾数据不完整 */
                memcpy(distance_stack.stack, zero, 100);
                distance_stack.stack_top = 0;
            }
        }
    }
}
```

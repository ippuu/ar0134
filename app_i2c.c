#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <unistd.h>

#include "ar0134.h"

#define DEVICE_FILE "/dev/ar0134_misc"

enum CMD {READ_CMD = 1, WRITE_CMD};
int main ()
{
    ar0134_add_data ar0134_param;
    
    int dev;
    int cnt;
    int temp;
    int add_temp,data_temp;
    //device Access (device file open)
    dev = open(DEVICE_FILE,O_RDWR | O_NDELAY);
    if(dev < 0)
    {
            printf ("device open err\r\n");
            
    }   
    
    while (1)
    {
 		printf("[1]Address Read\r\n");
		printf("[2]Address Data Write\r\n");
		//printf("[3]GPIO ON_OFF\r\n");
		//printf("[4]GPIO Timing Setting\r\n");
		
		scanf("%d",&cnt);
		if((cnt > 10) || (cnt <0 ) )
		{cnt = 0;}
		
        
        switch(cnt)
        {
                case READ_CMD:
                printf ("put register address (hex value)\r\n");
                
                do{
                    scanf("%04x",&temp);}while(temp>0xFFFF);
                ar0134_param.address = (unsigned short)temp;
                
                printf("Read Address : %04x\r\n", ar0134_param.address);
                ioctl(dev,READ_DATA,&ar0134_param);
                
                while (1)
                {
                    if(ar0134_param.flag == 1)
                    break;
                    usleep(1000);
                }
                printf ("Read Address Data : [%04x]\r\n",ar0134_param.data);         
                break;
                
                
                
                //write -> reg write -> reg read -> verify reg
                case WRITE_CMD:
                
                printf ("put register address (hex value)\r\n");
                do{scanf("%04x",&add_temp);}while(add_temp>0xFFFF);
                ar0134_param.address = (unsigned short)add_temp;
                
                printf ("put register DATA (hex value)\r\n");
                do{scanf("%04x",&data_temp);}while(data_temp>0xFFFF);
                ar0134_param.data = (unsigned char)data_temp;
                
                                
                ioctl(dev,WRITE_DATA,&ar0134_param);
                while (1)
                {
                    if(ar0134_param.flag == 1)
                    break;
                    usleep(1000);
                }
                
                if(ar0134_param.data != (unsigned char)data_temp)
                {
                        printf ("Write Fail!!- data value : [%04x]\r\n",ar0134_param.data);
                }
                
                else {printf("Write Success - Verify ok!!\r\n");}
                              
                
                break;
                
                
                
                
                break;
                
                
                default:
                break;
        }
        cnt = 0;
        
        
        
    
    }
    
    return close(dev);
    
}

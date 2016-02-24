#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <unistd.h>

#include "ar0134.h"

#define DEVICE_FILE "/dev/ar0134_misc"

#define ARRAY_SIZE(x) (sizeof(x) / sizeof(*(x)))
#define CLR_BIT(x,y)      ((x) &= ~(1<<(y)) )
#define SET_BIT(x,bit)    (x |= bit)

#define CHK_BIT(x,y)      (((x) & (1<<(y))) >> (y))
extern unsigned short res640x480_init[];

enum CMD {READ_CMD = 1,
    WRITE_CMD,              //2
    VGA_MODE,               //3
    SXGA_MODE,              //4
    CLOCK_SETTING_MODE,     //5
    GAIN_SETTING,           //6
    TEST_PT_COLRO_BAR,      //7
    TEST_PT_SOLID_BAR,      //8
    FLIP_MODE,              //9
    MIRROR_MODE,            //10
    TRG_LIVE_MODE,          //11
    WINDOW_CTRL_MODE,       //12
    AUTO_EXPOSURE_MODE,     //13
    };






void hex_to_bin(unsigned short hex);

int i2c_read(int *dev, ar0134_add_data *param);
int i2c_write(int *dev, ar0134_add_data *param);
int Resolution_change(int *dev, ar0134_add_data *param,int mode);
int Tigger_change(int *dev, ar0134_add_data *param);
int Clock_setting(int *dev, ar0134_add_data *param);
int Test_pattern_mode(int *dev, ar0134_add_data *param);
int Gain_switch(int *dev, ar0134_add_data *param);
void Press_any_key();



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
 		printf("\
   ============================================\r\n\
                AR0134 Image Sensor            \r\n\
                Control Application            \r\n\
   ============================================\r\n\r\n");

        printf("[1]Address Read\r\n");
		printf("[2]Address Data Write\r\n");
        printf("[3]Resolution Change 640*480\r\n");
		printf("[4]Resolution Change 1280*960\r\n");
        printf("[5]System Clock Setting\r\n");
        printf("[6]Gain Setting \r\n"); //R,G,B , or
        printf("[7]Test Pattern Corlor Bar Mode\r\n");
        printf("[8]Test Pattern Solide Mode\r\n");
        printf("[9]Filp Mode\r\n");
        printf("[10]Mirror Mode\r\n");
        printf("[11]Trigger Mode / Video Mode Change\r\n");//Read Mode->Change Mode
        printf("[12]Window Control Mode\r\n");
        printf("[13]Auto Exposure Mode\r\n");


		scanf("%d",&cnt);



        switch(cnt)
        {
                case READ_CMD:

                scanf("%04x",&temp);
                ar0134_param.address = (unsigned short)temp;

                if (i2c_read(&dev,&ar0134_param) < 0)
                {
                    printf("READ Fail\r\n");
                    break;
                }
                printf ("Read Address Data : [%04x]\r\n",ar0134_param.data);
                hex_to_bin(ar0134_param.data);
                Press_any_key();
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
                Press_any_key();
                break;




                case VGA_MODE:               //[3] 640*480
                if (Resolution_change(&dev, &ar0134_param,VGA_MODE) < 0 )
                {
                        printf("vga mode initialize fail\r\n");
                }
                printf("VGA Mode Initialized Complete. \r\n\r\n\r\n\r\n");
                Press_any_key();
                break;




                case SXGA_MODE:              //[4] 1280*960
                if (Resolution_change(&dev, &ar0134_param,SXGA_MODE) < 0 )
                {
                        printf("SXGA mode initialize fail\r\n");
                }
                printf("SXGA Mode Initialized Complete. \r\n\r\n\r\n\r\n");
                Press_any_key();
                break;

                case CLOCK_SETTING_MODE:     //[5]
                Clock_setting(&dev,&ar0134_param);
                Press_any_key();
                break;

                case GAIN_SETTING:           //[6]
                if (Gain_switch(&dev,&ar0134_param) < 0)
                {
                    printf("Gain setting change fail\r\n");
                }
                Press_any_key();
                break;

                case TEST_PT_COLRO_BAR:      //7
                if (Test_pattern_mode(&dev,&ar0134_param) < 0)
                {
                    printf("test pattern Mode Setting Fail");
                }
                Press_any_key();
                break;

                case TEST_PT_SOLID_BAR:      //8
                Press_any_key();
                break;

                case FLIP_MODE:              //9
                Press_any_key();
                break;

                case MIRROR_MODE:            //10
                Press_any_key();
                break;

                case TRG_LIVE_MODE:          //11
                if (Tigger_change(&dev, &ar0134_param) < 0 )
                {printf("mode change fail!!\r\n");}
                else{printf("mode change Success!!\r\n");}
                Press_any_key();
                break;

                case WINDOW_CTRL_MODE:       //12
                Press_any_key();
                break;

                case AUTO_EXPOSURE_MODE:      //13
                Press_any_key();
                break;


                case 14:
                scanf("%04x",&add_temp);
                printf("%x\r\n",add_temp);
                hex_to_bin((unsigned short)add_temp);
                Press_any_key();

                default:
                break;
        }

        cnt = 0;




    }

    return close(dev);

}



//Regiseter Read
int i2c_read(int *dev, ar0134_add_data *param)
{

    int time_out=0;


    //printf("Read Address : %04x\r\n",param->address);

    ioctl(*dev,READ_DATA,&(*param));
    
    while(1)
          {
              if(param->flag == 1)
              break;

              if (time_out>200) //1sec
                {
                    return -1;//device fail
                }

              usleep(5000);
              time_out++;

        }

    return 0;

}

int i2c_write(int *dev, ar0134_add_data *param)
{
    int time_out=0;
    //printf("Write Address : %04x\r\n", param->address);
    ioctl(*dev,WRITE_DATA,&(*param));
    while(1)
    {
        if(param->flag == 1)
        break;

        if (time_out>200) //1sec
        {
            return -1;//device fail
        }

        usleep(5000);
        time_out++;
    } //while

        time_out = 0;
}

int Resolution_change(int *dev, ar0134_add_data *param,int mode)
{
    int time_out=0,i;

    for(i=0;i<ARRAY_SIZE(res640x480_init);i++)
    {
        if (mode == VGA_MODE) //VGA Initialize
        {
            param->address = res640x480_init[i]; //address
            param->data = res640x480_init[i+1]; //data
        }

        else if (mode == SXGA_MODE) //1280*960 Initialize
        {
            param->address = res1280x960_init[i]; //address
            param->data = res1280x960_init[i+1]; //data
        }

        else{}
        //
        i++;
    }//for i=o

    return 0;
}


//Register Read -> mode check -> mode_Change

int Tigger_change(int *dev, ar0134_add_data *param)
{

    unsigned short reg;


    param->address = RESET_REGISTER;


    //Read Reset Address Data
    i2c_read(&(*dev),&(*param));




    reg=param->data; //reset register Read
    printf ("Reset Register Status : ");
    hex_to_bin(param->data); // register Value view
    
    //AR0134_DG.PDF 21Page
    if (CHK_BIT(reg,2)) //check Stream bit :1 Maseter Mode(video Mode)
    {
        CLR_BIT(reg,2); //stream bit clear : Trigger Mode Enable
        SET_BIT(reg,8); // GPI_EN
        printf ("Change Trigger Mode reset Register value : ");
        hex_to_bin(reg); // register Value view

        param->data = reg;


    }

    else// stream bit :0 Trigger Mode
    {
        SET_BIT(reg,2); // stream bit set : Video Mode Enable
        printf ("Change Video Mode reset Register value : ");
        hex_to_bin(reg); // register Value view
        param->data = reg;
    }


    //Write Reset Address Trigger & Video Mode Change Data
    i2c_write(&(*dev),&(*param));

    return 0;
}


int Clock_setting(int *dev, ar0134_add_data *param)
{
    int ret;
    unsigned short temp;
    unsigned short p_mul,pre_pll,vt_sys,vt_pix;
    char key[1];
    float pixel_clk;
    //1.bringu up -> reset register(0x301A)[2]bit=0
    //2. set up pll setting
    //pixel_clk = (External CLK * pll multiplier) / (pre_pll_clk_div* vt_sys_clk_div*vt_pix_xlk_div)
    //3. wait 1ms VCO locked
    //4. reset register (0x301A[2] = 1)
    
    
    
    param->address = RESET_REGISTER;    
    ret = i2c_read(&(*dev),&(*param));
    if(ret < 0)
        return -1; //read fail    
    CLR_BIT(param->data,2); // bit 2 Clear
    param->address = RESET_REGISTER;
    
    ret = i2c_write(&(*dev),&(*param));
     if(ret < 0 )
        return -1;
        
    ////set up PLL Register
    //PLL_Multiplier : 0x3030 - PLL_MULTILIER
    //PRE_PLL_CLK_DIV : 0x302E - PRE_PLL_CLK_DIV
    //vt sys_clk div : 0x302C - VT_SYS_CLK_DIV
    //vt pix clk div : 0x302A - VT_PIX_CLK_DIV

    param->address = PLL_MULTILIER;  
    ret = i2c_read(&(*dev),&(*param));
    if(ret <0 )
        return -1;
    p_mul = param->data; // PLL MULTIPLIER READ Data
    
    param->address = PRE_PLL_CLK_DIV;  
    ret = i2c_read(&(*dev),&(*param));
    if(ret <0 )
        return -1;
    pre_pll = param->data;// PRE_PLL_CLK_DIV READ Data
    
    param->address = VT_SYS_CLK_DIV;
    ret = i2c_read(&(*dev),&(*param));
    if(ret <0 )
        return -1;
    vt_sys = param->data; //VT_SYS_CLK_DIV Read DATA
    
    param->address = VT_PIX_CLK_DIV;
    ret = i2c_read(&(*dev),&(*param));
    if(ret <0 )
        return -1;
    vt_pix= param->data; //VT_PIX_CLK_DIV Read Data
    
    
    
    
    
     
     
     
    
    
//2. set up pll setting
    while(1)
    {
        //
        printf("PLL_MULTIPLIER Value : %d\r\n",p_mul);
        printf("PRE_PLL_CLK_DIV Value : %d\r\n",pre_pll);
        printf("VT_SYS_CLK_DIV Value : %d\r\n",vt_sys);
        printf("VT_PIX_CLK_DIV Value : %d\r\n",vt_pix);
        
        //calculrate Clock    
        pixel_clk= (EXTENAL_CLK*p_mul) / (pre_pll*vt_sys*vt_pix);
        printf("System Clock : [%f]\r\n",pixel_clk);
        
        printf("Press 'U' Key Clock Up\r\n");
        printf("Press 'D' Key Clock Down\r\n");
        printf("Press 'S' funtion Stop\r\n");
        
        scanf ("%s",key);
        if ((key[0] == 'U') || (key[0] == 'u'))
        {
            param->address = VT_SYS_CLK_DIV;  
            ret = i2c_read(&(*dev),&(*param));
            if(ret <0 )
                return -1;
                
            param->data +=1; //vt_sys clk Div 
            
            ret = i2c_write(*(&dev),*(&param));
            if (ret < 0)
                return -1;        
        }    
            
    
        
        else if ((key[0]== 'D') || (key[0]== 'd'))
        {
            param->address = VT_SYS_CLK_DIV;  
            ret = i2c_read(&(*dev),&(*param));
            if(ret <0 )
                return -1;
                
            param->data -=1; //vt_sys clk Div 
            
            ret = i2c_write(*(&dev),*(&param));
            if (ret < 0)
                return -1;            
        }
        
        else if ((key[0]== 'S') || (key[0]== 's'))
        {
                break;
        }
        
        else
        {printf("Not valid !\r\n");}        
        
     }
     
//3. wait 1ms VCO locked
     usleep(10000);
     
//4. reset register (0x301A[2] = 1)
    param->address = RESET_REGISTER;    
    ret = i2c_read(&(*dev),&(*param));
    if(ret < 0)
        return -1; //read fail    
    SET_BIT(param->data,2); // bit 2 set
    param->address = RESET_REGISTER;
    
    ret = i2c_write(&(*dev),&(*param));
     if(ret <0 )
        return -1;
    
    return 0;
}


int Test_pattern_mode(int *dev, ar0134_add_data *param)
{
    int key;
    int ret;
    while(1)
    {
        printf("Test Pattern Select\r\n");
        printf("[0] Nomal operation(General Output)\r\n");
        printf("[1]Solid Color test pattern\r\n");
        printf("[2]100% Color Bar test Pattern\r\n");
        printf("[3]fade to gray color bar test pattern\r\n");
        
        
        scanf("%d",&key);
        
        
        
        //solid Color pattern
        if ((  key >= 0 ) || ((  key <= 3 ) )
        {
            //1.Read TEST_PATTERN_MODE
            //2. set Data
            //3. write TEST_PATTERN_MODE Register
            param->address = TEST_PATTERN_MODE;            
            param->data = (unsigned short)key;
            
            ret= i2c_write(&(*dev),&(*param));
            if (ret < 0)
                return -1;          
        }        
                
        else
        {printf("Not valid !\r\n");}
        
        key = 0;
    }
    
    return ret;
}



void hex_to_bin(unsigned short hex)
{
    int i=0;
    volatile unsigned temp;

    for (i=0;i<16;i++)
    {
        temp=(hex<<i);
        if ((temp & 0x8000) && 0x8000)
        { printf ("1");}

        else { printf ("0"); }

        if(i==3 | i ==7 | i==11)
        printf(" ");
    }

    printf("\r\n");
}

int Gain_switch(int *dev, ar0134_add_data *param)
{
    int ret;
    
    param->address = AE_CTRL_REG;
    
    ret = i2c_read(*(&dev),&(*param));
    if (ret < 0)
        return -1;
    
    if (CHK_BIT(param->data,1)) // if auto gain Mode
    {
        CLR_BIT(param->data,1);//disable auto gain
        printf("DISABLE Auto Gain\r\n");
        
    }
    else  
    {   
        SET_BIT(param->data,1); //Enable Auto gain
        printf("ENABLE Auto Gain\r\n");
    } 
    
    param -> address = AE_CTRL_REG;
    ret = i2c_write(&(*dev),&(*param));
    if (ret < 0)
        return -1;
    
        
    return 0;

}

void Press_any_key()
{
    char temp[1];
    printf("Press Any Key.................\r\n");
    scanf("%s",temp);
    system("clear");
}

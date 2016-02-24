//
//AR0134 Image Sensor I2C Driver
//
//

#include <linux/init.h>
#include <linux/fs.h>
#include <linux/errno.h>
#include <linux/types.h>
#include <linux/fcntl.h>
#include <linux/slab.h>
#include <linux/kernel.h>
#include <linux/i2c.h>
#include <linux/module.h>
#include <linux/miscdevice.h>


#include <asm/uaccess.h>
#include <asm/io.h>
#include <media/ar0134.h> //include/media/ar0134.h



////////////////////////
////
#define DEBUG_MODE 1
//
///////////////////////
struct ar0134 {
		struct i2c_client *ar0134_client; 

};







struct ar0134 *p_ar0134;

static int ar0134_write_byte(const struct i2c_client *client, u16 reg_add, u8 data);
static int ar0134_read_byte(const struct i2c_client *client,u16 reg_add);
static int ar0134_register_write(const struct i2c_client *client,u16 reg_add,u16 data);
static int ar0134_register_read(const struct i2c_client *client,u16 reg_add);
static void ar0134_camera_initialize(const struct i2c_client *client);







static int ar0134_write_byte(const struct i2c_client *client, u16 reg_add, u8 data)
{

		char msg[3];
		int ret;
		
		//i2c Address half word -> byte Converting
		msg[0] = (u8)(reg_add >> 8);
		msg[1] = (u8)(reg_add & 0xFF);

		//i2c data (half word) -> byte convering
		msg[2] = data;
		

	   printk(" msg[0] : %x\r\n msg[1] : %x\r\n msg[2] : %x\r\n",msg[0],msg[1],msg[2]);	
		
		ret = i2c_master_send(client,(char*)&msg,sizeof(msg)); // i2c,msage (address 2byte,data2byte),count
		if (ret < 0){
				printk("Write Err : %s,LINE: %d\r\n", __func__,__LINE__);
				return ret;
		}

		return 0;
}


static int ar0134_read_byte(const struct i2c_client *client,u16 reg_add)
{
	char msg[4];
	int ret;
	//i2c Register Address
	msg[0] = (u8)(reg_add >> 8);
	msg[1] = (u8)(reg_add & 0xFF);
	

	ret = i2c_master_send(client,(char *) &msg, sizeof(msg));
	if(ret < 0 )
		printk("%s,LINE: %d\r\n", __func__,__LINE__);	

	ret = i2c_master_recv(client,msg,1); //address 2byte
	if(ret != 1)
        printk("%s,LINE: %d\r\n", __func__,__LINE__);
	
	return (int)msg[0];

}


//2byte Data Write 
//@reg_add : AR0134 Register Base Address 
//@data : 2byte data Write
//
//ex: Register reg_add 0x3000 / data : 0xFFAA
//	[Register] : [Value]	
//  [0x3000]   : [0xFF] 
//  [0x3001]   : [0xAA]

static int ar0134_register_write(const struct i2c_client *client,u16 reg_add,u16 data)
{
	char data_h,data_l;
	int ret;
	data_h = (char)(data >> 8);
	data_l = (char)(data & 0xFF);
	ret = ar0134_write_byte (client, reg_add, data_h);
	if (ret < 0){
			return ret;
	}

	ret = ar0134_write_byte (client, reg_add+1, data_l);
	if (ret < 0){
			return ret;
	}

	return 0;
}

//2byte Data Read
//@reg_add : AR0134 Register base address
//retrun : negative : errono or Reg
static int ar0134_register_read(const struct i2c_client *client,u16 reg_add)
{
	int ret=0;
	int data=0;

	ret = ar0134_read_byte(client,reg_add);
	if (ret < 0){
			printk("%s,LINE: %d\r\n",__func__,__LINE__);
			return ret;
	}

	data =(ret << 8);

	ret = ar0134_read_byte(client,reg_add+1);
	if (ret < 0){
			printk("%s,LINE: %d\r\n",__func__,__LINE__);
			return ret;
	}

	data |= ret;

	return data;
}


static void ar0134_camera_initialize(const struct i2c_client *client)
{
		
	unsigned int i;
#ifdef DEBUG_MODE	
    //int i,data_temp;
	printk("%s\r\n",__func__);

	
	printk ("AR0134 CHIP_VERSION :0X%04x \r\n",ar0134_register_read(client,CHIP_VER));
    printk("ar0134 initialize register_data array count : %d\r\n",ARRAY_SIZE(res640x480_init));
/*
	for (i=0;i<10;i++)
	{ 
        data_temp = ar0134_register_read(client,CHIP_VER); 
        printk("AR0134 CHIP Version Read For loop : %d\r\n",i);
    }
*/
#endif

    for(i=0;i<ARRAY_SIZE(res640x480_init);i++)
    {
        #ifdef DEBUG_MODE
        printk("ar0134_init address: [%x]  Data: [%04x]\r\n",res640x480_init[i],res640x480_init[i+1]);
        #endif
        
        //                            address          ,  data     
        ar0134_register_write(client,res640x480_init[i],res640x480_init[i+1]);
        i++;
    }
    
    

}


static int ar0134_probe(struct i2c_client *i2c, const struct i2c_device_id *id)
{
	
    //struct ar0134 *p_ar0134;
	
	//struct i2c_adapter *adapter = to_i2c_adapter(i2c->dev.parent);

	printk("ar0134 I2C Driver probe\r\n");

	p_ar0134 = kzalloc(sizeof(struct ar0134), GFP_KERNEL);
	if(!(p_ar0134))
		return -ENOMEM;
	
	i2c_set_clientdata(i2c,p_ar0134);
	p_ar0134->ar0134_client = i2c;

	
	
	//AR0134 Image sensor Initialize
	ar0134_camera_initialize(p_ar0134->ar0134_client);

	return 0;
}


static int ar0134_remove(struct i2c_client *i2c)
{
        //Memoey free
		printk("%s\r\n",__func__);
        kfree(i2c_get_clientdata(i2c));
		return 0;

}

//
//
//
// AR0134 chrdriver area
//
static int ar0134_open (struct inode *inode, struct file *filp)
{
        printk("%s\r\n",__func__);
        return 0;
}

static int ar0134_release(struct inode *inode, struct file *filp)
{
        printk("%s\r\n",__func__);
        return 0;
}

//
//             ar0134 IOCTL
//

static long ar0134_ioctl(struct file *filp, unsigned int cmd, unsigned long arg)
{
    ar0134_add_data ar0134_param;
    int err, size, ret;
    
    // Magic number check
    if(_IOC_TYPE(cmd) != AR0134_MAGIC ) return -EINVAL;
    if(_IOC_NR(cmd) >= AR0134_COMMAND_CNT) return -EINVAL;
    
    size = _IOC_SIZE(cmd);
    
    if (size)
    {
        err = 0;
        
        if(_IOC_DIR(cmd) & _IOC_READ ) 
        err = !access_ok(VERIFY_WRITE,(void __user *)arg,size);
        else if(_IOC_DIR(cmd) & _IOC_WRITE )
        err = !access_ok(VERIFY_READ,(void __user *)arg,size);
        
        if(err) return err;
    }
    
    switch (cmd)
    {
        case READ_DATA: // require register read data
        //application -> kernel (received register address)
        ret = copy_from_user((void *)&ar0134_param,(const void *)arg,size);
        
        //Read Register value
        printk("application require Address : [%04x]\r\n",ar0134_param.address);
        
        ar0134_param.address = ar0134_register_read(p_ar0134->ar0134_client,ar0134_param.address);
        ar0134_param.data = ar0134_register_read(p_ar0134->ar0134_client,ar0134_param.address);
        ar0134_param.flag = 1; //data wire complete flag (User area check flag)
        printk("Read Address : [%04x]\r\n Read Data : [%04x]\r\n",ar0134_param.address,ar0134_param.data);
                
        //kernel -> allpication send data
        ret = copy_to_user ((void *)arg,(const void *)&ar0134_param,(unsigned long) size);
        ar0134_param.flag = 0;
        break;
        
        
        
        case WRITE_DATA :
        ret = copy_from_user((void *)&ar0134_param,(const void *)arg,size);
        
        //write Register data
        ar0134_register_write(p_ar0134->ar0134_client,ar0134_param.address,ar0134_param.data);
        
        //read from register
        ar0134_param.data = ar0134_register_read(p_ar0134->ar0134_client,ar0134_param.address);
        
        //data wire complete flag (User area check flag)
        ar0134_param.flag = 1; 
        
        //kernel -> allpication send data
        ret = copy_to_user ((void *)arg,(const void *)&ar0134_param,(unsigned long) size);
        ar0134_param.flag = 0;
        break;
        
        case CMD_MODE: //command Mode
        ret = copy_from_user((void *)&ar0134_param,(const void *)arg,size);
        
        //reserve area
        switch (ar0134_param.command)
        {
            default:            
            break;
        }  
        break;
        
        
        default :
        break;
    }
    
    return 0;
}




static const struct i2c_device_id ar0134_id[] = {
			{ "ar0134", 0 },
			{},
			 };
MODULE_DEVICE_TABLE(i2c, ar0134_id);



static struct i2c_driver ar0134_driver = {
			.driver = {
						.owner	= THIS_MODULE,
						.name	= "ar0134",
			},
			.probe		= ar0134_probe,
			.remove		= ar0134_remove,
			.id_table	= ar0134_id,
};

struct file_operations ar0134_fops=
{
        .owner              = THIS_MODULE,
        .unlocked_ioctl   =  ar0134_ioctl,
        .open               = ar0134_open,
        .release           = ar0134_release,
};


static struct miscdevice ar0134_misc_drv ={
        .fops = & ar0134_fops,
        .name = "ar0134_misc",
        .minor = MISC_DYNAMIC_MINOR,
};


static int __init ar0134_init(void)
{
    int res;
     //if maching device name - call probe function
	 printk("%s,%d\r\n",__func__,__LINE__);
     //res = register_chrdev(I2C_MAJOR, AR0134_NAME, &ar0134_fops);
     res = misc_register(&ar0134_misc_drv);
     if (res<0){	
         printk("AR0134 chrdev Register Fail\r\n");
         return res;}
    
     
     return i2c_add_driver(&ar0134_driver);
}

 
static void __exit ar0134_exit(void)
{
     printk("%s\r\n",__func__);	
     //unregister_chrdev(I2C_MAJOR,AR0134_NAME);
     misc_deregister(&ar0134_misc_drv);
     i2c_del_driver(&ar0134_driver);
}


module_init(ar0134_init);
module_exit(ar0134_exit);
 
MODULE_DESCRIPTION("AR0134 I2C Control Driver"); 
MODULE_AUTHOR("Seok Jung <sjung8432@pnstech.net> http://www.pnstech.co.kr");
MODULE_LICENSE("Dual BSD/GPL");

/*

#include <zephyr/types.h>
#include <stddef.h>
#include <string.h>
#include <errno.h>
#include <sys/printk.h>
#include <sys/byteorder.h>
#include <zephyr.h>
#include <bluetooth/bluetooth.h>
#include <bluetooth/hci.h>
#include <bluetooth/conn.h>
#include <bluetooth/uuid.h>
#include <bluetooth/gatt.h>
#include <bluetooth/services/bas.h>
#include <bluetooth/services/hrs.h>
#include <drivers/i2c.h>
#include <drivers/sensor.h>
#include <devicetree.h>



static const struct bt_data ad[] = {
	BT_DATA_BYTES(BT_DATA_FLAGS, (BT_LE_AD_GENERAL | BT_LE_AD_NO_BREDR)),
	BT_DATA_BYTES(BT_DATA_UUID16_ALL,
		      BT_UUID_16_ENCODE(BT_UUID_HRS_VAL),
		      BT_UUID_16_ENCODE(BT_UUID_BAS_VAL),
		      BT_UUID_16_ENCODE(BT_UUID_DIS_VAL))
};

static void connected(struct bt_conn *conn, uint8_t err)
{
	if (err) {
		printk("Connection failed (err 0x%02x)\n", err);
	} else {
		printk("Connected\n");
	}
}

static void disconnected(struct bt_conn *conn, uint8_t reason)
{
	printk("Disconnected (reason 0x%02x)\n", reason);
}

BT_CONN_CB_DEFINE(conn_callbacks) = {
	.connected = connected,
	.disconnected = disconnected,
};

static void bt_ready(void)
{
	int err;

	printk("Bluetooth initialized\n");

	err = bt_le_adv_start(BT_LE_ADV_CONN_NAME, ad, ARRAY_SIZE(ad), NULL, 0);
	if (err) {
		printk("Advertising failed to start (err %d)\n", err);
		return;
	}

	printk("Advertising successfully started\n");
}

static void auth_cancel(struct bt_conn *conn)
{
	char addr[BT_ADDR_LE_STR_LEN];

	bt_addr_le_to_str(bt_conn_get_dst(conn), addr, sizeof(addr));

	printk("Pairing cancelled: %s\n", addr);
}

static struct bt_conn_auth_cb auth_cb_display = {
	.cancel = auth_cancel,
};






//LIS2DE12TR

void i2c_scan(void)
{
    const struct device *i2c_dev;
    int i, dev_count = 0;

    i2c_dev = DEVICE_DT_GET(DT_NODELABEL(i2c2));

    if (i2c_dev == NULL) {
        printk("Scanning I2C bus for devices....\n");
        return;
    }

    printk("Scanning I2C bus for devices....\n");



	for (i = 0; i < 128; ++i) {
        uint8_t dummy_data;
        int ret;

        struct i2c_msg msgs[1] = {
            {
                .buf = &dummy_data,
                .len = 0,
                .flags = I2C_MSG_READ,
            }
        };

        ret = i2c_transfer(i2c_dev, &msgs[0], 1, i);

        if (ret == 0 || ret == -ENODEV) {
            // If ret == 0, device acknowledged the address
            // If ret == -ENODEV, no device responded
            printk("I2C device found at Address 0x%02X\n", i);
            dev_count++;
        }
    }

	if (dev_count == 0) {
        printk("No I2C devices found.\n");
        
    }
	
    printk("I2C scan complete with device count: %d\n", dev_count);

}


void i2c_scan(void)
{
    const struct device *i2c_dev;
    int i, dev_count = 0;

    i2c_dev = DEVICE_DT_GET(DT_NODELABEL(i2c2));

    if (i2c_dev == NULL) {
        printk("I2C: Device not found!\n");
        return;
    }

    printk("Scanning I2C bus for devices....\n");

	

	for (i = 0; i < 128; ++i) {
        uint8_t dummy_data;
        int ret;

        struct i2c_msg msgs[1] = {
            {
                .buf = &dummy_data,
                .len = 0,
                .flags = I2C_MSG_READ,
            }
        };

        ret = i2c_transfer(i2c_dev, &msgs[0], 1, i);

        if (ret == 0 || ret == -ENODEV) {
            // If ret == 0, device acknowledged the address
            // If ret == -ENODEV, no device responded
            printk("I2C device found at address 0x%02X\n", i);
            dev_count++;
        }
    }
	

    printk("I2C scan complete.\n");

	
}



void main(void)
{
	int err;

	os_mgmt_register_group();
	img_mgmt_register_group();
	stat_mgmt_register_group();

	err = bt_enable(NULL);
	if (err) {
		printk("Bluetooth init failed (err %d)\n", err);
		return;
	}

	bt_ready();

	//bt_conn_cb_register(&conn_callbacks);
	bt_conn_auth_cb_register(&auth_cb_display);

	err = smp_bt_register();

	if (err) {
	printk("SMP BT register failed (err: %d)", err);
	}


	while (1) {
		k_sleep(K_SECONDS(1));
		printk("----\n");

		
		//#########################################pragma endregion

		i2c_scan();
		
	}	
}





CONFIG_BT=y
CONFIG_BT_DEBUG_LOG=y
CONFIG_BT_SMP=y
CONFIG_BT_PERIPHERAL=y
CONFIG_BT_DIS=y
CONFIG_BT_DIS_PNP=n
CONFIG_BT_BAS=y
CONFIG_BT_HRS=y
CONFIG_BT_DEVICE_NAME="Smartwatch"
CONFIG_BT_DEVICE_APPEARANCE=194


CONFIG_STDOUT_CONSOLE=y
CONFIG_I2C=y
CONFIG_GPIO=y
CONFIG_SENSOR=y
CONFIG_CBPRINTF_FP_SUPPORT=y
CONFIG_RTT_CONSOLE=y
CONFIG_USE_SEGGER_RTT=y
CONFIG_PRINTK=y

# Enable mcumgr.
CONFIG_MCUMGR=y

# Enable flash operations.
CONFIG_FLASH=y

# Required by the `taskstat` command.
CONFIG_THREAD_MONITOR=y


# Some command handlers require a large stack.
CONFIG_SYSTEM_WORKQUEUE_STACK_SIZE=2048

# Ensure an MCUboot-compatible binary is generated.
CONFIG_BOOTLOADER_MCUBOOT=y



# Enable statistics and statistic names.
CONFIG_STATS=y
CONFIG_STATS_NAMES=y

# Enable most core commands.
CONFIG_MCUMGR_CMD_IMG_MGMT=y
CONFIG_MCUMGR_CMD_OS_MGMT=y
CONFIG_MCUMGR_CMD_STAT_MGMT=y

# Allow for large Bluetooth data packets.
CONFIG_BT_L2CAP_TX_MTU=252
CONFIG_BT_BUF_ACL_RX_SIZE=256

# Enable the Bluetooth (unauthenticated) and shell mcumgr transports.
CONFIG_MCUMGR_SMP_BT=y
CONFIG_MCUMGR_SMP_BT_AUTHEN=n
CONFIG_MCUMGR_SMP_SHELL=y




















##########pragma endregion



#include <stddef.h>
#include <string.h>
#include <sys/printk.h>
#include <sys/byteorder.h>
#include <zephyr.h>
#include <drivers/i2c.h>
#include <drivers/sensor.h>
#include <devicetree.h>
#include <SEGGER_RTT.h>
#include <device.h>
#include <zephyr/types.h>
#include <drivers/gpio.h>
#include "accelometer/accelometer.h"


#define GPIO DT_LABEL(DT_NODELABEL(gpio0))
#define BACKLIGHT_PIN 7
const struct device *dev;
gpio_pin_configure(dev, BACKLIGHT_PIN, GPIO_OUTPUT);

void toggle_backlight(void){

	const struct device *dev;

    dev = device_get_binding(GPIO);
    if (dev == NULL) {
        printk("Error: Could not get GPIO device\n");
        return;
    }

	k_sleep(K_SECONDS(3));

    gpio_pin_configure(dev, BACKLIGHT_PIN, GPIO_OUTPUT);

	printk("BACKLIGHT TOGGLE\n");

	gpio_pin_toggle(dev, BACKLIGHT_PIN);
}

void main(void){

    SEGGER_RTT_Init();

	printk("RTT LOG\n\n");

	while (1) {

		fetch_accelometer_data();

		k_sleep(K_SECONDS(5));

        printk("---\n");

        const struct device *spi_dev;

        spi_dev = device_get_binding(DT_LABEL(DT_NODELABEL(spi3)));
        if (!spi_dev) {
            printk("Error: Could not get SPI device\n");
        }
        if(spi_dev){
            printk("FOUND SPI BUS");
        }

    }

}




*/
#include <iostream>
02
#include <libusb.h>
03
using namespace std;
04
 
05
void printdev(libusb_device *dev); //prototype of the function
06
 
07
int main() {
08
    libusb_device **devs; //pointer to pointer of device, used to retrieve a list of devices
09
    libusb_context *ctx = NULL; //a libusb session
10
    int r; //for return values
11
    ssize_t cnt; //holding number of devices in list
12
    r = libusb_init(&ctx); //initialize a library session
13
    if(r < 0) {
14
        cout<<"Init Error "<<r<<endl; //there was an error
15
                return 1;
16
    }
17
    libusb_set_debug(ctx, 3); //set verbosity level to 3, as suggested in the documentation
18
    cnt = libusb_get_device_list(ctx, &devs); //get the list of devices
19
    if(cnt < 0) {
20
        cout<<"Get Device Error"<<endl; //there was an error
21
    }
22
    cout<<cnt<<" Devices in list."<<endl; //print total number of usb devices
23
        ssize_t i; //for iterating through the list
24
    for(i = 0; i < cnt; i++) {
25
                printdev(devs[i]); //print specs of this device
26
        }
27
        libusb_free_device_list(devs, 1); //free the list, unref the devices in it
28
        libusb_exit(ctx); //close the session
29
        return 0;
30
}
31
 
32
void printdev(libusb_device *dev) {
33
    libusb_device_descriptor desc;
34
    int r = libusb_get_device_descriptor(dev, &desc);
35
    if (r < 0) {
36
        cout<<"failed to get device descriptor"<<endl;
37
        return;
38
    }
39
    cout<<"Number of possible configurations: "<<(int)desc.bNumConfigurations<<"  ";
40
    cout<<"Device Class: "<<(int)desc.bDeviceClass<<"  ";
41
    cout<<"VendorID: "<<desc.idVendor<<"  ";
42
    cout<<"ProductID: "<<desc.idProduct<<endl;
43
    libusb_config_descriptor *config;
44
    libusb_get_config_descriptor(dev, 0, &config);
45
    cout<<"Interfaces: "<<(int)config->bNumInterfaces<<" ||| ";
46
    const libusb_interface *inter;
47
    const libusb_interface_descriptor *interdesc;
48
    const libusb_endpoint_descriptor *epdesc;
49
    for(int i=0; i<(int)config->bNumInterfaces; i++) {
50
        inter = &config->interface[i];
51
        cout<<"Number of alternate settings: "<<inter->num_altsetting<<" | ";
52
        for(int j=0; j<inter->num_altsetting; j++) {
53
            interdesc = &inter->altsetting[j];
54
            cout<<"Interface Number: "<<(int)interdesc->bInterfaceNumber<<" | ";
55
            cout<<"Number of endpoints: "<<(int)interdesc->bNumEndpoints<<" | ";
56
            for(int k=0; k<(int)interdesc->bNumEndpoints; k++) {
57
                epdesc = &interdesc->endpoint[k];
58
                cout<<"Descriptor Type: "<<(int)epdesc->bDescriptorType<<" | ";
59
                cout<<"EP Address: "<<(int)epdesc->bEndpointAddress<<" | ";
60
            }
61
        }
62
    }
63
    cout<<endl<<endl<<endl;
64
    libusb_free_config_descriptor(config);
65
}


#define _GNU_SOURCE

#include <libftdi.h>
#include <stdio.h>
#include <unistd.h>

struct ftdi_context ftdic;


int main()
{
printf("init..\n");

	ftdi_init(&ftdic);
	ftdi_set_interface(&ftdic, INTERFACE_A);

	ftdi_usb_open(&ftdic, 0x0403, 0x6010);
  printf("Bye.\n");
	ftdi_disable_bitbang(&ftdic);
	ftdi_usb_close(&ftdic);
	ftdi_deinit(&ftdic);
	return 0;

}

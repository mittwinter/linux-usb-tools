// usbreset - Reset given usb device
// Based on: https://unix.stackexchange.com/a/243457
//       and http://www.roman10.net/2011/05/04/how-to-reset-usb-device-in-linux/

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/ioctl.h>

#include <linux/usbdevice_fs.h>


int main( int argc, char *argv[] ) {
	if (argc != 2) {
		fprintf( stderr, "Usage: usbreset <device-filename>\n" );
		return 1;
	}

	const char *filename = argv[ 1 ];
	int fd = open( filename, O_WRONLY );
	if( fd < 0 ) {
		perror( "Error opening device file" );
		return 1;
	}

	printf( "Resetting USB device %s\n", filename );
	int rc = ioctl( fd, USBDEVFS_RESET, 0 );
	if( rc < 0 ) {
		perror( "Error in ioctl()" );
		return 1;
	}
	printf( "Reset successful\n" );

	close( fd );
	return 0;
}

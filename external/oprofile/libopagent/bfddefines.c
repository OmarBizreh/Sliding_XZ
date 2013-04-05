/**
 * @file bfddefines.c
 * Write out defines for BFD arch and mach of the given binary
 *
 * @remark Copyright 2007 OProfile authors
 * @remark Read the file COPYING
 *
 * @author Jens Wilke
 *
 * Copyright IBM Corporation 2007
 *
 */

#include <stdio.h>
#include <bfd.h>

int main(int argc, char ** args)
{
	bfd * bfd;
	bfd_boolean r;

	bfd_init();
	bfd = bfd_openr(args[1], NULL);
	if (bfd == NULL) {
		bfd_perror("bfd_open");
		return 1;
	}
	r = bfd_check_format(bfd, bfd_object);
	if (!r) {
		bfd_perror("bfd_get_arch");
		return 1;
	}
	printf("/* automatically generated by bfddefines, do not edit*/\n");
	printf("#define BFD_TARGET_NAME \"%s\"\n", bfd->xvec->name);
	printf("#define BFD_ARCH %i\n", bfd_get_arch(bfd));
	printf("#define BFD_MACH %lu\n", bfd_get_mach(bfd));
	printf("#define BFD_PRINTABLE_NAME \"%s\"\n", bfd_printable_name(bfd));

	return 0;
}

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "telephone.h"

int main()
{
	telephone telephone;

	telephone.init_directory();
	telephone.process_command();

	return 0;
}

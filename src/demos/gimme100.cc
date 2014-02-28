#include "gimme100.h"
#include <mach-o/dyld.h>

int main(int argc, char **args) {
		char path[1024];
		uint32_t size = sizeof(path);
		if (_NSGetExecutablePath(path, &size) == 0)
				printf("executable path is %s\n", path);
		else
				printf("buffer too small; need size %u\n", size);	
    System s = SystemFactory::setupFor100();
    Physical letsget(s);
    letsget.MainLoop();

    return 0;
}

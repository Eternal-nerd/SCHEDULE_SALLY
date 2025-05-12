#include <SDL3/SDL_main.h>

#include <stdlib.h>
#include <stdio.h>
#include <errno.h> 

#define STB_IMAGE_IMPLEMENTATION

#include "types.h"
#include "engine.h"

#ifdef NDEBUG
const b8 enable_validation_layers = false;
#else
const b8 enable_validation_layers = true;
#endif


const char validation_layers[1][100] = {"VK_LAYER_KHRONOS_validation"};
const char device_extensions[2][100] = {VK_KHR_SWAPCHAIN_EXTENSION_NAME, VK_EXT_EXTENDED_DYNAMIC_STATE_3_EXTENSION_NAME};

int main(int argc, char** argv) {
	printf("main function invocation\n");

	engine e;
	
	printf("\nsizeof(engine): %zu \n\n", sizeof(engine));

	if (!run_engine(&e)) {
		printf("main function exit failure\n");
		return EXIT_FAILURE;
	}

    printf("main function exit success\n");
    return EXIT_SUCCESS;
}
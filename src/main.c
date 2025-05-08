#include <SDL3/SDL_main.h>

#include <stdlib.h>
#include <stdio.h>

#define STB_IMAGE_IMPLEMENTATION

#include "types.h"
#include "engine.h"

int main(int argc, char** argv) {
	printf("main function invocation\n");

	engine eng;

	error_code code = run_engine(&eng);

	if (code != 0) {
		printf("main function exit failure with error code: %u\n", code);
		return EXIT_FAILURE;
	}


    printf("main function exit success\n");
    return EXIT_SUCCESS;

	return 0;
}
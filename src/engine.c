#include "engine.h"

error_code run_engine(engine* e) {
	e->id = 33;
	printf("running engine with id %u\n", e->id);
	return 0;
}

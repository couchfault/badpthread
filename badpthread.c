#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <dlfcn.h>
#include <unistd.h>
#include <string.h>

static pthread_t badproggy_thread;
int wait_before_return = 0;

void *badproggy_main(void *argv) {
	char **argvp = (char**)argv;
	int argc = 0;
	for (int i=0; *(argvp+i) != NULL; ++i)
		++argc;
	static int retcode = 1;
	int (*badproggy_main_funcptr)(int,const char**);
	void *handle = dlopen(*argvp, RTLD_NOW);
	if (!handle)
		return &retcode;
	badproggy_main_funcptr = dlsym(handle, "main");
	if (!badproggy_main_funcptr)
		return &retcode;
	retcode = (*badproggy_main_funcptr)(argc, (const char**)argvp);
	return &retcode;
}

__attribute__((constructor))
static void before_run(int argc, char **argv, char *envp) {
	if (argc < 2)
		return;
	char **argv_copy = NULL;
	char **argvp = argv;
	size_t argv_copy_sz = 0;
	int new_argc = argc - 1;
	for (int i=1; i<argc; ++i)
		argv_copy_sz += strlen(argv[i])+1;
	argv_copy_sz += sizeof(NULL);
	if ((argv_copy = malloc(argv_copy_sz)) == NULL)
		return;
	printf("%zd\n", argv_copy_sz);
	memcpy(argv_copy, argv+1, argv_copy_sz);
	argv_copy[new_argc] = NULL;
	wait_before_return = 1;
	pthread_create(&badproggy_thread, NULL, badproggy_main, argv_copy);
}

__attribute__((destructor))
static void before_exit(void) {
	if (wait_before_return)
		pthread_join(badproggy_thread, NULL);
}

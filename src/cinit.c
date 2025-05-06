#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "default.h"
#include "init.h"


int main()
{
	char project_name[100], executable_name[100];
	int c_standard;
	bool include_dir;

	printf("project name: ");
	fflush(stdout);
	if (fgets(project_name, sizeof(project_name), stdin) == NULL){
		perror("Failed to readline");
		exit(EXIT_FAILURE);
	}


	printf("executable name (default by project name): ");
	fflush(stdout);
	if (fgets(executable_name, sizeof(executable_name), stdin) == NULL){
		perror("Failed to readline");
		exit(EXIT_FAILURE);
	}

	if (strcmp(executable_name, "\n") == 0){
		strcpy(executable_name, project_name);
	}

	/* \n to \0 */

	char* trim_proj = strchr(project_name, '\n');
	if (trim_proj != NULL)
		*trim_proj = '\0';

	char* trim_exec = strchr(executable_name, '\n');
	if (trim_exec != NULL)
		*trim_exec = '\0';


	/* ask standard c  */
	while(true){
		printf("standard c version: ");
		fflush(stdout);
		if (scanf("%d", &c_standard) != 1) {
			perror("Failed to readline");
			perror("Please enter a number");
			getchar();
			continue;
		}
		break;
	}
	getchar();

	printf("enable include directory?[y/n] ");
	fflush(stdout);
	char yes_or_no[100];

	if (fgets(yes_or_no, sizeof(yes_or_no), stdin) == NULL){
		perror("Failed to readline");
		exit(EXIT_FAILURE);
	}

	char* trim_yn = strchr(yes_or_no, '\n');
	if (trim_yn != NULL)
		*trim_yn = '\0';

	if (strcmp(yes_or_no, "y") == 0) {
		char* generated_cmake = generate_cmake(project_name, c_standard, 1, executable_name);
		init_project(true, generated_cmake);
		free(generated_cmake);
	} else {
		char* generated_cmake = generate_cmake(project_name, c_standard, 0, executable_name);
		init_project(false, generated_cmake);
		free(generated_cmake);
	}
}

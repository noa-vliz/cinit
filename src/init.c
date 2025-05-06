#include <stdio.h>
#include <sys/stat.h>
#include <stdbool.h>
#include <unistd.h>



int init_project(bool include, const char* generated_cmake)
{
	char src_dir[] = "src";
	char include_dir[] = "include";

	if (mkdir(src_dir, S_IRWXU|S_IRGRP|S_IXGRP) != 0){
		fprintf(stderr, "Failed to create %s", src_dir);
	} 

	if (mkdir(include_dir, S_IRWXU|S_IRGRP|S_IXGRP) != 0){
		fprintf(stderr, "Failed to create %s", include_dir);
	}

	if (mkdir("build", S_IRWXU|S_IRGRP|S_IXGRP) != 0){
		fprintf(stderr, "Failed to create build directory");
	}

	FILE* cmake = fopen("CMakeLists.txt", "w");
	fprintf(cmake, generated_cmake);
	fclose(cmake);

	FILE* main = fopen("src/main.c", "w");
	fprintf(main, "#include <stdio.h>\n"
			"#include \"template.h\"\n\n"
			"int main()\n"
			"{\n"
				"\tprintf(\"Hello, world!\\n\");\n"
				"\tdo_some();\n"
			"}\n");
	fclose(main);

	FILE* template = fopen("src/template.c", "w");
	fprintf(template, "#include <stdio.h>\n#include <unistd.h>\n"
			"\n"
			"void do_some()\n"
			"{\n"
				"\tsleep(1);\n"
			"}\n");
	fclose(template);

	FILE* include_temp = fopen("include/template.h", "w");
	fprintf(include_temp, "#ifndef _TEMPLATE_H\n"
			"#define _TEMPLATE_H\n"
			"\n"
			"void do_some();\n"
			"#endif /* _TEMPLATE_H */");

	fclose(include_temp);
}


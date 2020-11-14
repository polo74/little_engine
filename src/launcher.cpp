#include <launcher.hpp>

int launcher(int argc, char ** argv)
{
	int i = -1;

	fprintf(stdout, "1 : start game\n");
	fprintf(stdout, "2 : exit\n");

	fprintf(stdout, "your choice : ");
	fscanf(stdin, "%d", &i);

	switch(i)
	{
		case 1 :
			game(argc, argv);
			launcher(argc, argv);
			break;
		case 2:
			break;
		default:
			break;
	}

	return 0;
}

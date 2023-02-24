//main mael

#include "ft_minishell.h"


int main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	//(void)envp;
	t_env data;
	//(void)data;

	//ft_echo(argv);
	//ft_cd(argc, argv);
	//ft_pwd(argv);
	init_env(envp, &data);
	// if (ft_strncmp(argv[1], "env", 3) == 0)
	// {
	// 	env_3(argc, argv, &data);
	// 	return (0);
	// }
	//unset_2(argc, argv, &data);
	//exec_unset(argc, argv, &data);
	//printf("res export = %d\n", export_3(argc, argv, &data));
	//printf("res = %d\n", if_arg(argc, argv));
	print_export(argc, argv, &data);
	//export_arg(argc, argv, &data);
	return (0);
}

// int main(int argc, char **argv, char **envp)
// {
// 	//(void)argc;
// 	//(void)argv;
// 	//(void)envp;
// 	t_list *lst;

// 	lst = NULL;
// 	//char *input;

// 	// while (1)
// 	// {
// 	// 	input = readline(">");
// 	// 	// process 
// 	// 	if (ft_strncmp(input, "exit", 4) == 0)
// 	// 		break ;
// 	// 	printf("input: %s\n", input);
// 	// }
// 	//printf("echo = %d\n", ft_echo(argv));
// 	//ft_echo(argv);
// 	//ft_pwd(argv);
// 	//ft_env(argc, argv, envp);
// 	//ft_env_in_order(envp);
	
// 	//init_list(envp, &lst);
// 	if (init_list(envp, &lst) == FAIL)
//         return (FAIL);
// 	//printf("res = %s\n", ft_getenv(argv[1]));
// 	//env_2(argc, argv, &lst);
// 	unset(envp, &lst, argv, argc);
// 	env_2(argc, argv, &lst);
// 	//ft_index(&lst);
// 	//swap_index(&lst);
// 	//printf("res = %d\n", ft_cd(argc, argv));
// 	return (0);

// }

// main gael

// #include "ft_minishell.h"

// int main(int argc, char **argv)
// {
// 	(void)argc;
// 	//(void)argv;
// 	//char *input;

// 	// while (1)
// 	// {
// 	// 	input = readline(">");
// 	// 	// process 
// 	// 	if (ft_strncmp(input, "exit", 4) == 0)
// 	// 		break ;
// 	// 	printf("input: %s\n", input);
// 	// }
// 	//printf("echo = %d\n", ft_echo(argv));
// 	ft_echo(argv);
// 	return (0);

// }
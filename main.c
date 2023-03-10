//main mael

#include "ft_minishell.h"


// int main(int argc, char **argv, char **envp)
// {
// 	(void)argc;
// 	(void)argv;
// 	//(void)envp;
// 	t_env data;
// 	//(void)data;

// 	//ft_echo(argv);
// 	//ft_cd(argc, argv);
// 	//ft_pwd(argv);
// 	init_env(envp, &data);
// 	// if (ft_strncmp(argv[1], "env", 3) == 0)
// 	// {
// 	// 	env_3(argc, argv, &data);
// 	// 	return (0);
// 	// }
// 	//unset_2(argc, argv, &data);
// 	//exec_unset(argc, argv, &data);
// 	//printf("res export = %d\n", export_3(argc, argv, &data));
// 	//printf("res = %d\n", if_arg(argc, argv));
// 	print_export(argc, argv, &data);
// 	//export_arg(argc, argv, &data);
// 	return (0);
// }

//main built-in/signaux

// int main(int argc, char **argv, char **envp)
// {
// 	(void)argc;
// 	(void)argv;
// 	(void)envp;
// 	//t_list *lst;

// 	// struct sigaction sig_c;
// 	//struct sigaction sig_k;
// 	//lst = NULL;
// 	char *input;

// 	while (1)
// 	{
// 		input = readline(">");
// 		//sig_k.sa_handler = &handle_ctrl_kill;
// 		// sig_c.sa_handler = &handle_ctrl_c;
// 		// sigaction(SIGINT, &sig_c, NULL);
// 		//sigaction(SIGQUIT, &sig_k, NULL);
// 		exec_signal(1);
// 		add_history(input);
// 		if (!input)
// 		{
// 			printf("exit\n");
// 			// free
// 			break ;
// 		}
// 		if (ft_strncmp(input, "exit", 4) == 0)
// 		{
// 			printf("exit\n");
// 			// free
// 			break ;
// 		}
// 		// executing_signal(&sig);
// 		printf("input: %s\n", input);
// 	}
// 	//printf("echo = %d\n", ft_echo(argv));
// 	//ft_echo(argv);
// 	//ft_pwd(argv);
// 	//ft_env(argc, argv, envp);
// 	//ft_env_in_order(envp);
	
// 	//init_list(envp, &lst);
// 	//if (init_list(envp, &lst) == FAIL)
//         return (FAIL);
// 	//printf("res = %s\n", ft_getenv(argv[1]));
// 	//env_2(argc, argv, &lst);
// 	//unset(envp, &lst, argv, argc);
// 	//env_2(argc, argv, &lst);
// 	//ft_index(&lst);
// 	//swap_index(&lst);
// 	//printf("res = %d\n", ft_cd(argc, argv));
// 	return (0);

// }




int	main(int argc, char *argv[], char **envp)
{
	t_mini_sh	mini_sh;
	// t_exec_t	exec;
	int	env_length;

	// mini_sh.env = envp;
	env_length = 0;
	while (envp[env_length])
		env_length++;
	mini_sh.env = (char **)malloc((sizeof (char *)) * (env_length + 1));
	env_length = -1;
	while (envp[++env_length])
	{
		mini_sh.env[env_length] = ft_strdup(envp[env_length]);
	}
	mini_sh.env[env_length] = 0;
	mini_sh.output = NULL;
	while (1)
	{
		// char *imput;
		// imput = readline(">");
		// ft_find_args(&mini_sh, "ls -l --color=never 	 -a | /usr/bin/grep -i --color=never  	   in >     result.txt");
		mini_sh.output = readline("\n\033[31m>\033[0m");
		mini_sh.sep = 0;
		mini_sh.sep_2 = 0;
		//mini_sh.nbr_word = 0;
		add_history(mini_sh.output);
		if (!mini_sh.output)
		{
			printf("exit\n");
			break;
		}
		exec_signal(1);
		// printf(BLUE"mini_sh.output: %s\n"RESET, mini_sh.output);
		// printf("mini_sh.output[5]-48: %i\n", mini_sh.output[5]-48);
		// process 
		if (ft_parsing(&mini_sh) == SUCCESS)
		{
			//printf("_%i_\n", if_empty_chain(&mini_sh));
			//prepare_exec(&mini_sh);
			//count_sep(&mini_sh);
			//count_sep_2(&mini_sh);
			//check_error_first_sep(&mini_sh);
			//printf("res = %d\n", first_is_sep_2(&mini_sh));
			//check_first_sep_error_2(&mini_sh);
			//count_word_for_alloc(&mini_sh);
			if_redir_R(&mini_sh);
			init_sep_type(&mini_sh);
			printf("\n");
		}
		//count_sep(&mini_sh);
		//count_sep(&mini_sh, imput);
		//check_first_sep(&mini_sh, imput);
		
		// 	if (ft_strncmp(mini_sh.output, "exit", 4) == 0)
		// 	{
		// 		char **str;
		// 		int res;

		// 		str = ft_split(mini_sh.output, ' ');
		// 		res = atoi(str[1]);
		// 		return (res);
		// 	}
		free(mini_sh.output),
		mini_sh.output = NULL;
		free_parsing(&mini_sh);
	}
	free_env(&mini_sh);
	// env_length = -1;
		//  si c'est une simplle on interprete pas doublr

	// while (mini_sh.env[++env_length])
	// {
	// 	free(mini_sh.env[env_length]);
	// }
	// free(mini_sh.env);
	(void)mini_sh;
	(void)argc;
	(void)argv;
	// return ((int)(mini_sh.output[5]));
	return (0);
}


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
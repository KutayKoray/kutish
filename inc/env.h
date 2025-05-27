/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebabaogl <ebabaogl@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 20:19:17 by ebabaogl          #+#    #+#             */
/*   Updated: 2025/05/27 20:22:22 by ebabaogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

# include <stddef.h>

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_env;

// env.c
t_env	*init_env_list(char **envp);
int		set_env(t_env **env, char *key, char *value);
int		unset_env(t_env **env, char *key);
char	*get_env_value(t_env *env, char *key);

// env_utils.c
int		is_valid_key(char *key);
int		append_env_node(t_env **env, char *key, char *value);
void	free_env_list(t_env *env);

// env_init.c
void	initialize_envs(t_env **env);

#endif
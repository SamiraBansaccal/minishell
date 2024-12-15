/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbansacc <sbansacc@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 07:42:04 by sbansacc          #+#    #+#             */
/*   Updated: 2024/11/23 20:03:24 by sbansacc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	get_args_size(t_token *tokens)
{
	int	i;
	int	size;

	i = 0;
	size = 0;
	while (tokens[i].value && tokens[i].value[0] != '|')
	{
		if (tokens[i].e_type == TOKEN_OPERATOR)
		{
			i += 2;
			continue ;
		}
		size++;
		i++;
	}
	return (size);
}

int	get_inf_count(t_token *tokens)
{
	int	i;
	int	size;

	i = 0;
	size = 0;
	while (tokens[i].value && tokens[i].value[0] != '|')
	{
		if (tokens[i].value[0] == '<')
			size++;
		i++;
	}
	return (size);
}

int	get_outf_count(t_token *tokens)
{
	int	i;
	int	size;

	i = 0;
	size = 0;
	while (tokens[i].value && tokens[i].value[0] != '|')
	{
		if (tokens[i].value[0] == '>')
			size++;
		i++;
	}
	return (size);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_add_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanzieu <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/19 11:23:34 by aanzieu           #+#    #+#             */
/*   Updated: 2017/06/19 12:15:48 by aanzieu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <object.h>

void				add_paraboloid(t_paraboloid **alst, t_paraboloid *nw)
{
	t_paraboloid *curr;

	if (!nw || !alst)
		return ;
	if (!*alst)
		*alst = nw;
	else
	{
		curr = *alst;
		while (curr->next)
			curr = curr->next;
		curr->next = nw;
	}
}
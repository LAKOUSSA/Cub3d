/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gloukas <gloukas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 02:30:54 by gloukas           #+#    #+#             */
/*   Updated: 2023/11/14 14:26:58 by gloukas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, void *src, int n)
{
	if (!src && !dst)
		return (NULL);
	if (dst > src)
	{
		while (n--)
		{
			((char *)dst)[n] = ((char *)src)[n];
		}
	}
	else
		ft_memcpy(dst, src, n);
	return (dst);
}

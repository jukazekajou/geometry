/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cercle3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdurand <jdurand@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/20 14:45:02 by jdurand           #+#    #+#             */
/*   Updated: 2020/01/09 20:11:03 by jdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <strings.h>
#include <math.h>
#define X_MAX 40
#define Y_MAX 40
#define GREEN "\x1b[32m"
#define RESET "\x1b[0m"
#define PURPLE "\033[34;01m"
#define RED "\033[31m"
#define RED_END "\033[00m"
#define BLACK "\033[30m"
#define BOLDRED "\033[1m\033[31m"


void 	show_tab(char **tab)
{
	for (int j = 0; j < Y_MAX; j++)
	{
		for (int i = 0; i < X_MAX; i++)
		{
			if (tab[j][i] != '@')
				printf(BLACK "%c " RESET, tab[j][i]);
			else
				printf(BOLDRED "%c " RESET, tab[j][i]);
		}
		printf("\n");
	}
}

void 	ft_setup(char **tab)
{
	for (int i = 0; i < Y_MAX; i++)
	{
		for (int j = 0; j < X_MAX; j++)
			tab[i][j] = '0';
	}
}

void 	do_check_draw(char **tab, int x, int y)
{
	if (x > 0 && x < X_MAX && y > 0 && y < Y_MAX)
		tab[y][x] = '@';
}

void 	do_octant(int centerx, int centery, int x, int y, int m, char **tab)
{
	while (x <= y)
	{
		if (m < 0)
			m = (m + (4 * x) + 6);
		else
		{
			y -= 1;
			m += ((4 * (x - y) + 1));
		}
		do_check_draw(tab, x + centerx, y + centery);
		do_check_draw(tab, y + centerx, x + centery);
		do_check_draw(tab, -x + centerx, y + centery);
		do_check_draw(tab, -y + centerx, x + centery);
		do_check_draw(tab, x + centerx, -y + centery);
		do_check_draw(tab, y + centerx, -x + centery);
		do_check_draw(tab, -x + centerx, -y + centery);
		do_check_draw(tab, -y + centerx, -x + centery);
		x += 1;
	}
}

void 	fill_circle(char **tab, int centerx, int centery, int r)
{
	int x = 0; int y = 0;
	double dist;
	double rayon;

	rayon = (double)r;

	while (y < Y_MAX)
	{
		while (x < X_MAX)
		{
			dist = (((x - centerx) * (x - centerx)) + ((y - centery) * (y - centery)));
			if (dist <= rayon * rayon)
			{
				tab[y][x] = '@';
			}
			x++;
		}
		x = 0;
		y++;
	}
}


void	do_circle3(int cx, int cy, int r, char **tab)
{
	int x,y;
	double hrw;
	y = -r;
	while (y <= r)
	{
		hrw = sqrt(r * r - y * y);
		x = -hrw;
		do_check_draw(tab, cx + x, cy + y);
		while (x <= hrw)
		{
		//	do_check_draw(tab, cx + x, cy + y);
			x++;
		}
		do_check_draw(tab, cx + x, cy + y);
		y++;
	}
    //half_row_width=sqrt(radius*radius-y*y);
    //for(x=-half_row_width; x< half_row_width; x++)
     //   WritePixel(centre_x+x, centre_y+y, colour);
}


int	main(int ac, char **av)
{
	char **tab;
	int centerx;
	int centery;
	int ray;
	int x,y,m;

	tab = malloc(Y_MAX * sizeof(char*));
	for (int i =0; i < Y_MAX; i++)
		tab[i] = malloc(X_MAX * sizeof(char));
	ft_setup(tab);

	if (ac < 4)
	{
		printf("<exec> X_center Y_center ray\n");
		return (0);
	}
	centerx = atoi(av[1]);
	centery = atoi(av[2]);
	ray = atoi(av[3]);

	x = 0;
	y = ray;
	m = 3 - 2 * ray;
//	do_octant(centerx, centery, x, y, m, tab);
//	fill_circle(tab, centerx, centery, ray);
	do_circle3(centerx, centery, ray, tab);
	show_tab(tab);
	return (0);
}

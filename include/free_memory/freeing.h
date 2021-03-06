/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   determine_bytes.c                                .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: simrossi <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/11/27 15:04:52 by simrossi     #+#   ##    ##    #+#       */
/*   Updated: 2018/11/27 15:04:55 by simrossi    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef FREEING_H
# define FREEING_H

/*
** Freeing function for each data type
*/

void			free_ptr(void *ptr);
void			free_chare(void *str_ptr);
void			free_charee(void *array_ptr);
void			free_inte(void *array_ptr);
void			free_pylst_type(void *pylst_ptr);
void			free_hash_table_type(void *table_ptr);
void			free_hash_exec_type(void *hash_exec);
void			free_job_type(void *job);
void			free_static_type(void *static_ptr);

#endif

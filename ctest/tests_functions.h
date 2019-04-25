#ifndef TESTS_FUNCTION_H
# define TESTS_FUNCTION_H

/*
** test_function.h:
**
** File used to add each prototype define in the tests
** folder, contain all test functions.
*/

// Tests for t_pylst
void	simple_chare_pylst(void);
void	simple_int_pylst(void);
void	multitype_pylst(void);

// Tests for hash table
void	hash_creation(void);
void	hash_single_insert(void);
void	hash_multiple_insert(void);
void	hash_multitype_insert(void);
void	hash_insert_single_alveol(void);
void	hash_single_delete(void);
void	hash_multiple_delete(void);
void	hash_alveol_deletion(void);

// Tests for t_line elements only
void	t_line_allocation(void);
void	t_line_lst_allocation(void);
void	t_line_longer_lst(void);
void	t_line_len(void);
void	t_line_update_test(void);
void	t_line_get_last_test(void);
void	t_line_extract_test_simple(void);

// Tests for t_char element only
void	t_char_allocation_test(void);
void	t_char_push_test(void);
void	t_char_push_harder_test(void);
void	t_char_length_test(void);
void	t_char_update_pos_test(void);

// Tests for t_cursor
void	t_cursor_alloc_test(void);

// Tests for t_char selection (char_selection.c)
void	search_prev_char_test(void);
void	get_last_lock_test(void);
void	get_unlocked_char_test(void);
void	get_last_char_test(void);

#endif

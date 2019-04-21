#include "libft.h"
#include "test_runner.h"

#define ERROR		1
#define NO_ERROR	0


// Check if a table is create properly
void	hash_creation(void)
{
	t_ht_table	*new_tab = NULL;
	int			x_test = 0;

	// Test a simple creation and if all element are create at the right
	// place.
	int seed = 47;
	int size = 25;
	ht_new_table(&new_tab, seed, size);
	ASSERT_TEST(x_test, new_tab != NULL);
	// Test seed and size.
	ASSERT_INTCMP(x_test, new_tab->size, size);
	ASSERT_INTCMP(x_test, new_tab->seed, seed);

	//Test if each alveol are set to nul
	int index = 0;
	int error = NO_ERROR;
	while (index < new_tab->size && error == NO_ERROR)
	{
		if (new_tab->items[index] != NULL)
			error = ERROR;
		index++;
	}
	ASSERT_TEST(x_test, error == NO_ERROR);
}

// Simple test with a single element.
void	hash_single_insert(void)
{
	int			x_test = 0;

	//Tab initialization
	t_ht_table	*new_tab = NULL;
	int seed = 97; int size = 80;
	ht_new_table(&new_tab, seed, size);

	char *key = "first";
	char *value = "content";
	insert_value(new_tab, key, value, _chare);
	ASSERT_STRCMP(x_test, search_value(new_tab, key), value);
}

// Test if we can add multiple element inside a hash table.
void	hash_multiple_insert(void)
{
	int		x_test = 0;

	//Tab initialization
	t_ht_table	*new_tab = NULL;
	int seed = 97; int size = 80;
	ht_new_table(&new_tab, seed, size);

	char *key1 = "first"; char *value1 = "first_content";
	char *key2 = "second_key"; char *value2 = "a new content";
	char *key3 = "third_one"; char *value3 = "one more string to test";
	char *key4 = "always more"; char *value4 = "what the hell";

	insert_value(new_tab, key1, value1, _chare);
	insert_value(new_tab, key2, value2, _chare);
	insert_value(new_tab, key3, value3, _chare);
	insert_value(new_tab, key4, value4, _chare);

	ASSERT_STRCMP(x_test, search_value(new_tab, key1), value1);
	ASSERT_STRCMP(x_test, search_value(new_tab, key2), value2);
	ASSERT_STRCMP(x_test, search_value(new_tab, key3), value3);
	ASSERT_STRCMP(x_test, search_value(new_tab, key4), value4);
}

// Check if we can add mulitple element in a single alveol
void	hash_insert_single_alveol(void)
{
	int		x_test = 0;

	//Tab initialization
	t_ht_table	*new_tab = NULL;
	int seed = 97; int size = 1; // Set size to 1 to have a single alveol
	ht_new_table(&new_tab, seed, size);

	char *key1 = "whut"; char *value1 = "content whut";
	char *key2 = "plop"; int number1 = 450;
	char *key3 = "warza"; char *value2 = "warza content ?";

	insert_value(new_tab, key1, value1, _chare);
	insert_value(new_tab, key2, &number1, _int);
	insert_value(new_tab, key3, value2, _chare);

	ASSERT_STRCMP(x_test, search_value(new_tab, key1), value1);
	ASSERT_INTCMP(x_test, *(int *)search_value(new_tab, key2), number1);
	ASSERT_STRCMP(x_test, search_value(new_tab, key3), value2);
}


// Test if we can insert properly multiple type inside a hash_table.
void	hash_multitype_insert(void)
{
	int		x_test = 0;

	//Tab initialization
	t_ht_table	*new_tab = NULL;
	int seed = 97; int size = 80;
	ht_new_table(&new_tab, seed, size);

	char *key1 = "1"; char letter = 'a';
	char *key2 = "2"; char *str = "a long string";
	char *key3 = "3"; int number = 158;

	//Tab initialization for test
	t_ht_table	*tab_test = NULL;
	int seed_2 = 67; int size_2 = 20; char *key4 = "4";
	ht_new_table(&tab_test, seed_2, size_2);

	insert_value(new_tab, key1, &letter, _char);
	insert_value(new_tab, key2, str, _chare);
	insert_value(new_tab, key3, &number, _int);
	insert_value(new_tab, key4, tab_test, _hash_table);

	ASSERT_INTCMP(x_test, *(char *)search_value(new_tab, key1), letter);
	ASSERT_STRCMP(x_test, search_value(new_tab, key2), str);
	ASSERT_INTCMP(x_test, *(int *)search_value(new_tab, key3), number);
	ASSERT_PTRCMP(x_test, search_value(new_tab, key4), tab_test);
}

// Check if a single deletion can be run properly
void	hash_single_delete(void)
{
	int		x_test = 0;

	//Tab initialization
	t_ht_table	*new_tab = NULL;
	int seed = 97; int size = 80;
	ht_new_table(&new_tab, seed, size);

	char *key = "long str as key"; char *value = "empty";

	insert_value(new_tab, key, value, _chare);

	// Check if the insertion append properly
	ASSERT_STRCMP(x_test, search_value(new_tab, key), value);

	delete_value(new_tab, key);

	//Check the deletion
	ASSERT_PTRCMP(x_test, search_value(new_tab, key), NULL);
}

// Check if we can delete multiple element without trouble
void	hash_multiple_delete(void)
{
	int		x_test = 0;

	//Tab initialization
	t_ht_table	*new_tab = NULL;
	int seed = 97; int size = 80;
	ht_new_table(&new_tab, seed, size);

	char *key1 = "first_key"; char *value1 = "NO VALUE BRO";
	char *key2 = "SEcOnD-Keyyy"; char *value2 = "SURE THERE IS NO VALUE ??";
	char *key3 = "MDR Asshole"; char *value3 = "...";
	char *key4 = "Stop"; char *value4 = "why ?";

	insert_value(new_tab, key1, value1, _chare);
	insert_value(new_tab, key2, value2, _chare);
	insert_value(new_tab, key3, value3, _chare);
	insert_value(new_tab, key4, value4, _chare);

	//Delete key one by one and see if all is right and if we still
	//have the other value
	//key3
	delete_value(new_tab, key3);
	ASSERT_PTRCMP(x_test, search_value(new_tab, key3), NULL);

	ASSERT_STRCMP(x_test, search_value(new_tab, key1), value1);
	ASSERT_STRCMP(x_test, search_value(new_tab, key2), value2);
	ASSERT_STRCMP(x_test, search_value(new_tab, key4), value4);

	//key2
	delete_value(new_tab, key2);
	ASSERT_PTRCMP(x_test, search_value(new_tab, key2), NULL);

	ASSERT_STRCMP(x_test, search_value(new_tab, key1), value1);
	ASSERT_STRCMP(x_test, search_value(new_tab, key4), value4);
	//key1
	delete_value(new_tab, key1);
	ASSERT_PTRCMP(x_test, search_value(new_tab, key1), NULL);

	ASSERT_STRCMP(x_test, search_value(new_tab, key4), value4);

	//key4
	delete_value(new_tab, key4);
	ASSERT_PTRCMP(x_test, search_value(new_tab, key4), NULL);
}

// Same test than hash_multiple_delete but with an hash table
// of size 1, with a single alveol.
void		hash_alveol_deletion(void)
{
	int		x_test = 0;

	//Tab initialization
	t_ht_table	*new_tab = NULL;
	int seed = 97; int size = 1; //Set size to 1
	ht_new_table(&new_tab, seed, size);

	char *key1 = "first_key"; char *value1 = "NO VALUE BRO";
	char *key2 = "SEcOnD-Keyyy"; char *value2 = "SURE THERE IS NO VALUE ??";
	char *key3 = "MDR Asshole"; char *value3 = "...";
	char *key4 = "Stop"; char *value4 = "why ?";

	insert_value(new_tab, key1, value1, _chare);
	insert_value(new_tab, key2, value2, _chare);
	insert_value(new_tab, key3, value3, _chare);
	insert_value(new_tab, key4, value4, _chare);

	//Delete key one by one and see if all is right and if we still
	//have the other value
	//key3
	delete_value(new_tab, key3);
	ASSERT_PTRCMP(x_test, search_value(new_tab, key3), NULL);

	ASSERT_STRCMP(x_test, search_value(new_tab, key1), value1);
	ASSERT_STRCMP(x_test, search_value(new_tab, key2), value2);
	ASSERT_STRCMP(x_test, search_value(new_tab, key4), value4);

	//key2
	delete_value(new_tab, key2);
	ASSERT_PTRCMP(x_test, search_value(new_tab, key2), NULL);

	ASSERT_STRCMP(x_test, search_value(new_tab, key1), value1);
	ASSERT_STRCMP(x_test, search_value(new_tab, key4), value4);
	//key1
	delete_value(new_tab, key1);
	ASSERT_PTRCMP(x_test, search_value(new_tab, key1), NULL);

	ASSERT_STRCMP(x_test, search_value(new_tab, key4), value4);

	//key4
	delete_value(new_tab, key4);
	ASSERT_PTRCMP(x_test, search_value(new_tab, key4), NULL);
}




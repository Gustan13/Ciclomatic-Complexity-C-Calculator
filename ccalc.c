#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define INIT_TOKEN_SIZE 32

bool is_token_conditional(char* token)
{
	if (!strcmp(token, "if"))
		return true;
	else
	if (!strcmp(token, "for"))
		return true;
	else
	if (!strcmp(token, "while"))
		return true;
	else
	if (!strcmp(token, "switch"))
		return true;
	
	return false;
}

bool is_terminal_newtchar(char c)
{
	switch(c)
	{
	case ' ':
	case '\n':
	case '\t':
	case ')':
	case '(':
	case '}':
	case '{':
	case '\0':
	case '#':
		return true;
	}
	return false;
}

char *reallocate_token(char* token, size_t* token_size)
{
	char *aux;
	
	*token_size = (*token_size) * 2;
	aux = (char*)realloc(token, sizeof(char) * (*token_size));
	
	return aux;
}

size_t lex_file(char* src)
{
	size_t condition_count;
	size_t lookahead, token_size, token_count;
	char c;
	char *token;
	
	if (src == NULL)
		return -1;
	
	condition_count = 0;
	lookahead = 0;
	c = *src;
	token = NULL;
	token_count = 0;
	token_size = INIT_TOKEN_SIZE;
	
	token = (char*)malloc(sizeof(char) * INIT_TOKEN_SIZE);
	
	while (c != '\0')
	{
		
		if (is_terminal_newtchar(c))
		{
			if (token_count > 0)
			{	
				token[token_count] = '\0';
				token_count++;
				
				if (is_token_conditional(token))
				{
					condition_count++;
				}
				
				token_count = 0;
			}
			
			lookahead++;
			c = src[lookahead];
			continue;
		}
		
		token[token_count] = c;
		token_count++;
		
		if (token_count >= token_size)
		{
			token = reallocate_token(token, &token_size);
		}
		
		lookahead++;
		c = src[lookahead];
	}
			
	if (token_count > 0)
	{	
		token[token_count] = '\0';
		token_count++;
		
		if (is_token_conditional(token))
		{
			condition_count++;
		}
		
		token_count = 0;
	}
	
	free(token);
	token = NULL;
	
	return condition_count;
}

int main(int argc, char **argv)
{
	FILE* cfile = NULL;
	char *src = NULL;
	size_t filesize = 0;

	if (argc < 2)
	{
		puts("(CCalc) Usage: ccalc <c file>");
		return -1;
	}
	
	cfile = fopen(argv[1], "rb");
	if (cfile == NULL)
	{
		printf("(CCalc) Could not open file %s\n", argv[1]);
		return -1;
	}
	
	fseek(cfile, 0, SEEK_END);
	filesize = ftell(cfile);
	rewind(cfile);
	
	src = (char*)malloc(sizeof(char) * filesize + 1);
	if (src == NULL)
	{
		printf("(CCalc) Could not allocate memory\n");
		fclose(cfile);
		return -1;
	}
	
	fread(src, filesize, 1, cfile);
	src[filesize] = '\0';
	
	size_t complexity = lex_file(src);
	if (complexity == 0)
	{
		printf("(CCalc) There are no conditional branches in this program\n");
		free(src);
		src = NULL;
		fclose(cfile);
		return 0;
	}
	
	printf("(CCalc) SUCCESS\n");
	printf("(CCalc) Ciclomatic Complexity = %ld\n", complexity + 1);
	
	free(src);
	src = NULL;
	fclose(cfile);

	return 0;

}

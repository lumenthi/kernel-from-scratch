int		toupper(int c)
{
	if (c > 96 && c < 123)
		c = c - 32;
	return (c);
}

int		tolower(int c)
{
	if (c > 64 && c < 91)
		c = c + 32;
	return (c);
}

int		strcmp(const char *s1, const char *s2)
{
	int	i;

	i = 0;
	while (s1[i] == s2[i])
	{
		if (s1[i] == 0)
				break;
		i++;
	}
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

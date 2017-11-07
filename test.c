#include <fcntl.h>
#include "libft.h"
#include <stdio.h>

int		main(void)
{
	int		fd;
	int		txt;
	char	*str;

	txt = 1;
	while ((fd = open(ft_strjoin(ft_strjoin("test", ft_itoa(txt)), ".txt"), O_WRONLY | O_CREAT | O_EXCL)) < 0)
	{
		txt++;
		str = ft_strjoin(ft_strjoin("test", ft_itoa(txt)), ".txt");
		printf("%d, %s\n", fd, str);
		close(fd);
	}
	printf("%d\n", fd);
	return (0);
}

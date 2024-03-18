#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>

int	main(void)
{
	int		fd;
	char	*line;

	// Dosya açma işlemi
	fd = open("test.txt", O_RDONLY);
	if (fd == -1)
	{
		perror("Dosya açma hatası");
		return (1);
	}
	// Dosyadan satır satır okuma
	while ((line = get_next_line(fd)) != NULL)
	{
		printf("%s\n", line);
		free(line);
			// Bellek sızıntısını önlemek için satırı aldıktan sonra belleği serbest bırakın
	}
	// Dosya kapatma işlemi
	if (close(fd) == -1)
	{
		perror("Dosya kapatma hatası");
		return (1);
	}
	return (0);
}


// Чтение SPR файла в память.

#include <stdio.h>
#include <stdlib.h>

// Доступ к переменным из других программ.
	unsigned char bufferspr[40960]; // Массив для SPR файла.
	unsigned short int sizespr; // Размер SPR файла в байтах.

void LoadSPR(unsigned char* filename)
{

	unsigned short int addrspr; // Адрес в массиве bufferspr.
	int byte; // Текущий байт из SPR файла.

	FILE *filed = NULL;
	// Открытие двоичного файла (rb).
	filed = fopen(filename, "rb");

	if (filed == NULL)
		{
		printf("\n");

		printf("%s", "Внимание!");
		printf("\n");

		printf("%s", "Ошибка открытия файла ");
		printf("%s", filename);
		printf("%s", ".");
		printf("\n");

		printf("\n");

		// Завершение с кодом ошибки 1.
		exit(1);
		}

	addrspr = 0; sizespr = 0;

	while (1)
	{
	// Чтение одного байта из файла.
	byte = getc(filed);

	if (byte == EOF)
		{
		if (feof(filed) != 0)
			{
			// Чтение файла закончилось.
			break;
			}
			else
			{
			// Ошибка чтения из файла.
			printf("\n");

			printf("%s", "Внимание!");
			printf("\n");

			printf("%s", "Ошибка чтения SPR файла!");
			printf("\n");

			printf("\n");

			// Завершение.
			exit(1);
			}
		}

	// Слишком большой файл.
	if (sizespr == 40960)
		{

		// Закрытие файла.
		fclose(filed);

		printf("\n");
		printf("%s", "Ошибка SPR файла!");
		printf("\n");
		printf("\n");

		// Завершение.
		exit(1);
		}

	bufferspr[addrspr] = byte;
	addrspr++;
	sizespr++;
	}

	// Закрытие файла.
	fclose(filed);

}
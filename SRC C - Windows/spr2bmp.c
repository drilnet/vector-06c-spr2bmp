
// Конвертор графических файлов (SPR в BMP).
// Ukraine. (C) Demidov S.V.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ---

	// Загрузить SPR файл.
	extern unsigned char LoadSPR();

	// Распаковать SPR файл.
	extern void UnpackingSPR();

	// Перекодировать цвета.
	extern void CodeConversion();

	// Запись BMP файла на диск.
	extern void SaveBMP();

	extern unsigned char bufferspr[40960]; // Массив для SPR файла.
	extern unsigned short int sizespr;     // Размер SPR файла в байтах.
	extern unsigned long int sizedatabmp;  // Размер BMP данных.
	extern unsigned long int sizebmp;      // Размер BMP файла (заголовок и данные).

void main(int argc, char* argv[])
{

	unsigned char addrcolorspr; // Адрес цвета в bufferspr[40960].
	unsigned char* filenamespr; // Имя SPR файла.
	unsigned char addrfnspr;    // Адрес в filenamespr.

	// Переключатель плохое/хорошие расширение у SPR файла.
	unsigned char ext;

	// Здесь имя BMP файла.
	unsigned char filenamebmp[255] = { 0 };
	// Адрес в массиве filenamebmp[255].
	unsigned char addrfnb;

	filenamespr = argv[1];

	printf("\n");
	printf("%s", "Конвертер графических файлов (SPR в BMP).");
	printf("\n");
	printf("%s", "   Ukraine. (C) Демидов С.В.");
	printf("\n");
	printf("\n");
	printf("%s", "   SPR - графический формат файлов Вектор'а-06Ц.");
	printf("\n");
	printf("%s", "   BMP - графический формат файлов Windows.");
	printf("\n");

	if (argv[1] == NULL)
		{
		// Если в командной строке пусто.
		printf("\n");
		printf("%s", "   Формат командной строки:");
		printf("\n");
		printf("%s", "      $ spr2bmp имя_файла.spr");
		printf("\n");
		printf("\n");
		}
		else
		{
		// Проверить расширение SPR файла,
		addrfnspr = strlen(filenamespr) - 3;

		if (filenamespr[addrfnspr] == 'S' || filenamespr[addrfnspr] == 's')
			{
			addrfnspr++;
			if (filenamespr[addrfnspr] == 'P' || filenamespr[addrfnspr] == 'p')
				{
				addrfnspr++;
				if (filenamespr[addrfnspr] == 'R' || filenamespr[addrfnspr] == 'r')
					{
					ext = 1; // Good.
					}
					else
					{
					ext = 0;
					}
				}
				else
				{
				ext = 0;
				}
			}
			else
			{
			ext = 0;
			}

		// Если плохое расширение.
		if (ext == 0)
			{
			printf("\n");
			printf("%s", "Плохое расширение у SPR файла!");
			printf("\n");
			printf("\n");

			// Завершение.
			exit(1);
			}

		// ---
		// | Загрузить SPR файл.
		// ---
		LoadSPR(filenamespr);

		printf("\n");

		printf("%s", "             Файл: ");
		printf("%s", filenamespr);
		printf("\n");

		// Вывести на консоль размер файла SPR.
		printf("%s", " Размер SPR файла: ");
		printf("%d", sizespr);
		printf("%s", " ");
		printf("%s", "байт.");
		printf("\n");

		// ---
		// | Распаковываем SPR файл.
		// ---
		UnpackingSPR();

		// Вывести на консоль цвета SPR файла.
		printf("%s", "  Цвета SPR файла: ");

		for (addrcolorspr = 0; addrcolorspr < 16; addrcolorspr++)
			{
			// Вывод цвета в Hex.
			if (bufferspr[addrcolorspr] >=0 && bufferspr[addrcolorspr] <= 15)
				{
				// Ноль перед числом.
				printf("%s", "0");
				}

			printf("%X", bufferspr[addrcolorspr]);
			printf("%s", "H");

			if (addrcolorspr != 15)
				{
				printf("%s", " ");
				}
				else
				{
				printf("%s", ".");
				}
			}

		printf("\n");

		// ---
		// | Перекодировка.
		// | Экранная область Вектор'а-06Ц в bmp данные.
		// ---
		CodeConversion();

		printf("%s", "Размер BMP данных: ");
		printf("%u", sizedatabmp);
		printf("%s", " байт (минус заголовок).");
		printf("\n");

		// Копируем часть строки из filenamespr в filenamebmp.
		strncpy(filenamebmp, filenamespr + 0, strlen(filenamespr) - 4);

		addrfnb = strlen(filenamebmp);

		// Дописать в конец .bmp.
		filenamebmp[addrfnb++] = '.';
		filenamebmp[addrfnb++] = 'b';
		filenamebmp[addrfnb++] = 'm';
		filenamebmp[addrfnb++] = 'p';

		// ---
		// | Запись BMP файла на диск.
		// ---
		SaveBMP(filenamebmp);

		printf("%s", " Размер BMP файла: ");
		printf("%u", sizebmp);
		printf("%s", " байт.");
		printf("\n");

		printf("\n");

		printf("%s", "   ФАЙЛ КОНВЕРТИРОВАН! OK!");
		printf("\n");

		printf("\n");
		}
}
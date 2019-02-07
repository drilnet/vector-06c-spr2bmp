
// Распаковка SPR файла.

#include <stdio.h>
#include <stdlib.h>

	extern unsigned char bufferspr[40960]; // Массив для SPR файла.
	extern unsigned short int sizespr; // Размер SPR файла в байтах.

	// Экранная область Вектор-06Ц.
	unsigned char screen_vector_8000_FFFF[32768];

void UnpackingSPR()
{
	unsigned short int addrspr; // Адрес в массиве bufferspr.
	unsigned short int addrvcs; // Адрес в массиве экранная область Вектор-06Ц.

	unsigned char bit_s; // Есть ли повторяющиеся байты, 0 - нет, 1 - есть.
	unsigned char cb;    // Счётчик 
	unsigned char tb;    // Сколько не повторяющихся/повторяющихся байт.

	// Пропустить нули.
	for (addrspr = sizespr; addrspr > 0;)
		{
		if (bufferspr[addrspr] != 0)
			{
			break;
			}
		addrspr--;
		}	

	printf("%s", "Размер SPR данных: ");
	printf("%u", addrspr - 16 + 1);
	printf("%s", " байт (минус цвета и минус нулевые байты).");
	printf("\n");

	addrvcs = 32767;

	// Распаковка (распаковка в  screen_vector_8000_FFFF[addrvcs]).
	for (addrspr = addrspr; addrspr > 15; addrspr--)
		{

		bit_s = 128 & bufferspr[addrspr]; // 80H и bufferspr[addrspr].

		if (bit_s == 0)
			{
			// Не повторяющиеся байты.
			// ---

			tb = bufferspr[addrspr];

			for (cb = 0; cb < tb; cb++)
				{
				addrspr--;

				if (addrvcs == 65535)
					{
					printf("\n");
					printf("%s", "Ошибка SPR файла!");
					printf("\n");
					printf("\n");

					// Завершение.
					exit(1);
					}

				screen_vector_8000_FFFF[addrvcs] = bufferspr[addrspr];

				addrvcs--;
				}
			}
			else
			{
			// Повторяющиеся байты.
			// ---

			// Установить старший бит в ноль.
			tb = 127 & bufferspr[addrspr]; // 7FH и tb.

			addrspr--;

			for (cb = 0; cb < tb; cb++)
				{

				if (addrvcs == 65535)
					{
					printf("\n");
					printf("%s", "Ошибка SPR файла!");
					printf("\n");
					printf("\n");

					// Завершение.
					exit(1);
					}

				screen_vector_8000_FFFF[addrvcs] = bufferspr[addrspr];

				addrvcs--;
				}
			}

		}

	addrvcs++;

//	printf("%s", "      Распаковано: ");
//	printf("%u", 32768 - addrvcs);
//	printf("%s", " байт.");
//	printf("\n");

	if (addrvcs != 0)
		{
		printf("\n");
		printf("%s", "Ошибка SPR файла!");
		printf("\n");
		printf("\n");

		// Завершение.
		exit(1);
		}
}
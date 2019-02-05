
// ��ᯠ����� SPR 䠩��.

#include <stdio.h>
#include <stdlib.h>

	extern unsigned char bufferspr[40960]; // ���ᨢ ��� SPR 䠩��.
	extern unsigned short int sizespr; // ������ SPR 䠩�� � �����.

	// ��࠭��� ������� �����-06�.
	unsigned char screen_vector_8000_FFFF[32768];

void UnpackingSPR()
{
	unsigned short int addrspr; // ���� � ���ᨢ� bufferspr.
	unsigned short int addrvcs; // ���� � ���ᨢ� �࠭��� ������� �����-06�.

	unsigned char bit_s; // ���� �� �������騥�� �����, 0 - ���, 1 - ����.
	unsigned char cb;    // ����稪 
	unsigned char tb;    // ����쪮 �� �����������/����������� ����.

	// �ய����� �㫨.
	for (addrspr = sizespr; addrspr > 0;)
		{
		if (bufferspr[addrspr] != 0)
			{
			break;
			}
		addrspr--;
		}	

	printf("%s", "������ SPR ������: ");
	printf("%u", addrspr - 16 + 1);
	printf("%s", " ���� (����� 梥� � ����� �㫥�� �����).");
	printf("\n");

	addrvcs = 32767;

	// ��ᯠ����� (�ᯠ����� �  screen_vector_8000_FFFF[addrvcs]).
	for (addrspr = addrspr; addrspr > 15; addrspr--)
		{

		bit_s = 128 & bufferspr[addrspr]; // 80H � bufferspr[addrspr].

		if (bit_s == 0)
			{
			// �� �������騥�� �����.
			// ---

			tb = bufferspr[addrspr];

			for (cb = 0; cb < tb; cb++)
				{
				addrspr--;

				if (addrvcs >= 32768)
					{
					printf("\n");
					printf("%s", "�訡�� SPR 䠩��!");
					printf("\n");
					printf("\n");

					// �����襭��.
					exit(1);
					}

				screen_vector_8000_FFFF[addrvcs] = bufferspr[addrspr];

				addrvcs--;
				}
			}
			else
			{
			// �������騥�� �����.
			// ---

			// ��⠭����� ���訩 ��� � ����.
			tb = 127 & bufferspr[addrspr]; // 7FH � tb.

			addrspr--;

			for (cb = 0; cb < tb; cb++)
				{

				if (addrvcs >= 32768)
					{
					printf("\n");
					printf("%s", "�訡�� SPR 䠩��!");
					printf("\n");
					printf("\n");

					// �����襭��.
					exit(1);
					}

				screen_vector_8000_FFFF[addrvcs] = bufferspr[addrspr];

				addrvcs--;
				}
			}

		}

	addrvcs++;

//	printf("%s", "      ��ᯠ������: ");
//	printf("%u", 32768 - addrvcs);
//	printf("%s", " ����.");
//	printf("\n");

	if ((32768 - addrvcs) <= 32767)
		{
		printf("\n");
		printf("%s", "�訡�� SPR 䠩��!");
		printf("\n");
		printf("\n");

		// �����襭��.
		exit(1);
		}
}
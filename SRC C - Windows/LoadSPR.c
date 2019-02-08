
// �⥭�� SPR 䠩�� � ������.

#include <stdio.h>
#include <stdlib.h>

// ����� � ��६���� �� ��㣨� �ணࠬ�.
	unsigned char bufferspr[40960]; // ���ᨢ ��� SPR 䠩��.
	unsigned short int sizespr; // ������ SPR 䠩�� � �����.

void LoadSPR(unsigned char* filename)
{

	unsigned short int addrspr; // ���� � ���ᨢ� bufferspr.
	int byte; // ����騩 ���� �� SPR 䠩��.

	FILE *filed = NULL;
	// ����⨥ ����筮�� 䠩�� (rb).
	filed = fopen(filename, "rb");

	if (filed == NULL)
		{
		printf("\n");

		printf("%s", "��������!");
		printf("\n");

		printf("%s", "�訡�� ������ 䠩�� ");
		printf("%s", filename);
		printf("%s", ".");
		printf("\n");

		printf("\n");

		// �����襭�� � ����� �訡�� 1.
		exit(1);
		}

	addrspr = 0; sizespr = 0;

	while (1)
	{
	// �⥭�� ������ ���� �� 䠩��.
	byte = getc(filed);

	if (byte == EOF)
		{
		if (feof(filed) != 0)
			{
			// �⥭�� 䠩�� �����稫���.
			break;
			}
			else
			{
			// �訡�� �⥭�� �� 䠩��.
			printf("\n");

			printf("%s", "��������!");
			printf("\n");

			printf("%s", "�訡�� �⥭�� SPR 䠩��!");
			printf("\n");

			printf("\n");

			// �����襭��.
			exit(1);
			}
		}

	// ���誮� ����让 䠩�.
	if (sizespr == 40960)
		{

		// �����⨥ 䠩��.
		fclose(filed);

		printf("\n");
		printf("%s", "�訡�� SPR 䠩��!");
		printf("\n");
		printf("\n");

		// �����襭��.
		exit(1);
		}

	bufferspr[addrspr] = byte;
	addrspr++;
	sizespr++;
	}

	// �����⨥ 䠩��.
	fclose(filed);

}
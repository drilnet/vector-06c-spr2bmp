
// �������� ����᪨� 䠩��� (SPR � BMP).
// Ukraine. (C) Demidov S.V.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ---

	// ����㧨�� SPR 䠩�.
	extern unsigned char LoadSPR();

	// ��ᯠ������ SPR 䠩�.
	extern void UnpackingSPR();

	// ��४���஢��� 梥�.
	extern void CodeConversion();

	// ������ BMP 䠩�� �� ���.
	extern void SaveBMP();

	extern unsigned char bufferspr[32768]; // ���ᨢ ��� 䠩�� SPR.
	extern unsigned short int sizespr;     // ������ 䠩�� SPR � �����.
	extern unsigned long int sizedatabmp;  // ������ BMP ������.
	extern unsigned long int sizebmp;      // ������ BMP 䠩�� (��������� � �����).

void main(int argc, char* argv[])
{

	unsigned char addrcolorspr; // ���� 梥� � bufferspr[32768].
	unsigned char* filenamespr; // ��� SPR 䠩��.

	// ����� ��� BMP 䠩��.
	unsigned char filenamebmp[255] = { 0 };
	// ���� � ���ᨢ� filenamebmp[255].
	unsigned char addrfnb;

	filenamespr = argv[1];

	printf("\n");
	printf("%s", "�������� ����᪨� 䠩��� (SPR � BMP).");
	printf("\n");
	printf("%s", "   Ukraine. (C) ������� �.�.");
	printf("\n");
	printf("\n");
	printf("%s", "   SPR - ����᪨� �ଠ� 䠩��� �����'�-06�.");
	printf("\n");
	printf("%s", "   BMP - ����᪨� �ଠ� 䠩��� Windows.");
	printf("\n");

	if (argv[1] == NULL)
		{
		// �᫨ � ��������� ��ப� ����.
		printf("\n");
		printf("%s", "   ��ଠ� ��������� ��ப�:");
		printf("\n");
		printf("%s", "      $ spr2bmp ���_䠩��.spr");
		printf("\n");
		printf("\n");
		}
		else
		{
		// ---
		// | ����㧨�� SPR 䠩�.
		// ---
		LoadSPR(filenamespr);

		printf("\n");

		printf("%s", "             ����: ");
		printf("%s", filenamespr);
		printf("\n");

		// �뢥�� �� ���᮫� ࠧ��� 䠩�� SPR.
		printf("%s", " ������ SPR 䠩��: ");
		printf("%d", sizespr);
		printf("%s", " ");
		printf("%s", "����.");
		printf("\n");

		// ---
		// | ��ᯠ���뢠�� SPR 䠩�.
		// ---
		UnpackingSPR();

		// �뢥�� �� ���᮫� 梥� SPR 䠩��.
		printf("%s", "  ���� SPR 䠩��: ");

		for (addrcolorspr = 0; addrcolorspr < 16; addrcolorspr++)
			{
			// �뢮� 梥� � Hex.
			if (bufferspr[addrcolorspr] >=0 && bufferspr[addrcolorspr] <= 15)
				{
				// ���� ��। �᫮�.
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
		// | ��४���஢��.
		// | ��࠭��� ������� �����'�-06� � bmp �����.
		// ---
		CodeConversion();

		printf("%s", "������ BMP ������: ");
		printf("%u", sizedatabmp);
		printf("%s", " ���� (����� ���������).");
		printf("\n");

		// �����㥬 ���� ��ப� �� filenamespr� � filenamebmp.
		strncpy(filenamebmp, filenamespr + 0, strlen(filenamespr) - 4);

		addrfnb = strlen(filenamebmp);

		// ������� � ����� .bmp.
		filenamebmp[addrfnb++] = '.';
		filenamebmp[addrfnb++] = 'b';
		filenamebmp[addrfnb++] = 'm';
		filenamebmp[addrfnb++] = 'p';

		// ---
		// | ������ BMP 䠩�� �� ���.
		// ---
		SaveBMP(filenamebmp);

		printf("%s", " ������ BMP 䠩��: ");
		printf("%u", sizebmp);
		printf("%s", " ����.");
		printf("\n");

		printf("\n");

		printf("%s", "   ���� �������������! OK!");
		printf("\n");

		printf("\n");
		}
}

// ��४���஢��.
// ��࠭��� ������� �����'�-06� � BMP-䠩�.

	// ��� 梥� ��� BMP-䠩��.
	extern unsigned char B;
	extern unsigned char G;
	extern unsigned char R;

	extern unsigned char GetRGB();

	// ���ᨢ ��� SPR-䠩��.
	extern unsigned char bufferspr[40960];

	// ��࠭��� ������� �����-06�.
	extern unsigned char screen_vector_8000_FFFF[32768];

	unsigned char bufferbmp[196608]; // ���ᨢ ��� BMP-䠩�� (��� ���������).
	unsigned long int sizedatabmp; // ������ BMP-������.


void CodeConversion()
{
	// ���� � ���ᨢ� screen_vector_8000_FFFF[32768];
	unsigned short int addr_screen_8000_9FFF;
	unsigned short int addr_screen_A000_BFFF;
	unsigned short int addr_screen_C000_DFFF;
	unsigned short int addr_screen_E000_FFFF;

	unsigned char N; // ��� ��ॢ��� �᫠ � bin.

	// ���ᨢ� ��� ���⠭�� �� screen_vector_8000_FFFF[32768].
	unsigned char array_bit8_8000_9FFF[8];
	unsigned char array_bit8_A000_BFFF[8];
	unsigned char array_bit8_C000_DFFF[8];
	unsigned char array_bit8_E000_FFFF[8];
	char addrarraybit8; // ���� � ���ᨢ� array_bit8_8000_9FFF ... E000_FFFF.

	unsigned long int addrbmp; // ���� � ���ᨢ� bufferbmp[196608].
	unsigned long int push; // ��� ����������� ���� addrbmp.

	unsigned char x;
	unsigned short int y;

	addr_screen_8000_9FFF = 0;
		addr_screen_A000_BFFF = 8192;
			addr_screen_C000_DFFF = 16384;
				addr_screen_E000_FFFF = 24576;

	addrbmp = 0;
	sizedatabmp = 0;

	for (x = 0; x < 32; x++)
	{

	push = addrbmp;

	for (y = 0; y < 256; y++)
		{

		// 1.
		N = screen_vector_8000_FFFF[addr_screen_8000_9FFF];

		// N � ����筮� �᫮.
		addrarraybit8 = 0;
		while (N) // ���� �� ���稫��� ����.
			{
			array_bit8_8000_9FFF[addrarraybit8++] = N % 2;
			N = N / 2;
			}

		// ��⠢襩�� ���ᨢ ��������� ��ﬨ.
		for (addrarraybit8 = addrarraybit8; addrarraybit8 < 8;)
			{
			array_bit8_8000_9FFF[addrarraybit8] = 0;
			addrarraybit8++;
			}

		// 2.
		N = screen_vector_8000_FFFF[addr_screen_A000_BFFF];

		// N � ����筮� �᫮.
		addrarraybit8 = 0;
		while (N) // ���� �� ���稫��� ����.
			{
			array_bit8_A000_BFFF[addrarraybit8++] = N % 2;
			N = N / 2;
			}

		// ��⠢襩�� ���ᨢ ��������� ��ﬨ.
		for (addrarraybit8 = addrarraybit8; addrarraybit8 < 8;)
			{
			array_bit8_A000_BFFF[addrarraybit8] = 0;
			addrarraybit8++;
			}

		// 3.
		N = screen_vector_8000_FFFF[addr_screen_C000_DFFF];

		// N � ����筮� �᫮.
		addrarraybit8 = 0;
		while (N) // ���� �� ���稫��� ����.
			{
			array_bit8_C000_DFFF[addrarraybit8++] = N % 2;
			N = N / 2;
			}

		// ��⠢襩�� ���ᨢ ��������� ��ﬨ.
		for (addrarraybit8 = addrarraybit8; addrarraybit8 < 8;)
			{
			array_bit8_C000_DFFF[addrarraybit8] = 0;
			addrarraybit8++;
			}

		// 4.
		N = screen_vector_8000_FFFF[addr_screen_E000_FFFF];

		// N � ����筮� �᫮.
		addrarraybit8 = 0;
		while (N) // ���� �� ���稫��� ����.
			{
			array_bit8_E000_FFFF[addrarraybit8++] = N % 2;
			N = N / 2;
			}

		// ��⠢襩�� ���ᨢ ��������� ��ﬨ.
		for (addrarraybit8 = addrarraybit8; addrarraybit8 < 8;)
			{
			array_bit8_E000_FFFF[addrarraybit8] = 0;
			addrarraybit8++;
			}

		// ��४����㥬 梥�.
		for (addrarraybit8 = 7; addrarraybit8 > -1;) // ��ॡ�� � 7 ... 0.
			{

			if (array_bit8_E000_FFFF[addrarraybit8] == 0 && // 0.
			    array_bit8_C000_DFFF[addrarraybit8] == 0 &&
			    array_bit8_A000_BFFF[addrarraybit8] == 0 &&
			    array_bit8_8000_9FFF[addrarraybit8] == 0)
				{
				// ���� 梥� �� SPR-䠩�� (bufferspr[0]).
				GetRGB(bufferspr[0]);

				bufferbmp[addrbmp] = B; // ���� B.
				addrbmp++;
				bufferbmp[addrbmp] = G; // ���� G.
				addrbmp++;
				bufferbmp[addrbmp] = R; // ���� R.

				sizedatabmp = sizedatabmp + 3;
				goto M1;
				}

			if (array_bit8_E000_FFFF[addrarraybit8] == 1 && // 1.
			    array_bit8_C000_DFFF[addrarraybit8] == 0 &&
			    array_bit8_A000_BFFF[addrarraybit8] == 0 &&
			    array_bit8_8000_9FFF[addrarraybit8] == 0)
				{
				// ���� 梥� �� SPR-䠩�� (bufferspr[1]).
				GetRGB(bufferspr[1]);

				bufferbmp[addrbmp] = B; // ���� B.
				addrbmp++;
				bufferbmp[addrbmp] = G; // ���� G.
				addrbmp++;
				bufferbmp[addrbmp] = R; // ���� R.

				sizedatabmp = sizedatabmp + 3;
				goto M1;
				}

			if (array_bit8_E000_FFFF[addrarraybit8] == 0 && // 2.
			    array_bit8_C000_DFFF[addrarraybit8] == 1 &&
			    array_bit8_A000_BFFF[addrarraybit8] == 0 &&
			    array_bit8_8000_9FFF[addrarraybit8] == 0)
				{
				// ���� 梥� �� SPR-䠩�� (bufferspr[2]).
				GetRGB(bufferspr[2]);

				bufferbmp[addrbmp] = B; // ���� B.
				addrbmp++;
				bufferbmp[addrbmp] = G; // ���� G.
				addrbmp++;
				bufferbmp[addrbmp] = R; // ���� R.

				sizedatabmp = sizedatabmp + 3;
				goto M1;
				}

			if (array_bit8_E000_FFFF[addrarraybit8] == 1 && // 3.
			    array_bit8_C000_DFFF[addrarraybit8] == 1 &&
			    array_bit8_A000_BFFF[addrarraybit8] == 0 &&
			    array_bit8_8000_9FFF[addrarraybit8] == 0)
				{
				// ���� 梥� �� SPR-䠩�� (bufferspr[3]).
				GetRGB(bufferspr[3]);

				bufferbmp[addrbmp] = B; // ���� B.
				addrbmp++;
				bufferbmp[addrbmp] = G; // ���� G.
				addrbmp++;
				bufferbmp[addrbmp] = R; // ���� R.

				sizedatabmp = sizedatabmp + 3;
				goto M1;
				}

			if (array_bit8_E000_FFFF[addrarraybit8] == 0 && // 4.
			    array_bit8_C000_DFFF[addrarraybit8] == 0 &&
			    array_bit8_A000_BFFF[addrarraybit8] == 1 &&
			    array_bit8_8000_9FFF[addrarraybit8] == 0)
				{
				// ���� 梥� �� SPR-䠩�� (bufferspr[4]).
				GetRGB(bufferspr[4]);

				bufferbmp[addrbmp] = B; // ���� B.
				addrbmp++;
				bufferbmp[addrbmp] = G; // ���� G.
				addrbmp++;
				bufferbmp[addrbmp] = R; // ���� R.

				sizedatabmp = sizedatabmp + 3;
				goto M1;
				}

			if (array_bit8_E000_FFFF[addrarraybit8] == 1 && // 5.
			    array_bit8_C000_DFFF[addrarraybit8] == 0 &&
			    array_bit8_A000_BFFF[addrarraybit8] == 1 &&
			    array_bit8_8000_9FFF[addrarraybit8] == 0)
				{
				// ���� 梥� �� SPR-䠩�� (bufferspr[5]).
				GetRGB(bufferspr[5]);

				bufferbmp[addrbmp] = B; // ���� B.
				addrbmp++;
				bufferbmp[addrbmp] = G; // ���� G.
				addrbmp++;
				bufferbmp[addrbmp] = R; // ���� R.

				sizedatabmp = sizedatabmp + 3;
				goto M1;
				}

			if (array_bit8_E000_FFFF[addrarraybit8] == 0 && // 6.
			    array_bit8_C000_DFFF[addrarraybit8] == 1 &&
			    array_bit8_A000_BFFF[addrarraybit8] == 1 &&
			    array_bit8_8000_9FFF[addrarraybit8] == 0)
				{
				// ���� 梥� �� SPR-䠩�� (bufferspr[6]).
				GetRGB(bufferspr[6]);

				bufferbmp[addrbmp] = B; // ���� B.
				addrbmp++;
				bufferbmp[addrbmp] = G; // ���� G.
				addrbmp++;
				bufferbmp[addrbmp] = R; // ���� R.

				sizedatabmp = sizedatabmp + 3;
				goto M1;
				}

			if (array_bit8_E000_FFFF[addrarraybit8] == 1 && // 7.
			    array_bit8_C000_DFFF[addrarraybit8] == 1 &&
			    array_bit8_A000_BFFF[addrarraybit8] == 1 &&
			    array_bit8_8000_9FFF[addrarraybit8] == 0)
				{
				// ���� 梥� �� SPR-䠩�� (bufferspr[7]).
				GetRGB(bufferspr[7]);

				bufferbmp[addrbmp] = B; // ���� B.
				addrbmp++;
				bufferbmp[addrbmp] = G; // ���� G.
				addrbmp++;
				bufferbmp[addrbmp] = R; // ���� R.

				sizedatabmp = sizedatabmp + 3;
				goto M1;
				}

			if (array_bit8_E000_FFFF[addrarraybit8] == 0 && // 8.
			    array_bit8_C000_DFFF[addrarraybit8] == 0 &&
			    array_bit8_A000_BFFF[addrarraybit8] == 0 &&
			    array_bit8_8000_9FFF[addrarraybit8] == 1)
				{
				// ���� 梥� �� SPR-䠩�� (bufferspr[8]).
				GetRGB(bufferspr[8]);

				bufferbmp[addrbmp] = B; // ���� B.
				addrbmp++;
				bufferbmp[addrbmp] = G; // ���� G.
				addrbmp++;
				bufferbmp[addrbmp] = R; // ���� R.

				sizedatabmp = sizedatabmp + 3;
				goto M1;
				}

			if (array_bit8_E000_FFFF[addrarraybit8] == 1 && // 9.
			    array_bit8_C000_DFFF[addrarraybit8] == 0 &&
			    array_bit8_A000_BFFF[addrarraybit8] == 0 &&
			    array_bit8_8000_9FFF[addrarraybit8] == 1)
				{
				// ���� 梥� �� SPR-䠩�� (bufferspr[9]).
				GetRGB(bufferspr[9]);

				bufferbmp[addrbmp] = B; // ���� B.
				addrbmp++;
				bufferbmp[addrbmp] = G; // ���� G.
				addrbmp++;
				bufferbmp[addrbmp] = R; // ���� R.

				sizedatabmp = sizedatabmp + 3;
				goto M1;
				}

			if (array_bit8_E000_FFFF[addrarraybit8] == 0 && // 10.
			    array_bit8_C000_DFFF[addrarraybit8] == 1 &&
			    array_bit8_A000_BFFF[addrarraybit8] == 0 &&
			    array_bit8_8000_9FFF[addrarraybit8] == 1)
				{
				// ���� 梥� �� SPR-䠩�� (bufferspr[10]).
				GetRGB(bufferspr[10]);

				bufferbmp[addrbmp] = B; // ���� B.
				addrbmp++;
				bufferbmp[addrbmp] = G; // ���� G.
				addrbmp++;
				bufferbmp[addrbmp] = R; // ���� R.

				sizedatabmp = sizedatabmp + 3;
				goto M1;
				}

			if (array_bit8_E000_FFFF[addrarraybit8] == 1 && // 11.
			    array_bit8_C000_DFFF[addrarraybit8] == 1 &&
			    array_bit8_A000_BFFF[addrarraybit8] == 0 &&
			    array_bit8_8000_9FFF[addrarraybit8] == 1)
				{
				// ���� 梥� �� SPR-䠩�� (bufferspr[11]).
				GetRGB(bufferspr[11]);

				bufferbmp[addrbmp] = B; // ���� B.
				addrbmp++;
				bufferbmp[addrbmp] = G; // ���� G.
				addrbmp++;
				bufferbmp[addrbmp] = R; // ���� R.

				sizedatabmp = sizedatabmp + 3;
				goto M1;
				}

			if (array_bit8_E000_FFFF[addrarraybit8] == 0 && // 12.
			    array_bit8_C000_DFFF[addrarraybit8] == 0 &&
			    array_bit8_A000_BFFF[addrarraybit8] == 1 &&
			    array_bit8_8000_9FFF[addrarraybit8] == 1)
				{
				// ���� 梥� �� SPR-䠩�� (bufferspr[12]).
				GetRGB(bufferspr[12]);

				bufferbmp[addrbmp] = B; // ���� B.
				addrbmp++;
				bufferbmp[addrbmp] = G; // ���� G.
				addrbmp++;
				bufferbmp[addrbmp] = R; // ���� R.

				sizedatabmp = sizedatabmp + 3;
				goto M1;
				}

			if (array_bit8_E000_FFFF[addrarraybit8] == 1 && // 13.
			    array_bit8_C000_DFFF[addrarraybit8] == 0 &&
			    array_bit8_A000_BFFF[addrarraybit8] == 1 &&
			    array_bit8_8000_9FFF[addrarraybit8] == 1)
				{
				// ���� 梥� �� SPR-䠩�� (bufferspr[13]).
				GetRGB(bufferspr[13]);

				bufferbmp[addrbmp] = B; // ���� B.
				addrbmp++;
				bufferbmp[addrbmp] = G; // ���� G.
				addrbmp++;
				bufferbmp[addrbmp] = R; // ���� R.

				sizedatabmp = sizedatabmp + 3;
				goto M1;
				}

			if (array_bit8_E000_FFFF[addrarraybit8] == 0 && // 14.
			    array_bit8_C000_DFFF[addrarraybit8] == 1 &&
			    array_bit8_A000_BFFF[addrarraybit8] == 1 &&
			    array_bit8_8000_9FFF[addrarraybit8] == 1)
				{
				// ���� 梥� �� SPR-䠩�� (bufferspr[14]).
				GetRGB(bufferspr[14]);

				bufferbmp[addrbmp] = B; // ���� B.
				addrbmp++;
				bufferbmp[addrbmp] = G; // ���� G.
				addrbmp++;
				bufferbmp[addrbmp] = R; // ���� R.

				sizedatabmp = sizedatabmp + 3;
				goto M1;
				}

			if (array_bit8_E000_FFFF[addrarraybit8] == 1 && // 15.
			    array_bit8_C000_DFFF[addrarraybit8] == 1 &&
			    array_bit8_A000_BFFF[addrarraybit8] == 1 &&
			    array_bit8_8000_9FFF[addrarraybit8] == 1)
				{
				// ���� 梥� �� SPR-䠩�� (bufferspr[15]).
				GetRGB(bufferspr[15]);

				bufferbmp[addrbmp] = B; // ���� B.
				addrbmp++;
				bufferbmp[addrbmp] = G; // ���� G.
				addrbmp++;
				bufferbmp[addrbmp] = R; // ���� R.

				sizedatabmp = sizedatabmp + 3;
				}

M1:

			addrarraybit8--;
			addrbmp++;

			// addrarraybit8.
			}

		addrbmp = addrbmp - 24 + 256 * 3;

		addr_screen_8000_9FFF++;
		addr_screen_A000_BFFF++;
		addr_screen_C000_DFFF++;
		addr_screen_E000_FFFF++;

		// y.
		}

	addrbmp = push;
	addrbmp = addrbmp + 24;

	// x.
	}

}

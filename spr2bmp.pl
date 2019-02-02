
# Perl.
# Конвертер графических файлов (SPR в BMP).
# Ukraine. (C) Демидов С.В.';

	# Для объявления переменных.
	use strict;

	# В случае возникновений каких-либо проблем нужно остановить работу скрипта.
	use warnings FATAL => 'all';

	my $filename_SPR; # Здесь имя SPR файла (или ASM, если чтение из исходников).
	my $size_SPR; # Размер SPR файла.

	# Считываем SPR данные.
	# ---
	my $line_SPR;   # Текущая строка из файла $filename_SPR (если чтение из исходников).
	my $count_line; # Количество строк в $filename_SPR (если чтение из исходников)..
	my $pos_DB;     # Позиция DB в $line_SPR (чтение из исходников).
	my $data_SPR;   # Данные SPR (с запятыми).

	my @array_color_SPR; # Массив цветов (16 байт) SPR файла.
	my @array_data_SPR;  # Массив с данными SPR.

	# Распаковка SPR данных.
	# ---
	my $addr_VCS; # Адрес для экранной области Вектора (в массиве).
	my $addr_SPR; # Адрес для данныx SPR (в массиве).

	my $bit_s;      # 1 - повторяющиеся байты, 0 - не повторяющиеся байты.
	my $count_byte; # Счётчик для повторяющихся байт и не для поворяющихся.
	my $total_byte; # Сколько повторяющихся байт и сколько не повторяющихся байт.

	# Экранная область Вектор-06Ц.
	# Здесь распакованные данные.
	my @array_screen_area_8000_FFFF;

	# Вывод цветов SPR файла на экран.
	# ---
	my $count_color; # Счётчик для цветов.

	# Перекодировка цвета.
	# ---
	my $addr_screen_8000_9FFF; # Адрес экранной области Вектор-06Ц.
	my $addr_screen_A000_BFFF; # -/-
	my $addr_screen_C000_DFFF; # -/-
	my $addr_screen_E000_FFFF; # -/-

	my $bit8_8000_9FFF; # 8 бит из экранной области Вектор-06Ц.
	my $bit8_A000_BFFF; # -/-
	my $bit8_C000_DFFF; # -/-
	my $bit8_E000_FFFF; # -/-

	my $z;
	my $y;
	my $x;

	my $addr_bmp; # Адрес в массиве @array_data_bmp_hex;

	# Запись BMP файла.
	# ---
	my $title_bmp_hex;   # Заголовок bmp файла.
	my $file_bmp_length; # Длина (размер) bmp файла.
	my $filename_BMP;    # Здесь имя BMP файла.

	# ---

	my @array_bit8_8000_9FFF; # Массив с восемью битами (перекодировка цвета).
	my @array_bit8_A000_BFFF; # -/-
	my @array_bit8_C000_DFFF; # -/-
	my @array_bit8_E000_FFFF; # -/-

	my @array_data_bmp_hex; # Массив с данными (данные bmp файла).

	#
	# ---
	my $temp; # Временный результат.

	if (defined $ARGV[0] != 1) # Если неинициализирован @ARGV, значит, пусто.
		{
		$ARGV[0] = '';
		}

	if (defined $ARGV[1] != 1) # Если неинициализирован @ARGV, значит, пусто.
		{
		$ARGV[1] = '';
		}

	$filename_SPR = $ARGV[0];

	if ($ARGV[0] eq '')
	{

	print "\n";
	print 'Конвертер графических файлов (SPR в BMP).';
	print "\n";
	print '   Ukraine. (C) Демидов С.В.';
	print "\n";
	print "\n";
	print '   SPR - графический формат файлов Вектор\'а-06Ц.';
	print "\n";
	print '   BMP - графический формат файлов Windows.';
	print "\n";
	print "\n";
	print '   Формат командной строки:';
	print "\n";
	print '      $ perl spr2bmp.pl имя_файла.spr';
	print "\n";
	print '      $ perl spr2bmp.pl имя_файла.asm ASM <- Считывать будем из исходников.';
	print "\n";
	print "\n";

	}
	else
	{

	$count_line = 1;
	$data_SPR = '';

	print "\n";

# ---

	print '             Файл: ';
	print $filename_SPR;
	print "\n";

# ---

	my $sw;

	if ($ARGV[1] eq '')
		{
		$sw = 1;
		}
		else
		{
		$sw = 0; # Считывать будет из исходников.
		}

	if ($sw == 0)
		{
		open(InFile, '<', $filename_SPR) || die "Не могу открыть файл $filename_SPR";

		while ($line_SPR = <InFile>)
			{
			# Ищем DB.
			$pos_DB = index($line_SPR, 'DB', 0);

			if ($pos_DB ne '-1')
				{
				# Вырезаем после DB.
				$temp = substr($line_SPR, $pos_DB + 3);

				# Если строка первая, значит цвета SPR.
				if ($count_line == 1)
					{
				# Здесь цвета SPR.

					@array_color_SPR = split(',', $temp);
					}
					else
					{
				# Здесь данные SPR.

					# Удаляем \n.
					$_ = $temp;
					s/\n//g;
					$temp = $_;

					# Удаляем \r.
					$_ = $temp;
					s/\r//g;
					$temp = $_;

					if ($count_line == 2)
						{
						$data_SPR.= $temp;
						}
						else
						{
						$data_SPR.= ',' . $temp;
						}

					#print $temp . "\n";
					#<STDIN>;
					}

				$count_line++;
				}
			}

		close (InFile);

		# Данные SPR в массив.
		@array_data_SPR = split(',', $data_SPR);
		}
		else
		{
		# Получить размер SPR файла.
		$size_SPR = -s "$filename_SPR";

		print ' Размер SPR файла: ' . $size_SPR . ' байт.';
		print "\n";

		# Чтение SPR файла.
		open (InFileBin, "<" . $filename_SPR) or die "Ошибка...";
			sysread(InFileBin, $temp, $size_SPR, 0);
				close (InFileBin);

		$temp = unpack('H' . $size_SPR * 2, $temp);

		@array_color_SPR = unpack("(a2)*", substr($temp, 0, 16*2));
		@array_data_SPR = unpack("(a2)*", substr($temp, 16*2));

		# Палитру в Dec.
		for ($z=0; $z < @array_color_SPR;)
			{
			$array_color_SPR[$z] = hex $array_color_SPR[$z];
			$z++;
			}

		# SPR данные в Dec.
		for ($z=0; $z < @array_data_SPR;)
			{
			$array_data_SPR[$z] = hex $array_data_SPR[$z];
			$z++;
			}
		}

# ---

	print 'Размер SPR данных: ' . scalar(@array_data_SPR) . ' байт.';
	print "\n";

# ---

	# Вывод цветов.

	print '  Цвета SPR файла: ';

	for ($count_color = 0; $count_color < 16;)
		{
		print sprintf("%02X", $array_color_SPR[$count_color]) . 'H';
		if ($count_color != 15)
			{
			print ' ';
			}

		$count_color++;
		}

	print'.';
	print "\n";

# ---

	# ---
	# | Распаковка SPR данных.
	# ---

	$addr_VCS = 32767;

	$addr_SPR = scalar(@array_data_SPR) - 1;

	# Пропустить нули.
	for ($addr_SPR = $addr_SPR; $addr_SPR > 0;)
		{
		if ($array_data_SPR[$addr_SPR] ne '0')
			{
			last;
			}

		$addr_SPR--;
		}	

	# Сама распаковка.
	for ($addr_SPR = $addr_SPR; $addr_SPR > 0;)
		{
		if ($addr_SPR >= 32768 || $addr_SPR <= -1)
			{
			print "\n";
			print 'Ошибка SPR файла!';
			print "\n";
			print "\n";

			# Завершение.
			exit;
			}

		$bit_s = substr(sprintf("%08b", $array_data_SPR[$addr_SPR]), 0, 1);

		if ($bit_s eq '0')
			{
			# Не повторяющиеся байты.
			# ---

			$total_byte = $array_data_SPR[$addr_SPR];

			for ($count_byte = 0; $count_byte < $total_byte;)
				{
				$addr_SPR--;

				if ($addr_SPR >= 32768 || $addr_SPR <= -1)
					{
					print "\n";
					print 'Ошибка SPR файла!';
					print "\n";
					print "\n";

					# Завершение.
					exit;
					}

				$array_screen_area_8000_FFFF[$addr_VCS] = $array_data_SPR[$addr_SPR];

				$addr_VCS--;

				$count_byte++;
				}

			}
			else
			{
			# Повторяющиеся байты..
			# ---

			$total_byte = $array_data_SPR[$addr_SPR];
			$total_byte = 127 & $total_byte; # 7F и $total_byte.

			$addr_SPR--;

			for ($count_byte = 0; $count_byte < $total_byte;)
				{

				if ($addr_SPR >= 32768 || $addr_SPR <= -1)
					{
					print "\n";
					print 'Ошибка SPR файла!';
					print "\n";
					print "\n";

					# Завершение.
					exit;
					}

				$array_screen_area_8000_FFFF[$addr_VCS] = $array_data_SPR[$addr_SPR];

				$addr_VCS--;

				$count_byte++;
				}

			}

		$addr_SPR--;
		}

	print '      Распаковано: ' . scalar(@array_screen_area_8000_FFFF) . ' байт.';
	print "\n";

# ---

	# Перекодировка цвета.

	$addr_screen_8000_9FFF = 0;
	$addr_screen_A000_BFFF = 8192;
	$addr_screen_C000_DFFF = 16384;
	$addr_screen_E000_FFFF = 24576;

	$addr_bmp = 0; # Левый нижний угол.

	for ($z = 0; $z < 32;)
		{

		my $push = $addr_bmp;

		for ($y=0; $y < 256;)
			{
			$bit8_8000_9FFF = sprintf("%08b", $array_screen_area_8000_FFFF[$addr_screen_8000_9FFF]);
			$bit8_A000_BFFF = sprintf("%08b", $array_screen_area_8000_FFFF[$addr_screen_A000_BFFF]);
			$bit8_C000_DFFF = sprintf("%08b", $array_screen_area_8000_FFFF[$addr_screen_C000_DFFF]);
			$bit8_E000_FFFF = sprintf("%08b", $array_screen_area_8000_FFFF[$addr_screen_E000_FFFF]);

			@array_bit8_8000_9FFF = split('', $bit8_8000_9FFF);
			@array_bit8_A000_BFFF = split('', $bit8_A000_BFFF);
			@array_bit8_C000_DFFF = split('', $bit8_C000_DFFF);
			@array_bit8_E000_FFFF = split('', $bit8_E000_FFFF);

			# Обрабатываем 4-ре байта.
			for ($x=0; $x < 8;)
				{
				if ($array_bit8_E000_FFFF[$x] eq '0' && # 0.
				    $array_bit8_C000_DFFF[$x] eq '0' &&
				    $array_bit8_A000_BFFF[$x] eq '0' &&
				    $array_bit8_8000_9FFF[$x] eq '0')
					{
					# В $temp BGR.
					$temp = getRGB($array_color_SPR[0]);
					# Цвет B.
					$array_data_bmp_hex[$addr_bmp] = substr($temp, 0, 2);
					$addr_bmp++;
					# Цвет G.
					$array_data_bmp_hex[$addr_bmp] = substr($temp, 2, 2);
					$addr_bmp++;
					# Цвет R.
					$array_data_bmp_hex[$addr_bmp] = substr($temp, 4, 2);
					}

				if ($array_bit8_E000_FFFF[$x] eq '1' && # 1.
				    $array_bit8_C000_DFFF[$x] eq '0' &&
				    $array_bit8_A000_BFFF[$x] eq '0' &&
				    $array_bit8_8000_9FFF[$x] eq '0')
					{
					# В $temp BGR.
					$temp = getRGB($array_color_SPR[1]);
					# Цвет B.
					$array_data_bmp_hex[$addr_bmp] = substr($temp, 0, 2);
					$addr_bmp++;
					# Цвет G.
					$array_data_bmp_hex[$addr_bmp] = substr($temp, 2, 2);
					$addr_bmp++;
					# Цвет R.
					$array_data_bmp_hex[$addr_bmp] = substr($temp, 4, 2);
					}

				if ($array_bit8_E000_FFFF[$x] eq '0' && # 2.
				    $array_bit8_C000_DFFF[$x] eq '1' &&
				    $array_bit8_A000_BFFF[$x] eq '0' &&
				    $array_bit8_8000_9FFF[$x] eq '0')
					{
					# В $temp BGR.
					$temp = getRGB($array_color_SPR[2]);
					# Цвет B.
					$array_data_bmp_hex[$addr_bmp] = substr($temp, 0, 2);
					$addr_bmp++;
					# Цвет G.
					$array_data_bmp_hex[$addr_bmp] = substr($temp, 2, 2);
					$addr_bmp++;
					# Цвет R.
					$array_data_bmp_hex[$addr_bmp] = substr($temp, 4, 2);
					}

				if ($array_bit8_E000_FFFF[$x] eq '1' && # 3.
				    $array_bit8_C000_DFFF[$x] eq '1' &&
				    $array_bit8_A000_BFFF[$x] eq '0' &&
				    $array_bit8_8000_9FFF[$x] eq '0')
					{
					# В $temp BGR.
					$temp = getRGB($array_color_SPR[3]);
					# Цвет B.
					$array_data_bmp_hex[$addr_bmp] = substr($temp, 0, 2);
					$addr_bmp++;
					# Цвет G.
					$array_data_bmp_hex[$addr_bmp] = substr($temp, 2, 2);
					$addr_bmp++;
					# Цвет R.
					$array_data_bmp_hex[$addr_bmp] = substr($temp, 4, 2);
					}

				if ($array_bit8_E000_FFFF[$x] eq '0' && # 4.
				    $array_bit8_C000_DFFF[$x] eq '0' &&
				    $array_bit8_A000_BFFF[$x] eq '1' &&
				    $array_bit8_8000_9FFF[$x] eq '0')
					{
					# В $temp BGR.
					$temp = getRGB($array_color_SPR[4]);
					# Цвет B.
					$array_data_bmp_hex[$addr_bmp] = substr($temp, 0, 2);
					$addr_bmp++;
					# Цвет G.
					$array_data_bmp_hex[$addr_bmp] = substr($temp, 2, 2);
					$addr_bmp++;
					# Цвет R.
					$array_data_bmp_hex[$addr_bmp] = substr($temp, 4, 2);
					}

				if ($array_bit8_E000_FFFF[$x] eq '1' && # 5.
				    $array_bit8_C000_DFFF[$x] eq '0' &&
				    $array_bit8_A000_BFFF[$x] eq '1' &&
				    $array_bit8_8000_9FFF[$x] eq '0')
					{
					# В $temp BGR.
					$temp = getRGB($array_color_SPR[5]);
					# Цвет B.
					$array_data_bmp_hex[$addr_bmp] = substr($temp, 0, 2);
					$addr_bmp++;
					# Цвет G.
					$array_data_bmp_hex[$addr_bmp] = substr($temp, 2, 2);
					$addr_bmp++;
					# Цвет R.
					$array_data_bmp_hex[$addr_bmp] = substr($temp, 4, 2);
					}

				if ($array_bit8_E000_FFFF[$x] eq '0' && # 6.
				    $array_bit8_C000_DFFF[$x] eq '1' &&
				    $array_bit8_A000_BFFF[$x] eq '1' &&
				    $array_bit8_8000_9FFF[$x] eq '0')
					{
					# В $temp BGR.
					$temp = getRGB($array_color_SPR[6]);
					# Цвет B.
					$array_data_bmp_hex[$addr_bmp] = substr($temp, 0, 2);
					$addr_bmp++;
					# Цвет G.
					$array_data_bmp_hex[$addr_bmp] = substr($temp, 2, 2);
					$addr_bmp++;
					# Цвет R.
					$array_data_bmp_hex[$addr_bmp] = substr($temp, 4, 2);
					}

				if ($array_bit8_E000_FFFF[$x] eq '1' && # 7.
				    $array_bit8_C000_DFFF[$x] eq '1' &&
				    $array_bit8_A000_BFFF[$x] eq '1' &&
				    $array_bit8_8000_9FFF[$x] eq '0')
					{
					# В $temp BGR.
					$temp = getRGB($array_color_SPR[7]);
					# Цвет B.
					$array_data_bmp_hex[$addr_bmp] = substr($temp, 0, 2);
					$addr_bmp++;
					# Цвет G.
					$array_data_bmp_hex[$addr_bmp] = substr($temp, 2, 2);
					$addr_bmp++;
					# Цвет R.
					$array_data_bmp_hex[$addr_bmp] = substr($temp, 4, 2);
					}

				if ($array_bit8_E000_FFFF[$x] eq '0' && # 8.
				    $array_bit8_C000_DFFF[$x] eq '0' &&
				    $array_bit8_A000_BFFF[$x] eq '0' &&
				    $array_bit8_8000_9FFF[$x] eq '1')
					{
					# В $temp BGR.
					$temp = getRGB($array_color_SPR[8]);
					# Цвет B.
					$array_data_bmp_hex[$addr_bmp] = substr($temp, 0, 2);
					$addr_bmp++;
					# Цвет G.
					$array_data_bmp_hex[$addr_bmp] = substr($temp, 2, 2);
					$addr_bmp++;
					# Цвет R.
					$array_data_bmp_hex[$addr_bmp] = substr($temp, 4, 2);
					}

				if ($array_bit8_E000_FFFF[$x] eq '1' && # 9.
				    $array_bit8_C000_DFFF[$x] eq '0' &&
				    $array_bit8_A000_BFFF[$x] eq '0' &&
				    $array_bit8_8000_9FFF[$x] eq '1')
					{
					# В $temp BGR.
					$temp = getRGB($array_color_SPR[9]);
					# Цвет B.
					$array_data_bmp_hex[$addr_bmp] = substr($temp, 0, 2);
					$addr_bmp++;
					# Цвет G.
					$array_data_bmp_hex[$addr_bmp] = substr($temp, 2, 2);
					$addr_bmp++;
					# Цвет R.
					$array_data_bmp_hex[$addr_bmp] = substr($temp, 4, 2);
					}

				if ($array_bit8_E000_FFFF[$x] eq '0' && # 10.
				    $array_bit8_C000_DFFF[$x] eq '1' &&
				    $array_bit8_A000_BFFF[$x] eq '0' &&
				    $array_bit8_8000_9FFF[$x] eq '1')
					{
					# В $temp BGR.
					$temp = getRGB($array_color_SPR[10]);
					# Цвет B.
					$array_data_bmp_hex[$addr_bmp] = substr($temp, 0, 2);
					$addr_bmp++;
					# Цвет G.
					$array_data_bmp_hex[$addr_bmp] = substr($temp, 2, 2);
					$addr_bmp++;
					# Цвет R.
					$array_data_bmp_hex[$addr_bmp] = substr($temp, 4, 2);
					}

				if ($array_bit8_E000_FFFF[$x] eq '1' && # 11.
				    $array_bit8_C000_DFFF[$x] eq '1' &&
				    $array_bit8_A000_BFFF[$x] eq '0' &&
				    $array_bit8_8000_9FFF[$x] eq '1')
					{
					# В $temp BGR.
					$temp = getRGB($array_color_SPR[11]);
					# Цвет B.
					$array_data_bmp_hex[$addr_bmp] = substr($temp, 0, 2);
					$addr_bmp++;
					# Цвет G.
					$array_data_bmp_hex[$addr_bmp] = substr($temp, 2, 2);
					$addr_bmp++;
					# Цвет R.
					$array_data_bmp_hex[$addr_bmp] = substr($temp, 4, 2);
					}

				if ($array_bit8_E000_FFFF[$x] eq '0' && # 12.
				    $array_bit8_C000_DFFF[$x] eq '0' &&
				    $array_bit8_A000_BFFF[$x] eq '1' &&
				    $array_bit8_8000_9FFF[$x] eq '1')
					{
					# В $temp BGR.
					$temp = getRGB($array_color_SPR[12]);
					# Цвет B.
					$array_data_bmp_hex[$addr_bmp] = substr($temp, 0, 2);
					$addr_bmp++;
					# Цвет G.
					$array_data_bmp_hex[$addr_bmp] = substr($temp, 2, 2);
					$addr_bmp++;
					# Цвет R.
					$array_data_bmp_hex[$addr_bmp] = substr($temp, 4, 2);
						}

				if ($array_bit8_E000_FFFF[$x] eq '1' && # 13.
				    $array_bit8_C000_DFFF[$x] eq '0' &&
				    $array_bit8_A000_BFFF[$x] eq '1' &&
				    $array_bit8_8000_9FFF[$x] eq '1')
					{
					# В $temp BGR.
					$temp = getRGB($array_color_SPR[13]);
					# Цвет B.
					$array_data_bmp_hex[$addr_bmp] = substr($temp, 0, 2);
					$addr_bmp++;
					# Цвет G.
					$array_data_bmp_hex[$addr_bmp] = substr($temp, 2, 2);
					$addr_bmp++;
					# Цвет R.
					$array_data_bmp_hex[$addr_bmp] = substr($temp, 4, 2);
					}

				if ($array_bit8_E000_FFFF[$x] eq '0' && # 14.
				    $array_bit8_C000_DFFF[$x] eq '1' &&
				    $array_bit8_A000_BFFF[$x] eq '1' &&
				    $array_bit8_8000_9FFF[$x] eq '1')
					{
					# В $temp BGR.
					$temp = getRGB($array_color_SPR[14]);
					# Цвет B.
					$array_data_bmp_hex[$addr_bmp] = substr($temp, 0, 2);
					$addr_bmp++;
					# Цвет G.
					$array_data_bmp_hex[$addr_bmp] = substr($temp, 2, 2);
					$addr_bmp++;
					# Цвет R.
					$array_data_bmp_hex[$addr_bmp] = substr($temp, 4, 2);
					}

				if ($array_bit8_E000_FFFF[$x] eq '1' && # 15.
				    $array_bit8_C000_DFFF[$x] eq '1' &&
				    $array_bit8_A000_BFFF[$x] eq '1' &&
				    $array_bit8_8000_9FFF[$x] eq '1')
					{
					# В $temp BGR.
					$temp = getRGB($array_color_SPR[15]);
					# Цвет B.
					$array_data_bmp_hex[$addr_bmp] = substr($temp, 0, 2);
					$addr_bmp++;
					# Цвет G.
					$array_data_bmp_hex[$addr_bmp] = substr($temp, 2, 2);
					$addr_bmp++;
					# Цвет R.
					$array_data_bmp_hex[$addr_bmp] = substr($temp, 4, 2);
					}

				$addr_bmp++;
				$x++;
				}

			$addr_bmp = $addr_bmp - 24 + 256 * 3;

			$addr_screen_8000_9FFF++;
			$addr_screen_A000_BFFF++;
			$addr_screen_C000_DFFF++;
			$addr_screen_E000_FFFF++;

			$y++;
			}

		$addr_bmp = $push;
		$addr_bmp = $addr_bmp + 24;

		$z++;
		}

# ---

	# Заголовок bmp файла.
	$title_bmp_hex = '424d7a000300000000007a0000006c00'; # 0000.
	$title_bmp_hex.= '00000001000000010000010018000000'; # 0010.
	$title_bmp_hex.= '000000000300130b0000130b00000000'; # 0020.
	$title_bmp_hex.= '00000000000042475273000000000000'; # 0030.
	$title_bmp_hex.= '00000000000000000000000000000000'; # 0040.
	$title_bmp_hex.= '00000000000000000000000000000000'; # 0050.
	$title_bmp_hex.= '00000000000000000000020000000000'; # 0060.
	$title_bmp_hex.= '00000000000000000000';             # 0070.

	$temp = $title_bmp_hex . join('', @array_data_bmp_hex);
	$file_bmp_length = length($temp) / 2;
	$temp = pack('H' . length($temp), $temp);

	print 'Размер BMP данных: ' . scalar(@array_data_bmp_hex) . '. ';
	print "\n";
	print ' Размер BMP файла: ' . $file_bmp_length . '. ';
	print "\n";

	$filename_BMP = substr($filename_SPR, 0, length($filename_SPR) - 3);
	$filename_BMP.= 'bmp';

	# Записать изображение (файл bmp).
	open (InFileBin, ">" . $filename_BMP) or die "Ошибка...";
		syswrite(InFileBin, $temp, $file_bmp_length, 0);
			close (InFileBin);

	print "\n";
	print '   OK!';
	print "\n";
	print "\n";

	}

# ----- ----- ----- ----- ----- ----- -----

#
# Цвета Вектор-06Ц через цвета PC компьютера.
#

sub getRGB
{
	my $countpalette; # Сяётчик для палитры.
	my $R_bit;   # Биты для R.
	my $G_bit;   # Биты для G.
	my $B_bit;   # Биты для B.
	my $R;       # Текущий цвет R.
	my $G;       # Текущий цвет G.
	my $B;       # Текущий цвет B.
	my $RGB_hex; # Текущий цвет RGB (hex).
	my $BGR_hex; # Текущий цвет RGB (hex) наоборот.

	# Массивы цветов Вектор-06Ц.
	my @array_PC_R; # Красный.
	my @array_PC_G; # Зелёный.
	my @array_PC_B; # Синий.

	# Массивы цветов Вектор-06Ц.
	@array_PC_R = (0, 36, 72, 108, 144, 180, 216, 255);
	@array_PC_G = (0, 36, 72, 108, 144, 180, 216, 255);
	@array_PC_B = (0, 85, 170, 255);


		# Получить палитру.
		$temp = $_[0];
		# В двоичную систему.
		$temp = sprintf('%b', $temp);
		# Дополнить нулями слева (если нужно).
		$temp = sprintf("%08d", $temp);

#		print $temp . ' - ';

		# 2 бита синий.
		$B_bit = substr($temp, 0, 2);
#		print $B_bit . ' ';

		# 3 бита зелёный.
		$G_bit = substr($temp, 2, 3);
#		print $G_bit . ' ';

		# 3 бита красный.
		$R_bit = substr($temp, 5, 3);
#		print $R_bit;

		# Blue.
		if ($B_bit eq '00')
			{
			$B = $array_PC_B[0];
			}
		if ($B_bit eq '01')
			{
			$B = $array_PC_B[1];
			}
		if ($B_bit eq '10')
			{
			$B = $array_PC_B[2];
			}
		if ($B_bit eq '11')
			{
			$B = $array_PC_B[3];
			}

		# Green.
		if ($G_bit eq '000')
			{
			$G = $array_PC_G[0];
			}
		if ($G_bit eq '001')
			{
			$G = $array_PC_G[1];
			}
		if ($G_bit eq '010')
			{
			$G = $array_PC_G[2];
			}
		if ($G_bit eq '011')
			{
			$G = $array_PC_G[3];
			}
		if ($G_bit eq '100')
			{
			$G = $array_PC_G[4];
			}
		if ($G_bit eq '101')
			{
			$G = $array_PC_G[5];
			}
		if ($G_bit eq '110')
			{
			$G = $array_PC_G[6];
			}
		if ($G_bit eq '111')
			{
			$G = $array_PC_G[7];
			}

		# Red.
		if ($R_bit eq '000')
			{
			$R = $array_PC_R[0];
			}
		if ($R_bit eq '001')
			{
			$R = $array_PC_R[1];
			}
		if ($R_bit eq '010')
			{
			$R = $array_PC_R[2];
			}
		if ($R_bit eq '011')
			{
			$R = $array_PC_R[3];
			}
		if ($R_bit eq '100')
			{
			$R = $array_PC_R[4];
			}
		if ($R_bit eq '101')
			{
			$R = $array_PC_R[5];
			}
		if ($R_bit eq '110')
			{
			$R = $array_PC_R[6];
			}
		if ($R_bit eq '111')
			{
			$R = $array_PC_R[7];
			}

#		$RGB_hex = sprintf("%02x", $R) . sprintf("%02x", $G) . sprintf("%02x", $B);
		$BGR_hex = sprintf("%02x", $B) . sprintf("%02x", $G) . sprintf("%02x", $R);

#		print ' - ';
#		print $RGB_hex;

		return $BGR_hex;
}
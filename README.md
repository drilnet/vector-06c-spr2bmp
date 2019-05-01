# hobby
### Вектор-06Ц. Конвертер графических файлов SPR в BMP.

Лицензия на программу и скрипт: **GNU GPL V3**.

![](https://github.com/drilnet/vector-06c-spr2bmp/blob/master/UA.png)

**SPR** - графический формат файлов [Вектор'а-06Ц](https://ru.wikipedia.org/wiki/Вектор-06Ц) ([UKR](https://uk.wikipedia.org/wiki/Вектор-06Ц)).
<br>
**BMP** - графический формат файлов **Windows**.

Что содержит репозиторий.
    
    Каталог: SRC C - FreeBSD, Linux - Исходники на Си.
    Каталог: SRC C - Windows        - Исходники на Си.

Отличие каталогов - кодировка **UTF8** и **CP866**!

Сложно ли их скомпилировать исходники? Компиляция в двух действиях!
<br>
Смотрите каталоги [SRC C - FreeBSD, Linux](https://github.com/drilnet/vector-06c-spr2bmp/tree/master/SRC%20C%20-%20FreeBSD%2C%20Linux) и [SRC C - Windows](https://github.com/drilnet/vector-06c-spr2bmp/tree/master/SRC%20C%20-%20Windows)
(внутри есть **описание**).

**SPR-файлы**:

    Файл: Graphics Files Vector-06C (SPR).1.7z
    Архив SPR-файлов (разные, внутри есть и BMP-файлы).

    Файл: Graphics Files Vector-06C (SPR).2.7z
    Архив SPR-файлов (разные, внутри есть и BMP-файлы).

    Файл: Graphics Files Vector-06C (SPR).3.7z
    Архив SPR-файлов (доисторические животные, внутри есть и BMP-файлы).

    Файл: Graphics Files Vector-06C (SPR).4.7z
    Архив SPR-файлов (карикатуры на Харьковских программистов,
    ХХ век, 90-е года, внутри есть BMP-файлы).

    Примечание.
    Внутри этих архивов есть программы для просмотра SPR-файлов на Вектор'е-06Ц,
    это программа VSPR.COM и программа DEMO-SPR.COM (для этих программ необходима ДОС Т-34).

**Инфо по SPR** (эта информация есть в [Wiki](https://github.com/drilnet/vector-06c-spr2bmp/wiki)):

    Файл: Info SPR.7z
    Как устроен SPR-файл, плюс программа распаковщика на
    ассемблере для Вектор'а-06Ц.

**Испоняемые файлы**:

    spr2bmp     - Исполняемый файл для FreeBSD (SPR-файл в BMP-файл).
    spr2bmp.exe - Исполняемый файл для Windows (SPR-файл в BMP-файл).
    spr2bmp.pl  - Скрипт на Perl (SPR-файл в BMP-файл). Этот скрипт ещё умеет "выдирать" изображения из исходников.

**Скриншоты работы программы spr2bmp**:

![](https://github.com/drilnet/vector-06c-spr2bmp/blob/master/spr2bmp_Screenshot_1.png)

![](https://github.com/drilnet/vector-06c-spr2bmp/blob/master/spr2bmp_Screenshot_2.png)

**Результат работы программы spr2bmp**:

![](https://github.com/drilnet/vector-06c-spr2bmp/blob/master/SRC%20C%20-%20FreeBSD%2C%20Linux/Test/TEST2.bmp)

Приведенное изображение выше: **Sorayama Hayme**.

* [Вот ещё (1).](https://github.com/drilnet/vector-06c-spr2bmp/blob/master/SRC%20C%20-%20FreeBSD%2C%20Linux/Test/TEST3.bmp)
* [Вот ещё (2).](https://github.com/drilnet/vector-06c-spr2bmp/blob/master/SRC%20C%20-%20FreeBSD%2C%20Linux/Test/TEST4.bmp)

**Примечание**.
<br>
Как попадали такие изображения как **Sorayama Hayme** (и др.) в [Вектор-06Ц](https://ru.wikipedia.org/wiki/Вектор-06Ц) ([UKR](https://uk.wikipedia.org/wiki/Вектор-06Ц))?
<br>
Была написана утилита ([VPCX.COM](https://drilnet.github.io/downloads/vector-06c/system-disk-1-fls/VPCX.COM), автор **Терентьев С.В.**) для просмотра [PCX](https://ru.wikipedia.org/wiki/PCX) ([UKR](https://uk.wikipedia.org/wiki/PCX)) файлов и конвертация их в формат **SPR**.

<hr>

Различные сообщества ([ZX Spectrum](https://ru.wikipedia.org/wiki/ZX_Spectrum) ([UKR](https://uk.wikipedia.org/wiki/ZX_Spectrum)), [Вектор-06Ц](https://ru.wikipedia.org/wiki/Вектор-06Ц) ([UKR](https://uk.wikipedia.org/wiki/Вектор-06Ц)), [Специалист](https://ru.wikipedia.org/wiki/Специалист_(компьютер)) и др.) живут [здесь](https://zx-pk.ru).

<hr>

Ниже привожу ещё гифку, которую сделал из **SPR** взятых с [Вектор'а-06Ц](https://ru.wikipedia.org/wiki/Вектор-06Ц) ([UKR](https://uk.wikipedia.org/wiki/Вектор-06Ц)).
<br>
Какрикатуры на Харьковских программистов (**XX век**, **90-е года**).
<br>
Совместное творчество **Третьяков А.Л.** и **Терентьев С.В.**

![](https://github.com/drilnet/vector-06c-spr2bmp/blob/master/Karikatury.gif)

Дополнительная информация (как устроен **SPR**-файл): [Wiki](https://github.com/drilnet/vector-06c-spr2bmp/wiki)

Украина. (C) Демидов С.В.

<hr>

**Дополнительные ссылки:**

* Вектор-06Ц в ПЛИС: [https://github.com/svofski/vector06cc](https://github.com/svofski/vector06cc)
* Картотека ПО для Вектор-06Ц: [http://sensi.org/scalar](http://sensi.org/scalar)
* Блог московского "макрушника" здесь: [http://macrobloger.com/vector-06c](http://macrobloger.com/vector-06c)
* CP/M для Windows: [http://www.sydneysmith.com/wordpress/cpm-programs/](http://www.sydneysmith.com/wordpress/cpm-programs/)
* Утилита для работы с образами CP/M дисков: [http://era-cg.su/steinblume/index.php?name=about&lang=ru](http://era-cg.su/steinblume/index.php?name=about&lang=ru)
* Информация по BDOS OC CP/M: [http://marinovsoft.narod.ru/korvet/bdos_doc.pdf](http://marinovsoft.narod.ru/korvet/bdos_doc.pdf)

<hr>

**Файловый архив Вектор'а-06Ц:**

* Системный диск Вектор'а-06Ц с МикроДОС Т-34 (Харьковский вариант).

    [Перейти в архив Вектор'а-06Ц](https://drilnet.github.io/downloads/vector-06c/)

<hr>

**Ещё репозитории автора:**

**Репозиторий:** [Blender 3D. Модель игральной кости (dice).](https://github.com/drilnet/blender3d-dice2)
<br>
**Репозиторий:** [Blender 3D. Модель мотора (motor).](https://github.com/drilnet/blender3d-motor)
<br>
**Репозиторий:** [Blender 3D. Символика Украины (Флаг, Герб).](https://github.com/drilnet/blender3d-ukrainian-symbols)
<br>
**Репозиторий:** [Скрипт, который подписывает цифровые фотографии.](https://github.com/drilnet/programming-perl-signature-images)
<br>
<br>
**Репозиторий:** [Вектор-06Ц. Ожившее кино.](https://github.com/drilnet/vector-06c-kino)
<br>
**Репозиторий:** [Вектор-06Ц. Конвертер графических файлов GRF в BMP.](https://github.com/drilnet/vector-06c-grf2bmp)
<br>
**Репозиторий:** [Скрипт, который показывает все цвета Вектор'а-06Ц.](https://github.com/drilnet/vector-06c-color256)
<br>
<br>
**Репозиторий:** [RLE кодирование своими руками (vRLE8).](https://github.com/drilnet/rle)

<hr>

**Полезные ссылки:**

[Правила оформления файла README.MD на GITHUB](https://github.com/OlgaVlasova/markdown-doc/blob/master/README.md#SpecialSymbol)
<br>
[Создаем свой сайт на Github](https://www.youtube.com/watch?v=05nLdIVfSRU)

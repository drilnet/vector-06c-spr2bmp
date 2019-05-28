![](https://github.com/drilnet/vector-06c-spr2bmp/blob/master/UA.png)

Написано на Си в [FreeBSD](https://www.freebsd.org/ru/)!

**Исходники**:

    spr2bmp.c        - Гланый файл.
    CodeConversion.c - Перекодировка цвета.
    GetRGB.c         - Цвета Вектор-06Ц через цвета PC компьютера.
    LoadSPR.c        - Загрузить SPR-файл в память.
    SaveBMP.c        - Сохранить BMP-файл на диск.
    UnpackingSPR.c   - Распаковать SPR-файл.

**Объектные файлы**:

    CodeConversion.o - Объектный файлй.
    GetRGB.o         - -/-
    LoadSPR.o        - -/-
    SaveBMP.o        - -/-
    spr2bmp.o        - -/-
    UnpackingSPR.o   - -/-

**Автоматизация процесса компиляции и сборки**:

    obj.sh      - Чтобы не делать объектные файлы руками.
    linking.sh  - Чтобы не делать линковку руками.

**Как скомпилировать исполняемый файл в FreeBSD или в Linux!**
 
       Действие 1. Создаём объектные файлы.
       $ gcc -c spr2bmp.c LoadSPR.c UnpackingSPR.c CodeConversion.c GetRGB.c SaveBMP.c

       Действие 2. Линковка объектных файлов.
       $ gcc spr2bmp.o LoadSPR.o UnpackingSPR.o CodeConversion.o GetRGB.o SaveBMP.o -o spr2bmp

       На выходе исполняемый файл spr2bmp

**Как скомпилировать исполняемый файл в FreeBSD или в Linux для Windows!**

       Действие 1. Создаём объектные файлы.
       $ mingw32-gcc -c spr2bmp.c LoadSPR.c UnpackingSPR.c CodeConversion.c GetRGB.c SaveBMP.c

       Действие 2. Линковка объектных файлов.
       $ mingw32-gcc spr2bmp.o LoadSPR.o UnpackingSPR.o CodeConversion.o GetRGB.o SaveBMP.o -o spr2bmp.exe

       На выходе исполняемый файл spr2bmp.exe

**Perl**:    
    
    ---
    | Каталог Perl - для получения заголовка BMP-файла.
    ---

    Примечание.
    Каталог Perl в 'SRC - Windows' - отсутствует.

**Тестовые изображения**:

    ---
    | Каталог Test
    ---

[Ukraine](https://en.wikipedia.org/wiki/Ukraine) (Украина). (**C**) Демидов С.В.

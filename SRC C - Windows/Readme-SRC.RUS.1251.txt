
    �������� �� �� � FreeBSD!

    spr2bmp.c        - ������ ����.
    CodeConversion.c - ������������� �����.
    GetRGB.c         - ����� ������-06� ����� ����� PC ����������.
    LoadSPR.c        - ��������� SPR-���� � ������.
    SaveBMP.c        - ��������� BMP-���� �� ����.
    UnpackingSPR.c   - ����������� SPR-����.

    CodeConversion.o - ��������� ����.
    GetRGB.o         - -/-
    LoadSPR.o        - -/-
    SaveBMP.o        - -/-
    spr2bmp.o        - -/-
    UnpackingSPR.o   - -/-

    obj.sh      - ����� �� ������ ��������� ����� ������.
    linking.sh  - ����� �� ������ �������� ������.

    Readme-SRC.RUS.1251.txt - ��� �������� � ��������� cp1251 (Windows).
    Readme-SRC.RUS.UTF8.txt - ��� �������� � ��������� UTF-8 (FreeBSD, Linux).

    ��� �������������� ����������� ���� � FreeBSD ��� � Linux!
 
       �������� 1. ������ ��������� �����.
       $ gcc -c spr2bmp.c LoadSPR.c UnpackingSPR.c CodeConversion.c GetRGB.c SaveBMP.c

       �������� 2. �������� ��������� ������.
       $ gcc spr2bmp.o LoadSPR.o UnpackingSPR.o CodeConversion.o GetRGB.o SaveBMP.o -o spr2bmp

       �� ������ ����������� ���� spr2bmp

    ��� �������������� ����������� ���� � FreeBSD ��� � Linux ��� Windows!

       �������� 1. ������ ��������� �����.
       $ mingw32-gcc -c spr2bmp.c LoadSPR.c UnpackingSPR.c CodeConversion.c GetRGB.c SaveBMP.c

       �������� 2. �������� ��������� ������.
       $ mingw32-gcc spr2bmp.o LoadSPR.o UnpackingSPR.o CodeConversion.o GetRGB.o SaveBMP.o -o spr2bmp.exe

       �� ������ ����������� ���� spr2bmp.exe

    ---
    | ������� Perl - ��� ��������� ��������� BMP-�����.
    ---

    ����������.
    ������� Perl � 'SRC - Windows' - �����������.

    ---
    | ������� Test - �������� �����������.
    ---

    Ukraine. (C) ������� �.�.

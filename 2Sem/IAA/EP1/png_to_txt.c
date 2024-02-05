/*
 * IAA 2Sem2022 - Hermon Faria de Araujo
 * Código adaptado de:
 * Guillaume Cottenceau [http://zarb.org/~gc/html/libpng.html]
 * Jérôme Belleman [http://jeromebelleman.gitlab.io/posts/devops/libpng/#read-pixel-values]
 */

#include <stdio.h>

/* não esqueça de incluir o libpng header file */
#include <png.h>

/* Declarações de variáveis */
int lin, col;           /* linha e coluna da imagem (matriz de pixels) */
int width, height;      /* Largura e Altura da imagem (unidade pixel) */
int count_black_px = 0; /* contador de pixels pretos */
int count_white_px = 0; /* contador de pixels brancos */
int count_other_px = 0; /* contador de outras cores */

png_structp pngptr; /* struct libpng: contém dados dos pixels */
png_infop pnginfo;  /* struct libpng: contém dados sobre arquivo PNG */
png_bytepp rows;    /* struct libpng: array com linhas da matriz da imagem */

void read_png_file(char *file_name)
{
   /* testar se o arquivo aberto é uma imagem PNG */
   char header[8];
   FILE *fpng = fopen(file_name, "rb");
   if (!fpng)
      printf("[read_png_file] Arquivo %s não pode ser aberto para leitura", file_name);

   pngptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
   pnginfo = png_create_info_struct(pngptr);
   png_set_palette_to_rgb(pngptr); /* converte para RGB */

   /* Certifique-se de abrir o arquivo em modo binário */
   png_init_io(pngptr, fpng);

   /* PNG_TRANSFORM_IDENTITY constante indica não aplicar transformação, ler "AS IS" */
   png_read_png(pngptr, pnginfo, PNG_TRANSFORM_IDENTITY, NULL);

   fclose(fpng);
}

void write_txt_file(char *file_name)
{
   FILE *ftxt = fopen(file_name, "w");

   /* Obter largura e altura da imagem */
   width = png_get_image_width(pngptr, pnginfo);
   height = png_get_image_height(pngptr, pnginfo);

   printf("(Altura,Largura)= %i x %i pixels\n", height, width);

   rows = png_get_rows(pngptr, pnginfo);

   for (lin = 0; lin < height; lin++)
   {
      for (col = 0; col < width * 3; col += 3)
      {
         // printf("pixel[%i,%i] RGB(%d,%d,%d)\n", lin, col / 3, rows[lin][col], rows[lin][col + 1], rows[lin][col + 2]);
         if (rows[lin][col] == 255 && rows[lin][col + 1] == 255 && rows[lin][col + 2] == 255)
         {
            count_white_px += 1;
            fprintf(ftxt, "%i", 1); /* branco */
         }
         else if (rows[lin][col] == 0 && rows[lin][col + 1] == 0 && rows[lin][col + 2] == 0)
         {
            count_black_px += 1;
            fprintf(ftxt, "%i", 0); /* preto */
         }
         else
         {
            count_other_px += 1;
            fprintf(ftxt, "%i", 9); /* outro */
         }
      }
      fprintf(ftxt, "\n");
   }
   printf("Número de pixels brancos = %i\nNúmero de pixels pretos = %i\nNúmero de pixels outras cores = %i\n", count_white_px, count_black_px, count_other_px);
   if (count_other_px != 0)
   {
      printf("Imagem PNG não é PRETO e BRANCO\n");
   }
   fclose(ftxt);
}

int main(int argc, char **argv)
{
   if (argc != 3)
      printf("Uso: nome_do_programa.exe <arquivo_png> <arquivo_txt>");

   read_png_file(argv[1]);
   write_txt_file(argv[2]);

   return 0;
}

/**************************************************************
***************************************************************
*** 
***   plot.c
***
***   Jason Olejarz
***   2011-01-27
***
***   This file contains all graphics functions for ising3d.
***
***************************************************************
**************************************************************/

#include "includes.h"

void plot_rect(int *X_int, int nx, int ny, FILE *eps_plot)
{
	int x, y;

	fprintf(eps_plot, "%!PS-Adobe-3.0 EPSF-3.0\n");
	fprintf(eps_plot, "%%BoundingBox: 0 0 794 446\n");
	fprintf(eps_plot, "%%Pages: 0\n");
	fprintf(eps_plot, "%%Creator: LibreOffice 7.1\n");
	fprintf(eps_plot, "%%Title: none\n");
	fprintf(eps_plot, "%%CreationDate: none\n");
	fprintf(eps_plot, "%%LanguageLevel: 2\n");
	fprintf(eps_plot, "%%EndComments\n");
	fprintf(eps_plot, "%%BeginProlog\n");
	fprintf(eps_plot, "%%BeginResource: procset SDRes-Prolog 1.0 0\n");
	fprintf(eps_plot, "/b4_inc_state save def\n");
	fprintf(eps_plot, "/dict_count countdictstack def\n");
	fprintf(eps_plot, "/op_count count 1 sub def\n");
	fprintf(eps_plot, "userdict begin\n");
	fprintf(eps_plot, "0 setgray 0 setlinecap 1 setlinewidth 0 setlinejoin 10 setmiterlimit[] 0 setdash newpath\n");
	fprintf(eps_plot, "/languagelevel where {pop languagelevel 1 ne {false setstrokeadjust false setoverprint} if} if\n");
	fprintf(eps_plot, "/bdef {bind def} bind def\n");
	fprintf(eps_plot, "/c {setrgbcolor} bdef\n");
	fprintf(eps_plot, "/l {neg lineto} bdef\n");
	fprintf(eps_plot, "/rl {neg rlineto} bdef\n");
	fprintf(eps_plot, "/lc {setlinecap} bdef\n");
	fprintf(eps_plot, "/lj {setlinejoin} bdef\n");
	fprintf(eps_plot, "/lw {setlinewidth} bdef\n");
	fprintf(eps_plot, "/ml {setmiterlimit} bdef\n");
	fprintf(eps_plot, "/ld {setdash} bdef\n");
	fprintf(eps_plot, "/m {neg moveto} bdef\n");
	fprintf(eps_plot, "/ct {6 2 roll neg 6 2 roll neg 6 2 roll neg curveto} bdef\n");
	fprintf(eps_plot, "/r {rotate} bdef\n");
	fprintf(eps_plot, "/t {neg translate} bdef\n");
	fprintf(eps_plot, "/s {scale} bdef\n");
	fprintf(eps_plot, "/sw {show} bdef\n");
	fprintf(eps_plot, "/gs {gsave} bdef\n");
	fprintf(eps_plot, "/gr {grestore} bdef\n");
	fprintf(eps_plot, "/f {findfont dup length dict begin\n");
	fprintf(eps_plot, "{1 index /FID ne {def} {pop pop} ifelse} forall /Encoding ISOLatin1Encoding def\n");
	fprintf(eps_plot, "currentdict end /NFont exch definefont pop /NFont findfont} bdef\n");
	fprintf(eps_plot, "/p {closepath} bdef\n");
	fprintf(eps_plot, "/sf {scalefont setfont} bdef\n");
	fprintf(eps_plot, "/ef {eofill}bdef\n");
	fprintf(eps_plot, "/pc {closepath stroke}bdef\n");
	fprintf(eps_plot, "/ps {stroke}bdef\n");
	fprintf(eps_plot, "/pum {matrix currentmatrix}bdef\n");
	fprintf(eps_plot, "/pom {setmatrix}bdef\n");
	fprintf(eps_plot, "/bs {/aString exch def /nXOfs exch def /nWidth exch def currentpoint nXOfs 0 rmoveto pum nWidth aString stringwidth pop div 1 scale aString show pom moveto} bdef\n");
	fprintf(eps_plot, "%%EndResource\n");
	fprintf(eps_plot, "%%EndProlog\n");
	fprintf(eps_plot, "%%BeginSetup\n");
	fprintf(eps_plot, "%%EndSetup\n");
	fprintf(eps_plot, "%%Page: 1 1\n");
	fprintf(eps_plot, "%%BeginPageSetup\n");
	fprintf(eps_plot, "%%EndPageSetup\n");
	fprintf(eps_plot, "pum\n");
	fprintf(eps_plot, "0.02835 0.02831 s\n");
	fprintf(eps_plot, "0 -15750 t\n");
	fprintf(eps_plot, "/tm matrix currentmatrix def\n");
	fprintf(eps_plot, "gs\n");
	fprintf(eps_plot, "0 0 m 27999 0 l 27999 15749 l 0 15749 l 0 0 l eoclip newpath\n");
	fprintf(eps_plot, "gs\n");
	fprintf(eps_plot, "0 0 m 27999 0 l 27999 15749 l 0 15749 l 0 0 l eoclip newpath\n");
	for (y=0; y<ny; y++)
	{
		for (x=0; x<nx; x++)
		{
			fprintf(eps_plot, "gs\n");

			if (*(X_int+7*(nx*y+x)+0)==0 &&
			    *(X_int+7*(nx*y+x)+1)==0 &&
			    *(X_int+7*(nx*y+x)+2)==0 &&
			    *(X_int+7*(nx*y+x)+3)==0 &&
			    *(X_int+7*(nx*y+x)+4)==0 &&
			    *(X_int+7*(nx*y+x)+5)==0 &&
			    *(X_int+7*(nx*y+x)+6)==0) fprintf(eps_plot, "1 0 0 c ");
			else if (*(X_int+7*(nx*y+x)+1)>0 ||
				 *(X_int+7*(nx*y+x)+3)>0 ||
				 *(X_int+7*(nx*y+x)+5)>0 ||
				 *(X_int+7*(nx*y+x)+6)>0) fprintf(eps_plot, "1 0.5 1 c ");
			else if (*(X_int+7*(nx*y+x)+0)>0 ||
				 *(X_int+7*(nx*y+x)+1)>0) fprintf(eps_plot, "0 0 1 c ");
			else fprintf(eps_plot, "0 1 0 c ");

			fprintf(eps_plot, "%d %d m  %d %d l  %d %d l  %d %d l  %d %d l\n", 50+100*x, 50+100*y, 50+100*x, 50+100*y, 50+100*x, 50+100*(y+1), 50+100*(x+1), 50+100*(y+1), 50+100*(x+1), 50+100*y);
			fprintf(eps_plot, "%d %d l  p ef\n", 50+100*x, 50+100*y);
			fprintf(eps_plot, "gr\n");

			fprintf(eps_plot, "gs\n10 lw 1 lj 0 0 0 c ");

			fprintf(eps_plot, "%d %d m  %d %d l  %d %d l  %d %d l  %d %d l\n", 50+100*x, 50+100*y, 50+100*x, 50+100*y, 50+100*x, 50+100*(y+1), 50+100*(x+1), 50+100*(y+1), 50+100*(x+1), 50+100*y);
			fprintf(eps_plot, "%d %d l  pc\n", 50+100*x, 50+100*y);
			fprintf(eps_plot, "gr\n");
		}
	}
	for (x=1; x<nx; x++)
	{
		fprintf(eps_plot, "gs\n");
		fprintf(eps_plot, "1 lw 1 lj 0 0 0 c %d 50 m  %d %d l  ps\n", 50+100*x, 50+100*x, 50+100*ny);
		fprintf(eps_plot, "gr\n");

		fprintf(eps_plot, "gs\n");
		fprintf(eps_plot, "1 lw 1 lj 0 0 0 c 50 %d m  %d %d l  ps\n", 50+100*x, 50+100*nx, 50+100*x);
		fprintf(eps_plot, "gr\n");
	}
	fprintf(eps_plot, "gs\n");
	fprintf(eps_plot, "0 0 0 c 0 0 m  0 0 l 0 %d l 50 %d l 50 0 l\n", 100+100*ny, 100+100*ny);
	fprintf(eps_plot, "0 0 l  p ef\n");
	fprintf(eps_plot, "gr\n");
	fprintf(eps_plot, "gs\n");
	fprintf(eps_plot, "0 0 0 c 0 0 m  0 0 l %d 0 l %d 50 l 0 50 l\n", 100+100*nx, 100+100*nx);
	fprintf(eps_plot, "0 0 l  p ef\n");
	fprintf(eps_plot, "gr\n");
	fprintf(eps_plot, "gs\n");
	fprintf(eps_plot, "0 0 0 c 0 0 m  %d 0 l %d %d l %d %d l %d 0 l\n", 50+100*nx, 50+100*nx, 100+100*ny, 100+100*nx, 100+100*ny, 100+100*nx);
	fprintf(eps_plot, "0 0 l  p ef\n");
	fprintf(eps_plot, "gr\n");
	fprintf(eps_plot, "gs\n");
	fprintf(eps_plot, "0 0 0 c 0 0 m  0 %d l %d %d l %d %d l 0 %d l\n", 50+100*ny, 100+100*nx, 50+100*ny, 100+100*nx, 100+100*ny, 100+100*ny);
	fprintf(eps_plot, "0 0 l  p ef\n");
	fprintf(eps_plot, "gr\n");
	fprintf(eps_plot, "gr\n");
	fprintf(eps_plot, "gs\n");
	fprintf(eps_plot, "0 0 m 27999 0 l 27999 15749 l 0 15749 l 0 0 l eoclip newpath\n");
	fprintf(eps_plot, "gr\n");
	fprintf(eps_plot, "gr\n");
	fprintf(eps_plot, "0 15750 t\n");
	fprintf(eps_plot, "pom\n");
	fprintf(eps_plot, "count op_count sub {pop} repeat countdictstack dict_count sub {end} repeat b4_inc_state restore\n");
	fprintf(eps_plot, "%%PageTrailer\n");
	fprintf(eps_plot, "%%Trailer\n");
	fprintf(eps_plot, "%%EOF\n");

	return;
}


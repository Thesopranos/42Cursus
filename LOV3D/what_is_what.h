# include <time.h>

typedef struct		s_display
{
	double			stepdraw;
	double			texpos;
	int				texxwall;
	int				texywall;
	int				indexdey;
	int				indexdex;
	double			onspritex;
	double			onspritey;
	double			invdet;
	double			transformx;
	double			transformy;
	int				spritescreenx;
	int				spriteheight;
	int				spritewidth;
	int				drawstarty;
	unsigned int	colorsprite;
	int				drawendy;
	int				drawstartx;
	int				drawendx;
	int				stripe;
	int				texx;
	int				texy;
	int				y;
	int				dsprite;
	int				spritenumber;
	int				cellx;
	int				celly;
	int				txfloor;
	int				tyfloor;
	int				txfloor2;
	int				tyfloor2;
	float			raydirx0;
	float			raydiry0;
	float			raydirx1;
	float			raydiry1;
	float			rowdistance;
	float			posz;
	int				initsuccess;
	int				maptofree;
	int				keyboard[100000]; // basılan tuşların değerini 1 yapar, yukarıda define edilen tuşlar
	int				index;
	int				bpp;
	int				bpp2[11];
	int				s_line;
	int				s_line2[11];
	int				ed2[11];
	int				ed;
	int				startline; // sol kısımda çizilecek çizginin
	int				endline;
	int				side;
	double			*zbuffer;
	char			**map;
	char			*pxl;
	char			*spritenum;
	char			*north; // kuzey yönündeki duvarların texture dosyasının yolunu tutar
	char			*south; // güney yönündeki duvarların texture dosyasının yolunu tutar
	char			*west; // batı yönündeki duvarların texture dosyasının yolunu tutar
	char			*east; // doğu yönündeki duvarların texture dosyasının yolunu tutar
	char			*spritepwd;
	void			*mlx_ptr; // mlx adresini tutar
	void			*mlx_win; // pencere adresini tutar
	void			*img;
	int				r1; // map içerisinden okunan ekran genişliği
	int				errorbool;
	int				spritecounted;
	int				r2; // map içerisinden okunan ekran yüksekliği
	int				fd;
	double			stepx; // x ekseninde bir adımın değeri (-1 yada 1)
	double			stepy; // y ekseninde bir adımın değeri (-1 yada 1)
	double			camerax;
	double			rotspeed; // dönme hızı
	double			dirx;
	double			wallx;
	double			diry;
	double			planex;
	double			planey;
	int				lineheight;
	double			perwalldist;
	double			pspeed; // hareket hızı
	int				mapx;
	int				bmp;
	int				mapy;
	int				*spritex;
	int				*spritey;
	double			*spritedist;
	int				numberofplayer;
	int				widthtext[11];
	int				heighttext[11];
	void			*text_no; // kuzey yönündeki duvarların texture dosyasının mlx adresini tutar
	void			*text_so; // güney yönündeki duvarların texture dosyasının mlx adresini tutar
	char			*filename; // harita dosyasının yolunu tutar
	int				mapboleen;
	void			*text_we; // batı yönündeki duvarların texture dosyasının mlx adresini tutar
	void			*text_ea; // doğu yönündeki duvarların texture dosyasının mlx adresini tutar
	void			*sprite;
	int				textnum;
	char			*ptr[11];
	clock_t			last_frame;
	clock_t			next_frame;
	unsigned int	color;
	unsigned int	rgbfloor[3]; // zemin rengini tutan array, r, g, b
	unsigned int	rgbceiling[3]; // tavan rengini tutan array, r, g, b
	unsigned int	rgbtemp[3];
	t_ray			player; // player.x ve player.y ile playerın konumunu tutar
	t_ray			d;
	t_ray			deltadist;
	t_ray			sidedist;
	t_xy1			mapi;
}					t_display;

typedef struct		s_parse
{
	int				r1; // map içerisinden okunan ekran genişliği
	int				r2; // map içerisinden okunan ekran yüksekliği
	char			**map;
	t_xy1			sizemap; // okunan haritanın satır ve sütun uzunluğunu tutar
}					t_parse;

typedef struct		s_xy1
{
	int				x; // okunan haritanın satır uzunluğu, yani haritanın genişliği
	int				y; // okunan haritanın sütun uzunluğu, yani haritanın yüksekliği
}					t_xy1;

typedef struct		s_ray
{
	double			x;
	double			y;
}					t_ray;

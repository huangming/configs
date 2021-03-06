typedef enum {
  CHECK_AA,
  CHECK_BASE,
  CHECK_BLACK,
  CHECK_DARK,
  CHECK_LIGHT,
  CHECK_MID,
  CHECK_TEXT,
  RADIO_BASE,
  RADIO_BLACK,
  RADIO_DARK,
  RADIO_LIGHT,
  RADIO_MID,
  RADIO_TEXT
} Part;

#define PART_SIZE 13

static unsigned char check_aa_bits[] = {
 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x04,0x00,0x00,0x00,0x00,0x58,0x00,0xa0,
 0x00,0x10,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
static unsigned char check_base_bits[] = {
 0x00,0x00,0x00,0x00,0xfc,0x07,0xfc,0x07,0xfc,0x07,0xfc,0x07,0xfc,0x07,0xfc,
 0x07,0xfc,0x07,0xfc,0x07,0xfc,0x07,0x00,0x00,0x00,0x00};
static unsigned char check_black_bits[] = {
 0x00,0x00,0xfe,0x0f,0x02,0x00,0x02,0x00,0x02,0x00,0x02,0x00,0x02,0x00,0x02,
 0x00,0x02,0x00,0x02,0x00,0x02,0x00,0x02,0x00,0x00,0x00};
static unsigned char check_dark_bits[] = {
 0xff,0x1f,0x01,0x00,0x01,0x00,0x01,0x00,0x01,0x00,0x01,0x00,0x01,0x00,0x01,
 0x00,0x01,0x00,0x01,0x00,0x01,0x00,0x01,0x00,0x01,0x00};
static unsigned char check_light_bits[] = {
 0x00,0x00,0x00,0x10,0x00,0x10,0x00,0x10,0x00,0x10,0x00,0x10,0x00,0x10,0x00,
 0x10,0x00,0x10,0x00,0x10,0x00,0x10,0x00,0x10,0xfe,0x1f};
static unsigned char check_mid_bits[] = {
 0x00,0x00,0x00,0x00,0x00,0x08,0x00,0x08,0x00,0x08,0x00,0x08,0x00,0x08,0x00,
 0x08,0x00,0x08,0x00,0x08,0x00,0x08,0xfc,0x0f,0x00,0x00};
static unsigned char check_text_bits[] = {
 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x02,0x00,0x03,0x80,0x01,0x80,0x00,0xd8,
 0x00,0x60,0x00,0x40,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
static unsigned char radio_base_bits[] = {
 0x00,0x00,0x00,0x00,0xf0,0x01,0xf8,0x03,0xfc,0x07,0xfc,0x07,0xfc,0x07,0xfc,
 0x07,0xfc,0x07,0xf8,0x03,0xf0,0x01,0x00,0x00,0x00,0x00};
static unsigned char radio_black_bits[] = {
 0x00,0x00,0xf0,0x01,0x08,0x02,0x04,0x00,0x02,0x00,0x02,0x00,0x02,0x00,0x02,
 0x00,0x02,0x00,0x04,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
static unsigned char radio_dark_bits[] = {
 0xf0,0x01,0x08,0x02,0x04,0x04,0x02,0x04,0x01,0x00,0x01,0x00,0x01,0x00,0x01,
 0x00,0x01,0x00,0x02,0x00,0x0c,0x00,0x00,0x00,0x00,0x00};
static unsigned char radio_light_bits[] = {
 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x08,0x00,0x10,0x00,0x10,0x00,0x10,0x00,
 0x10,0x00,0x10,0x00,0x08,0x00,0x04,0x08,0x02,0xf0,0x01};
static unsigned char radio_mid_bits[] = {
 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x08,0x00,0x08,0x00,0x08,0x00,
 0x08,0x00,0x08,0x00,0x04,0x00,0x02,0xf0,0x01,0x00,0x00};
static unsigned char radio_text_bits[] = {
 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xe0,0x00,0xf0,0x01,0xf0,0x01,0xf0,
 0x01,0xe0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};

static struct {
  char      *bits;
  GdkBitmap *bmap;
} parts[] = {
  { check_aa_bits, NULL },
  { check_base_bits, NULL },
  { check_black_bits, NULL },
  { check_dark_bits, NULL },
  { check_light_bits, NULL },
  { check_mid_bits, NULL },
  { check_text_bits, NULL },
  { radio_base_bits, NULL },
  { radio_black_bits, NULL },
  { radio_dark_bits, NULL },
  { radio_light_bits, NULL },
  { radio_mid_bits, NULL },
  { radio_text_bits, NULL }
};

static void
draw_part (GdkDrawable  *drawable,
		   GdkGC        *gc,
		   GdkRectangle *area,
		   gint          x,
		   gint          y,
		   Part          part)
{
  if (area)
    gdk_gc_set_clip_rectangle (gc, area);
  
  if (!parts[part].bmap)
      parts[part].bmap = gdk_bitmap_create_from_data (drawable,
						      parts[part].bits,
						      PART_SIZE, PART_SIZE);

  gdk_gc_set_ts_origin (gc, x, y);
  gdk_gc_set_stipple (gc, parts[part].bmap);
  gdk_gc_set_fill (gc, GDK_STIPPLED);

  gdk_draw_rectangle (drawable, gc, TRUE, x, y, PART_SIZE, PART_SIZE);

  gdk_gc_set_fill (gc, GDK_SOLID);

  if (area)
    gdk_gc_set_clip_rectangle (gc, NULL);
}

static void
raleigh_draw_check(GtkStyle      *style,
		   GdkWindow     *window,
		   GtkStateType   state,
		   GtkShadowType  shadow,
		   GdkRectangle  *area,
		   GtkWidget     *widget,
		   gchar         *detail,
		   gint           x,
		   gint           y,
		   gint           width,
		   gint           height)
{
  x -= (1 + PART_SIZE - width) / 2;
  y -= (1 + PART_SIZE - height) / 2;
      
  if (strcmp (detail, "check") == 0)	/* Menu item */
    {
      if (shadow == GTK_SHADOW_IN)
	{
	  draw_part (window, style->black_gc, area, x, y, CHECK_TEXT);
	  draw_part (window, style->dark_gc[state], area, x, y, CHECK_AA);
	}
    }
  else
    {
      draw_part (window, style->black_gc, area, x, y, CHECK_BLACK);
      draw_part (window, style->dark_gc[state], area, x, y, CHECK_DARK);
      draw_part (window, style->mid_gc[state], area, x, y, CHECK_MID);
      draw_part (window, style->light_gc[state], area, x, y, CHECK_LIGHT);
      draw_part (window, style->base_gc[state], area, x, y, CHECK_BASE);
      
      if (shadow == GTK_SHADOW_IN)
	{
	  draw_part (window, style->text_gc[state], area, x, y, CHECK_TEXT);
	  /*draw_part (window, engine_data->aa_gc[state], area, x, y, CHECK_AA); */
	}
    }
}

static void
raleigh_draw_option(GtkStyle      *style,
		    GdkWindow     *window,
		    GtkStateType   state,
		    GtkShadowType  shadow,
		    GdkRectangle  *area,
		    GtkWidget     *widget,
		    gchar         *detail,
		    gint           x,
		    gint           y,
		    gint           width,
		    gint           height)
{
  x -= (1 + PART_SIZE - width) / 2;
  y -= (1 + PART_SIZE - height) / 2;
      
  if (strcmp (detail, "option") == 0)	/* Menu item */
    {
      if (shadow == GTK_SHADOW_IN)
	draw_part (window, style->black_gc, area, x, y, RADIO_TEXT);
    }
  else
    {
      draw_part (window, style->black_gc, area, x, y, RADIO_BLACK);
      draw_part (window, style->dark_gc[state], area, x, y, RADIO_DARK);
      draw_part (window, style->mid_gc[state], area, x, y, RADIO_MID);
      draw_part (window, style->light_gc[state], area, x, y, RADIO_LIGHT);
      draw_part (window, style->base_gc[state], area, x, y, RADIO_BASE);
      
      if (shadow == GTK_SHADOW_IN)
	draw_part (window, style->text_gc[state], area, x, y, RADIO_TEXT);
    }
}

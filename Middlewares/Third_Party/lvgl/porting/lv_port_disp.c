#include "lv_port_disp.h"
#include "main.h"

#define LCD_SCREEN_WIDTH                  ((uint16_t)1024)
#define LCD_SCREEN_HEIGHT                 ((uint16_t)600)
#define SDRAM_DEVICE_ADDR                 ((uint32_t)0xD0000000)

#define DISP_BUF_LINES                    30

/* Extern handles from main.c */
extern DMA2D_HandleTypeDef hdma2d;

/* Declare two draw buffers in internal SRAM (30 lines of RGB565) */
static __attribute__((aligned(32))) lv_color_t lv_disp_buf1[LCD_SCREEN_WIDTH * DISP_BUF_LINES];
static __attribute__((aligned(32))) lv_color_t lv_disp_buf2[LCD_SCREEN_WIDTH * DISP_BUF_LINES];

static lv_disp_drv_t disp_drv;

/* Private callback prototypes */
static void disp_flush(lv_disp_drv_t * disp_drv, const lv_area_t * area, lv_color_t * color_p);
static void disp_flush_complete(DMA2D_HandleTypeDef *hdma2d);

void lv_port_disp_init(void)
{
  static lv_disp_draw_buf_t draw_buf_dsc;

  /* Initialize draw buffer structure */
  lv_disp_draw_buf_init(&draw_buf_dsc, lv_disp_buf1, lv_disp_buf2, LCD_SCREEN_WIDTH * DISP_BUF_LINES);

  /* Initialize display driver structure */
  lv_disp_drv_init(&disp_drv);

  /* Set display resolution */
  disp_drv.hor_res = LCD_SCREEN_WIDTH;
  disp_drv.ver_res = LCD_SCREEN_HEIGHT;

  /* Register flush callback */
  disp_drv.flush_cb = disp_flush;

  /* Link the draw buffer */
  disp_drv.draw_buf = &draw_buf_dsc;

  /* Register the driver in LVGL */
  lv_disp_drv_register(&disp_drv);

  /* Interrupt callback for DMA2D transfer completion */
  hdma2d.XferCpltCallback = disp_flush_complete;
}

/**
  * @brief LVGL flush callback. Renders area from SRAM into SDRAM using hardware DMA2D
  */
static void disp_flush(lv_disp_drv_t * disp_drv_p, const lv_area_t * area, lv_color_t * color_p)
{
  (void)disp_drv_p;
  uint32_t width = area->x2 - area->x1 + 1;
  uint32_t height = area->y2 - area->y1 + 1;
  
  /* Target address in external SDRAM framebuffer */
  uint32_t *fb = (uint32_t *)SDRAM_DEVICE_ADDR;
  uint32_t *dst_addr = fb + (area->y1 * LCD_SCREEN_WIDTH) + area->x1;

  uint32_t srcOffset = 0;
  uint32_t dstOffset = LCD_SCREEN_WIDTH - width;

  /* Configure DMA2D registers directly for ultra-fast execution */
  DMA2D->CR = 0x01U << DMA2D_CR_MODE_Pos; /* M2M with PFC (RGB565 -> ARGB8888) */
  DMA2D->FGPFCCR = DMA2D_INPUT_RGB565;
  DMA2D->FGMAR = (uint32_t)color_p;
  DMA2D->FGOR = srcOffset;
  DMA2D->OPFCCR = DMA2D_OUTPUT_ARGB8888;
  DMA2D->OMAR = (uint32_t)dst_addr;
  DMA2D->OOR = dstOffset;
  DMA2D->NLR = (width << DMA2D_NLR_PL_Pos) | (height << DMA2D_NLR_NL_Pos);
  DMA2D->IFCR = 0x3FU;
  DMA2D->CR |= DMA2D_CR_TCIE; // Enable transfer complete interrupt
  DMA2D->CR |= DMA2D_CR_START;
}

static void disp_flush_complete(DMA2D_HandleTypeDef *hdma2d_p)
{
  (void)hdma2d_p;
  lv_disp_flush_ready(&disp_drv);
}

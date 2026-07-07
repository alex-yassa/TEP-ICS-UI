# Display and UI Hardware Specifications

This document outlines the hardware, memory mapping, and timing specifications of the 7.0" Riverdi display panel integrated with the Central EMS system.

---

## 🖥️ Display Specifications

* **Panel Model**: Riverdi 7.0" IPS TFT LCD with DSI interface (built around the Riverdi STM32H7 board template)
* **Resolution**: 1024 x 600 pixels (Landscape)
* **Backlight Control**: PWM-controlled via Timer 15 Channel 1 (`TIM15_CH1`) on the Cortex-M7 core
* **Input Device**: 2x5 Matrix Keypad scanned by Cortex-M4 (touchscreen is disabled)

---

## 🎨 Color Depth & Pixel Formats

To maximize rendering performance while keeping memory footprint low, the system uses a multi-tier color depth strategy:

| Component | Format | Bits Per Pixel | Description |
|---|---|---|---|
| **LVGL Render Buffer** | RGB565 | 16-bit | Drawn by Cortex-M4 into internal SRAM buffers `buf_1` & `buf_2`. |
| **LTDC Framebuffer** | ARGB8888 | 32-bit | Positioned at SDRAM base `0xD0000000` (1024x600 size). |
| **DMA2D Upscaling** | PFC (RGB565 ➔ ARGB8888) | On-the-fly | The DMA2D controller performs pixel format conversion during memory-to-memory copy. |
| **DSI Host Output** | RGB888 | 24-bit | The DSI host retrieves the 32-bit LTDC output and transmits it as 24-bit RGB video packets. |

---

## ⏱️ LTDC & DSI Video Timings

Timings are configured in the Cortex-M7 initialization stack. The display operates in **DSI Video Burst Mode**.

### 1. Active & Blanking Timings
* **Horizontal Timings**:
  * **HACT (Horizontal Active)**: 1024 pixels
  * **HSYNC (Horizontal Sync)**: 70 pixels
  * **HBP (Horizontal Back Porch)**: 160 pixels
  * **HFP (Horizontal Front Porch)**: 160 pixels
  * **H_Total**: 1414 pixels

* **Vertical Timings**:
  * **VACT (Vertical Active)**: 600 lines
  * **VSYNC (Vertical Sync)**: 10 lines
  * **VBP (Vertical Back Porch)**: 23 lines
  * **VFP (Vertical Front Porch)**: 12 lines
  * **V_Total**: 645 lines

### 2. Frequency & Refresh Rate (FPS)
* **Display Pixel Clock (`LcdClock`)**: 41.666 MHz
* **DSI Lane Byte Clock (`laneByteClk_kHz`)**: 62.0 MHz (running over 2 data lanes)
* **Calculated Frame Rate (Refresh Rate)**: 
  $$\text{FPS} = \frac{\text{Pixel Clock}}{H_{\text{Total}} \times V_{\text{Total}}} = \frac{41,666,000}{1414 \times 645} \approx 45.68\text{ Hz}$$

---

## 🧠 Memory Map & DMA2D Integration

```
 +----------------------------------+
 |  CM4 Internal SRAM               |
 |  (buf_1 & buf_2: 1024x15 RGB565) |
 +----------------------------------+
                 |
                 | DMA2D Transfer
                 | (with PFC: RGB565 -> ARGB8888)
                 v
 +----------------------------------+
 |  External SDRAM (0xD0000000)     |
 |  (LTDC Framebuffer ARGB8888)     |
 +----------------------------------+
                 |
                 | LTDC Controller Read
                 v
 +----------------------------------+
 |  DSI Host Controller             |
 |  (Packs output to 24-bit RGB888) |
 +----------------------------------+
                 |
                 v
       Display Panel (1024x600)
```

### Framebuffer Memory Addresses (SDRAM)
* **Base Framebuffer Address**: `0xD0000000` (FMC Bank 2 SDRAM)
* **Total Framebuffer Size**: $1024 \times 600 \times 4\text{ bytes (ARGB8888)} = 2.4576\text{ MB}$

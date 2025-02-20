# 项目介绍：基于 MSPM0 微控制器的信号发生器和示波器

## 项目概述
本项目是一个基于 **Texas Instruments MSPM0 微控制器** 的信号发生器和示波器系统。它结合了硬件和软件设计，能够实现以下功能：
1. **信号发生器（Signal Generator, SG）**：
   - 生成多种波形信号，包括正弦波、三角波和方波。
   - 支持频率、幅度和相位的调节。
   - 通过旋转编码器和按键进行参数设置。
2. **数字存储示波器（Digital Storage Oscilloscope, DSO）**：
   - 实时采集和显示模拟信号。
   - 支持触发功能，能够捕捉特定电压的信号。
   - 提供频率测量功能。

## 硬件设计
1. **核心控制器**：
   - 使用 **MSPM0 微控制器** 作为主控芯片，负责信号生成、数据采集和显示控制。
2. **显示模块**：
   - 使用 **OLED 显示屏** 实时显示波形和参数信息。
3. **输入设备**：
   - 使用 **旋转编码器** 和 **按键** 进行参数调节和模式切换。
4. **信号生成模块**：
   - 使用 **AD9833 波形发生器芯片** 生成高精度波形信号。
5. **信号采集模块**：
   - 使用 **ADC（模数转换器）** 采集模拟信号，并通过 DMA（直接内存访问）传输数据。

## 软件设计
1. **主程序**：
   - 初始化硬件模块（如 OLED、ADC、DMA 等）。
   - 通过主循环实现信号发生器和示波器的功能切换。
2. **信号发生器（SG）**：
   - 支持正弦波、三角波和方波的生成。
   - 通过旋转编码器调节频率、幅度和相位。
   - 使用 AD9833 芯片生成波形信号。
3. **示波器（DSO）**：
   - 实时采集模拟信号并通过 OLED 显示波形。
   - 支持触发功能，能够捕捉特定电压的信号。
   - 提供频率测量功能。
4. **用户界面**：
   - 通过 OLED 显示当前模式、波形参数和测量结果。
   - 使用旋转编码器和按键进行交互。

## 功能特点
1. **多功能集成**：
   - 集成了信号发生器和示波器功能，适用于多种应用场景。
2. **高精度信号生成**：
   - 使用 AD9833 芯片生成高精度波形信号，支持频率、幅度和相位的精确调节。
3. **实时信号采集**：
   - 通过 ADC 和 DMA 实现高速信号采集，确保波形显示的实时性。
4. **用户友好界面**：
   - 通过 OLED 显示屏和旋转编码器提供直观的操作界面。


## 技术栈
- **硬件**：MSPM0 微控制器、AD9833 波形发生器、OLED 显示屏、旋转编码器、ADC。
- **软件**：C 语言、TI 驱动程序库（DL）、DMA、中断处理。

## 项目结构
- **`main.c`**：主程序，负责硬件初始化和功能调度。
- **`DSO()`**：示波器功能实现。
- **`SG()`**：信号发生器功能实现。
- **`draw.c`**：OLED 显示相关函数。
- **`adc.c`**：ADC 数据采集相关函数。
- **`Encoder.c`**：旋转编码器读取相关函数。
- **`AD9833.c`**：AD9833 波形生成相关函数。


## 总结
本项目是一个功能强大的信号发生器和示波器系统，结合了 MSPM0 微控制器的高性能和 AD9833 芯片的高精度波形生成能力。通过 OLED 显示屏和旋转编码器，用户可以方便地进行参数设置和波形观察。该项目适用于教学、嵌入式开发和工业测试等多种场景，具有广泛的应用前景。

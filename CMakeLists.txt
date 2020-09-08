cmake_minimum_required(VERSION 3.17.3)

project(stm32f3-base)

enable_language(CXX C ASM)
set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_program(OPENOCD openocd)

set(PROJECT_FILES
  vendor/stm32f3xx_hal_driver/Src/stm32f3xx_ll_usb.c
  vendor/stm32f3xx_hal_driver/Src/stm32f3xx_hal_i2c.c
  vendor/stm32f3xx_hal_driver/Src/stm32f3xx_hal_i2c_ex.c
  vendor/stm32f3xx_hal_driver/Src/stm32f3xx_hal.c
  vendor/stm32f3xx_hal_driver/Src/stm32f3xx_hal_rcc.c
  vendor/stm32f3xx_hal_driver/Src/stm32f3xx_hal_rcc_ex.c
  vendor/stm32f3xx_hal_driver/Src/stm32f3xx_hal_gpio.c
  vendor/stm32f3xx_hal_driver/Src/stm32f3xx_hal_dma.c
  vendor/stm32f3xx_hal_driver/Src/stm32f3xx_hal_cortex.c
  vendor/stm32f3xx_hal_driver/Src/stm32f3xx_hal_pwr.c
  vendor/stm32f3xx_hal_driver/Src/stm32f3xx_hal_pwr_ex.c
  vendor/stm32f3xx_hal_driver/Src/stm32f3xx_hal_flash.c
  vendor/stm32f3xx_hal_driver/Src/stm32f3xx_hal_flash_ex.c
  vendor/stm32f3xx_hal_driver/Src/stm32f3xx_hal_exti.c
  vendor/stm32f3xx_hal_driver/Src/stm32f3xx_hal_spi.c
  vendor/stm32f3xx_hal_driver/Src/stm32f3xx_hal_spi_ex.c
  vendor/stm32f3xx_hal_driver/Src/stm32f3xx_hal_tim.c
  vendor/stm32f3xx_hal_driver/Src/stm32f3xx_hal_tim_ex.c
  vendor/stm32f3xx_hal_driver/Src/stm32f3xx_hal_pcd.c
  vendor/stm32f3xx_hal_driver/Src/stm32f3xx_hal_pcd_ex.c
  vendor/stm32f3xx_hal_driver/Src/stm32f3xx_hal_uart.c
  vendor/stm32f3xx_hal_driver/Src/stm32f3xx_hal_uart_ex.c
  vendor/stm32f3xx_hal_driver/Src/stm32f3xx_ll_usart.c
  vendor/stm32f3xx_hal_driver/Src/stm32f3xx_hal_usart.c
  vendor/stm32f3xx_hal_driver/Src/stm32f3xx_hal_usart_ex.c

  src/main.cpp
  src/system_stm32f3xx.c
  include/stm32f3xx_hal_conf.h

  startup_stm32f303xc.s
  )

set(EXECUTABLE ${PROJECT_NAME}.out)

add_executable(${EXECUTABLE} ${PROJECT_FILES})

target_compile_definitions(${EXECUTABLE} PRIVATE
  -DUSE_HAL_DRIVER
  -DSTM32F303xC
  )

target_include_directories(${EXECUTABLE} SYSTEM PRIVATE
  vendor/stm32f3xx_hal_driver/Inc
  vendor/cmsis_device_f3/Include
  vendor/cmsis_core/Include
  )

target_include_directories(${EXECUTABLE} PRIVATE
  drivers
  include
  src
  )

target_compile_options(${EXECUTABLE} PRIVATE
  -mcpu=cortex-m4
  -mthumb
  -mfpu=fpv4-sp-d16
  -mfloat-abi=hard

  -fdata-sections
  -ffunction-sections

   $<$<COMPILE_LANGUAGE:CXX>:@${CMAKE_SOURCE_DIR}/gcc-options-cxx.txt>

  -Wall

  $<$<CONFIG:Debug>:-Og>
  )

target_link_options(${EXECUTABLE} PRIVATE
  -T${CMAKE_SOURCE_DIR}/STM32F303VCTx_FLASH.ld
  -mcpu=cortex-m4
  -mthumb
  -mfpu=fpv4-sp-d16
  -mfloat-abi=hard
  -specs=nosys.specs
  -lc
  -lm
  -lnosys
  -Wl,-Map=${PROJECT_NAME}.map,--cref
  -Wl,--gc-sections
  )

# Print executable size
add_custom_command(TARGET ${EXECUTABLE}
  POST_BUILD
  COMMAND arm-none-eabi-size ${EXECUTABLE}
  )

# Create hex file
add_custom_command(TARGET ${EXECUTABLE}
  POST_BUILD
  COMMAND arm-none-eabi-objcopy -O ihex ${EXECUTABLE} ${PROJECT_NAME}.hex
  COMMAND arm-none-eabi-objcopy -O binary ${EXECUTABLE} ${PROJECT_NAME}.bin
  )

# Improve clean target
set_target_properties(${EXECUTABLE} PROPERTIES ADDITIONAL_CLEAN_FILES
  ${PROJECT_NAME}.hex
  ${PROJECT_NAME}.bin
  ${PROJECT_NAME}.map
  )

add_custom_target(upload COMMAND
  ${OPENOCD} -f interface/stlink-v2.cfg -f target/stm32f3x.cfg -c "init" -c "reset init" -c "halt" -c "flash write_image erase ${PROJECT_NAME}.hex" -c "verify_image ${PROJECT_NAME}.hex" -c "reset run" -c "shutdown"
  DEPENDS ${EXECUTABLE}
  )

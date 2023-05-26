# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "/home/etorob/zephyrproject/modules/hal/espressif/components/bootloader/subproject"
  "/home/etorob/Documentos/GitHub/DigitalElectronic/Zephyr/NTC3950F/build/esp-idf/build/bootloader"
  "/home/etorob/Documentos/GitHub/DigitalElectronic/Zephyr/NTC3950F/build/esp-idf"
  "/home/etorob/Documentos/GitHub/DigitalElectronic/Zephyr/NTC3950F/build/esp-idf/tmp"
  "/home/etorob/Documentos/GitHub/DigitalElectronic/Zephyr/NTC3950F/build/esp-idf/src/EspIdfBootloader-stamp"
  "/home/etorob/Documentos/GitHub/DigitalElectronic/Zephyr/NTC3950F/build/esp-idf/src"
  "/home/etorob/Documentos/GitHub/DigitalElectronic/Zephyr/NTC3950F/build/esp-idf/src/EspIdfBootloader-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "/home/etorob/Documentos/GitHub/DigitalElectronic/Zephyr/NTC3950F/build/esp-idf/src/EspIdfBootloader-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "/home/etorob/Documentos/GitHub/DigitalElectronic/Zephyr/NTC3950F/build/esp-idf/src/EspIdfBootloader-stamp${cfgdir}") # cfgdir has leading slash
endif()

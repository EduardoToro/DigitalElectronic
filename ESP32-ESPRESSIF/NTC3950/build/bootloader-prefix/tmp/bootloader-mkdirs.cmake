# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "/home/etorob/esp/esp-idf/components/bootloader/subproject"
  "/home/etorob/Documentos/GitHub/DigitalElectronic/ESP32-ESPRESSIF/NTC3950/build/bootloader"
  "/home/etorob/Documentos/GitHub/DigitalElectronic/ESP32-ESPRESSIF/NTC3950/build/bootloader-prefix"
  "/home/etorob/Documentos/GitHub/DigitalElectronic/ESP32-ESPRESSIF/NTC3950/build/bootloader-prefix/tmp"
  "/home/etorob/Documentos/GitHub/DigitalElectronic/ESP32-ESPRESSIF/NTC3950/build/bootloader-prefix/src/bootloader-stamp"
  "/home/etorob/Documentos/GitHub/DigitalElectronic/ESP32-ESPRESSIF/NTC3950/build/bootloader-prefix/src"
  "/home/etorob/Documentos/GitHub/DigitalElectronic/ESP32-ESPRESSIF/NTC3950/build/bootloader-prefix/src/bootloader-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "/home/etorob/Documentos/GitHub/DigitalElectronic/ESP32-ESPRESSIF/NTC3950/build/bootloader-prefix/src/bootloader-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "/home/etorob/Documentos/GitHub/DigitalElectronic/ESP32-ESPRESSIF/NTC3950/build/bootloader-prefix/src/bootloader-stamp${cfgdir}") # cfgdir has leading slash
endif()

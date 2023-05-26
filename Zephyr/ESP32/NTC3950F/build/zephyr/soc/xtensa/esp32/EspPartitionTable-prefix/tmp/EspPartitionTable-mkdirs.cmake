# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "/home/etorob/zephyrproject/modules/hal/espressif/components/partition_table"
  "/home/etorob/Documentos/GitHub/DigitalElectronic/Zephyr/NTC3950F/build/esp-idf/build"
  "/home/etorob/Documentos/GitHub/DigitalElectronic/Zephyr/NTC3950F/build/zephyr/soc/xtensa/esp32/EspPartitionTable-prefix"
  "/home/etorob/Documentos/GitHub/DigitalElectronic/Zephyr/NTC3950F/build/zephyr/soc/xtensa/esp32/EspPartitionTable-prefix/tmp"
  "/home/etorob/Documentos/GitHub/DigitalElectronic/Zephyr/NTC3950F/build/zephyr/soc/xtensa/esp32/EspPartitionTable-prefix/src/EspPartitionTable-stamp"
  "/home/etorob/Documentos/GitHub/DigitalElectronic/Zephyr/NTC3950F/build/zephyr/soc/xtensa/esp32/EspPartitionTable-prefix/src"
  "/home/etorob/Documentos/GitHub/DigitalElectronic/Zephyr/NTC3950F/build/zephyr/soc/xtensa/esp32/EspPartitionTable-prefix/src/EspPartitionTable-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "/home/etorob/Documentos/GitHub/DigitalElectronic/Zephyr/NTC3950F/build/zephyr/soc/xtensa/esp32/EspPartitionTable-prefix/src/EspPartitionTable-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "/home/etorob/Documentos/GitHub/DigitalElectronic/Zephyr/NTC3950F/build/zephyr/soc/xtensa/esp32/EspPartitionTable-prefix/src/EspPartitionTable-stamp${cfgdir}") # cfgdir has leading slash
endif()

# SPDX-License-Identifier: Apache-2.0

cmake_minimum_required(VERSION 3.20.0)

find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})
project(wifi)

# FILE(GLOB app_sources src/*.c)
target_sources(app PRIVATE ${app_sources})
target_sources_ifdef(CONFIG_WIFI app PRIVATE src/wifi.c)
target_sources(app PRIVATE src/dhcp.c)
target_sources(app PRIVATE src/tcp_client.c)
target_sources(app PRIVATE src/main.c)

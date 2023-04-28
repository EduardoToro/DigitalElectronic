/*
 * Copyright (c) 2020 Gerson Fernando Budke <nandojve@gmail.com>
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef WIFI_H
#define WIFI_H
/* #if defined(CONFIG_WIFI) */

#include <zephyr/logging/log.h>
/* LOG_MODULE_DECLARE(main, CONFIG_LOG_DEFAULT_LEVEL); */
/* LOG_MODULE_DECLARE(wifi, CONFIG_LOG_DEFAULT_LEVEL); */
/* LOG_MODULE_REGISTER(wifi, CONFIG_LOG_DEFAULT_LEVEL); */
/* LOG_MODULE_REGISTER(wifi); */


void wifi_connect(void);

/* #else */
/* #define wifi_connect(void) */
#endif

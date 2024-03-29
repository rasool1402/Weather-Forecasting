/*
 * Copyright 2018-2019 Uber Technologies, Inc.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *         http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
/** @file
 * @brief tests H3 distance function.
 *
 *  usage: `testH3Distance`
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "h3Index.h"
#include "h3api.h"
#include "localij.h"
#include "test.h"
#include "utility.h"

SUITE(h3Line) {
    TEST(h3Line_acrossMultipleFaces) {
        H3Index start = 0x85285aa7fffffff;
        H3Index end = 0x851d9b1bfffffff;

        int lineSz = H3_EXPORT(h3LineSize)(start, end);
        t_assert(lineSz < 0, "Line not computable across multiple icosa faces");
    }
}

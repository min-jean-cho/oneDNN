/*******************************************************************************
* Copyright 2019-2023 Intel Corporation
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
*     http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*******************************************************************************/

#ifndef GPU_OCL_RNN_RNN_TYPES_H
#define GPU_OCL_RNN_RNN_TYPES_H

#include "gpu/ocl/ocl_types.h"

#if OUTPUT_DT_U8
#define TO_OUTPUT(x) convert_uchar_sat_rte(x)
#elif OUTPUT_DT_S8
#define TO_OUTPUT(x) convert_char_sat_rte(x)
#elif OUTPUT_DT_S32
#define TO_OUTPUT(x) convert_int_sat_rte(x)
#else
#define TO_OUTPUT(x) (x)
#endif

#if INPUT_DT_BF16
#define TO_INPUT(x) cvt_f32_to_bf16(x)
#define TO_REF(x) cvt_bf16_to_f32(x)
#else
#define TO_INPUT(x) (x)
#define TO_REF(x) (float)(x)
#endif

#if DT_F16 && !IS_FWD
#error "FP16 is not supported for BWD"
#endif

#define OFFTYPE ulong
#define TO_WS_STATE(x) TO_SRC(x)

#define OFF6(i0, D0, i1, D1, i2, D2, i3, D3, i4, D4, i5, D5) \
    ((((((i0) * (D1) + (i1)) * (D2) + (i2)) * (D3) + (i3)) * (D4) + (i4)) \
                    * (D5) \
            + (i5))
#define OFF5(i0, D0, i1, D1, i2, D2, i3, D3, i4, D4) \
    (((((i0) * (D1) + (i1)) * (D2) + (i2)) * (D3) + (i3)) * (D4) + (i4))
#define OFF4(i0, D0, i1, D1, i2, D2, i3, D3) \
    ((((i0) * (D1) + (i1)) * (D2) + (i2)) * (D3) + (i3))
#define OFF3(i0, D0, i1, D1, i2, D2) (((i0) * (D1) + (i1)) * (D2) + (i2))
#define OFF2(i0, D0, i1, D1) ((i0) * (D1) + (i1))

#define SRC_L_OFF(x0, x1, x2) \
    (((x0) % SRC_L_B0) * SRC_L_SB0 + ((x0) / SRC_L_B0) * SRC_L_S0 \
            + ((x1) % SRC_L_B1) * SRC_L_SB1 + ((x1) / SRC_L_B1) * SRC_L_S1 \
            + ((x2) % SRC_L_B2) * SRC_L_SB2 + ((x2) / SRC_L_B2) * SRC_L_S2)
#define SRC_I_OFF(x0, x1, x2, x3) \
    (((x0) % SRC_I_B0) * SRC_I_SB0 + ((x0) / SRC_I_B0) * SRC_I_S0 \
            + ((x1) % SRC_I_B1) * SRC_I_SB1 + ((x1) / SRC_I_B1) * SRC_I_S1 \
            + ((x2) % SRC_I_B2) * SRC_I_SB2 + ((x2) / SRC_I_B2) * SRC_I_S2 \
            + ((x3) % SRC_I_B3) * SRC_I_SB3 + ((x3) / SRC_I_B3) * SRC_I_S3)
#define SRC_I_C_OFF(x0, x1, x2, x3) \
    (((x0) % SRC_I_C_B0) * SRC_I_C_SB0 + ((x0) / SRC_I_C_B0) * SRC_I_C_S0 \
            + ((x1) % SRC_I_C_B1) * SRC_I_C_SB1 \
            + ((x1) / SRC_I_C_B1) * SRC_I_C_S1 \
            + ((x2) % SRC_I_C_B2) * SRC_I_C_SB2 \
            + ((x2) / SRC_I_C_B2) * SRC_I_C_S2 \
            + ((x3) % SRC_I_C_B3) * SRC_I_C_SB3 \
            + ((x3) / SRC_I_C_B3) * SRC_I_C_S3)
#define DST_L_OFF(x0, x1, x2) \
    (((x0) % DST_L_B0) * DST_L_SB0 + ((x0) / DST_L_B0) * DST_L_S0 \
            + ((x1) % DST_L_B1) * DST_L_SB1 + ((x1) / DST_L_B1) * DST_L_S1 \
            + ((x2) % DST_L_B2) * DST_L_SB2 + ((x2) / DST_L_B2) * DST_L_S2)
#define DST_I_OFF(x0, x1, x2, x3) \
    (((x0) % DST_I_B0) * DST_I_SB0 + ((x0) / DST_I_B0) * DST_I_S0 \
            + ((x1) % DST_I_B1) * DST_I_SB1 + ((x1) / DST_I_B1) * DST_I_S1 \
            + ((x2) % DST_I_B2) * DST_I_SB2 + ((x2) / DST_I_B2) * DST_I_S2 \
            + ((x3) % DST_I_B3) * DST_I_SB3 + ((x3) / DST_I_B3) * DST_I_S3)
#define DST_I_C_OFF(x0, x1, x2, x3) \
    (((x0) % DST_I_C_B0) * DST_I_C_SB0 + ((x0) / DST_I_C_B0) * DST_I_C_S0 \
            + ((x1) % DST_I_C_B1) * DST_I_C_SB1 \
            + ((x1) / DST_I_C_B1) * DST_I_C_S1 \
            + ((x2) % DST_I_C_B2) * DST_I_C_SB2 \
            + ((x2) / DST_I_C_B2) * DST_I_C_S2 \
            + ((x3) % DST_I_C_B3) * DST_I_C_SB3 \
            + ((x3) / DST_I_C_B3) * DST_I_C_S3)
#define BIAS_OFF(x0, x1, x2, x3) \
    (((x0) % BIAS_B0) * BIAS_SB0 + ((x0) / BIAS_B0) * BIAS_S0 \
            + ((x1) % BIAS_B1) * BIAS_SB1 + ((x1) / BIAS_B1) * BIAS_S1 \
            + ((x2) % BIAS_B2) * BIAS_SB2 + ((x2) / BIAS_B2) * BIAS_S2 \
            + ((x3) % BIAS_B3) * BIAS_SB3 + ((x3) / BIAS_B3) * BIAS_S3)

#define DIFF_SRC_L_OFF(x0, x1, x2) \
    (((x0) % DIFF_SRC_L_B0) * DIFF_SRC_L_SB0 \
            + ((x0) / DIFF_SRC_L_B0) * DIFF_SRC_L_S0 \
            + ((x1) % DIFF_SRC_L_B1) * DIFF_SRC_L_SB1 \
            + ((x1) / DIFF_SRC_L_B1) * DIFF_SRC_L_S1 \
            + ((x2) % DIFF_SRC_L_B2) * DIFF_SRC_L_SB2 \
            + ((x2) / DIFF_SRC_L_B2) * DIFF_SRC_L_S2)
#define DIFF_DST_L_OFF(x0, x1, x2) \
    (((x0) % DIFF_DST_L_B0) * DIFF_DST_L_SB0 \
            + ((x0) / DIFF_DST_L_B0) * DIFF_DST_L_S0 \
            + ((x1) % DIFF_DST_L_B1) * DIFF_DST_L_SB1 \
            + ((x1) / DIFF_DST_L_B1) * DIFF_DST_L_S1 \
            + ((x2) % DIFF_DST_L_B2) * DIFF_DST_L_SB2 \
            + ((x2) / DIFF_DST_L_B2) * DIFF_DST_L_S2)
#define DIFF_SRC_I_OFF(x0, x1, x2, x3) \
    (((x0) % DIFF_SRC_I_B0) * DIFF_SRC_I_SB0 \
            + ((x0) / DIFF_SRC_I_B0) * DIFF_SRC_I_S0 \
            + ((x1) % DIFF_SRC_I_B1) * DIFF_SRC_I_SB1 \
            + ((x1) / DIFF_SRC_I_B1) * DIFF_SRC_I_S1 \
            + ((x2) % DIFF_SRC_I_B2) * DIFF_SRC_I_SB2 \
            + ((x2) / DIFF_SRC_I_B2) * DIFF_SRC_I_S2 \
            + ((x3) % DIFF_SRC_I_B3) * DIFF_SRC_I_SB3 \
            + ((x3) / DIFF_SRC_I_B3) * DIFF_SRC_I_S3)
#define DIFF_DST_I_OFF(x0, x1, x2, x3) \
    (((x0) % DIFF_DST_I_B0) * DIFF_DST_I_SB0 \
            + ((x0) / DIFF_DST_I_B0) * DIFF_DST_I_S0 \
            + ((x1) % DIFF_DST_I_B1) * DIFF_DST_I_SB1 \
            + ((x1) / DIFF_DST_I_B1) * DIFF_DST_I_S1 \
            + ((x2) % DIFF_DST_I_B2) * DIFF_DST_I_SB2 \
            + ((x2) / DIFF_DST_I_B2) * DIFF_DST_I_S2 \
            + ((x3) % DIFF_DST_I_B3) * DIFF_DST_I_SB3 \
            + ((x3) / DIFF_DST_I_B3) * DIFF_DST_I_S3)
#define DIFF_SRC_I_C_OFF(x0, x1, x2, x3) \
    (((x0) % DIFF_SRC_I_C_B0) * DIFF_SRC_I_C_SB0 \
            + ((x0) / DIFF_SRC_I_C_B0) * DIFF_SRC_I_C_S0 \
            + ((x1) % DIFF_SRC_I_C_B1) * DIFF_SRC_I_C_SB1 \
            + ((x1) / DIFF_SRC_I_C_B1) * DIFF_SRC_I_C_S1 \
            + ((x2) % DIFF_SRC_I_C_B2) * DIFF_SRC_I_C_SB2 \
            + ((x2) / DIFF_SRC_I_C_B2) * DIFF_SRC_I_C_S2 \
            + ((x3) % DIFF_SRC_I_C_B3) * DIFF_SRC_I_C_SB3 \
            + ((x3) / DIFF_SRC_I_C_B3) * DIFF_SRC_I_C_S3)
#define DIFF_DST_I_C_OFF(x0, x1, x2, x3) \
    (((x0) % DIFF_DST_I_C_B0) * DIFF_DST_I_C_SB0 \
            + ((x0) / DIFF_DST_I_C_B0) * DIFF_DST_I_C_S0 \
            + ((x1) % DIFF_DST_I_C_B1) * DIFF_DST_I_C_SB1 \
            + ((x1) / DIFF_DST_I_C_B1) * DIFF_DST_I_C_S1 \
            + ((x2) % DIFF_DST_I_C_B2) * DIFF_DST_I_C_SB2 \
            + ((x2) / DIFF_DST_I_C_B2) * DIFF_DST_I_C_S2 \
            + ((x3) % DIFF_DST_I_C_B3) * DIFF_DST_I_C_SB3 \
            + ((x3) / DIFF_DST_I_C_B3) * DIFF_DST_I_C_S3)
#define DIFF_BIAS_OFF(x0, x1, x2, x3) \
    (((x0) % DIFF_BIAS_B0) * DIFF_BIAS_SB0 \
            + ((x0) / DIFF_BIAS_B0) * DIFF_BIAS_S0 \
            + ((x1) % DIFF_BIAS_B1) * DIFF_BIAS_SB1 \
            + ((x1) / DIFF_BIAS_B1) * DIFF_BIAS_S1 \
            + ((x2) % DIFF_BIAS_B2) * DIFF_BIAS_SB2 \
            + ((x2) / DIFF_BIAS_B2) * DIFF_BIAS_S2 \
            + ((x3) % DIFF_BIAS_B3) * DIFF_BIAS_SB3 \
            + ((x3) / DIFF_BIAS_B3) * DIFF_BIAS_S3)

#endif

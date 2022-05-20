// ----------------------------------------------------------------------------
// Copyright 2021 Pelion Ltd.
//
// SPDX-License-Identifier: Apache-2.0
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
// ----------------------------------------------------------------------------
#include "fota_platform_hooks.h"

#if defined(MBED_CLOUD_CLIENT_FOTA_ENABLE)

#if !defined(FOTA_CUSTOM_PLATFORM) || (!FOTA_CUSTOM_PLATFORM)

#include "fota/fota_sub_component.h"

#if 0
static void print_component_info(const char *comp_name, const char *sub_comp_name, const uint8_t *vendor_data, size_t vendor_data_size)
{
    printf("%s component installed\n", comp_name);
    if (sub_comp_name) {
        printf("sub_comp_name: %s\n", sub_comp_name);
    }
    if (vendor_data) {
        printf("vendor_data: %.*s\n", (int)vendor_data_size, vendor_data);
    }
}

static int pdmc_component_verifier(const char *comp_name, const char *sub_comp_name, const uint8_t *vendor_data, size_t vendor_data_size, void* app_ctx)
{
    printf("-----------------------------------------------------------------------------------\n");
    printf("pdmc_component_verifier CB invoked for sub_comp_name: %s, vendor_data: %.*s\n", sub_comp_name, (int)vendor_data_size, vendor_data);
    print_component_info(comp_name, sub_comp_name, vendor_data, vendor_data_size);

    return FOTA_STATUS_SUCCESS;
}

int sub_component_rollback_handler(const char *comp_name, const char *sub_comp_name, const uint8_t *vendor_data, size_t vendor_data_size, void *app_ctx)
{
    printf("-----------------------------------------------------------------------------------\n");
    printf("sub_component_rollback_handler CB invoked for sub_comp_name: %s, vendor_data: %.*s\n", sub_comp_name, (int)vendor_data_size, vendor_data);

    return FOTA_STATUS_SUCCESS;
}

int sub_component_finalize_handler(const char *comp_name, const char *sub_comp_name, const uint8_t *vendor_data, size_t vendor_data_size, fota_status_e fota_status, void *app_ctx)
{
    printf("-----------------------------------------------------------------------------------\n");
    printf("sub_component_finalize_handler CB invoked for sub_comp_name: %s, vendor_data: %.*s\n", sub_comp_name, (int)vendor_data_size, vendor_data);

    return FOTA_STATUS_SUCCESS;
}

int pdmc_component_installer(const char *comp_name, const char *sub_comp_name, fota_comp_candidate_iterate_callback_info *info, const uint8_t *vendor_data, size_t vendor_data_size, void *app_ctx)
{
    switch (info->status) {
        case FOTA_CANDIDATE_ITERATE_START:
            printf("fota candidate iterate start \n");
            return FOTA_STATUS_SUCCESS;
        case FOTA_CANDIDATE_ITERATE_FRAGMENT:
            printf(".");
            return FOTA_STATUS_SUCCESS;
        case FOTA_CANDIDATE_ITERATE_FINISH:
            printf("\nfota candidate iterate finish \n");
            printf("\nApplication received external update\n"); // Use same phrase than in UCHub case. Test case is polling this line.
            print_component_info(comp_name, sub_comp_name, vendor_data, vendor_data_size);
            return FOTA_STATUS_SUCCESS;
        default:
            return FOTA_STATUS_INTERNAL_ERROR;
    }
    return FOTA_STATUS_SUCCESS;
}
#endif

// Default platform hooks
int fota_platform_init_hook(bool after_upgrade)
{
    printf("fota_platform_init_hook\r\n");

#if 0
    fota_sub_comp_info_t dummy_sub_component_desc = { 0 };
    dummy_sub_component_desc.finalize_cb = sub_component_finalize_handler;
    dummy_sub_component_desc.finalize_order = 1;
    dummy_sub_component_desc.install_cb= pdmc_component_installer;
    dummy_sub_component_desc.install_order = 1;
    dummy_sub_component_desc.rollback_cb = sub_component_rollback_handler;
    dummy_sub_component_desc.rollback_order = 3;
    dummy_sub_component_desc.verify_cb= pdmc_component_verifier;
    dummy_sub_component_desc.verify_order = 1;
    int ret = fota_sub_component_add("MAIN","S", &dummy_sub_component_desc); //Component MAIN registered by default during fota initialization, no need to call `fota_component_add` for MAIN component.

    printf("ret: %d\r\n", ret);

    fota_sub_comp_info_t dummy_sub_component_desc2 = { 0 };
    dummy_sub_component_desc2.finalize_cb = sub_component_finalize_handler;
    dummy_sub_component_desc2.finalize_order = 2;
    dummy_sub_component_desc2.install_cb = pdmc_component_installer;
    dummy_sub_component_desc2.install_order = 2;
    dummy_sub_component_desc2.rollback_cb = sub_component_rollback_handler;
    dummy_sub_component_desc2.rollback_order = 2;
    dummy_sub_component_desc2.verify_cb = pdmc_component_verifier;
    dummy_sub_component_desc2.verify_order = 2;
    fota_sub_component_add("MAIN","NS", &dummy_sub_component_desc2);//Component MAIN registered by default during fota initialization, no need to call `fota_component_add` for MAIN component.

    fota_sub_comp_info_t dummy_sub_component_desc3 = { 0 };
    dummy_sub_component_desc3.finalize_cb = sub_component_finalize_handler;
    dummy_sub_component_desc3.finalize_order = 3;
    dummy_sub_component_desc3.install_cb = pdmc_component_installer;
    dummy_sub_component_desc3.install_order = 3;
    dummy_sub_component_desc3.rollback_cb = sub_component_rollback_handler;
    dummy_sub_component_desc3.rollback_order = 1;
    dummy_sub_component_desc3.verify_cb = pdmc_component_verifier;
    dummy_sub_component_desc3.verify_order = 3;
    fota_sub_component_add("MAIN","MODEM", &dummy_sub_component_desc3);//Component MAIN registered by default during fota initialization, no need to call `fota_component_add` for MAIN component.
#endif

    return FOTA_STATUS_SUCCESS;
}

int fota_platform_start_update_hook(const char *comp_name)
{
    return FOTA_STATUS_SUCCESS;
}

int fota_platform_finish_update_hook(const char *comp_name)
{
    return FOTA_STATUS_SUCCESS;
}

int fota_platform_abort_update_hook(const char *comp_name)
{
    return FOTA_STATUS_SUCCESS;
}

#endif // !defined(FOTA_CUSTOM_PLATFORM) || (!FOTA_CUSTOM_PLATFORM)

#endif // defined(MBED_CLOUD_CLIENT_FOTA_ENABLE)


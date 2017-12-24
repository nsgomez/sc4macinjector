/*
 *  injector.cpp
 *  injector
 *
 *  Created by Nelson Gomez on 12/23/17.
 *  Copyright © 2017 Nelson Gomez. All rights reserved.
 *
 */

#include <stdio.h>
#include "cGZCOMLibrary.h"
#include "incompat_msg.h"
#include "rd_route.h"

const char *kszLoadTargetFunc = "__ZN13cGZCOMLibrary4LoadEv";

bool cGZCOMLibrary__Load(cGZCOMLibrary *self)
{
    fprintf(stderr, "Inside the replacement cGZCOMLibrary loader!\n");
    return false;
}

__attribute__((constructor))
static void ctor(void)
{
    // rd_route ignores one leading underscore when searching for symbols,
    // so we'll also skip the first underscore in our symbol string.
    int ret = rd_route_byname(kszLoadTargetFunc + 1, NULL, (void *)cGZCOMLibrary__Load, NULL);
    if (ret == 0) {
        ShowIncompatAlert();
    }
}

﻿#pragma once

// Binary Reading
#include "MakeBinaryReadHeader.h"
#include "schemas/schemas.hpp"
#include "MakeBinaryReadFooter.h"

#ifdef LUCID_SCHEMAS_IMPLEMENTATION
    #include "MakeBinaryWriteHeader.h"
#else
    #include "MakeBinaryWriteHeaderFWD.h"
#endif
#include "schemas/schemas.hpp"
#include "MakeBinaryWriteFooter.h"

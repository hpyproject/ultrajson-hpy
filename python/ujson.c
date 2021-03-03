/*
Developed by ESN, an Electronic Arts Inc. studio.
Copyright (c) 2014, Electronic Arts Inc.
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:
* Redistributions of source code must retain the above copyright
notice, this list of conditions and the following disclaimer.
* Redistributions in binary form must reproduce the above copyright
notice, this list of conditions and the following disclaimer in the
documentation and/or other materials provided with the distribution.
* Neither the name of ESN, Electronic Arts Inc. nor the
names of its contributors may be used to endorse or promote products
derived from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL ELECTRONIC ARTS INC. BE LIABLE
FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.


Portions of code from MODP_ASCII - Ascii transformations (upper/lower, etc)
http://code.google.com/p/stringencoders/
Copyright (c) 2007  Nick Galbreath -- nickg [at] modp [dot] com. All rights reserved.

Numeric decoder derived from from TCL library
http://www.opensource.apple.com/source/tcl/tcl-14/tcl/license.terms
* Copyright (c) 1988-1993 The Regents of the University of California.
* Copyright (c) 1994 Sun Microsystems, Inc.
*/

#include "py_defines.h"
#include "version.h"

/* JSONToobj */

extern HPyDef JSONToObj;
extern HPyDef JSONToObj_decode;
extern HPyDef JSONFileToObj;

/* objToJSON */

void initObjToJSON(void);
extern HPyDef objToJSON;
extern HPyDef objToJSON_encode;
extern HPyDef objToJSONFile;

static HPyDef *module_defines[] = {
    &JSONToObj,
    &JSONToObj_decode,
    &JSONFileToObj,
    &objToJSON,
    &objToJSON_encode,
    &objToJSONFile,
    NULL
};

static HPyModuleDef moduledef = {
  HPyModuleDef_HEAD_INIT,
  .m_name = "ujson_hpy",
  .m_doc = 0,
  .m_size = -1,
  .defines = module_defines,
};


HPy_MODINIT(ujson_hpy)
static HPy init_ujson_hpy_impl(HPyContext ctx)
{
  HPy module;
  HPy version_string;

  initObjToJSON();
  module = HPyModule_Create(ctx, &moduledef);
  if (HPy_IsNull(module)) {
      return HPy_NULL;
  }

  version_string = HPyUnicode_FromString(ctx, UJSON_VERSION);
  if (HPy_IsNull(version_string)) {
      HPy_Close(ctx, module);
      return HPy_NULL;
  }
  HPy_SetAttr_s(ctx, module, "__version__", version_string);
  return module;
}

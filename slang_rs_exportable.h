/*
 * Copyright 2010, The Android Open Source Project
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
 */

#ifndef _FRAMEWORKS_COMPILE_SLANG_SLANG_RS_EXPORTABLE_H_  // NOLINT
#define _FRAMEWORKS_COMPILE_SLANG_SLANG_RS_EXPORTABLE_H_

#include "slang_rs_context.h"

namespace slang {

class RSExportable {
 public:
  enum Kind {
    EX_FUNC,
    EX_TYPE,
    EX_VAR,
    EX_FOREACH
  };

 private:
  RSContext *mContext;

  Kind mK;

 protected:
  RSExportable(RSContext *Context, RSExportable::Kind K)
      : mContext(Context),
        mK(K) {
    Context->newExportable(this);
  }

 public:
  inline Kind getKind() const { return mK; }

  // When keep() is invoked, mKeep will set to true and the associated RSContext
  // won't free this RSExportable object in its destructor. The deallcation
  // responsibility is then transferred to the object who invoked this function.
  // Return false if the exportable is kept or failed to keep.
  virtual bool keep();
  inline bool isKeep() const { return (mContext == nullptr); }

  virtual bool equals(const RSExportable *E) const;

  inline RSContext *getRSContext() const { return mContext; }

  virtual ~RSExportable() { }
};
}  // namespace slang

#endif  // _FRAMEWORKS_COMPILE_SLANG_SLANG_RS_EXPORTABLE_H_  NOLINT

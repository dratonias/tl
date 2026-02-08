# Single-header C base layer
Base layer for myself to replace c std lib
## Usage

```c
#define TL_IMPLEMENTATION //place where implementation should be 
#define TL_ADD_PREFIX //optional when name collision occurs
#define TL_DEFF static //optional prefix for functions
#include "tl.h"
```

## TODO
- strings
- nob.h-style build system
- write generator for macros instead of manually adding
- linear algebra generator
